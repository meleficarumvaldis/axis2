// Reminder_DLG.cpp : implementation file
//

#include "stdafx.h"
#include "Axis2.h"
#include "Reminder_DLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReminderDLG dialog


CReminderDLG::CReminderDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CReminderDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReminderDLG)
	m_csMessage = _T("");
	m_csTitle = _T("");
	//}}AFX_DATA_INIT}


void CReminderDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReminderDLG)
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Text(pDX, IDC_MESSAGE, m_csMessage);
	DDX_Text(pDX, IDC_TITLE, m_csTitle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReminderDLG, CDialog)
	//{{AFX_MSG_MAP(CReminderDLG)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReminderDLG message handlers

BOOL CReminderDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	m_OK.SetButtonImage(IDB_OK);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CReminderDLG::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	// TODO: Return a different brush if the default is not desired
	return ((CAxis2App*)AfxGetApp())->m_bkbrush;
}