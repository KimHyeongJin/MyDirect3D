#include "StdAfx.h"
#include "cMainGame.h"


extern HWND g_hwnd;



cMainGame::cMainGame( VOID )
{
	m_pd3d = NULL;
	m_hWnd = NULL;
}

cMainGame::~cMainGame( VOID )
{
}



// �ʱ�ȭ
BOOL	cMainGame::InitWindow( VOID )
{
	//< ���α׷� ���� ��ü �н� 
	GetCurrentDirectory(_MAX_FNAME,m_strPath);

	//	���ؽ� ���� �ʱ�ȭ
	InitVertexBuffer();

	m_vScale = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );
	m_vTrans =	m_vRot	=	D3DXVECTOR3(0, 0, 0);

	//
	InitCamera();

	m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	return TRUE;
}

//Direct3D �ʱ�ȭ
HRESULT	cMainGame::Init3D( HWND hWnd , HINSTANCE hInst, BOOL bWindowMode, INT nWidth, INT nHeight )
{
	m_hWnd	= hWnd;
	//m_hInst	= hInst;

	//Direct3D ��ü �������̽� ����
	m_pd3d = Direct3DCreate9( D3D_SDK_VERSION );

	//< ���� ó�� 
	if( m_pd3d == NULL )
	{
		//< ���� 
		return E_FAIL;
	}

	//< �ϵ���� ���� ���� Ȯ�� (Caps)
	D3DCAPS9		caps;	//< ��ġ ���� 
	DWORD			dwVp;	//< ���ؽ� ���μ���
	D3DDEVTYPE		sDevType;

	m_pd3d->GetDeviceCaps(D3DADAPTER_DEFAULT , D3DDEVTYPE_HAL, &caps);

	if( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
	{
		dwVp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
		sDevType = D3DDEVTYPE_HAL;
	}
	else
	{
		dwVp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
		sDevType = D3DDEVTYPE_SW;
	}

	//< D3D�Ķ���� ���� 
	D3DPRESENT_PARAMETERS		d3dpp;
	ZeroMemory( &d3dpp, sizeof(d3dpp) );//�ʱ�ȭ

	d3dpp.BackBufferWidth			= nWidth;
	d3dpp.BackBufferHeight			= nHeight;
	d3dpp.BackBufferCount			= 1;
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat			= D3DFMT_X8R8G8B8;
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D24S8;	
	d3dpp.EnableAutoDepthStencil	= TRUE;	
	d3dpp.Windowed					= bWindowMode;

	//< ����̽� ����
	if( FAILED(m_pd3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		sDevType,
		hWnd,
		dwVp,
		&d3dpp,
		&m_pd3dDevice)))
	{
		//< ����̽� ���� ó�� 
		return E_FAIL;
	}

	//< ��~~
	return S_OK;
}


//����
 VOID 	cMainGame::Release( VOID )
{
	SAFE_RELEASE( m_pVB );
	SAFE_RELEASE(m_pd3dDevice);//����̽��� ���� �����ϰ�
	SAFE_RELEASE(m_pd3d);//Direct3D �� �����Ѵ�.
}


// ������Ʈ
 VOID 	cMainGame::Update( VOID )
{
	if( GetAsyncKeyState( VK_LEFT ) & 0x8000 )
	{
		m_vRot.y++;
	}

	if( GetAsyncKeyState( VK_RIGHT ) & 0x8000 )
	{
		m_vRot.y--;
	}

	if( GetAsyncKeyState( VK_UP) & 0x8000 )
	{
		m_vRot.x++;
	}

	if( GetAsyncKeyState( VK_DOWN ) & 0x8000 )
	{
		m_vRot.x--;
	}

	if( GetAsyncKeyState( '1') & 0x8000 )
	{
		m_vRot.z++;
	}

	if( GetAsyncKeyState( '2' ) & 0x8000 )
	{
		m_vRot.z--;
	}

}

