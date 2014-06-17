#pragma once

class cVertexBuffer
{
private:
	LPDIRECT3DDEVICE9			m_pd3dDevice;
	LPDIRECT3DVERTEXBUFFER9		m_pVB;

	DWORD						m_dwFVF_Format;		//	FVF포맷
	DWORD						m_dwFVF_StructSize;	//	FVF구조체크기
	D3DPRIMITIVETYPE			m_dwFVF_DrawType;	//	FVF그리기타입
	DWORD						m_dwFVF_VertexCount;//	FVF정점 개수

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
