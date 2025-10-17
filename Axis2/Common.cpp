#include "stdafx.h"
#include "Axis2.h"
#include "Common.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

void StringTrim(CString * pString, char cTrim)
{
	if ( !pString )
		return;
	pString->TrimLeft(cTrim);
	pString->TrimRight(cTrim);
}

CString CMsg(int iID)
{
	CString csMessage;
	csMessage.LoadString(iID);
	return csMessage;
}

CString CFMsg(CString csMessage, CString csStr1, CString csStr2, CString csStr3, CString csStr4, CString csStr5, CString csStr6, CString csStr7, CString csStr8, CString csStr9, CString csStr10)
{
	csMessage.Replace("%1", csStr1);
	csMessage.Replace("%2", csStr2);
	csMessage.Replace("%3", csStr3);
	csMessage.Replace("%4", csStr4);
	csMessage.Replace("%5", csStr5);
	csMessage.Replace("%6", csStr6);
	csMessage.Replace("%7", csStr7);
	csMessage.Replace("%8", csStr8);
	csMessage.Replace("%9", csStr9);
	csMessage.Replace("%10", csStr10);
	return csMessage;
}

CString CFMsg(int iID, CString csStr1, CString csStr2, CString csStr3, CString csStr4, CString csStr5, CString csStr6, CString csStr7, CString csStr8, CString csStr9, CString csStr10)
{
	CString csMessage;
	csMessage.LoadString(iID);
	csMessage.Replace("%1", csStr1);
	csMessage.Replace("%2", csStr2);
	csMessage.Replace("%3", csStr3);
	csMessage.Replace("%4", csStr4);
	csMessage.Replace("%5", csStr5);
	csMessage.Replace("%6", csStr6);
	csMessage.Replace("%7", csStr7);
	csMessage.Replace("%8", csStr8);
	csMessage.Replace("%9", csStr9);
	csMessage.Replace("%10", csStr10);
	return csMessage;
}

UINT LoadProfileThread(LPVOID pParam)
{
	if ( (int)pParam == 1 )
		((CAxis2App*)AfxGetApp())->m_pScripts->LoadProfile(((CAxis2App*)AfxGetApp())->GetRegistryString("Default Profile"));
	else
		((CAxis2App*)AfxGetApp())->m_pScripts->LoadProfile(((CAxis2App*)AfxGetApp())->GetRegistryString("Last Profile Loaded"));

	((CAxis2App*)AfxGetApp())->UpdateProfileMenu();
	((CAxis2App*)AfxGetApp())->UpdateProfileSettings();
	return 0;
}

UINT Reminder(LPVOID pParam)
{
	while(1)
	{
		CTime time = CTime::GetCurrentTime();
		for ( int i = 0; i < ((CAxis2App*)AfxGetApp())->m_pScripts->m_aReminders.GetSize(); i++ )
		{
			CReminder * pReminder = (CReminder *) ((CAxis2App*)AfxGetApp())->m_pScripts->m_aReminders.GetAt(i);
			if (pReminder->iHour == time.GetHour() && pReminder->iMin == time.GetMinute())
			{
				CReminderDLG * pReminderDLG = new CReminderDLG;
				pReminderDLG->csMessage = pReminder->csMessage;
				pReminderDLG->csTitle = pReminder->csTitle;
				pReminderDLG->DoModal();
				delete pReminderDLG;
			}
		}
		Sleep(60000);
	}
	return 0;
}

