// ClientInfo.cpp: implementation of the CClientInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Axis2.h"
#include "ClientInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClientInfo::CClientInfo()
{

}

CClientInfo::~CClientInfo()
{

}

bool CClientInfo::SetClientBuffer()
{
	if ( m_ClientFile.Open(csUOPath, CFile::modeRead) )
	{
		m_ClientFile.Read(&m_cClientBuffer, 4096);
		m_ClientFile.Close();
		return true;
	}
	else
	{
		((CAxis2App*)AfxGetApp())->m_log.Add(1,CMsg("IDS_CLIENT_NOTOPEN"), csUOPath);
		return false;
	}
}

void CClientInfo::DeleteClientBuffer()
{
	memset(&m_cClientBuffer, 0x00, 4096);
}

CString CClientInfo::GetClientVersion()
{
	CString csVersion;
	csVersion.Format("%d.%d.%d.%d", m_cClientBuffer[4083], m_cClientBuffer[4082], m_cClientBuffer[4081], m_cClientBuffer[4080]);
	return csVersion;
}

bool CClientInfo::SetClientVersion(CString csVersion)
{
	return true;
}

bool CClientInfo::SaveClient()
{
	return true;
}