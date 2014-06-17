#include "StdAfx.h"
#include "cMainGame.h"

#include "cMK_Camera.h"
#include "cFPSCamera.h"
#include "cGrid.h"

cMainGame::cMainGame( VOID )
{
}

cMainGame::~cMainGame( VOID )
{
}


/************************************************************************/
/* Init                                                                 */
/************************************************************************/
///< 초기화
BOOL	cMainGame::InitWindow( VOID )
{
	//< 프로그램 실행 전체 패스 
	GetCurrentDirectory(_MAX_FNAME,m_strPath);

	//	버텍스 버퍼 초기화
	InitVertexBuffer();

	InitCamera();

	m_pGrid	=	new cGrid;

	m_pGrid->Init( 20 );

	tagFontInfo	Data = { 20, "궁서체" };

	FONT_MGR->AddFont( JN_Base3D::m_pd3dDevice, "기본", Data );

	m_XFile.LoadFile( JN_Base3D::m_pd3dDevice, "tiger.x" );

	m_XFileAni.SetScale( 0.1f, 0.1f, 0.1f );
	m_XFileAni.Load( JN_Base3D::m_pd3dDevice, "tiny.x" );

	JN_Base3D::m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	
	return TRUE;
}

///< 삭제
 VOID 	cMainGame::Release( VOID )
{
	JN_Base3D::Release();

	if( m_pCamera != NULL )
	{
		delete m_pCamera;
		m_pCamera	=	NULL;
	}

	if( m_pGrid != NULL )
	{
		delete m_pGrid;
		m_pGrid	=	NULL;
	}
}


///< 업데이트
 VOID 	cMainGame::Update( VOID )
{
	m_pCamera->KeyInput();
}

///< 렌더
 VOID 	cMainGame::Render( VOID )
{
	if( JN_Base3D::m_pd3dDevice != NULL )
	{
		//< 화면 소거 
		if( JN_Base3D::ClearScreen(D3DCOLOR_XRGB(0,0,255)) != S_OK )	
		{
			//< 에러 처리
			return;
		}

		//< 렌더링 시작
		if( JN_Base3D::RenderStart() != S_OK )	
		{
			//< 에러 처리
			return;
		}

		///////////////////////////////////////////////////////////////////////////////
		// 출력 부분

		m_XFile.Render();
		
		m_XFileAni.Render(0.016f);

		m_pGrid->Render();

		FONT_MGR->DrawFont( 0, 60, "x : %d, y %d", m_ptMousePos.x, m_ptMousePos.y );
				
		///////////////////////////////////////////////////////////////////////////////

		//< 렌더링 끝
		if( JN_Base3D::RenderEnd() != S_OK )	
		{
			//< 에러 처리 	
		}

		//< 화면 출력
		if( JN_Base3D::Present() != S_OK )	
		{
			//< 에러 처리 	
		}
	}
}

/************************************************************************/
/* Event                                                                */
/************************************************************************/
///< 메세지 프로시져
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

	case WM_MOUSEMOVE:
		{
		}
		break;

	case WM_RBUTTONDOWN:
		{
		}
		break;

	case WM_RBUTTONUP:
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
	//	D3DXVECTOR3			vPoint[8]	=	{
	//	D3DXVECTOR3(-1,  1, -1 ),
	//	D3DXVECTOR3( 1,  1, -1 ), 
	//    D3DXVECTOR3(-1,	 1,  1 ),
	//	D3DXVECTOR3( 1,  1,  1 ),
	//    D3DXVECTOR3(-1, -1, -1 ), 
	//	D3DXVECTOR3( 1, -1, -1 ),
	//    D3DXVECTOR3(-1, -1,  1 ), 
	//	D3DXVECTOR3( 1, -1,  1 )};

	//int i = 0;
}

//< 기본 카메라 설정
HRESULT	cMainGame::InitCamera(  VOID  )
{
	//< 카메라 위치,카메라 시점
	D3DXVECTOR3		vEye( 0.0f, 10.0f, -20.0f );
	D3DXVECTOR3		vLookAt( 0.0f, 0.0f, 0.0f );

	m_pCamera	=	new cFPSCamera;

	m_pCamera->InitCam( JN_Base3D::m_pd3dDevice, &vEye, &vLookAt );
	return S_OK;
}