// _CalendarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Clock.h"
#include "CalendarDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalendarDlg dialog


CCalendarDlg::CCalendarDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCalendarDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalendarDlg)
	//}}AFX_DATA_INIT

	OnSetDate();
}


void CCalendarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalendarDlg)
	DDX_Control(pDX, IDC_MONTHCALENDAR1, m_Calendar);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCalendarDlg, CDialog)
	//{{AFX_MSG_MAP(CCalendarDlg)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalendarDlg message handlers

void CCalendarDlg::OnSetDate()
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Пример из MSDN
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//CMonthCalCtrl* pCtrl = (CMonthCalCtrl*) GetDlgItem(IDC_MONTHCALENDAR1);

	//COleDateTime timeToday;
	//if (pCtrl->GetToday(timeToday))
	//{
	//  // Format the date information from the value we received
	//  // and post a message box about it.
	//  CString str = timeToday.Format(VAR_DATEVALUEONLY);
	//  AfxMessageBox(str);

	//  // Set the control's "today" indicator to be five
	//  // days previous.
	//  timeToday -= 5;
	//  pCtrl->SetToday(timeToday);
	//}
	//else
	//{
	//  // Something is wrong!
	//  ASSERT(FALSE);
	//}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//SYSTEMTIME sysTime;   // Win32 time information
	//GetSystemTime(&sysTime);
	//sysTime.wDay -= 1;
	//COleDateTime time5(sysTime); 

	//CString str = time5.Format(VAR_DATEVALUEONLY);
	//AfxMessageBox(str);

	//CMonthCalCtrl* pCtrl = (CMonthCalCtrl*) GetDlgItem(IDC_MONTHCALENDAR1);
	//pCtrl->SetToday(time5);

	return;
}

void CCalendarDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here

}
