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



// 초기화
BOOL	cMainGame::InitWindow( VOID )
{
	//< 프로그램 실행 전체 패스 
	GetCurrentDirectory(_MAX_FNAME,m_strPath);

	//	버텍스 버퍼 초기화
	InitVertexBuffer();

	m_vScale = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );
	m_vTrans =	m_vRot	=	D3DXVECTOR3(0, 0, 0);

	//
	InitCamera();

	m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	return TRUE;
}

//Direct3D 초기화
HRESULT	cMainGame::Init3D( HWND hWnd , HINSTANCE hInst, BOOL bWindowMode, INT nWidth, INT nHeight )
{
	m_hWnd	= hWnd;
	//m_hInst	= hInst;

	//Direct3D 객체 인터페이스 생성
	m_pd3d = Direct3DCreate9( D3D_SDK_VERSION );

	//< 예외 처리 
	if( m_pd3d == NULL )
	{
		//< 에러 
		return E_FAIL;
	}

	//< 하드웨어 가속 여부 확인 (Caps)
	D3DCAPS9		caps;	//< 장치 정보 
	DWORD			dwVp;	//< 버텍스 프로세싱
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

	//< D3D파라메터 설정 
	D3DPRESENT_PARAMETERS		d3dpp;
	ZeroMemory( &d3dpp, sizeof(d3dpp) );//초기화

	d3dpp.BackBufferWidth			= nWidth;
	d3dpp.BackBufferHeight			= nHeight;
	d3dpp.BackBufferCount			= 1;
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat			= D3DFMT_X8R8G8B8;
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D24S8;	
	d3dpp.EnableAutoDepthStencil	= TRUE;	
	d3dpp.Windowed					= bWindowMode;

	//< 디바이스 생성
	if( FAILED(m_pd3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		sDevType,
		hWnd,
		dwVp,
		&d3dpp,
		&m_pd3dDevice)))
	{
		//< 디바이스 예외 처리 
		return E_FAIL;
	}

	//< 끝~~
	return S_OK;
}


//삭제
 VOID 	cMainGame::Release( VOID )
{
	SAFE_RELEASE( m_pVB );
	SAFE_RELEASE(m_pd3dDevice);//디바이스를 먼저 해제하고
	SAFE_RELEASE(m_pd3d);//Direct3D 를 해제한다.
}


// 업데이트
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

// 렌더
 VOID 	cMainGame::Render( VOID )
{
	if ( NULL == m_pd3dDevice )
		return;

	// 화면 소거		
	m_pd3dDevice->Clear(0,NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL,D3DCOLOR_XRGB(0,0,255),1,0);

	//렌더링 시작
	if ( SUCCEEDED(m_pd3dDevice->BeginScene()) )
	{
		// Rendering of scene objects can happen here
		//	행렬을 적용해야 한다.
		D3DXMATRIXA16 m_Scale, m_Trans, m_RotZ, m_RotY, m_RotX, m_Total;

		//	항등행렬로 만든다. 즉, 행렬의 초기화
		D3DXMatrixIdentity( &m_Scale );
		D3DXMatrixIdentity( &m_Trans );
		D3DXMatrixIdentity( &m_RotZ );
		D3DXMatrixIdentity( &m_RotY );
		D3DXMatrixIdentity( &m_RotX );

		//	버텍스의 크기 변경
		D3DXMatrixScaling( &m_Scale, m_vScale.x,m_vScale.y, m_vScale.z );

		//	버텍스의 이동량 변경
		D3DXMatrixTranslation( &m_Trans, m_vTrans.x, m_vTrans.y, m_vTrans.z );

		//	버텍스의 Z축 회전
		D3DXMatrixRotationX( &m_RotX, m_vRot.x * PI / 180 );
		D3DXMatrixRotationY( &m_RotY, m_vRot.y * PI / 180 );
		D3DXMatrixRotationZ( &m_RotZ, m_vRot.z * PI / 180 );

		//	행렬의 통합( 순서에 주의 )
		m_Total	=	m_Scale * m_RotX * m_RotY * m_RotZ * m_Trans;

		//	행렬을 월드행렬로 지정
		m_pd3dDevice->SetTransform( D3DTS_WORLD, &m_Total );





		//버텍스 렌더링
		//	버텍스 버퍼와 스트림소스 연결
		m_pd3dDevice->SetStreamSource(
			0,								//	다중 스트림이 아니면 0
			m_pVB,							//	스트림 연결 버텍스 버퍼
			0,								//	데이터의 시작점
			m_dwFVFSize );					//	버텍스 구조체의 크기

		//	FVF 포맷 설정
		m_pd3dDevice->SetFVF( tagVerColor::FVF_VER_COLOR );

		//	그리기
		m_pd3dDevice->DrawPrimitive( 
			D3DPT_TRIANGLELIST,					//	그리는 방식
			0,									//	그리기 시작학 인덱스 
			VERTEX_MAX / 3 );					//	그리는 개체 개수

		m_pd3dDevice->EndScene();//렌더링 종료
	}

	// Present the backbuffer contents to the display,화면 출력
	m_pd3dDevice->Present(NULL,NULL,NULL,NULL);

	HDC hdc	=	GetDC(m_hWnd);

	WCHAR szBuf[256];


	swprintf_s( szBuf, L"x회전 : %f", m_vRot.x );
	TextOutW( hdc, 0, 0, szBuf, wcslen(szBuf) );
	
	swprintf_s( szBuf, L"y회전 : %f", m_vRot.y );
	TextOutW( hdc, 0, 20, szBuf, wcslen(szBuf) );

	swprintf_s( szBuf, L"z회전 : %f", m_vRot.z );
	TextOutW( hdc, 0, 40, szBuf, wcslen(szBuf) );

	ReleaseDC( m_hWnd, hdc );

	
}

