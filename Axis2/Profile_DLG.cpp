// Profile_DLG.cpp : implementation file
//

#include "stdafx.h"
#include "Axis2.h"
#include "Profile_DLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProfileDLG dialog


CProfileDLG::CProfileDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CProfileDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProfileDLG)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT}


void CProfileDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProfileDLG)
	DDX_Control(pDX, IDC_PROFILELIST, m_ProfileList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProfileDLG, CDialog)
	//{{AFX_MSG_MAP(CProfileDLG)
	ON_WM_CTLCOLOR()
	ON_LBN_SELCHANGE(IDC_PROFILELIST, OnSelchangeProfilelist)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProfileDLG message handlers

HBRUSH CProfileDLG::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	// TODO: Return a different brush if the default is not desired
	return ((CAxis2App*)AfxGetApp())->m_bkbrush;
}

BOOL CProfileDLG::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	// Get a list of the profiles in the default profile directory
	CString csPath;
	csPath.Format("%s\\*.*", csProfilePath);

	CFileFind finder;
	BOOL bWorking = finder.FindFile(csPath);
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if ( !finder.IsDirectory() && !finder.IsDots() )
		{
			m_ProfileList.AddString(finder.GetFileName());
		}
   }

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CProfileDLG::OnSelchangeProfilelist()
{
	// TODO: Add your control notification handler code here
	int iSel = m_ProfileList.GetCurSel();
	if ( iSel == -1 )
		return;
	
	CString csProfile;
	m_ProfileList.GetText(iSel, csProfile);
	((CAxis2App*)AfxGetApp())->m_pScripts->UnloadProfile();
	((CAxis2App*)AfxGetApp())->m_pScripts->LoadProfile(csProfile);
	((CAxis2App*)AfxGetApp())->m_csCurrentProfile = csProfile;
	((CAxis2App*)AfxGetApp())->UpdateProfileMenu();
	((CAxis2App*)AfxGetApp())->UpdateProfileSettings();
}

void CProfileDLG::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	((CAxis2App*)AfxGetApp())->m_dlgProfile = NULL;
	CDialog::OnClose();
}