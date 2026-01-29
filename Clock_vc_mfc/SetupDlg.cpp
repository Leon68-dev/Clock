#include "pch.h"
#include "Clock_vc_mfc.h"
#include "SetupDlg.h"

CSetupDlg::CSetupDlg(BOOL gmt, BOOL date, BOOL day, BOOL moving, BOOL top, BOOL trans, BOOL border, BOOL sound, int opacity, CWnd* pParent)
    : CDialogEx(IDD_SETUP_DLG, pParent)
    , m_bGMT(gmt), m_bDate(date), m_bDay(day), m_bMoving(moving)
    , m_bTopMost(top), m_bTransparent(trans), m_bBorder(border)
    , m_bSound(sound), m_nOpacity(opacity)
{
}

void CSetupDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_SLIDER_OPACITY, m_sliderOpacity);

    // Зв'язуємо чекбокси зі змінними (DDX автоматично ставить/знімає галочки)
    DDX_Check(pDX, IDC_CHK_GMT, m_bGMT);
    DDX_Check(pDX, IDC_CHK_DATE, m_bDate);
    DDX_Check(pDX, IDC_CHK_DAY, m_bDay);
    DDX_Check(pDX, IDC_CHK_MOVING, m_bMoving);
    DDX_Check(pDX, IDC_CHK_TOPMOST, m_bTopMost);
    DDX_Check(pDX, IDC_CHK_TRANSPARENT, m_bTransparent);
    DDX_Check(pDX, IDC_CHK_BORDER, m_bBorder);
    DDX_Check(pDX, IDC_CHK_SOUND, m_bSound);
}

BEGIN_MESSAGE_MAP(CSetupDlg, CDialogEx)
    ON_WM_HSCROLL()
END_MESSAGE_MAP()

BOOL CSetupDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    ModifyStyleEx(0, WS_EX_LAYERED);
    SetLayeredWindowAttributes(0, 216, LWA_ALPHA);

    // Налаштування слайдера (0-100%)
    m_sliderOpacity.SetRange(0, 100);
    m_sliderOpacity.SetPos(m_nOpacity);

    // Ініціалізація підказки (ToolTip)
    m_toolTip.Create(this);
    m_toolTip.AddTool(&m_sliderOpacity, _T(""));

    return TRUE;
}

void CSetupDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    // Якщо рухали наш слайдер прозорості
    if (pScrollBar == (CScrollBar*)&m_sliderOpacity)
    {
        m_nOpacity = m_sliderOpacity.GetPos();

        // Оновлюємо текст підказки (аналог вашого toolTip1.SetToolTip)
        CString str;
        str.Format(_T("%d%%"), m_nOpacity);
        m_toolTip.UpdateTipText(str, &m_sliderOpacity);
    }
    CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CSetupDlg::OnOK()
{
    // DDX_Check спрацює автоматично при виклику базового OnOK
    m_nOpacity = m_sliderOpacity.GetPos();
    CDialogEx::OnOK();
}