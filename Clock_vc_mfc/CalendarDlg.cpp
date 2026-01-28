#include "pch.h" // Або "stdafx.h"
#include "Clock_vc_mfc.h"
#include "CalendarDlg.h"

CCalendarDlg::CCalendarDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_CALENDAR_DLG, pParent)
{
}

void CCalendarDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    // Зв'язуємо змінну з контролом на формі
    DDX_Control(pDX, IDC_MONTHCALENDAR1, m_calendar);
}

BEGIN_MESSAGE_MAP(CCalendarDlg, CDialogEx)
END_MESSAGE_MAP()

BOOL CCalendarDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // Аналог вашого setCalendar()
    SYSTEMTIME st;
    GetLocalTime(&st); // Отримуємо поточний системний час

    // Встановлюємо поточну дату як вибрану
    m_calendar.SetCurSel(&st);

    // Встановлюємо "Today" (нижній напис у календарі)
    m_calendar.SetToday(&st);

    return TRUE;
}