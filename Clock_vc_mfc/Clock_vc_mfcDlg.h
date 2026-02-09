#pragma once

class CWorldMapDlg;

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

	CWorldMapDlg* m_pMapDlg = nullptr;

	// --- Налаштування годинника (змінні) ---
	BOOL m_bGMT;
	BOOL m_bDate;
	BOOL m_bDay;
	BOOL m_bMoving;
	BOOL m_bTopMost;
	BOOL m_bTransparent;
	BOOL m_bBorder;
	int  m_nOpacity;
	BOOL m_bAlreadyExecuted;
	BOOL m_bSmooth; 
	int m_lastSecond = -1; 
	BOOL m_bHours;
	BOOL m_b1530;
	BOOL m_bTickTack;
	BOOL m_b24Hours;

	BOOL m_bMouseOver = FALSE; // Стан миші над вікном

	// Метод для малювання сірої підкладки модулів
	void DrawModulesBackground(Gdiplus::Graphics& g, float w, float yStart, float h);

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

	void PlayMCI(CString fileName, CString alias);
	void StopMCI(CString alias);
	BOOL IsPlayingMCI(CString alias);

	void UpdateTransparency();
	void UpdateLayeredClock();

	/*****************************************************************************************************************************/
	void DrawPanelBackground(Gdiplus::Graphics& g, float w, float h);
	void DrawAnalogClock(Gdiplus::Graphics& g, float x, float y, float radius);
	void DrawHandHelper(Gdiplus::Graphics& g, float xCenter, float yCenter, float val, float len, float width, bool hasWhiteLine);
	void DrawDigitalClock(Gdiplus::Graphics& g, float x, float y);
	void DrawCalendar(Gdiplus::Graphics& g, float x, float y);
	void DrawSystemMonitor(Gdiplus::Graphics& g, float x, float y); 
	void DrawPing(Gdiplus::Graphics& g, float w, float yStart);
	void DrawWeather(Gdiplus::Graphics& g, float w, float yStart);
	/*****************************************************************************************************************************/

	/*****************************************************************************************************************************/
	const int HEIGHT_DIGITAL_CLOCK = 65;
	const int HEIGHT_CALENDAR = 140; 
	const int HEIGHT_SYSMON = 80; 
	const int HEIGHT_PING = 35;
	const int HEIGHT_WEATHER = 55;

	/*****************************************************************************************************************************/

	Gdiplus::PrivateFontCollection m_fontCollection; // Для завантаження твого шрифту
	BOOL m_bDigitalClock = TRUE;   // Прапорець для цифрового годинника
	int m_nPanelWidth = 150;      // Нова ширина панелі
	int m_nPanelHeight = 150;     // Висота (буде рахуватися динамічно)

	BOOL m_bCalendar = TRUE;

	BOOL m_bSysMon = TRUE;
	float m_cpuUsage = 0.0f;
	float m_ramUsage = 0.0f;
	int m_sysMonTickCount = 0;
	FILETIME m_prevIdleTime;
	FILETIME m_prevKernelTime;
	FILETIME m_prevUserTime;
	void UpdateSystemMetrics();

	BOOL    m_bPing = TRUE;
	CString m_strPingAddress = _T("8.8.8.8");		// Дефолтний IP (Google)
	int     m_nPingValue = -1;						// -1 означає "немає відповіді"
	BOOL    m_bPingInProgress = FALSE;				// Щоб не запускати кілька потоків одночасно
	void UpdatePing();	

	BOOL    m_bWeather = FALSE;
	CString m_strWeatherCity = _T("Odesa,ua");
	CString m_strWeatherApiKey = _T("b6edfbab96459a29db1b3dab05857103");
	CString m_strTemp = _T("?°C");
	CString m_strWeatherDesc = _T("Loading...");
	Gdiplus::Image* m_pWeatherIcon = nullptr;
	int m_weatherTickCount = 0; // Для оновлення раз на 15-30 хв
	void UpdateWeather();
	Gdiplus::Image* DownloadImage(CString url); // Допоміжний метод

	Gdiplus::Color m_dynamicColor;	// Поточний колір тексту (чорний або білий)
	void UpdateThemeColor();		// Метод для аналізу яскравості фону
	void DrawSeparator(Gdiplus::Graphics& g, float w, float y);

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC); // Для запобігання мерехтінню
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg LRESULT OnTrayNotify(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);

	// Обробники команд меню
	afx_msg void OnMenuSetup();
	afx_msg void OnMenuAbout();
	afx_msg void OnMenuCalendar();
	afx_msg void OnMenuShutdown();
	afx_msg void OnMenuExit();
	afx_msg void OnMenuHide();          // Приховати/Відкрити
	afx_msg void OnMenuStartPosition(); // Повернути в кут
	afx_msg void OnMenuWorldmap();
	
	DECLARE_MESSAGE_MAP()
};