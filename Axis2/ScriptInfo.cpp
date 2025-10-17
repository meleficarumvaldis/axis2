// ScriptInfo.cpp : implementation file
//

#include "stdafx.h"
#include "Axis2.h"
#include "ScriptInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScriptInfo dialog


CScriptInfo::CScriptInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CScriptInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScriptInfo)
	m_csAuthor = _T("");
	m_csDescription = _T("");
	m_csEmail = _T("");
	m_csVersion = _T("");
	m_csWebsite = _T("");
	//}}AFX_DATA_INIT}


void CScriptInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScriptInfo)
	DDX_Text(pDX, IDC_AUTHOR, m_csAuthor);
	DDX_Text(pDX, IDC_DESCRIPTION, m_csDescription);
	DDX_Text(pDX, IDC_EMAIL, m_csEmail);
	DDX_Text(pDX, IDC_VERSION, m_csVersion);
	DDX_Text(pDX, IDC_WEBSITE, m_csWebsite);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScriptInfo, CDialog)
	//{{AFX_MSG_MAP(CScriptInfo)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptInfo message handlers

HBRUSH CScriptInfo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	// TODO: Return a different brush if the default is not desired
	return ((CAxis2App*)AfxGetApp())->m_bkbrush;
}