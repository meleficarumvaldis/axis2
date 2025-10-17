// Settings_Travel.cpp : implementation file
//

#include "stdafx.h"
#include "Axis2.h"
#include "Settings_Travel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingsTravel property page

IMPLEMENT_DYNCREATE(CSettingsTravel, CPropertyPage)

CSettingsTravel::CSettingsTravel() : CPropertyPage(CSettingsTravel::IDD)
{
	//{{AFX_DATA_INIT(CSettingsTravel)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT}


CSettingsTravel::~CSettingsTravel()
{
}

void CSettingsTravel::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingsTravel)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingsTravel, CPropertyPage)
	//{{AFX_MSG_MAP(CSettingsTravel)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingsTravel message handlers

HBRUSH CSettingsTravel::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	// TODO: Return a different brush if the default is not desired
	return ((CAxis2App*)AfxGetApp())->m_bkbrush;
}