CString GetMulFileName(int iIndex)
{
	CString csFileName;
	switch(iIndex)
	{
	case VERFILE_MAP0:
		csFileName = "map0.mul";
		break;
	case VERFILE_STAIDX0:
		csFileName = "staidx0.mul";
		break;
	case VERFILE_STATICS0:
		csFileName = "statics0.mul";
		break;
	case VERFILE_ARTIDX:
		csFileName = "artidx.mul";
		break;
	case VERFILE_ART:
		csFileName = "art.mul";
		break;
	case VERFILE_ANIM:
		csFileName = "anim.mul";
		break;
	case VERFILE_SOUNDIDX:
		csFileName = "soundidx.mul";
		break;
	case VERFILE_SOUND:
		csFileName = "sound.mul";
		break;
	case VERFILE_TEXIDX:
		csFileName = "texidx.mul";
		break;
	case VERFILE_TEXMAPS:
		csFileName = "texmaps.mul";
		break;
	case VERFILE_GUMPIDX:
		csFileName = "gumpidx.mul";
		break;
	case VERFILE_GUMPART:
		csFileName = "gumpart.mul";
		break;
	case VERFILE_MULTIIDX:
		csFileName = "multi.idx";
		break;
	case VERFILE_MULTIMAP:
		csFileName = "multi.mul";
		break;
	case VERFILE_SKILLSIDX:
		csFileName = "skills.idx";
		break;
	case VERFILE_SKILLS:
		csFileName = "skills.mul";
		break;
	case VERFILE_VERDATA:
		csFileName = "verdata.mul";
		break;
	case VERFILE_MAPDIF0:
		csFileName = "mapdif0.mul";
		break;
	case VERFILE_MAPDIFL0:
		csFileName = "mapdifl0.mul";
		break;
	case VERFILE_STADIF0:
		csFileName = "stadif0.mul";
		break;
	case VERFILE_STADIFI0:
		csFileName = "stadifi0.mul";
		break;
	case VERFILE_STADIFL0:
		csFileName = "stadifl0.mul";
		break;
	case VERFILE_TILEDATA:
		csFileName = "tiledata.mul";
		break;
	case VERFILE_ANIMDATA:
		csFileName = "animdata.mul";
		break;
	case VERFILE_HUES:
		csFileName = "hues.mul";
		break;
	case VERFILE_BODYDEF:
		csFileName = "body.def";
		break;
	case VERFILE_BODYCONVDEF:
		csFileName = "bodyconv.def";
		break;
	case VERFILE_MAP1:
		csFileName = "map1.mul";
		break;
	case VERFILE_STAIDX1:
		csFileName = "staidx1.mul";
		break;
	case VERFILE_STATICS1:
		csFileName = "statics1.mul";
		break;
	case VERFILE_MAPDIF1:
		csFileName = "mapdif1.mul";
		break;
	case VERFILE_MAPDIFL1:
		csFileName = "mapdifl1.mul";
		break;
	case VERFILE_STADIF1:
		csFileName = "stadif1.mul";
		break;
	case VERFILE_STADIFI1:
		csFileName = "stadifi1.mul";
		break;
	case VERFILE_STADIFL1:
		csFileName = "stadifl1.mul";
		break;
	case VERFILE_MAP2:
		csFileName = "map2.mul";
		break;
	case VERFILE_STAIDX2:
		csFileName = "staidx2.mul";
		break;
	case VERFILE_STATICS2:
		csFileName = "statics2.mul";
		break;
	case VERFILE_MAPDIF2:
		csFileName = "mapdif2.mul";
		break;
	case VERFILE_MAPDIFL2:
		csFileName = "mapdifl2.mul";
		break;
	case VERFILE_STADIF2:
		csFileName = "stadif2.mul";
		break;
	case VERFILE_STADIFI2:
		csFileName = "stadifi2.mul";
		break;
	case VERFILE_STADIFL2:
		csFileName = "stadifl2.mul";
		break;
	case VERFILE_MAP3:
		csFileName = "map3.mul";
		break;
	case VERFILE_STAIDX3:
		csFileName = "staidx3.mul";
		break;
	case VERFILE_STATICS3:
		csFileName = "statics3.mul";
		break;
	case VERFILE_MAPDIF3:
		csFileName = "mapdif3.mul";
		break;
	case VERFILE_MAPDIFL3:
		csFileName = "mapdifl3.mul";
		break;
	case VERFILE_STADIF3:
		csFileName = "stadif3.mul";
		break;
	case VERFILE_STADIFI3:
		csFileName = "stadifi3.mul";
		break;
	case VERFILE_STADIFL3:
		csFileName = "stadifl3.mul";
		break;
	case VERFILE_MAP4:
		csFileName = "map4.mul";
		break;
	case VERFILE_STAIDX4:
		csFileName = "staidx4.mul";
		break;
	case VERFILE_STATICS4:
		csFileName = "statics4.mul";
		break;
	case VERFILE_MAPDIF4:
		csFileName = "mapdif4.mul";
		break;
	case VERFILE_MAPDIFL4:
		csFileName = "mapdifl4.mul";
		break;
	case VERFILE_STADIF4:
		csFileName = "stadif4.mul";
		break;
	case VERFILE_STADIFI4:
		csFileName = "stadifi4.mul";
		break;
	case VERFILE_STADIFL4:
		csFileName = "stadifl4.mul";
		break;
	case VERFILE_MAP5:
		csFileName = "map5.mul";
		break;
	case VERFILE_STAIDX5:
		csFileName = "staidx5.mul";
		break;
	case VERFILE_STATICS5:
		csFileName = "statics5.mul";
		break;
	case VERFILE_MAPDIF5:
		csFileName = "mapdif5.mul";
		break;
	case VERFILE_MAPDIFL5:
		csFileName = "mapdifl5.mul";
		break;
	case VERFILE_STADIF5:
		csFileName = "stadif5.mul";
		break;
	case VERFILE_STADIFI5:
		csFileName = "stadifi5.mul";
		break;
	case VERFILE_STADIFL5:
		csFileName = "stadifl5.mul";
		break;
	case VERFILE_FONTS:
		csFileName = "fonts.mul";
		break;
	case VERFILE_UNIFONT:
		csFileName = "unifont.mul";
		break;
	case VERFILE_UNIFONT1:
		csFileName = "unifont1.mul";
		break;
	case VERFILE_UNIFONT2:
		csFileName = "unifont2.mul";
		break;
	case VERFILE_UNIFONT3:
		csFileName = "unifont3.mul";
		break;
	case VERFILE_UNIFONT4:
		csFileName = "unifont4.mul";
		break;
	case VERFILE_UNIFONT5:
		csFileName = "unifont5.mul";
		break;
	case VERFILE_UNIFONT6:
		csFileName = "unifont6.mul";
		break;
	case VERFILE_LIGHTIDX:
		csFileName = "lightidx.mul";
		break;
	case VERFILE_LIGHT:
		csFileName = "light.mul";
		break;
	case VERFILE_MUSICLIST:
		csFileName = "config\\music.cfg";
		break;
	case VERFILE_MAP0_UOP:
		csFileName = "map0.uop";
		break;
	case VERFILE_MAP1_UOP:
		csFileName = "map1.uop";
		break;
	case VERFILE_MAP2_UOP:
		csFileName = "map2.uop";
		break;
	case VERFILE_MAP3_UOP:
		csFileName = "map3.uop";
		break;
	case VERFILE_MAP4_UOP:
		csFileName = "map4.uop";
		break;
	case VERFILE_MAP5_UOP:
		csFileName = "map5.uop";
		break;
	default:
		csFileName = "";
		break;
	}
	return csFileName;
}

int FindTable(LPCTSTR pszFind, const char * const * pszTable, int iMax)
{
	for ( int i = 0; i < iMax; i++ )
	{
		if ( !_strcmpi(pszFind, pszTable[i]) )
			return i;
	}
	return -1;
}

BOOL GetPathDlg(HWND hParent, LPTSTR pszPath, LPCTSTR pszTitle)
{
	LPMALLOC pMalloc;
	BROWSEINFO bi;
	char pszDisplayName[MAX_PATH];
	LPITEMIDLIST pidl;
	BOOL bResult = FALSE;

	if (SUCCEEDED(SHGetMalloc(&pMalloc)))
	{
		bi.hwndOwner = hParent;
		bi.pidlRoot = NULL;
		bi.pszDisplayName = pszDisplayName;
		bi.lpszTitle = pszTitle;
		bi.ulFlags = BIF_RETURNONLYFSDIRS;
		bi.lpfn = NULL;
		bi.lParam = 0;
		if ((pidl = SHBrowseForFolder(&bi)) != NULL)
		{
			if (SHGetPathFromIDList(pidl, pszPath))
				bResult = TRUE;
			pMalloc->Free(pidl);
		}
		pMalloc->Release();
	}
	return bResult;
}