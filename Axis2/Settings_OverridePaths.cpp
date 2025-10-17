// Settings_OverridePaths.cpp : implementation file
//

#include "stdafx.h"
#include "Axis2.h"
#include "Settings_OverridePaths.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingsOverridePaths property page

IMPLEMENT_DYNCREATE(CSettingsOverridePaths, CPropertyPage)

CSettingsOverridePaths::CSettingsOverridePaths() : CPropertyPage(CSettingsOverridePaths::IDD)
{
	//{{AFX_DATA_INIT(CSettingsOverridePaths)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT}


CSettingsOverridePaths::~CSettingsOverridePaths()
{
}

void CSettingsOverridePaths::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingsOverridePaths)
	DDX_Control(pDX, IDC_PATHLIST, m_PathList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingsOverridePaths, CPropertyPage)
	//{{AFX_MSG_MAP(CSettingsOverridePaths)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_SETP, OnSetp)
	ON_BN_CLICKED(IDC_RESETP, OnResetp)
	ON_LBN_SELCHANGE(IDC_PATHLIST, OnSelchangePathlist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingsOverridePaths message handlers

HBRUSH CSettingsOverridePaths::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	// TODO: Return a different brush if the default is not desired
	return ((CAxis2App*)AfxGetApp())->m_bkbrush;
}

BOOL CSettingsOverridePaths::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO: Add extra initialization here
	for ( int i = 0; i < VERFILE_QTY; i++ )
	{
		m_PathList.AddString(GetMulFileName(i));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CSettingsOverridePaths::OnApply()
{
	// TODO: Add specialized code here and/or call the base class

	return CPropertyPage::OnApply();
}

void CSettingsOverridePaths::OnSetp()
{
	// TODO: Add your control notification handler code here
	int iSel = m_PathList.GetCurSel();
	if ( iSel == -1 )
		return;

	CString csFileName;
	m_PathList.GetText(iSel, csFileName);

	CFileDialog dlg(true, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Mul Files (*.mul)|*.mul|UOP Files (*.uop)|*.uop|All Files (*.*)|*.*||");
	if ( dlg.DoModal() == IDOK )
	{
		((CAxis2App*)AfxGetApp())->PutRegistryString(csFileName, dlg.GetPathName(), hRegLocation, REGKEY_OVERRIDEPATH);
	}
}

void CSettingsOverridePaths::OnResetp()
{
	// TODO: Add your control notification handler code here
	int iSel = m_PathList.GetCurSel();
	if ( iSel == -1 )
		return;

	CString csFileName;
	m_PathList.GetText(iSel, csFileName);
	((CAxis2App*)AfxGetApp())->DeleteRegistryValue(csFileName, REGKEY_OVERRIDEPATH);
}

void CSettingsOverridePaths::OnSelchangePathlist()
{
	// TODO: Add your control notification handler code here
	int iSel = m_PathList.GetCurSel();
	if ( iSel == -1 )
		return;

	CString csFileName;
	m_PathList.GetText(iSel, csFileName);
	CString csPath = ((CAxis2App*)AfxGetApp())->GetRegistryString(csFileName, "", hRegLocation, REGKEY_OVERRIDEPATH);
	SetDlgItemText(IDC_CURRENTPATH, csPath);
}