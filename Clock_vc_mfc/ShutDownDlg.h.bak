#pragma once
#include "afxdialogex.h"

class CShutDownDlg : public CDialogEx
{
public:
    // Конструктор з параметрами для ініціалізації (як у C#)
    CShutDownDlg(COleDateTime tm, BOOL sd, BOOL sl, CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_SHUTDOWN_DLG };
#endif

    // Публічні змінні для отримання результату
    COleDateTime m_tm;
    BOOL m_isShutDown;
    BOOL m_isSleep;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();

    // Контроли
    CDateTimeCtrl m_timePicker;
    CButton m_chkWork;
    CButton m_chkSleep;

    // Обробники подій
    afx_msg void OnBnClickedChkShutdownWork();
    afx_msg void OnBnClickedChkSleep();
    virtual void OnOK();

    void UpdateUIState(); // Аналог вашого set_tmShutDown

    DECLARE_MESSAGE_MAP()
};
