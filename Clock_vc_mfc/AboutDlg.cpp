#include "pch.h"
#include "Clock_vc_mfc.h"
#include "AboutDlg.h"
#include <atlbase.h> 

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ModifyStyleEx(0, WS_EX_LAYERED);
	SetLayeredWindowAttributes(0, 216, LWA_ALPHA);

	// 1. Версія
	SetDlgItemText(IDC_STATIC_VER, _T("Clock Version 1.0.0"));

	// 2. Copyright
	COleDateTime now = COleDateTime::GetCurrentTime();
	CString strCopy;
	strCopy.Format(_T("Copyright (C) 2004-%d"), now.GetYear());
	SetDlgItemText(IDC_STATIC_COPY, strCopy);

	// 3. ОС
	SetDlgItemText(IDC_STATIC_WINVER, GetWindowsVersionString());

	// 4. Пам'ять
	MEMORYSTATUSEX memStatus;
	memStatus.dwLength = sizeof(memStatus);

	if (::GlobalMemoryStatusEx(&memStatus))
	{
		DWORDLONG totalGB = memStatus.ullTotalPhys / (1024 * 1024 * 1024);
		DWORDLONG availGB = memStatus.ullAvailPhys / (1024 * 1024 * 1024);

		CString strTotal, strAvail;
		strTotal.Format(_T("Total Physical Memory %I64u GB"), totalGB);
		strAvail.Format(_T("Available Physical Memory %I64u GB"), availGB);

		SetDlgItemText(IDC_STATIC_TOTAL_MEM, strTotal);
		SetDlgItemText(IDC_STATIC_AVAIL_MEM, strAvail);
	}

	return TRUE;
}

CString CAboutDlg::GetWindowsVersionString()
{
	CRegKey key;
	CString strProductName = _T("Windows");
	CString strDisplayVersion = _T("");
	CString strBuild = _T("");

	if (key.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion"), KEY_READ) == ERROR_SUCCESS)
	{
		TCHAR szBuffer[256];
		ULONG nChars = 256;

		// Читаємо назву (напр. Windows 10 Pro)
		if (key.QueryStringValue(_T("ProductName"), szBuffer, &nChars) == ERROR_SUCCESS)
			strProductName = szBuffer;

		// Читаємо версію (напр. 22H2 або 10.0)
		nChars = 256;
		if (key.QueryStringValue(_T("DisplayVersion"), szBuffer, &nChars) == ERROR_SUCCESS)
			strDisplayVersion = szBuffer;

		// Читаємо номер збірки (Build)
		nChars = 256;
		if (key.QueryStringValue(_T("CurrentBuild"), szBuffer, &nChars) == ERROR_SUCCESS)
			strBuild = szBuffer;
	}

	CString strResult;
	// Форматуємо точно як у C# прикладі
	strResult.Format(_T("Microsoft %s %s.%s"), strProductName, strDisplayVersion, strBuild);
	return strResult;
}