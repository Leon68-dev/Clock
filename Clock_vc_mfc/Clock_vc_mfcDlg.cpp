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

	// Завантажуємо шрифт для цифрового годинника
	m_fontCollection.AddFontFile(L"digital_7italic.ttf");

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

//void CClockvcmfcDlg::DrawClock(Gdiplus::Graphics& g)
//{
//	const float PI = 3.1415926535f;
//	float w = (float)m_nPanelWidth;  // 150.0f
//	float h = (float)m_nPanelHeight; // Динамічна (150 або 200)
//
//	g.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
//	// GridFit допомагає цифровим шрифтам не "сіпатися"
//	g.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAliasGridFit);
//
//	// --- 1. ТЕМНА ПІДЛОЖКА (Sidebar Style) ---
//	Gdiplus::GraphicsPath path;
//	float cornerR = 15.0f;
//	path.AddArc(0.0f, 0.0f, cornerR, cornerR, 180.0f, 90.0f);
//	path.AddArc(w - cornerR, 0.0f, cornerR, cornerR, 270.0f, 90.0f);
//	path.AddArc(w - cornerR, h - cornerR, cornerR, cornerR, 0.0f, 90.0f);
//	path.AddArc(0.0f, h - cornerR, cornerR, cornerR, 90.0f, 90.0f);
//	path.CloseFigure();
//
//	Gdiplus::SolidBrush panelBrush(Gdiplus::Color(160, 20, 20, 20));
//	g.FillPath(&panelBrush, &path);
//
//	Gdiplus::Pen glassPen(Gdiplus::Color(80, 255, 255, 255), 1.0f);
//	g.DrawPath(&glassPen, &path);
//
//	// --- 2. ПАРАМЕТРИ АНАЛОГОВОГО ГОДИННИКА ---
//	float xCenter = w / 2.0f; // 75.0f
//	float yCenter = 75.0f;    // Центр у верхньому квадраті 150x150
//	float radius = 67.0f;     // Радіус (діаметр 134)
//	float borderThickness = 6.0f;
//
//	// Фон циферблата (ТІЛЬКИ КРУГ)
//	if (!m_bTransparent)
//	{
//		Gdiplus::SolidBrush faceBrush(Gdiplus::Color(255, 242, 238, 225));
//		g.FillEllipse(&faceBrush, xCenter - radius, yCenter - radius, radius * 2.0f, radius * 2.0f);
//	}
//
//	// Бордєр (Кільце)
//	if (m_bBorder)
//	{
//		Gdiplus::RectF penRect(xCenter - radius, yCenter - radius, radius * 2.0f, radius * 2.0f);
//		float inset = borderThickness / 2.0f;
//		penRect.Inflate(-inset, -inset);
//		Gdiplus::Pen pBlack(Gdiplus::Color::Black, borderThickness);
//		Gdiplus::Pen pGray(Gdiplus::Color::Gray, 2.0f);
//		g.DrawEllipse(&pBlack, penRect);
//		g.DrawEllipse(&pGray, penRect);
//	}
//
//	float innerRadius = radius - borderThickness - 1.5f;
//
//	// 3. ПОДІЛКИ (Ticks)
//	Gdiplus::Pen penHour(Gdiplus::Color::Black, 2.0f);
//	Gdiplus::Pen penQuarter(Gdiplus::Color::Black, 4.0f);
//	Gdiplus::SolidBrush brushBlack(Gdiplus::Color::Black);
//	Gdiplus::SolidBrush brushFace(Gdiplus::Color(255, 242, 238, 225));
//
//	for (int i = 0; i < 60; i++)
//	{
//		float angle = i * PI / 30.0f - PI / 2.0f;
//		float cosA = cosf(angle);
//		float sinA = sinf(angle);
//
//		if (i % 5 == 0)
//		{
//			float len = (i % 15 == 0) ? innerRadius * 0.22f : innerRadius * 0.15f;
//			Gdiplus::Pen* p = (i % 15 == 0) ? &penQuarter : &penHour;
//			g.DrawLine(p,
//				xCenter + cosA * (innerRadius - len), yCenter + sinA * (innerRadius - len),
//				xCenter + cosA * (innerRadius + 3.0f), yCenter + sinA * (innerRadius + 3.0f));
//
//			float markDotR = 1.5f;
//			g.FillEllipse(&brushFace,
//				xCenter + cosA * (innerRadius - len) - markDotR,
//				yCenter + sinA * (innerRadius - len) - markDotR,
//				markDotR * 2.0f, markDotR * 2.0f);
//		}
//		else
//		{
//			float dotR = 1.3f;
//			g.FillEllipse(&brushBlack,
//				xCenter + cosA * (innerRadius + 1.5f) - dotR,
//				yCenter + sinA * (innerRadius + 1.5f) - dotR,
//				dotR * 2.0f, dotR * 2.0f);
//		}
//	}
//
//	// --- ОТРИМАННЯ ЧАСУ ---
//	SYSTEMTIME st;
//	if (m_bGMT) ::GetSystemTime(&st); else ::GetLocalTime(&st);
//	COleDateTime now(st);
//
//	// 4. ТЕКСТ НА ЦИФЕРБЛАТІ (Arial)
//	Gdiplus::FontFamily fontFamily(L"Arial");
//	Gdiplus::StringFormat sf;
//	sf.SetAlignment(Gdiplus::StringAlignmentCenter);
//	sf.SetLineAlignment(Gdiplus::StringAlignmentCenter);
//
//	Gdiplus::Font fontLN(&fontFamily, innerRadius * 0.2f, Gdiplus::FontStyleItalic | Gdiplus::FontStyleUnderline);
//	Gdiplus::SolidBrush bLN(Gdiplus::Color(255, 240, 128, 128));
//	g.DrawString(L"LN", -1, &fontLN, Gdiplus::PointF(xCenter, yCenter - innerRadius * 0.52f), &sf, &bLN);
//
//	Gdiplus::Font fontText(&fontFamily, innerRadius * 0.11f, Gdiplus::FontStyleBold);
//	Gdiplus::SolidBrush bGray(Gdiplus::Color::Gray);
//	g.DrawString(L"C++", -1, &fontText, Gdiplus::PointF(xCenter, yCenter + 16.0f - innerRadius * 0.52f), &sf, &bGray);
//
//	float yDelta = 5.0f;
//	if (m_bDay)
//	{
//		CString strDay = now.Format(_T("%a"));
//		strDay.MakeUpper();
//		bool isWeekend = (now.GetDayOfWeek() == 1 || now.GetDayOfWeek() == 7);
//		Gdiplus::SolidBrush bDay(isWeekend ? Gdiplus::Color(255, 240, 128, 128) : Gdiplus::Color::Gray);
//		g.DrawString(strDay, -1, &fontText, Gdiplus::PointF(xCenter, yCenter + yDelta + innerRadius * 0.12f), &sf, &bDay);
//	}
//	if (m_bDate)
//	{
//		CString strDate = now.Format(_T("%d-%m-%y"));
//		g.DrawString(strDate, -1, &fontText, Gdiplus::PointF(xCenter, yCenter + yDelta + innerRadius * 0.35f), &sf, &bGray);
//	}
//	if (m_bGMT)
//	{
//		g.DrawString(L"GMT", -1, &fontText, Gdiplus::PointF(xCenter, yCenter + yDelta + innerRadius * 0.58f), &sf, &bGray);
//	}
//
//	// 5. СТРІЛКИ
//	float fSeconds = m_bSmooth ? (st.wSecond + st.wMilliseconds / 1000.0f) : (float)st.wSecond;
//	float fMinutes = st.wMinute + fSeconds / 60.0f;
//	float fHours = (st.wHour % 12 + fMinutes / 60.0f) * 5.0f;
//
//	auto DrawHandMFC = [&](float val, float len, float width, bool hasWhiteLine)
//	{
//		float a = val * PI / 30.0f - PI / 2.0f;
//		float x = xCenter + cosf(a) * len;
//		float y = yCenter + sinf(a) * len;
//		Gdiplus::Pen pBlack(Gdiplus::Color::Black, width);
//		pBlack.SetStartCap(Gdiplus::LineCapRound);
//		pBlack.SetEndCap(Gdiplus::LineCapRound);
//		g.DrawLine(&pBlack, xCenter, yCenter, x, y);
//		if (hasWhiteLine) {
//			Gdiplus::Pen pWhite(Gdiplus::Color::White, width / 2.2f);
//			pWhite.SetStartCap(Gdiplus::LineCapRound);
//			pWhite.SetEndCap(Gdiplus::LineCapRound);
//			g.DrawLine(&pWhite, xCenter, yCenter, x, y);
//		}
//	};
//
//	DrawHandMFC(fHours, innerRadius * 0.58f, 6.5f, true);
//	DrawHandMFC(fMinutes, innerRadius * 0.85f, 4.5f, true);
//
//	Gdiplus::Pen pSec(Gdiplus::Color::Red, 1.5f);
//	float sAngle = fSeconds * PI / 30.0f - PI / 2.0f;
//	g.DrawLine(&pSec,
//		xCenter - cosf(sAngle) * (innerRadius * 0.15f), yCenter - sinf(sAngle) * (innerRadius * 0.15f),
//		xCenter + cosf(sAngle) * (innerRadius * 0.95f), yCenter + sinf(sAngle) * (innerRadius * 0.95f));
//
//	g.FillEllipse(&brushBlack, xCenter - 4.0f, yCenter - 4.0f, 8.0f, 8.0f);
//
//	// --- 6. ЦИФРОВИЙ ГОДИННИК (LCD STYLE - ULTRA TIGHT) ---
//	if (m_bShowDigital)
//	{
//		SYSTEMTIME st;
//		if (m_bGMT) ::GetSystemTime(&st); else ::GetLocalTime(&st);
//
//		Gdiplus::FontFamily digFamily;
//		int numFound = 0;
//		m_fontCollection.GetFamilies(1, &digFamily, &numFound);
//
//		if (numFound > 0)
//		{
//			// 1. ПАРАМЕТРИ LCD ПАНЕЛІ
//			float lcdW = 110.0f; // Трохи звузили панель під компактні цифри
//			float lcdH = 36.0f;
//			float lcdX = xCenter - (lcdW / 2.0f);
//			float lcdY = 154.0f;
//
//			Gdiplus::SolidBrush lcdBackBrush(Gdiplus::Color(255, 170, 185, 165));
//			Gdiplus::GraphicsPath lcdPath;
//			float r = 5.0f;
//			lcdPath.AddArc(lcdX, lcdY, r, r, 180, 90);
//			lcdPath.AddArc(lcdX + lcdW - r, lcdY, r, r, 270, 90);
//			lcdPath.AddArc(lcdX + lcdW - r, lcdY + lcdH - r, r, r, 0, 90);
//			lcdPath.AddArc(lcdX, lcdY + lcdH - r, r, r, 90, 90);
//			lcdPath.CloseFigure();
//			g.FillPath(&lcdBackBrush, &lcdPath);
//
//			Gdiplus::Pen lcdBorder(Gdiplus::Color(100, 0, 0, 0), 1.0f);
//			g.DrawPath(&lcdBorder, &lcdPath);
//
//			// 2. НАЛАШТУВАННЯ ШРИФТУ
//			Gdiplus::Font digFont(&digFamily, 26, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
//
//			Gdiplus::StringFormat sfCenter, sfLeft, sfRight;
//			sfCenter.SetAlignment(Gdiplus::StringAlignmentCenter);
//			sfCenter.SetLineAlignment(Gdiplus::StringAlignmentCenter);
//			sfLeft.SetAlignment(Gdiplus::StringAlignmentNear);
//			sfLeft.SetLineAlignment(Gdiplus::StringAlignmentCenter);
//			sfRight.SetAlignment(Gdiplus::StringAlignmentFar);
//			sfRight.SetLineAlignment(Gdiplus::StringAlignmentCenter);
//
//			float textY = lcdY + (lcdH / 2.0f) + 2.0f;
//
//			// --- НОВІ ТІСНІ КООРДИНАТИ ---
//			// baseMid з корекцією нахилу (italic)
//			float baseMid = xCenter + 2.0f;
//
//			float posX_Minutes = baseMid;           // Центр
//			float posX_Colon1 = baseMid - 13.0f;   // Було -15 (зсунули ближче до центру на 2px)
//			float posX_Colon2 = baseMid + 13.0f;   // Було +15 (зсунули ближче до центру на 2px)
//			float posX_Hours = baseMid - 16.0f;   // Було -19 (притиснули години до двокрапки)
//			float posX_Seconds = baseMid + 16.0f;   // Було +19 (притиснули секунди до двокрапки)
//
//			// 3. МАЛЮЄМО ФОНОВІ СЕГМЕНТИ
//			Gdiplus::SolidBrush shadowBrush(Gdiplus::Color(25, 0, 0, 0));
//			g.DrawString(L"88", -1, &digFont, Gdiplus::PointF(posX_Hours, textY), &sfRight, &shadowBrush);
//			g.DrawString(L":", -1, &digFont, Gdiplus::PointF(posX_Colon1, textY), &sfCenter, &shadowBrush);
//			g.DrawString(L"88", -1, &digFont, Gdiplus::PointF(posX_Minutes, textY), &sfCenter, &shadowBrush);
//			g.DrawString(L":", -1, &digFont, Gdiplus::PointF(posX_Colon2, textY), &sfCenter, &shadowBrush);
//			g.DrawString(L"88", -1, &digFont, Gdiplus::PointF(posX_Seconds, textY), &sfLeft, &shadowBrush);
//
//			// 4. МАЛЮЄМО АКТИВНИЙ ЧАС
//			Gdiplus::SolidBrush digBrush(Gdiplus::Color(255, 0, 0, 0));
//
//			CString sH, sM, sS;
//			sH.Format(_T("%d"), st.wHour);
//			sM.Format(_T("%02d"), st.wMinute);
//			sS.Format(_T("%02d"), st.wSecond);
//
//			g.DrawString(sH, -1, &digFont, Gdiplus::PointF(posX_Hours, textY), &sfRight, &digBrush);
//			g.DrawString(L":", -1, &digFont, Gdiplus::PointF(posX_Colon1, textY), &sfCenter, &digBrush);
//			g.DrawString(sM, -1, &digFont, Gdiplus::PointF(posX_Minutes, textY), &sfCenter, &digBrush);
//			g.DrawString(L":", -1, &digFont, Gdiplus::PointF(posX_Colon2, textY), &sfCenter, &digBrush);
//			g.DrawString(sS, -1, &digFont, Gdiplus::PointF(posX_Seconds, textY), &sfLeft, &digBrush);
//		}
//	}
//
//
//	// --- 7. МОДУЛЬ КАЛЕНДАРЯ ---
//	if (m_bShowCalendar)
//	{
//		// Визначаємо початкову Y-позицію (після цифрового годинника)
//		float calY = 150.0f + (m_bShowDigital ? 50.0f : 0.0f);
//		float calX = 10.0f; // Відступ зліва
//		float calW = w - 20.0f; // Ширина сітки
//
//		// 1. Розділювальна лінія (ефект вдавлювання)
//		g.DrawLine(&Gdiplus::Pen(Gdiplus::Color(50, 0, 0, 0), 1.0f), 15.0f, calY, w - 15.0f, calY);
//		g.DrawLine(&Gdiplus::Pen(Gdiplus::Color(30, 255, 255, 255), 1.0f), 15.0f, calY + 1.0f, w - 15.0f, calY + 1.0f);
//
//		// 2. Отримуємо дані про поточний місяць
//		SYSTEMTIME st;
//		GetLocalTime(&st);
//		COleDateTime today(st);
//		COleDateTime firstDay(st.wYear, st.wMonth, 1, 0, 0, 0);
//
//		// Визначаємо день тижня для 1-го числа (в MFC 1=Нд, 2=Пн...)
//		// Переводимо в формат: 0=Пн, 6=Нд
//		int startDay = firstDay.GetDayOfWeek();
//		startDay = (startDay == 1) ? 6 : startDay - 2;
//
//		// Кількість днів у місяці
//		int daysInMonth = 31;
//		if (st.wMonth == 4 || st.wMonth == 6 || st.wMonth == 9 || st.wMonth == 11) daysInMonth = 30;
//		else if (st.wMonth == 2) {
//			bool leap = (st.wYear % 4 == 0 && st.wYear % 100 != 0) || (st.wYear % 400 == 0);
//			daysInMonth = leap ? 29 : 28;
//		}
//
//		// 3. Малюємо заголовок (Місяць та Рік)
//		Gdiplus::FontFamily arial(L"Arial");
//		Gdiplus::Font fontHeader(&arial, 12, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
//		Gdiplus::SolidBrush bWhite(Gdiplus::Color(220, 255, 255, 255));
//
//		CString strHeader = today.Format(_T("%B %Y")); // Назва місяця та рік
//		Gdiplus::StringFormat sf;
//		sf.SetAlignment(Gdiplus::StringAlignmentCenter);
//		g.DrawString(strHeader, -1, &fontHeader, Gdiplus::PointF(w / 2.0f, calY + 10), &sf, &bWhite);
//
//		// 4. Малюємо дні тижня (Пн...Нд)
//		Gdiplus::Font fontDays(&arial, 10, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
//		const TCHAR* dayNames[] = { _T("M"), _T("T"), _T("W"), _T("T"), _T("F"), _T("S"), _T("S") };
//		float cellW = calW / 7.0f;
//
//		for (int i = 0; i < 7; i++) {
//			Gdiplus::SolidBrush bDayName((i >= 5) ? Gdiplus::Color(200, 255, 100, 100) : Gdiplus::Color(150, 255, 255, 255));
//			g.DrawString(dayNames[i], -1, &fontDays, Gdiplus::PointF(calX + i * cellW + cellW / 2, calY + 30), &sf, &bDayName);
//		}
//
//		// 5. Малюємо сітку чисел
//		int row = 0;
//		for (int d = 1; d <= daysInMonth; d++) {
//			int col = (startDay + d - 1) % 7;
//			if (d > 1 && col == 0) row++;
//
//			float x = calX + col * cellW + cellW / 2;
//			float y = calY + 50 + row * 15;
//
//			// Якщо це сьогодні — малюємо підсвітку
//			if (d == st.wDay) {
//				Gdiplus::SolidBrush bToday(Gdiplus::Color(100, 255, 255, 255));
//				g.FillRectangle(&bToday, calX + col * cellW + 2.0f, y - 1.0f, cellW - 4.0f, 14.0f);
//			}
//
//			Gdiplus::SolidBrush bNum((col >= 5) ? Gdiplus::Color(255, 255, 150, 150) : Gdiplus::Color(255, 255, 255, 255));
//			if (d == st.wDay) bNum.SetColor(Gdiplus::Color(255, 0, 0, 0)); // Чорний текст для сьогодні
//
//			CString sD; sD.Format(_T("%d"), d);
//			g.DrawString(sD, -1, &fontDays, Gdiplus::PointF(x, y), &sf, &bNum);
//		}
//	}
//}

