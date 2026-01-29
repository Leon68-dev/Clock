#include "pch.h"
#include "framework.h"
#include "Clock_vc_mfc.h"
#include "Clock_vc_mfcDlg.h"
#include "afxdialogex.h"

// Додаємо необхідні бібліотеки
#include <cmath>
#include <gdiplus.h>

// Підключаємо ваші створені діалоги (перевірте назви файлів!)
#include "AboutDlg.h"
#include "CalendarDlg.h"
#include "SetupDlg.h"
#include "ShutDownDlg.h"

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
	m_bSound = FALSE;
	m_nOpacity = 80;
	m_isShutDown = FALSE;
	m_isSleep = FALSE;
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
	// Обробники команд меню (перевірте ID у вашому Menu Editor)
	ON_COMMAND(ID_MENU_SETUP, &CClockvcmfcDlg::OnMenuSetup)
	ON_COMMAND(ID_MENU_ABOUT, &CClockvcmfcDlg::OnMenuAbout)
	ON_COMMAND(ID_MENU_CALENDAR, &CClockvcmfcDlg::OnMenuCalendar)
	ON_COMMAND(ID_MENU_SHUTDOWN, &CClockvcmfcDlg::OnMenuShutdown)
	ON_COMMAND(ID_MENU_EXIT, &CClockvcmfcDlg::OnMenuExit)
	ON_COMMAND(ID_MENU_STARTPOSITION, &CClockvcmfcDlg::OnMenuStartPosition)
	ON_COMMAND(ID_MENU_HIDE, &CClockvcmfcDlg::OnMenuHide)
END_MESSAGE_MAP()

BOOL CClockvcmfcDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE; // Просто повертаємо TRUE, нічого не зафарбовуючи
}

BOOL CClockvcmfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 1. Встановлюємо точний розмір вікна (140x140 пікселів)
	int nSize = 136;

	// 2. Розраховуємо позицію (нижній правий кут, як у C# startPosition)
	CRect rcWorkArea;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWorkArea, 0); // Отримуємо робочу область (без Taskbar)

	int x = rcWorkArea.right - static_cast<int>(nSize + nSize * 0.2);
	int y = rcWorkArea.bottom - static_cast<int>(nSize + nSize * 0.2);

	// Встановлюємо розмір та позицію вікна
	// SWP_NOZORDER - не змінюємо порядок вікон, SWP_SHOWWINDOW - показуємо
	SetWindowPos(NULL, x, y, nSize, nSize, SWP_NOZORDER | SWP_SHOWWINDOW);

	// 3. Налаштування прозорості (Layered Window)
	ModifyStyleEx(0, WS_EX_LAYERED);
	SetLayeredWindowAttributes(0, (255 * m_nOpacity) / 100, LWA_ALPHA);

	// 4. Створення круглої форми вікна (тепер точно під розмір 140x140)
	CRgn rgn;
	// Робимо регіон на 1 піксель більшим за вікно, щоб згладжування (Anti-aliasing) бордера не обрізалося
	rgn.CreateEllipticRgn(-1, -1, nSize + 1, nSize + 1);
	SetWindowRgn(rgn, TRUE);

	// 5. Завжди зверху (якщо m_bTopMost увімкнено)
	if (m_bTopMost) {
		SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}

	InitTrayIcon();
	SetTimer(1, 1000, NULL);

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
	CRect rect;
	GetClientRect(&rect);

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	CBitmap memBitmap;
	memBitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	memDC.SelectObject(&memBitmap);

	Gdiplus::Graphics graphics(memDC.GetSafeHdc());
	graphics.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);

	// ВАЖЛИВО: Колір фону тепер такий самий, як у циферблата (Parchment)
	Gdiplus::SolidBrush backBrush(Gdiplus::Color(255, 242, 238, 225));
	graphics.FillRectangle(&backBrush, 0, 0, rect.Width(), rect.Height());

	DrawClock(graphics);

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
}

