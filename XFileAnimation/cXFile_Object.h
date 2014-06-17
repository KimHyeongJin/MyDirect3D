#pragma once

struct tagXFileInfo
{
	LPD3DXMESH							pMesh;
	std::vector< D3DMATERIAL9 >			vecMaterials;
	std::vector< LPDIRECT3DTEXTURE9 >	vecTextures;
};

class cXFile_Object
{
protected:
	LPDIRECT3DDEVICE9	m_pd3dDevice;		//	디바이스

	D3DXVECTOR3			m_vTrans;			//	이동
	D3DXVECTOR3			m_vScale;			//	크기
	D3DXVECTOR3			m_vRot;				//	회전

	D3DXMATRIXA16		m_matNoScaleWorld;	//	크기를 제외한 나머지 적용 행렬
	LPD3DXMATRIXA16		m_pMatParent;		//	부모행렬

	BOOL				m_bAni;				//	애니메이션 유무
	DWORD				m_dwID;				//	ID값

	std::string			m_szFileName;		//	파일명
	DWORD				m_dwType;			//	오브젝트 타입

protected:
	VOID	SetMatrix(VOID);
	
public:
	cXFile_Object(void);
	virtual ~cXFile_Object(void);

	virtual		VOID	Render(VOID) {};
	virtual		VOID	Update( FLOAT	fDT = 0 ) {};

	//	Get/Set 함수
	inline	VOID			SetRot( FLOAT x, FLOAT y, FLOAT z )
	{
		m_vRot	=	D3DXVECTOR3( x, y, z );
	}
	inline	VOID			SetAddRot( FLOAT x, FLOAT y, FLOAT z )
	{
		m_vRot	+=	D3DXVECTOR3( x, y, z );
	}
	inline	LPD3DXVECTOR3	GetRot(VOID)
	{
		return &m_vRot;
	}

	inline	VOID			SetTrans( FLOAT x, FLOAT y, FLOAT z )
	{
		m_vTrans	=	D3DXVECTOR3( x, y, z );
	}
	inline	VOID			SetAddTrans( FLOAT x, FLOAT y, FLOAT z )
	{
		m_vTrans	+=	D3DXVECTOR3( x, y, z );
	}
	inline	LPD3DXVECTOR3	GetTrans(VOID)
	{
		return &m_vRot;
	}

	inline	VOID			SetScale( FLOAT x, FLOAT y, FLOAT z )
	{
		m_vScale	=	D3DXVECTOR3( x, y, z );
	}
	inline	VOID			SetAddScale( FLOAT x, FLOAT y, FLOAT z )
	{
		m_vScale	+=	D3DXVECTOR3( x, y, z );
	}
	inline	LPD3DXVECTOR3	GetScale(VOID)
	{
		return &m_vRot;
	}
};
