// PlayerTweakTab.cpp : implementation file
//

#include "stdafx.h"
#include "Axis2.h"
#include "PlayerTweakTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlayerTweakTab property page

IMPLEMENT_DYNCREATE(CPlayerTweakTab, CPropertyPage)

CPlayerTweakTab::CPlayerTweakTab() : CPropertyPage(CPlayerTweakTab::IDD)
{
	//{{AFX_DATA_INIT(CPlayerTweakTab)
	m_csValue = _T("");
	//}}AFX_DATA_INIT
}

CPlayerTweakTab::~CPlayerTweakTab()
{
}

void CPlayerTweakTab::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlayerTweakTab)
	DDX_Control(pDX, IDC_VALUE, m_Value);
	DDX_Control(pDX, IDC_TAG, m_Tag);
	DDX_Control(pDX, IDC_RESIST, m_Resist);
	DDX_Control(pDX, IDC_STAT, m_Stat);
	DDX_Text(pDX, IDC_VALUE, m_csValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPlayerTweakTab, CPropertyPage)
	//{{AFX_MSG_MAP(CPlayerTweakTab)
	ON_BN_CLICKED(IDC_SETSTAT, OnSetstat)
	ON_BN_CLICKED(IDC_SETRESIST, OnSetresist)
	ON_BN_CLICKED(IDC_SETTAG, OnSettag)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlayerTweakTab message handlers

void CPlayerTweakTab::OnSetstat()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CString csCmd, csStat;
	int iSel = m_Stat.GetCurSel();
	if (iSel == -1)
		return;
	m_Stat.GetLBText(iSel, csStat);

	csCmd.Format("%s%s %s", ((CAxis2App*)AfxGetApp())->m_csCommandPrefix, csStat, m_csValue);

	if (((CAxis2App*)AfxGetApp())->m_pRConsole)
		((CAxis2App*)AfxGetApp())->m_pRConsole->Send(csCmd);
}

void CPlayerTweakTab::OnSetresist()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CString csCmd, csResist;
	int iSel = m_Resist.GetCurSel();
	if (iSel == -1)
		return;
	m_Resist.GetLBText(iSel, csResist);

	csCmd.Format("%s%s %s", ((CAxis2App*)AfxGetApp())->m_csCommandPrefix, csResist, m_csValue);

	if (((CAxis2App*)AfxGetApp())->m_pRConsole)
		((CAxis2App*)AfxGetApp())->m_pRConsole->Send(csCmd);
}

void CPlayerTweakTab::OnSettag()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CString csCmd, csTag;
	int iSel = m_Tag.GetCurSel();
	if (iSel == -1)
		return;
	m_Tag.GetLBText(iSel, csTag);

	csCmd.Format("%sset tag.%s %s", ((CAxis2App*)AfxGetApp())->m_csCommandPrefix, csTag, m_csValue);

	if (((CAxis2App*)AfxGetApp())->m_pRConsole)
		((CAxis2App*)AfxGetApp())->m_pRConsole->Send(csCmd);
}

BOOL CPlayerTweakTab::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO: Add extra initialization here
	m_dcPropertyPage = ((CAxis2App*)AfxGetApp())->m_pcppPlayerTweakTab;

	if (m_dcCurrentPage == this)
		((CAxis2App*)AfxGetApp())->m_pcppPlayerTweakTab->m_dcCurrentPage = this;

	for ( int i = 0; i < ((CAxis2App*)AfxGetApp())->m_pScripts->m_asaNPCStats.GetSize(); i++ )
	{
		m_Stat.AddString(((CAxis2App*)AfxGetApp())->m_pScripts->m_asaNPCStats.GetAt(i));
	}

	for ( i = 0; i < ((CAxis2App*)AfxGetApp())->m_pScripts->m_asaNPCResistences.GetSize(); i++ )
	{
		m_Resist.AddString(((CAxis2App*)AfxGetApp())->m_pScripts->m_asaNPCResistences.GetAt(i));
	}

	for ( i = 0; i < ((CAxis2App*)AfxGetApp())->m_pScripts->m_asaNPCTags.GetSize(); i++ )
	{
		m_Tag.AddString(((CAxis2App*)AfxGetApp())->m_pScripts->m_asaNPCTags.GetAt(i));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CPlayerTweakTab::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	// TODO: Return a different brush if the default is not desired
	return ((CAxis2App*)AfxGetApp())->m_bkbrush;
}