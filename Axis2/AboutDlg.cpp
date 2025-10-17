#include "stdafx.h"
#include "Axis2.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_COPYRIGHT, m_Copyright);
	DDX_Control(pDX, IDOK, m_OK);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	m_OK.SetButtonImage(IDB_OK);

	CString csCopyright = ((CAxis2App*)AfxGetApp())->GetVersionTitle();
	csCopyright += "\r\n";
	csCopyright += CMsg(IDS_COPY1);
	csCopyright += "\r\n";
	csCopyright += CFMsg(IDS_COPY2,((CAxis2App*)AfxGetApp())->GetBuildTimestamp());
	csCopyright += "\r\n";
	csCopyright += CMsg(IDS_COPY3);

	m_Copyright.SetWindowText(csCopyright);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	// TODO: Return a different brush if the default is not desired
	return ((CAxis2App*)AfxGetApp())->m_bkbrush;
}