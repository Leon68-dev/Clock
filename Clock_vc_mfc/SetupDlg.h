#pragma once
#include "afxdialogex.h"

class CSetupDlg : public CDialogEx
{
public:
    // Конструктор, що приймає всі поточні налаштування
    CSetupDlg(BOOL gmt, BOOL date, BOOL day, BOOL moving, BOOL top, 
        BOOL trans, BOOL border, int opacity, BOOL smooth, 
        BOOL soundTickTack, BOOL sound1530, BOOL soundHours,
        BOOL digitalClock, BOOL calendar, BOOL sysMon, BOOL ping, BOOL weather,
        CString pingAddr, CString weatherCity, CString weatherKey,
        CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_SETUP_DLG };
#endif

    // Публічні змінні для результату
    BOOL m_bGMT, m_bDate, m_bDay, m_bMoving, m_bTopMost, m_bTransparent, 
        m_bBorder, m_bSmooth, m_bHours, m_b1530, m_bTickTack,
        m_bDigitalClock, m_bCalendar, m_bSysMon, m_bPing, m_bWeather;
    
    int m_nOpacity;

    CString m_strPingAddress;
    CString m_strWeatherCity;
    CString m_strWeatherApiKey;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();

    // Контрол слайдера
    CSliderCtrl m_sliderOpacity;
    CToolTipCtrl m_toolTip; // Для відображення відсотка прозорості

    // Обробник руху слайдера (аналог ValueChanged)
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    virtual void OnOK();

    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedChkSoundHours();
};
