// Accordage GuitareDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mmsystem.h"
#include <math.h>
#include "Accord.h"

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
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAccordageGuitareDlg dialog

CAccordageGuitareDlg::CAccordageGuitareDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAccordageGuitareDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAccordageGuitareDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAccordageGuitareDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAccordageGuitareDlg)
	DDX_Control(pDX, ID_GO, m_btnGO);
	DDX_Control(pDX, IDC_COMBO_ACCORD, m_cboAccord);
	DDX_Control(pDX, IDC_SLIDER_NOTES, m_ctlSlider);
	DDX_Control(pDX, IDC_COMBO_CARTESON, m_cboCarteSon);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAccordageGuitareDlg, CDialog)
	//{{AFX_MSG_MAP(CAccordageGuitareDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_GO, OnGo)
	ON_BN_CLICKED(ID_STOP, OnStop)
	ON_WM_CLOSE()
	ON_WM_HSCROLL()
	ON_CBN_SELCHANGE(IDC_COMBO_ACCORD, OnSelchangeComboAccord)
	ON_CBN_SELCHANGE(IDC_COMBO_CARTESON, OnSelchangeComboCarteson)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAccordageGuitareDlg message handlers

BOOL CAccordageGuitareDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);


	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	m_ctlSlider.SetRange(0,5,TRUE);	//Range du Slider (0 � 5 = 6 notes)


	ImagIn=NULL;	//Imaginaire In � NULL

	UINT NbreCarteSon;	//Variable pour le nombre de cartes son
	WAVEINCAPS caracteristiques;	//Variable pour les caract�ristiques de la carte son


	NbreCarteSon=waveInGetNumDevs();	//On r�cup�re le nombre de carte son

	for (UINT i=0;i<NbreCarteSon;i++)	//Pour chaque carte son
	{
		DWORD support;	//Variable pour le type de support (Dans notre cas 16 bits Mono)

		waveInGetDevCaps(i,&caracteristiques,sizeof(WAVEINCAPS));	//On r�cup�re les caract�ristiques de la carte son

		support=caracteristiques.dwFormats & WAVE_FORMAT_4M16;	
		if (support==WAVE_FORMAT_4M16)	//Si carte son supporte 16 bits Mono
		{
			m_cboCarteSon.AddString(caracteristiques.szPname);	//On l'ajoute au combo carte son
			m_cboCarteSon.SetItemData(m_cboCarteSon.GetCount()-1,i);	//Et on lui rattache un Data
		}
	}
	if (m_cboCarteSon.GetCount()>0)	//On affiche la premi�re carte son valide
		m_cboCarteSon.SetCurSel(0);

	
	TCHAR szPath[MAX_PATH],szNom[9],szNote[8],szNmrAccord[3];	//Variable pour le chemin du fichier ini, du nom de l'accord, des notes de l'accord, du num�ro de l'accord du fichier ini
	int NbreAccord=1;	//Num�ro d'accord courant
	char szAccord[80],szNotes[80];	//Variable pour le nom courant de l'accord et de la s�rie de notes qui le compose
	DWORD retour;	//Variable pour savoir si un accord et des notes ont �t� charg�

	GetCurrentDirectory(MAX_PATH, szPath);	//On retrouve le chemin du fichier ini

	strcat(szPath,"\\Accords.ini");	//On ajoute son nom

	do	//Faire
	{

		strcpy(szNom,"Accord");	//Mise � jour du nom variable accord
		strcpy(szNote,"Notes");	//Mise � jour du nom variable note

		sprintf(szNmrAccord,"%d",NbreAccord);	//On ajoute le num�ro courant de l'accord

		strcat(szNom,szNmrAccord);	// � l'accord
		strcat(szNote,szNmrAccord);	//et � la note

		retour=GetPrivateProfileString("NOM",szNom,"",szAccord,sizeof(szAccord),szPath);
		//On charge le nom de l'accord
		retour=GetPrivateProfileString("NOTES",szNote,"",szNotes,sizeof(szNotes),szPath);
		//et le nom des notes
		if (retour!=0)	//Si on a bien trouv� un accord et des notes
		{
			m_cboAccord.AddString(szAccord);	//On ajoute le nom de l'accord � la combo
			m_arszAccords.Add(szAccord);	//et au tableau des accords
			m_arszNotes.Add(szNotes);	//et au tableau des notes
		}

		NbreAccord++;	//Au prochain accord
	}

	while (retour!=0);	//Tant qu'il y a des accords


	m_cboAccord.SetCurSel(0);	//Affiche le premier accord	

	Handle=NULL;	//Buffer des donn�es musicaux � NULL	

	OnSelchangeComboCarteson();	//Vers la proc�dure de changement de carte son


	CWnd* Desktop;	//Pointeur sur le bureau

	Desktop=GetDesktopWindow();	//Mise � jour du pointeur
	m_dlgDiagramme.Create(IDD_DIALOG_FREQUENCE,this);	//Cr�ation de la fen�tre Diagramme
	m_dlgDiagramme.ShowWindow(SW_SHOW);	//Affichage

	CRect Diagramme,dlg,Bureau;	//Coordonn�es de la fen�tre Diagramme, Accordage et bureau

	Desktop->GetWindowRect(&Bureau);	//On r�cup�re les coordonn�es du bureau

	GetWindowRect(&dlg);	//De la fen�tre principale

	SetWindowPos(&wndTop,Bureau.Width()-dlg.Width(),10,0,0,SWP_NOSIZE);	//on l'a met � fond � droite

	GetWindowRect(&dlg);	//On r�cup�re les nouvelles coordonn�es


	m_dlgDiagramme.SetWindowPos(&wndTop,0,0,Bureau.Width()-dlg.Width(),Bureau.Height(),SWP_SHOWWINDOW);
	//On met la fen�tre diagramme � fond � gauche
	OnSelchangeComboAccord();
	//Appel de la proc�dure Changement d'accord

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAccordageGuitareDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAccordageGuitareDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAccordageGuitareDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


