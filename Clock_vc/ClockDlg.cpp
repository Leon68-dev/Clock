// ClockDlg.cpp : implementation file
//
//
/*********************************************************************************************
* Версия 1.4.0.0
	В меню добавлен CheckBox при пререключении времени.
	Передача <времени отключения> без файла на диске, через переменную.
* Версия 1.5.0.0
	В окне "О программе" определяется версия операционки и общее количество памяти.
	Выходные меняют цвет.
* Версия 1.6.0.0
	Бой часов.
* Версия 1.6.1.0
	Основное окно -> модальное 
*********************************************************************************************/


#include "stdafx.h"
#include "Clock.h"
#include "ClockDlg.h"
#include "ExitDlg.h"
#include "CalendarDlg.h"

/////////////////////////////////////////////////////////////////////////////
#include <windows.h>  // main Windows header
#include <windowsx.h> // message cracker macros, etc.
#include <shellapi.h> // Shell32 api
#include <winbase.h>
#include <atlbase.h>
#include <mmsystem.h>
/////////////////////////////////////////////////////////////////////////////

#pragma comment(lib,"winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define WM_MYICONNOTIFY				    WM_USER+1

const int _sizeFont1 = 22;
const int _sizeFont2 = 15;
const int _sizeFont3 = 14;

CFont fontTime, fontDate, fontDay;

HINSTANCE ghInst;

CString winVer()
{

	_MEMORYSTATUS _tmpMem;
    _tmpMem.dwLength = sizeof(_tmpMem);
	GlobalMemoryStatus(&_tmpMem);

    OSVERSIONINFO OV;
	OV.dwOSVersionInfoSize = sizeof(OV);
	GetVersionEx(&OV);
	
	int c_dwMajorVersion   = OV.dwMajorVersion;
	int c_dwMinorVersion   = OV.dwMinorVersion;
	int c_dwBuildNumber    = OV.dwBuildNumber;
	CString c_szCSDVersion = OV.szCSDVersion;
	
	CString  ver, tmp;
	ver = "Microsoft Windows ";

/*----------------------------------------------------------------------------------------
*	Конвертация int->CString
*	char buffer[16];
*	tmp = _gcvt(c_dwMajorVersion, 8, buffer);
*	tmp.Format("%s%d", tmp, c_dwMajorVersion);
----------------------------------------------------------------------------------------*/
	
	tmp = "";
	tmp.Format("%s%d", tmp, c_dwMajorVersion);
	ver += tmp;
	
	tmp = "";
	tmp.Format("%s%d", tmp, c_dwMinorVersion);
	ver += "." + tmp + " (Build ";

	tmp = "";
	tmp.Format("%s%d", tmp, c_dwBuildNumber);
	ver += tmp;

	tmp = " " + c_szCSDVersion + ")";
	ver += tmp;
	
	//tmp = "\nPhysical memory available: ";
	//ver += tmp;

	//tmp = "";
	//tmp.Format("%s%d", tmp, (_tmpMem.dwTotalPhys / 1024));
	//

	//ver += tmp;
	//tmp = " KB";
	//ver += tmp;

	return(ver);

/*    
	if (OV.dwPlatformId == VER_PLATFORM_WIN32_NT)             // Windows NT
    {
    	return("Microsoft Windows NT " + IntToStr(OV.dwMajorVersion) + "." +
        	IntToStr(OV.dwMinorVersion) +" (Build " + OV.dwBuildNumber + ": " +
            OV.szCSDVersion +")");
	}
    else if ((OV.dwPlatformId == VER_PLATFORM_WIN32s))        // Win32s
	{
    	return("Microsoft Win32s " + IntToStr(OV.dwMajorVersion) + "." +
        	IntToStr(OV.dwMinorVersion));
    }
	else         // Windows 95 -- No build numbers provided
    {
		return("Microsoft Windows 9x " + IntToStr(OV.dwMajorVersion) + "." +
        IntToStr(OV.dwMinorVersion));
	}
*/
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

// Dialog Data
    //{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CStatic	m_CStatVer;
	//}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAboutDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    //{{AFX_MSG(CAboutDlg)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
    //{{AFX_DATA_INIT(CAboutDlg)
    //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_STATICVER, m_CStatVer);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
    //{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClockDlg dialog

CClockDlg::CClockDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CClockDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CClockDlg)
	//}}AFX_DATA_INIT
    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
}

void CClockDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CClockDlg)
	DDX_Control(pDX, IDC_STATIC2, m_static2);
	DDX_Control(pDX, IDC_STATIC3, m_static3);
	DDX_Control(pDX, IDC_STATIC1, m_static1);
	//}}AFX_DATA_MAP