void CClockvcmfcDlg::DrawClock(Gdiplus::Graphics& g)
{
	CRect clientRect;
	GetClientRect(&clientRect);

	// Створюємо RectF на повний розмір вікна (134x134)
	Gdiplus::RectF fullRect(0.0f, 0.0f, (float)clientRect.Width(), (float)clientRect.Height());

	// Налаштування згладжування
	g.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
	g.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighQuality);

	// --- 1. ЗАПОВНЕННЯ ВСЬОГО ПРОСТОРУ ---
	// Замість FillEllipse малюємо прямокутник на все вікно кольором циферблата.
	// Оскільки вікно обрізане регіоном (SetWindowRgn), кути самі стануть круглими.
	// Це на 100% прибере білі пікселі по краях.
	Gdiplus::SolidBrush faceBrush(Gdiplus::Color(255, 242, 238, 225));
	g.FillRectangle(&faceBrush, fullRect);

	float borderThickness = 6.0f;
	float xCenter = fullRect.Width / 2.0f;
	float yCenter = fullRect.Height / 2.0f;

	// --- 2. БОРДЕР (Кільце) ---
	if (m_bBorder) 
	{
		// Розрахунок: щоб край 7-піксельного пера торкався краю вікна,
		// ми малюємо еліпс, який трохи "втиснутий" всередину.
		Gdiplus::RectF penRect = fullRect;
		float inset = (borderThickness / 2.0f) - 0.5f; // -0.5 для компенсації згладжування
		penRect.Inflate(-inset, -inset);

		Gdiplus::Pen penBlack(Gdiplus::Color::Black, borderThickness);
		g.DrawEllipse(&penBlack, penRect);

		// Сіра лінія (відблиск)
		Gdiplus::Pen penGray(Gdiplus::Color::Gray, 2.0f);
		g.DrawEllipse(&penGray, penRect);
	}

	float innerRadius = (fullRect.Width / 2.0f) - borderThickness;

	// --- 3. ПОДІЛКИ ---
	Gdiplus::Pen penHour(Gdiplus::Color::Black, 2.0f);
	Gdiplus::Pen penQuarter(Gdiplus::Color::Black, 4.0f);
	Gdiplus::SolidBrush brushBlack(Gdiplus::Color::Black);

	for (int i = 0; i < 60; i++) 
	{
		float angle = i * PI / 30.0f - PI / 2.0f;
		if (i % 5 == 0) 
		{
			float len = (i % 15 == 0) ? innerRadius * 0.22f : innerRadius * 0.15f;
			if(!m_bBorder)
				len = (i % 15 == 0) ? innerRadius * 0.15f : innerRadius * 0.1f;
		
			float delta = 6.0f;
			if(m_bBorder)
				delta = 2.0f;

			Gdiplus::Pen* p = (i % 15 == 0) ? &penQuarter : &penHour;
			g.DrawLine(p,
				xCenter + (float)cos(angle) * (innerRadius - len),
				yCenter + (float)sin(angle) * (innerRadius - len),
				xCenter + (float)cos(angle) * (innerRadius + delta),
				yCenter + (float)sin(angle) * (innerRadius + delta)
			);
		}
		else 
		{
			float dotR = 1.3f;

			float delta = 3.0f;
			if (m_bBorder)
				delta = 0.0f;

			float px = xCenter + (float)cos(angle) * (innerRadius + delta);
			float py = yCenter + (float)sin(angle) * (innerRadius + delta);
			g.FillEllipse(&brushBlack, px - dotR, py - dotR, dotR * 2.0f, dotR * 2.0f);
		}
	}

	// --- 4. ТЕКСТ ---
	Gdiplus::FontFamily fontFamily(L"Arial");
	Gdiplus::StringFormat strFormat;
	strFormat.SetAlignment(Gdiplus::StringAlignmentCenter);

	Gdiplus::Font fontLN(&fontFamily, innerRadius * 0.2f, Gdiplus::FontStyleItalic | Gdiplus::FontStyleUnderline);
	Gdiplus::SolidBrush brushLN(Gdiplus::Color(255, 240, 128, 128));
	g.DrawString(L"LN", -1, &fontLN, Gdiplus::PointF(xCenter, yCenter - innerRadius * 0.52f), &strFormat, &brushLN);

	COleDateTime now = COleDateTime::GetCurrentTime();
	if (m_bDay) {
		CString strDay = now.Format(_T("%A"));
		Gdiplus::Font fontDay(&fontFamily, innerRadius * 0.12f, Gdiplus::FontStyleBold);
		Gdiplus::SolidBrush brushDay((now.GetDayOfWeek() == 1 || now.GetDayOfWeek() == 7) ? Gdiplus::Color::Red : Gdiplus::Color(255, 139, 69, 19));
		g.DrawString(strDay, -1, &fontDay, Gdiplus::PointF(xCenter, yCenter + innerRadius * 0.18f), &strFormat, &brushDay);
	}

	if (m_bDate) {
		CString strDate = now.Format(_T("%d.%m.%Y"));
		Gdiplus::Font fontDate(&fontFamily, innerRadius * 0.12f, Gdiplus::FontStyleBold);
		Gdiplus::SolidBrush brushDate(Gdiplus::Color(255, 70, 130, 180));
		g.DrawString(strDate, -1, &fontDate, Gdiplus::PointF(xCenter, yCenter + innerRadius * 0.45f), &strFormat, &brushDate);
	}

	// --- 5. СТРІЛКИ ---
	auto DrawHand = [&](int pos, float len, float width, bool hasWhiteLine) 
	{
		Gdiplus::Pen pHand(Gdiplus::Color::Black, width);
		pHand.SetEndCap(Gdiplus::LineCapRound);
		float angle = pos * PI / 30.0f - PI / 2.0f;
		float x = xCenter + (float)cos(angle) * len;
		float y = yCenter + (float)sin(angle) * len;
		g.DrawLine(&pHand, xCenter, yCenter, x, y);
		if (hasWhiteLine) 
		{
			Gdiplus::Pen pWhite(Gdiplus::Color::White, width / 2.2f);
			pWhite.SetEndCap(Gdiplus::LineCapRound);
			g.DrawLine(&pWhite, xCenter, yCenter, x, y);
		}
	};

	DrawHand(now.GetHour() * 5 + now.GetMinute() / 12, innerRadius * 0.58f, 6.5f, true);
	DrawHand(now.GetMinute(), innerRadius * 0.85f, 4.5f, true);

	Gdiplus::Pen pSec(Gdiplus::Color::Red, 1.5f);
	float sAngle = now.GetSecond() * PI / 30.0f - PI / 2.0f;
	g.DrawLine(&pSec,
		xCenter + (float)cos(sAngle + PI) * (innerRadius * 0.15f),
		yCenter + (float)sin(sAngle + PI) * (innerRadius * 0.15f),
		xCenter + (float)cos(sAngle) * (innerRadius * 0.92f),
		yCenter + (float)sin(sAngle) * (innerRadius * 0.92f));

	g.FillEllipse(&brushBlack, xCenter - 4.0f, yCenter - 4.0f, 8.0f, 8.0f);
}


