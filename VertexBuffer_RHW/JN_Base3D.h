#pragma once

namespace JN_Base3D
{
	extern HINSTANCE			m_hInst;		//�ν��Ͻ��� �ڵ� ����
	extern HWND					m_hWnd;			//���ο� �ڵ�
	extern LPDIRECT3D9			m_pd3d;			//< iDirect ��ü �������̽� ���
	extern LPDIRECT3DDEVICE9	m_pd3dDevice;		//< ��ġ ����̽� ���

	//< d3d�ʱ�ȭ
	HRESULT Init3D( HWND hWnd, HINSTANCE hInst, BOOL bWindowMode, INT nWidth, INT nHeight );

	//< ����
	VOID Release( VOID );

	//< d3d �����̽�(surface) �ʱ�ȭ
	HRESULT ClearScreen( D3DCOLOR color );

	//< �׸��� ����
	HRESULT	RenderStart( VOID );

	//<< �׸��� ����
	HRESULT RenderEnd( VOID );

	//< ȭ�� ���
	HRESULT	Present( VOID );
};//namespace end
