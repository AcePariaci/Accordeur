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
	BOOL GetValiditeAccord();	//Retourne la validité de l'accord (toutes les notes connues)
	CString GetNomNote(int Index);	//Retourne le nom de la note en fonction de sa position
	CString GetNomAccord(void);	//Retourne le nom de l'accord
	void SetAccord(CString NomAccord,CString Notes);	//Met à jour le nom de l'accord, le string des notes, la fréquence des notes
	float GetValeurNote(int Index);	//Retourne la fréquence de la note en fonction de sa position
	CAccord(CString NomAccord,CString Notes);	//Même chose que SetNomAccord mais en constructeur
	CAccord();	//Constructeur par défaut
	virtual ~CAccord();	//Detructeur

private:
	void Initialisation();	//Initialisation des variables
	CStringArray m_szarNotes;	//Nom de toutes les notes
	BOOL m_bAccord;	//Validité de l'accord
	static const double m_fNoteEtalon[18];	//Valeur de toutes les notes de la portée
	double m_fNotes[6];	//Valeur des 6 notes de l'accord
	void CalculNotes(CString Notes);	//Mise à jour de la fréquence des notes en fonction du nom des notes
	CString m_szNotes;	//Valeur de toutes les notes
	CString m_szNomAccord;	//Valeur de l'accord
	CMap<int,int,CString,CString>MapIndexNote;	//Nom de toutes les notes de la portée
};

#endif // !defined(AFX_ACCORD_H__71CB57B9_51D3_4A4A_8B02_801FEA969C6C__INCLUDED_)
