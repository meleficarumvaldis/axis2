// UOmap.cpp: implementation of the CUOmap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Axis2.h"
#include "UOmap.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUOmap::CUOmap()
{
	iCurMap = 0;
	iMaxX = 0;
	iMaxY = 0;
}

CUOmap::~CUOmap()
{

}

void CUOmap::LoadBlock(int iMap, int iBlockX, int iBlockY)
{
	CFile cfMap;
	CString csMapFileName;
	if (iMap == 0)
	{
		csMapFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAP0);
		iMaxX = 3071;
		iMaxY = 2047;
	}
	else if (iMap == 1)
	{
		csMapFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAP1);
		iMaxX = 3071;
		iMaxY = 2047;
	}
	else if (iMap == 2)
	{
		csMapFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAP2);
		iMaxX = 2304;
		iMaxY = 1600;
	}
	else if (iMap == 3)
	{
		csMapFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAP3);
		iMaxX = 2560;
		iMaxY = 2048;
	}
	else if (iMap == 4)
	{
		csMapFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAP4);
		iMaxX = 1448;
		iMaxY = 1448;
	}
	else if (iMap == 5)
	{
		csMapFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAP5);
		iMaxX = 1280;
		iMaxY = 1024;
	}

	if ( cfMap.Open( csMapFileName, CFile::modeRead | CFile::typeBinary | CFile::shareDenyNone ) )
	{
		int iOffset = ((iBlockX * (iMaxY + 1)) + iBlockY) * 196;
		cfMap.Seek(iOffset, CFile::begin);
		cfMap.Read(&m_pMapBlock, 196);
		cfMap.Close();
	}
}

void CUOmap::LoadStatics(int iMap, int iBlockX, int iBlockY)
{
	CFile cfStaticIdx;
	CString csStaticIdxName;
	CFile cfStatic;
	CString csStaticFileName;
	if (iMap == 0)
	{
		csStaticIdxName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STAIDX0);
		csStaticFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STATICS0);
		iMaxX = 3071;
		iMaxY = 2047;
	}
	else if (iMap == 1)
	{
		csStaticIdxName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STAIDX1);
		csStaticFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STATICS1);
		iMaxX = 3071;
		iMaxY = 2047;
	}
	else if (iMap == 2)
	{
		csStaticIdxName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STAIDX2);
		csStaticFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STATICS2);
		iMaxX = 2304;
		iMaxY = 1600;
	}
	else if (iMap == 3)
	{
		csStaticIdxName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STAIDX3);
		csStaticFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STATICS3);
		iMaxX = 2560;
		iMaxY = 2048;
	}
	else if (iMap == 4)
	{
		csStaticIdxName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STAIDX4);
		csStaticFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STATICS4);
		iMaxX = 1448;
		iMaxY = 1448;
	}
	else if (iMap == 5)
	{
		csStaticIdxName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STAIDX5);
		csStaticFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STATICS5);
		iMaxX = 1280;
		iMaxY = 1024;
	}

	if ( cfStaticIdx.Open( csStaticIdxName, CFile::modeRead | CFile::typeBinary | CFile::shareDenyNone ) )
	{
		int iOffset = ((iBlockX * (iMaxY + 1)) + iBlockY) * 12;
		cfStaticIdx.Seek(iOffset, CFile::begin);
		cfStaticIdx.Read(&m_pStaticIdx, 12);
		cfStaticIdx.Close();

		if (m_pStaticIdx.dwStart != 0xFFFFFFFF)
		{
			if ( cfStatic.Open( csStaticFileName, CFile::modeRead | CFile::typeBinary | CFile::shareDenyNone ) )
			{
				cfStatic.Seek(m_pStaticIdx.dwStart, CFile::begin);
				int iCount = m_pStaticIdx.dwLength / 7;
				for ( int i = 0; i < iCount; i++ )
				{
					STATIC_CELL * pStatic = new STATIC_CELL;
					cfStatic.Read(pStatic, 7);
					m_paStatics.Add(pStatic);
				}
				cfStatic.Close();
			}
		}
	}
}

void CUOmap::ClearStatics()
{
	for ( int i = 0; i < m_paStatics.GetSize(); i++ )
	{
		STATIC_CELL * pStatic = (STATIC_CELL *) m_paStatics.GetAt(i);
		delete pStatic;
	}
	m_paStatics.RemoveAll();
}

