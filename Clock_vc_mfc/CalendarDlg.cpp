#include "pch.h" 
#include "Clock_vc_mfc.h"
#include "CalendarDlg.h"

CCalendarDlg::CCalendarDlg(CWnd* pParent )
    : CDialogEx(IDD_CALENDAR_DLG, pParent)
{
}

void CCalendarDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    
    DDX_Control(pDX, IDC_MONTHCALENDAR1, m_calendar);
}

BEGIN_MESSAGE_MAP(CCalendarDlg, CDialogEx)
END_MESSAGE_MAP()

BOOL CCalendarDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    ModifyStyleEx(0, WS_EX_LAYERED);
    SetLayeredWindowAttributes(0, 216, LWA_ALPHA);

    
    SYSTEMTIME st;
    GetLocalTime(&st); 

    
    m_calendar.SetCurSel(&st);

    
    m_calendar.SetToday(&st);

    return TRUE;
}