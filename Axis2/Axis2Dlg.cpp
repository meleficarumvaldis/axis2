// Axis2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Axis2.h"
#include "Axis2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAxis2Dlg

IMPLEMENT_DYNAMIC(CAxis2Dlg, CPropertySheet)

CAxis2Dlg::CAxis2Dlg(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CAxis2Dlg::CAxis2Dlg(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	EnableStackedTabs( false );
}

CAxis2Dlg::~CAxis2Dlg()
{
}


BEGIN_MESSAGE_MAP(CAxis2Dlg, CPropertySheet)
	//{{AFX_MSG_MAP(CAxis2Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_SETTINGS, OnOpenSettingsPage)
	ON_COMMAND(ID_PROFILES_OPENPROFILE, OnProfilesOpenprofile)
	ON_COMMAND(ID_PROFILES_UNLOAD, OnProfilesUnload)
	ON_COMMAND(ID_PROFILES_LOADDEFAULT, OnProfilesLoaddefault)
	ON_COMMAND(ID_PROFILES_LOADLASTPROFILE, OnProfilesLoadlastprofile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAxis2App message handlers

BOOL CAxis2Dlg::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	((CAxis2App*)AfxGetApp())->pDefMenu.LoadMenu(IDR_MENU1);
	SetMenu(&((CAxis2App*)AfxGetApp())->pDefMenu);
	
	// Load the current profile and set the menu accordingly
	((CAxis2App*)AfxGetApp())->UpdateProfileMenu();

	// Set the window's position
	CString csX, csY;
	csX = ((CAxis2App*)AfxGetApp())->m_csPosition.SpanExcluding(",");
	int x = atoi(csX);
	int y = 0;
	if ( ((CAxis2App*)AfxGetApp())->m_csPosition.Find(",") != -1 )
		csY = ((CAxis2App*)AfxGetApp())->m_csPosition.Mid(((CAxis2App*)AfxGetApp())->m_csPosition.Find(",") + 1 );
	y = atoi(csY);
	if ( x != 0 && y != 0 )
		SetWindowPos(NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	// Load the ToolBar and hide it
	CAxis2Dlg(CFMsg(CMsg("IDS_AXISTITLE"), ((CAxis2App*)AfxGetApp())->GetVersionTitle()));

	// Create Tray Icon
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = m_hWnd;
	nid.uID = 0;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_TRAY_NOTIFY;
	nid.hIcon = m_hIcon;
	CString csTip;
	csTip.Format("%s (%s)", ((CAxis2App*)AfxGetApp())->GetVersionTitle(), ((CAxis2App*)AfxGetApp())->m_csCurrentProfile);
	_tcscpy(nid.szTip, csTip);
	Shell_NotifyIcon(NIM_ADD, &nid);

	return bResult;
}

void CAxis2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CPropertySheet::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAxis2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPropertySheet::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAxis2Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAxis2Dlg::OnClose()
{
	if(((CAxis2App*)AfxGetApp())->m_dwSysClose)
		CPropertySheet::OnClose();
	else
		ShowWindow(SW_HIDE);
}

void CAxis2Dlg::OnDestroy()
{
	CPropertySheet::OnDestroy();

	// TODO: Add your message handler code here
	WINDOWPLACEMENT place;
	GetWindowPlacement(&place);

	HKEY hKey;
	DWORD dwDisp;
	LONG lStatus = RegCreateKeyEx( hRegLocation, REGKEY_AXIS, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dwDisp);
	if ( lStatus == ERROR_SUCCESS )
	{
		((CAxis2App*)AfxGetApp())->m_csPosition.Format("%ld,%ld", place.rcNormalPosition.left, place.rcNormalPosition.top);
		lStatus = RegSetValueEx( hKey, "Position", 0, REG_SZ, ((BYTE *) ((CAxis2App*)AfxGetApp())->m_csPosition.GetBuffer(((CAxis2App*)AfxGetApp())->m_csPosition.GetLength())), ((CAxis2App*)AfxGetApp())->m_csPosition.GetLength() );
		RegCloseKey(hKey);
	}

	Shell_NotifyIcon(NIM_DELETE, &nid);
}

void CAxis2Dlg::OnTrayNotify(WPARAM wParam, LPARAM lParam)
{
	UINT uID;
    UINT uMsg;

    uID = (UINT) wParam;
    uMsg = (UINT) lParam;

	if (uMsg == WM_LBUTTONDBLCLK)
	{
		ShowWindow(SW_SHOWNORMAL);
		SetForegroundWindow();
	}
	if (uMsg == WM_RBUTTONUP)
	{
		CMenu trayMenu;
		trayMenu.CreatePopupMenu();
		trayMenu.AppendMenu(MF_STRING, WM_TRAY_RESTORE, "Restore");
		trayMenu.AppendMenu(MF_STRING, WM_TRAY_CLOSE, "Close");

		CPoint pos;
		GetCursorPos(&pos);
		SetForegroundWindow();
		trayMenu.TrackPopupMenu(TPM_RIGHTBUTTON, pos.x, pos.y, this, NULL);
		PostMessage(WM_NULL, 0, 0);
	}
}

LRESULT CAxis2Dlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	if (message == WM_TRAY_NOTIFY)
		OnTrayNotify(wParam, lParam);

	return CPropertySheet::WindowProc(message, wParam, lParam);
}

BOOL CAxis2Dlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	if (wParam == WM_TRAY_RESTORE)
	{
		ShowWindow(SW_SHOWNORMAL);
		SetForegroundWindow();
	}
	if (wParam == WM_TRAY_CLOSE)
	{
		CPropertySheet::OnClose();
	}

	return CPropertySheet::OnCommand(wParam, lParam);
}

