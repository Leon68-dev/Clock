// ClockDlg.h : header file
//

#if !defined(AFX_ClockDLG_H__BA28C1C7_FF30_11D2_A088_008048D9775E__INCLUDED_)
#define AFX_ClockDLG_H__BA28C1C7_FF30_11D2_A088_008048D9775E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "staticcolor.h"

/////////////////////////////////////////////////////////////////////////////
// CClockDlg dialog

class CClockDlg : public CDialog
{
// Construction
public:
	CClockDlg(CWnd* pParent = NULL);	// standard constructor
	
// Dialog Data
	//{{AFX_DATA(CClockDlg)
	enum { IDD = IDDClock_DIALOG };
	CStaticColor	m_static2;
	CStaticColor	m_static3;
	CStaticColor	m_static1;
	CMenu pMenu;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClockDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	HICON m_hIcon;
	
	UINT m_nIDColor;        // last color command
	COLORREF m_clrText;

	bool typeTime;
	UINT m_TimerID;

	CString timeExit;
	LOGFONT logfont1, logfont2, logfont3;
	CString szFont1, szFont2, szFont3;
/*
	CStatic&    PromptText1()    // prompt area
				{ return *(CStatic*)GetDlgItem(IDC_STATIC1); }
	CStatic&    PromptText2()    // prompt area
				{ return *(CStatic*)GetDlgItem(IDC_STATIC2); }
	CStatic&    PromptText3()    // prompt area
				{ return *(CStatic*)GetDlgItem(IDC_STATIC3); }
*/
	bool trayView;
	bool canBoom;
	int  countBoom;
	bool tckTck;

	void setSysTray(); 
	void destroyTray();
	//void OnIcon(WPARAM wp, LPARAM lp);
	LRESULT OnIcon(WPARAM wp, LPARAM lp);
	void setFont();	
	void setColorCtrl(CTime & _time, short type);
	void setTimeCtrl(CTime & _time, short type);
	void setTypeFont(LOGFONT _logfont, CString & _szFont, int _sizeFont, CFont &fnt, int nWeight);
	void boom(bool & a, CString b);
	void tickTack(bool & a);
	void boom(CString a, CString b);

	// Generated message map functions
	//{{AFX_MSG(CClockDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnUpdateGmt(CCmdUI* pCmdUI);
	afx_msg void OnGmt();
	afx_msg void OnTimeExit();
	afx_msg void OnAboutbox();
	afx_msg void OnOpenCalendar();
	afx_msg void OnUpdateCalendar(CCmdUI* pCmdUI);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnAppExit();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ClockDLG_H__BA28C1C7_FF30_11D2_A088_008048D9775E__INCLUDED_)
