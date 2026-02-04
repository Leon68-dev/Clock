#include "pch.h"
#include "framework.h"
#include "Clock_vc_mfc.h"
#include "Clock_vc_mfcDlg.h"
#include "afxdialogex.h"

// Додаємо необхідні бібліотеки
#include <cmath>
#include <gdiplus.h>

// Підключаємо ваші створені діалоги
#include "AboutDlg.h"
#include "CalendarDlg.h"
#include "SetupDlg.h"
#include "ShutDownDlg.h"
#include "WorldMapDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_TRAY_ICON_MSG (WM_USER + 1)
const double PI = 3.14159265358979323846;

// CClockvcmfcDlg dialog

CClockvcmfcDlg::CClockvcmfcDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CLOCK_VC_MFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// Ініціалізація налаштувань (аналог C# initialization)
	m_bGMT = FALSE;
	m_bDate = TRUE;
	m_bDay = TRUE;
	m_bMoving = TRUE;
	m_bTopMost = FALSE;
	m_bTransparent = FALSE;
	m_bBorder = TRUE;
	m_nOpacity = 80;
	m_isShutDown = FALSE;
	m_isSleep = FALSE;
	m_bAlreadyExecuted = FALSE;
	m_bSmooth = false;
	m_bTickTack = FALSE;
	m_b1530 = FALSE;
	m_bHours = FALSE;
	m_timeShutDown = COleDateTime::GetCurrentTime();
}

void CClockvcmfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CClockvcmfcDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_CONTEXTMENU()
	ON_WM_ERASEBKGND()
	ON_MESSAGE(WM_TRAY_ICON_MSG, &CClockvcmfcDlg::OnTrayNotify)
	ON_COMMAND(ID_MENU_SETUP, &CClockvcmfcDlg::OnMenuSetup)
	ON_COMMAND(ID_MENU_ABOUT, &CClockvcmfcDlg::OnMenuAbout)
	ON_COMMAND(ID_MENU_CALENDAR, &CClockvcmfcDlg::OnMenuCalendar)
	ON_COMMAND(ID_MENU_SHUTDOWN, &CClockvcmfcDlg::OnMenuShutdown)
	ON_COMMAND(ID_MENU_EXIT, &CClockvcmfcDlg::OnMenuExit)
	ON_COMMAND(ID_MENU_STARTPOSITION, &CClockvcmfcDlg::OnMenuStartPosition)
	ON_COMMAND(ID_MENU_HIDE, &CClockvcmfcDlg::OnMenuHide)
	ON_COMMAND(ID_MENU_WORLDMAP, &CClockvcmfcDlg::OnMenuWorldmap)
END_MESSAGE_MAP()

BOOL CClockvcmfcDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

BOOL CClockvcmfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);

	int nSize = 134;

	CRect rcWorkArea;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWorkArea, 0);

	int x = rcWorkArea.right - static_cast<int>(nSize + nSize * 0.2);
	int y = rcWorkArea.bottom - static_cast<int>(nSize + nSize * 0.2);

	SetWindowPos(NULL, x, y, nSize, nSize, SWP_NOZORDER | SWP_SHOWWINDOW);

	ModifyStyleEx(0, WS_EX_LAYERED);
	LoadSettings();

	// Замість прямого виклику SetLayeredWindowAttributes використовуємо наш метод
	UpdateTransparency();

	if (m_bTopMost)
	{
		SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}

	InitTrayIcon();
	SetTimer(1, m_bSmooth ? 200 : 1000, NULL);

	return TRUE;
}

void CClockvcmfcDlg::InitTrayIcon()
{
	memset(&m_nid, 0, sizeof(NOTIFYICONDATA));
	m_nid.cbSize = sizeof(NOTIFYICONDATA);
	m_nid.hWnd = m_hWnd;
	m_nid.uID = 1;
	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_nid.uCallbackMessage = WM_TRAY_ICON_MSG;
	m_nid.hIcon = m_hIcon;
	_tcscpy_s(m_nid.szTip, _T("MFC Clock"));
	Shell_NotifyIcon(NIM_ADD, &m_nid);
}