//
//запуск таймера
//
    m_TimerID = SetTimer(1, 1000, NULL);
}

BEGIN_MESSAGE_MAP(CClockDlg, CDialog)
    //{{AFX_MSG_MAP(CClockDlg)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_TIMER()
    ON_WM_DESTROY()
    ON_UPDATE_COMMAND_UI(ID_GMT, OnUpdateGmt)
    ON_COMMAND(ID_GMT, OnGmt)
    ON_COMMAND(ID_TIMEEXIT, OnTimeExit)
    ON_COMMAND(ID_ABOUTBOX, OnAboutbox)
	ON_COMMAND(ID_CALENDAR, OnOpenCalendar)
	ON_UPDATE_COMMAND_UI(ID_CALENDAR, OnUpdateCalendar)
	ON_WM_SHOWWINDOW()
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	ON_MESSAGE(WM_MYICONNOTIFY,OnIcon)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClockDlg message handlers

BOOL CClockDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Add "About..." menu item to system menu.
    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }
    
    // Set the icon for this dialog.  The framework does this automatically
    // when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);         // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon
	
    // TODO: Add extra initialization here
    setFont();
	
	trayView  = true;
	typeTime  = true;
	canBoom   = false;   
	countBoom = 0;
	tckTck    = true;

	bool aa = true;
	tickTack(aa);
	setSysTray();	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}
//------------------------------------------------------------------------

void CClockDlg::setFont()
{
//
//  время
	setTypeFont(logfont1, szFont1, _sizeFont1, fontTime, FW_BOLD);
//
//  дата
	setTypeFont(logfont2, szFont2, _sizeFont2, fontDate, FW_NORMAL);
//
//	день  
    setTypeFont(logfont3, szFont3, _sizeFont3, fontDay, FW_BOLD);

	m_static1.SetFont(&fontTime);
	m_static2.SetFont(&fontDate);
	m_static3.SetFont(&fontDay);

    CTime  time = CTime::GetCurrentTime();
	
	
/*
	PromptText1().SetFont(&fontTime);
	PromptText2().SetFont(&fontDate);
	PromptText3().SetFont(&fontDay);
*/

/**************************************************************************************

  //CFont *myFont=new CFont;
	myFont->CreateFont(14,							// nHeight
						0,							// nWidth
						0,							// nEscapement
						0,							// nOrientation
						FW_BOLD,					// nWeight
						FALSE,						// bItalic
						FALSE,						// bUnderline
						0,							// cStrikeOut
						ANSI_CHARSET,				// nCharSet
						OUT_DEFAULT_PRECIS,			// nOutPrecision
						CLIP_DEFAULT_PRECIS,		// nClipPrecision
						DEFAULT_QUALITY,			// nQuality
						DEFAULT_PITCH | FF_SWISS,	// nPitchAndFamily
						"Arial");
	//Устанавливаем шрифт
	m_static3.SetFont(myFont);
**************************************************************************************/
/*
	// вывод времени и даты
    PromptText1().SetWindowText(time.Format("%X")) ;
    PromptText2().SetWindowText(time.Format("%d-%m-%Y"));   
    PromptText3().SetWindowText(time.Format("%A"));   
*/	

	setTimeCtrl(time,  0);
	setColorCtrl(time, 0);
	
}
//------------------------------------------------------------------------

void CClockDlg::setTypeFont(LOGFONT lgfont, CString & szFnt, int szFont, CFont &fnt, int nWeight)
{	
	memset(&lgfont, 0, sizeof(lgfont));
    lgfont.lfHeight = szFont;
	lgfont.lfWeight = nWeight;						//FW_BOLD;
	szFnt.LoadString(IDS_FONT_NAME);				// TrueType font
    lstrcpy(lgfont.lfFaceName, szFnt);
    VERIFY(fnt.CreateFontIndirect(&lgfont));
}
//------------------------------------------------------------------------

void CClockDlg::setColorCtrl(CTime & _time, short type)
{
	//Saturday-Суббота
	//Sunday-Воскресенье
	//type = 1 -> Гринвич    
	if(type == 0) 
	{
		m_static3.SetTextColor(RGB(0,0,0));
		if(_time.Format("%w") == "6") 
		{
			m_static3.SetTextColor(RGB(0,0,255));  
		}
		else if(_time.Format("%w") == "0")
		{
			m_static3.SetTextColor(RGB(255,0,0));
		}
		else
		{
			m_static3.SetTextColor(RGB(0,0,0));
		}
	}
	else
	{
		if(_time.FormatGmt("%w") == "6") 
		{
			m_static3.SetTextColor(RGB(0,0,255));  
		}
		else if(_time.FormatGmt("%w") == "0")
		{
			m_static3.SetTextColor(RGB(255,0,0));
		}	
		else
		{
			m_static3.SetTextColor(RGB(0,0,0));
		}	
	}

	//m_static1.SetBkColor(RGB(128,128,128));
}
//------------------------------------------------------------------------

