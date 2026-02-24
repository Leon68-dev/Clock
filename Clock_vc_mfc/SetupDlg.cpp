#include "pch.h"
#include "Clock_vc_mfc.h"
#include "SetupDlg.h"

CSetupDlg::CSetupDlg(BOOL gmt, BOOL date, BOOL day, BOOL moving, BOOL top, 
    BOOL trans, BOOL border, int opacity, BOOL smooth,
    BOOL soundTickTack, BOOL sound1530, BOOL soundHours,
    BOOL digitalClock, BOOL calendar, BOOL sysMon, BOOL ping, BOOL weather,
    CString pingAddr, CString weatherCity, CString weatherUrl, BOOL sound24Hours,
    CWnd* pParent) : CDialogEx(IDD_SETUP_DLG, pParent)
    , m_bGMT(gmt), m_bDate(date), m_bDay(day), m_bMoving(moving)
    , m_bTopMost(top), m_bTransparent(trans), m_bBorder(border)
    , m_nOpacity(opacity), m_bSmooth(smooth)
    , m_bTickTack(soundTickTack), m_b1530(sound1530), m_bHours(soundHours)
    , m_bDigitalClock(digitalClock), m_bCalendar(calendar)
    , m_bSysMon(sysMon), m_bPing(ping), m_bWeather(weather) 
    , m_strPingAddress(pingAddr), m_strWeatherCity(weatherCity), m_strWeatherUrl(weatherUrl)
    , m_b24Hours(sound24Hours) { }

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
    DDX_Check(pDX, IDC_CHK_SOUND_HOURS, m_bHours);
    DDX_Check(pDX, IDC_CHK_SMOOTH, m_bSmooth);
    DDX_Check(pDX, IDC_CHK_SOUND_TICKTACK, m_bTickTack);
    DDX_Check(pDX, IDC_CHK_SOUND_1530, m_b1530);
    DDX_Check(pDX, IDC_CHK_DIGITAL, m_bDigitalClock);
    DDX_Check(pDX, IDC_CHK_CALENDAR, m_bCalendar);
    DDX_Check(pDX, IDC_CHK_SYSMON, m_bSysMon);
    DDX_Check(pDX, IDC_CHK_PING, m_bPing);
    DDX_Check(pDX, IDC_CHK_WEATHER, m_bWeather);
    DDX_Text(pDX, IDC_EDT_PING_ADR, m_strPingAddress);
    DDX_Text(pDX, IDC_EDT_WEATHER_CITY, m_strWeatherCity);
    DDX_Text(pDX, IDC_EDT_WEATHER_KEY, m_strWeatherUrl);
    DDX_Check(pDX, IDC_CHK_24HOURS, m_b24Hours);
}

BEGIN_MESSAGE_MAP(CSetupDlg, CDialogEx)
    ON_WM_HSCROLL()
    ON_BN_CLICKED(IDC_CHK_SOUND_HOURS, &CSetupDlg::OnBnClickedChkSoundHours)
    ON_BN_CLICKED(IDC_BTN_LINK, &CSetupDlg::OnBnClickedBtnLink)
END_MESSAGE_MAP()

BOOL CSetupDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    ModifyStyleEx(0, WS_EX_LAYERED);
    SetLayeredWindowAttributes(0, 216, LWA_ALPHA);

    // Налаштування слайдера (20-100%)
    m_sliderOpacity.SetRange(20, 100);
    if (m_nOpacity < 20) 
        m_nOpacity = 20;
    m_sliderOpacity.SetPos(m_nOpacity);
    m_sliderOpacity.SetTicFreq(10);

    // Ініціалізація підказки (ToolTip)
    m_toolTip.Create(this);
    m_toolTip.AddTool(&m_sliderOpacity, _T(""));
    m_toolTip.AddTool(GetDlgItem(IDC_EDT_WEATHER_KEY), _T("Paste the 'API URL' generated on the website here"));
    m_toolTip.AddTool(GetDlgItem(IDC_BTN_LINK), _T("Open Open-Meteo configurator to select your city and get the URL"));
    m_toolTip.SetDelayTime(TTDT_INITIAL, 200); // 0.2 сек до появи
    m_toolTip.SetDelayTime(TTDT_AUTOPOP, 10000); // висітиме 10 сек

    return TRUE;
}

BOOL CSetupDlg::PreTranslateMessage(MSG* pMsg)
{
    // Передаємо повідомлення об'єкту ToolTip
    if (m_toolTip.GetSafeHwnd()) {
        m_toolTip.RelayEvent(pMsg);
    }
    return CDialogEx::PreTranslateMessage(pMsg);
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

void CSetupDlg::OnBnClickedChkSoundHours()
{
    // TODO: Add your control notification handler code here
}

void CSetupDlg::OnBnClickedBtnLink()
{
    // Відкриваємо сайт OpenWeatherMap
    //ShellExecute(NULL, _T("open"), _T("https://openweathermap.org/api"), NULL, NULL, SW_SHOWNORMAL);
    ShellExecute(NULL, _T("open"), _T("https://open-meteo.com/en/docs"), NULL, NULL, SW_SHOWNORMAL);
}