void CClockvcmfcDlg::OnPaint()
{
	CPaintDC dc(this);
}

void CClockvcmfcDlg::DrawClock(Gdiplus::Graphics& g)
{
	CRect clientRect;
	GetClientRect(&clientRect);

	float w = (float)clientRect.Width();
	float h = (float)clientRect.Height();

	// Налаштування якості
	g.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
	g.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighQuality);
	g.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);

	float xCenter = w / 2.0f;
	float yCenter = h / 2.0f;
	float radius = (w < h ? w : h) / 2.0f;
	float borderThickness = 6.0f;

	// 1. ФОН ЦИФЕРБЛАТА
	if (!m_bTransparent)
	{
		Gdiplus::SolidBrush faceBrush(Gdiplus::Color(255, 242, 238, 225));
		g.FillEllipse(&faceBrush, 0.5f, 0.5f, w - 1.0f, h - 1.0f);
	}

	// 2. БОРДЕР (Кільце)
	if (m_bBorder)
	{
		Gdiplus::RectF penRect(0.0f, 0.0f, w, h);
		float inset = borderThickness / 2.0f;
		penRect.Inflate(-inset, -inset);

		Gdiplus::Pen penBlack(Gdiplus::Color::Black, borderThickness);
		Gdiplus::Pen penGray(Gdiplus::Color::Gray, 2.0f);

		g.DrawEllipse(&penBlack, penRect);
		g.DrawEllipse(&penGray, penRect);
	}

	float innerRadius = radius - borderThickness - 1.5f;

	// 3. ПОДІЛКИ (Ticks)
	Gdiplus::Pen penHour(Gdiplus::Color::Black, 2.0f);
	Gdiplus::Pen penQuarter(Gdiplus::Color::Black, 4.0f);
	Gdiplus::SolidBrush brushBlack(Gdiplus::Color::Black);
	Gdiplus::SolidBrush brushFace(Gdiplus::Color(255, 242, 238, 225));

	for (int i = 0; i < 60; i++)
	{
		float angle = i * PI / 30.0f - PI / 2.0f;
		float cosA = cosf(angle);
		float sinA = sinf(angle);

		if (i % 5 == 0)
		{
			float len = (i % 15 == 0) ? innerRadius * 0.22f : innerRadius * 0.15f;
			Gdiplus::Pen* p = (i % 15 == 0) ? &penQuarter : &penHour;

			g.DrawLine(p,
				xCenter + cosA * (innerRadius - len),
				yCenter + sinA * (innerRadius - len),
				xCenter + cosA * (innerRadius + 3.0f),
				yCenter + sinA * (innerRadius + 3.0f)
			);

			float markDotR = 1.5f;
			g.FillEllipse(&brushFace,
				xCenter + cosA * (innerRadius - len) - markDotR,
				yCenter + sinA * (innerRadius - len) - markDotR,
				markDotR * 2.0f, markDotR * 2.0f);
		}
		else
		{
			float dotR = 1.3f;
			g.FillEllipse(&brushBlack,
				xCenter + cosA * (innerRadius + 1.5f) - dotR,
				yCenter + sinA * (innerRadius + 1.5f) - dotR,
				dotR * 2.0f, dotR * 2.0f);
		}
	}

	// --- ОТРИМАННЯ ЧАСУ З МІЛІСЕКУНДАМИ ---
	SYSTEMTIME st;
	if (m_bGMT) ::GetSystemTime(&st);
	else ::GetLocalTime(&st);
	COleDateTime now(st);

	// 4. ТЕКСТ
	Gdiplus::FontFamily fontFamily(L"Arial");
	Gdiplus::StringFormat sf;
	sf.SetAlignment(Gdiplus::StringAlignmentCenter);
	sf.SetLineAlignment(Gdiplus::StringAlignmentCenter);

	Gdiplus::Font fontLN(&fontFamily, innerRadius * 0.2f, Gdiplus::FontStyleItalic | Gdiplus::FontStyleUnderline);
	Gdiplus::SolidBrush bLN(Gdiplus::Color::Gray);
	g.DrawString(L"LN", -1, &fontLN, Gdiplus::PointF(xCenter, yCenter - innerRadius * 0.52f), &sf, &bLN);

	Gdiplus::Font fontText(&fontFamily, innerRadius * 0.11f, Gdiplus::FontStyleBold);

	Gdiplus::SolidBrush bCpp(Gdiplus::Color::Gray);
	g.DrawString(L"C++", -1, &fontText, Gdiplus::PointF(xCenter, yCenter + 16.0f - innerRadius * 0.52f), &sf, &bCpp);
	
	float yDelta = 5.0f;

	if (m_bDay)
	{
		// Формат %a дає скорочену назву (Mon, Tue...), MakeUpper робить її великими літерами
		CString strDay = now.Format(_T("%a"));
		strDay.MakeUpper();

		bool isWeekend = (now.GetDayOfWeek() == 1 || now.GetDayOfWeek() == 7);
		Gdiplus::SolidBrush bDay(isWeekend ? Gdiplus::Color::RosyBrown : Gdiplus::Color::Gray); // Сірий для буднів
		g.DrawString(strDay, -1, &fontText, Gdiplus::PointF(xCenter, yCenter + yDelta + innerRadius * 0.12f), &sf, &bDay);
	}

	if (m_bDate)
	{
		CString strDate = now.Format(_T("%d-%m-%y"));
		Gdiplus::SolidBrush bDate(Gdiplus::Color::Gray);
		g.DrawString(strDate, -1, &fontText, Gdiplus::PointF(xCenter, yCenter + yDelta + innerRadius * 0.35f), &sf, &bDate);
	}

	if (m_bGMT)
	{
		Gdiplus::SolidBrush bUTC(Gdiplus::Color::Gray);
		g.DrawString(L"GMT", -1, &fontText, Gdiplus::PointF(xCenter, yCenter + yDelta + innerRadius * 0.58f), &sf, &bUTC);
	}

	// 5. СТРІЛКИ (ПЛАВНИЙ РУХ)
	float fSeconds = m_bSmooth ? (st.wSecond + st.wMilliseconds / 1000.0f) : (float)st.wSecond;
	float fMinutes = st.wMinute + fSeconds / 60.0f;
	float fHours = (st.wHour % 12 + fMinutes / 60.0f) * 5.0f;

	auto DrawHandMFC = [&](float val, float len, float width, bool hasWhiteLine)
		{
			float a = val * PI / 30.0f - PI / 2.0f;
			float x = xCenter + cosf(a) * len;
			float y = yCenter + sinf(a) * len;

			Gdiplus::Pen pBlack(Gdiplus::Color::Black, width);
			pBlack.SetStartCap(Gdiplus::LineCapRound);
			pBlack.SetEndCap(Gdiplus::LineCapRound);
			g.DrawLine(&pBlack, xCenter, yCenter, x, y);

			if (hasWhiteLine)
			{
				Gdiplus::Pen pWhite(Gdiplus::Color::White, width / 2.2f);
				pWhite.SetStartCap(Gdiplus::LineCapRound);
				pWhite.SetEndCap(Gdiplus::LineCapRound);
				g.DrawLine(&pWhite, xCenter, yCenter, x, y);
			}
		};

	DrawHandMFC(fHours, innerRadius * 0.58f, 6.5f, true);
	DrawHandMFC(fMinutes, innerRadius * 0.85f, 4.5f, true);

	// Секундна стрілка
	Gdiplus::Pen pSec(Gdiplus::Color::Red, 1.5f);
	float sAngle = fSeconds * PI / 30.0f - PI / 2.0f;
	g.DrawLine(&pSec,
		xCenter - cosf(sAngle) * (innerRadius * 0.15f),
		yCenter - sinf(sAngle) * (innerRadius * 0.15f),
		xCenter + cosf(sAngle) * (innerRadius * 0.95f),
		yCenter + sinf(sAngle) * (innerRadius * 0.95f)
	);

	g.FillEllipse(&brushBlack, xCenter - 4.0f, yCenter - 4.0f, 8.0f, 8.0f);
}

