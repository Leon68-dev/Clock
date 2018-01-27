//{{AFX_INCLUDES()

//}}AFX_INCLUDES
#if !defined(AFX__CALENDARDLG_H__01CA7B94_8B61_4480_BA08_7058AC9FB712__INCLUDED_)
#define AFX__CALENDARDLG_H__01CA7B94_8B61_4480_BA08_7058AC9FB712__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// _CalendarDlg.h : header file
//

#include "afxdtctl.h"

/////////////////////////////////////////////////////////////////////////////
// CCalendarDlg dialog

class CCalendarDlg : public CDialog
{
// Construction
public:
	CCalendarDlg(CWnd* pParent = NULL);   // standard constructor
	
	void OnSetDate();
// Dialog Data
	//{{AFX_DATA(CCalendarDlg)
	enum { IDD = IDD_CALENDAR_DIALOG };
	//CMonthCalCtrl	m_Calen;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalendarDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCalendarDlg)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CMonthCalCtrl m_Calendar;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX__CALENDARDLG_H__01CA7B94_8B61_4480_BA08_7058AC9FB712__INCLUDED_)
