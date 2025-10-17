// LightWizard.cpp : implementation file
//

#include "stdafx.h"
#include "Axis2.h"
#include "LightWizard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLightWizard dialog


CLightWizard::CLightWizard(CWnd* pParent /*=NULL*/)
	: CDialog(CLightWizard::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLightWizard)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT}


void CLightWizard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLightWizard)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLightWizard, CDialog)
	//{{AFX_MSG_MAP(CLightWizard)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLightWizard message handlers

void CLightWizard::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	((CAxis2App*)AfxGetApp())->m_dlgLightWiz = NULL;

	CDialog::OnClose();
}

HBRUSH CLightWizard::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	// TODO: Return a different brush if the default is not desired
	return ((CAxis2App*)AfxGetApp())->m_bkbrush;
}