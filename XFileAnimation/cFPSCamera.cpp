#include "StdAfx.h"
#include "cFPSCamera.h"

cFPSCamera::cFPSCamera(void)
{
	RECT	rcPos;
	GetWindowRect( JN_Base3D::m_hWnd, &rcPos );
	SetCursorPos( rcPos.left + WINSIZE_X/2, rcPos.top + WINSIZE_Y/2 );

	GetCursorPos( &m_ptMouse );
}

cFPSCamera::~cFPSCamera(void)
{
}

void	cFPSCamera::KeyInput(VOID)
{
	//	현재 마우스 위치
	POINT	ptMouse;
	GetCursorPos( &ptMouse );

	if( ptMouse.x != m_ptMouse.x ||
		ptMouse.y != m_ptMouse.y )
	{
		FLOAT	fX	=	(FLOAT)ptMouse.y - m_ptMouse.y;
		FLOAT	fY	=	(FLOAT)ptMouse.x - m_ptMouse.x;

		Rotation_X( fX * 0.1f );
		Rotation_Y( fY * 0.1f );

		RECT	rcPos;
		GetWindowRect( JN_Base3D::m_hWnd, &rcPos );

		SetCursorPos( rcPos.left + WINSIZE_X/2, rcPos.top + WINSIZE_Y/2 );

		m_ptMouse.x	=	rcPos.left + WINSIZE_X/2;
		m_ptMouse.y =	rcPos.top + WINSIZE_Y/2;
	}	

	if( GetAsyncKeyState( 'D' ) & 0x8000 )
	{
		m_vEye		+=	m_vRight * 0.3f;
		m_vLookAt	+=	m_vRight * 0.3f;

		Update();
	}

	if( GetAsyncKeyState( 'A' ) & 0x8000 )
	{
		m_vEye		-=	m_vRight * 0.3f;
		m_vLookAt	-=	m_vRight * 0.3f;

		Update();
	}

	if( GetAsyncKeyState( 'W' ) & 0x8000 )
	{
		D3DXVECTOR3	vDir	=	GetLookVector();

		vDir.y	=	0;

		D3DXVec3Normalize( &vDir, &vDir );

		m_vEye		+=	vDir * 0.3f;
		m_vLookAt	+=	vDir * 0.3f;

		Update();
	}

	if( GetAsyncKeyState( 'S' ) & 0x8000 )
	{
		D3DXVECTOR3	vDir	=	GetLookVector();
		vDir.y	=	0;
		
		D3DXVec3Normalize( &vDir, &vDir );

		m_vEye		-=	vDir * 0.3f;
		m_vLookAt	-=	vDir * 0.3f;

		Update();
	}
}