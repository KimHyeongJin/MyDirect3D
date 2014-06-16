#include "stdafx.h"
#include "JN_Base3D.h"

#if 0
namespace JN_Base3D
{
	HINSTANCE			m_hInst			= NULL;	//인스턴스의 핸들 선언
	HWND				m_hWnd			= NULL;	//윈두오 핸들
	LPDIRECT3D9			m_pd3d			= NULL;	//< iDirect 객체 인터페이스 얻기
	LPDIRECT3DDEVICE9	m_pd3dDevice	= NULL;	//< 장치 디바이스 얻기

	//< d3d초기화
	HRESULT Init3D( HWND hWnd, HINSTANCE hInst, BOOL bWindowMode, INT nWidth, INT nHeight )
	{
		m_hWnd = hWnd;
		m_hInst = hInst;

		//< d3d 객체 인터페이스 생성
		m_pd3d = Direct3DCreate9( D3D_SDK_VERSION );

		//< 예외 처리
		if ( m_pd3d == NULL )
		{
			//< 에러
			return E_FAIL;
		}

		//< 하드웨어 가속 여부 확인(Caps)
		D3DCAPS9	caps;	//< 장치 정보
		DWORD		dwVp;	//< 버텍스 프로세싱
		D3DDEVTYPE	sDevType;

		m_pd3d->GetDeviceCaps( 
			D3DADAPTER_DEFAULT,				//기본 디스플레이 어댑터를 표기한다.
			D3DDEVTYPE_HAL,					//장치 타입을 지정한다. 보통은 D3DDEVTYPE_HAL이다.
			&caps );						//기본 디스플레이 어댑터의 특성으로 채워진
											//D3DCAPS9 구조체를 리턴한다.

		//하드웨어 버텍스 프로세싱을 이용할 수 있는가?
		if ( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
		{
			//그렇다. 하드웨어 버텍스 프로세싱이 지원된다는 사실을 dwVp에 저장
			dwVp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
			sDevType = D3DDEVTYPE_HAL;
		}
		else
		{
			//그렇지 않다. 소프트웨어 버텍스 프로세싱을 이용해야 한다는 사실을 dwVp에 저장한다.
			dwVp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
			sDevType = D3DDEVTYPE_SW;
		}

		//< D3D파라메터 설정
		D3DPRESENT_PARAMETERS	d3dpp;
		ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

		d3dpp.BackBufferWidth			= nWidth;
		d3dpp.BackBufferHeight			= nHeight;
		d3dpp.BackBufferCount			= 1;
		d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat			= D3DFMT_X8R8G8B8;
		d3dpp.AutoDepthStencilFormat	= D3DFMT_D24S8;	
		d3dpp.EnableAutoDepthStencil	= TRUE;	
		d3dpp.Windowed					= bWindowMode;

		//< 디바이스 생성
		if ( FAILED( m_pd3d->CreateDevice( D3DADAPTER_DEFAULT, sDevType, m_hWnd, dwVp, &d3dpp, &m_pd3dDevice )))
		{
			//< 디바이스 예외 처리
			return E_FAIL;
		}

		//< 끝
		return S_OK;
	}

	//< 해제
	VOID Release( VOID )
	{
		SAFE_RELEASE(m_pd3dDevice);
		SAFE_RELEASE(m_pd3d);
	}

	//< d3d 서페이스(surface) 초기화
	HRESULT ClearScreen( D3DCOLOR color )
	{
		if ( m_pd3dDevice == NULL )
		{
			return E_FAIL;
		}
		return m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL, color, 1, 0 );
	}

	//< 그리기 시작
	HRESULT	RenderStart( VOID )
	{
		if ( m_pd3dDevice == NULL )
		{
			return E_FAIL;
		}
		return m_pd3dDevice->BeginScene();
	}

	//<< 그리기 종료
	HRESULT RenderEnd( VOID )
	{
		if ( m_pd3dDevice == NULL )
		{
			return E_FAIL;
		}
		return m_pd3dDevice->EndScene();
	}

	//< 화면 출력
	HRESULT	Present( VOID )
	{
		return m_pd3dDevice->Present( NULL, NULL, NULL, NULL );
	}
}
#endif
/*
표면(surface)
포면은 Direct3D가 주로 2D 이미지 데이터를 보관하는 데 이용하는 픽셀의 행렬이다.

HAL(Hardware Abstraction Layer:하드웨어 추상 층)
*/
