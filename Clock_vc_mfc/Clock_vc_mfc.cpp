#include "pch.h"
#include "framework.h"
#include "Clock_vc_mfc.h"
#include "Clock_vc_mfcDlg.h"
#include <memory>

#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CClockvcmfcApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

CClockvcmfcApp::CClockvcmfcApp()
{
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
}

CClockvcmfcApp theApp;

// File-local token for GDI+ initialization
static ULONG_PTR s_gdiplusToken = 0;

BOOL CClockvcmfcApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);

	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	GdiplusStartupInput gdiplusStartupInput;
	if (GdiplusStartup(&s_gdiplusToken, &gdiplusStartupInput, NULL) != Gdiplus::Ok)
	{
		TRACE(traceAppMsg, 0, "Error: GdiplusStartup failed.\n");
		return FALSE;
	}

	AfxEnableControlContainer();

	// Use smart pointer to manage shell manager lifecycle safely
	std::unique_ptr<CShellManager> pShellManager = std::make_unique<CShellManager>();

	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CClockvcmfcDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{


	}
	else if (nResponse == IDCANCEL)
	{


	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	pShellManager.reset();

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	GdiplusShutdown(s_gdiplusToken);

	return FALSE;
}