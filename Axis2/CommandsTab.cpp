// CommandsTab.cpp : implementation file
//

#include "stdafx.h"
#include "Axis2.h"
#include "CommandsTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommandsTab property page

IMPLEMENT_DYNCREATE(CCommandsTab, CPropertyPage)

CCommandsTab::CCommandsTab() : CPropertyPage(CCommandsTab::IDD)
{
	//{{AFX_DATA_INIT(CCommandsTab)
	m_csCommand = _T("");
	//}}AFX_DATA_INIT
	m_iHistory = 0;
}

CCommandsTab::~CCommandsTab()
{
}

void CCommandsTab::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommandsTab)
	DDX_Control(pDX, IDC_COMMAND, m_Command);
	DDX_Control(pDX, IDC_COMMANDLIST, m_CommandList);
	DDX_Text(pDX, IDC_COMMAND, m_csCommand);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCommandsTab, CPropertyPage)
	//{{AFX_MSG_MAP(CCommandsTab)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_WM_CTLCOLOR()
	ON_LBN_DBLCLK(IDC_COMMANDLIST, OnDblclkCommandlist)
	ON_EN_VSCROLL(IDC_COMMAND, OnVscrollCommand)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_EN_CHANGE(IDC_COMMAND, OnChangeCommand)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommandsTab message handlers

/**
 * @brief Sendet einen Befehl an die Remote-Konsole.
 * Formatiert den Befehl mit dem Befehlspräfix und sendet ihn.
 */
void CCommandsTab::OnSend()
{
	UpdateData(true);
	CString csCmd;
	csCmd.Format("%s%s", static_cast<CAxis2App*>(AfxGetApp())->m_csCommandPrefix, m_csCommand);

	if (static_cast<CAxis2App*>(AfxGetApp())->m_pRConsole)
		static_cast<CAxis2App*>(AfxGetApp())->m_pRConsole->Send(csCmd);

	m_saHistory.Add(m_csCommand);
	m_iHistory = m_saHistory.GetUpperBound();

	m_Command.SetWindowText("");
}

BOOL CCommandsTab::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_dcPropertyPage = static_cast<CAxis2App*>(AfxGetApp())->m_pcppCommandsTab;

	if (m_dcCurrentPage == this)
		static_cast<CAxis2App*>(AfxGetApp())->m_pcppCommandsTab->m_dcCurrentPage = this;

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
HBRUSH CCommandsTab::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255, 255, 255));

	return static_cast<CAxis2App*>(AfxGetApp())->m_bkbrush;
}

void CCommandsTab::OnDblclkCommandlist()
{
	// TODO: Add your control notification handler code here
	int iSel = m_CommandList.GetCurSel();
	if ( iSel == -1 )
		return;

	CString csCmd;
	m_CommandList.GetText(iSel, csCmd);

	m_Command.SetWindowText(csCmd);
}

BOOL CCommandsTab::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_UP)
		{
			if ( m_iHistory > 0 )
				m_iHistory--;
			m_Command.SetWindowText(m_saHistory.GetAt(m_iHistory));
		}
		if (pMsg->wParam == VK_DOWN)
		{
			if ( m_iHistory < m_saHistory.GetUpperBound() )
				m_iHistory++;
			m_Command.SetWindowText(m_saHistory.GetAt(m_iHistory));
		}
		if (pMsg->wParam == VK_RETURN)
		{
			OnSend();
		}
	}

	return CPropertyPage::PreTranslateMessage(pMsg);
}

void CCommandsTab::OnVscrollCommand()
{
	// TODO: Add your control notification handler code here
}

void CCommandsTab::OnKeydown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	CPropertyPage::OnKeydown(nChar, nRepCnt, nFlags);
}

void CCommandsTab::OnKeyup(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	CPropertyPage::OnKeyup(nChar, nRepCnt, nFlags);
}

void CCommandsTab::OnChangeCommand()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	
}

/**
 * @brief Speichert die anfänglichen Positionen und Größen aller Steuerelemente auf der Registerkarte.
 */
void CCommandsTab::SaveInitialControlRects()
{
    for (CWnd* pChild = GetWindow(GW_CHILD); pChild != nullptr; pChild = pChild->GetNextWindow())
    {
        CRect rect;
        pChild->GetWindowRect(&rect);
        ScreenToClient(&rect);
        m_initialRects[pChild->GetDlgCtrlID()] = rect;
    }
}

/**
 * @brief Wird aufgerufen, wenn die Größe der Registerkarte geändert wird.
 * Passt die Position und Größe der Steuerelemente dynamisch an.
 */
void CCommandsTab::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

    if (m_initialRects.empty())
        return;

	// Das Eingabefeld und die Befehlsliste anpassen
    CWnd* pCommandList = GetDlgItem(IDC_COMMANDLIST);
    CWnd* pCommand = GetDlgItem(IDC_COMMAND);
    CWnd* pSend = GetDlgItem(IDC_SEND);

    if (pCommandList && pCommand && pSend)
    {
        CRect commandListRect = m_initialRects[IDC_COMMANDLIST];
        CRect commandRect = m_initialRects[IDC_COMMAND];
        CRect sendRect = m_initialRects[IDC_SEND];

        // Befehlsliste in der Höhe anpassen
        commandListRect.bottom = cy - (commandRect.Height() + 20);
        commandListRect.right = cx - 10;
        pCommandList->MoveWindow(commandListRect);

        // Eingabefeld und Senden-Button nach unten verschieben
        commandRect.top = commandListRect.bottom + 10;
        commandRect.bottom = commandRect.top + commandRect.Height();
        commandRect.right = cx - (sendRect.Width() + 20);
        pCommand->MoveWindow(commandRect);

        sendRect.top = commandRect.top;
        sendRect.left = commandRect.right + 10;
        sendRect.right = sendRect.left + sendRect.Width();
        pSend->MoveWindow(sendRect);
    }
}