// RemoteProfileLoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Axis2.h"
#include "RemoteProfileLoginDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRemoteProfileLoginDlg dialog


CRemoteProfileLoginDlg::CRemoteProfileLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRemoteProfileLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRemoteProfileLoginDlg)
	m_csAddress = _T("");
	m_csPassword = _T("");
	m_iPort = 0;
	m_csUsername = _T("");
	m_csProfileName = _T("");
	//}}AFX_DATA_INIT}


void CRemoteProfileLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRemoteProfileLoginDlg)
	DDX_Text(pDX, IDC_ADDRESS, m_csAddress);
	DDX_Text(pDX, IDC_PASSWORD, m_csPassword);
	DDX_Text(pDX, IDC_PORT, m_iPort);
	DDX_Text(pDX, IDC_USERNAME, m_csUsername);
	DDX_CBString(pDX, IDC_PROFILENAME, m_csProfileName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRemoteProfileLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CRemoteProfileLoginDlg)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRemoteProfileLoginDlg message handlers

HBRUSH CRemoteProfileLoginDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	// TODO: Return a different brush if the default is not desired
	return ((CAxis2App*)AfxGetApp())->m_bkbrush;
}