void CClockvcmfcDlg::DrawClock(Gdiplus::Graphics& g)
{
	float w = (float)m_nPanelWidth;
	float h = (float)m_nPanelHeight;

	g.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
	g.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAliasGridFit);

	// 1. Фон панелі
	DrawPanelBackground(g, w, h);

	// 2. Аналоговий годинник (завжди зверху, y=75)
	DrawAnalogClock(g, w / 2.0f, 75.0f, 67.0f);

	float currentY = 150.0f; // Початкова точка під аналоговим годинником

	// 3. Цифровий годинник
	if (m_bShowDigital) {
		DrawDigitalClock(g, w / 2.0f, currentY);
		currentY += 50.0f;
	}

	// 4. Календар
	if (m_bShowCalendar) {
		DrawCalendar(g, w, currentY);
		currentY += 140.0f;
	}

	if (m_bShowSysMon) {
		DrawSystemMonitor(g, w, currentY);
		currentY += 80.0f;
	}
}

void CClockvcmfcDlg::DrawPanelBackground(Gdiplus::Graphics& g, float w, float h)
{
	Gdiplus::GraphicsPath path;
	float cornerR = 15.0f;
	path.AddArc(0.0f, 0.0f, cornerR, cornerR, 180.0f, 90.0f);
	path.AddArc(w - cornerR, 0.0f, cornerR, cornerR, 270.0f, 90.0f);
	path.AddArc(w - cornerR, h - cornerR, cornerR, cornerR, 0.0f, 90.0f);
	path.AddArc(0.0f, h - cornerR, cornerR, cornerR, 90.0f, 90.0f);
	path.CloseFigure();

	Gdiplus::SolidBrush panelBrush(Gdiplus::Color(160, 20, 20, 20));
	g.FillPath(&panelBrush, &path);

	Gdiplus::Pen glassPen(Gdiplus::Color(80, 255, 255, 255), 1.0f);
	g.DrawPath(&glassPen, &path);
}

