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

	//< 버텍스 버퍼 생성 
	if( FAILED(	m_pd3dDevice->CreateVertexBuffer(
			nVertexSize * nCount,					//	버퍼에 할당할 바이트
			0,										//	버퍼의 특성( 기본 0 )
			tagVerRhwColor::FVF_VER_RHW_COLOR,		//	FVF 구조체의 타입
			D3DPOOL_DEFAULT,						//	메모리 풀
			&m_pVB,									//	버텍스버퍼 포인터
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

	//< 버텍스 버퍼 생성 
	if( FAILED(	m_pd3dDevice->CreateVertexBuffer(
			nVertexSize * nCount,					//	버퍼에 할당할 바이트
			0,										//	버퍼의 특성( 기본 0 )
			tagVerColor::FVF_VER_COLOR,				//	FVF 구조체의 타입
			D3DPOOL_DEFAULT,						//	메모리 풀
			&m_pVB,									//	버텍스버퍼 포인터
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

	//< 버텍스 버퍼 생성 
	if( FAILED(	m_pd3dDevice->CreateVertexBuffer(
			nVertexSize * nCount,					//	버퍼에 할당할 바이트
			0,										//	버퍼의 특성( 기본 0 )
			tagVerNormalTex::FVF_VER_NOR_TEX,				//	FVF 구조체의 타입
			D3DPOOL_DEFAULT,						//	메모리 풀
			&m_pVB,									//	버텍스버퍼 포인터
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
	//	버텍스 버퍼와 스트림소스 연결
	m_pd3dDevice->SetStreamSource(
		0,								//	다중 스트림이 아니면 0
		m_pVB,							//	스트림 연결 버텍스 버퍼
		0,								//	데이터의 시작점
		m_dwFVF_StructSize );		//	버텍스 구조체의 크기

	//	FVF 포맷 설정
	m_pd3dDevice->SetFVF( m_dwFVF_Format );

	//	그리기
	m_pd3dDevice->DrawPrimitive( 
		m_dwFVF_DrawType,					//	그리는 방식
		0,									//	그리기 시작학 인덱스 
		m_dwFVF_VertexCount / 3 );			//	그리는 개체 개수
}	

void	cVertexBuffer::UpdateVertex( VOID *pVertex )
{
	VOID *	pVer = NULL;

	//< 정보 설정 
	m_pVB->Lock( 
		0,											//	잠금을 시작할 위치 ( 기본 처음이므로 0 )
		m_dwFVF_StructSize * m_dwFVF_VertexCount,	//	잠금할 바이트 수
		&pVer,										//	잠금 메모리의 시작 위치
		0);											//	잠금 방법( 기본 0 )

	if( pVer != NULL )
	{
		memmove( pVer,	pVertex, m_dwFVF_StructSize * m_dwFVF_VertexCount	);
	}

	m_pVB->Unlock();
}