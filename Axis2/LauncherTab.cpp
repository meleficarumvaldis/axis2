// LauncherTab.cpp : implementation file
//

#include "stdafx.h"
#include "Axis2.h"
#include "LauncherTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLauncherTab property page

IMPLEMENT_DYNCREATE(CLauncherTab, CPropertyPage)

CLauncherTab::CLauncherTab() : CPropertyPage(CLauncherTab::IDD)
{
	//{{AFX_DATA_INIT(CLauncherTab)
	m_bRemove = FALSE;
	m_csParameters = _T("");
	//}}AFX_DATA_INIT
}

CLauncherTab::~CLauncherTab()
{
}

void CLauncherTab::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLauncherTab)
	DDX_Control(pDX, IDC_CLIENTLIST, m_ClientList);
	DDX_Check(pDX, IDC_REMOVE, m_bRemove);
	DDX_Text(pDX, IDC_PARAMETERS, m_csParameters);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLauncherTab, CPropertyPage)
	//{{AFX_MSG_MAP(CLauncherTab)
	ON_BN_CLICKED(IDC_LAUNCH, OnLaunch)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLauncherTab message handlers

void CLauncherTab::OnLaunch()
{
	// TODO: Add your control notification handler code here
	CString csClient;
	int iSel = m_ClientList.GetCurSel();
	if ( iSel == -1 )
		return;

	CProgram * pProgram = (CProgram *)((CAxis2App*)AfxGetApp())->m_pScripts->m_aLaunch.GetAt(iSel);
	csClient = pProgram->csPath;

	if (m_bRemove)
	{
		csClient.Replace("client.exe", "razor.exe");
		csClient.Replace("client_2d.exe", "razor.exe");
	}

	STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

	CreateProcess(csClient, (char *)(LPCTSTR)m_csParameters, NULL, NULL, false, 0, NULL, NULL, &si, &pi);
}

BOOL CLauncherTab::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO: Add extra initialization here
	m_dcPropertyPage = ((CAxis2App*)AfxGetApp())->m_pcppLauncherTab;

	if (m_dcCurrentPage == this)
		((CAxis2App*)AfxGetApp())->m_pcppLauncherTab->m_dcCurrentPage = this;

	for ( int i = 0; i < ((CAxis2App*)AfxGetApp())->m_pScripts->m_aLaunch.GetSize(); i++ )
	{
		CProgram * pProgram = (CProgram *) ((CAxis2App*)AfxGetApp())->m_pScripts->m_aLaunch.GetAt(i);
		m_ClientList.AddString(pProgram->csName);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CLauncherTab::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	// TODO: Return a different brush if the default is not desired
	return ((CAxis2App*)AfxGetApp())->m_bkbrush;
}