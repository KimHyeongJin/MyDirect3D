#pragma once

#include <string>
#include <map>

struct tagFontInfo
{
	int				nFontSize;
	std::string		strFontName;
};

class JN_DXFontMgr
{
public:
	typedef	std::map<std::string, LPD3DXFONT>					FontMap;
	typedef	std::map<std::string, LPD3DXFONT>::iterator			FontMapIter;


private:
	static	JN_DXFontMgr	*m_pInstance;

	//< 폰트 관리 맵
	FontMap					m_FontMap;

	std::string				m_BaseFontName;
	D3DXCOLOR				m_BaseFontColor;
	DWORD					m_BaseFontFormat;

public:
	JN_DXFontMgr( VOID );
	~JN_DXFontMgr( VOID );

public:
	static	JN_DXFontMgr*	GetInstance(VOID);
			VOID			Destroy(VOID);

	//< 해제
	 VOID 	Release(  VOID  );

	//<	기본 세팅
	 VOID	SetBaseFont( std::string strFontName )
	 {
			m_BaseFontName	=	strFontName;
	 }
	 VOID	SetBaseColor( D3DXCOLOR	BaseFontColor )
	 {
			m_BaseFontColor	=	BaseFontColor;
	 }
	 VOID	SetBaseFormat( DWORD dwFormat )
	 {
			m_BaseFontFormat	=	dwFormat;
	 }

	//< 렌더
	 VOID 	DrawFont(std::string strFontName, std::string strText, DWORD dwAlign, RECT rcDrawArea, D3DXCOLOR color);
	 VOID	DrawFont(INT nX, INT nY, LPCSTR szBuf, ... );

	//< 글씨추가
	HRESULT	AddFont( LPDIRECT3DDEVICE9 pd3dDevice, std::string strFontName, tagFontInfo& FontInfo);
};