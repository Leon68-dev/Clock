#include "pch.h" // Або "pch.h" у нових версіях VS
#include "Clock_vc_mfc.h" // Назва вашого головного хедеру
#include "AboutDlg.h"

// Для роботи з реєстром (щоб дізнатися версію Windows)
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

// ---------------------------------------------------------
// Логіка завантаження (аналог FAbout_Load)
// ---------------------------------------------------------
BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 1. Версія (Hardcoded, як у вашому прикладі)
	CString strVer = _T("Clock Version 1.0.0");
	SetDlgItemText(IDC_STATIC_VER, strVer);

	// 2. Copyright (Динамічний рік)
	COleDateTime now = COleDateTime::GetCurrentTime();
	CString strCopy;
	strCopy.Format(_T("Copyright (C) 2004-%d"), now.GetYear());
	SetDlgItemText(IDC_STATIC_COPY, strCopy);

	// 3. Версія Windows (Читаємо з реєстру, бо це надійніше для відображення назви "Pro/Home")
	CString strWinVer = GetWindowsVersionString();
	SetDlgItemText(IDC_STATIC_WINVER, strWinVer);

	// 4. Пам'ять (GlobalMemoryStatusEx)
	MEMORYSTATUSEX memStatus;
	memStatus.dwLength = sizeof(memStatus);

	if (::GlobalMemoryStatusEx(&memStatus))
	{
		// Переводимо байти в ГБ (ділимо на 1024^3)
		double totalPhysGB = (double)memStatus.ullTotalPhys / (1024.0 * 1024.0 * 1024.0);
		double availPhysGB = (double)memStatus.ullAvailPhys / (1024.0 * 1024.0 * 1024.0);

		CString strMem;
		strMem.Format(_T("Total Physical Memory: %.2f GB\nAvailable Physical Memory: %.2f GB"),
			totalPhysGB, availPhysGB);

		SetDlgItemText(IDC_STATIC_MEM, strMem);
	}

	return TRUE;
}

CString CAboutDlg::GetWindowsVersionString()
{
	// Спроба прочитати "ProductName" з реєстру (наприклад, "Windows 10 Pro")
	CRegKey key;
	CString strProductName = _T("Windows (Unknown)");

	if (key.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion"), KEY_READ) == ERROR_SUCCESS)
	{
		TCHAR szBuffer[256];
		ULONG nChars = 256;
		if (key.QueryStringValue(_T("ProductName"), szBuffer, &nChars) == ERROR_SUCCESS)
		{
			strProductName = szBuffer;
		}
	}
	return strProductName;
}