void CAxis2Dlg::OnOpenSettingsPage(int iStartPage)
{
	CSettingsDlg dlg(CMsg("IDS_SETTINGS"));
	dlg.AddPage(((CAxis2App*)AfxGetApp())->m_pcppSetGeneral);
	dlg.AddPage(((CAxis2App*)AfxGetApp())->m_pcppSetPaths);
	dlg.AddPage(((CAxis2App*)AfxGetApp())->m_pcppSetItem);
	dlg.AddPage(((CAxis2App*)AfxGetApp())->m_pcppSetTravel);
	dlg.AddPage(((CAxis2App*)AfxGetApp())->m_pcppSetSpawn);
	dlg.AddPage(((CAxis2App*)AfxGetApp())->m_pcppSetOverridePaths);

	if (iStartPage)
		dlg.SetActivePage(iStartPage);

	if (dlg.DoModal() == IDOK)
	{
		((CAxis2App*)AfxGetApp())->InitializeMulPaths();
		((CAxis2App*)AfxGetApp())->UnLoadBodyDef();
		((CAxis2App*)AfxGetApp())->UnLoadBodyConvert();
		((CAxis2App*)AfxGetApp())->UnLoadHues();
		((CAxis2App*)AfxGetApp())->UnLoadSounds();
		((CAxis2App*)AfxGetApp())->UnLoadMusic();
		((CAxis2App*)AfxGetApp())->LoadBodyDef();
		((CAxis2App*)AfxGetApp())->LoadBodyConvert();
		((CAxis2App*)AfxGetApp())->LoadHues();
		((CAxis2App*)AfxGetApp())->LoadSounds();
		((CAxis2App*)AfxGetApp())->LoadMusic();
	}
}

void CAxis2Dlg::OnProfilesOpenprofile()
{
	// TODO: Add your command handler code here
	if (((CAxis2App*)AfxGetApp())->m_dlgProfile)
		delete ((CAxis2App*)AfxGetApp())->m_dlgProfile;
	((CAxis2App*)AfxGetApp())->m_dlgProfile = new CProfileDLG;
	((CAxis2App*)AfxGetApp())->m_dlgProfile->Create(IDD_PROFILE_DLG);
	((CAxis2App*)AfxGetApp())->m_dlgProfile->ShowWindow(SW_SHOWNORMAL);
}

void CAxis2Dlg::OnProfilesUnload()
{
	// TODO: Add your command handler code here
	((CAxis2App*)AfxGetApp())->m_pScripts->UnloadProfile();
	((CAxis2App*)AfxGetApp())->LoadIni(1);
	((CAxis2App*)AfxGetApp())->LoadIni(2);
	((CAxis2App*)AfxGetApp())->m_csCurrentProfile = CMsg(IDS_NONE);
	((CAxis2App*)AfxGetApp())->UpdateProfileMenu();
	((CAxis2App*)AfxGetApp())->UpdateProfileSettings();
}

void CAxis2Dlg::OnProfilesLoaddefault()
{
	// TODO: Add your command handler code here
	((CAxis2App*)AfxGetApp())->m_pScripts->UnloadProfile();
	((CAxis2App*)AfxGetApp())->LoadIni(1);
	((CAxis2App*)AfxGetApp())->LoadIni(2);
	((CAxis2App*)AfxGetApp())->m_csCurrentProfile = ((CAxis2App*)AfxGetApp())->GetRegistryString("Default Profile");
	((CAxis2App*)AfxGetApp())->m_pScripts->LoadProfile(((CAxis2App*)AfxGetApp())->m_csCurrentProfile);
	((CAxis2App*)AfxGetApp())->UpdateProfileMenu();
	((CAxis2App*)AfxGetApp())->UpdateProfileSettings();
}

void CAxis2Dlg::OnProfilesLoadlastprofile()
{
	// TODO: Add your command handler code here
	((CAxis2App*)AfxGetApp())->m_pScripts->UnloadProfile();
	((CAxis2App*)AfxGetApp())->LoadIni(1);
	((CAxis2App*)AfxGetApp())->LoadIni(2);
	((CAxis2App*)AfxGetApp())->m_csCurrentProfile = ((CAxis2App*)AfxGetApp())->GetRegistryString("Last Profile Loaded");
	((CAxis2App*)AfxGetApp())->m_pScripts->LoadProfile(((CAxis2App*)AfxGetApp())->m_csCurrentProfile);
	((CAxis2App*)AfxGetApp())->UpdateProfileMenu();
	((CAxis2App*)AfxGetApp())->UpdateProfileSettings();
}