void CClockvcmfcDlg::DrawAnalogClock(Gdiplus::Graphics& g, float xCenter, float yCenter, float radius)
{
	const float PI = 3.1415926535f;
	float borderThickness = 6.0f;

	if (!m_bTransparent) {
		Gdiplus::SolidBrush faceBrush(Gdiplus::Color(255, 242, 238, 225));
		g.FillEllipse(&faceBrush, xCenter - radius, yCenter - radius, radius * 2.0f, radius * 2.0f);
	}

	if (m_bBorder) {
		Gdiplus::RectF penRect(xCenter - radius, yCenter - radius, radius * 2.0f, radius * 2.0f);
		float inset = borderThickness / 2.0f;
		penRect.Inflate(-inset, -inset);
		Gdiplus::Pen pBlack(Gdiplus::Color::Black, borderThickness);
		Gdiplus::Pen pGray(Gdiplus::Color::Gray, 2.0f);
		g.DrawEllipse(&pBlack, penRect);
		g.DrawEllipse(&pGray, penRect);
	}

	float innerRadius = radius - borderThickness - 1.5f;

	// Поділки
	Gdiplus::Pen penHour(Gdiplus::Color::Black, 2.0f);
	Gdiplus::Pen penQuarter(Gdiplus::Color::Black, 4.0f);
	Gdiplus::SolidBrush brushBlack(Gdiplus::Color::Black);
	Gdiplus::SolidBrush brushFace(Gdiplus::Color(255, 242, 238, 225));

	for (int i = 0; i < 60; i++) {
		float angle = i * PI / 30.0f - PI / 2.0f;
		float cosA = cosf(angle);
		float sinA = sinf(angle);
		if (i % 5 == 0) {
			float len = (i % 15 == 0) ? innerRadius * 0.22f : innerRadius * 0.15f;
			Gdiplus::Pen* p = (i % 15 == 0) ? &penQuarter : &penHour;
			g.DrawLine(p, xCenter + cosA * (innerRadius - len), yCenter + sinA * (innerRadius - len),
				xCenter + cosA * (innerRadius + 3.0f), yCenter + sinA * (innerRadius + 3.0f));
			g.FillEllipse(&brushFace, xCenter + cosA * (innerRadius - len) - 1.5f, yCenter + sinA * (innerRadius - len) - 1.5f, 3.0f, 3.0f);
		}
		else {
			g.FillEllipse(&brushBlack, xCenter + cosA * (innerRadius + 1.5f) - 1.3f, yCenter + sinA * (innerRadius + 1.5f) - 1.3f, 2.6f, 2.6f);
		}
	}

	SYSTEMTIME st;
	if (m_bGMT) ::GetSystemTime(&st); else ::GetLocalTime(&st);
	COleDateTime now(st);

	// Текст
	Gdiplus::FontFamily fontFamily(L"Arial");
	Gdiplus::StringFormat sf;
	sf.SetAlignment(Gdiplus::StringAlignmentCenter);
	sf.SetLineAlignment(Gdiplus::StringAlignmentCenter);

	Gdiplus::Font fontLN(&fontFamily, innerRadius * 0.2f, Gdiplus::FontStyleItalic | Gdiplus::FontStyleUnderline);
	g.DrawString(L"LN", -1, &fontLN, Gdiplus::PointF(xCenter, yCenter - innerRadius * 0.52f), &sf, &Gdiplus::SolidBrush(Gdiplus::Color(255, 240, 128, 128)));

	Gdiplus::Font fontText(&fontFamily, innerRadius * 0.11f, Gdiplus::FontStyleBold);
	Gdiplus::SolidBrush bGray(Gdiplus::Color::Gray);
	g.DrawString(L"C++", -1, &fontText, Gdiplus::PointF(xCenter, yCenter + 16.0f - innerRadius * 0.52f), &sf, &bGray);

	float yDelta = 5.0f;
	if (m_bDay) {
		CString strDay = now.Format(_T("%a")); strDay.MakeUpper();
		bool isWeekend = (now.GetDayOfWeek() == 1 || now.GetDayOfWeek() == 7);
		Gdiplus::SolidBrush bDay(isWeekend ? Gdiplus::Color(255, 240, 128, 128) : Gdiplus::Color::Gray);
		g.DrawString(strDay, -1, &fontText, Gdiplus::PointF(xCenter, yCenter + yDelta + innerRadius * 0.12f), &sf, &bDay);
	}
	if (m_bDate) {
		g.DrawString(now.Format(_T("%d-%m-%y")), -1, &fontText, Gdiplus::PointF(xCenter, yCenter + yDelta + innerRadius * 0.35f), &sf, &bGray);
	}
	if (m_bGMT) {
		g.DrawString(L"GMT", -1, &fontText, Gdiplus::PointF(xCenter, yCenter + yDelta + innerRadius * 0.58f), &sf, &bGray);
	}

	// Стрілки
	float fSeconds = m_bSmooth ? (st.wSecond + st.wMilliseconds / 1000.0f) : (float)st.wSecond;
	float fMinutes = st.wMinute + fSeconds / 60.0f;
	float fHours = (st.wHour % 12 + fMinutes / 60.0f) * 5.0f;

	DrawHandHelper(g, xCenter, yCenter, fHours, innerRadius * 0.58f, 6.5f, true);
	DrawHandHelper(g, xCenter, yCenter, fMinutes, innerRadius * 0.85f, 4.5f, true);

	float sAngle = fSeconds * PI / 30.0f - PI / 2.0f;
	Gdiplus::Pen pSec(Gdiplus::Color::Red, 1.5f);
	g.DrawLine(&pSec, xCenter - cosf(sAngle) * (innerRadius * 0.15f), yCenter - sinf(sAngle) * (innerRadius * 0.15f),
		xCenter + cosf(sAngle) * (innerRadius * 0.95f), yCenter + sinf(sAngle) * (innerRadius * 0.95f));

	g.FillEllipse(&brushBlack, xCenter - 4.0f, yCenter - 4.0f, 8.0f, 8.0f);
}