void CClockDlg::setTimeCtrl(CTime & _time, short type)
{
	if(type == 0)
	{
		m_static1.SetWindowText(_time.Format("%X")) ;
		m_static2.SetWindowText(_time.Format("%d-%m-%Y"));   
		m_static3.SetWindowText(_time.Format("%A"));   
	}
	else
	{
		m_static1.SetWindowText(_time.FormatGmt("%X")) ;
		m_static2.SetWindowText(_time.FormatGmt("%d-%m-%Y"));   
		m_static3.SetWindowText(_time.FormatGmt("%A"));   
	}
}
//------------------------------------------------------------------------

void CClockDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialog::OnSysCommand(nID, lParam);
    }
}
//------------------------------------------------------------------------

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClockDlg::OnPaint()
{
    if (IsIconic())
    {
         // device context for painting
        CPaintDC dc(this);
        SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClockDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}

//------------------------------------------------------------------------
//
// Вывод времени
//
void CClockDlg::OnTimer(UINT nIDEvent)
{
    // TODO: Add your message handler code here and/or call default
	tickTack(tckTck);	
    
	CDialog::OnTimer(nIDEvent);
    CTime time = CTime::GetCurrentTime();
//
// Установка шрифтов
//
    m_static1.SetFont(&fontTime);
	m_static2.SetFont(&fontDate);
	m_static3.SetFont(&fontDay);

  // вывод времени
    if(typeTime == true)
    {
		setTimeCtrl(time, 0);		
		setColorCtrl(time, 0);
	}
    else
    {
		setTimeCtrl(time, 1);		
		setColorCtrl(time, 1);
	}

	boom(time.Format("%M"), time.Format("%S"));
/*  	
	if(time.Format("%M") == "15" && time.Format("%S") == "00")
	{
		mciSendString("play 15.wav", NULL, 0, NULL);
    }


	if(time.Format("%M") == "30" && time.Format("%S") == "00")
	{
		mciSendString("play 30.wav", NULL, 0, NULL);
    }
	

	if(time.Format("%M") == "45" && time.Format("%S") == "00")
	{
		mciSendString("play 15.wav", NULL, 0, NULL);
    }
*/
    
	if(time.Format("%M") == "00" && time.Format("%S") == "00")
    {
		canBoom = true;
    }
	
	boom(canBoom, time.Format("%I"));	


//
// Выход из операционки -> SHUTDOWN
//
    if(time.Format("%X") == timeExit)
    {
        #define WIN32S  0x80000000l   
        HANDLE hToken;
        TOKEN_PRIVILEGES tkp;
        
        if (!(GetVersion() & WIN32S)) 
        {
            //OutputDebugString("Setting token");

            // Running on NT so need to change privileges
            if (!OpenProcessToken(GetCurrentProcess(),
                TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)){   }

            // Get the LUID for shutdown privilege
            LookupPrivilegeValue(NULL, TEXT("SeShutdownPrivilege"), 
                &tkp.Privileges[0].Luid);
            tkp.PrivilegeCount = 1;  // one privilege to set
            tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
            
            // Get shutdown privilege for this process.
            if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, 
                (PTOKEN_PRIVILEGES)NULL, 0)){   }
        }
        ExitWindowsEx( EWX_SHUTDOWN|EWX_FORCE, 0); 
    }
	
}
//------------------------------------------------------------------------

void CClockDlg::OnDestroy()
{
    CDialog::OnDestroy();
    // TODO: Add your message handler code here
}
//------------------------------------------------------------------------

void CClockDlg::OnUpdateGmt( CCmdUI* pCmdUI )
{
    // TODO: Add your command update UI handler code here
    if( typeTime != false )
    {
        typeTime = false;
		MessageBox("Greenwich time", "Clock");
    }
    else
    {
        typeTime = true;
		MessageBox("Local time", "Clock");
    }
}
//------------------------------------------------------------------------

void CClockDlg::OnGmt()
{
    // TODO: Add your command handler code here
	CMenu* cm=GetMenu();
	if (cm->GetMenuState(ID_GMT,MF_BYCOMMAND) & MF_CHECKED)
		cm->CheckMenuItem(ID_GMT,MF_UNCHECKED); 
	else
		cm->CheckMenuItem(ID_GMT,MF_CHECKED);
}
//------------------------------------------------------------------------

