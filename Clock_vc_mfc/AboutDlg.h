#pragma once

#include "afxdialogex.h"

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	virtual BOOL OnInitDialog(); // Головна функція ініціалізації

	// Допоміжна функція для отримання назви Windows з реєстру
	CString GetWindowsVersionString();

	DECLARE_MESSAGE_MAP()
};
