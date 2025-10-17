// ScriptObjects.cpp: implementation of the CScriptObjects class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Axis2.h"
#include "ScriptObjects.h"
#include ".\scriptobjects.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CScriptObjects::CScriptObjects()
{

}

CScriptObjects::~CScriptObjects()
{

}

bool CScriptObjects::LoadProfile(CString csProfile)
{
	try
	{
		CString csFile;
		csFile.Format("%s\\%s", csProfilePath, csProfile);
		CStdioFile pFile;
		if ( !pFile.Open(csFile, CFile::modeRead | CFile::shareDenyNone) )
		{
			((CAxis2App*)AfxGetApp())->m_log.Add(1,CFMsg(CMsg("IDS_WARNING_NOOPEN"), csFile));
			return false;
		}

		BOOL bStatus = TRUE;
		while ( bStatus )
		{
			CString csLine;
			bStatus = pFile.ReadString(csLine);

			if ( !bStatus )
				break;

			if ( csLine.Find("[") == 0 )
			{
				while ( bStatus )
				{
					if ( !bStatus )
						break;
					if ( csLine.Find("[") == 0 )
					{
						CString csKey = csLine.Mid(1);
						csKey = csKey.SpanExcluding("]");
						CString csIndex;
						if ( csKey.Find(" ") != -1 )
							csIndex = csKey.Mid(csKey.Find(" ") + 1);
						CString csType = csKey.SpanExcluding(" ");
						int resource = FindTable(csType, pIniBlocks, PROFILE_QTY);

						switch (resource)
						{
						case PROFILE_DEF:
							{
								while ( bStatus )
								{
									bStatus = pFile.ReadString(csLine);
									if ( !bStatus )
										break;
									if ( csLine.Find("[") == 0 )
									{
										break;
									}
									csLine = csLine.SpanExcluding("//");
									csLine.Trim();
									if ( csLine != "" )
									{
										CSObject *pDef = new CSObject;
										pDef->m_csName = csLine.SpanExcluding(" \t=");
										pDef->m_csName.Trim();
										pDef->m_csID = csLine.Mid(pDef->m_csName.GetLength() + 1);
										pDef->m_csID.Trim();
										if( pDef->m_csID.Find(" \t="))
											pDef->m_csID = pDef->m_csID.Mid(pDef->m_csID.Find(" \t=") + 1);
										pDef->m_csID.Trim();

										m_aDefList.Add(pDef);
									}
								}
							}
							break;
						case PROFILE_ITEM:
							{
								while ( bStatus )
								{
									bStatus = pFile.ReadString(csLine);
									if ( !bStatus )
										break;
									if ( csLine.Find("[") == 0 )
									{
										break;
									}
									csLine = csLine.SpanExcluding("//");
									csLine.Trim();
									if ( csLine != "" )
									{
										CSObject *pItem = new CSObject;
										pItem->m_csID = csLine.SpanExcluding(",");
										pItem->m_csID.Trim();
										pItem->m_csName = csLine.Mid(pItem->m_csID.GetLength() + 1);
										pItem->m_csName.Trim();

										m_aItems.Add(pItem);
									}
								}
							}
							break;
						case PROFILE_NPC:
							{
								while ( bStatus )
								{
									bStatus = pFile.ReadString(csLine);
									if ( !bStatus )
										break;
									if ( csLine.Find("[") == 0 )
									{
										break;
									}
									csLine = csLine.SpanExcluding("//");
									csLine.Trim();
									if ( csLine != "" )
									{
										CSObject *pNPC = new CSObject;
										pNPC->m_csID = csLine.SpanExcluding(",");
										pNPC->m_csID.Trim();
										pNPC->m_csName = csLine.Mid(pNPC->m_csID.GetLength() + 1);
										pNPC->m_csName.Trim();

										m_aNPC.Add(pNPC);
									}
								}
							}
							break;
						case PROFILE_SPELL:
							{
								while ( bStatus )
								{
									bStatus = pFile.ReadString(csLine);
									if ( !bStatus )
										break;
									if ( csLine.Find("[") == 0 )
									{
										break;
									}
									csLine = csLine.SpanExcluding("//");
									csLine.Trim();
									if ( csLine != "" )
									{
										CSpell *pSpell = new CSpell;
										pSpell->csMantra = csLine.SpanExcluding(",");
										pSpell->csMantra.Trim();
										pSpell->csName = csLine.Mid(pSpell->csMantra.GetLength() + 1);
										pSpell->csName.Trim();

										m_aSpells.Add(pSpell);
									}
								}
							}
							break;
						case PROFILE_GUMP:
							{
								while ( bStatus )
								{
									bStatus = pFile.ReadString(csLine);
									if ( !bStatus )
										break;
									if ( csLine.Find("[") == 0 )
									{
										break;
									}
									csLine = csLine.SpanExcluding("//");
									csLine.Trim();
									if ( csLine != "" )
									{
										CGump *pGump = new CGump;
										pGump->csName = csLine.SpanExcluding(",");
										pGump->csName.Trim();
										pGump->iGumpID = atoi(csLine.Mid(pGump->csName.GetLength() + 1));

										m_aGumps.Add(pGump);
									}
								}
							}
							break;
						case PROFILE_SKILL:
							{
								while ( bStatus )
								{
									bStatus = pFile.ReadString(csLine);
									if ( !bStatus )
										break;
									if ( csLine.Find("[") == 0 )
									{
										break;
									}
									csLine = csLine.SpanExcluding("//");
									csLine.Trim();
									if ( csLine != "" )
									{
										CSkill *pSkill = new CSkill;
										pSkill->csName = csLine.SpanExcluding(",");
										pSkill->csName.Trim();
										pSkill->iSkillID = atoi(csLine.Mid(pSkill->csName.GetLength() + 1));

										m_aSkills.Add(pSkill);
									}
								}
							}
							break;
						case PROFILE_LAUNCH:
							{
								while ( bStatus )
								{
									bStatus = pFile.ReadString(csLine);
									if ( !bStatus )
										break;
									if ( csLine.Find("[") == 0 )
									{
										break;
									}
									csLine = csLine.SpanExcluding("//");
									csLine.Trim();
									if ( csLine != "" )
									{
										CProgram *pProgram = new CProgram;
										pProgram->csName = csLine.SpanExcluding(",");
										pProgram->csName.Trim();
										pProgram->csPath = csLine.Mid(pProgram->csName.GetLength() + 1);
										pProgram->csPath.Trim();

										m_aLaunch.Add(pProgram);
									}
								}
							}
							break;
						case PROFILE_DOOR:
							{
								while ( bStatus )
								{
									bStatus = pFile.ReadString(csLine);
									if ( !bStatus )
										break;
									if ( csLine.Find("[") == 0 )
									{
										break;
									}
									csLine = csLine.SpanExcluding("//");
									csLine.Trim();
									if ( csLine != "" )
									{
										CDoor *pDoor = new CDoor;
										pDoor->csName = csLine.SpanExcluding(",");
										pDoor->csName.Trim();
										CString csTemp = csLine.Mid(pDoor->csName.GetLength() + 1);
										pDoor->csOpen = csTemp.SpanExcluding(",");
										pDoor->csOpen.Trim();
										pDoor->csClosed = csTemp.Mid(pDoor->csOpen.GetLength() + 1);
										pDoor->csClosed.Trim();

										m_aDoors.Add(pDoor);
									}
								}
							}
							break;
						case PROFILE_REMINDER:
							{
								while ( bStatus )
								{
									bStatus = pFile.ReadString(csLine);
									if ( !bStatus )
										break;
									if ( csLine.Find("[") == 0 )
									{
										break;
									}
									csLine = csLine.SpanExcluding("//");
									csLine.Trim();
									if ( csLine != "" )
									{
										CReminder *pReminder = new CReminder;
										pReminder->csTitle = csLine.SpanExcluding(",");
										pReminder->csTitle.Trim();
										CString csTemp = csLine.Mid(pReminder->csTitle.GetLength() + 1);
										pReminder->csMessage = csTemp.SpanExcluding(",");
										pReminder->csMessage.Trim();
										CString csTime = csTemp.Mid(pReminder->csMessage.GetLength() + 1);
										csTime.Trim();
										pReminder->iHour = atoi(csTime.SpanExcluding(":"));
										pReminder->iMin = atoi(csTime.Mid(csTime.Find(":")+1));

										m_aReminders.Add(pReminder);
									}
								}
							}
							break;
						case PROFILE_SPAWNCHAR:
							{
								while ( bStatus )
								{
									bStatus = pFile.ReadString(csLine);
									if ( !bStatus )
										break;
									if ( csLine.Find("[") == 0 )
									{
										break;
									}
									csLine = csLine.SpanExcluding("//");
									csLine.Trim();
									if ( csLine != "" )
									{
										m_asaSPAWNchar.Add(csLine);
									}
								}
							}
							break;
						case PROFILE_SPAWNITEM:
							{
								while ( bStatus )
								{
									bStatus = pFile.ReadString(csLine);
									if ( !bStatus )
										break;
									if ( csLine.Find("[") == 0 )
									{
										break;
									}
									csLine = csLine.SpanExcluding("//");
									csLine.Trim();
									if ( csLine != "" )
									{
										m_asaSPAWNitem.Add(csLine);
									}
								}
							}
							break;
						default:
							((CAxis2App*)AfxGetApp())->m_log.Add(1,CFMsg(CMsg("IDS_WARNING_UNKNOWN_SECTION"), csLine, csFile));
							bStatus = pFile.ReadString(csLine);
							break;
						}
					}
					else
					{
						bStatus = pFile.ReadString(csLine);
					}
				}
			}
		}
	}
	catch (CFileException *e)
	{
		((CAxis2App*)AfxGetApp())->m_log.Add(1,CFMsg(CMsg("IDS_WARNING_EXCEPTION_FILE"), e->m_strFileName, e->m_cause));
		e->Delete();
	}
	return true;
}

