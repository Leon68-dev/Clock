#if !defined(AFX_STATICCOLOR_H__93973619_5EED_4951_8586_1CDA7227FA54__INCLUDED_)
#define AFX_STATICCOLOR_H__93973619_5EED_4951_8586_1CDA7227FA54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// staticcolor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStaticColor window

class CStaticColor : public CStatic
{
// Construction
public:
	CStaticColor();
	void SetTextColor(COLORREF crTextColor);
	void SetBkColor(COLORREF crTextColor);
// Attributes
public:

private:
	COLORREF m_crTextColor;
	COLORREF m_crBkColor;
	CBrush m_brBkgnd;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticColor)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStaticColor();

	// Generated message map functions
protected:
	//{{AFX_MSG(CStaticColor)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATICCOLOR_H__93973619_5EED_4951_8586_1CDA7227FA54__INCLUDED_)
