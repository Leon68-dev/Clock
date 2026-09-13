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

	SetDlgItemText(IDC_STATIC_VER, _T("Clock Version 2.3.0.8"));

	COleDateTime now = COleDateTime::GetCurrentTime();
	CString strCopy;
	strCopy.Format(_T("Copyright (C) 1998-%d"), now.GetYear());
	SetDlgItemText(IDC_STATIC_COPY, strCopy);

	SetDlgItemText(IDC_STATIC_WINVER, GetWindowsVersionString());

	MEMORYSTATUSEX memStatus;
	memStatus.dwLength = sizeof(memStatus);

	if (::GlobalMemoryStatusEx(&memStatus))
	{
		// Format memory with fractional precision rather than truncated integers
		double totalGB = (double)memStatus.ullTotalPhys / (1024.0 * 1024.0 * 1024.0);
		double availGB = (double)memStatus.ullAvailPhys / (1024.0 * 1024.0 * 1024.0);

		CString strTotal, strAvail;
		strTotal.Format(_T("Total Physical Memory: %.1f GB"), totalGB);
		strAvail.Format(_T("Available Physical Memory: %.1f GB"), availGB);

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

		if (key.QueryStringValue(_T("ProductName"), szBuffer, &nChars) == ERROR_SUCCESS)
			strProductName = szBuffer;

		nChars = 256;
		if (key.QueryStringValue(_T("DisplayVersion"), szBuffer, &nChars) == ERROR_SUCCESS)
			strDisplayVersion = szBuffer;

		nChars = 256;
		if (key.QueryStringValue(_T("CurrentBuild"), szBuffer, &nChars) == ERROR_SUCCESS)
			strBuild = szBuffer;

		// Correct product name for Windows 11 (Build >= 22000 still reports Windows 10 in registry)
		int nBuildNumber = _ttoi(strBuild);
		if (nBuildNumber >= 22000)
		{
			strProductName.Replace(_T("Windows 10"), _T("Windows 11"));
		}

		// Query Update Build Revision (UBR) if available
		DWORD dwUBR = 0;
		if (key.QueryDWORDValue(_T("UBR"), dwUBR) == ERROR_SUCCESS)
		{
			strBuild.AppendFormat(_T(".%u"), dwUBR);
		}
	}

	CString strResult;

	if (!strDisplayVersion.IsEmpty())
	{
		strResult.Format(_T("Microsoft %s %s (Build %s)"), (LPCTSTR)strProductName, (LPCTSTR)strDisplayVersion, (LPCTSTR)strBuild);
	}
	else
	{
		strResult.Format(_T("Microsoft %s (Build %s)"), (LPCTSTR)strProductName, (LPCTSTR)strBuild);
	}

	return strResult;
}