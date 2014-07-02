// Accordage Guitare.h : main header file for the ACCORDAGE GUITARE application
//

#if !defined(AFX_ACCORDAGEGUITARE_H__3EE8DFFD_B030_4381_A5F0_BDB67047699D__INCLUDED_)
#define AFX_ACCORDAGEGUITARE_H__3EE8DFFD_B030_4381_A5F0_BDB67047699D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAccordageGuitareApp:
// See Accordage Guitare.cpp for the implementation of this class
//

class CAccordageGuitareApp : public CWinApp
{
public:
	CAccordageGuitareApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAccordageGuitareApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAccordageGuitareApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACCORDAGEGUITARE_H__3EE8DFFD_B030_4381_A5F0_BDB67047699D__INCLUDED_)
