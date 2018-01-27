// _Exit_Dlg.cpp : implementation file
//

#include "afx.h"
#include "stdafx.h"
#include "Clock.h"
#include "ExitDlg.h"

//#include <afxwin.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CExitDlg dialog

CExitDlg::CExitDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExitDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExitDlg)
	m_timeExit = mStdAfx_TempTime;
	//}}AFX_DATA_INIT
}
//------------------------------------------------------------------------

void CExitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExitDlg)
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_ctrlTime);
	DDX_Control(pDX, IDC_STATIC3, m_timeSDNow);
}
//------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CExitDlg, CDialog)
	//{{AFX_MSG_MAP(CExitDlg)
	//}}AFX_MSG_MAP
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipText)
END_MESSAGE_MAP()
//------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////
// CExitDlg message handlers

void CExitDlg::OnOK() 
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//m_CEdit.GetWindowText(mStdAfx_TempTime);
	//_timeExit =  mStdAfx_TempTime;
	//
	//CString tmp;
	//
	//try
	//{
	//	tmp = mStdAfx_TempTime.operator [](0);
	//	tmp = tmp + mStdAfx_TempTime.operator [](1);

	//	int hh = atoi(tmp);
	//	tmp = "";
	//
	//	tmp = tmp + mStdAfx_TempTime.operator [](3);		
	//	tmp = tmp + mStdAfx_TempTime.operator [](4);		
	//	
	//	int mm = atoi(tmp);
	//	tmp = "";

	//	if((hh>=24||mm>=60) || (mStdAfx_TempTime.operator [](2) != ':')) 
	//	{
	//		MessageBox("Error enter time", "Clock");				
	//		mStdAfx_TempTime = "";
	//		_timeExit = mStdAfx_TempTime;
	//		m_CEdit.SetWindowText(mStdAfx_TempTime);
	//	}
	//	else if(mStdAfx_TempTime == "")
	//	{
	//		MessageBox("Time dont enter", "Clock");				
	//	}
	//	else
	//	{
	//		// TODO: Add extra validation here
	//		CDialog::OnOK();	
	//	}

	//}
	//catch (...)
	//{
	//	mStdAfx_TempTime = "";
	//	_timeExit = mStdAfx_TempTime;
	//	MessageBox("Error enter time", "Clock");
	//}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CTime timeExit;
	DWORD dwResult = m_ctrlTime.GetTime(timeExit);
	if (dwResult == GDT_VALID)
	{
		// the user checked the box and specified data
		CString str = "Time Shot Down is ";

		// is it a time-only control, or a date-only control?
		if ((m_ctrlTime.GetStyle() & DTS_TIMEFORMAT) == DTS_TIMEFORMAT)
		{
			str += timeExit.Format(_T("%X"));
			mStdAfx_TempTime = timeExit.Format(_T("%X"));
		}
		else
		{
			str = timeExit.Format(_T("%x"));
			mStdAfx_TempTime = timeExit.Format(_T("%x"));

		}
		str += "\n"; 
		str += "Confirm this operation";

		if(AfxMessageBox(str, MB_YESNO|MB_ICONQUESTION) == IDYES)
		{
			CDialog::OnOK();
		}
	}
	else
	{
		// the user unmarked the "none" box
		AfxMessageBox(_T("Time not set!"));
		mStdAfx_TempTime = "";
		m_timeExit = mStdAfx_TempTime;
	}

}
//------------------------------------------------------------------------

void CExitDlg::OnCancel()
{
	// TODO: Add extra cleanup here
	
	if(mStdAfx_TempTime != "")
	{
		CString str = "Time Shot Down is " + mStdAfx_TempTime +  "\nDelete this time?";
	
		if(AfxMessageBox(str, MB_YESNO|MB_ICONQUESTION) == IDYES)
		{
			mStdAfx_TempTime = "";
			m_timeExit = mStdAfx_TempTime;
		}
	}

	CDialog::OnCancel();
}
//------------------------------------------------------------------------

BOOL CExitDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	EnableToolTips(true);
	
	m_timeSDNow.SetWindowText(TEXT(mStdAfx_TempTime));
	//m_CEdit.SetWindowText(mStdAfx_TempTime);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
//------------------------------------------------------------------------

BOOL CExitDlg::OnToolTipText( UINT ui, NMHDR* pNMHDR, LRESULT*)
{
		
	TOOLTIPTEXT* pTTT = (TOOLTIPTEXT*) pNMHDR;
	
	if(!(pTTT -> uFlags & TTF_IDISHWND))
		return FALSE;
	
	UINT uID = ::GetDlgCtrlID((HWND) pNMHDR -> idFrom );
/*	
	if( uID != pNMHDR -> idFrom ) // Должна быть эта строка
		return false;


	if( uID != 0 )
		return false;
*/	
	CString ctrTipText;		
	if(uID == 1005)
	{
		if(!ctrTipText.LoadString(IDC_MASKHELP))
			return false;
	}

	if(uID == 0x00000001)
	{
		if(!ctrTipText.LoadString(IDC_MASKOK))
			return false;
	}

	if(uID == 0x00000002)
	{
		if(!ctrTipText.LoadString(IDC_MASKCANCEL))
			return false;
	}

	strncpy(pTTT -> lpszText, ctrTipText, 80);
	return true;
}
//------------------------------------------------------------------------
