// RemoteConsoleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Axis2.h"
#include "RemoteConsoleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRemoteConsoleDlg

IMPLEMENT_DYNCREATE(CRemoteConsoleDlg, CPropertySheet)

CRemoteConsoleDlg::CRemoteConsoleDlg(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CRemoteConsoleDlg::CRemoteConsoleDlg(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CRemoteConsoleDlg::~CRemoteConsoleDlg()
{
}


BEGIN_MESSAGE_MAP(CRemoteConsoleDlg, CPropertySheet)
	//{{AFX_MSG_MAP(CRemoteConsoleDlg)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRemoteConsoleDlg message handlers

HBRUSH CRemoteConsoleDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertySheet::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	// TODO: Return a different brush if the default is not desired
	return ((CAxis2App*)AfxGetApp())->m_bkbrush;
}

BOOL CRemoteConsoleDlg::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	// TODO: Add extra initialization here

	return bResult;
}