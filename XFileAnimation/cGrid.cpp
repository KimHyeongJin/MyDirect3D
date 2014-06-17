#include "StdAfx.h"
#include "cGrid.h"

cGrid::cGrid(void)
:m_sGridVer(NULL)
{
}

cGrid::~cGrid(void)
{
	if( m_sGridVer != NULL )
	{
		delete [] m_sGridVer;
		m_sGridVer	=	NULL;
	}
}

VOID	cGrid::Init( INT nWidth )
{
	GRID_WIDTH	=	nWidth;
	GRID_VERMAX	=	(GRID_WIDTH * 2 + 1)* 4;

	m_sGridVer	=	new tagVerColor[ GRID_VERMAX ];

	GridInit();
	ArrowInit();
}

VOID	cGrid::Render(VOID)
{
	D3DXMATRIXA16		matBase;
	D3DXMatrixIdentity( &matBase );
	JN_Base3D::m_pd3dDevice->SetTransform( D3DTS_WORLD, &matBase );

	DWORD	dwLight;
	
	JN_Base3D::m_pd3dDevice->GetRenderState( D3DRS_LIGHTING, &dwLight );
	JN_Base3D::m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	GridRender();
	ArrowRender();

	JN_Base3D::m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, dwLight );
}

VOID	cGrid::GridInit(VOID)
{
	ZeroMemory( m_sGridVer, sizeof(tagVerColor) * GRID_VERMAX );

	//	���� ����
	for( int i = 0; i < GRID_VERMAX/2; i+=2 )
	{
		m_sGridVer[i].vPos		=	D3DXVECTOR3( -(FLOAT)GRID_WIDTH + i/2, 0, (FLOAT)GRID_WIDTH );
		m_sGridVer[i+1].vPos	=	D3DXVECTOR3( -(FLOAT)GRID_WIDTH + i/2, 0, -(FLOAT)GRID_WIDTH );

		m_sGridVer[i].dwColor	=	D3DCOLOR_XRGB( 255, 255, 255 );
		m_sGridVer[i+1].dwColor	=	D3DCOLOR_XRGB( 255, 255, 255 );
	}

	//	���� ����
	for( int i = GRID_VERMAX/2; i < GRID_VERMAX; i+=2 )
	{
		m_sGridVer[i].vPos		=	D3DXVECTOR3( (FLOAT)GRID_WIDTH, 0, -(FLOAT)GRID_WIDTH + (i - GRID_VERMAX/2)/2 );
		m_sGridVer[i+1].vPos	=	D3DXVECTOR3( -(FLOAT)GRID_WIDTH, 0, -(FLOAT)GRID_WIDTH + (i - GRID_VERMAX/2)/2 );

		m_sGridVer[i].dwColor	=	D3DCOLOR_XRGB( 255, 255, 255 );
		m_sGridVer[i+1].dwColor	=	D3DCOLOR_XRGB( 255, 255, 255 );
	}

	if( FAILED(	JN_Base3D::m_pd3dDevice->CreateVertexBuffer(
			sizeof(tagVerColor) * GRID_VERMAX,		//	���ۿ� �Ҵ��� ����Ʈ
			0,										//	������ Ư��( �⺻ 0 )
			tagVerColor::FVF_VER_COLOR,				//	FVF ����ü�� Ÿ��
			D3DPOOL_DEFAULT,						//	�޸� Ǯ
			&m_GridVB,								//	���ؽ����� ������
			0)))
	{
			return;
	}

	VOID *	pVer = NULL;

	//< ���� ���� 
	m_GridVB->Lock( 
		0,										//	����� ������ ��ġ ( �⺻ ó���̹Ƿ� 0 )
		sizeof(tagVerColor) * GRID_VERMAX,		//	����� ����Ʈ ��
		&pVer,									//	��� �޸��� ���� ��ġ
		0);										//	��� ���( �⺻ 0 )

	if( pVer != NULL )
	{
		memmove( pVer,	m_sGridVer, sizeof(tagVerColor) * GRID_VERMAX	);
	}

	m_GridVB->Unlock();
}

