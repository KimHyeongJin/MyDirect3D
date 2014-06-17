#include "StdAfx.h"
#include "cXFile_Object.h"

cXFile_Object::cXFile_Object(void)
{
	m_pd3dDevice	=	NULL;		//	����̽�

	m_vTrans		=	D3DXVECTOR3(0, 0, 0);			//	�̵�
	m_vScale		=	D3DXVECTOR3(1, 1, 1);			//	ũ��
	m_vRot			=	D3DXVECTOR3(0, 0, 0);			//	ȸ��

	m_pMatParent	=	NULL;	//	�θ����

	m_bAni			=	FALSE;	//	�ִϸ��̼� ����
	m_dwID			=	0;		//	ID��

	m_szFileName	=	"";		//	���ϸ�
	m_dwType		=	0;		//	������Ʈ Ÿ��
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
		m_vRot.y * D3DX_PI / 180, //yaw : ��� �̵����⿡ ���� �����鿡 �ִ� �������� ȸ���Դϴ�.
		m_vRot.x * D3DX_PI / 180, //pitch : ��ġ�� �̵� ���⿡ ���� ������ ����鿡 �ִ� �� ������ ȸ���Դϴ�.
		m_vRot.z * D3DX_PI / 180 );//roll	: ���� �̵����⿡ ���� ������ ����鿡 �ִ� �� ������ ȸ���Դϴ�.

	m_matNoScaleWorld	=	matRot * matTrans;

	matTotal			=	matScale * m_matNoScaleWorld;

	if( m_pMatParent != NULL )
	{
		matTotal	*=	*m_pMatParent;
	}

	m_pd3dDevice->SetTransform( D3DTS_WORLD, &matTotal );
}