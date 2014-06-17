#include "StdAfx.h"
#include "cVertexBuffer.h"

cVertexBuffer::cVertexBuffer(void)
{
}

cVertexBuffer::~cVertexBuffer(void)
{
	Release();
}

void	cVertexBuffer::Init( LPDIRECT3DDEVICE9 pDevice, tagVerRhwColor *pVertex, INT nVertexSize, INT nCount )
{
	m_pd3dDevice	=	pDevice;

	//< ���ؽ� ���� ���� 
	if( FAILED(	m_pd3dDevice->CreateVertexBuffer(
			nVertexSize * nCount,					//	���ۿ� �Ҵ��� ����Ʈ
			0,										//	������ Ư��( �⺻ 0 )
			tagVerRhwColor::FVF_VER_RHW_COLOR,		//	FVF ����ü�� Ÿ��
			D3DPOOL_DEFAULT,						//	�޸� Ǯ
			&m_pVB,									//	���ؽ����� ������
			0)))
	{
			return;
	}

	m_dwFVF_Format		=	tagVerRhwColor::FVF_VER_RHW_COLOR;
	m_dwFVF_StructSize	=	nVertexSize;
	m_dwFVF_VertexCount	=	nCount;
	m_dwFVF_DrawType	=	D3DPT_TRIANGLELIST;

	//////////////////////////////////////////////////////////////////////////////////
	UpdateVertex( pVertex );
}

void	cVertexBuffer::Init( LPDIRECT3DDEVICE9 pDevice, tagVerColor *pVertex, INT nVertexSize, INT nCount )
{
	m_pd3dDevice	=	pDevice;

	//< ���ؽ� ���� ���� 
	if( FAILED(	m_pd3dDevice->CreateVertexBuffer(
			nVertexSize * nCount,					//	���ۿ� �Ҵ��� ����Ʈ
			0,										//	������ Ư��( �⺻ 0 )
			tagVerColor::FVF_VER_COLOR,				//	FVF ����ü�� Ÿ��
			D3DPOOL_DEFAULT,						//	�޸� Ǯ
			&m_pVB,									//	���ؽ����� ������
			0)))
	{
			return;
	}

	m_dwFVF_Format		=	tagVerColor::FVF_VER_COLOR;
	m_dwFVF_StructSize	=	nVertexSize;
	m_dwFVF_VertexCount	=	nCount;
	m_dwFVF_DrawType	=	D3DPT_TRIANGLELIST;

	//////////////////////////////////////////////////////////////////////////////////
	UpdateVertex( pVertex );
}

void	cVertexBuffer::Init( LPDIRECT3DDEVICE9 pDevice, tagVerNormalTex *pVertex, INT nVertexSize, INT nCount )
{
	m_pd3dDevice	=	pDevice;

	//< ���ؽ� ���� ���� 
	if( FAILED(	m_pd3dDevice->CreateVertexBuffer(
			nVertexSize * nCount,					//	���ۿ� �Ҵ��� ����Ʈ
			0,										//	������ Ư��( �⺻ 0 )
			tagVerNormalTex::FVF_VER_NOR_TEX,				//	FVF ����ü�� Ÿ��
			D3DPOOL_DEFAULT,						//	�޸� Ǯ
			&m_pVB,									//	���ؽ����� ������
			0)))
	{
			return;
	}

	m_dwFVF_Format		=	tagVerNormalTex::FVF_VER_NOR_TEX;
	m_dwFVF_StructSize	=	nVertexSize;
	m_dwFVF_VertexCount	=	nCount;
	m_dwFVF_DrawType	=	D3DPT_TRIANGLELIST;

	//////////////////////////////////////////////////////////////////////////////////
	UpdateVertex( pVertex );
}

void	cVertexBuffer::Release(void)
{
	SAFE_RELEASE( m_pVB );
}

void	cVertexBuffer::Render(void)
{
	//	���ؽ� ���ۿ� ��Ʈ���ҽ� ����
	m_pd3dDevice->SetStreamSource(
		0,								//	���� ��Ʈ���� �ƴϸ� 0
		m_pVB,							//	��Ʈ�� ���� ���ؽ� ����
		0,								//	�������� ������
		m_dwFVF_StructSize );		//	���ؽ� ����ü�� ũ��

	//	FVF ���� ����
	m_pd3dDevice->SetFVF( m_dwFVF_Format );

	//	�׸���
	m_pd3dDevice->DrawPrimitive( 
		m_dwFVF_DrawType,					//	�׸��� ���
		0,									//	�׸��� ������ �ε��� 
		m_dwFVF_VertexCount / 3 );			//	�׸��� ��ü ����
}	

void	cVertexBuffer::UpdateVertex( VOID *pVertex )
{
	VOID *	pVer = NULL;

	//< ���� ���� 
	m_pVB->Lock( 
		0,											//	����� ������ ��ġ ( �⺻ ó���̹Ƿ� 0 )
		m_dwFVF_StructSize * m_dwFVF_VertexCount,	//	����� ����Ʈ ��
		&pVer,										//	��� �޸��� ���� ��ġ
		0);											//	��� ���( �⺻ 0 )

	if( pVer != NULL )
	{
		memmove( pVer,	pVertex, m_dwFVF_StructSize * m_dwFVF_VertexCount	);
	}

	m_pVB->Unlock();
}