// stdafx.cpp : source file that includes just the standard includes
//	Axis2.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

CString csUOPath;
CString csMulPath;
CString csProfilePath;
HKEY hRegLocation;
HWND hwndHoGInstance = NULL;

BOOL CALLBACK EnumInstanceProc(HWND hWnd, LPARAM lParam)
{
	DWORD dwProcessId;
	GetWindowThreadProcessId(hWnd, &dwProcessId);
	if (dwProcessId == GetCurrentProcessId())
	{
		TCHAR szClassName[100];
		GetClassName(hWnd, szClassName, 100);
		if (strcmp(szClassName, "Afx:400000:0:10011:0:0") == 0)
		{
			CString csTitle;
			CWnd::FromHandle(hWnd)->GetWindowText(csTitle);
			if (csTitle.Find(((CAxis2App*)AfxGetApp())->GetVersionTitle()) != -1)
			{
				hwndHoGInstance = hWnd;
				return FALSE;
			}
		}
	}
	return TRUE;
}

BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
	DWORD dwProcessId;
	GetWindowThreadProcessId(hWnd, &dwProcessId);
	TCHAR szClassName[100];
	GetClassName(hWnd, szClassName, 100);
	if (strcmp(szClassName, "Ultima Online") == 0)
	{
		CString csTitle;
		CWnd::FromHandle(hWnd)->GetWindowText(csTitle);
		if ((csTitle.Find("Ultima Online") != -1) || (csTitle.Find("UOSA -") != -1) || (csTitle.Find("ClassicUO") != -1) || (((CAxis2App*)AfxGetApp())->m_csUOTitle.GetLength() > 0 && (csTitle.Find(((CAxis2App*)AfxGetApp())->m_csUOTitle) != -1)))
		{
			hwndHoGInstance = hWnd;
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CALLBACK EnumWindowsProc2(HWND hWnd, LPARAM lParam)
{
	DWORD dwProcessId;
	GetWindowThreadProcessId(hWnd, &dwProcessId);
	TCHAR szClassName[100];
	GetClassName(hWnd, szClassName, 100);
	CString csTitle;
	CWnd::FromHandle(hWnd)->GetWindowText(csTitle);
	if (csTitle.Find(((CAxis2App*)AfxGetApp())->GetVersionTitle()) != -1)
	{
		hwndHoGInstance = hWnd;
		return FALSE;
	}
	return TRUE;
}

void ProfileLoad(CString csProfile)
{
	CString csKey;
	csKey.Format("Software\\Axis2\\Profiles\\%s", csProfile);
	CString csType = ((CAxis2App*)AfxGetApp())->GetRegistryString("Type", "Local", hRegLocation, csKey);
	if (csType == "Local")
	{
		// Load from local file
	}
	else if (csType == "Remote")
	{
		// Load from remote server
	}
}