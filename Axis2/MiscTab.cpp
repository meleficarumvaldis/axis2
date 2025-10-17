// MiscTab.cpp : implementation file
//

#include "stdafx.h"
#include "Axis2.h"
#include "MiscTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMiscTab property page

IMPLEMENT_DYNCREATE(CMiscTab, CPropertyPage)

CMiscTab::CMiscTab() : CPropertyPage(CMiscTab::IDD)
{
	//{{AFX_DATA_INIT(CMiscTab)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMiscTab::~CMiscTab()
{
}

void CMiscTab::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMiscTab)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMiscTab, CPropertyPage)
	//{{AFX_MSG_MAP(CMiscTab)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_OPENDOOR, OnOpendw)
	ON_BN_CLICKED(IDC_OPENLW, OnOpenlw)
	ON_BN_CLICKED(IDC_OPENSCRIPT, OnOpenscript)
	ON_BN_CLICKED(IDC_OPENMULTIVIEW, OnOpenmultiview)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMiscTab message handlers

HBRUSH CMiscTab::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));
	
	// TODO: Return a different brush if the default is not desired
	return ((CAxis2App*)AfxGetApp())->m_bkbrush;
}

BOOL CMiscTab::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_dcPropertyPage = ((CAxis2App*)AfxGetApp())->m_pcppMiscTab;

	if (m_dcCurrentPage == this)
		((CAxis2App*)AfxGetApp())->m_pcppMiscTab->m_dcCurrentPage = this;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMiscTab::OnOpendw()
{
	// TODO: Add your control notification handler code here
	if (((CAxis2App*)AfxGetApp())->m_dlgDoorWiz)
		delete ((CAxis2App*)AfxGetApp())->m_dlgDoorWiz;
	((CAxis2App*)AfxGetApp())->m_dlgDoorWiz = new CDoorWizard;
	((CAxis2App*)AfxGetApp())->m_dlgDoorWiz->Create(IDD_DOORWIZ);
	((CAxis2App*)AfxGetApp())->m_dlgDoorWiz->ShowWindow(SW_SHOWNORMAL);
}

void CMiscTab::OnOpenlw()
{
	// TODO: Add your control notification handler code here
	if (((CAxis2App*)AfxGetApp())->m_dlgLightWiz)
		delete ((CAxis2App*)AfxGetApp())->m_dlgLightWiz;
	((CAxis2App*)AfxGetApp())->m_dlgLightWiz = new CLightWizard;
	((CAxis2App*)AfxGetApp())->m_dlgLightWiz->Create(IDD_LIGHTWIZ);
	((CAxis2App*)AfxGetApp())->m_dlgLightWiz->ShowWindow(SW_SHOWNORMAL);
}

void CMiscTab::OnOpenscript()
{
	// TODO: Add your control notification handler code here
	CScriptEditorFrame *pScriptEditor = new CScriptEditorFrame;
	pScriptEditor->Create(NULL, "Script Editor", WS_OVERLAPPED | WS_SYSMENU);
	pScriptEditor->ShowWindow(SW_SHOWNORMAL);
}

void CMiscTab::OnOpenmultiview()
{
	// TODO: Add your control notification handler code here
	if (((CAxis2App*)AfxGetApp())->m_dlgMultiView)
		delete ((CAxis2App*)AfxGetApp())->m_dlgMultiView;
	((CAxis2App*)AfxGetApp())->m_dlgMultiView = new CMultiView;
	((CAxis2App*)AfxGetApp())->m_dlgMultiView->Create(IDD_MULTIVIEW);
	((CAxis2App*)AfxGetApp())->m_dlgMultiView->ShowWindow(SW_SHOWNORMAL);
}