void CClockDlg::OnTimeExit() 
{
    // TODO: Add your command handler code here
    CExitDlg dlg;
    //dlg.m_timeExit = timeExit;

    int nResponse = dlg.DoModal();

    if (nResponse == IDOK)
    {
        // TODO: Place code here to handle when the dialog is
        //  dismissed with OK
        timeExit = dlg.m_timeExit;
        //timeExit = timeExit + ":00";
        dlg.DestroyWindow();
    }
    else if (nResponse == IDCANCEL)
    {
        // TODO: Place code here to handle when the dialog is
        //  dismissed with Cancel
        timeExit = dlg.m_timeExit;
		return;
    }
}
//------------------------------------------------------------------------

void CClockDlg::OnAboutbox() 
{
    // TODO: Add your command handler code here
    CAboutDlg adlg;
    adlg.DoModal();
}
//------------------------------------------------------------------------

void CClockDlg::OnOpenCalendar() 
{
	// TODO: Add your command handler code here
    CCalendarDlg cdlg;
	cdlg.DoModal();
}
//------------------------------------------------------------------------

void CClockDlg::OnUpdateCalendar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
}
//------------------------------------------------------------------------

void CClockDlg::setSysTray() 
{
	NOTIFYICONDATA nf;
	nf.hWnd = m_hWnd;
	nf.uID = NULL;
	
	nf.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nf.uCallbackMessage = WM_MYICONNOTIFY;
	strcpy(nf.szTip,"Clock");

	HICON hIcon;
	hIcon=AfxGetApp()->LoadIcon(IDI_ICONCLOCK);
	nf.hIcon = hIcon;
	Shell_NotifyIcon(NIM_ADD,&nf);
}
//------------------------------------------------------------------------

void CClockDlg::destroyTray()
{
	NOTIFYICONDATA nf;
	nf.hWnd = m_hWnd;
	nf.uID = NULL;
	nf.uFlags = NIF_ICON;
	nf.uCallbackMessage = NULL;
	nf.hIcon = NULL;
	Shell_NotifyIcon(NIM_DELETE,&nf);
}
//------------------------------------------------------------------------

LRESULT CClockDlg::OnIcon(WPARAM wp, LPARAM lp)
{
	POINT pt;
	HMENU hmenu, hpopup;

	if (lp==WM_LBUTTONDBLCLK ) 
	{		
	
		if(trayView == true)
		{
			trayView = false;
			ShowWindow(SW_RESTORE);
		}
		else
		{
			trayView = true;
			ShowWindow(SW_HIDE);
		}
	}

	if (lp==WM_RBUTTONDOWN) 
	{
		GetCursorPos(&pt);
		hmenu = LoadMenu(ghInst,MAKEINTRESOURCE(IDR_MENUClock));
        hpopup = GetSubMenu(hmenu, 0);
		::SetForegroundWindow(m_hWnd);
		TrackPopupMenuEx(hpopup,TPM_HORIZONTAL|TPM_LEFTALIGN,pt.x, pt.y,m_hWnd,NULL);
	}          
	
    DestroyMenu(hmenu);					// Delete loaded menu and reclaim its resources
	::PostMessage(m_hWnd, WM_USER, 0, 0);

	return 1;
}
//------------------------------------------------------------------------

void CClockDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	// TODO: Add your message handler code here

}
//------------------------------------------------------------------------

BOOL CClockDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	destroyTray();
	
	return CDialog::DestroyWindow();
}
//------------------------------------------------------------------------


void CAboutDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	m_CStatVer.SetWindowText(winVer());		
}
//------------------------------------------------------------------------

void CClockDlg::boom(bool & a, CString b)	
{
	if(a)
	{
		if(countBoom==(atoi(b)*4)) 
		{
			a = false;
			countBoom = 0;	
		}
		else
		{		
			mciSendString("play boom.wav", NULL, 0, NULL);
			countBoom++;  
		}
	}
}
//------------------------------------------------------------------------

void CClockDlg::boom(CString a, CString b)
{
	if((a == "15" || a == "45") && b == "00")
	{
		mciSendString("play 15.wav", NULL, 0, NULL);
    }
	else if(a == "30" && b == "00")
	{
		mciSendString("play 30.wav", NULL, 0, NULL);
    }
}

void CClockDlg::tickTack(bool & a)
{
	if(a) 
	{
		mciSendString("play TickTack.wav", NULL, 0, NULL);
		a = false;
	}
	else
	{
		a = true;
	}
}
//------------------------------------------------------------------------

void CClockDlg::OnAppExit() 
{
    DestroyWindow();
}

void CClockDlg::OnClose() 
{
	//AfxMessageBox("Exit");
	trayView = true	;
	CDialog::OnClose(); 
	//DestroyWindow();
}
