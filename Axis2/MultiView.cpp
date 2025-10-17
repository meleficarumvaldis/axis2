// MultiView.cpp : implementation file
//

#include "stdafx.h"
#include "Axis2.h"
#include "MultiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultiView dialog


CMultiView::CMultiView(CWnd* pParent /*=NULL*/)
	: CDialog(CMultiView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMultiView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT}


void CMultiView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMultiView)
	DDX_Control(pDX, IDC_VIEWAREA, m_ViewArea);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMultiView, CDialog)
	//{{AFX_MSG_MAP(CMultiView)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiView message handlers

void CMultiView::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	((CAxis2App*)AfxGetApp())->m_dlgMultiView = NULL;

	CDialog::OnClose();
}

HBRUSH CMultiView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	// TODO: Return a different brush if the default is not desired
	return ((CAxis2App*)AfxGetApp())->m_bkbrush;
}

BOOL CMultiView::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	CRect rect;
	m_ViewArea.GetWindowRect(&rect);

	m_MultiMap.Create(NULL, NULL, WS_CHILD | WS_VISIBLE, rect, &m_ViewArea, 1);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}