void CUOmap::GetMapSize(int iMap, int &iSizeX, int &iSizeY)
{
	switch (iMap)
	{
	case 0:
		iSizeX = 6144;
		iSizeY = 4096;
		break;
	case 1:
		iSizeX = 6144;
		iSizeY = 4096;
		break;
	case 2:
		iSizeX = 2304;
		iSizeY = 1600;
		break;
	case 3:
		iSizeX = 2560;
		iSizeY = 2048;
		break;
	case 4:
		iSizeX = 1448;
		iSizeY = 1448;
		break;
	case 5:
		iSizeX = 1280;
		iSizeY = 1024;
		break;
	default:
		iSizeX = 6144;
		iSizeY = 4096;
		break;
	}
}
void CUOmap::GetMapSizeBlocks(int iMap, int& iSizeX, int& iSizeY)
{
	switch (iMap)
	{
	case 0:
		iSizeX = 768;
		iSizeY = 512;
		break;
	case 1:
		iSizeX = 768;
		iSizeY = 512;
		break;
	case 2:
		iSizeX = 288;
		iSizeY = 200;
		break;
	case 3:
		iSizeX = 320;
		iSizeY = 256;
		break;
	case 4:
		iSizeX = 181;
		iSizeY = 181;
		break;
	case 5:
		iSizeX = 160;
		iSizeY = 128;
		break;
	default:
		iSizeX = 768;
		iSizeY = 512;
		break;
	}
}
void CUOmap::SetMap(int iMap)
{
	iCurMap = iMap;
	GetMapSize(iCurMap, iMaxX, iMaxY);
}
int CUOmap::GetMap()
{
	return iCurMap;
}
void CUOmap::GetMapFileNames(int iMap, CString& csMapFileName, CString& csStaticIdxName, CString& csStaticFileName, CString& csMapDifFileName, CString& csMapDiflFileName, CString& csStaDifName, CString& csStaDifiName, CString& csStaDiflName)
{
	switch (iMap)
	{
	case 0:
		csMapFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAP0);
		csStaticIdxName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STAIDX0);
		csStaticFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STATICS0);
		csMapDifFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAPDIF0);
		csMapDiflFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAPDIFL0);
		csStaDifName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STADIF0);
		csStaDifiName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STADIFI0);
		csStaDiflName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STADIFL0);
		break;
	case 1:
		csMapFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAP1);
		csStaticIdxName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STAIDX1);
		csStaticFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STATICS1);
		csMapDifFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAPDIF1);
		csMapDiflFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAPDIFL1);
		csStaDifName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STADIF1);
		csStaDifiName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STADIFI1);
		csStaDiflName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STADIFL1);
		break;
	case 2:
		csMapFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAP2);
		csStaticIdxName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STAIDX2);
		csStaticFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STATICS2);
		csMapDifFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAPDIF2);
		csMapDiflFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAPDIFL2);
		csStaDifName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STADIF2);
		csStaDifiName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STADIFI2);
		csStaDiflName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STADIFL2);
		break;
	case 3:
		csMapFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAP3);
		csStaticIdxName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STAIDX3);
		csStaticFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STATICS3);
		csMapDifFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAPDIF3);
		csMapDiflFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAPDIFL3);
		csStaDifName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STADIF3);
		csStaDifiName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STADIFI3);
		csStaDiflName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STADIFL3);
		break;
	case 4:
		csMapFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAP4);
		csStaticIdxName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STAIDX4);
		csStaticFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STATICS4);
		csMapDifFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAPDIF4);
		csMapDiflFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAPDIFL4);
		csStaDifName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STADIF4);
		csStaDifiName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STADIFI4);
		csStaDiflName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STADIFL4);
		break;
	case 5:
		csMapFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAP5);
		csStaticIdxName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STAIDX5);
		csStaticFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STATICS5);
		csMapDifFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAPDIF5);
		csMapDiflFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAPDIFL5);
		csStaDifName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STADIF5);
		csStaDifiName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STADIFI5);
		csStaDiflName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STADIFL5);
		break;
	}

	CFileStatus status;
	if (CFile::GetStatus(csMapFileName, status))
	{
		if (csMapFileName.Right(3) == "uop")
		{
			switch (iMap)
			{
			case 0:
				csMapFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAP0_UOP);
				break;
			case 1:
				csMapFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAP1_UOP);
				break;
			case 2:
				csMapFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAP2_UOP);
				break;
			case 3:
				csMapFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAP3_UOP);
				break;
			case 4:
				csMapFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAP4_UOP);
				break;
			case 5:
				csMapFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAP5_UOP);
				break;
			}
		}
	}
	else
	{
		switch (iMap)
		{
		case 0:
			csMapFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAP0);
			csStaticIdxName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STAIDX0);
			csStaticFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STATICS0);
			csMapDifFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAPDIF1);
			csMapDiflFileName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAPDIFL1);
			csStaDifName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STADIF1);
			csStaDifiName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STADIFI1);
			csStaDiflName = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_STADIFL1);
			break;
		}
	}

}
bool CUOmap::ApplyMapDiffs(CString sFile, CUOmap* pMap)
{
	return true;
}
bool CUOmap::ApplyStaticDiffs(CString sFile, CUOmap* pMap)
{
	return true;
}
bool CUOmap::IsUOP(int iMap)
{
	CString sFile;
	switch (iMap)
	{
	case 0:
		sFile = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAPDIF0);
		break;
	case 1:
		sFile = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAPDIF1);
		break;
	case 2:
		sFile = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAPDIF2);
		break;
	case 3:
		sFile = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAPDIF3);
		break;
	case 4:
		sFile = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAPDIF4);
		break;
	case 5:
		sFile = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAPDIF5);
		break;
	}
	CFileStatus rStatus;
	if (CFile::GetStatus(sFile, rStatus))
	{
		return true;
	}
	else
	{
		switch (iMap)
		{
		case 0:
			sFile = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAP0);
			break;
		case 1:
			sFile = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAP1);
			break;
		case 2:
			sFile = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAP2);
			break;
		case 3:
			sFile = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAP3);
			break;
		case 4:
			sFile = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAP4);
			break;
		case 5:
			sFile = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_MAP5);
			break;
		}
		if (CFile::GetStatus(sFile, rStatus))
		{
			if (sFile.Right(3) == "uop")
				return true;
		}
	}
	return false;
}
bool CUOmap::LoadMap(int iMap, CString sFile)
{
	return true;
}
bool CUOmap::LoadStatics(int iMap, CString sFile)
{
	return true;
}
MAP_CELL* CUOmap::GetMapCell(int x, int y)
{
	return NULL;
}
STATIC_CELL* CUOmap::GetStaticCell(int x, int y)
{
	return NULL;
}