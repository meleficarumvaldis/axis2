// GeneralTab.cpp : implementation file
//

#include "stdafx.h"
#include "Axis2.h"
#include "GeneralTab.h"
#include "Axis2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGeneralTab property page

IMPLEMENT_DYNCREATE(CGeneralTab, CPropertyPage)

CGeneralTab::CGeneralTab() : CPropertyPage(CGeneralTab::IDD)
{
	//{{AFX_DATA_INIT(CGeneralTab)
	//}}AFX_DATA_INIT
}

CGeneralTab::~CGeneralTab()
{
}

void CGeneralTab::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGeneralTab)
	DDX_Control(pDX, IDC_CLIENT, m_Client);
	DDX_Control(pDX, IDC_PROFILE, m_Profile);
	DDX_Control(pDX, IDC_MULFILES, m_MulFiles);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGeneralTab, CPropertyPage)
	//{{AFX_MSG_MAP(CGeneralTab)
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGeneralTab message handlers

/**
 * @brief Speichert die anfänglichen Positionen und Größen aller Steuerelemente auf der Registerkarte.
 * Diese Funktion durchläuft alle untergeordneten Fenster (Steuerelemente) des Dialogs und
 * speichert deren ursprüngliches Rechteck (Position und Größe) in der m_initialRects-Map.
 * Dies ist die Grundlage für die dynamische Größenanpassung.
 */
void CGeneralTab::SaveInitialControlRects()
{
    for (CWnd* pChild = GetWindow(GW_CHILD); pChild != nullptr; pChild = pChild->GetNextWindow())
    {
        CRect rect;
        pChild->GetWindowRect(&rect);
        ScreenToClient(&rect);
        m_initialRects[pChild->GetDlgCtrlID()] = rect;
    }
}

BOOL CGeneralTab::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	// TODO: Add extra initialization here
	m_dcPropertyPage = ((CAxis2App*)AfxGetApp())->m_pcppGeneralTab;

	if (m_dcCurrentPage == this)
		((CAxis2App*)AfxGetApp())->m_pcppGeneralTab->m_dcCurrentPage = this;

	m_Client.SetWindowText(csUOPath);
	m_Profile.SetWindowText(csProfilePath);
	m_MulFiles.SetWindowText(csMulPath);

    CRect rect;
    GetClientRect(&rect);
    m_initialWidth = rect.Width();

    SaveInitialControlRects();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/**
 * @brief Wird aufgerufen, um die Farbe für Steuerelemente festzulegen.
 * Setzt den Hintergrundmodus auf transparent und die Textfarbe auf Weiß.
 * @param pDC Zeiger auf den Gerätekontext.
 * @param pWnd Zeiger auf das Fenster.
 * @param nCtlColor Typ des Steuerelements.
 * @return HBRUSH Handle zum Pinsel für den Hintergrund.
 */
HBRUSH CGeneralTab::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255, 255, 255));

	return static_cast<CAxis2App*>(AfxGetApp())->m_bkbrush;
}

/**
 * @brief Wird aufgerufen, wenn die Größe der Registerkarte geändert wird.
 * Passt die Position und Größe der Steuerelemente dynamisch an.
 * @param nType Typ der Größenänderung.
 * @param cx Neue Breite des Client-Bereichs.
 * @param cy Neue Höhe des Client-Bereichs.
 */
void CGeneralTab::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

    if (m_initialRects.empty())
        return;

	for (auto const& [id, initialRect] : m_initialRects)
	{
        CWnd* pWnd = GetDlgItem(id);
        if (pWnd)
        {
            CRect newRect = initialRect;

            // Horizontale Skalierung: Breite anpassen
            newRect.right = initialRect.right + (cx - m_initialWidth);

            pWnd->MoveWindow(newRect);
        }
	}
}