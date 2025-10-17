// Settings_Paths.cpp : implementation file
//

#include "stdafx.h"
#include "Axis2.h"
#include "Settings_Paths.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingsPaths property page

IMPLEMENT_DYNCREATE(CSettingsPaths, CPropertyPage)

CSettingsPaths::CSettingsPaths() : CPropertyPage(CSettingsPaths::IDD)
{
	//{{AFX_DATA_INIT(CSettingsPaths)
	m_csClientPath = _T("");
	m_csMulPath = _T("");
	m_csProfilePath = _T("");
	m_csLastProfile = _T("");
	m_csDefaultProfile = _T("");
	//}}AFX_DATA_INIT}

CSettingsPaths::~CSettingsPaths()
{
}

void CSettingsPaths::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingsPaths)
	DDX_Text(pDX, IDC_CLIENTPATH, m_csClientPath);
	DDX_Text(pDX, IDC_MULPATH, m_csMulPath);
	DDX_Text(pDX, IDC_PROFILEPATH, m_csProfilePath);
	DDX_CBString(pDX, IDC_LASTPROFILE, m_csLastProfile);
	DDX_CBString(pDX, IDC_DEFAULTPROFILE, m_csDefaultProfile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingsPaths, CPropertyPage)
	//{{AFX_MSG_MAP(CSettingsPaths)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BROWSECLIENT, OnBrowseclient)
	ON_BN_CLICKED(IDC_BROWSEMUL, OnBrowsemul)
	ON_BN_CLICKED(IDC_BROWSEPROFILE, OnBrowseprofile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingsPaths message handlers

HBRUSH CSettingsPaths::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	// TODO: Return a different brush if the default is not desired
	return ((CAxis2App*)AfxGetApp())->m_bkbrush;
}

BOOL CSettingsPaths::OnApply()
{
	// TODO: Add specialized code here and/or call the base class
	UpdateData(true);
	((CAxis2App*)AfxGetApp())->PutRegistryString("Default Client", m_csClientPath);
	((CAxis2App*)AfxGetApp())->PutRegistryString("Default MulPath", m_csMulPath);
	((CAxis2App*)AfxGetApp())->PutRegistryString("Default ProfilePath", m_csProfilePath);
	((CAxis2App*)AfxGetApp())->PutRegistryString("Last Profile Loaded", m_csLastProfile);
	((CAxis2App*)AfxGetApp())->PutRegistryString("Default Profile", m_csDefaultProfile);

	csUOPath = m_csClientPath;
	csMulPath = m_csMulPath;
	csProfilePath = m_csProfilePath;

	return CPropertyPage::OnApply();
}

BOOL CSettingsPaths::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO: Add extra initialization here
	m_csClientPath = ((CAxis2App*)AfxGetApp())->GetRegistryString("Default Client");
	m_csMulPath = ((CAxis2App*)AfxGetApp())->GetRegistryString("Default MulPath");
	m_csProfilePath = ((CAxis2App*)AfxGetApp())->GetRegistryString("Default ProfilePath");
	m_csLastProfile = ((CAxis2App*)AfxGetApp())->GetRegistryString("Last Profile Loaded");
	m_csDefaultProfile = ((CAxis2App*)AfxGetApp())->GetRegistryString("Default Profile");

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSettingsPaths::OnBrowseclient()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(true, "exe", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Executable Files (*.exe)|*.exe|All Files (*.*)|*.*||");
	if ( dlg.DoModal() == IDOK )
	{
		SetDlgItemText(IDC_CLIENTPATH, dlg.GetPathName());
	}
}

void CSettingsPaths::OnBrowsemul()
{
	// TODO: Add your control notification handler code here
	char path[MAX_PATH];
	if ( GetPathDlg(this->m_hWnd, path, "Select the directory where your UO mul files are located") )
	{
		SetDlgItemText(IDC_MULPATH, path);
	}
}

void CSettingsPaths::OnBrowseprofile()
{
	// TODO: Add your control notification handler code here
	char path[MAX_PATH];
	if ( GetPathDlg(this->m_hWnd, path, "Select the directory where your Axis profiles are located") )
	{
		SetDlgItemText(IDC_PROFILEPATH, path);
	}
}