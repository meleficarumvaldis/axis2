// Settings_Spawn.cpp : implementation file
//

#include "stdafx.h"
#include "Axis2.h"
#include "Settings_Spawn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingsSpawn property page

IMPLEMENT_DYNCREATE(CSettingsSpawn, CPropertyPage)

CSettingsSpawn::CSettingsSpawn() : CPropertyPage(CSettingsSpawn::IDD)
{
	//{{AFX_DATA_INIT(CSettingsSpawn)
	m_bShowItems = FALSE;
	m_bShowMap = FALSE;
	m_bShowNPCs = FALSE;
	m_bShowSpawnPoints = FALSE;
	//}}AFX_DATA_INIT}

CSettingsSpawn::~CSettingsSpawn()
{
}

void CSettingsSpawn::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingsSpawn)
	DDX_Control(pDX, IDC_SPAWNBGCOLOR, m_SpawnBGColor);
	DDX_Control(pDX, IDC_NPCSPAWNCOLOR, m_NPCSpawnColor);
	DDX_Control(pDX, IDC_ITEMSPAWNCOLOR, m_ItemSpawnColor);
	DDX_Check(pDX, IDC_SHOWITEMS, m_bShowItems);
	DDX_Check(pDX, IDC_SHOWMAP, m_bShowMap);
	DDX_Check(pDX, IDC_SHOWNSPS, m_bShowNPCs);
	DDX_Check(pDX, IDC_SHOWSPAWNPOINTS, m_bShowSpawnPoints);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingsSpawn, CPropertyPage)
	//{{AFX_MSG_MAP(CSettingsSpawn)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingsSpawn message handlers

HBRUSH CSettingsSpawn::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	// TODO: Return a different brush if the default is not desired
	return ((CAxis2App*)AfxGetApp())->m_bkbrush;
}

BOOL CSettingsSpawn::OnApply()
{
	// TODO: Add specialized code here and/or call the base class
	UpdateData(true);
	((CAxis2App*)AfxGetApp())->m_dwShowSpawnpoints = m_bShowSpawnPoints;
	((CAxis2App*)AfxGetApp())->m_dwNPCSpawnColor = m_NPCSpawnColor.GetColor();
	((CAxis2App*)AfxGetApp())->m_dwItemSpawnColor = m_ItemSpawnColor.GetColor();
	((CAxis2App*)AfxGetApp())->m_dwSpawnBGColor = m_SpawnBGColor.GetColor();
	((CAxis2App*)AfxGetApp())->m_dwShowItems = m_bShowItems;
	((CAxis2App*)AfxGetApp())->m_dwShowNPCs = m_bShowNPCs;
	((CAxis2App*)AfxGetApp())->m_dwShowMap = m_bShowMap;

	((CAxis2App*)AfxGetApp())->PutRegistryDword("ShowSpawnpoints", m_bShowSpawnPoints);
	((CAxis2App*)AfxGetApp())->PutRegistryDword("NPCSpawnColor", ((CAxis2App*)AfxGetApp())->m_dwNPCSpawnColor);
	((CAxis2App*)AfxGetApp())->PutRegistryDword("ItemSpawnColor", ((CAxis2App*)AfxGetApp())->m_dwItemSpawnColor);
	((CAxis2App*)AfxGetApp())->PutRegistryDword("SpawnBGColor", ((CAxis2App*)AfxGetApp())->m_dwSpawnBGColor);
	((CAxis2App*)AfxGetApp())->PutRegistryDword("ShowItems", m_bShowItems);
	((CAxis2App*)AfxGetApp())->PutRegistryDword("ShowNPCs", m_bShowNPCs);
	((CAxis2App*)AfxGetApp())->PutRegistryDword("ShowMap", m_bShowMap);

	return CPropertyPage::OnApply();
}

BOOL CSettingsSpawn::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO: Add extra initialization here
	m_bShowSpawnPoints = ((CAxis2App*)AfxGetApp())->m_dwShowSpawnpoints;
	m_NPCSpawnColor.SetColor(((CAxis2App*)AfxGetApp())->m_dwNPCSpawnColor);
	m_ItemSpawnColor.SetColor(((CAxis2App*)AfxGetApp())->m_dwItemSpawnColor);
	m_SpawnBGColor.SetColor(((CAxis2App*)AfxGetApp())->m_dwSpawnBGColor);
	m_bShowItems = ((CAxis2App*)AfxGetApp())->m_dwShowItems;
	m_bShowNPCs = ((CAxis2App*)AfxGetApp())->m_dwShowNPCs;
	m_bShowMap = ((CAxis2App*)AfxGetApp())->m_dwShowMap;

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}