int CClockvcmfcDlg::ClcX(int sec, int size, int xCenter)
{
	return (int)(cos(sec * PI / 30 - PI / 2) * size + xCenter);
}

int CClockvcmfcDlg::ClcY(int sec, int size, int yCenter)
{
	return (int)(sin(sec * PI / 30 - PI / 2) * size + yCenter);
}

void CClockvcmfcDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		SYSTEMTIME st;
		if (m_bGMT) ::GetSystemTime(&st); else ::GetLocalTime(&st);

		UpdateLayeredClock();

		if (st.wSecond != m_lastSecond)
		{
			m_lastSecond = st.wSecond;

			// 1. Щогодинний бій
			if (m_bHours && st.wMinute == 0 && st.wSecond == 0)
			{
				PlayHourlyChime(st.wHour);
			}

			// 2. Чверті
			if (m_b1530 && st.wSecond == 0)
			{
				if (st.wMinute == 15 || st.wMinute == 45)
					PlayMCI(GetSoundPath(_T("_15.wav")), _T("chime"));
				else if (st.wMinute == 30)
					PlayMCI(GetSoundPath(_T("_30.wav")), _T("chime"));
			}

			// 3. Тік-Так (грає паралельно з іншими!)
			if (m_bTickTack && st.wSecond % 2 == 0)
			{
				// Перевіряємо, чи не грає зараз довгий звук (опціонально)
				if (!IsPlayingMCI(_T("hours")) && !IsPlayingMCI(_T("chime")))
				{
					PlayMCI(GetSoundPath(_T("_TickTack.wav")), _T("tick"));
				}
			}
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CClockvcmfcDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_bMoving)
		PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);
	
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CClockvcmfcDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu menu;
	if (menu.LoadMenu(IDR_MENU_CONTEXT))
	{
		CMenu* pPopup = menu.GetSubMenu(0);
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
}

