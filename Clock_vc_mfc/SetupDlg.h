#pragma once
#include "afxdialogex.h"

class CSetupDlg : public CDialogEx
{
public:
    // Конструктор, що приймає всі поточні налаштування
    CSetupDlg(BOOL gmt, BOOL date, BOOL day, BOOL moving, BOOL top, BOOL trans, BOOL border, BOOL sound, int opacity, BOOL smooth, CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_SETUP_DLG };
#endif

    // Публічні змінні для результату
    BOOL m_bGMT, m_bDate, m_bDay, m_bMoving, m_bTopMost, m_bTransparent, m_bBorder, m_bSound, m_bSmooth;
    int m_nOpacity;

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
};
