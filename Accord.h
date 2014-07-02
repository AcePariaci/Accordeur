// Accord.h: interface for the CAccord class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACCORD_H__71CB57B9_51D3_4A4A_8B02_801FEA969C6C__INCLUDED_)
#define AFX_ACCORD_H__71CB57B9_51D3_4A4A_8B02_801FEA969C6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAccord  
{
public:
	BOOL GetValiditeAccord();	//Retourne la validit� de l'accord (toutes les notes connues)
	CString GetNomNote(int Index);	//Retourne le nom de la note en fonction de sa position
	CString GetNomAccord(void);	//Retourne le nom de l'accord
	void SetAccord(CString NomAccord,CString Notes);	//Met � jour le nom de l'accord, le string des notes, la fr�quence des notes
	float GetValeurNote(int Index);	//Retourne la fr�quence de la note en fonction de sa position
	CAccord(CString NomAccord,CString Notes);	//M�me chose que SetNomAccord mais en constructeur
	CAccord();	//Constructeur par d�faut
	virtual ~CAccord();	//Detructeur

private:
	void Initialisation();	//Initialisation des variables
	CStringArray m_szarNotes;	//Nom de toutes les notes
	BOOL m_bAccord;	//Validit� de l'accord
	static const double m_fNoteEtalon[18];	//Valeur de toutes les notes de la port�e
	double m_fNotes[6];	//Valeur des 6 notes de l'accord
	void CalculNotes(CString Notes);	//Mise � jour de la fr�quence des notes en fonction du nom des notes
	CString m_szNotes;	//Valeur de toutes les notes
	CString m_szNomAccord;	//Valeur de l'accord
	CMap<int,int,CString,CString>MapIndexNote;	//Nom de toutes les notes de la port�e
};

#endif // !defined(AFX_ACCORD_H__71CB57B9_51D3_4A4A_8B02_801FEA969C6C__INCLUDED_)