LRESULT CClockvcmfcDlg::OnTrayNotify(WPARAM wParam, LPARAM lParam)
{
	if (lParam == WM_RBUTTONUP)
	{
		CPoint pos;
		GetCursorPos(&pos);

		CMenu menu;
		if (menu.LoadMenu(IDR_MENU_CONTEXT))
		{
			CMenu* pPopup = menu.GetSubMenu(1);
			if (pPopup)
			{
				SetForegroundWindow();

				if (IsWindowVisible())
					pPopup->ModifyMenu(ID_MENU_HIDE, MF_BYCOMMAND | MF_STRING, ID_MENU_HIDE, _T("Hide"));
				else
					pPopup->ModifyMenu(ID_MENU_HIDE, MF_BYCOMMAND | MF_STRING, ID_MENU_HIDE, _T("Open"));

				pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pos.x, pos.y, this);
			}
		}
	}
	else if (lParam == WM_LBUTTONDBLCLK)
	{
		SendMessage(WM_COMMAND, ID_MENU_HIDE);
	}

	return 0;
}

void CClockvcmfcDlg::OnMenuAbout()
{
	CAboutDlg dlg; dlg.DoModal();
}

void CClockvcmfcDlg::OnMenuCalendar()
{
	CCalendarDlg dlg; dlg.DoModal();
}

void CClockvcmfcDlg::OnMenuExit()
{
	SaveSettings();
	Shell_NotifyIcon(NIM_DELETE, &m_nid);
	PostQuitMessage(0);
}

void CClockvcmfcDlg::OnMenuShutdown()
{
	CShutDownDlg dlg(m_timeShutDown, m_isShutDown, m_isSleep);

	if (dlg.DoModal() == IDOK)
	{
		m_timeShutDown = dlg.m_tm;
		m_isShutDown = dlg.m_isShutDown;
		m_isSleep = dlg.m_isSleep;
	}
}

