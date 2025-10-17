// Settings_Item.cpp : implementation file
//

#include "stdafx.h"
#include "Axis2.h"
#include "Settings_Item.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingsItem property page

IMPLEMENT_DYNCREATE(CSettingsItem, CPropertyPage)

CSettingsItem::CSettingsItem() : CPropertyPage(CSettingsItem::IDD)
{
	//{{AFX_DATA_INIT(CSettingsItem)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT}


CSettingsItem::~CSettingsItem()
{
}

void CSettingsItem::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingsItem)
	DDX_Control(pDX, IDC_ITEMBGCOLOR, m_ItemBGColor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingsItem, CPropertyPage)
	//{{AFX_MSG_MAP(CSettingsItem)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingsItem message handlers

HBRUSH CSettingsItem::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	// TODO: Return a different brush if the default is not desired
	return ((CAxis2App*)AfxGetApp())->m_bkbrush;
}

BOOL CSettingsItem::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO: Add extra initialization here
	m_ItemBGColor.SetColor(((CAxis2App*)AfxGetApp())->m_dwItemBGColor);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CSettingsItem::OnApply()
{
	// TODO: Add specialized code here and/or call the base class
	((CAxis2App*)AfxGetApp())->m_dwItemBGColor = m_ItemBGColor.GetColor();
	((CAxis2App*)AfxGetApp())->PutRegistryDword("ItemBGColor", ((CAxis2App*)AfxGetApp())->m_dwItemBGColor);

	return CPropertyPage::OnApply();
}