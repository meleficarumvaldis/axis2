// ToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "Axis2.h"
#include "ToolBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAxis2LBar dialog


CAxis2LBar::CAxis2LBar(CWnd* pParent /*=NULL*/)
	: CDialog(CAxis2LBar::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAxis2LBar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT}


void CAxis2LBar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAxis2LBar)
	DDX_Control(pDX, IDC_BUTTON6, m_Button6);
	DDX_Control(pDX, IDC_BUTTON5, m_Button5);
	DDX_Control(pDX, IDC_BUTTON4, m_Button4);
	DDX_Control(pDX, IDC_BUTTON3, m_Button3);
	DDX_Control(pDX, IDC_BUTTON2, m_Button2);
	DDX_Control(pDX, IDC_BUTTON1, m_Button1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAxis2LBar, CDialog)
	//{{AFX_MSG_MAP(CAxis2LBar)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAxis2LBar message handlers

HBRUSH CAxis2LBar::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	// TODO: Return a different brush if the default is not desired
	return ((CAxis2App*)AfxGetApp())->m_bkbrush;
}

BOOL CAxis2LBar::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	m_Button1.SetButtonImage(IDB_BUTTON1, 0, 0, 0, 0);
	m_Button2.SetButtonImage(IDB_BUTTON2, 0, 0, 0, 0);
	m_Button3.SetButtonImage(IDB_BUTTON3, 0, 0, 0, 0);
	m_Button4.SetButtonImage(IDB_BUTTON4, 0, 0, 0, 0);
	m_Button5.SetButtonImage(IDB_BUTTON5, 0, 0, 0, 0);
	m_Button6.SetButtonImage(IDB_BUTTON6, 0, 0, 0, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}