void CClockvcmfcDlg::OnMenuSetup()
{
	CSetupDlg dlg(m_bGMT, m_bDate, m_bDay, m_bMoving, m_bTopMost, m_bTransparent,
		m_bBorder, m_nOpacity, m_bSmooth, m_bTickTack, m_b1530, m_bHours);

	if (dlg.DoModal() == IDOK)
	{
		m_bGMT = dlg.m_bGMT;
		m_bDate = dlg.m_bDate;
		m_bDay = dlg.m_bDay;
		m_bMoving = dlg.m_bMoving;
		m_bTopMost = dlg.m_bTopMost;
		m_bTransparent = dlg.m_bTransparent;
		m_bBorder = dlg.m_bBorder;
		m_nOpacity = dlg.m_nOpacity;
		m_bSmooth = dlg.m_bSmooth;
		m_bTickTack = dlg.m_bTickTack;
		m_b1530 = dlg.m_b1530;
		m_bHours = dlg.m_bHours;

		// Оновлюємо інтервал таймера
		KillTimer(1);
		SetTimer(1, m_bSmooth ? 200 : 1000, NULL);

		SetWindowPos(m_bTopMost ? &wndTopMost : &wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		UpdateTransparency();
		UpdateLayeredClock();
		SaveSettings();
	}
}

void CClockvcmfcDlg::OnMenuStartPosition()
{
	int nSize = 140;
	CRect rcWorkArea;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWorkArea, 0);
	int x = rcWorkArea.right - static_cast<int>(nSize + nSize * 0.2);
	int y = rcWorkArea.bottom - static_cast<int>(nSize + nSize * 0.2);

	SetWindowPos(NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_SHOWWINDOW);
}

void CClockvcmfcDlg::OnMenuHide()
{
	if (IsWindowVisible())
	{
		ShowWindow(SW_HIDE);
	}
	else
	{
		ShowWindow(SW_SHOW);
		SetForegroundWindow();
	}
}

HCURSOR CClockvcmfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString CClockvcmfcDlg::GetIniPath()
{
	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);
	CString strPath(szPath);
	int nIndex = strPath.ReverseFind(_T('\\'));
	if (nIndex != -1)
	{
		strPath = strPath.Left(nIndex + 1);
	}

	return strPath + _T("clock_vc_mfc.ini");
}


void CClockvcmfcDlg::SaveSettings()
{
	CString strPath = GetIniPath();
	CString strVal;
	auto WriteBool = [&](LPCTSTR key, BOOL val) 
	{
		WritePrivateProfileString(_T("Settings"), key, val ? _T("1") : _T("0"), strPath);
	};

	WriteBool(_T("chkGMT"), m_bGMT);
	WriteBool(_T("chkDate"), m_bDate);
	WriteBool(_T("chkDay"), m_bDay);
	WriteBool(_T("chkMoving"), m_bMoving);
	WriteBool(_T("chkAlwaysOnTop"), m_bTopMost);
	WriteBool(_T("chkTransparent"), m_bTransparent);
	WriteBool(_T("chkBorder"), m_bBorder);
	WriteBool(_T("chkSmooth"), m_bSmooth);
	WriteBool(_T("chkTickTack"), m_bTickTack);
	WriteBool(_T("chk1530"), m_b1530);
	WriteBool(_T("chkHours"), m_bHours);

	strVal.Format(_T("%d"), m_nOpacity);
	WritePrivateProfileString(_T("Settings"), _T("frmOpacity"), strVal, strPath);

	CRect rect; GetWindowRect(&rect);
	strVal.Format(_T("%d"), rect.left); WritePrivateProfileString(_T("Settings"), _T("deskX"), strVal, strPath);
	strVal.Format(_T("%d"), rect.top); WritePrivateProfileString(_T("Settings"), _T("deskY"), strVal, strPath);

	WriteBool(_T("chkOff"), m_isShutDown);
	WriteBool(_T("chkSleep"), m_isSleep);
	WritePrivateProfileString(_T("Settings"), _T("timeOff"), m_timeShutDown.Format(_T("%H:%M")), strPath);
}

