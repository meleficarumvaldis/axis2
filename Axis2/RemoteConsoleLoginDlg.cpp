// RemoteConsoleLoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Axis2.h"
#include "RemoteConsoleLoginDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRemoteConsoleLoginDlg dialog


CRemoteConsoleLoginDlg::CRemoteConsoleLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRemoteConsoleLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRemoteConsoleLoginDlg)
	m_csAddress = _T("");
	m_csPassword = _T("");
	m_iPort = 0;
	m_csUsername = _T("");
	//}}AFX_DATA_INIT}


void CRemoteConsoleLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRemoteConsoleLoginDlg)
	DDX_Text(pDX, IDC_ADDRESS, m_csAddress);
	DDX_Text(pDX, IDC_PASSWORD, m_csPassword);
	DDX_Text(pDX, IDC_PORT, m_iPort);
	DDX_Text(pDX, IDC_USERNAME, m_csUsername);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRemoteConsoleLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CRemoteConsoleLoginDlg)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRemoteConsoleLoginDlg message handlers

HBRUSH CRemoteConsoleLoginDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	// TODO: Return a different brush if the default is not desired
	return ((CAxis2App*)AfxGetApp())->m_bkbrush;
}