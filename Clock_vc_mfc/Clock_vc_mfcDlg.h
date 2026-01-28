#pragma once

// CClockvcmfcDlg dialog
class CClockvcmfcDlg : public CDialogEx
{
	// Construction
public:
	CClockvcmfcDlg(CWnd* pParent = nullptr);	// standard constructor

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLOCK_VC_MFC_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


	// Implementation
protected:
	HICON m_hIcon;

	// --- Змінні для налаштувань годинника ---
	BOOL m_bGMT;
	BOOL m_bDate;
	BOOL m_bDay;
	BOOL m_bMoving;
	BOOL m_bTopMost;
	BOOL m_bTransparent;
	BOOL m_bBorder;
	BOOL m_bSound;
	int  m_nOpacity;

	// --- Змінні для вимкнення ПК ---
	BOOL m_isShutDown;
	BOOL m_isSleep;
	COleDateTime m_timeShutDown;

	// --- Системний трей ---
	NOTIFYICONDATA m_nid;
	void InitTrayIcon();

	// --- Малювання (GDI+) ---
	void DrawClock(Gdiplus::Graphics& g);
	int ClcX(int sec, int size, int xCenter);
	int ClcY(int sec, int size, int yCenter);

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg LRESULT OnTrayNotify(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	// Обробники меню
	afx_msg void OnMenuSetup();
	afx_msg void OnMenuAbout();
	afx_msg void OnMenuCalendar();
	afx_msg void OnMenuShutdown();
	afx_msg void OnMenuExit();
	afx_msg void OnMenuStartPosition();
	afx_msg void OnMenuHide();

	DECLARE_MESSAGE_MAP()
};