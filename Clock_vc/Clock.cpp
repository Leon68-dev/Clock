// Clock.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Clock.h"
#include "ClockDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const char *NamedMutex = "ClockVC";
HANDLE CheckInstance(const char *Name)
{
    HANDLE Mutex = CreateMutex(NULL, true, Name);
    int er = GetLastError();
    if(er) return 0;
    return Mutex;
}

/////////////////////////////////////////////////////////////////////////////
// CClockApp

BEGIN_MESSAGE_MAP(CClockApp, CWinApp)
	//{{AFX_MSG_MAP(CClockApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClockApp construction

CClockApp::CClockApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CClockApp object

CClockApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CClockApp initialization

BOOL CClockApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	
    HANDLE Mutex = CheckInstance(NamedMutex);
    if(!Mutex)
    {
        MessageBox(NULL,"Programm is runing!", "Warning", MB_OK|MB_ICONWARNING);
        ReleaseMutex(Mutex);
        return 1;
    }

	/*
	CClockDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	*/

	CClockDlg* dlg;
	dlg = new CClockDlg;
	m_pMainWnd = dlg;
	dlg->Create(IDDClock_DIALOG);
	dlg->ShowWindow(SW_HIDE);

	return TRUE;
}
