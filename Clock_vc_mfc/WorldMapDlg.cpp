#include "pch.h" // або "stdafx.h" у старих проєктах
#include "Clock_vc_mfc.h" // Назва вашого головного файлу проєкту
#include "WorldMapDlg.h"
#include "afxdialogex.h"
#include <cmath>

IMPLEMENT_DYNAMIC(CWorldMapDlg, CDialogEx)

CWorldMapDlg::CWorldMapDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_WORLD_MAP, pParent)
{
}

CWorldMapDlg::~CWorldMapDlg()
{
    if (m_pMapImage) {
        delete m_pMapImage;
        m_pMapImage = nullptr;
    }
}

void CWorldMapDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWorldMapDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_TIMER()
    ON_WM_DESTROY()
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

BOOL CWorldMapDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    SetWindowText(_T("World Day/Night Map"));

    // 1. Встановлюємо розмір вікна 1000x500 (клієнтська область)
    CRect rc(0, 0, 1000, 500);
    CalcWindowRect(&rc);
    SetWindowPos(NULL, 0, 0, rc.Width(), rc.Height(), SWP_NOMOVE | SWP_NOZORDER);

    CenterWindow(GetDesktopWindow());

    // 2. Завантажуємо карту з ресурсів
    // IDR_WORLD_MAP - це ID вашого JPG, lpszType - "IMAGE"
    m_pMapImage = LoadImageFromResource(IDR_WORLD_MAP, _T("IMAGE"));

    if (!m_pMapImage) {
        AfxMessageBox(_T("Помилка: Не вдалося завантажити карту з ресурсів!"));
    }

    // 3. Таймер оновлення (раз на хвилину)
    SetTimer(1, 60000, NULL);

    return TRUE;
}

void CWorldMapDlg::OnPaint()
{
    CPaintDC dc(this); // Контекст пристрою для малювання
    if (!m_pMapImage) return;

    CRect clientRect;
    GetClientRect(&clientRect);
    int w = clientRect.Width();
    int h = clientRect.Height();

    // 1. Створюємо буфер у пам'яті (Bitmap) розміром з вікно
    Gdiplus::Bitmap backBuffer(w, h, PixelFormat32bppARGB);
    Gdiplus::Graphics gMemory(&backBuffer); // Малюємо в пам'ять

    // Налаштування якості для буфера
    gMemory.SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);
    gMemory.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);

    // --- ПОЧАТОК МАЛЮВАННЯ В БУФЕР ---

    // 2. Малюємо карту світу
    gMemory.DrawImage(m_pMapImage, 0.0f, 0.0f, (float)w, (float)h);

    // 3. Розрахунок Сонця та Тіні (UTC)
    SYSTEMTIME st;
    GetSystemTime(&st);
    int daysInMonth[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };
    double dayOfYear = daysInMonth[st.wMonth - 1] + st.wDay;
    const double PI = 3.14159265358979323846;
    double sunLat = 23.44 * sin(2.0 * PI * (dayOfYear - 81.0) / 365.25);
    double sunLon = (12.0 - (st.wHour + st.wMinute / 60.0 + st.wSecond / 3600.0)) * 15.0;

    // 4. Побудова лінії термінатора
    Gdiplus::GraphicsPath path;
    std::vector<Gdiplus::PointF> points;
    for (float x = 0; x <= w; x += 2)
    {
        double lon = (x / w) * 360.0 - 180.0;
        double latRad = atan(-cos((lon - sunLon) * PI / 180.0) / tan(sunLat * PI / 180.0));
        double lat = latRad * 180.0 / PI;
        points.push_back(Gdiplus::PointF(x, (float)((90.0 - lat) / 180.0 * h)));
    }

    if (sunLat > 0) {
        points.push_back(Gdiplus::PointF((float)w, (float)h));
        points.push_back(Gdiplus::PointF(0.0f, (float)h));
    }
    else {
        points.push_back(Gdiplus::PointF((float)w, 0.0f));
        points.push_back(Gdiplus::PointF(0.0f, 0.0f));
    }
    path.AddPolygon(points.data(), (int)points.size());

    // 5. Малюємо тінь у буфер
    Gdiplus::SolidBrush shadowBrush(Gdiplus::Color(215, 5, 5, 20));
    gMemory.FillPath(&shadowBrush, &path);

    // 6. Малюємо Сонце у буфер
    Gdiplus::SolidBrush sunBrush(Gdiplus::Color::Yellow);
    float sx = (float)((sunLon + 180.0) / 360.0 * w);
    float sy = (float)((90.0 - sunLat) / 180.0 * h);
    gMemory.FillEllipse(&sunBrush, sx - 4.0f, sy - 4.0f, 8.0f, 8.0f);

    // --- КІНЕЦЬ МАЛЮВАННЯ В БУФЕР ---

    // 7. Копіюємо готовий буфер на реальний екран за один виклик
    Gdiplus::Graphics gScreen(dc.GetSafeHdc());
    gScreen.DrawImage(&backBuffer, 0, 0);
}

// Функція завантаження JPG з ресурсів
Gdiplus::Image* CWorldMapDlg::LoadImageFromResource(UINT nID, LPCTSTR lpszType)
{
    HMODULE hInst = AfxGetResourceHandle();
    HRSRC hRsrc = ::FindResource(hInst, MAKEINTRESOURCE(nID), lpszType);
    if (!hRsrc) return nullptr;

    DWORD dwSize = ::SizeofResource(hInst, hRsrc);
    LPVOID lpRes = ::LockResource(::LoadResource(hInst, hRsrc));
    if (!lpRes) return nullptr;

    HGLOBAL hGlobal = ::GlobalAlloc(GMEM_MOVEABLE, dwSize);
    if (!hGlobal) return nullptr;

    void* pData = ::GlobalLock(hGlobal);
    memcpy(pData, lpRes, dwSize);
    ::GlobalUnlock(hGlobal);

    IStream* pStream = nullptr;
    if (::CreateStreamOnHGlobal(hGlobal, TRUE, &pStream) == S_OK) {
        return Gdiplus::Image::FromStream(pStream);
    }
    return nullptr;
}

void CWorldMapDlg::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent == 1) Invalidate(FALSE); // Перемалювати без очищення фону
    CDialogEx::OnTimer(nIDEvent);
}

void CWorldMapDlg::OnDestroy()
{
    CDialogEx::OnDestroy();
    KillTimer(1);
}

void CWorldMapDlg::OnCancel()
{
    // Для немодального вікна замість EndDialog треба викликати DestroyWindow
    DestroyWindow();
}

BOOL CWorldMapDlg::OnEraseBkgnd(CDC* pDC)
{
    return TRUE; // Кажемо системі, що ми самі все намалюємо
}