/************************************************************************/
/* Event                                                                */
/************************************************************************/
// 메세지 프로시져
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

	//	큐브 앞 
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

	//	큐브 뒤
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

	//	큐브 위
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

	// 큐브 아래
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

	//	큐브 오른쪽
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

	//	큐브 왼쪽
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
	


	// 버텍스 버퍼 생성 
	if( FAILED(	m_pd3dDevice->CreateVertexBuffer(
		m_dwFVFSize * VERTEX_MAX,					//	버퍼에 할당할 바이트
		0,										//	버퍼의 특성( 기본 0 )
		tagVerColor::FVF_VER_COLOR,		//	FVF 구조체의 타입
		D3DPOOL_DEFAULT,						//	메모리 풀
		&m_pVB,									//	버텍스버퍼 포인터
		0)))
	{
		return;
	}	

	
	VOID *	pVer = NULL;

	//< 정보 설정 
	m_pVB->Lock( 
		0,											//	잠금을 시작할 위치 ( 기본 처음이므로 0 )
		m_dwFVFSize * VERTEX_MAX,	//	잠금할 바이트 수
		&pVer,										//	잠금 메모리의 시작 위치
		0);											//	잠금 방법( 기본 0 )

	if( pVer != NULL )
	{
		memmove( pVer,	m_sVer, m_dwFVFSize * VERTEX_MAX	);
	}

	m_pVB->Unlock();
}

//< 기본 카메라 설정
HRESULT	cMainGame::InitCamera(  VOID  )
{
	//< 카메라 스페이스 설정
	D3DXMATRIXA16		matView;

	//< 카메라 위치,카메라 시점, 카메라 상향벡터 설정
	D3DXVECTOR3		vEye( 0.0f, 10.0f, -20.0f );
	D3DXVECTOR3		vLookAt( 0.0f, 0.0f, 0.0f );
	D3DXVECTOR3		vUp( 0.0f, 1.0f, 0.0f );

	//< 카메라 공간으로 행렬 생성
	D3DXMatrixLookAtLH( &matView, &vEye, &vLookAt, &vUp );

	////< 공간 적용 ( 공간 적용은 DX타입의 행렬을 써야 하기 때문에 변환한다 )
	m_pd3dDevice->SetTransform( D3DTS_VIEW , &matView );

	////< 투영 스페이스 설정
	D3DXMATRIXA16		matProj;

	//< 투영 설정 
	D3DXMatrixPerspectiveFovLH( 
		&matProj, 
		D3DX_PI / 4,			//< 시야각
		WIN_WIDTH / WIN_HEIGHT,	//< 종횡비
		1.0f,					//< 시야 최소치
		1000.0f					//< 시야 최대치
		);

	//< 투영 적용
	m_pd3dDevice->SetTransform( D3DTS_PROJECTION , &matProj );
	return S_OK;
}















