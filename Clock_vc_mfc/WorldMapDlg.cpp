#include "pch.h" 
#include "Clock_vc_mfc.h" 
#include "WorldMapDlg.h"
#include "afxdialogex.h"
#include <cmath>

IMPLEMENT_DYNAMIC(CWorldMapDlg, CDialogEx)

CWorldMapDlg::CWorldMapDlg(CWnd* pParent )
    : CDialogEx(IDD_WORLD_MAP, pParent){ }

CWorldMapDlg::~CWorldMapDlg()
{
    if (m_pMapImage != nullptr)
    {
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

    
    CRect rc(0, 0, 1000, 500);
    CalcWindowRect(&rc);
    SetWindowPos(NULL, 0, 0, rc.Width(), rc.Height(), SWP_NOMOVE | SWP_NOZORDER);

    CenterWindow(GetDesktopWindow());

    
    
    m_pMapImage = LoadImageFromResource(IDR_WORLD_MAP, _T("IMAGE"));

    if (!m_pMapImage) {
        AfxMessageBox(_T("E!"));
    }

    
    SetTimer(1, 60000, NULL);

    return TRUE;
}

void CWorldMapDlg::OnPaint()
{
    CPaintDC dc(this);
    if (!m_pMapImage) return;


    CRect clientRect;
    GetClientRect(&clientRect);
    int w = clientRect.Width();
    int h = clientRect.Height();

    if (w <= 0 || h <= 0) return;


    Gdiplus::Bitmap backBuffer(w, h, PixelFormat32bppARGB);
    Gdiplus::Graphics gMemory(&backBuffer);


    gMemory.SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);
    gMemory.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);

    // Delegate rendering to dedicated day/night drawing method
    DrawDayNightMap(gMemory, w, h);


    Gdiplus::Graphics gScreen(dc.GetSafeHdc());
    gScreen.DrawImage(&backBuffer, 0, 0);
}

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
    if (!pData)
    {
        ::GlobalFree(hGlobal);
        return nullptr;
    }
    memcpy(pData, lpRes, dwSize);
    ::GlobalUnlock(hGlobal);

    IStream* pStream = nullptr;

    if (::CreateStreamOnHGlobal(hGlobal, TRUE, &pStream) != S_OK)
    {
        ::GlobalFree(hGlobal);
        return nullptr;
    }

    Gdiplus::Image* pImg = Gdiplus::Image::FromStream(pStream);
    Gdiplus::Bitmap* pResultBitmap = nullptr;

    // Detach from the stream by cloning so the stream can be safely released
    if (pImg && pImg->GetLastStatus() == Gdiplus::Ok)
    {
        pResultBitmap = static_cast<Gdiplus::Bitmap*>(pImg)->Clone(
            0, 0, pImg->GetWidth(), pImg->GetHeight(), PixelFormat32bppARGB);
        delete pImg;
    }


    pStream->Release();

    return pResultBitmap;
}

void CWorldMapDlg::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent == 1) Invalidate(FALSE); 
    CDialogEx::OnTimer(nIDEvent);
}

void CWorldMapDlg::OnDestroy()
{
    CDialogEx::OnDestroy();
    KillTimer(1);
}

void CWorldMapDlg::OnCancel()
{
    
    DestroyWindow();
}

BOOL CWorldMapDlg::OnEraseBkgnd(CDC* pDC)
{
    return TRUE; 
}

void CWorldMapDlg::DrawDayNightMap(Gdiplus::Graphics& g, int w, int h)
{
    if (!m_pMapImage) return;

    g.DrawImage(m_pMapImage, 0.0f, 0.0f, (float)w, (float)h);

    SYSTEMTIME st;
    GetSystemTime(&st);
    int daysInMonth[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };
    double dayOfYear = daysInMonth[st.wMonth - 1] + st.wDay;
    const double PI = 3.14159265358979323846;
    double sunLat = 23.44 * sin(2.0 * PI * (dayOfYear - 81.0) / 365.25);
    double sunLon = (12.0 - (st.wHour + st.wMinute / 60.0 + st.wSecond / 3600.0)) * 15.0;

    // Avoid division by zero during equinox when sunLat is close to 0
    double tanSunLat = tan(sunLat * PI / 180.0);
    if (fabs(tanSunLat) < 1e-6)
    {
        tanSunLat = (tanSunLat >= 0.0) ? 1e-6 : -1e-6;
    }

    Gdiplus::GraphicsPath path;
    std::vector<Gdiplus::PointF> points;
    for (float x = 0; x <= w; x += 2)
    {
        double lon = (x / w) * 360.0 - 180.0;
        double latRad = atan(-cos((lon - sunLon) * PI / 180.0) / tanSunLat);
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

    Gdiplus::SolidBrush shadowBrush(Gdiplus::Color(215, 5, 5, 20));
    g.FillPath(&shadowBrush, &path);

    Gdiplus::SolidBrush sunBrush(Gdiplus::Color::Yellow);
    float sx = (float)((sunLon + 180.0) / 360.0 * w);
    float sy = (float)((90.0 - sunLat) / 180.0 * h);
    g.FillEllipse(&sunBrush, sx - 4.0f, sy - 4.0f, 8.0f, 8.0f);
}