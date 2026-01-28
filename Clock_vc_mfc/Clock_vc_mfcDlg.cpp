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
	int nSize = 134;

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
	CRect rect;
	GetClientRect(&rect);

	// Ваше зміщення на 1 піксель для центру
	int xCenter = (rect.Width() / 2) - 1;
	int yCenter = (rect.Height() / 2) - 1;

	// Товщина кільця
	int borderThickness = 6;

	// ЩЕ БІЛЬШИЙ РАДІУС:
	// Використовуємо -2 замість попередніх розрахунків. 
	// Це виштовхне край 6-піксельного кільця впритул до межі вікна.
	int radius = (min(rect.Width() / 2, rect.Height() / 2)) - 2;

	COleDateTime now = COleDateTime::GetCurrentTime();
	if (m_bGMT) {
		SYSTEMTIME st;
		GetSystemTime(&st);
		now = COleDateTime(st);
	}

	// --- 1. ФОН ЦИФЕРБЛАТА ---
	Gdiplus::SolidBrush faceBrush(Gdiplus::Color(255, 242, 238, 225));
	g.FillEllipse(&faceBrush, xCenter - radius, yCenter - radius, radius * 2, radius * 2);

	// --- 2. ПОДВІЙНИЙ БОРДЕР (Кільце) ---
	if (m_bBorder) {
		// Зовнішнє чорне кільце
		Gdiplus::Pen penBlack(Gdiplus::Color::Black, (float)borderThickness);
		g.DrawEllipse(&penBlack, xCenter - radius, yCenter - radius, radius * 2, radius * 2);

		// Внутрішня сіра лінія (відблиск)
		Gdiplus::Pen penGray(Gdiplus::Color::Gray, 2.0f);
		g.DrawEllipse(&penGray, xCenter - radius, yCenter - radius, radius * 2, radius * 2);
	}

	// Внутрішній радіус для елементів (відступ від центру кільця всередину)
	int innerRadius = radius - (borderThickness / 2);

	// --- 3. ПОДІЛКИ (Marks) ---
	Gdiplus::Pen penHour(Gdiplus::Color::Black, 2.0f);
	Gdiplus::Pen penQuarter(Gdiplus::Color::Black, 3.5f);
	Gdiplus::SolidBrush brushDot(Gdiplus::Color::Black);

	for (int i = 0; i < 60; i++) {
		if (i % 5 == 0) {
			float len = (i % 15 == 0) ? innerRadius * 0.18f : innerRadius * 0.12f;
			Gdiplus::Pen* p = (i % 15 == 0) ? &penQuarter : &penHour;
			g.DrawLine(p, ClcX(i, innerRadius - (int)len, xCenter), ClcY(i, innerRadius - (int)len, yCenter),
				ClcX(i, innerRadius, xCenter), ClcY(i, innerRadius, yCenter));
		}
		else {
			float dotR = innerRadius * 0.015f;
			if (dotR < 1.1f) dotR = 1.1f;
			int px = ClcX(i, innerRadius - (int)(innerRadius * 0.05f), xCenter);
			int py = ClcY(i, innerRadius - (int)(innerRadius * 0.05f), yCenter);
			g.FillEllipse(&brushDot, (float)px - dotR, (float)py - dotR, dotR * 2, dotR * 2);
		}
	}

	// --- 4. ТЕКСТОВІ НАПИСИ ---
	Gdiplus::FontFamily fontFamily(L"Arial");
	Gdiplus::StringFormat strFormat;
	strFormat.SetAlignment(Gdiplus::StringAlignmentCenter);

	// "LN"
	Gdiplus::Font fontLN(&fontFamily, innerRadius * 0.18f, Gdiplus::FontStyleItalic | Gdiplus::FontStyleUnderline);
	Gdiplus::SolidBrush brushLN(Gdiplus::Color(255, 240, 128, 128));
	g.DrawString(L"LN", -1, &fontLN, Gdiplus::PointF((float)xCenter, yCenter - innerRadius * 0.48f), &strFormat, &brushLN);

	// День тижня
	if (m_bDay) {
		CString strDay = now.Format(_T("%A"));
		Gdiplus::Font fontDay(&fontFamily, innerRadius * 0.1f, Gdiplus::FontStyleBold);
		Gdiplus::SolidBrush brushDay((now.GetDayOfWeek() == 1 || now.GetDayOfWeek() == 7) ?
			Gdiplus::Color::Red : Gdiplus::Color(255, 139, 69, 19));
		g.DrawString(strDay, -1, &fontDay, Gdiplus::PointF((float)xCenter, yCenter + innerRadius * 0.18f), &strFormat, &brushDay);
	}

	// Дата
	if (m_bDate) {
		CString strDate = now.Format(_T("%d.%m.%Y"));
		Gdiplus::Font fontDate(&fontFamily, innerRadius * 0.1f, Gdiplus::FontStyleBold);
		Gdiplus::SolidBrush brushDate(Gdiplus::Color(255, 70, 130, 180));
		g.DrawString(strDate, -1, &fontDate, Gdiplus::PointF((float)xCenter, yCenter + innerRadius * 0.42f), &strFormat, &brushDate);
	}

	// --- 5. СТРІЛКИ ---
	auto DrawHand = [&](int pos, int len, float width, bool hasWhiteLine) {
		Gdiplus::Pen pBlack(Gdiplus::Color::Black, width);
		pBlack.SetEndCap(Gdiplus::LineCapRound);
		int x = ClcX(pos, len, xCenter);
		int y = ClcY(pos, len, yCenter);
		g.DrawLine(&pBlack, xCenter, yCenter, x, y);

		if (hasWhiteLine) {
			Gdiplus::Pen pWhite(Gdiplus::Color::White, width / 2.5f);
			pWhite.SetEndCap(Gdiplus::LineCapRound);
			g.DrawLine(&pWhite, xCenter, yCenter, x, y);
		}
		};

	DrawHand(now.GetHour() * 5 + now.GetMinute() / 12, (int)(innerRadius * 0.55f), 6.0f, true);
	DrawHand(now.GetMinute(), (int)(innerRadius * 0.8f), 4.0f, true);

	// Секундна стрілка
	Gdiplus::Pen pSec(Gdiplus::Color::Red, 1.5f);
	int sX = ClcX(now.GetSecond(), (int)(innerRadius * 0.9f), xCenter);
	int sY = ClcY(now.GetSecond(), (int)(innerRadius * 0.9f), yCenter);
	int sX_tail = ClcX(now.GetSecond() + 30, (int)(innerRadius * 0.15f), xCenter);
	int sY_tail = ClcY(now.GetSecond() + 30, (int)(innerRadius * 0.15f), yCenter);
	g.DrawLine(&pSec, sX_tail, sY_tail, sX, sY);

	// Центральна точка
	Gdiplus::SolidBrush brushCenter(Gdiplus::Color::Black);
	g.FillEllipse(&brushCenter, xCenter - 4, yCenter - 4, 8, 8);
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
	if (lParam == WM_LBUTTONDBLCLK) ShowWindow(IsWindowVisible() ? SW_HIDE : SW_SHOW);
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
		ShowWindow(SW_HIDE);
	else
	{
		ShowWindow(SW_SHOW);
		SetForegroundWindow(); 
	}
}

HCURSOR CClockvcmfcDlg::OnQueryDragIcon() { return static_cast<HCURSOR>(m_hIcon); }