VOID	cGrid::ArrowInit(VOID)
{
	ZeroMemory( m_sArrowVer, sizeof(tagVerColor) * 18 );

	//	x�� ȭ��ǥ
	m_sArrowVer[0].vPos		=	D3DXVECTOR3( GRID_WIDTH * 1.5f, 0, 0 );
	m_sArrowVer[1].vPos		=	D3DXVECTOR3( -GRID_WIDTH * 1.5f, 0, 0 );
	m_sArrowVer[0].dwColor	=	D3DCOLOR_XRGB( 255, 0, 0 );
	m_sArrowVer[1].dwColor	=	D3DCOLOR_XRGB( 255, 0, 0 );

	m_sArrowVer[2]			=	m_sArrowVer[0];
	m_sArrowVer[3].vPos		=	D3DXVECTOR3( GRID_WIDTH * 1.5f - GRID_WIDTH/10, 0, (FLOAT)GRID_WIDTH/10 );
	m_sArrowVer[3].dwColor	=	D3DCOLOR_XRGB( 255, 0, 0 );

	m_sArrowVer[4]			=	m_sArrowVer[0];
	m_sArrowVer[5].vPos		=	D3DXVECTOR3( GRID_WIDTH * 1.5f - GRID_WIDTH/10, 0, -(FLOAT)GRID_WIDTH/10 );
	m_sArrowVer[5].dwColor	=	D3DCOLOR_XRGB( 255, 0, 0 );

	//	z�� ȭ��ǥ
	m_sArrowVer[6].vPos		=	D3DXVECTOR3( 0, 0, GRID_WIDTH * 1.5f );
	m_sArrowVer[7].vPos		=	D3DXVECTOR3( 0, 0, -GRID_WIDTH * 1.5f );
	m_sArrowVer[6].dwColor	=	D3DCOLOR_XRGB( 0, 255, 0 );
	m_sArrowVer[7].dwColor	=	D3DCOLOR_XRGB( 0, 255, 0 );

	m_sArrowVer[8]			=	m_sArrowVer[6];
	m_sArrowVer[9].vPos		=	D3DXVECTOR3( GRID_WIDTH/10.0f, 0, GRID_WIDTH * 1.5f - GRID_WIDTH/10 );
	m_sArrowVer[9].dwColor	=	D3DCOLOR_XRGB( 0, 255, 0 );

	m_sArrowVer[10]			=	m_sArrowVer[6];
	m_sArrowVer[11].vPos	=	D3DXVECTOR3( -GRID_WIDTH/10.0f, 0, GRID_WIDTH * 1.5f - GRID_WIDTH/10 );
	m_sArrowVer[11].dwColor	=	D3DCOLOR_XRGB( 0, 255, 0 );

	//	y�� ȭ��ǥ
	m_sArrowVer[12].vPos		=	D3DXVECTOR3( 0, GRID_WIDTH * 1.5f, 0 );
	m_sArrowVer[13].vPos		=	D3DXVECTOR3( 0, -GRID_WIDTH * 1.5f, 0 );
	m_sArrowVer[12].dwColor		=	D3DCOLOR_XRGB( 255, 255, 0 );
	m_sArrowVer[13].dwColor		=	D3DCOLOR_XRGB( 255, 255, 0 );

	m_sArrowVer[14]				=	m_sArrowVer[12];
	m_sArrowVer[15].vPos		=	D3DXVECTOR3( GRID_WIDTH/10.0f, GRID_WIDTH * 1.5f - GRID_WIDTH/10, 0 );
	m_sArrowVer[15].dwColor		=	D3DCOLOR_XRGB( 255, 255, 0 );

	m_sArrowVer[16]				=	m_sArrowVer[12];
	m_sArrowVer[17].vPos		=	D3DXVECTOR3( -GRID_WIDTH/10.0f, GRID_WIDTH * 1.5f - GRID_WIDTH/10, 0 );
	m_sArrowVer[17].dwColor		=	D3DCOLOR_XRGB( 255, 255, 0 );

	if( FAILED(	JN_Base3D::m_pd3dDevice->CreateVertexBuffer(
			sizeof(tagVerColor) * 18,				//	���ۿ� �Ҵ��� ����Ʈ
			0,										//	������ Ư��( �⺻ 0 )
			tagVerColor::FVF_VER_COLOR,				//	FVF ����ü�� Ÿ��
			D3DPOOL_DEFAULT,						//	�޸� Ǯ
			&m_ArrowVB,								//	���ؽ����� ������
			0)))
	{
			return;
	}

	VOID *	pVer = NULL;

	//< ���� ���� 
	m_ArrowVB->Lock( 
		0,										//	����� ������ ��ġ ( �⺻ ó���̹Ƿ� 0 )
		sizeof(tagVerColor) * 18,				//	����� ����Ʈ ��
		&pVer,									//	��� �޸��� ���� ��ġ
		0);										//	��� ���( �⺻ 0 )

	if( pVer != NULL )
	{
		memmove( pVer,	m_sArrowVer, sizeof(tagVerColor) * 18	);
	}

	m_ArrowVB->Unlock();
}

VOID	cGrid::GridRender(VOID)
{
	//	���ؽ� ���ۿ� ��Ʈ���ҽ� ����
	m_pd3dDevice->SetStreamSource(
		0,							//	���� ��Ʈ���� �ƴϸ� 0
		m_GridVB,					//	��Ʈ�� ���� ���ؽ� ����
		0,							//	�������� ������
		sizeof(tagVerColor) );		//	���ؽ� ����ü�� ũ��

	//	FVF ���� ����
	m_pd3dDevice->SetFVF( tagVerColor::FVF_VER_COLOR );

	//	�׸���
	m_pd3dDevice->DrawPrimitive( 
		D3DPT_LINELIST,				//	�׸��� ���
		0,							//	�׸��� ������ �ε��� 
		GRID_VERMAX / 2 );			//	�׸��� ��ü ����
}

VOID	cGrid::ArrowRender(VOID)
{
	//	���ؽ� ���ۿ� ��Ʈ���ҽ� ����
	m_pd3dDevice->SetStreamSource(
		0,							//	���� ��Ʈ���� �ƴϸ� 0
		m_ArrowVB,					//	��Ʈ�� ���� ���ؽ� ����
		0,							//	�������� ������
		sizeof(tagVerColor) );		//	���ؽ� ����ü�� ũ��

	//	FVF ���� ����
	m_pd3dDevice->SetFVF( tagVerColor::FVF_VER_COLOR );

	//	�׸���
	m_pd3dDevice->DrawPrimitive( 
		D3DPT_LINELIST,				//	�׸��� ���
		0,							//	�׸��� ������ �ε��� 
		18 / 2 );					//	�׸��� ��ü ����
}