// WorldMap.cpp : implementation file
//

#include "stdafx.h"
#include "Axis2.h"
#include "WorldMap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorldMap dialog


CWorldMap::CWorldMap(CWnd* pParent /*=NULL*/)
	: CDialog(CWorldMap::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWorldMap)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT}


void CWorldMap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWorldMap)
	DDX_Control(pDX, IDC_MAP, m_WorldMap);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWorldMap, CDialog)
	//{{AFX_MSG_MAP(CWorldMap)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorldMap message handlers

void CWorldMap::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	((CAxis2App*)AfxGetApp())->m_dlgWorldMap = NULL;

	CDialog::OnClose();
}

HBRUSH CWorldMap::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	// TODO: Return a different brush if the default is not desired
	CTravelTab * pTravel = (CTravelTab *)((CAxis2App*)AfxGetApp())->m_pcppTravelTab->m_dcCurrentPage;
	if (pWnd->GetDlgCtrlID() == IDC_MAP)
	{
		// TODO: Return a different brush if the default is not desired
		return CreateSolidBrush(((CAxis2App*)AfxGetApp())->m_dwSpawnBGColor);
	}

	return ((CAxis2App*)AfxGetApp())->m_bkbrush;
}

BOOL CWorldMap::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	m_WorldMap.SetMap(0);

	if (((CAxis2App*)AfxGetApp())->m_dwShowSpawnpoints)
	{
		CString csSpawn;
		for ( int i = 0; i < ((CAxis2App*)AfxGetApp())->m_pScripts->m_asaSPAWNchar.GetSize(); i++ )
		{
			csSpawn = ((CAxis2App*)AfxGetApp())->m_pScripts->m_asaSPAWNchar.GetAt(i);
			CString csX = csSpawn.SpanExcluding(",");
			csSpawn = csSpawn.Mid(csX.GetLength() + 1);
			CString csY = csSpawn.SpanExcluding(",");
			csSpawn = csSpawn.Mid(csY.GetLength() + 1);
			CString csMap = csSpawn.SpanExcluding(",");

			int x = atoi(csX);
			int y = atoi(csY);
			int map = atoi(csMap);

			int sSize = 4;

			m_WorldMap.AddDrawObject(x, y, 1, sSize, ((CAxis2App*)AfxGetApp())->m_dwNPCSpawnColor);
		}
		for ( int j = 0; j < ((CAxis2App*)AfxGetApp())->m_pScripts->m_asaSPAWNitem.GetSize(); j++ )
		{
			csSpawn = ((CAxis2App*)AfxGetApp())->m_pScripts->m_asaSPAWNitem.GetAt(j);
			CString csX = csSpawn.SpanExcluding(",");
			csSpawn = csSpawn.Mid(csX.GetLength() + 1);
			CString csY = csSpawn.SpanExcluding(",");
			csSpawn = csSpawn.Mid(csY.GetLength() + 1);
			CString csMap = csSpawn.SpanExcluding(",");

			int x = atoi(csX);
			int y = atoi(csY);
			int map = atoi(csMap);

			int sSize = 4;

			m_WorldMap.AddDrawObject(x, y, 1, sSize, ((CAxis2App*)AfxGetApp())->m_dwItemSpawnColor);
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}