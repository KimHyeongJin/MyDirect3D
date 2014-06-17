#pragma once

#include "cXFile_Dummy.h"
#include "cXFile_Animation.h"

CONST INT VERTEX_MAX	=	36;

class cMK_Camera;
class cGrid;

class cMainGame
{
private:
	//< ������Ʈ ��� 
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
	///< �ʱ�ȭ
	BOOL	InitWindow( VOID );

	///< ����
	 VOID 	Release( VOID );

	///< ������Ʈ
	 VOID 	Update( VOID );

	///< ����
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
	///< �޼��� ���ν���
	LRESULT MainProc(HWND hWnd,UINT iMessage ,WPARAM wParam,LPARAM lParam);
};
