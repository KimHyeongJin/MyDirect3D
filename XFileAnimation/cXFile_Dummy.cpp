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
	//	���� ����� ���Ե��� ������ ����
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
		szFileName,				//	���� �̸�
		D3DXMESH_MANAGED,		//	X ���� �ɼ�
		pd3dDevice,				//	����̽�
		NULL,					//	��������...
		&pMtrlBuffer,			//	���͸��� ����
		NULL,					//	����Ʈ ����
		&dwMtrls,				//	���͸��� ����
		&m_Data.pMesh );		//	�޽� Ŭ����

	if( hr	==	D3DERR_INVALIDCALL ||	//	ȣ�� ��ȿ
		hr	==	E_OUTOFMEMORY )			//	�޸� �Ҵ� ����
	{
		return hr;
	}

	for( DWORD i = 0; i < dwMtrls; ++i )
	{
		LPD3DXMATERIAL pMtrls = (LPD3DXMATERIAL)pMtrlBuffer->GetBufferPointer();

		//	ȯ�汤�� �������� �ʱ� ������ ���ݻ籤�� ���� �����Ѵ�.
		pMtrls[i].MatD3D.Ambient	=	pMtrls[i].MatD3D.Diffuse;

		//	���� �߰�
		m_Data.vecMaterials.push_back( pMtrls[i].MatD3D );

		
		LPDIRECT3DTEXTURE9	pTex	=	NULL;

		if( pMtrls[i].pTextureFilename != NULL )
		{
			D3DXCreateTextureFromFileA( m_pd3dDevice, pMtrls[i].pTextureFilename, &pTex );
		}

		//	�ؽ�ó �߰�
		m_Data.vecTextures.push_back( pTex );
	}

	//	����� �������۴� �����Ѵ�.
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

	//	�ؽ�ó ���� �ʱ�ȭ
	m_pd3dDevice->SetTexture( 0, NULL);
}

VOID		cXFile_Dummy::Update( FLOAT	fDT )
{

}