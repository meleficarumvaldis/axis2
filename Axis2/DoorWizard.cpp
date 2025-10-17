// DoorWizard.cpp : implementation file
//

#include "stdafx.h"
#include "Axis2.h"
#include "DoorWizard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDoorWizard dialog


CDoorWizard::CDoorWizard(CWnd* pParent /*=NULL*/)
	: CDialog(CDoorWizard::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDoorWizard)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDoorWizard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDoorWizard)
	DDX_Control(pDX, IDC_DOORLIST, m_DoorList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDoorWizard, CDialog)
	//{{AFX_MSG_MAP(CDoorWizard)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDoorWizard message handlers

void CDoorWizard::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	((CAxis2App*)AfxGetApp())->m_dlgDoorWiz = NULL;
	
	CDialog::OnClose();
}

BOOL CDoorWizard::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	for ( int i = 0; i < ((CAxis2App*)AfxGetApp())->m_pScripts->m_aDoors.GetSize(); i++ )
	{
		CDoor * pDoor = (CDoor *) ((CAxis2App*)AfxGetApp())->m_pScripts->m_aDoors.GetAt(i);
		m_DoorList.AddString(pDoor->csName);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CDoorWizard::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	// TODO: Return a different brush if the default is not desired
	return ((CAxis2App*)AfxGetApp())->m_bkbrush;
}