// DlgDiagramme.cpp : implementation file
//

#include "stdafx.h"
#include "mmsystem.h"
#include <math.h>

#include "FFT.h"
#include "Accordage Guitare.h"
#include "Accordage GuitareDlg.h"

#include "DlgDiagramme.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDiagramme dialog


CDlgDiagramme::CDlgDiagramme(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDiagramme::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDiagramme)
	m_nFreqMoins = 0;
	m_nFreqPlus = 0;
	//}}AFX_DATA_INIT
}


void CDlgDiagramme::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDiagramme)
	DDX_Text(pDX, IDC_EDIT_FREQMOINS, m_nFreqMoins);
	DDX_Text(pDX, IDC_EDIT_FREQPLUS, m_nFreqPlus);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDiagramme, CDialog)
	//{{AFX_MSG_MAP(CDlgDiagramme)
	ON_EN_CHANGE(IDC_EDIT_FREQMOINS, OnChangeEditFreqmoins)
	ON_EN_CHANGE(IDC_EDIT_FREQPLUS, OnChangeEditFreqplus)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDiagramme message handlers

void CDlgDiagramme::OnChangeEditFreqmoins() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here

	//Changement de fréquence mise à jour de la fenêtre

		OnPaint();


	
}

void CDlgDiagramme::OnChangeEditFreqplus() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here

		//Changement de fréquence mise à jour de la fenêtre


	OnPaint();

	
}

void CDlgDiagramme::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages

	//Affichage des barres à chaque fréquence suivant l'amplitude du signal

	float LargeurFrequence,FrequenceCours;	//Variable pour la gamme de fréquence et la fréquence à afficher
	CPen lSolidPen(PS_SOLID,1,RGB(255,0,0)),*oldPen,penVert(PS_SOLID,1,RGB(0,255,0));
	//Pinceau pour la barre, le vieux pinceau et la fréquence étalon
	CAccordageGuitareDlg *dlg;	//Pointeur sur la fenêtre Mère

	dlg=(CAccordageGuitareDlg*)GetOwner();	//On le retrouve

	if (dlg->ImagIn!=NULL)	//Si un tableau de valeur existe
	{
		DWORD IndexFreqDebut,IndexFreqFin,i;	//Fréquence de début, de fin et un Index
		CRect rcDiagramme;	//Coordonnées de la fenêtre
		float AffichageFreq=0;	//Position de la fréquence

		GetClientRect(&rcDiagramme);	//On retrouve les coordonnées

		CPoint Courant(0,rcDiagramme.bottom);	//Le point de la fréquence en cours


		UpdateData();	//Mise à jour de la fréquence + et -

		FrequenceCours=(float)(m_nFreqMoins);	//1er fréquence à afficher
		LargeurFrequence=(float)rcDiagramme.Width();	
		LargeurFrequence/=(float)(m_nFreqPlus-m_nFreqMoins);	//On retrouve la plage de fréquence en fonction de la largeur de la fenêtre
		IndexFreqDebut=(m_nFreqMoins*(dlg->Buffer.dwBufferLength/2))/44100;

		//Index de la fréquence de début dans le tableau des données fréquentielles
		IndexFreqFin=(m_nFreqPlus*(dlg->Buffer.dwBufferLength/2))/44100;
		
		//On sélectionne le pinceau vert
		oldPen=dc.SelectObject(&penVert);

		//On fait un trait au milieu
		dc.MoveTo(rcDiagramme.Width()/2,rcDiagramme.bottom);
		dc.LineTo(rcDiagramme.Width()/2,rcDiagramme.top);

		//On sélectionne le pinceau rouge
		dc.SelectObject(&lSolidPen);

		//Pour la plage de fréquence
		for (i=IndexFreqDebut;i<=IndexFreqFin;i++)
		{
			float mag,freq;	//Variable pour l'amplitude et la fréquence à afficher
			int Hauteur;	//Hauteur de la fenêtre

			Hauteur=rcDiagramme.Height()/2;	//Moitié de fenêtre

			mag=(float)(sqrt(pow(dlg->RealO[i],2)+pow(dlg->ImagO[i],2)));
			//On retrouve l'amplitude du signal

			dc.MoveTo(Courant);
			//On va au point en cours

			int essai;
			float calcul;

			//Calcul de la hauteur de la barre
			calcul=(float)(Hauteur*mag/1E08);
			essai=(int)calcul;

			//Tracage de la barre
			dc.LineTo(Courant.x,Courant.y-essai); 

			//On passe à la fréquence suivante
			freq=(float)((44100*(i+1))*2);
			freq/=dlg->Buffer.dwBufferLength;

			//Mise à jour de la	position de la fréquence sur la fenêtre
			AffichageFreq+=(freq-FrequenceCours)*LargeurFrequence;

			//Mise à jour du point
			Courant.x=(long)AffichageFreq;

			//Prochaine fréquence
			FrequenceCours=freq;
		}

		dc.SelectObject(oldPen);	//On reprend l'ancien pinceau
	}
}
