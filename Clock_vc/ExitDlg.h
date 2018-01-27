//{{AFX_INCLUDES()

//}}AFX_INCLUDES
#include "afxdtctl.h"
#include "afxwin.h"
#if !defined(AFX__EXIT_DLG_H__59666D13_1399_11D3_A0C2_008048D9775E__INCLUDED_)
#define AFX__EXIT_DLG_H__59666D13_1399_11D3_A0C2_008048D9775E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// _Exit_Dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExitDlg dialog


class CExitDlg : public CDialog
{
// Construction
public:
	CExitDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CExitDlg)
	enum { IDD = IDD_SETEXIT_DIALOG };
	//}}AFX_DATA
	CString m_timeExit;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExitDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CExitDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	BOOL OnToolTipText( UINT, NMHDR* pNMHDR, LRESULT*);
	DECLARE_MESSAGE_MAP()
public:
	CDateTimeCtrl m_ctrlTime;
	CStatic m_timeSDNow;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX__EXIT_DLG_H__59666D13_1399_11D3_A0C2_008048D9775E__INCLUDED_)
