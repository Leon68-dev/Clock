#pragma once
#include <afxdialogex.h>
#include <gdiplus.h>
#include <vector>

class CWorldMapDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CWorldMapDlg)

public:
    CWorldMapDlg(CWnd* pParent = nullptr);   // стандартний конструктор
    virtual ~CWorldMapDlg();
    virtual void OnCancel() override;

    // Дані діалогового вікна
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_WORLD_MAP }; // Переконайтеся, що IDD_WORLD_MAP створено в Resource View
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // підтримка DDX/DDV
    virtual BOOL OnInitDialog();

    // Обробники повідомлень
    afx_msg void OnPaint();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnDestroy();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    DECLARE_MESSAGE_MAP()

private:
    Gdiplus::Image* m_pMapImage = nullptr;

    // Допоміжні методи
    Gdiplus::Image* LoadImageFromResource(UINT nID, LPCTSTR lpszType);
    void DrawDayNightMap(Gdiplus::Graphics& g);
};