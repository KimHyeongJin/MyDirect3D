#include "stdafx.h"
#include "cMK_Camera.h"

cMK_Camera::cMK_Camera(void)
{
}

cMK_Camera::~cMK_Camera(void)
{
}

void	cMK_Camera::InitCam( LPDIRECT3DDEVICE9 pd3dDevice, D3DXVECTOR3 *pEye, D3DXVECTOR3	*pLookAt )
{
	m_pd3dDevice	=	pd3dDevice;
	m_vEye			=	*pEye;
	m_vLookAt		=	*pLookAt;
	m_vUp			=	D3DXVECTOR3( 0, 1, 0 );
	m_vRight		=	D3DXVECTOR3( 1, 0, 0 );

	D3DXMatrixIdentity( &m_matView );
	D3DXMatrixIdentity( &m_matProj );
	D3DXMatrixIdentity( &m_matViewProj );
	D3DXMatrixIdentity( &m_matBill );

	SetUp( &m_vEye, &m_vLookAt, &m_vUp );

	m_fDist	=	D3DXVec3Length( &GetLookVector() );
}

void	cMK_Camera::SetUp( D3DXVECTOR3	*pEye, D3DXVECTOR3	*pLookAt, D3DXVECTOR3	*pUp )
{
	m_vEye			=	*pEye;
	m_vLookAt		=	*pLookAt;
	m_vUp			=	*pUp;

	Update();
}

void	cMK_Camera::Update()
{
	SetMatrix();
	
	SetRight();

	SetViewProj();

	SetBill();
}

void	cMK_Camera::SetBill()
{
	D3DXMatrixInverse( &m_matBill, NULL, &m_matView );
}

void	cMK_Camera::SetMatrix()
{
	SetView();

	SetProj();
}

void	cMK_Camera::SetView()
{
	D3DXMatrixLookAtLH( &m_matView, &m_vEye, &m_vLookAt, &m_vUp );

	m_pd3dDevice->SetTransform( D3DTS_VIEW, &m_matView );
}

void	cMK_Camera::SetProj()
{
	D3DXMatrixPerspectiveFovLH( &m_matProj, D3DX_PI / 2, WINSIZE_X / WINSIZE_Y, 1.0f, 1000.0f );

	m_pd3dDevice->SetTransform( D3DTS_PROJECTION, &m_matProj );
}

void	cMK_Camera::SetViewProj()
{
	m_matViewProj	=	m_matView + m_matProj;
}

void	cMK_Camera::SetRight()
{
	D3DXVECTOR3	vLook = GetLookVector();

	D3DXVec3Cross( &m_vRight, &m_vUp, &vLook );

	D3DXVec3Normalize( &m_vRight, &m_vRight );
}

D3DXVECTOR3	cMK_Camera::GetLookVector()
{
	return m_vLookAt - m_vEye;
}


//////////////////////////////////////////////////////////////////////////
D3DXVECTOR3	cMK_Camera::RotateAxis_X( float	fAngleX ) 
{
	D3DXMATRIXA16	matRotRight;
	D3DXMatrixIdentity( &matRotRight );

	//	카메라의 방향벡터를 구하고 단위벡터화 시킨다.
	D3DXVECTOR3		vDir	=	GetLookVector();
	D3DXVec3Normalize( &vDir, &vDir );

	//	우향 벡터를 구한다.
	D3DXVec3Cross( &m_vRight, &m_vUp, &vDir );

	//	해당 각도만큼 회전하는 축회전 행렬을 만든다.( 우향벡터를 기준 )
	D3DXMatrixRotationAxis( &matRotRight, &m_vRight, D3DXToRadian( fAngleX ) );

	//	방향 벡터를 회전한다.
	D3DXVECTOR3	vNewDir;
	D3DXVec3TransformCoord( &vNewDir, &vDir, &matRotRight );
	D3DXVec3Normalize( &vNewDir, &vNewDir );

	return vNewDir;
}

D3DXVECTOR3	cMK_Camera::RotateAxis_Y( float	fAngleY )
{
	D3DXMATRIXA16	matRotUp;
	D3DXMatrixIdentity( &matRotUp );

	//	카메라의 방향벡터를 구하고 단위벡터화 시킨다.
	D3DXVECTOR3		vDir	=	GetLookVector();
	D3DXVec3Normalize( &vDir, &vDir );

	//	해당 각도만큼 회전하는 축회전 행렬을 만든다.( 업벡터를 기준 )
	D3DXMatrixRotationAxis( &matRotUp, &m_vUp, D3DXToRadian( fAngleY ) );

	//	방향 벡터를 회전한다.
	D3DXVECTOR3	vNewDir;
	D3DXVec3TransformCoord( &vNewDir, &vDir, &matRotUp );
	D3DXVec3Normalize( &vNewDir, &vNewDir );

	return vNewDir;
}

void	cMK_Camera::SetDist( float fDist )
{
	m_fDist = fDist;

	D3DXVECTOR3		vDir	=	GetLookVector();

	D3DXVec3Normalize( &vDir, &vDir );

	m_vEye	=	m_vLookAt - vDir * m_fDist;

	Update();
}


void	cMK_Camera::Rotation_X( float	fAngleX )
{
	D3DXVECTOR3	vNewDir = RotateAxis_X( fAngleX );

	m_vLookAt	= m_vEye + vNewDir * m_fDist;

	Update();
}

void	cMK_Camera::Rotation_Y( float	fAngleY )
{
	D3DXVECTOR3	vNewDir = RotateAxis_Y( fAngleY );

	m_vLookAt = m_vEye + vNewDir * m_fDist;

	Update();
}

void	cMK_Camera::Revolution_X( float	fAngleX )
{
	D3DXVECTOR3	vNewDir = RotateAxis_X( fAngleX );

	m_vEye	=	m_vLookAt - vNewDir * m_fDist;

	Update();
} 


void	cMK_Camera::Revolution_Y( float	fAngleY )
{
	D3DXVECTOR3	vNewDir = RotateAxis_Y( fAngleY );

	m_vEye	=	m_vLookAt - vNewDir * m_fDist;

	Update();
}

void	cMK_Camera::ZoomInOut( float fDist )
{
	m_fDist += fDist;

	if( m_fDist < 1 )
	{
		m_fDist = 1;
	}

	SetDist( m_fDist );
}