#pragma once

CONST INT VERTEX_MAX = 4;

class cMainGame
{
private:
	//< 프로젝트 경로 
	TCHAR					m_strPath[_MAX_FNAME];

	//< 버텍스 버퍼
	LPDIRECT3DVERTEXBUFFER9 m_pVB;

	//< 버텍스 구조체
	sVER_RHW_COLOR			m_sVer[VERTEX_MAX];
private:
	VOID InitVertexBuffer(VOID);
	VOID ReleaseVertexBuffer(VOID);
	VOID RenderVertexBuffer(VOID);

	//락 언락
	VOID UpdateVertexBuffer(VOID);
public:
	cMainGame( VOID );
	~cMainGame( VOID );
	/************************************************************************/
	/* Init                                                                 */
	/************************************************************************/
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
