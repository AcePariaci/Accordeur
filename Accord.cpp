// Accord.cpp: implementation of the CAccord class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <math.h>
#include "Accordage Guitare.h"
#include "Accord.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


const double CAccord::m_fNoteEtalon[18]=
{
	//Valeur des fr�quences des notes de la port�e � 0
	32.7,	//DO 0 etc...
	34.65,
	34.65,
	36.7,
	38.9,
	38.9,
	41.2,
	43.65,
	46.25,
	46.25,
	49,
	51.95,
	51.95,
	55,
	58.25,
	58.25,
	61.75,
	61.75
};


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAccord::CAccord()
{
	//Constructeur par d�faut 
	Initialisation();	//Initialisation des varaiables
	
}

CAccord::~CAccord()
{
	//Destructeur par d�faut
}

CAccord::CAccord(CString NomAccord, CString Notes)
{
	//Constructeur avec nom de l'accord et des notes
	Initialisation();	//Initialisation des variables
	m_szNomAccord=NomAccord;	//Mise � jour du nom de l'accord
	m_szNotes=Notes;	//Mise � jour du nom de toutes les notes
	CalculNotes(m_szNotes);	//Mise � jour du nom et de la fr�quence des 6 notes
}

float CAccord::GetValeurNote(int Index)
{
	return m_fNotes[Index];	//Retourne la fr�quence de la note suivant sa position
}

void CAccord::SetAccord(CString NomAccord, CString Notes)
{
	//Mise � jour de l'accord
	m_szNomAccord=NomAccord;	//Initialisation des variables
	m_szNotes=Notes;	//Mise � jour du nom de l'accord
	CalculNotes(m_szNotes);	//Mise � jour du nom et de la fr�quence des 6 notes
}

CString CAccord::GetNomAccord()
{
	return m_szNomAccord;	//Retourne le nom de l'accord
}

CString CAccord::GetNomNote(int Index)
{
	return m_szarNotes[Index];	//Retourne le nom de la note en fonction de sa position
}

void CAccord::CalculNotes(CString Notes)
{
	//Mise � jour du nom et de la fr�quence des 6 notes
	POSITION pos;//Postion du tableau CMap	
	int j=0,Debut=0;	//Index

	m_szarNotes.RemoveAll();	//On enl�ve toutes les entr�es du tableau des noms des notes

	for (int i=0;((i<6) && (m_bAccord));i++)	//Pour les 6 notes et si l'accord est valide
	{
		CString Note,Valeur;	//Nom de la note et nom de la note dans la tableau CMap
		int Harmo,cle;

		while (Notes.Mid(j,1).SpanIncluding("0123456789").IsEmpty()!=NULL)
			//Tant que l'on n'a pas de chiffre
		{
			j++;	//On passe � l'autre caract�re
		}
		
		//On a trouv� le chiffre
		Note=Notes.Mid(Debut,j-Debut);	//Sauvegarde du nom de la note
		Harmo=(int)(Notes.GetAt(j)-48);	//et de la hauteur de la note

		j++;	//Prochain caract�re
		Debut=j;	//Sauvegarde

		pos=MapIndexNote.GetStartPosition();	//Mise � jour du d�but du tableau CMap

		while((pos!=NULL) && (Note!=Valeur))
			//Tant que l'on n'a pas trouv� la Note et pas � la fin du tableau
		{
			MapIndexNote.GetNextAssoc(pos,cle,Valeur);	//R�cup�ration de la note, de l'index et de la prochaine position
		}

		if (Note!=Valeur)	//Si la note trouv�e n'est pas celle recherch�e
		{
			//Affichage d'une boite de dialogue "Accord erron�"
			CString mes;

			mes.Format("Votre accord %s est erron�",GetNomAccord());

			AfxMessageBox(mes,MB_OK || MB_ICONSTOP );

			m_bAccord=FALSE;
		}
		else
		{
			//Autrement sauvegarde du nom de la note et de sa fr�quence
			CString szNote;
			double t = 2;
			m_fNotes[i]=m_fNoteEtalon[cle]*pow(t,Harmo);
			szNote.Format("%s%d",Note,Harmo);
			m_szarNotes.Add(szNote);
		}
	}
}

BOOL CAccord::GetValiditeAccord()
{
	//Retourne la validit� de l'accord
	return m_bAccord;
}

void CAccord::Initialisation()
{
	//Initialise touts les noms des notes
	MapIndexNote.SetAt(0,"DO");
	MapIndexNote.SetAt(1,"DO#");
	MapIndexNote.SetAt(2,"REb");
	MapIndexNote.SetAt(3,"RE");
	MapIndexNote.SetAt(4,"RE#");
	MapIndexNote.SetAt(5,"MIb");
	MapIndexNote.SetAt(6,"MI");
	MapIndexNote.SetAt(7,"FA");
	MapIndexNote.SetAt(8,"FA#");
	MapIndexNote.SetAt(9,"SOLb");
	MapIndexNote.SetAt(10,"SOL");
	MapIndexNote.SetAt(11,"SOL#");
	MapIndexNote.SetAt(12,"LAb");
	MapIndexNote.SetAt(13,"LA");
	MapIndexNote.SetAt(14,"LA#");
	MapIndexNote.SetAt(15,"SIb");
	MapIndexNote.SetAt(16,"SI");
	MapIndexNote.SetAt(17,"DOb");

	m_bAccord=TRUE;	//Validit� de l'accord � vrai
}
