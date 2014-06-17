#include "StdAfx.h"
#include "cXFile_Object.h"

cXFile_Object::cXFile_Object(void)
{
	m_pd3dDevice	=	NULL;		//	디바이스

	m_vTrans		=	D3DXVECTOR3(0, 0, 0);			//	이동
	m_vScale		=	D3DXVECTOR3(1, 1, 1);			//	크기
	m_vRot			=	D3DXVECTOR3(0, 0, 0);			//	회전

	m_pMatParent	=	NULL;	//	부모행렬

	m_bAni			=	FALSE;	//	애니메이션 유무
	m_dwID			=	0;		//	ID값

	m_szFileName	=	"";		//	파일명
	m_dwType		=	0;		//	오브젝트 타입
}

cXFile_Object::~cXFile_Object(void)
{
}

VOID	cXFile_Object::SetMatrix(VOID)
{
	D3DXMATRIXA16	matTotal;
	D3DXMATRIXA16	matScale;
	D3DXMATRIXA16	matTrans;
	D3DXMATRIXA16	matRot;

	D3DXMatrixScaling( &matScale, m_vScale.x, m_vScale.y, m_vScale.z );
	D3DXMatrixTranslation( &matTrans, m_vTrans.x, m_vTrans.y, m_vTrans.z );
	D3DXMatrixRotationYawPitchRoll( &matRot, 
		m_vRot.y * D3DX_PI / 180, //yaw : 요는 이동방향에 대해 수직면에 있는 축주위의 회전입니다.
		m_vRot.x * D3DX_PI / 180, //pitch : 피치는 이동 방향에 대해 수직의 수평면에 있는 축 주위의 회전입니다.
		m_vRot.z * D3DX_PI / 180 );//roll	: 롤은 이동방향에 대한 평행한 수평면에 있는 축 주위의 회전입니다.

	m_matNoScaleWorld	=	matRot * matTrans;

	matTotal			=	matScale * m_matNoScaleWorld;

	if( m_pMatParent != NULL )
	{
		matTotal	*=	*m_pMatParent;
	}

	m_pd3dDevice->SetTransform( D3DTS_WORLD, &matTotal );
}