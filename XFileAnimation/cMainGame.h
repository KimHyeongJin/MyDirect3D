#pragma once

#include "cXFile_Dummy.h"
#include "cXFile_Animation.h"

CONST INT VERTEX_MAX	=	36;

class cMK_Camera;
class cGrid;

class cMainGame
{
private:
	//< 프로젝트 경로 
	TCHAR					m_strPath[_MAX_FNAME];

	cXFile_Dummy			m_XFile;
	cXFile_Animation		m_XFileAni;

	/////////////////////////////////////////
	//
	POINT					m_ptMousePos;

	cMK_Camera				*m_pCamera;
	cGrid					*m_pGrid;

	HRESULT	InitCamera();

private:
	VOID	InitVertexBuffer(VOID);

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
