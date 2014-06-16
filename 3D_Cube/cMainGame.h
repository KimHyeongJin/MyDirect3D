#pragma once

//#include "cVertexBuffer.h"

CONST INT VERTEX_MAX	=	36;

class cMainGame
{
private:
	//< 프로젝트 경로 
	TCHAR					m_strPath[_MAX_FNAME];

	//<	버텍스 구조체
	sVER_COLOR				m_sVer[VERTEX_MAX];

	//	HP
	int						m_nNowHP;

	//cVertexBuffer			m_VB;


	//	변환용 벡터
	D3DXVECTOR3				m_vTrans;	//	이동량을 저장하는 벡터
	D3DXVECTOR3				m_vScale;	//	크기를 저장하는 벡터
	D3DXVECTOR3				m_vRot;		//	회전 벡터


	LPDIRECT3DDEVICE9			m_pd3dDevice;//< 장치 디바이스얻기
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	DWORD						m_dwFVFSize;	//	FVF구조체크기


	//HINSTANCE			m_hInst;	//인스턴스의 핸들선언(운영체제에서 정해줄 번호)
	HWND				m_hWnd;	//윈도우의 핸들(윈도우를 대표하는 번호)
	LPDIRECT3D9			m_pd3d;	//< iDirect 객체 인터페이스 얻기



	HRESULT	InitCamera();
	
private:
	VOID	InitVertexBuffer(VOID);

public:
	cMainGame( VOID );
	~cMainGame( VOID );
	/************************************************************************/
	/* Init                                                                 */
	/************************************************************************/
	//< d3d초기화
	HRESULT Init3D( HWND hWnd , HINSTANCE hInst, BOOL bWindowMode, INT nWidth, INT nHeight );
	///< 초기화
	BOOL	InitWindow( VOID );
	
	///< 삭제
	 VOID 	Release( VOID );

	///< 업데이트
	 VOID 	Update( VOID );

	///< 렌더
	 VOID 	Render( VOID );
private:
	/************************************************************************/
	/* virtual                                                              */
	/************************************************************************/
protected:


public:
	/************************************************************************/
	/* Event                                                                */
	/************************************************************************/
	///< 메세지 프로시져
	LRESULT MainProc(HWND hWnd,UINT iMessage ,WPARAM wParam,LPARAM lParam);
};
