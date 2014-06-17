#pragma once

class cVertexBuffer
{
private:
	LPDIRECT3DDEVICE9			m_pd3dDevice;
	LPDIRECT3DVERTEXBUFFER9		m_pVB;

	DWORD						m_dwFVF_Format;		//	FVF����
	DWORD						m_dwFVF_StructSize;	//	FVF����üũ��
	D3DPRIMITIVETYPE			m_dwFVF_DrawType;	//	FVF�׸���Ÿ��
	DWORD						m_dwFVF_VertexCount;//	FVF���� ����

private:


public:
	cVertexBuffer(void);
	~cVertexBuffer(void);

	void	Init( LPDIRECT3DDEVICE9 pDevice, tagVerRhwColor *pVertex, INT nVertexSize, INT nCount );
	void	Init( LPDIRECT3DDEVICE9 pDevice, tagVerColor *pVertex, INT nVertexSize, INT nCount );
	void	Init( LPDIRECT3DDEVICE9 pDevice, tagVerNormalTex *pVertex, INT nVertexSize, INT nCount );

	void	Release(void);

	void	Render(void);

	///////////////////////////////////////////////////////////////////////////
	void	UpdateVertex( VOID *pVertex );
};
