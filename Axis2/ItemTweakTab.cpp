// ItemTweakTab.cpp : implementation file
//

#include "stdafx.h"
#include "Axis2.h"
#include "ItemTweakTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CItemTweakTab property page

IMPLEMENT_DYNCREATE(CItemTweakTab, CPropertyPage)

CItemTweakTab::CItemTweakTab() : CPropertyPage(CItemTweakTab::IDD)
{
	//{{AFX_DATA_INIT(CItemTweakTab)
	m_csValue = _T("");
	//}}AFX_DATA_INIT
}

CItemTweakTab::~CItemTweakTab()
{
}

void CItemTweakTab::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CItemTweakTab)
	DDX_Control(pDX, IDC_PROP, m_Prop);
	DDX_Control(pDX, IDC_TAG, m_Tag);
	DDX_Control(pDX, IDC_VALUE, m_Value);
	DDX_Text(pDX, IDC_VALUE, m_csValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CItemTweakTab, CPropertyPage)
	//{{AFX_MSG_MAP(CItemTweakTab)
	ON_BN_CLICKED(IDC_SETPROP, OnSetprop)
	ON_BN_CLICKED(IDC_SETTAG, OnSettag)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CItemTweakTab message handlers

void CItemTweakTab::OnSetprop()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CString csCmd, csProp;
	int iSel = m_Prop.GetCurSel();
	if (iSel == -1)
		return;
	m_Prop.GetLBText(iSel, csProp);

	csCmd.Format("%s%s %s", ((CAxis2App*)AfxGetApp())->m_csCommandPrefix, csProp, m_csValue);
	
	if (((CAxis2App*)AfxGetApp())->m_pRConsole)
		((CAxis2App*)AfxGetApp())->m_pRConsole->Send(csCmd);
}

void CItemTweakTab::OnSettag()
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

BOOL CItemTweakTab::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO: Add extra initialization here
	m_dcPropertyPage = ((CAxis2App*)AfxGetApp())->m_pcppItemTweakTab;

	if (m_dcCurrentPage == this)
		((CAxis2App*)AfxGetApp())->m_pcppItemTweakTab->m_dcCurrentPage = this;

	for ( int i = 0; i < ((CAxis2App*)AfxGetApp())->m_pScripts->m_asaITEMProps.GetSize(); i++ )
	{
		m_Prop.AddString(((CAxis2App*)AfxGetApp())->m_pScripts->m_asaITEMProps.GetAt(i));
	}

	for ( i = 0; i < ((CAxis2App*)AfxGetApp())->m_pScripts->m_asaITEMTags.GetSize(); i++ )
	{
		m_Tag.AddString(((CAxis2App*)AfxGetApp())->m_pScripts->m_asaITEMTags.GetAt(i));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CItemTweakTab::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	// TODO: Return a different brush if the default is not desired
	return ((CAxis2App*)AfxGetApp())->m_bkbrush;
}