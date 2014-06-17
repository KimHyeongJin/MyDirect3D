#include "StdAfx.h"
#include "cXFile_Dummy.h"

cXFile_Dummy::cXFile_Dummy(void)
{
}

cXFile_Dummy::~cXFile_Dummy(void)
{
	Release();
}

HRESULT		cXFile_Dummy::LoadFile( LPDIRECT3DDEVICE9	pd3dDevice, LPCSTR	szFileName, D3DXMATRIXA16	*pMatParent )
{
	//	값이 제대로 대입되지 않으면 실패
	if( szFileName == NULL ||
		pd3dDevice == NULL )
	{
		return E_FAIL;
	}

	m_pd3dDevice	=	pd3dDevice;
	m_szFileName	=	szFileName;
	m_pMatParent	=	pMatParent;


	LPD3DXBUFFER					pMtrlBuffer;
	DWORD							dwMtrls;

	HRESULT	hr		=	D3DXLoadMeshFromXA(
		szFileName,				//	파일 이름
		D3DXMESH_MANAGED,		//	X 파일 옵션
		pd3dDevice,				//	디바이스
		NULL,					//	인접버퍼...
		&pMtrlBuffer,			//	메터리얼 버퍼
		NULL,					//	이펙트 버퍼
		&dwMtrls,				//	메터리얼 개수
		&m_Data.pMesh );		//	메쉬 클래스

	if( hr	==	D3DERR_INVALIDCALL ||	//	호출 무효
		hr	==	E_OUTOFMEMORY )			//	메모리 할당 실패
	{
		return hr;
	}

	for( DWORD i = 0; i < dwMtrls; ++i )
	{
		LPD3DXMATERIAL pMtrls = (LPD3DXMATERIAL)pMtrlBuffer->GetBufferPointer();

		//	환경광을 지원하지 않기 때문에 난반사광의 색을 적용한다.
		pMtrls[i].MatD3D.Ambient	=	pMtrls[i].MatD3D.Diffuse;

		//	재질 추가
		m_Data.vecMaterials.push_back( pMtrls[i].MatD3D );

		
		LPDIRECT3DTEXTURE9	pTex	=	NULL;

		if( pMtrls[i].pTextureFilename != NULL )
		{
			D3DXCreateTextureFromFileA( m_pd3dDevice, pMtrls[i].pTextureFilename, &pTex );
		}

		//	텍스처 추가
		m_Data.vecTextures.push_back( pTex );
	}

	//	사용한 재질버퍼는 해제한다.
	pMtrlBuffer->Release();

	return S_OK;
}

VOID		cXFile_Dummy::Release(VOID)
{
	for( UINT	i	=	0;	i < m_Data.vecTextures.size(); ++i )
	{
		if( m_Data.vecTextures[i] != NULL )
		{
			m_Data.vecTextures[i]->Release();
		}
	}

	m_Data.vecMaterials.clear();
	m_Data.vecTextures.clear();
	m_Data.pMesh->Release();
}

VOID		cXFile_Dummy::Render(VOID)
{
	SetMatrix();

	for( UINT	i	=	0;	i < m_Data.vecMaterials.size(); ++i )
	{
		m_pd3dDevice->SetMaterial( &m_Data.vecMaterials[i] );
		m_pd3dDevice->SetTexture( 0, m_Data.vecTextures[i] );
		m_Data.pMesh->DrawSubset( i );
	}

	//	텍스처 설정 초기화
	m_pd3dDevice->SetTexture( 0, NULL);
}

VOID		cXFile_Dummy::Update( FLOAT	fDT )
{

}