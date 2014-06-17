#include "stdafx.h"
#include "JN_DXFontMgr.h"

JN_DXFontMgr	*JN_DXFontMgr::m_pInstance	=	NULL;

JN_DXFontMgr::JN_DXFontMgr( VOID )
{
	m_BaseFontName		=	"기본";
	m_BaseFontColor		=	D3DCOLOR_XRGB( 255, 255, 255 );
	m_BaseFontFormat	=	DT_LEFT | DT_NOCLIP;

	m_FontMap.clear();
}

JN_DXFontMgr::~JN_DXFontMgr( VOID )
{
	Release();
}	

JN_DXFontMgr*	JN_DXFontMgr::GetInstance(VOID)
{
	if( m_pInstance == NULL )
	{
		m_pInstance	=	new JN_DXFontMgr;
	}

	return m_pInstance;
}

VOID	JN_DXFontMgr::Destroy(VOID)
{
	if( m_pInstance != NULL )
	{
		delete m_pInstance;
		m_pInstance	=	NULL;
	}
}


 VOID  JN_DXFontMgr::Release(  VOID  )
{
	FontMapIter		iter = m_FontMap.begin();

	for( ; iter != m_FontMap.end() ; iter++ )
	{
		LPD3DXFONT pFont	= iter->second;

		if( pFont != NULL )
		{
			pFont->Release();
		}
	}

	m_FontMap.clear();
}

///< 폰트추가
 HRESULT JN_DXFontMgr::AddFont( LPDIRECT3DDEVICE9 pd3dDevice, std::string strFontName, tagFontInfo& FontInfo)
{
	FontMapIter		iter = m_FontMap.find(strFontName);

	if( iter == m_FontMap.end() )
	{
		LPD3DXFONT			pFont;

		if( D3DXCreateFont( pd3dDevice, FontInfo.nFontSize, 0, FW_BOLD, 1, false, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, FIXED_PITCH | FF_DONTCARE, FontInfo.strFontName.c_str(), &pFont) != S_OK )
		{
			return S_FALSE;
		}

		m_FontMap.insert(make_pair(strFontName, pFont));

		return S_OK;
	}

	return S_OK;
}

///< 폰트출력
 VOID  JN_DXFontMgr::DrawFont(std::string strFontName, std::string strText, DWORD dwAlign, RECT rcDrawArea, D3DXCOLOR color)
{
	FontMapIter				find;

	///< 폰트가 하나도 없는경우 리턴
	if(m_FontMap.empty() == true)
	{
		MessageBox(NULL, "폰트가 없습니다", "오류", MB_OK);
		return;
	}
	
	///< 찾는 폰트가 없는경우
	find = m_FontMap.find(strFontName);
	if(find == m_FontMap.end())
	{
		return;
	}

	find->second->DrawText(NULL, strText.c_str(), -1, &rcDrawArea, dwAlign, color);
}

VOID	JN_DXFontMgr::DrawFont(INT nX, INT nY, LPCSTR szBuf, ... )
{
	 FontMapIter				find;

	 ///< 폰트가 하나도 없는경우 리턴
	 if( m_FontMap.empty() == true )
	 {
		 MessageBox(NULL, "폰트가 없습니다", "오류", MB_OK);
		 return;
	 }

	 ///< 찾는 폰트가 없는경우
	 find = m_FontMap.find(m_BaseFontName);
	 if(find == m_FontMap.end())
	 {
		 return;
	 }

	char String[256];

	va_list	va;

	va_start( va, szBuf );
	vsprintf_s(String, 256, szBuf, va );
	va_end(va);

	RECT	rc = { nX, nY, 0, 0 };

	find->second->DrawText(NULL, String, strlen(String), &rc, m_BaseFontFormat, m_BaseFontColor );
}