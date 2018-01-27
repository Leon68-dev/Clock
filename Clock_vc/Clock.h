// Clock.h : main header file for the Clock application
//

#if !defined(AFX_Clock_H__BA28C1C5_FF30_11D2_A088_008048D9775E__INCLUDED_)
#define AFX_Clock_H__BA28C1C5_FF30_11D2_A088_008048D9775E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

//myStr timeStr();
	
/////////////////////////////////////////////////////////////////////////////
// CClockApp:
// See Clock.cpp for the implementation of this class
//

class CClockApp : public CWinApp
{
public:
	CClockApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClockApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CClockApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_Clock_H__BA28C1C5_FF30_11D2_A088_008048D9775E__INCLUDED_)