void CClockvcmfcDlg::LoadSettings()
{
	CString strPath = GetIniPath();
	auto GetBool = [&](LPCTSTR key, int def) {
		return GetPrivateProfileInt(_T("Settings"), key, def, strPath);
		};

	m_bGMT = GetBool(_T("chkGMT"), 0);
	m_bDate = GetBool(_T("chkDate"), 1);
	m_bDay = GetBool(_T("chkDay"), 1);
	m_bMoving = GetBool(_T("chkMoving"), 1);
	m_bTopMost = GetBool(_T("chkAlwaysOnTop"), 0);
	m_bTransparent = GetBool(_T("chkTransparent"), 0);
	m_bBorder = GetBool(_T("chkBorder"), 1);
	m_bSmooth = GetBool(_T("chkSmooth"), 1);
	m_bTickTack = GetBool(_T("chkTickTack"), 0);
	m_b1530 = GetBool(_T("chk1530"), 0);
	m_bHours = GetBool(_T("chkHours"), 0);
	m_nOpacity = GetPrivateProfileInt(_T("Settings"), _T("frmOpacity"), 80, strPath);

	int x = GetPrivateProfileInt(_T("Settings"), _T("deskX"), -1, strPath);
	int y = GetPrivateProfileInt(_T("Settings"), _T("deskY"), -1, strPath);
	if (x != -1 && y != -1) SetWindowPos(NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	m_isShutDown = GetBool(_T("chkOff"), 0);
	m_isSleep = GetBool(_T("chkSleep"), 0);
	TCHAR szTime[10];
	GetPrivateProfileString(_T("Settings"), _T("timeOff"), _T("00:00"), szTime, 10, strPath);
	m_timeShutDown.ParseDateTime(szTime);
}

BOOL CClockvcmfcDlg::SetShutdownPrivilege()
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;

	// Отримуємо токен поточного процесу
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		return FALSE;

	// Шукаємо LUID для привілею вимкнення
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);

	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	// Застосовуємо привілей
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);

	if (GetLastError() != ERROR_SUCCESS)
		return FALSE;

	return TRUE;
}

// Сама логіка вимкнення/сну
void CClockvcmfcDlg::ExecuteShutdown()
{
	if (m_isSleep)
	{
		// Режим сну (Sleep)
		// Параметри: Hibernate = FALSE, ForceCritical = TRUE, DisableWakeEvent = FALSE
		SetSuspendState(FALSE, TRUE, FALSE);
	}
	else
	{
		// Режим вимкнення (Power Off)
		if (SetShutdownPrivilege())
		{
			// EWX_POWEROFF - вимкнути живлення
			// EWX_FORCE - примусово закрити програми (як у вашому C# коді)
			ExitWindowsEx(EWX_POWEROFF | EWX_FORCE, SHTDN_REASON_MAJOR_OTHER);
		}
	}
}

// Отримання повного шляху до звукового файлу
CString CClockvcmfcDlg::GetSoundPath(CString fileName)
{
	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);
	CString strPath(szPath);
	int nIndex = strPath.ReverseFind(_T('\\'));
	if (nIndex != -1)
		strPath = strPath.Left(nIndex + 1);

	return strPath + fileName;
}

