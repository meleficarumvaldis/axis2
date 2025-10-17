// CommandsTab.cpp : implementation file
//

#include "stdafx.h"
#include "Axis2.h"
#include "CommandsTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommandsTab property page

IMPLEMENT_DYNCREATE(CCommandsTab, CPropertyPage)

CCommandsTab::CCommandsTab() : CPropertyPage(CCommandsTab::IDD)
{
	//{{AFX_DATA_INIT(CCommandsTab)
	m_csCommand = _T("");
	//}}AFX_DATA_INIT
	m_iHistory = 0;
}

CCommandsTab::~CCommandsTab()
{
}

void CCommandsTab::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommandsTab)
	DDX_Control(pDX, IDC_COMMAND, m_Command);
	DDX_Control(pDX, IDC_COMMANDLIST, m_CommandList);
	DDX_Text(pDX, IDC_COMMAND, m_csCommand);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCommandsTab, CPropertyPage)
	//{{AFX_MSG_MAP(CCommandsTab)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_WM_CTLCOLOR()
	ON_LBN_DBLCLK(IDC_COMMANDLIST, OnDblclkCommandlist)
	ON_EN_VSCROLL(IDC_COMMAND, OnVscrollCommand)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_EN_CHANGE(IDC_COMMAND, OnChangeCommand)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommandsTab message handlers

void CCommandsTab::OnSend()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CString csCmd;
	csCmd.Format("%s%s", ((CAxis2App*)AfxGetApp())->m_csCommandPrefix, m_csCommand);

	if (((CAxis2App*)AfxGetApp())->m_pRConsole)
		((CAxis2App*)AfxGetApp())->m_pRConsole->Send(csCmd);

	m_saHistory.Add(m_csCommand);
	m_iHistory = m_saHistory.GetUpperBound();

	m_Command.SetWindowText("");
}

BOOL CCommandsTab::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO: Add extra initialization here
	m_dcPropertyPage = ((CAxis2App*)AfxGetApp())->m_pcppCommandsTab;

	if (m_dcCurrentPage == this)
		((CAxis2App*)AfxGetApp())->m_pcppCommandsTab->m_dcCurrentPage = this;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CCommandsTab::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	// TODO: Return a different brush if the default is not desired
	return ((CAxis2App*)AfxGetApp())->m_bkbrush;
}

void CCommandsTab::OnDblclkCommandlist()
{
	// TODO: Add your control notification handler code here
	int iSel = m_CommandList.GetCurSel();
	if ( iSel == -1 )
		return;

	CString csCmd;
	m_CommandList.GetText(iSel, csCmd);

	m_Command.SetWindowText(csCmd);
}

BOOL CCommandsTab::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_UP)
		{
			if ( m_iHistory > 0 )
				m_iHistory--;
			m_Command.SetWindowText(m_saHistory.GetAt(m_iHistory));
		}
		if (pMsg->wParam == VK_DOWN)
		{
			if ( m_iHistory < m_saHistory.GetUpperBound() )
				m_iHistory++;
			m_Command.SetWindowText(m_saHistory.GetAt(m_iHistory));
		}
		if (pMsg->wParam == VK_RETURN)
		{
			OnSend();
		}
	}

	return CPropertyPage::PreTranslateMessage(pMsg);
}

void CCommandsTab::OnVscrollCommand()
{
	// TODO: Add your control notification handler code here
}

void CCommandsTab::OnKeydown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	CPropertyPage::OnKeydown(nChar, nRepCnt, nFlags);
}

void CCommandsTab::OnKeyup(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	CPropertyPage::OnKeyup(nChar, nRepCnt, nFlags);
}

void CCommandsTab::OnChangeCommand()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	
}