// AccountTab.cpp : implementation file
//

#include "stdafx.h"
#include "Axis2.h"
#include "AccountTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAccountTab property page

IMPLEMENT_DYNCREATE(CAccountTab, CPropertyPage)

CAccountTab::CAccountTab() : CPropertyPage(CAccountTab::IDD)
{
	//{{AFX_DATA_INIT(CAccountTab)
	m_csPassword = _T("");
	m_csUsername = _T("");
	m_iPrivLevel = -1;
	m_iResdisp = -1;
	//}}AFX_DATA_INIT
}

CAccountTab::~CAccountTab()
{
}

void CAccountTab::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAccountTab)
	DDX_Control(pDX, IDC_PRIVLEVEL, m_PrivLevel);
	DDX_Control(pDX, IDC_RESDISP, m_Resdisp);
	DDX_Control(pDX, IDC_PASSWORD, m_Password);
	DDX_Control(pDX, IDC_USERNAME, m_Username);
	DDX_Control(pDX, IDC_TAGLIST, m_TagList);
	DDX_Control(pDX, IDC_TAG, m_Tag);
	DDX_Control(pDX, IDC_TAGVAL, m_TagVal);
	DDX_Text(pDX, IDC_PASSWORD, m_csPassword);
	DDX_Text(pDX, IDC_USERNAME, m_csUsername);
	DDX_CBIndex(pDX, IDC_PRIVLEVEL, m_iPrivLevel);
	DDX_CBIndex(pDX, IDC_RESDISP, m_iResdisp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAccountTab, CPropertyPage)
	//{{AFX_MSG_MAP(CAccountTab)
	ON_BN_CLICKED(IDC_LOGIN, OnLogin)
	ON_BN_CLICKED(IDC_ADDACCOUNT, OnAddaccount)
	ON_BN_CLICKED(IDC_DELETEACCOUNT, OnDeleteaccount)
	ON_BN_CLICKED(IDC_SETPL, OnSetpl)
	ON_BN_CLICKED(IDC_SETRESDISP, OnSetresdisp)
	ON_CBN_SELCHANGE(IDC_PRIVLEVEL, OnSelchangePrivlevel)
	ON_CBN_SELCHANGE(IDC_RESDISP, OnSelchangeResdisp)
	ON_BN_CLICKED(IDC_GETTAG, OnGettag)
	ON_BN_CLICKED(IDC_SETTAG, OnSettag)
	ON_CBN_SELCHANGE(IDC_TAGLIST, OnSelchangeTaglist)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAccountTab message handlers

void CAccountTab::OnLogin()
{
	// TODO: Add your control notification handler code here

}

void CAccountTab::OnAddaccount()
{
	// TODO: Add your control notification handler code here

}

void CAccountTab::OnDeleteaccount()
{
	// TODO: Add your control notification handler code here

}

void CAccountTab::OnSetpl()
{
	// TODO: Add your control notification handler code here

}

void CAccountTab::OnSetresdisp()
{
	// TODO: Add your control notification handler code here

}

void CAccountTab::OnSelchangePrivlevel()
{
	// TODO: Add your control notification handler code here

}

void CAccountTab::OnSelchangeResdisp()
{
	// TODO: Add your control notification handler code here

}

void CAccountTab::OnGettag()
{
	// TODO: Add your control notification handler code here

}

void CAccountTab::OnSettag()
{
	// TODO: Add your control notification handler code here

}

void CAccountTab::OnSelchangeTaglist()
{
	// TODO: Add your control notification handler code here

}

BOOL CAccountTab::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO: Add extra initialization here
	m_dcPropertyPage = ((CAxis2App*)AfxGetApp())->m_pcppAccountTab;

	if (m_dcCurrentPage == this)
		((CAxis2App*)AfxGetApp())->m_pcppAccountTab->m_dcCurrentPage = this;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CAccountTab::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	// TODO: Return a different brush if the default is not desired
	return ((CAxis2App*)AfxGetApp())->m_bkbrush;
}

void CAccountTab::OnSetPrivLevel(int iPrivLevel)
{
	CString csCmd;
	csCmd.Format("%sprivset %d", ((CAxis2App*)AfxGetApp())->m_csCommandPrefix, iPrivLevel);

	if (((CAxis2App*)AfxGetApp())->m_pRConsole)
		((CAxis2App*)AfxGetApp())->m_pRConsole->Send(csCmd);
}

void CAccountTab::OnSetResdisp(int iResdisp)
{
	CString csCmd;
	csCmd.Format("%sset account.resdisp %d", ((CAxis2App*)AfxGetApp())->m_csCommandPrefix, iResdisp);

	if (((CAxis2App*)AfxGetApp())->m_pRConsole)
		((CAxis2App*)AfxGetApp())->m_pRConsole->Send(csCmd);
}

void CAccountTab::OnSetTag(CString csTag, CString csVal)
{
	CString csCmd;
	csCmd.Format("%set account.%s %s", ((CAxis2App*)AfxGetApp())->m_csCommandPrefix, csTag, csVal);

	if (((CAxis2App*)AfxGetApp())->m_pRConsole)
		((CAxis2App*)AfxGetApp())->m_pRConsole->Send(csCmd);
}

void CAccountTab::OnGetTag(CString csTag)
{
	CString csCmd;
	csCmd.Format("%sget account.%s", ((CAxis2App*)AfxGetApp())->m_csCommandPrefix, csTag);

	if (((CAxis2App*)AfxGetApp())->m_pRConsole)
		((CAxis2App*)AfxGetApp())->m_pRConsole->Send(csCmd);
}