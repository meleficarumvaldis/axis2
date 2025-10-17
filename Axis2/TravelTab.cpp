// TravelTab.cpp : implementation file
//

#include "stdafx.h"
#include "Axis2.h"
#include "TravelTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTravelTab property page

IMPLEMENT_DYNCREATE(CTravelTab, CPropertyPage)

CTravelTab::CTravelTab() : CPropertyPage(CTravelTab::IDD)
{
	//{{AFX_DATA_INIT(CTravelTab)
	m_csX = _T("");
	m_csY = _T("");
	m_csZ = _T("");
	m_iMap = -1;
	//}}AFX_DATA_INIT}

CTravelTab::~CTravelTab()
{
}

void CTravelTab::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTravelTab)
	DDX_Control(pDX, IDC_MAP, m_Map);
	DDX_Control(pDX, IDC_Z, m_Z);
	DDX_Control(pDX, IDC_Y, m_Y);
	DDX_Control(pDX, IDC_X, m_X);
	DDX_Text(pDX, IDC_X, m_csX);
	DDX_Text(pDX, IDC_Y, m_csY);
	DDX_Text(pDX, IDC_Z, m_csZ);
	DDX_CBIndex(pDX, IDC_MAP, m_iMap);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTravelTab, CPropertyPage)
	//{{AFX_MSG_MAP(CTravelTab)
	ON_BN_CLICKED(IDC_GO, OnGo)
	ON_BN_CLICKED(IDC_RECALL, OnRecall)
	ON_BN_CLICKED(IDC_GATE, OnGate)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTravelTab message handlers

void CTravelTab::OnGo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CString csCommand;
	csCommand.Format("%sgo %s %s %s %d", ((CAxis2App*)AfxGetApp())->m_csCommandPrefix, m_csX, m_csY, m_csZ, m_iMap);
	
	if (((CAxis2App*)AfxGetApp())->m_pRConsole)
		((CAxis2App*)AfxGetApp())->m_pRConsole->Send(csCommand);
}

void CTravelTab::OnRecall()
{
	// TODO: Add your control notification handler code here
	
}

void CTravelTab::OnGate()
{
	// TODO: Add your control notification handler code here
	
}

BOOL CTravelTab::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO: Add extra initialization here
	m_dcPropertyPage = ((CAxis2App*)AfxGetApp())->m_pcppTravelTab;

	if (m_dcCurrentPage == this)
		((CAxis2App*)AfxGetApp())->m_pcppTravelTab->m_dcCurrentPage = this;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CTravelTab::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	// TODO: Return a different brush if the default is not desired
	return ((CAxis2App*)AfxGetApp())->m_bkbrush;
}