void CScriptObjects::UnloadProfile()
{
	for ( int i = 0; i < m_aDefList.GetSize(); i++ )
	{
		CSObject * pDef = (CSObject *) m_aDefList.GetAt(i);
		delete pDef;
	}
	m_aDefList.RemoveAll();

	for ( i = 0; i < m_aItems.GetSize(); i++ )
	{
		CSObject * pItem = (CSObject *) m_aItems.GetAt(i);
		delete pItem;
	}
	m_aItems.RemoveAll();

	for ( i = 0; i < m_aNPC.GetSize(); i++ )
	{
		CSObject * pNPC = (CSObject *) m_aNPC.GetAt(i);
		delete pNPC;
	}
	m_aNPC.RemoveAll();

	for ( i = 0; i < m_aSpells.GetSize(); i++ )
	{
		CSpell * pSpell = (CSpell *) m_aSpells.GetAt(i);
		delete pSpell;
	}
	m_aSpells.RemoveAll();

	for ( i = 0; i < m_aGumps.GetSize(); i++ )
	{
		CGump * pGump = (CGump *) m_aGumps.GetAt(i);
		delete pGump;
	}
	m_aGumps.RemoveAll();

	for ( i = 0; i < m_aSkills.GetSize(); i++ )
	{
		CSkill * pSkill = (CSkill *) m_aSkills.GetAt(i);
		delete pSkill;
	}
	m_aSkills.RemoveAll();

	for ( i = 0; i < m_aLaunch.GetSize(); i++ )
	{
		CProgram * pProgram = (CProgram *) m_aLaunch.GetAt(i);
		delete pProgram;
	}
	m_aLaunch.RemoveAll();

	for ( i = 0; i < m_aDoors.GetSize(); i++ )
	{
		CDoor * pDoor = (CDoor *) m_aDoors.GetAt(i);
		delete pDoor;
	}
	m_aDoors.RemoveAll();

	for ( i = 0; i < m_aReminders.GetSize(); i++ )
	{
		CReminder * pReminder = (CReminder *) m_aReminders.GetAt(i);
		delete pReminder;
	}
	m_aReminders.RemoveAll();

	m_asaSPAWNchar.RemoveAll();
	m_asaSPAWNitem.RemoveAll();
}

int CScriptObjects::FindDef(CString csDef)
{
	for ( int i = 0; i < m_aDefList.GetSize(); i++ )
	{
		CSObject * pDef = (CSObject *) m_aDefList.GetAt(i);
		if (pDef->m_csName == csDef)
			return i;
	}
	return -1;
}

int CDefArray::Find(WORD wVal)
{
	for (int i = 0; i < this->GetSize(); i++)
	{
		CDefObj *pDef = (CDefObj *)this->GetAt(i);
		if (pDef->wValue == wVal)
			return i;
	}
	return -1;
}

void CDefArray::Insert(CDefObj *pNew)
{
	if (this->GetSize() == 0)
	{
		this->Add(pNew);
		return;
	}
	for (int i = 0; i < this->GetSize(); i++)
	{
		CDefObj *pDef = (CDefObj *)this->GetAt(i);
		if (pNew->wValue < pDef->wValue)
		{
			this->InsertAt(i, pNew);
			return;
		}
	}
	this->Add(pNew);
}