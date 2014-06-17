#pragma once 

namespace JN_Base3D
{
	extern		HINSTANCE			m_hInst;			//�ν��Ͻ��� �ڵ鼱��(�ü������ ������ ��ȣ)
	extern		HWND				m_hWnd;				//�������� �ڵ�(�����츦 ��ǥ�ϴ� ��ȣ)
	extern		LPDIRECT3D9			m_pd3d;				//< iDirect ��ü �������̽� ���
	extern		LPDIRECT3DDEVICE9	m_pd3dDevice;		//< ��ġ ����̽����

	//< d3d�ʱ�ȭ
	HRESULT			Init3D(  HWND hWnd , HINSTANCE hInst,  BOOL bWindowMode, INT nWidth,
		INT nHeight );
	//< ����
	 VOID 			Release( VOID );
	//< d3d �����̽� �ʱ�ȭ
	HRESULT			ClearScreen( D3DCOLOR Color );

	//< �׸��� ����
	HRESULT			RenderStart( VOID );

	//< �׸��� ����
	HRESULT			RenderEnd( VOID );

	//< ȭ�� ���
	HRESULT			Present( VOID );
}//< namespace end
