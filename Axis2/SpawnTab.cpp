// SpawnTab.cpp : implementation file
//

#include "stdafx.h"
#include "Axis2.h"
#include "SpawnTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpawnTab property page

IMPLEMENT_DYNCREATE(CSpawnTab, CPropertyPage)

CSpawnTab::CSpawnTab() : CPropertyPage(CSpawnTab::IDD)
{
	//{{AFX_DATA_INIT(CSpawnTab)
	m_csAmount = _T("");
	m_csNPC = _T("");
	m_bFemale = FALSE;
	m_bNPC = FALSE;
	//}}AFX_DATA_INIT}

CSpawnTab::~CSpawnTab()
{
}

void CSpawnTab::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpawnTab)
	DDX_Control(pDX, IDC_NPCLIST, m_NPCList);
	DDX_Control(pDX, IDC_NPC, m_NPC);
	DDX_Control(pDX, IDC_AMOUNT, m_Amount);
	DDX_Text(pDX, IDC_AMOUNT, m_csAmount);
	DDX_Text(pDX, IDC_NPC, m_csNPC);
	DDX_Check(pDX, IDC_FEMALE, m_bFemale);
	DDX_Check(pDX, IDC_ISNPC, m_bNPC);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSpawnTab, CPropertyPage)
	//{{AFX_MSG_MAP(CSpawnTab)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_LBN_SELCHANGE(IDC_NPCLIST, OnSelchangeNpclist)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_OPENMAP, OnOpenmap)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpawnTab message handlers

void CSpawnTab::OnAdd()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CString csCommand;
	if (m_bNPC)
	{
		csCommand.Format("%sadd npc %s", ((CAxis2App*)AfxGetApp())->m_csCommandPrefix, m_csNPC);
	}
	else
	{
		csCommand.Format("%sadd %s", ((CAxis2App*)AfxGetApp())->m_csCommandPrefix, m_csNPC);
	}

	if (m_csAmount != "")
		csCommand.Format("%s %s", csCommand, m_csAmount);

	if (m_bFemale)
		csCommand += " female";
	
	if (((CAxis2App*)AfxGetApp())->m_pRConsole)
		((CAxis2App*)AfxGetApp())->m_pRConsole->Send(csCommand);
}

void CSpawnTab::OnSelchangeNpclist()
{
	// TODO: Add your control notification handler code here
	int iSel = m_NPCList.GetCurSel();
	if (iSel == -1)
		return;

	CSObject * pNPC = (CSObject *) ((CAxis2App*)AfxGetApp())->m_pScripts->m_aNPC.GetAt(iSel);
	m_NPC.SetWindowText(pNPC->m_csID);
}

BOOL CSpawnTab::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO: Add extra initialization here
	m_dcPropertyPage = ((CAxis2App*)AfxGetApp())->m_pcppSpawnTab;

	if (m_dcCurrentPage == this)
		((CAxis2App*)AfxGetApp())->m_pcppSpawnTab->m_dcCurrentPage = this;

	for ( int i = 0; i < ((CAxis2App*)AfxGetApp())->m_pScripts->m_aNPC.GetSize(); i++ )
	{
		CSObject * pNPC = (CSObject *) ((CAxis2App*)AfxGetApp())->m_pScripts->m_aNPC.GetAt(i);
		m_NPCList.AddString(pNPC->m_csName);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CSpawnTab::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	// TODO: Return a different brush if the default is not desired
	return ((CAxis2App*)AfxGetApp())->m_bkbrush;
}

void CSpawnTab::OnOpenmap()
{
	// TODO: Add your control notification handler code here
	if (((CAxis2App*)AfxGetApp())->m_dlgWorldMap)
		delete ((CAxis2App*)AfxGetApp())->m_dlgWorldMap;
	((CAxis2App*)AfxGetApp())->m_dlgWorldMap = new CWorldMap;
	((CAxis2App*)AfxGetApp())->m_dlgWorldMap->Create(IDD_WORLDMAP);
	((CAxis2App*)AfxGetApp())->m_dlgWorldMap->ShowWindow(SW_SHOWNORMAL);
}