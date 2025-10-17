// LogTab.cpp : implementation file
//

#include "stdafx.h"
#include "Axis2.h"
#include "LogTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogTab property page

IMPLEMENT_DYNCREATE(CLogTab, CPropertyPage)

CLogTab::CLogTab() : CPropertyPage(CLogTab::IDD)
{
	//{{AFX_DATA_INIT(CLogTab)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CLogTab::~CLogTab()
{
}

void CLogTab::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogTab)
	DDX_Control(pDX, IDC_LOG, m_Log);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogTab, CPropertyPage)
	//{{AFX_MSG_MAP(CLogTab)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogTab message handlers

BOOL CLogTab::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	// TODO: Add extra initialization here
	m_dcPropertyPage = ((CAxis2App*)AfxGetApp())->m_pcppAxisLogTab;

	if (m_dcCurrentPage == this)
		((CAxis2App*)AfxGetApp())->m_pcppAxisLogTab->m_dcCurrentPage = this;

	m_Log.InsertColumn(0, "Time", LVCFMT_LEFT, 50);
	m_Log.InsertColumn(1, "Type", LVCFMT_LEFT, 50);
	m_Log.InsertColumn(2, "Message", LVCFMT_LEFT, 300);

	if (!((CAxis2App*)AfxGetApp())->m_olLog.IsEmpty())
	{
		POSITION Pos = ((CAxis2App*)AfxGetApp())->m_olLog.GetHeadPosition();
		while (Pos != NULL)
		{
			CLogArray * pLog = (CLogArray *) ((CAxis2App*)AfxGetApp())->m_olLog.GetNext(Pos);
			AddLine(pLog);
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CLogTab::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	// TODO: Return a different brush if the default is not desired
	return ((CAxis2App*)AfxGetApp())->m_bkbrush;
}

void CLogTab::AddLine(CLogArray *pLog)
{
	LVITEM lvi;

	lvi.mask = LVIF_TEXT | LVIF_STATE;
	lvi.iItem = m_Log.GetItemCount();
	lvi.iSubItem = 0;
	lvi.pszText = (LPTSTR)(LPCTSTR)(pLog->GetAt(0));
	lvi.state = 0;
	lvi.stateMask = 0;
	m_Log.InsertItem(&lvi);

	lvi.iSubItem = 1;
	lvi.pszText = (LPTSTR)(LPCTSTR)(pLog->GetAt(1));
	m_Log.SetItem(&lvi);

	lvi.iSubItem = 2;
	lvi.pszText = (LPTSTR)(LPCTSTR)(pLog->GetAt(2));
	m_Log.SetItem(&lvi);
}