void CClockvcmfcDlg::DrawHandHelper(Gdiplus::Graphics& g, float xCenter, float yCenter, float val, float len, float width, bool hasWhiteLine)
{
	const float PI = 3.1415926535f;
	float a = val * PI / 30.0f - PI / 2.0f;
	float x = xCenter + cosf(a) * len;
	float y = yCenter + sinf(a) * len;

	Gdiplus::Pen pBlack(Gdiplus::Color::Black, width);
	pBlack.SetStartCap(Gdiplus::LineCapRound);
	pBlack.SetEndCap(Gdiplus::LineCapRound);
	g.DrawLine(&pBlack, xCenter, yCenter, x, y);

	if (hasWhiteLine) {
		Gdiplus::Pen pWhite(Gdiplus::Color::White, width / 2.2f);
		pWhite.SetStartCap(Gdiplus::LineCapRound);
		pWhite.SetEndCap(Gdiplus::LineCapRound);
		g.DrawLine(&pWhite, xCenter, yCenter, x, y);
	}
}

void CClockvcmfcDlg::DrawDigitalClock(Gdiplus::Graphics& g, float xCenter, float yStart)
{
	SYSTEMTIME st;
	if (m_bGMT) ::GetSystemTime(&st); else ::GetLocalTime(&st);

	Gdiplus::FontFamily digFamily;
	int numFound = 0;
	m_fontCollection.GetFamilies(1, &digFamily, &numFound);

	if (numFound > 0) {
		float lcdW = 110.0f, lcdH = 36.0f;
		float lcdX = xCenter - (lcdW / 2.0f), lcdY = yStart + 4.0f;

		Gdiplus::SolidBrush lcdBackBrush(Gdiplus::Color(255, 170, 185, 165));
		Gdiplus::GraphicsPath lcdPath;
		float r = 5.0f;
		lcdPath.AddArc(lcdX, lcdY, r, r, 180, 90);
		lcdPath.AddArc(lcdX + lcdW - r, lcdY, r, r, 270, 90);
		lcdPath.AddArc(lcdX + lcdW - r, lcdY + lcdH - r, r, r, 0, 90);
		lcdPath.AddArc(lcdX, lcdY + lcdH - r, r, r, 90, 90);
		lcdPath.CloseFigure();
		g.FillPath(&lcdBackBrush, &lcdPath);
		g.DrawPath(&Gdiplus::Pen(Gdiplus::Color(100, 0, 0, 0), 1.0f), &lcdPath);

		Gdiplus::Font digFont(&digFamily, 26, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
		Gdiplus::StringFormat sfCenter, sfLeft, sfRight;
		sfCenter.SetAlignment(Gdiplus::StringAlignmentCenter); sfCenter.SetLineAlignment(Gdiplus::StringAlignmentCenter);
		sfLeft.SetAlignment(Gdiplus::StringAlignmentNear); sfLeft.SetLineAlignment(Gdiplus::StringAlignmentCenter);
		sfRight.SetAlignment(Gdiplus::StringAlignmentFar); sfRight.SetLineAlignment(Gdiplus::StringAlignmentCenter);

		float textY = lcdY + (lcdH / 2.0f) + 2.0f;
		float baseMid = xCenter + 2.0f;

		// Малюємо тіні "88:88:88" та активний час (використовуй свою логіку posX_...)
		Gdiplus::SolidBrush shadowBrush(Gdiplus::Color(25, 0, 0, 0));
		Gdiplus::SolidBrush digBrush(Gdiplus::Color(255, 0, 0, 0));

		float pM = baseMid, pC1 = baseMid - 13.0f, pC2 = baseMid + 13.0f, pH = baseMid - 16.0f, pS = baseMid + 16.0f;

		g.DrawString(L"88", -1, &digFont, Gdiplus::PointF(pH, textY), &sfRight, &shadowBrush);
		g.DrawString(L":", -1, &digFont, Gdiplus::PointF(pC1, textY), &sfCenter, &shadowBrush);
		// ... і так далі для всіх сегментів ...

		CString sH, sM, sS;
		sH.Format(_T("%d"), st.wHour); sM.Format(_T("%02d"), st.wMinute); sS.Format(_T("%02d"), st.wSecond);
		g.DrawString(sH, -1, &digFont, Gdiplus::PointF(pH, textY), &sfRight, &digBrush);
		g.DrawString(L":", -1, &digFont, Gdiplus::PointF(pC1, textY), &sfCenter, &digBrush);
		g.DrawString(sM, -1, &digFont, Gdiplus::PointF(pM, textY), &sfCenter, &digBrush);
		g.DrawString(L":", -1, &digFont, Gdiplus::PointF(pC2, textY), &sfCenter, &digBrush);
		g.DrawString(sS, -1, &digFont, Gdiplus::PointF(pS, textY), &sfLeft, &digBrush);
	}
}

void CClockvcmfcDlg::DrawCalendar(Gdiplus::Graphics& g, float w, float yStart)
{
	float calY = yStart + 5.0f;
	float calX = 10.0f, calW = w - 20.0f;

	// Розділювач
	g.DrawLine(&Gdiplus::Pen(Gdiplus::Color(50, 0, 0, 0), 1.0f), 15.0f, calY, w - 15.0f, calY);
	g.DrawLine(&Gdiplus::Pen(Gdiplus::Color(30, 255, 255, 255), 1.0f), 15.0f, calY + 1.0f, w - 15.0f, calY + 1.0f);

	SYSTEMTIME st; GetLocalTime(&st);
	COleDateTime today(st);
	COleDateTime firstDay(st.wYear, st.wMonth, 1, 0, 0, 0);
	int startDay = firstDay.GetDayOfWeek(); startDay = (startDay == 1) ? 6 : startDay - 2;

	int daysInMonth = 31;
	if (st.wMonth == 4 || st.wMonth == 6 || st.wMonth == 9 || st.wMonth == 11) daysInMonth = 30;
	else if (st.wMonth == 2) daysInMonth = ((st.wYear % 4 == 0 && st.wYear % 100 != 0) || (st.wYear % 400 == 0)) ? 29 : 28;

	Gdiplus::FontFamily arial(L"Arial");
	Gdiplus::Font fontHeader(&arial, 12, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
	Gdiplus::StringFormat sf; sf.SetAlignment(Gdiplus::StringAlignmentCenter);
	g.DrawString(today.Format(_T("%B %Y")), -1, &fontHeader, Gdiplus::PointF(w / 2.0f, calY + 10), &sf, &Gdiplus::SolidBrush(Gdiplus::Color(220, 255, 255, 255)));

	Gdiplus::Font fontDays(&arial, 10, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	const TCHAR* dayNames[] = { _T("M"), _T("T"), _T("W"), _T("T"), _T("F"), _T("S"), _T("S") };
	float cellW = calW / 7.0f;

	for (int i = 0; i < 7; i++) {
		Gdiplus::SolidBrush bDayName((i >= 5) ? Gdiplus::Color(200, 255, 100, 100) : Gdiplus::Color(150, 255, 255, 255));
		g.DrawString(dayNames[i], -1, &fontDays, Gdiplus::PointF(calX + i * cellW + cellW / 2, calY + 30), &sf, &bDayName);
	}

	int row = 0;
	for (int d = 1; d <= daysInMonth; d++) {
		int col = (startDay + d - 1) % 7;
		if (d > 1 && col == 0) row++;
		float x = calX + col * cellW + cellW / 2, y = calY + 50 + row * 15;
		if (d == st.wDay) g.FillRectangle(&Gdiplus::SolidBrush(Gdiplus::Color(100, 255, 255, 255)), calX + col * cellW + 2.0f, y - 1.0f, cellW - 4.0f, 14.0f);
		Gdiplus::SolidBrush bNum((col >= 5) ? Gdiplus::Color(255, 255, 150, 150) : Gdiplus::Color(255, 255, 255, 255));
		if (d == st.wDay) bNum.SetColor(Gdiplus::Color(255, 0, 0, 0));
		CString sD; sD.Format(_T("%d"), d);
		g.DrawString(sD, -1, &fontDays, Gdiplus::PointF(x, y), &sf, &bNum);
	}
}

void CClockvcmfcDlg::DrawSystemMonitor(Gdiplus::Graphics& g, float w, float yStart)
{
	float monY = yStart + 5.0f;
	float margin = 15.0f;
	float barW = w - (margin * 2.0f);
	float barH = 12.0f;

	// Розділювач
	g.DrawLine(&Gdiplus::Pen(Gdiplus::Color(50, 0, 0, 0), 1.0f), 15.0f, monY, w - 15.0f, monY);
	g.DrawLine(&Gdiplus::Pen(Gdiplus::Color(30, 255, 255, 255), 1.0f), 15.0f, monY + 1.0f, w - 15.0f, monY + 1.0f);

	Gdiplus::FontFamily arial(L"Arial");
	Gdiplus::Font fontLabel(&arial, 10, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
	Gdiplus::Font fontValue(&arial, 9, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	Gdiplus::SolidBrush bWhite(Gdiplus::Color(200, 255, 255, 255));
	Gdiplus::StringFormat sfLeft, sfRight;
	sfRight.SetAlignment(Gdiplus::StringAlignmentFar);

	auto DrawBar = [&](float y, const TCHAR* label, float percent, Gdiplus::Color color) {
		// 1. Текст зліва (Назва модуля)
		g.DrawString(label, -1, &fontLabel, Gdiplus::PointF(margin, y), &bWhite);

		// 2. Текст справа (Відсотки)
		CString sVal;
		sVal.Format(_T("%.0f%%"), percent);
		g.DrawString(sVal, -1, &fontValue, Gdiplus::PointF(w - margin, y + 1.0f), &sfRight, &bWhite);

		// 3. Фон смужки (вдавлене ложе)
		Gdiplus::RectF barRect(margin, y + 14.0f, barW, barH);

		// Малюємо дуже темний фон підкладки
		Gdiplus::SolidBrush bgBrush(Gdiplus::Color(100, 0, 0, 0));
		g.FillRectangle(&bgBrush, barRect);

		// Тінь зверху всередині (ефект вдавлювання)
		Gdiplus::Pen innerShadow(Gdiplus::Color(80, 0, 0, 0), 1.0f);
		g.DrawLine(&innerShadow, margin, y + 14.0f, margin + barW, y + 14.0f);

		// Зовнішня світла рамка (ледь помітна)
		Gdiplus::Pen borderPen(Gdiplus::Color(50, 255, 255, 255), 1.0f);
		g.DrawRectangle(&borderPen, barRect);

		// 4. Заповнення (Progress)
		if (percent > 0.0f) {
			float fillW = (barW * percent) / 100.0f;
			if (fillW > barW) fillW = barW; // Обмежувач
			if (fillW < 2.0f) fillW = 2.0f; // Мінімальна видимість

			Gdiplus::RectF fillRect(margin + 1.0f, y + 15.0f, fillW - 2.0f, barH - 2.0f);

			// Створюємо градієнт: основний колір -> темніший відтінок
			Gdiplus::LinearGradientBrush grad(fillRect, color, Gdiplus::Color(180, 0, 0, 0), Gdiplus::LinearGradientModeVertical);

			// Додаємо "глянцевий" ефект через налаштування блендингу градієнта
			float factors[] = { 0.0f, 0.8f, 1.0f };
			float positions[] = { 0.0f, 0.3f, 1.0f };
			grad.SetBlend(factors, positions, 3);

			g.FillRectangle(&grad, fillRect);

			// Світлий відблиск зверху на самій смужці заповнення
			Gdiplus::Pen highlight(Gdiplus::Color(120, 255, 255, 255), 1.0f);
			g.DrawLine(&highlight, margin + 2.0f, y + 15.0f, margin + fillW - 2.0f, y + 15.0f);
		}
	};

	Gdiplus::Color cpuColor = (m_cpuUsage > 80.0f) ? Gdiplus::Color(200, 255, 50, 50) :
							  (m_cpuUsage > 50.0f) ? Gdiplus::Color(200, 255, 150, 0) :
		                                             Gdiplus::Color(200, 100, 255, 100);

	// 2. Малюємо смужку CPU
	DrawBar(monY + 10.0f, _T("CPU"), m_cpuUsage, cpuColor);

	// 3. Малюємо смужку RAM (завжди блакитна)
	DrawBar(monY + 40.0f, _T("RAM"), m_ramUsage, Gdiplus::Color(200, 100, 150, 255));
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
		if (m_bGMT) 
			::GetSystemTime(&st); 
		else 
			::GetLocalTime(&st);

		m_sysMonTickCount++;

		if (m_sysMonTickCount >= 15) // Кожні 3 секунди
		{
			UpdateSystemMetrics();
			m_sysMonTickCount = 0; // Скидаємо лічильник
		}

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
	mciSendString(_T("close all"), NULL, 0, NULL);
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
	
	WritePrivateProfileString(_T("Settings"), _T("chkCalendar"), m_bShowCalendar ? _T("1") : _T("0"), strPath);

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
	m_bShowCalendar = GetPrivateProfileInt(_T("Settings"), _T("chkCalendar"), 1, strPath);


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
	if (count == 0) 
		count = 12;

	CString fullPath = GetSoundPath(_T("_Boom.wav"));

	// Передаємо копію шляху, щоб уникнути проблем із доступом
	std::thread([this, fullPath, count]()
	{
		// 1. Відкриваємо файл ОДИН РАЗ для всієї серії
		mciSendString(_T("close hours"), NULL, 0, NULL);
		CString openCmd;
		openCmd.Format(_T("open \"%s\" alias hours"), (LPCTSTR)fullPath);
		mciSendString(openCmd, NULL, 0, NULL);

		for (int i = 0; i < count; i++)
		{
			// 2. Граємо з початку (from 0)
			mciSendString(_T("play hours from 0"), NULL, 0, NULL);

			Sleep(200); // Даємо час почати

			int timeout = 0;
			while (IsPlayingMCI(_T("hours")) && timeout < 60) 
			{
				Sleep(100);
				timeout++;
			}
			Sleep(300); // Пауза між ударами
		}

		// 3. ВАЖЛИВО: Закриваємо файл після завершення всіх ударів
		// Це звільнить той самий буфер у 2.2 МБ
		mciSendString(_T("close hours"), NULL, 0, NULL);

	}).detach();
}

void CClockvcmfcDlg::UpdateTransparency()
{
	UpdateLayeredClock();
}

void CClockvcmfcDlg::UpdateLayeredClock()
{
	// 1. Розрахунок динамічної висоти
	// 150px - зона аналогового годинника
	// 50px - зона цифрового годинника
	int newHeight = 150;
	if (m_bShowDigital) 
		newHeight += 50;
	
	if (m_bShowCalendar) 
		newHeight += 140; // Додаємо 140px під календар

	if (m_bShowSysMon) 
		newHeight += 80; // Додаємо 80px під монітор
	
	m_nPanelHeight = newHeight;

	// Оновлюємо розмір вікна
	SetWindowPos(NULL, 0, 0, m_nPanelWidth, m_nPanelHeight, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

	CRect rect;
	GetWindowRect(&rect);
	CSize size(rect.Width(), rect.Height());
	CPoint ptSrc(0, 0);
	CPoint ptDest(rect.left, rect.top);

	HDC hdcScreen = ::GetDC(NULL);
	HDC hMemDC = ::CreateCompatibleDC(hdcScreen);

	BITMAPINFO bmi = { 0 };
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
	g.Clear(Gdiplus::Color(0, 0, 0, 0)); // ПОВНА ПРОЗОРІСТЬ ОСНОВИ

	DrawClock(g); // Малюємо наш годинник та панель

	BLENDFUNCTION blend = { AC_SRC_OVER, 0, (BYTE)((255 * m_nOpacity) / 100), AC_SRC_ALPHA };
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
	// 1. На випадок, якщо цей аліас ще відкритий — закриваємо
	mciSendString(_T("close ") + alias, NULL, 0, NULL);

	// 2. Відкриваємо та запускаємо
	CString cmd;
	cmd.Format(_T("open \"%s\" alias %s"), (LPCTSTR)fileName, (LPCTSTR)alias);

	if (mciSendString(cmd, NULL, 0, NULL) == 0)
	{
		mciSendString(_T("play ") + alias, NULL, 0, NULL);

		// 3. Запускаємо фоновий потік для очищення пам'яті
		std::thread([alias]() 
		{
			Sleep(1000); // Даємо звуку почати грати

			TCHAR res[128];
			CString statusCmd = _T("status ") + alias + _T(" mode");

			// Чекаємо, поки статус зміниться з "playing" на щось інше
			while (true) 
			{
				mciSendString(statusCmd, res, 128, NULL);
				if (_tcsicmp(res, _T("playing")) != 0) break;
				Sleep(500); // Перевіряємо двічі на секунду
			}

			// 4. ЗВІЛЬНЯЄМО ПАМ'ЯТЬ
			mciSendString(_T("close ") + alias, NULL, 0, NULL);
		}).detach();
	}
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

void CClockvcmfcDlg::UpdateSystemMetrics()
{
	// --- 1. РОЗРАХУНОК CPU ---
	FILETIME idleTime, kernelTime, userTime;
	if (GetSystemTimes(&idleTime, &kernelTime, &userTime))
	{
		auto FileTimeToQuad = [](FILETIME ft) {
			return ((((ULONGLONG)ft.dwHighDateTime) << 32) | ft.dwLowDateTime);
			};

		ULONGLONG idle = FileTimeToQuad(idleTime) - FileTimeToQuad(m_prevIdleTime);
		ULONGLONG kernel = FileTimeToQuad(kernelTime) - FileTimeToQuad(m_prevKernelTime);
		ULONGLONG user = FileTimeToQuad(userTime) - FileTimeToQuad(m_prevUserTime);
		ULONGLONG total = kernel + user;

		if (total > 0)
			m_cpuUsage = (float)(total - idle) * 100.0f / total;

		m_prevIdleTime = idleTime;
		m_prevKernelTime = kernelTime;
		m_prevUserTime = userTime;
	}

	// --- 2. РОЗРАХУНОК RAM ---
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	if (GlobalMemoryStatusEx(&memInfo))
	{
		m_ramUsage = (float)memInfo.dwMemoryLoad;
	}
}