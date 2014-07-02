#if !defined(AFX_DLGDIAGRAMME_H__3F35B527_88D4_42EC_B9C6_E3FC6694E31B__INCLUDED_)
#define AFX_DLGDIAGRAMME_H__3F35B527_88D4_42EC_B9C6_E3FC6694E31B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDiagramme.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDiagramme dialog

class CDlgDiagramme : public CDialog
{
// Construction
public:
	CDlgDiagramme(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDiagramme)
	enum { IDD = IDD_DIALOG_FREQUENCE };
	int		m_nFreqMoins;	//Gamme de fréquence
	int		m_nFreqPlus;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDiagramme)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDiagramme)
	afx_msg void OnChangeEditFreqmoins();	//Changement de fréquence
	afx_msg void OnChangeEditFreqplus();
	afx_msg void OnPaint();	//Affichage du signal
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDIAGRAMME_H__3F35B527_88D4_42EC_B9C6_E3FC6694E31B__INCLUDED_)
