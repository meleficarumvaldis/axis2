// GeneralTab.cpp : implementation file
//

#include "stdafx.h"
#include "Axis2.h"
#include "GeneralTab.h"
#include "Axis2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGeneralTab property page

IMPLEMENT_DYNCREATE(CGeneralTab, CPropertyPage)

CGeneralTab::CGeneralTab() : CPropertyPage(CGeneralTab::IDD)
{
	//{{AFX_DATA_INIT(CGeneralTab)
	//}}AFX_DATA_INIT
}

CGeneralTab::~CGeneralTab()
{
}

void CGeneralTab::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGeneralTab)
	DDX_Control(pDX, IDC_CLIENT, m_Client);
	DDX_Control(pDX, IDC_PROFILE, m_Profile);
	DDX_Control(pDX, IDC_MULFILES, m_MulFiles);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGeneralTab, CPropertyPage)
	//{{AFX_MSG_MAP(CGeneralTab)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGeneralTab message handlers

BOOL CGeneralTab::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	// TODO: Add extra initialization here
	m_dcPropertyPage = ((CAxis2App*)AfxGetApp())->m_pcppGeneralTab;

	if (m_dcCurrentPage == this)
		((CAxis2App*)AfxGetApp())->m_pcppGeneralTab->m_dcCurrentPage = this;

	m_Client.SetWindowText(csUOPath);
	m_Profile.SetWindowText(csProfilePath);
	m_MulFiles.SetWindowText(csMulPath);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CGeneralTab::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	// TODO: Return a different brush if the default is not desired
	return ((CAxis2App*)AfxGetApp())->m_bkbrush;
}