// Відтворення одного файлу (асинхронно, щоб не фризити UI)
void CClockvcmfcDlg::PlaySoundFile(CString fileName)
{
	CString fullPath = GetSoundPath(fileName);
	// SND_ASYNC - не чекати завершення, SND_FILENAME - шлях до файлу
	::PlaySound(fullPath, NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
}

void CClockvcmfcDlg::PlayHourlyChime(int hours)
{
	int count = hours % 12;
	if (count == 0) count = 12;

	CString fullPath = GetSoundPath(_T("_Boom.wav"));

	std::thread([this, fullPath, count]()
		{
			for (int i = 0; i < count; i++)
			{
				PlayMCI(fullPath, _T("hours"));

				// Чекаємо, поки удар дограє
				while (IsPlayingMCI(_T("hours"))) {
					Sleep(50);
				}
				Sleep(200); // Пауза між ударами
			}
		}).detach();
}

void CClockvcmfcDlg::UpdateTransparency()
{
	UpdateLayeredClock();
}

void CClockvcmfcDlg::UpdateLayeredClock()
{
	CRect rect;
	GetWindowRect(&rect);
	CSize size(rect.Width(), rect.Height());
	CPoint ptSrc(0, 0);
	CPoint ptDest(rect.left, rect.top);

	HDC hdcScreen = ::GetDC(NULL);
	HDC hMemDC = ::CreateCompatibleDC(hdcScreen);

	BITMAPINFO bmi;
	memset(&bmi, 0, sizeof(bmi));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = size.cx;
	bmi.bmiHeader.biHeight = size.cy;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;

	void* pvBits;
	HBITMAP hBitmap = ::CreateDIBSection(hMemDC, &bmi, DIB_RGB_COLORS, &pvBits, NULL, 0);
	HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hMemDC, hBitmap);

	Gdiplus::Graphics g(hMemDC);

	// Налаштування для максимальної гладкості як у C#
	g.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
	g.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighQuality);
	g.SetCompositingQuality(Gdiplus::CompositingQualityHighQuality);

	// 1. Очищаємо все ПОВНІСТЮ прозорим кольором (Alpha = 0)
	g.Clear(Gdiplus::Color(0, 0, 0, 0));

	// 2. Якщо прозорість ВИМКНЕНА — малюємо КРУГЛИЙ фон
	if (!m_bTransparent)
	{
		// Малюємо еліпс на 1 піксель менше розміру, щоб згладжування було ідеальним
		Gdiplus::RectF faceRect(0.5f, 0.5f, (float)size.cx - 1.0f, (float)size.cy - 1.0f);
		Gdiplus::SolidBrush faceBrush(Gdiplus::Color(255, 242, 238, 225));
		g.FillEllipse(&faceBrush, faceRect);
	}

	// 3. Малюємо стрілки, риски та текст
	DrawClock(g);

	BLENDFUNCTION blend = { 0 };
	blend.BlendOp = AC_SRC_OVER;
	blend.SourceConstantAlpha = (BYTE)((255 * m_nOpacity) / 100);
	blend.AlphaFormat = AC_SRC_ALPHA;

	::UpdateLayeredWindow(m_hWnd, hdcScreen, &ptDest, &size, hMemDC, &ptSrc, 0, &blend, ULW_ALPHA);

	::SelectObject(hMemDC, hOldBitmap);
	::DeleteObject(hBitmap);
	::DeleteDC(hMemDC);
	::ReleaseDC(NULL, hdcScreen);
}

void CClockvcmfcDlg::OnMenuWorldmap()
{
	if (m_pMapDlg != nullptr && ::IsWindow(m_pMapDlg->GetSafeHwnd()))
	{
		m_pMapDlg->ShowWindow(SW_SHOW);
		m_pMapDlg->SetForegroundWindow();
	}
	else
	{
		// Якщо об'єкт існує, але вікно закрите - ВИДАЛЯЄМО ОБ'ЄКТ
		if (m_pMapDlg != nullptr)
		{
			delete m_pMapDlg; // Це викличе деструктор і видалить Image
			m_pMapDlg = nullptr;
		}

		m_pMapDlg = new CWorldMapDlg(this);
		if (m_pMapDlg->Create(IDD_WORLD_MAP, this))
		{
			m_pMapDlg->ShowWindow(SW_SHOW);
		}
	}
}

void CClockvcmfcDlg::PlayMCI(CString fileName, CString alias)
{
	// Закриваємо попередній сеанс для цього аліасу
	mciSendString(_T("close ") + alias, NULL, 0, NULL);

	// Відкриваємо файл (беремо шлях у лапки для безпеки)
	CString cmd;
	cmd.Format(_T("open \"%s\" alias %s"), (LPCTSTR)fileName, (LPCTSTR)alias);
	mciSendString(cmd, NULL, 0, NULL);

	// Граємо
	mciSendString(_T("play ") + alias, NULL, 0, NULL);
}

void CClockvcmfcDlg::StopMCI(CString alias)
{
	mciSendString(_T("stop ") + alias, NULL, 0, NULL);
	mciSendString(_T("close ") + alias, NULL, 0, NULL);
}

BOOL CClockvcmfcDlg::IsPlayingMCI(CString alias)
{
	TCHAR res[128];
	CString cmd = _T("status ") + alias + _T(" mode");
	mciSendString(cmd, res, 128, NULL);
	return (_tcsicmp(res, _T("playing")) == 0);
}