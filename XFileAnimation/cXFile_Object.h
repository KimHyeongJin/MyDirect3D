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
	LPDIRECT3DDEVICE9	m_pd3dDevice;		//	����̽�

	D3DXVECTOR3			m_vTrans;			//	�̵�
	D3DXVECTOR3			m_vScale;			//	ũ��
	D3DXVECTOR3			m_vRot;				//	ȸ��

	D3DXMATRIXA16		m_matNoScaleWorld;	//	ũ�⸦ ������ ������ ���� ���
	LPD3DXMATRIXA16		m_pMatParent;		//	�θ����

	BOOL				m_bAni;				//	�ִϸ��̼� ����
	DWORD				m_dwID;				//	ID��

	std::string			m_szFileName;		//	���ϸ�
	DWORD				m_dwType;			//	������Ʈ Ÿ��

protected:
	VOID	SetMatrix(VOID);
	
public:
	cXFile_Object(void);
	virtual ~cXFile_Object(void);

	virtual		VOID	Render(VOID) {};
	virtual		VOID	Update( FLOAT	fDT = 0 ) {};

	//	Get/Set �Լ�
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
