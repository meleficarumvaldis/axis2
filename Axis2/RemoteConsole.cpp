// RemoteConsole.cpp: implementation of the CRemoteConsole class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Axis2.h"
#include "RemoteConsole.h"
#include "RemoteConsoleLoginDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRemoteConsole::CRemoteConsole()
{
	m_pSocket = NULL;
	m_pLoginDlg = NULL;
}

CRemoteConsole::~CRemoteConsole()
{

}

//////////////////////////////////////////////////////////////////////

void CRemoteConsole::Login()
{
	if ( m_pLoginDlg )
		delete m_pLoginDlg;
	m_pLoginDlg = new CRemoteConsoleLoginDlg;
	if ( m_pLoginDlg->DoModal() == IDOK )
	{
		m_pSocket = new CRemoteSocket(this);
		m_pSocket->Create();
		if ( !m_pSocket->Connect(m_pLoginDlg->m_csAddress, m_pLoginDlg->m_iPort) )
		{
			if ( GetLastError() != WSAEWOULDBLOCK )
			{
				((CAxis2App*)AfxGetApp())->m_log.Add(2, CMsg(IDS_CONNECT_ERROR));
				Logout();
				return;
			}
		}
		((CAxis2App*)AfxGetApp())->m_log.Add(0, CMsg(IDS_CONNECT_SUCCESS));
	}
	delete m_pLoginDlg;
	m_pLoginDlg = NULL;
}

void CRemoteConsole::Logout()
{
	if ( m_pSocket )
	{
		m_pSocket->Close();
		delete m_pSocket;
		m_pSocket = NULL;
	}
	((CAxis2App*)AfxGetApp())->m_log.Add(0, CMsg(IDS_DISCONNECTED));
}

void CRemoteConsole::OnConnect()
{
	CString csBuffer;
	csBuffer.Format("%s\n%s\n", m_pLoginDlg->m_csUsername, m_pLoginDlg->m_csPassword);
	m_pSocket->Send(csBuffer.GetBuffer(csBuffer.GetLength()), csBuffer.GetLength());
}

void CRemoteConsole::Send(CString csMessage)
{
	if (m_pSocket)
	{
		csMessage += "\n";
		m_pSocket->Send(csMessage.GetBuffer(csMessage.GetLength()), csMessage.GetLength());
	}
}