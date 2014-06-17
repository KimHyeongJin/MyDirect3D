#pragma once

#include "cXFile_Object.h"

class cXFile_Dummy
	: public	cXFile_Object
{
private:
	tagXFileInfo	m_Data;

private:
	VOID		Release(VOID);

public:
	cXFile_Dummy(void);
	~cXFile_Dummy(void);

	//	X파일 로드
	HRESULT		LoadFile( LPDIRECT3DDEVICE9	pd3dDevice, LPCSTR	szFileName, D3DXMATRIXA16	*pMatParent = NULL );
	

	VOID		Render(VOID);
	VOID		Update( FLOAT	fDT	=	0);
};
