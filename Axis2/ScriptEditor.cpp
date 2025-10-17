// ScriptEditor.cpp : implementation file
//

#include "stdafx.h"
#include "Axis2.h"
#include "ScriptEditor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScriptEditor

IMPLEMENT_DYNCREATE(CScriptEditor, CEditView)

CScriptEditor::CScriptEditor()
{
}

CScriptEditor::~CScriptEditor()
{
}


BEGIN_MESSAGE_MAP(CScriptEditor, CEditView)
	//{{AFX_MSG_MAP(CScriptEditor)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptEditor construction/destruction

BOOL CScriptEditor::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Add your specialized code here and/or call the base class

	return CEditView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CScriptEditor drawing

void CScriptEditor::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CScriptEditor printing

BOOL CScriptEditor::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CScriptEditor::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CScriptEditor::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CScriptEditor diagnostics

#ifdef _DEBUG
void CScriptEditor::AssertValid() const
{
	CEditView::AssertValid();
}

void CScriptEditor::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScriptEditor message handlers

HBRUSH CScriptEditor::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CEditView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	// TODO: Return a different brush if the default is not desired
	return ((CAxis2App*)AfxGetApp())->m_bkbrush;
}