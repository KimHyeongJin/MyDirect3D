#include "StdAfx.h"
#include "cMainGame.h"

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

	//< 버텍스 버퍼 초기화
	InitVertexBuffer();

	return TRUE;
}

///< 삭제
 VOID 	cMainGame::Release( VOID )
{
	//버텍스 버퍼 해제
	ReleaseVertexBuffer();

	JN_Base3D::Release();
}


///< 업데이트
 VOID 	cMainGame::Update( VOID )
{
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
		RenderVertexBuffer();
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
			m_sVer[1].x -= 50.0f;
			m_sVer[3].x -= 50.0f;
	
			UpdateVertexBuffer();
		}
		break;

	case WM_RBUTTONDOWN:
		{
			m_sVer[1].x += 50.0f;
			m_sVer[3].x += 50.0f;
			UpdateVertexBuffer();
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

VOID cMainGame::InitVertexBuffer(VOID)
{
	m_sVer[0].x = 200.0f;
	m_sVer[0].y = 200.0f;
	m_sVer[0].z = 0.0f;
	m_sVer[0].rhw = 1.0f;
	m_sVer[0].dwColor = 0xffff0000;

	m_sVer[1].x = 600.0f;
	m_sVer[1].y = 200.0f;
	m_sVer[1].z = 0.0f;
	m_sVer[1].rhw = 1.0f;
	m_sVer[1].dwColor = 0xff00ff00;

	m_sVer[2].x = 200.0f;
	m_sVer[2].y = 300.0f;
	m_sVer[2].z = 0.0f;
	m_sVer[2].rhw = 1.0f;
	m_sVer[2].dwColor = 0xffff0000;

	m_sVer[3].x = 600.0f;
	m_sVer[3].y = 300.0f;
	m_sVer[3].z = 0.0f;
	m_sVer[3].rhw = 1.0f;
	m_sVer[3].dwColor = 0xff00ff00;

	if ( JN_Base3D::m_pd3dDevice != NULL )
	{
		if ( FAILED( JN_Base3D::m_pd3dDevice->CreateVertexBuffer( sizeof(sVER_RHW_COLOR)*VERTEX_MAX, 0, sVER_RHW_COLOR::FVF_VER_RHW_COLOR, D3DPOOL_DEFAULT, &m_pVB, 0 ) ) )
		{
			return;
		}

		UpdateVertexBuffer();
	}
}

VOID cMainGame::ReleaseVertexBuffer()
{
	SAFE_RELEASE( m_pVB );
}

VOID cMainGame::RenderVertexBuffer()
{
	//1. 스트림 소스 지정. 스트림 소스를 버텍스 버퍼와 연결하여 버퍼의 기하정보를 렌더링 파이프라인에 보낼 수 있도록 한다.
	//버텍스 버퍼와 스트림소스 연결
	JN_Base3D::m_pd3dDevice->SetStreamSource( 
		0,										//다중 스트림이 아니면 0 
		m_pVB,									//스트림과 연결하고자 하는 버텍스 버퍼로의 포인터
		0,										//데이터의 시작점
		sizeof(sVER_RHW_COLOR) );				//버텍스 구조체의 크기

	//2. 버텍스 포맷을 지정한다. 이후의 드로잉 호출에서 이용될 버텍스 포맷을 지정하는 단계이다.
	//FVF 포맷 설정
	JN_Base3D::m_pd3dDevice->SetFVF( sVER_RHW_COLOR::FVF_VER_RHW_COLOR );

	//3. 인덱스 버퍼를 지정한다. 만약 인덱스 버퍼를 이용한다면 이후의 드로잉 과정에서 이용될 인덱스 버퍼를 지정해야 하는데,
	// 한번에 하나의 인덱스 버퍼만 이용할 수 있다. 따라서 다른 인덱스 버퍼를 가진 물체를 그려야 한다면 인덱스 버퍼를 전환하는 과정이 필요하다.
	//인덱스 버퍼를 지정하는 방법은 다음과 같다.
	//JN_Base3D::m_pd3dDevice->SetIndices( _ib );

	//그리기. 이 메서드는 인덱스 정보를 이용하지 않는 기본형을 그리는데 이용 된다.
	JN_Base3D::m_pd3dDevice->DrawPrimitive( 
		D3DPT_TRIANGLESTRIP,						//그리고자 하는 기본형 타입
		0,										//버텍스 읽기를 시작할 버텍스 스트림 요소의 인덱스
		2 );									//그리고자 하는 기본형의 수
}

VOID cMainGame::UpdateVertexBuffer(VOID)
{
	VOID* pVer = NULL;

	//< 정보 설정
	m_pVB->Lock( 0, sizeof(sVER_RHW_COLOR)*VERTEX_MAX, &pVer, 0 );
	//If the method succeeds, the return value is D3D_OK. If the method fails, the return value can be D3DERR_INVALIDCALL.

	if ( pVer != NULL )
	{
		memmove( pVer, m_sVer, sizeof(sVER_RHW_COLOR)*VERTEX_MAX );
	}
	m_pVB->Unlock();
}
/*
http://blog.naver.com/gkqxhq324456?Redirect=Log&logNo=110146202869
Lock(), Unlock()
버텍스/인덱스 버퍼 메모리에 접근하기 위해서 내부 메모리 컨텐트로의 포인터가 필요하다
포인터를 얻기 위해서 Lock 메서드를 이용하며, 이용이 끝난뒤에는 반드시 Unlock 메서드를 이용해서 버퍼의 잠금을 해제 해야 한다.


http://blog.naver.com/gkqxhq324456?Redirect=Log&logNo=110146202869
메모리 풀,FVF


http://blog.naver.com/gkqxhq324456?Redirect=Log&logNo=110146202869

출처 http://blog.daum.net/artofcom/8
RHW란 무엇인가.
아래 펌글들을 종합하면 아래와 같은 정의를 내릴 수 있다.
 
rhw라고 하는 것은 reciprocal homogeneous w 의 약자로 동차좌표 'w의 역수' 라는 뜻. 즉, 1/w.
왜 이것을 사용하느냐 하면, perspective 변환 행렬을 거치면 나오는 행렬값을 우리가 원하는 동차좌표로 바꾸기 위해 w로 4번째 성분을 나눠야 하는데, 이것의 역수를 미리 정의해 놓은 것이 rhw 라는 얘기가 되겠다.
 
또한 특징으로는, D3DFVF_XYZRHW를 사용할 경우, 이것은 파이프라인을 이미 처리된 정보로 간주하므로, 2D를 바로 사용하기에 용이하다는 것이다.
 

 
-------------------------------------------------------------------------------------------
 
 


게임에서 User Interface 를 화면에 렌더링할때 
다음 두가지 방법에서 택일한다.
RHW, 동차좌표계 로서 위치를 지정하는 방법과 
Orthogonal로서 렌더링하는 방법이 있다.
 
1. RHW
D3DFVF_XYZRHW는 변환 된 정점의 위치 좌표를 나타내므로 파이프라인에서 변환를 수행할수 없다. 그래서 화면에서 UI를 
이동 시키려면 직접 정점버퍼를 건드려야 한다. 아주 불편하다.
그리고 해상도가 변경되면 상대적으로 작아진다.
(0, 0)은 클라이언트 영역의 왼쪽상단을 나타낸다.

2. Orthogonal Projection
직교 투영 행렬을 사용하여 정점 변환이 수행가능하도록한다. 
화면상에서 UI 이동 및 회전을 쉽게 설정할 수 있는 것이 장점 이다.
D3DXMatrixOrthoOffCenterLH 함수를 이용하여 투영 행렬을 클라이언트 영역과 일치시킬수 있다.
 (0, 0) ~ (width, height)
2/(r-l)      0              0             0 
0             2/(t-b)      0             0 
0             0              1/(zf-zn)  0 
(l+r)/(l-r) (t+b)/(b-t) zn/(zn-zf) 1

기본값은 다음과 같이 설정한다. 
l = -w/2 
r = w/2 
b = -h/2 
t = h/2
코드:
// 다음과 같이 설정하면 클라이언트 영역과 일치 시킬수 있다.
// 단 왼쪽하단 부분이 (0, 0) 이다.
D3DXMatrixOrthoOffCenterLH ( &m_matProj, 0, m_dwWidth, 0, m_dwHeight, m_fNearZ, m_fFarZ);
 

왼쪽 상단을 0,0 으로 맞출려고 (0~w, -h~0) 으로 설정했는데 안되네요. 
그냥 왼쪽 하단으로 쓰는것이 정점을 +값만으로 쉽게 생각할수 있으니까 편할듯하네요.

UI는 마지막에 View , World 등을 단위행렬로 세팅하고 
z-buffer를 끄고 렌더링하여 항상 위로 올라오게 한다.
D3DFVF_XYZRHW - 이 플래그는 변환된 정점의 위치를 포함한다.
이것은 X,Y요소가 스크린 공간에 있으며 Z요소는 뷰 평면으로부터의 거리를 나타내며 RHW라는 추가 부동 소수 점수는 역동차 W좌표를 저장한다는 것을 위미한다.
이것은 D3DFVF_NORMAL 플래그와 같이 쓰일수 없다.
RHW 동차 좌표계의 w값 이값이 있으면 변환이 완료된 정점이다. 
 
----------------------------------------------------------------------------------------

W는 Homogeneous coordinates의 네번째 성분이고 homogeneous coordinates 는 우리말로 동치 좌표라고 합니다.
일반적으로 3차원 좌표변환 행렬로 4*4 행렬을 사용하는데.. 그렇게 되면 버텍스 좌표계 값은 (x,y,z,1)로 사용합니다.
perspective 변환 행렬을 적용하고 나면 버텍스 좌표값의 네번째 성분이 1이 아닌 값이 나오게 되는데..
이렇게 얻어지는 좌표값을 보통 (x,y,z,w)라고 표시합니다.
이때 이런 좌표값을 동치 좌표라고 합니다. 실제로 스크린상의 좌표값으로 사용하기 위해서는 동차좌표가 아닌 일반적인 좌표로 변환을 해야 하는데.. 좌표의 각성분을 w로 나누어서 구하게 됩니다. 즉, (x/w, y/w, z/w, w/w) = (x/w, y/w, z/w, 1) 이 되고 네째 성분 값이 1인 일반적인 좌표로 바뀌죠.
rhw라고 하는 것은 reciprocal homogeneous w 의 약자로 동차좌표 'w의 역수' 라는 뜻입니다. 즉, 1/w 를 말하죠.
위에서 동차좌표를 일반적인 좌표로 변환하기 위해서 w로 나누었는데, 컴퓨터에서는 나누기 계산이 느리므로 1/w를 한번만 구해서 각성분에다 1/w를 곱하는 식으로 계산을 처리합니다.
그래서 direct3d에서는 w의 역수를 rhw라고 이름하고 따로 저장하는 거죠.
 
그런데 직접 행렬 변환을 처리할 목적이 아니라면 이런 부분은 굳이 알지 못하더라도 물체의 좌표를 담은 오브젝트 좌표값만 넘겨주면 위에서 언급한 계산들은 세팅해준 행렬에 따라 자동으로 알아서 처리해주므로 신경쓰지 않아도 됩니다. 좌표변환의 전과정을 직접 처리할게 아니라면 rhw는 크게 신경쓰지 않아도 됩니다. 그냥 변환 행렬만 제대로 세팅하면 되지요.
*/