UINT CAccordageGuitareDlg::ThreadFunc(LPVOID pParam)
{
	//Thread pour la passer les donn�es audio de temporel � fr�quentiel
	CAccordageGuitareDlg *dlg=(CAccordageGuitareDlg*)pParam;
	//On r�cup�re le pointeur de la fen�tre principale


	while (dlg->bGO==TRUE)	//Tant qu'on arr�te pas l'analyse
	{
		MMRESULT resultat;	//R�sultat de l'�tat de r�cup�ration des donn�es audio

		resultat=waveInAddBuffer(*dlg->Handle,&dlg->Buffer,sizeof(dlg->Buffer));
		//On met � jour le buffer des donn�es
		if (dlg->Buffer.dwBytesRecorded!=0)	//S'il y a des donn�es d'enregistr�es
		{
			CFFT fft;	//Variable FFT

			signed short *sRealI;	//Variable pour les donn�es en short
			DWORD octets,i;	//Du nombre d'octets enregistr�es, Index

			octets=dlg->Buffer.dwBytesRecorded/2;	//Nombre d'�chantillons 
			

			sRealI=(short*)&dlg->Buffer.lpData[0];	//On met � jour le tableau 

			for (i=0;i<octets;i++)
			{
				dlg->RealIn[i]=(float)sRealI[i];	//on le passe en float

				dlg->ImagIn[i]=0;	//et on met les imaginaires � z�ro
			}

 
			
			fft.fft_float(octets,0, dlg->RealIn,dlg->ImagIn,dlg->RealO,dlg->ImagO);
			//On passe en fr�quentiel
			
			CDlgDiagramme *Diagramme;

			Diagramme=&dlg->m_dlgDiagramme;

			if (Diagramme!=NULL)
				Diagramme->InvalidateRect(NULL);	//On affiche les diff�rentes fr�quences 			
		}
		
	} 
	return 0;
}

void CAccordageGuitareDlg::OnStop() 
{
	// TODO: Add your control notification handler code here
	//Arr�t du Thread

	bGO=FALSE;	//Bool�en � Faux

	if(Thread!=NULL)	//S'il y a un thread
		::WaitForSingleObject(Thread,INFINITE);	//On l'arr�te en attendant le fin des calculs

	Thread=NULL;	//On met le thread � NULL
	
}

void CAccordageGuitareDlg::OnGo() 
{
	// TODO: Add your control notification handler code here
	LPVOID pParam;	//Pointeur sur les param�tres � fournir

	if (ImagIn==NULL)	//Si on n'a pas initialis� les tableaux
	{

		RealIn=new float[Buffer.dwBufferLength];	//On le fait
		ImagIn=new float[Buffer.dwBufferLength];
		RealO=new float[Buffer.dwBufferLength];
		ImagO=new float[Buffer.dwBufferLength];
	}

	bGO=TRUE;	//Bool�en � True
	pParam=this;	//On passe la fen�tre principale comme param�tre
	Thread=AfxBeginThread(ThreadFunc,pParam,THREAD_PRIORITY_IDLE);	//On d�marre le thread
}


void CAccordageGuitareDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	//Fermeture de la fen�tre
	MMRESULT resultat;
	DWORD res;
	
	if (Thread!=NULL)	//S'il y a un thread
	{
		bGO=FALSE;	//Bool�en � Faux
		res=::WaitForSingleObject(Thread,INFINITE);	//On attend la fin du thread
	}
	resultat=waveInStop(*Handle);	//On arr�te d'enregistrer

	resultat=waveInUnprepareHeader(*Handle,&Buffer,sizeof(Buffer));	//On lib�re la m�moire

	delete Handle;	//On supprime le pointeur

	delete Buffer.lpData;	//ainsi que les donn�es
	
	if (ImagIn!=NULL)	//si le tableau de donn�es existe
	{
		delete ImagIn;
		delete ImagO;	//on les supprime
		delete RealIn;
		delete RealO;
	}
	
	CDialog::OnClose();	//On ferme la fen�tre
}


void CAccordageGuitareDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	//Mise � jour du Slider
	UpdateFrequence();	//Mise � jour de la fr�quence (Note)

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CAccordageGuitareDlg::OnSelchangeComboAccord() 
{
	// TODO: Add your control notification handler code here

	//Changement d'accord

	CStatic *pStatic;	//pointeur sur les diff�rents Labels des notes
	CString szAccord;	//Nom de l'accord

	szAccord=m_arszAccords[m_cboAccord.GetCurSel()];	//On retrouve le nom de l'accord
	m_acAccord.SetAccord(szAccord,m_arszNotes[m_cboAccord.GetCurSel()]);	
	//Met � jour la variable Accord

	m_btnGO.EnableWindow(m_acAccord.GetValiditeAccord());	//Inhibe ou non le bouton Go 
	//en fonction de la validit� de l'accord

	if (m_acAccord.GetValiditeAccord())	//Si accord valide
	{

		for (int i=0;i<6;i++)	//Pour les 6 notes
		{		

			pStatic=(CStatic*)GetDlgItem(IDC_STATIC_1+i);	//Pointeur du label

			pStatic->SetWindowText(m_acAccord.GetNomNote(i));	//Met � jour le nom de la notes
		}
		UpdateFrequence();	//Met � jour les fr�quence + et - du diagramme

	}
	
	
}

void CAccordageGuitareDlg::UpdateFrequence()
{
	//Mise � jour des fr�quences + et - du Diagramme
	float freq,freqDelta;	//Fr�quence en cours

	freq=m_acAccord.GetValeurNote(m_ctlSlider.GetPos());	//Retourne la freq d'accordage

	freqDelta=freq/10;	//Affectation de la valeur Delta

	if (freqDelta>20)	//Si Delta>20 Hz alors Delta=20hz
		freqDelta=20;

	m_dlgDiagramme.m_nFreqMoins=(int)(freq-freqDelta);	//Mise � jour de Fr�quence -
	m_dlgDiagramme.m_nFreqPlus=(int)(freq+freqDelta);	//Mise � jour Fr�quence + 

	m_dlgDiagramme.UpdateData(FALSE);	//Mise � jour des champs

	m_dlgDiagramme.InvalidateRect(NULL);	//Mise � jour de la fen�tre
}

void CAccordageGuitareDlg::OnSelchangeComboCarteson() 
{
	// TODO: Add your control notification handler code here
	//Changement de carte son

	WAVEFORMATEX Format;	//Variable sur le format
	MMRESULT resultat;	//Resultat de l'op�ration
	double Samples=19;	//Echantillons �gal � 2^19

	OnStop();	//On arr�te l'�chantillonnage et le thread

	if (Handle!=NULL)	//Si on avait d�j� un Handle pour la carte son
	{

		resultat=waveInStop(*Handle);	//On arr�te l'enregistrement

		resultat=waveInUnprepareHeader(*Handle,&Buffer,sizeof(Buffer));	//On nettoie le buffer

		delete Handle;	//Suppression du Handle

		delete Buffer.lpData;	//et des donn�es
	}
	
	


	Handle=new HWAVEIN;	//Nouvelle allocation pour le Handle

	Format.wFormatTag=WAVE_FORMAT_PCM;	//Mise � jour du format
	Format.nChannels=1;
	Format.nSamplesPerSec=44100;
	Format.wBitsPerSample=16;
	Format.nBlockAlign=(Format.nChannels*Format.wBitsPerSample)/8;
	Format.nAvgBytesPerSec=Format.nSamplesPerSec*Format.nBlockAlign;
	Format.cbSize=0;

	resultat=waveInOpen(Handle,m_cboCarteSon.GetItemData(m_cboCarteSon.GetCurSel()),&Format,NULL,NULL,CALLBACK_NULL);
	//Ouverture pour enregistrement
	int t = 2;
	Buffer.dwBufferLength=(DWORD)pow(t,Samples);	//Longueur du buffer
	Buffer.dwFlags=0;	//Mise � z�ro du flag

	Buffer.lpData= new char[Buffer.dwBufferLength];	//Allocation des donn�es
	Buffer.dwBytesRecorded=0;	//Pas d'enregistrement pour l'instant
	
	resultat=waveInPrepareHeader(*Handle,&Buffer,sizeof(Buffer));	//Pr�paration � l'enregistrement

	resultat=waveInStart(*Handle);	//d�but de l'enregistrement
	
}
