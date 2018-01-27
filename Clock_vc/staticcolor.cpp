// staticcolor.cpp : implementation file
//

#include "stdafx.h"
#include "staticcolor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStaticColor

CStaticColor::CStaticColor()
{
	// Set default foreground text
	m_crTextColor = ::GetSysColor(COLOR_BTNTEXT);
		// Set default background text
	m_crBkColor = ::GetSysColor(COLOR_BTNFACE);

	// Set default background brush
	m_brBkgnd.CreateSolidBrush(m_crBkColor);
}

CStaticColor::~CStaticColor()
{
}


BEGIN_MESSAGE_MAP(CStaticColor, CStatic)
	//{{AFX_MSG_MAP(CStaticColor)
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaticColor message handlers


HBRUSH CStaticColor::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	pDC->SetTextColor(m_crTextColor);
		
	pDC->SetBkColor(m_crBkColor);

    return (HBRUSH)m_brBkgnd;
	// TODO: Return a non-NULL brush if the parent's handler should not be called
	//return NULL;
}

void CStaticColor::SetTextColor(COLORREF crTextColor)
{
	// Set new foreground color
	if (crTextColor != 0xffffffff)
	{
		m_crTextColor = crTextColor;
	}
	else // Set default foreground color
	{
		m_crTextColor = ::GetSysColor(COLOR_BTNTEXT);
	}

	// Repaint control
	Invalidate();
} // End of SetTextColor


void CStaticColor::SetBkColor(COLORREF crTextColor)
{
	// Set new foreground color
	if (m_crBkColor != 0xffffffff)
	{
		m_crBkColor = crTextColor;
	}
	else // Set default foreground color
	{
		m_crBkColor = ::GetSysColor(COLOR_BTNTEXT);
	}

	// Repaint control
	Invalidate();
} // End of SetTextColor