// ����
 VOID 	cMainGame::Render( VOID )
{
	if ( NULL == m_pd3dDevice )
		return;

	// ȭ�� �Ұ�		
	m_pd3dDevice->Clear(0,NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL,D3DCOLOR_XRGB(0,0,255),1,0);

	//������ ����
	if ( SUCCEEDED(m_pd3dDevice->BeginScene()) )
	{
		// Rendering of scene objects can happen here
		//	����� �����ؾ� �Ѵ�.
		D3DXMATRIXA16 m_Scale, m_Trans, m_RotZ, m_RotY, m_RotX, m_Total;

		//	�׵���ķ� �����. ��, ����� �ʱ�ȭ
		D3DXMatrixIdentity( &m_Scale );
		D3DXMatrixIdentity( &m_Trans );
		D3DXMatrixIdentity( &m_RotZ );
		D3DXMatrixIdentity( &m_RotY );
		D3DXMatrixIdentity( &m_RotX );

		//	���ؽ��� ũ�� ����
		D3DXMatrixScaling( &m_Scale, m_vScale.x,m_vScale.y, m_vScale.z );

		//	���ؽ��� �̵��� ����
		D3DXMatrixTranslation( &m_Trans, m_vTrans.x, m_vTrans.y, m_vTrans.z );

		//	���ؽ��� Z�� ȸ��
		D3DXMatrixRotationX( &m_RotX, m_vRot.x * PI / 180 );
		D3DXMatrixRotationY( &m_RotY, m_vRot.y * PI / 180 );
		D3DXMatrixRotationZ( &m_RotZ, m_vRot.z * PI / 180 );

		//	����� ����( ������ ���� )
		m_Total	=	m_Scale * m_RotX * m_RotY * m_RotZ * m_Trans;

		//	����� ������ķ� ����
		m_pd3dDevice->SetTransform( D3DTS_WORLD, &m_Total );





		//���ؽ� ������
		//	���ؽ� ���ۿ� ��Ʈ���ҽ� ����
		m_pd3dDevice->SetStreamSource(
			0,								//	���� ��Ʈ���� �ƴϸ� 0
			m_pVB,							//	��Ʈ�� ���� ���ؽ� ����
			0,								//	�������� ������
			m_dwFVFSize );					//	���ؽ� ����ü�� ũ��

		//	FVF ���� ����
		m_pd3dDevice->SetFVF( tagVerColor::FVF_VER_COLOR );

		//	�׸���
		m_pd3dDevice->DrawPrimitive( 
			D3DPT_TRIANGLELIST,					//	�׸��� ���
			0,									//	�׸��� ������ �ε��� 
			VERTEX_MAX / 3 );					//	�׸��� ��ü ����

		m_pd3dDevice->EndScene();//������ ����
	}

	// Present the backbuffer contents to the display,ȭ�� ���
	m_pd3dDevice->Present(NULL,NULL,NULL,NULL);

	HDC hdc	=	GetDC(m_hWnd);

	WCHAR szBuf[256];


	swprintf_s( szBuf, L"xȸ�� : %f", m_vRot.x );
	TextOutW( hdc, 0, 0, szBuf, wcslen(szBuf) );
	
	swprintf_s( szBuf, L"yȸ�� : %f", m_vRot.y );
	TextOutW( hdc, 0, 20, szBuf, wcslen(szBuf) );

	swprintf_s( szBuf, L"zȸ�� : %f", m_vRot.z );
	TextOutW( hdc, 0, 40, szBuf, wcslen(szBuf) );

	ReleaseDC( m_hWnd, hdc );

	
}

