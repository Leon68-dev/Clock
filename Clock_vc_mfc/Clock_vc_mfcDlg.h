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

	// --- Налаштування годинника (змінні) ---
	BOOL m_bGMT;
	BOOL m_bDate;
	BOOL m_bDay;
	BOOL m_bMoving;
	BOOL m_bTopMost;
	BOOL m_bTransparent;
	BOOL m_bBorder;
	BOOL m_bSound;
	int  m_nOpacity;
	BOOL m_bAlreadyExecuted;

	// --- Налаштування вимкнення ПК ---
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

	// --- Робота з INI-файлом (Збереження/Завантаження) ---
	CString GetIniPath();
	void SaveSettings();
	void LoadSettings();

	BOOL SetShutdownPrivilege();
	void ExecuteShutdown();

	CString GetSoundPath(CString fileName);
	void PlaySoundFile(CString fileName);
	void PlayHourlyChime(int hours);

	void UpdateTransparency();
	void UpdateLayeredClock();

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC); // Для запобігання мерехтінню
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg LRESULT OnTrayNotify(WPARAM wParam, LPARAM lParam);

	// Обробники команд меню
	afx_msg void OnMenuSetup();
	afx_msg void OnMenuAbout();
	afx_msg void OnMenuCalendar();
	afx_msg void OnMenuShutdown();
	afx_msg void OnMenuExit();
	afx_msg void OnMenuHide();          // Приховати/Відкрити
	afx_msg void OnMenuStartPosition(); // Повернути в кут

	DECLARE_MESSAGE_MAP()
};