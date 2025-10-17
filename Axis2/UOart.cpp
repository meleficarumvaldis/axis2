// UOart.cpp: implementation of the CUOart class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Axis2.h"
#include "UOart.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUOart::CUOart()
{

}

CUOart::~CUOart()
{

}

void CUOart::LoadTile(int iTile)
{
	CFile cfArtIdx;
	CString csArtIdxFile;
	csArtIdxFile = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_ARTIDX);
	if ( cfArtIdx.Open( csArtIdxFile, CFile::modeRead | CFile::typeBinary | CFile::shareDenyNone ) )
	{
		CFile cfArt;
		CString csArtFile;
		csArtFile = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_ART);
		if ( cfArt.Open( csArtFile, CFile::modeRead | CFile::typeBinary | CFile::shareDenyNone ) )
		{
			cfArtIdx.Seek(iTile * 12, CFile::begin);
			cfArtIdx.Read(&m_pTile, 12);

			cfArt.Seek(m_pTile.dwStart, CFile::begin);
			if ( m_pTile.dwLookup != 0xFFFFFFFF )
			{
				if ( (m_pTile.dwImgSize & 0x80000000) == 0x80000000 )
				{
					// Compressed
				}
				else
				{
					// Uncompressed
					m_pTile.wHeight = (short) sqrt((double)m_pTile.dwImgSize / 2.0) * 2;
					m_pTile.wWidth = m_pTile.wHeight;
					cfArt.Read(&m_pTile.wArt, m_pTile.dwImgSize);
				}
			}
			cfArt.Close();
		}
		cfArtIdx.Close();
	}
}

void CUOart::LoadGump(int iGump)
{
	CFile cfGumpIdx;
	CString csGumpIdxFile;
	csGumpIdxFile = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_GUMPIDX);
	if ( cfGumpIdx.Open( csGumpIdxFile, CFile::modeRead | CFile::typeBinary | CFile::shareDenyNone ) )
	{
		CFile cfGump;
		CString csGumpFile;
		csGumpFile = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_GUMPART);
		if ( cfGump.Open( csGumpFile, CFile::modeRead | CFile::typeBinary | CFile::shareDenyNone ) )
		{
			cfGumpIdx.Seek(iGump * 12, CFile::begin);
			cfGumpIdx.Read(&m_pGump, 12);

			cfGump.Seek(m_pGump.dwStart, CFile::begin);
			if ( m_pGump.dwLookup != 0xFFFFFFFF )
			{
				m_pGump.pGump = new GUMPHEADER[m_pGump.dwLookup];
				cfGump.Read(m_pGump.pGump, m_pGump.dwLookup * 4);
				m_pGump.pArt = new WORD[m_pGump.dwHeight * m_pGump.dwWidth];
				for ( int i = 0; i < m_pGump.dwHeight; i++ )
				{
					int iOffset = m_pGump.pGump[i].dwLookup;
					cfGump.Seek(m_pGump.dwStart + (iOffset * 2), CFile::begin);
					for ( int j = 0; j < m_pGump.pGump[i].wVal; j++ )
					{
						WORD wColor, wRun;
						cfGump.Read(&wColor, 2);
						cfGump.Read(&wRun, 2);
						for ( int k = 0; k < wRun; k++ )
						{
							m_pGump.pArt[(i * m_pGump.dwWidth) + j + k] = wColor;
						}
					}
				}
			}
			cfGump.Close();
		}
		cfGumpIdx.Close();
	}
}

void CUOart::LoadCharacter(int iAnim)
{
	CFile cfAnim;
	CString csAnimFile;
	csAnimFile = ((CAxis2App*)AfxGetApp())->GetMulPath(VERFILE_ANIM);
	if ( cfAnim.Open( csAnimFile, CFile::modeRead | CFile::typeBinary | CFile::shareDenyNone ) )
	{
		int iOffset = 0;
		if ( iAnim >= 0x200 )
			iOffset = 0x110000 + ((iAnim - 0x200) * 175);
		else
			iOffset = (iAnim * 110);

		cfAnim.Seek(iOffset, CFile::begin);
		cfAnim.Read(&m_pAnim.caFrame, 64 * 8);

		cfAnim.Seek(m_pAnim.caFrame[0].dwStart, CFile::begin);
		cfAnim.Read(&m_pAnim.wWidth, 2);
		cfAnim.Read(&m_pAnim.wHeight, 2);

		int iImgSize = m_pAnim.caFrame[0].dwSize;
		m_pAnim.pArt = new WORD[iImgSize];
		cfAnim.Read(m_pAnim.pArt, iImgSize);
	}
}