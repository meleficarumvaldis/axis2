// AxisLog.cpp: implementation of the CAxisLog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Axis2.h"
#include "AxisLog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAxisLog::CAxisLog()
{
	m_iVerbosity = 0;
	m_csLogName = "Axis.log";
	m_csSeperator = "*******************************************************************************";
	m_dwOptions = LOG_TEXT;
	m_pLogFile = NULL;
}

CAxisLog::~CAxisLog()
{
	if ( m_pLogFile )
	{
		m_pLogFile->Close();
		delete m_pLogFile;
	}
}

//////////////////////////////////////////////////////////////////////

void CAxisLog::Add(int iType, CString csMessage)
{
	// Get the time and format it
	CTime time = CTime::GetCurrentTime();
	CString csTime = time.Format( "%H:%M:%S" );

	CString csType;
	switch ( iType )
	{
	case 0:
		csType = "Status";
		break;
	case 1:
		csType = "Warning";
		break;
	case 2:
		csType = "Error";
		break;
	default:
		csType = "Debug";
		break;
	}

	// Add the line to the log file
	if ( m_dwOptions & LOG_TEXT )
	{
		if ( !m_pLogFile )
		{
			m_pLogFile = new CStdioFile;
			if ( !m_pLogFile->Open(m_csLogName, CFile::modeWrite | CFile::modeCreate | CFile::modeNoTruncate | CFile::shareDenyNone | CFile::typeText ) )
			{
				delete m_pLogFile;
				m_pLogFile = NULL;
				//AfxMessageBox("Unable to open log file for writing.");
				return;
			}
		}
		m_pLogFile->SeekToEnd();
		m_pLogFile->WriteString( CFMsg("%1 (%2): %3\n", csTime, csType, csMessage) );
		m_pLogFile->Flush();
	}

	CLogArray * pLog = new CLogArray;
	pLog->Add(csTime);
	pLog->Add(csType);
	pLog->Add(csMessage);

	if (((CAxis2App*)AfxGetApp())->m_pcppAxisLogTab)
	{
		CLogTab * pLogTab = (CLogTab *)((CAxis2App*)AfxGetApp())->m_pcppAxisLogTab->m_dcCurrentPage;
		pLogTab->AddLine(pLog);
	}

	((CAxis2App*)AfxGetApp())->m_olLog.AddTail(pLog);
}

void CAxisLog::Clear()
{
	if ( m_pLogFile )
	{
		m_pLogFile->Close();
		delete m_pLogFile;
		m_pLogFile = NULL;
	}
	if ( remove(m_csLogName) != 0 )
	{
		// error deleting file
	}
}