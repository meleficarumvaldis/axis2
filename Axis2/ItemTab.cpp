// ItemTab.cpp : implementation file
//

#include "stdafx.h"
#include "Axis2.h"
#include "ItemTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CItemTab property page

IMPLEMENT_DYNCREATE(CItemTab, CPropertyPage)

CItemTab::CItemTab() : CPropertyPage(CItemTab::IDD)
{
	//{{AFX_DATA_INIT(CItemTab)
	m_csAmount = _T("");
	m_csContainer = _T("");
	m_csItemID = _T("");
	m_csName = _T("");
	m_bCont = FALSE;
	m_bBank = FALSE;
	m_bEquip = FALSE;
	m_csColor = _T("");
	//}}AFX_DATA_INIT
}

CItemTab::~CItemTab()
{
}

void CItemTab::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CItemTab)
	DDX_Control(pDX, IDC_ITEMLIST, m_ItemList);
	DDX_Control(pDX, IDC_ITEMCOLOR, m_ItemColor);
	DDX_Control(pDX, IDC_ITEMID, m_ItemID);
	DDX_Control(pDX, IDC_CONTAINER, m_Container);
	DDX_Control(pDX, IDC_AMOUNT, m_Amount);
	DDX_Control(pDX, IDC_ITEMNAME, m_Name);
	DDX_Text(pDX, IDC_AMOUNT, m_csAmount);
	DDX_Text(pDX, IDC_CONTAINER, m_csContainer);
	DDX_Text(pDX, IDC_ITEMID, m_csItemID);
	DDX_Text(pDX, IDC_ITEMNAME, m_csName);
	DDX_Check(pDX, IDC_CONT, m_bCont);
	DDX_Check(pDX, IDC_BANK, m_bBank);
	DDX_Check(pDX, IDC_EQUIP, m_bEquip);
	DDX_Text(pDX, IDC_ITEMCOLOR, m_csColor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CItemTab, CPropertyPage)
	//{{AFX_MSG_MAP(CItemTab)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_LBN_SELCHANGE(IDC_ITEMLIST, OnSelchangeItemlist)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_BN_CLICKED(IDC_SEARCH, OnSearch)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CItemTab message handlers

void CItemTab::OnAdd()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CString csCommand;
	csCommand.Format("%sadd %s", ((CAxis2App*)AfxGetApp())->m_csCommandPrefix, m_csItemID);

	if (m_csAmount != "")
		csCommand.Format("%s %s", csCommand, m_csAmount);
	if (m_csColor != "")
		csCommand.Format("%s %s", csCommand, m_csColor);
	if (m_csName != "")
		csCommand.Format("%s %s", csCommand, m_csName);
	if (m_bCont)
	{
		csCommand.Format("%s cont %s", csCommand, m_csContainer);
	}
	if (m_bBank)
	{
		csCommand += " bank";
	}
	if (m_bEquip)
	{
		csCommand += " equip";
	}
	
	if (((CAxis2App*)AfxGetApp())->m_pRConsole)
		((CAxis2App*)AfxGetApp())->m_pRConsole->Send(csCommand);
}

void CItemTab::OnSelchangeItemlist()
{
	// TODO: Add your control notification handler code here
	int iSel = m_ItemList.GetCurSel();
	if (iSel == -1)
		return;

	CSObject * pItem = (CSObject *) ((CAxis2App*)AfxGetApp())->m_pScripts->m_aItems.GetAt(iSel);
	m_ItemID.SetWindowText(pItem->m_csID);
}

void CItemTab::OnRemove()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CString csCommand;
	csCommand.Format("%sremove %s", ((CAxis2App*)AfxGetApp())->m_csCommandPrefix, m_csItemID);

	if (((CAxis2App*)AfxGetApp())->m_pRConsole)
		((CAxis2App*)AfxGetApp())->m_pRConsole->Send(csCommand);
}

void CItemTab::OnClear()
{
	// TODO: Add your control notification handler code here
	CString csCommand;
	csCommand.Format("%sclear", ((CAxis2App*)AfxGetApp())->m_csCommandPrefix);

	if (((CAxis2App*)AfxGetApp())->m_pRConsole)
		((CAxis2App*)AfxGetApp())->m_pRConsole->Send(csCommand);
}

void CItemTab::OnSearch()
{
	// TODO: Add your control notification handler code here

}

BOOL CItemTab::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO: Add extra initialization here
	m_dcPropertyPage = ((CAxis2App*)AfxGetApp())->m_pcppItemTab;

	if (m_dcCurrentPage == this)
		((CAxis2App*)AfxGetApp())->m_pcppItemTab->m_dcCurrentPage = this;

	for ( int i = 0; i < ((CAxis2App*)AfxGetApp())->m_pScripts->m_aItems.GetSize(); i++ )
	{
		CSObject * pItem = (CSObject *) ((CAxis2App*)AfxGetApp())->m_pScripts->m_aItems.GetAt(i);
		m_ItemList.AddString(pItem->m_csName);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CItemTab::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	// TODO: Return a different brush if the default is not desired
	return ((CAxis2App*)AfxGetApp())->m_bkbrush;
}