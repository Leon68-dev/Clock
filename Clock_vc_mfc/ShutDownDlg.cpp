#include "pch.h"
#include "Clock_vc_mfc.h"
#include "ShutDownDlg.h"

CShutDownDlg::CShutDownDlg(COleDateTime tm, BOOL sd, BOOL sl, CWnd* pParent)
    : CDialogEx(IDD_SHUTDOWN_DLG, pParent)
    , m_tm(tm)
    , m_isShutDown(sd)
    , m_isSleep(sl)
{
}

void CShutDownDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TIME_SHUTDOWN, m_timePicker);
    DDX_Control(pDX, IDC_CHK_SHUTDOWN_WORK, m_chkWork);
    DDX_Control(pDX, IDC_CHK_SLEEP, m_chkSleep);
}

BEGIN_MESSAGE_MAP(CShutDownDlg, CDialogEx)
    ON_BN_CLICKED(IDC_CHK_SHUTDOWN_WORK, &CShutDownDlg::OnBnClickedChkShutdownWork)
    ON_BN_CLICKED(IDC_CHK_SLEEP, &CShutDownDlg::OnBnClickedChkSleep)
END_MESSAGE_MAP()

BOOL CShutDownDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    ModifyStyleEx(0, WS_EX_LAYERED);
    SetLayeredWindowAttributes(0, 216, LWA_ALPHA);

    // ≤н≥ц≥ал≥зац≥€ значень
    m_timePicker.SetTime(m_tm);
    m_chkWork.SetCheck(m_isShutDown);
    m_chkSleep.SetCheck(m_isSleep);

    UpdateUIState();

    return TRUE;
}

void CShutDownDlg::UpdateUIState()
{
    BOOL isChecked = m_chkWork.GetCheck();

    // «м≥на тексту та доступност≥ (аналог set_tmShutDown)
    m_chkWork.SetWindowText(isChecked ? _T("Shut down \"On\"") : _T("Shut down \"Off\""));

    m_timePicker.EnableWindow(isChecked);
    m_chkSleep.EnableWindow(isChecked);

    if (!isChecked) {
        m_chkSleep.SetCheck(FALSE);
    }
}

void CShutDownDlg::OnBnClickedChkShutdownWork()
{
    UpdateUIState();
}

void CShutDownDlg::OnBnClickedChkSleep()
{
    m_isSleep = m_chkSleep.GetCheck();
}

void CShutDownDlg::OnOK()
{
    // «бер≥гаЇмо ф≥нальн≥ значенн€ перед закритт€м
    m_timePicker.GetTime(m_tm);
    m_isShutDown = m_chkWork.GetCheck();
    m_isSleep = m_chkSleep.GetCheck();

    CDialogEx::OnOK();
}