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
END_MESSAGE_MAP()

BOOL CClockvcmfcDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE; // Просто повертаємо TRUE, нічого не зафарбовуючи
}

BOOL CClockvcmfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 1. Встановлюємо точний розмір вікна (140x140 пікселів)
	int nSize = 140;

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
	rgn.CreateEllipticRgn(0, 0, nSize, nSize);
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

	// 1. Створюємо буфер у пам'яті (віртуальне полотно)
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	CBitmap memBitmap;
	memBitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	CBitmap* pOldBitmap = memDC.SelectObject(&memBitmap);

	// 2. Малюємо на віртуальному полотні за допомогою GDI+
	Gdiplus::Graphics graphics(memDC.GetSafeHdc());
	graphics.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);

	// Очищаємо фон буфера (прозорим або кольором фону)
	Gdiplus::SolidBrush backBrush(Gdiplus::Color(255, 245, 245, 245));
	graphics.FillRectangle(&backBrush, 0, 0, rect.Width(), rect.Height());

	// Викликаємо малювання годинника
	DrawClock(graphics);

	// 3. Копіюємо готовий буфер на реальний екран одним рухом
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	// Очищення ресурсів
	memDC.SelectObject(pOldBitmap);
}

void CClockvcmfcDlg::DrawClock(Gdiplus::Graphics& g)
{
	CRect rect;
	GetClientRect(&rect);
	int xCenter = rect.Width() / 2;
	int yCenter = rect.Height() / 2;
	int radius = static_cast<int>(min(xCenter, yCenter) * 0.9);

	COleDateTime now = COleDateTime::GetCurrentTime();
	if (m_bGMT) {
		SYSTEMTIME st;
		GetSystemTime(&st);
		now = COleDateTime(st);
	}

	// --- 1. ФОН (Колір "Parchment" як у C#) ---
	Gdiplus::SolidBrush faceBrush(Gdiplus::Color(255, 242, 238, 225));
	g.FillEllipse(&faceBrush, xCenter - radius, yCenter - radius, radius * 2, radius * 2);

	// --- 2. ТЕКСТОВІ НАПИСИ (LN, День, Дата) ---
	Gdiplus::FontFamily fontFamily(L"Arial");
	Gdiplus::StringFormat strFormat;
	strFormat.SetAlignment(Gdiplus::StringAlignmentCenter);

	// "LN" зверху
	Gdiplus::Font fontLN(&fontFamily, radius * 0.15f, Gdiplus::FontStyleItalic | Gdiplus::FontStyleUnderline);
	Gdiplus::SolidBrush brushLN(Gdiplus::Color::LightCoral);
	g.DrawString(L"LN", -1, &fontLN, Gdiplus::PointF(xCenter, yCenter - radius * 0.45f), &strFormat, &brushLN);

	// День тижня
	if (m_bDay) {
		CString strDay = now.Format(_T("%A")); // Назва дня
		Gdiplus::Font fontDay(&fontFamily, radius * 0.08f, Gdiplus::FontStyleBold);
		Gdiplus::SolidBrush brushDay((now.GetDayOfWeek() == 1 || now.GetDayOfWeek() == 7) ?
			Gdiplus::Color::Red : Gdiplus::Color::SaddleBrown);
		g.DrawString(strDay, -1, &fontDay, Gdiplus::PointF(xCenter, yCenter + radius * 0.15f), &strFormat, &brushDay);
	}

	// Дата
	if (m_bDate) {
		CString strDate = now.Format(_T("%d.%m.%Y"));
		Gdiplus::Font fontDate(&fontFamily, radius * 0.08f, Gdiplus::FontStyleBold);
		Gdiplus::SolidBrush brushDate(Gdiplus::Color::SteelBlue);
		g.DrawString(strDate, -1, &fontDate, Gdiplus::PointF(xCenter, yCenter + radius * 0.35f), &strFormat, &brushDate);
	}

	// --- 3. ЦИФЕРБЛАТ (Рисочки та точки) ---
	Gdiplus::Pen penBlack(Gdiplus::Color::Black, 1);
	Gdiplus::SolidBrush brushBlack(Gdiplus::Color::Black);

	for (int i = 0; i < 60; i++) {
		if (i % 5 == 0) { // Годинні рисочки
			int len = (i % 15 == 0) ? radius * 0.15f : radius * 0.1f;
			g.DrawLine(&penBlack, ClcX(i, radius - len, xCenter), ClcY(i, radius - len, yCenter),
				ClcX(i, radius, xCenter), ClcY(i, radius, yCenter));
		}
		else { // Хвилинні точки
			int dotR = 1;
			int px = ClcX(i, radius - 5, xCenter);
			int py = ClcY(i, radius - 5, yCenter);
			g.FillEllipse(&brushBlack, px - dotR, py - dotR, dotR * 2, dotR * 2);
		}
	}

	// --- 4. СТРІЛКИ (Ефект "подвійної лінії") ---
	auto DrawHand = [&](int pos, int len, int width, Gdiplus::Color color) {
		Gdiplus::Pen pMain(color, (float)width);
		Gdiplus::Pen pInner(Gdiplus::Color::White, 1.0f); // Біла лінія всередині
		int x = ClcX(pos, len, xCenter);
		int y = ClcY(pos, len, yCenter);
		g.DrawLine(&pMain, xCenter, yCenter, x, y);
		if (width > 1) g.DrawLine(&pInner, xCenter, yCenter, x, y);
		};

	// Годинна
	DrawHand(now.GetHour() * 5 + now.GetMinute() / 12, radius * 0.5, 5, Gdiplus::Color::Black);
	// Хвилинна
	DrawHand(now.GetMinute(), radius * 0.75, 3, Gdiplus::Color::Black);
	// Секундна (червона, без білої лінії)
	Gdiplus::Pen pSec(Gdiplus::Color::Red, 1);
	g.DrawLine(&pSec, ClcX(now.GetSecond() + 30, radius * 0.15, xCenter), ClcY(now.GetSecond() + 30, radius * 0.15, yCenter),
		ClcX(now.GetSecond(), radius * 0.85, xCenter), ClcY(now.GetSecond(), radius * 0.85, yCenter));

	// Центр
	g.FillEllipse(&brushBlack, xCenter - 3, yCenter - 3, 6, 6);
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

HCURSOR CClockvcmfcDlg::OnQueryDragIcon() { return static_cast<HCURSOR>(m_hIcon); }