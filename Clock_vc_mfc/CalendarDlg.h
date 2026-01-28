#pragma once

#include "afxdialogex.h"

class CCalendarDlg : public CDialogEx
{
public:
    CCalendarDlg(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_CALENDAR_DLG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();

    // Змінна для керування календарем
    CMonthCalCtrl m_calendar;

    DECLARE_MESSAGE_MAP()
};