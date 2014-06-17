#pragma once 

namespace JN_Base3D
{
	extern		HINSTANCE			m_hInst;			//인스턴스의 핸들선언(운영체제에서 정해줄 번호)
	extern		HWND				m_hWnd;				//윈도우의 핸들(윈도우를 대표하는 번호)
	extern		LPDIRECT3D9			m_pd3d;				//< iDirect 객체 인터페이스 얻기
	extern		LPDIRECT3DDEVICE9	m_pd3dDevice;		//< 장치 디바이스얻기

	//< d3d초기화
	HRESULT			Init3D(  HWND hWnd , HINSTANCE hInst,  BOOL bWindowMode, INT nWidth,
		INT nHeight );
	//< 해제
	 VOID 			Release( VOID );
	//< d3d 서페이스 초기화
	HRESULT			ClearScreen( D3DCOLOR Color );

	//< 그리기 시작
	HRESULT			RenderStart( VOID );

	//< 그리기 종료
	HRESULT			RenderEnd( VOID );

	//< 화면 출력
	HRESULT			Present( VOID );
}//< namespace end
