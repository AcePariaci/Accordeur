// Accordage GuitareDlg.h : header file
//

#if !defined(AFX_ACCORDAGEGUITAREDLG_H__4B5A0FF8_FAF0_4262_AFD9_C38A95920287__INCLUDED_)
#define AFX_ACCORDAGEGUITAREDLG_H__4B5A0FF8_FAF0_4262_AFD9_C38A95920287__INCLUDED_

#include "DlgDiagramme.h"	// Added by ClassView
#include "Accord.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAccordageGuitareDlg dialog

class CAccordageGuitareDlg : public CDialog
{
// Construction
public:
	float * ImagO;	//Pointeur sur l'imaginaire Out
	float * RealO;	//Pointeur sur le réel out
	float* ImagIn;	//Pointeur sur l'imaginaire In
	float * RealIn;	//Pointeur sur le réel in
	WAVEHDR Buffer;	//Structure du buffer
	HWAVEIN* Handle;	//Structure du Handle
	CAccordageGuitareDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAccordageGuitareDlg)
	enum { IDD = IDD_ACCORDAGEGUITARE_DIALOG };
	CButton	m_btnGO;	//Contrôle Bouton GO
	CComboBox	m_cboAccord;	//Contrôle Combo Accord
	CSliderCtrl	m_ctlSlider;	//Contrôle Slider
	CComboBox	m_cboCarteSon;	//Contrôle Combo Carte Son
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAccordageGuitareDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAccordageGuitareDlg)
	virtual BOOL OnInitDialog();	//Initialisation de la fenêtre Mère
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();	//Mise à jour de la fenêtre
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnGo();	//Appui sur le bouton GO
	afx_msg void OnStop();	//Appui sur le bouton Stop
	afx_msg void OnClose();	//Fermeture de la fenêtre 
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//Changement de position du Slider
	afx_msg void OnSelchangeComboAccord();	//Changement d'accord 
	afx_msg void OnSelchangeComboCarteson();	//Changement de carte son
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void UpdateFrequence();	//Mise à jour de la fréquence lors du changement de note
	CStringArray m_arszAccords;	//Tableau de tous les accords
	CStringArray m_arszNotes;	//Tableau de toutes les notes de chaque accord
	CAccord m_acAccord;	//Variable de classe CAccord
	CDlgDiagramme m_dlgDiagramme;	//Variable de la fenêtre Diagramme
	BOOL bGO;	//A-t-on démarré le traitement
	CWinThread* Thread;	//Thread pour le traitement du signal
	static UINT ThreadFunc(LPVOID pParam);	//Procédure pour le traitement du signal
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACCORDAGEGUITAREDLG_H__4B5A0FF8_FAF0_4262_AFD9_C38A95920287__INCLUDED_)