int CClockvcmfcDlg::ClcX(int sec, int size, int xCenter) {
	return (int)(cos(sec * PI / 30 - PI / 2) * size + xCenter);
}

int CClockvcmfcDlg::ClcY(int sec, int size, int yCenter) {
	return (int)(sin(sec * PI / 30 - PI / 2) * size + yCenter);
}

void CClockvcmfcDlg::OnTimer(UINT_PTR nIDEvent)
{
	Invalidate(FALSE); // Перемалювати
	CDialogEx::OnTimer(nIDEvent);
}

void CClockvcmfcDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_bMoving) PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CClockvcmfcDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu menu;
	if (menu.LoadMenu(IDR_MENU_CONTEXT)) { // ID вашого меню
		CMenu* pPopup = menu.GetSubMenu(0);
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
}

LRESULT CClockvcmfcDlg::OnTrayNotify(WPARAM wParam, LPARAM lParam)
{
	if (lParam == WM_RBUTTONUP)
	{
		CPoint pos;
		GetCursorPos(&pos); // Отримуємо координати курсора

		CMenu menu;
		if (menu.LoadMenu(IDR_MENU_CONTEXT)) // ID вашого ресурсу меню
		{
			// Вибираємо TrayPopup (індекс 1, бо ClockPopup — це 0)
			CMenu* pPopup = menu.GetSubMenu(1);
			if (pPopup)
			{
				// ВАЖЛИВО: Це потрібно, щоб меню зникало, коли ви клікаєте повз нього
				SetForegroundWindow();

				// Динамічно змінюємо текст Hide/Open залежно від стану вікна
				if (IsWindowVisible())
					pPopup->ModifyMenu(ID_MENU_HIDE, MF_BYCOMMAND | MF_STRING, ID_MENU_HIDE, _T("Hide"));
				else
					pPopup->ModifyMenu(ID_MENU_HIDE, MF_BYCOMMAND | MF_STRING, ID_MENU_HIDE, _T("Open"));

				// Показуємо меню
				pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pos.x, pos.y, this);
			}
		}
	}
	// Якщо подвійний клік лівою — відкриваємо/ховаємо годинник
	else if (lParam == WM_LBUTTONDBLCLK)
	{
		SendMessage(WM_COMMAND, ID_MENU_HIDE);
	}

	return 0;
}

// Обробники меню
void CClockvcmfcDlg::OnMenuAbout() { CAboutDlg dlg; dlg.DoModal(); }
void CClockvcmfcDlg::OnMenuCalendar() { CCalendarDlg dlg; dlg.DoModal(); }
void CClockvcmfcDlg::OnMenuExit() { Shell_NotifyIcon(NIM_DELETE, &m_nid); PostQuitMessage(0); }

void CClockvcmfcDlg::OnMenuShutdown() {
	CShutDownDlg dlg(m_timeShutDown, m_isShutDown, m_isSleep);
	if (dlg.DoModal() == IDOK) {
		m_timeShutDown = dlg.m_tm; m_isShutDown = dlg.m_isShutDown; m_isSleep = dlg.m_isSleep;
	}
}

void CClockvcmfcDlg::OnMenuSetup() {
	CSetupDlg dlg(m_bGMT, m_bDate, m_bDay, m_bMoving, m_bTopMost, m_bTransparent, m_bBorder, m_bSound, m_nOpacity);
	if (dlg.DoModal() == IDOK) {
		m_bGMT = dlg.m_bGMT; m_bDate = dlg.m_bDate; m_bDay = dlg.m_bDay;
		m_bMoving = dlg.m_bMoving; m_bTopMost = dlg.m_bTopMost;
		m_bTransparent = dlg.m_bTransparent; m_bBorder = dlg.m_bBorder;
		m_bSound = dlg.m_bSound; m_nOpacity = dlg.m_nOpacity;
		SetLayeredWindowAttributes(0, (255 * m_nOpacity) / 100, LWA_ALPHA);
		SetWindowPos(m_bTopMost ? &wndTopMost : &wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
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

HCURSOR CClockvcmfcDlg::OnQueryDragIcon() { return static_cast<HCURSOR>(m_hIcon); }