/************************************************************************/
/* Event                                                                */
/************************************************************************/
// �޼��� ���ν���
LRESULT	cMainGame::MainProc(HWND hWnd,UINT iMessage ,WPARAM wParam,LPARAM lParam)
{
	switch(iMessage)
	{
	case WM_TIMER:
		break;

	case WM_LBUTTONDOWN:
		{
		}
		break;

	case WM_RBUTTONDOWN:
		{
		}
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
			//(esc key)
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

VOID	cMainGame::InitVertexBuffer(VOID)
{
		D3DXVECTOR3			vPoint[8]	=	{
		D3DXVECTOR3(-1,  1, -1 ),
		D3DXVECTOR3( 1,  1, -1 ), 
	    D3DXVECTOR3(-1,	 1,  1 ),
		D3DXVECTOR3( 1,  1,  1 ),
	    D3DXVECTOR3(-1, -1, -1 ), 
		D3DXVECTOR3( 1, -1, -1 ),
	    D3DXVECTOR3(-1, -1,  1 ), 
		D3DXVECTOR3( 1, -1,  1 )};

	//	ť�� �� 
	m_sVer[0].vPos		=	vPoint[0];
	m_sVer[1].vPos		=	vPoint[1];
	m_sVer[2].vPos		=	vPoint[4];
	m_sVer[0].dwColor	=	0xff00ff00;
	m_sVer[1].dwColor	=	0xff00ff00;
	m_sVer[2].dwColor	=	0xff00ff00;

	m_sVer[3].vPos		=	vPoint[1];
	m_sVer[4].vPos		=	vPoint[5];
	m_sVer[5].vPos		=	vPoint[4];
	m_sVer[3].dwColor	=	0xff00ff00;
	m_sVer[4].dwColor	=	0xff00ff00;
	m_sVer[5].dwColor	=	0xff00ff00;

	//	ť�� ��
	m_sVer[6].vPos		=	vPoint[3];
	m_sVer[7].vPos		=	vPoint[2];
	m_sVer[8].vPos		=	vPoint[6];
	m_sVer[6].dwColor	=	0xff00ffff;
	m_sVer[7].dwColor	=	0xff00ffff;
	m_sVer[8].dwColor	=	0xff00ffff;

	m_sVer[9].vPos		=	vPoint[3];
	m_sVer[10].vPos		=	vPoint[6];
	m_sVer[11].vPos		=	vPoint[7];
	m_sVer[9].dwColor	=	0xff00ffff;
	m_sVer[10].dwColor	=	0xff00ffff;
	m_sVer[11].dwColor	=	0xff00ffff;

	//	ť�� ��
	m_sVer[12].vPos		=	vPoint[0];
	m_sVer[13].vPos		=	vPoint[2];
	m_sVer[14].vPos		=	vPoint[1];
	m_sVer[12].dwColor	=	0xffff0000;
	m_sVer[13].dwColor	=	0xffff0000;
	m_sVer[14].dwColor	=	0xffff0000;

	m_sVer[15].vPos		=	vPoint[2];
	m_sVer[16].vPos		=	vPoint[3];
	m_sVer[17].vPos		=	vPoint[1];
	m_sVer[15].dwColor	=	0xffff0000;
	m_sVer[16].dwColor	=	0xffff0000;
	m_sVer[17].dwColor	=	0xffff0000;

	// ť�� �Ʒ�
	m_sVer[18].vPos		=	vPoint[4];
	m_sVer[19].vPos		=	vPoint[5];
	m_sVer[20].vPos		=	vPoint[6];
	m_sVer[18].dwColor	=	0xffff00ff;
	m_sVer[19].dwColor	=	0xffff00ff;
	m_sVer[20].dwColor	=	0xffff00ff;

	m_sVer[21].vPos		=	vPoint[5];
	m_sVer[22].vPos		=	vPoint[7];
	m_sVer[23].vPos		=	vPoint[6];
	m_sVer[21].dwColor	=	0xffff00ff;
	m_sVer[22].dwColor	=	0xffff00ff;
	m_sVer[23].dwColor	=	0xffff00ff;

	//	ť�� ������
	m_sVer[24].vPos		=	vPoint[1];
	m_sVer[25].vPos		=	vPoint[3];
	m_sVer[26].vPos		=	vPoint[5];
	m_sVer[24].dwColor	=	0xffffffff;
	m_sVer[25].dwColor	=	0xffffffff;
	m_sVer[26].dwColor	=	0xffffffff;

	m_sVer[27].vPos		=	vPoint[3];
	m_sVer[28].vPos		=	vPoint[7];
	m_sVer[29].vPos		=	vPoint[5];
	m_sVer[27].dwColor	=	0xffffffff;
	m_sVer[28].dwColor	=	0xffffffff;
	m_sVer[29].dwColor	=	0xffffffff;

	//	ť�� ����
	m_sVer[30].vPos		=	vPoint[0];
	m_sVer[31].vPos		=	vPoint[4];
	m_sVer[32].vPos		=	vPoint[6];
	m_sVer[30].dwColor	=	0xffdddddd;
	m_sVer[31].dwColor	=	0xffdddddd;
	m_sVer[32].dwColor	=	0xffdddddd;

	m_sVer[33].vPos		=	vPoint[0];
	m_sVer[34].vPos		=	vPoint[6];
	m_sVer[35].vPos		=	vPoint[2];
	m_sVer[33].dwColor	=	0xffdddddd;
	m_sVer[34].dwColor	=	0xffdddddd;
	m_sVer[35].dwColor	=	0xffdddddd;

	m_dwFVFSize		=	sizeof(tagVerColor);
	


	// ���ؽ� ���� ���� 
	if( FAILED(	m_pd3dDevice->CreateVertexBuffer(
		m_dwFVFSize * VERTEX_MAX,					//	���ۿ� �Ҵ��� ����Ʈ
		0,										//	������ Ư��( �⺻ 0 )
		tagVerColor::FVF_VER_COLOR,		//	FVF ����ü�� Ÿ��
		D3DPOOL_DEFAULT,						//	�޸� Ǯ
		&m_pVB,									//	���ؽ����� ������
		0)))
	{
		return;
	}	

	
	VOID *	pVer = NULL;

	//< ���� ���� 
	m_pVB->Lock( 
		0,											//	����� ������ ��ġ ( �⺻ ó���̹Ƿ� 0 )
		m_dwFVFSize * VERTEX_MAX,	//	����� ����Ʈ ��
		&pVer,										//	��� �޸��� ���� ��ġ
		0);											//	��� ���( �⺻ 0 )

	if( pVer != NULL )
	{
		memmove( pVer,	m_sVer, m_dwFVFSize * VERTEX_MAX	);
	}

	m_pVB->Unlock();
}

//< �⺻ ī�޶� ����
HRESULT	cMainGame::InitCamera(  VOID  )
{
	//< ī�޶� �����̽� ����
	D3DXMATRIXA16		matView;

	//< ī�޶� ��ġ,ī�޶� ����, ī�޶� ���⺤�� ����
	D3DXVECTOR3		vEye( 0.0f, 10.0f, -20.0f );
	D3DXVECTOR3		vLookAt( 0.0f, 0.0f, 0.0f );
	D3DXVECTOR3		vUp( 0.0f, 1.0f, 0.0f );

	//< ī�޶� �������� ��� ����
	D3DXMatrixLookAtLH( &matView, &vEye, &vLookAt, &vUp );

	////< ���� ���� ( ���� ������ DXŸ���� ����� ��� �ϱ� ������ ��ȯ�Ѵ� )
	m_pd3dDevice->SetTransform( D3DTS_VIEW , &matView );

	////< ���� �����̽� ����
	D3DXMATRIXA16		matProj;

	//< ���� ���� 
	D3DXMatrixPerspectiveFovLH( 
		&matProj, 
		D3DX_PI / 4,			//< �þ߰�
		WIN_WIDTH / WIN_HEIGHT,	//< ��Ⱦ��
		1.0f,					//< �þ� �ּ�ġ
		1000.0f					//< �þ� �ִ�ġ
		);

	//< ���� ����
	m_pd3dDevice->SetTransform( D3DTS_PROJECTION , &matProj );
	return S_OK;
}















