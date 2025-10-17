// Settings_General.cpp : implementation file
//

#include "stdafx.h"
#include "Axis2.h"
#include "Settings_General.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingsGeneral property page

IMPLEMENT_DYNCREATE(CSettingsGeneral, CPropertyPage)

CSettingsGeneral::CSettingsGeneral() : CPropertyPage(CSettingsGeneral::IDD)
{
	//{{AFX_DATA_INIT(CSettingsGeneral)
	m_bAllowMultiple = FALSE;
	m_bAlwaysOnTop = FALSE;
	m_bDisableToolbar = FALSE;
	m_bLoadDefault = FALSE;
	m_bSysClose = FALSE;
	m_iStartTab = -1;
	m_bDrawStatics = FALSE;
	m_bRoomView = FALSE;
	m_bSameAsClient = FALSE;
	m_bDrawDifs = FALSE;
	m_csCommandPrefix = _T("");
	m_csUOTitle = _T("");
	//}}AFX_DATA_INIT}

CSettingsGeneral::~CSettingsGeneral()
{
}

void CSettingsGeneral::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingsGeneral)
	DDX_Control(pDX, IDC_STARTUOTITLE, m_UOTitle);
	DDX_Control(pDX, IDC_STARTCOMMANDPREFIX, m_CommandPrefix);
	DDX_Control(pDX, IDC_STARTTAB, m_StartTab);
	DDX_Check(pDX, IDC_ALLOWMULTIPLE, m_bAllowMultiple);
	DDX_Check(pDX, IDC_ALWAYSONTOP, m_bAlwaysOnTop);
	DDX_Check(pDX, IDC_DISABLETOOLBAR, m_bDisableToolbar);
	DDX_Check(pDX, IDC_LOADDEFAULT, m_bLoadDefault);
	DDX_Check(pDX, IDC_SYSCLOSE, m_bSysClose);
	DDX_CBIndex(pDX, IDC_STARTTAB, m_iStartTab);
	DDX_Check(pDX, IDC_DRAWSTATICS, m_bDrawStatics);
	DDX_Check(pDX, IDC_ROOMVIEW, m_bRoomView);
	DDX_Check(pDX, IDC_SAMEASCLIENT, m_bSameAsClient);
	DDX_Check(pDX, IDC_DRAWDIFS, m_bDrawDifs);
	DDX_Text(pDX, IDC_STARTCOMMANDPREFIX, m_csCommandPrefix);
	DDX_Text(pDX, IDC_STARTUOTITLE, m_csUOTitle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingsGeneral, CPropertyPage)
	//{{AFX_MSG_MAP(CSettingsGeneral)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingsGeneral message handlers

HBRUSH CSettingsGeneral::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	// TODO: Return a different brush if the default is not desired
	return ((CAxis2App*)AfxGetApp())->m_bkbrush;
}

BOOL CSettingsGeneral::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO: Add extra initialization here
	m_bAllowMultiple = ((CAxis2App*)AfxGetApp())->m_dwAllowMultiple;
	m_bAlwaysOnTop = ((CAxis2App*)AfxGetApp())->m_dwAlwaysOnTop;
	m_bDisableToolbar = ((CAxis2App*)AfxGetApp())->m_dwDisableToolbar;
	m_bLoadDefault = ((CAxis2App*)AfxGetApp())->m_dwLoadDefault;
	m_iStartTab = ((CAxis2App*)AfxGetApp())->m_dwStartTab;
	m_bSysClose = ((CAxis2App*)AfxGetApp())->m_dwSysClose;
	m_bDrawStatics = ((CAxis2App*)AfxGetApp())->m_dwDrawStatics;
	m_bRoomView = ((CAxis2App*)AfxGetApp())->m_dwRoomView;
	m_bSameAsClient = ((CAxis2App*)AfxGetApp())->m_dwSameAsClient;
	m_bDrawDifs = ((CAxis2App*)AfxGetApp())->m_dwDrawDifs;
	m_csCommandPrefix = ((CAxis2App*)AfxGetApp())->m_csCommandPrefix;
	m_csUOTitle = ((CAxis2App*)AfxGetApp())->m_csUOTitle;

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CSettingsGeneral::OnApply()
{
	// TODO: Add specialized code here and/or call the base class
	UpdateData(true);
	((CAxis2App*)AfxGetApp())->m_dwAllowMultiple = m_bAllowMultiple;
	((CAxis2App*)AfxGetApp())->m_dwAlwaysOnTop = m_bAlwaysOnTop;
	((CAxis2App*)AfxGetApp())->m_dwDisableToolbar = m_bDisableToolbar;
	((CAxis2App*)AfxGetApp())->m_dwLoadDefault = m_bLoadDefault;
	((CAxis2App*)AfxGetApp())->m_dwStartTab = m_iStartTab;
	((CAxis2App*)AfxGetApp())->m_dwSysClose = m_bSysClose;
	((CAxis2App*)AfxGetApp())->m_dwDrawStatics = m_bDrawStatics;
	((CAxis2App*)AfxGetApp())->m_dwRoomView = m_bRoomView;
	((CAxis2App*)AfxGetApp())->m_dwSameAsClient = m_bSameAsClient;
	((CAxis2App*)AfxGetApp())->m_dwDrawDifs = m_bDrawDifs;
	((CAxis2App*)AfxGetApp())->m_csCommandPrefix = m_csCommandPrefix;
	((CAxis2App*)AfxGetApp())->m_csUOTitle = m_csUOTitle;

	((CAxis2App*)AfxGetApp())->PutRegistryDword("AllowMultipleInstances", m_bAllowMultiple);
	((CAxis2App*)AfxGetApp())->PutRegistryDword("AlwaysOnTop", m_bAlwaysOnTop);
	((CAxis2App*)AfxGetApp())->PutRegistryDword("DisableToolbar", m_bDisableToolbar);
	((CAxis2App*)AfxGetApp())->PutRegistryDword("LoadDefault", m_bLoadDefault);
	((CAxis2App*)AfxGetApp())->PutRegistryDword("StartTab", m_iStartTab);
	((CAxis2App*)AfxGetApp())->PutRegistryDword("SysClose", m_bSysClose);
	((CAxis2App*)AfxGetApp())->PutRegistryDword("DrawStatics", m_bDrawStatics);
	((CAxis2App*)AfxGetApp())->PutRegistryDword("RoomView", m_bRoomView);
	((CAxis2App*)AfxGetApp())->PutRegistryDword("SameAsCLient", m_bSameAsClient);
	((CAxis2App*)AfxGetApp())->PutRegistryDword("DrawDifs", m_bDrawDifs);
	((CAxis2App*)AfxGetApp())->PutRegistryString("CommandPrefix", m_csCommandPrefix);
	((CAxis2App*)AfxGetApp())->PutRegistryString("UOTitle", m_csUOTitle);
	
	return CPropertyPage::OnApply();
}