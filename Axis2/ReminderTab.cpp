// ReminderTab.cpp : implementation file
//

#include "stdafx.h"
#include "Axis2.h"
#include "ReminderTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReminderTab property page

IMPLEMENT_DYNCREATE(CReminderTab, CPropertyPage)

CReminderTab::CReminderTab() : CPropertyPage(CReminderTab::IDD)
{
	//{{AFX_DATA_INIT(CReminderTab)
	m_csMessage = _T("");
	m_csTitle = _T("");
	m_csTime = _T("");
	//}}AFX_DATA_INIT}

CReminderTab::~CReminderTab()
{
}

void CReminderTab::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReminderTab)
	DDX_Control(pDX, IDC_REMINDERLIST, m_ReminderList);
	DDX_Text(pDX, IDC_MESSAGE, m_csMessage);
	DDX_Text(pDX, IDC_TITLE, m_csTitle);
	DDX_Text(pDX, IDC_TIME, m_csTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReminderTab, CPropertyPage)
	//{{AFX_MSG_MAP(CReminderTab)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReminderTab message handlers

void CReminderTab::OnAdd()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CReminder * pReminder = new CReminder;
	pReminder->csMessage = m_csMessage;
	pReminder->csTitle = m_csTitle;
	pReminder->iHour = atoi(m_csTime.SpanExcluding(":"));
	pReminder->iMin = atoi(m_csTime.Mid(m_csTime.Find(":")+1));
	((CAxis2App*)AfxGetApp())->m_pScripts->m_aReminders.Add(pReminder);
	m_ReminderList.AddString(m_csTitle);
}

void CReminderTab::OnRemove()
{
	// TODO: Add your control notification handler code here
	int iSel = m_ReminderList.GetCurSel();
	if ( iSel == -1 )
		return;

	CReminder * pReminder = (CReminder *)((CAxis2App*)AfxGetApp())->m_pScripts->m_aReminders.GetAt(iSel);
	delete pReminder;
	((CAxis2App*)AfxGetApp())->m_pScripts->m_aReminders.RemoveAt(iSel);
	m_ReminderList.DeleteString(iSel);
}

BOOL CReminderTab::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO: Add extra initialization here
	m_dcPropertyPage = ((CAxis2App*)AfxGetApp())->m_pcppReminderTab;

	if (m_dcCurrentPage == this)
		((CAxis2App*)AfxGetApp())->m_pcppReminderTab->m_dcCurrentPage = this;

	for ( int i = 0; i < ((CAxis2App*)AfxGetApp())->m_pScripts->m_aReminders.GetSize(); i++ )
	{
		CReminder * pReminder = (CReminder *) ((CAxis2App*)AfxGetApp())->m_pScripts->m_aReminders.GetAt(i);
		m_ReminderList.AddString(pReminder->csTitle);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CReminderTab::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	// TODO: Return a different brush if the default is not desired
	return ((CAxis2App*)AfxGetApp())->m_bkbrush;
}