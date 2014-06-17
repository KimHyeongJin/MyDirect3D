#include "StdAfx.h"
#include "JN_Base3D.h"

namespace JN_Base3D
{
	HINSTANCE			m_hInst			= NULL;	//�ν��Ͻ��� �ڵ鼱��(�ü������ ������ ��ȣ)
	HWND				m_hWnd			= NULL;	//�������� �ڵ�(�����츦 ��ǥ�ϴ� ��ȣ)
	LPDIRECT3D9			m_pd3d			= NULL;	//< iDirect ��ü �������̽� ���
	LPDIRECT3DDEVICE9	m_pd3dDevice	= NULL;	//< ��ġ ����̽����
	//< d3d�ʱ�ȭ
	HRESULT			Init3D( HWND hWnd , HINSTANCE hInst, BOOL bWindowMode, INT nWidth, INT nHeight )
	{
		m_hWnd	= hWnd;
		m_hInst	= hInst;

		//< d3d��ü �������̽� ����
		m_pd3d = Direct3DCreate9( D3D_SDK_VERSION );

		//< ���� ó�� 
		if( m_pd3d == NULL )
		{
			//< ���� 
			return E_FAIL;
		}

		//< �ϵ���� ���� ���� Ȯ�� (Caps)
		D3DCAPS9		caps;	//< ��ġ ���� 
		DWORD			dwVp;	//< ���ؽ� ���μ���
		D3DDEVTYPE		sDevType;

		m_pd3d->GetDeviceCaps(D3DADAPTER_DEFAULT , D3DDEVTYPE_HAL, &caps);

		if( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
		{
			dwVp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
			sDevType = D3DDEVTYPE_HAL;
		}
		else
		{
			dwVp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
			sDevType = D3DDEVTYPE_SW;
		}

		//< D3D�Ķ���� ���� 
		D3DPRESENT_PARAMETERS		d3dpp;
		ZeroMemory(&d3dpp,sizeof(D3DPRESENT_PARAMETERS));

		d3dpp.BackBufferWidth			= nWidth;
		d3dpp.BackBufferHeight			= nHeight;
		d3dpp.BackBufferCount			= 1;
		d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat			= D3DFMT_X8R8G8B8;
		d3dpp.AutoDepthStencilFormat	= D3DFMT_D24S8;	
		d3dpp.EnableAutoDepthStencil	= TRUE;	
		d3dpp.Windowed					= bWindowMode;

		//< ����̽� ����
		if( FAILED(m_pd3d->CreateDevice(
			D3DADAPTER_DEFAULT,
			sDevType,
			m_hWnd,
			dwVp,
			&d3dpp,
			&m_pd3dDevice)))
		{
			//< ����̽� ���� ó�� 
			return E_FAIL;
		}

		//< ��~~
		return S_OK;
	}
	//< ����
	 VOID 			Release( VOID )
	{
		SAFE_RELEASE(m_pd3dDevice);
		SAFE_RELEASE(m_pd3d);
	}
	//< d3d �����̽� �ʱ�ȭ
	HRESULT			ClearScreen( D3DCOLOR Color )
	{
		if( m_pd3dDevice == NULL )
		{
			return E_FAIL;
		}

		return m_pd3dDevice->Clear(0,NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER
			| D3DCLEAR_STENCIL,
			Color,1,0);	
	}

	//< �׸��� ����
	HRESULT			RenderStart( VOID )
	{
		if( m_pd3dDevice == NULL )
		{
			return E_FAIL;
		}

		return m_pd3dDevice->BeginScene();
	}	

	//< �׸��� ����
	HRESULT			RenderEnd( VOID )
	{
		if( m_pd3dDevice == NULL )
		{
			return E_FAIL;
		}

		return m_pd3dDevice->EndScene();
	}

	//< ȭ�� ���
	HRESULT			Present( VOID )
	{
		return m_pd3dDevice->Present(NULL,NULL,NULL,NULL);
	}
}//< namespace end
