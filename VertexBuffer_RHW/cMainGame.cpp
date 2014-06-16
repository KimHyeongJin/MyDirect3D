#include "StdAfx.h"
#include "cMainGame.h"

cMainGame::cMainGame( VOID )
{
}

cMainGame::~cMainGame( VOID )
{
}


/************************************************************************/
/* Init                                                                 */
/************************************************************************/
///< �ʱ�ȭ
BOOL	cMainGame::InitWindow( VOID )
{
	//< ���α׷� ���� ��ü �н� 
	GetCurrentDirectory(_MAX_FNAME,m_strPath);

	//< ���ؽ� ���� �ʱ�ȭ
	InitVertexBuffer();

	return TRUE;
}

///< ����
 VOID 	cMainGame::Release( VOID )
{
	//���ؽ� ���� ����
	ReleaseVertexBuffer();

	JN_Base3D::Release();
}


///< ������Ʈ
 VOID 	cMainGame::Update( VOID )
{
}

///< ����
 VOID 	cMainGame::Render( VOID )
{
	if( JN_Base3D::m_pd3dDevice != NULL )
	{
		//< ȭ�� �Ұ� 
		if( JN_Base3D::ClearScreen(D3DCOLOR_XRGB(0,0,255)) != S_OK )	
		{
			//< ���� ó��
			return;
		}

		//< ������ ����
		if( JN_Base3D::RenderStart() != S_OK )	
		{
			//< ���� ó��
			return;
		}

		///////////////////////////////////////////////////////////////////////////////
		// ��� �κ�
		RenderVertexBuffer();
		///////////////////////////////////////////////////////////////////////////////

		//< ������ ��
		if( JN_Base3D::RenderEnd() != S_OK )	
		{
			//< ���� ó�� 	
		}

		//< ȭ�� ���
		if( JN_Base3D::Present() != S_OK )	
		{
			//< ���� ó�� 	
		}

	}
}

/************************************************************************/
/* Event                                                                */
/************************************************************************/
///< �޼��� ���ν���
LRESULT	cMainGame::MainProc(HWND hWnd,UINT iMessage ,WPARAM wParam,LPARAM lParam)
{
	switch(iMessage)
	{
	case WM_TIMER:
		break;

	case WM_LBUTTONDOWN:
		{
			m_sVer[1].x -= 50.0f;
			m_sVer[3].x -= 50.0f;
	
			UpdateVertexBuffer();
		}
		break;

	case WM_RBUTTONDOWN:
		{
			m_sVer[1].x += 50.0f;
			m_sVer[3].x += 50.0f;
			UpdateVertexBuffer();
		}
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
			//(esc key)
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

VOID cMainGame::InitVertexBuffer(VOID)
{
	m_sVer[0].x = 200.0f;
	m_sVer[0].y = 200.0f;
	m_sVer[0].z = 0.0f;
	m_sVer[0].rhw = 1.0f;
	m_sVer[0].dwColor = 0xffff0000;

	m_sVer[1].x = 600.0f;
	m_sVer[1].y = 200.0f;
	m_sVer[1].z = 0.0f;
	m_sVer[1].rhw = 1.0f;
	m_sVer[1].dwColor = 0xff00ff00;

	m_sVer[2].x = 200.0f;
	m_sVer[2].y = 300.0f;
	m_sVer[2].z = 0.0f;
	m_sVer[2].rhw = 1.0f;
	m_sVer[2].dwColor = 0xffff0000;

	m_sVer[3].x = 600.0f;
	m_sVer[3].y = 300.0f;
	m_sVer[3].z = 0.0f;
	m_sVer[3].rhw = 1.0f;
	m_sVer[3].dwColor = 0xff00ff00;

	if ( JN_Base3D::m_pd3dDevice != NULL )
	{
		if ( FAILED( JN_Base3D::m_pd3dDevice->CreateVertexBuffer( sizeof(sVER_RHW_COLOR)*VERTEX_MAX, 0, sVER_RHW_COLOR::FVF_VER_RHW_COLOR, D3DPOOL_DEFAULT, &m_pVB, 0 ) ) )
		{
			return;
		}

		UpdateVertexBuffer();
	}
}

VOID cMainGame::ReleaseVertexBuffer()
{
	SAFE_RELEASE( m_pVB );
}

VOID cMainGame::RenderVertexBuffer()
{
	//1. ��Ʈ�� �ҽ� ����. ��Ʈ�� �ҽ��� ���ؽ� ���ۿ� �����Ͽ� ������ ���������� ������ ���������ο� ���� �� �ֵ��� �Ѵ�.
	//���ؽ� ���ۿ� ��Ʈ���ҽ� ����
	JN_Base3D::m_pd3dDevice->SetStreamSource( 
		0,										//���� ��Ʈ���� �ƴϸ� 0 
		m_pVB,									//��Ʈ���� �����ϰ��� �ϴ� ���ؽ� ���۷��� ������
		0,										//�������� ������
		sizeof(sVER_RHW_COLOR) );				//���ؽ� ����ü�� ũ��

	//2. ���ؽ� ������ �����Ѵ�. ������ ����� ȣ�⿡�� �̿�� ���ؽ� ������ �����ϴ� �ܰ��̴�.
	//FVF ���� ����
	JN_Base3D::m_pd3dDevice->SetFVF( sVER_RHW_COLOR::FVF_VER_RHW_COLOR );

	//3. �ε��� ���۸� �����Ѵ�. ���� �ε��� ���۸� �̿��Ѵٸ� ������ ����� �������� �̿�� �ε��� ���۸� �����ؾ� �ϴµ�,
	// �ѹ��� �ϳ��� �ε��� ���۸� �̿��� �� �ִ�. ���� �ٸ� �ε��� ���۸� ���� ��ü�� �׷��� �Ѵٸ� �ε��� ���۸� ��ȯ�ϴ� ������ �ʿ��ϴ�.
	//�ε��� ���۸� �����ϴ� ����� ������ ����.
	//JN_Base3D::m_pd3dDevice->SetIndices( _ib );

	//�׸���. �� �޼���� �ε��� ������ �̿����� �ʴ� �⺻���� �׸��µ� �̿� �ȴ�.
	JN_Base3D::m_pd3dDevice->DrawPrimitive( 
		D3DPT_TRIANGLESTRIP,						//�׸����� �ϴ� �⺻�� Ÿ��
		0,										//���ؽ� �б⸦ ������ ���ؽ� ��Ʈ�� ����� �ε���
		2 );									//�׸����� �ϴ� �⺻���� ��
}

VOID cMainGame::UpdateVertexBuffer(VOID)
{
	VOID* pVer = NULL;

	//< ���� ����
	m_pVB->Lock( 0, sizeof(sVER_RHW_COLOR)*VERTEX_MAX, &pVer, 0 );
	//If the method succeeds, the return value is D3D_OK. If the method fails, the return value can be D3DERR_INVALIDCALL.

	if ( pVer != NULL )
	{
		memmove( pVer, m_sVer, sizeof(sVER_RHW_COLOR)*VERTEX_MAX );
	}
	m_pVB->Unlock();
}
/*
http://blog.naver.com/gkqxhq324456?Redirect=Log&logNo=110146202869
Lock(), Unlock()
���ؽ�/�ε��� ���� �޸𸮿� �����ϱ� ���ؼ� ���� �޸� ����Ʈ���� �����Ͱ� �ʿ��ϴ�
�����͸� ��� ���ؼ� Lock �޼��带 �̿��ϸ�, �̿��� �����ڿ��� �ݵ�� Unlock �޼��带 �̿��ؼ� ������ ����� ���� �ؾ� �Ѵ�.


http://blog.naver.com/gkqxhq324456?Redirect=Log&logNo=110146202869
�޸� Ǯ,FVF


http://blog.naver.com/gkqxhq324456?Redirect=Log&logNo=110146202869

��ó http://blog.daum.net/artofcom/8
RHW�� �����ΰ�.
�Ʒ� �߱۵��� �����ϸ� �Ʒ��� ���� ���Ǹ� ���� �� �ִ�.
 
rhw��� �ϴ� ���� reciprocal homogeneous w �� ���ڷ� ������ǥ 'w�� ����' ��� ��. ��, 1/w.
�� �̰��� ����ϴ��� �ϸ�, perspective ��ȯ ����� ��ġ�� ������ ��İ��� �츮�� ���ϴ� ������ǥ�� �ٲٱ� ���� w�� 4��° ������ ������ �ϴµ�, �̰��� ������ �̸� ������ ���� ���� rhw ��� ��Ⱑ �ǰڴ�.
 
���� Ư¡���δ�, D3DFVF_XYZRHW�� ����� ���, �̰��� ������������ �̹� ó���� ������ �����ϹǷ�, 2D�� �ٷ� ����ϱ⿡ �����ϴٴ� ���̴�.
 

 
-------------------------------------------------------------------------------------------
 
 


���ӿ��� User Interface �� ȭ�鿡 �������Ҷ� 
���� �ΰ��� ������� �����Ѵ�.
RHW, ������ǥ�� �μ� ��ġ�� �����ϴ� ����� 
Orthogonal�μ� �������ϴ� ����� �ִ�.
 
1. RHW
D3DFVF_XYZRHW�� ��ȯ �� ������ ��ġ ��ǥ�� ��Ÿ���Ƿ� ���������ο��� ��ȯ�� �����Ҽ� ����. �׷��� ȭ�鿡�� UI�� 
�̵� ��Ű���� ���� �������۸� �ǵ���� �Ѵ�. ���� �����ϴ�.
�׸��� �ػ󵵰� ����Ǹ� ��������� �۾�����.
(0, 0)�� Ŭ���̾�Ʈ ������ ���ʻ���� ��Ÿ����.

2. Orthogonal Projection
���� ���� ����� ����Ͽ� ���� ��ȯ�� ���డ���ϵ����Ѵ�. 
ȭ��󿡼� UI �̵� �� ȸ���� ���� ������ �� �ִ� ���� ���� �̴�.
D3DXMatrixOrthoOffCenterLH �Լ��� �̿��Ͽ� ���� ����� Ŭ���̾�Ʈ ������ ��ġ��ų�� �ִ�.
 (0, 0) ~ (width, height)
2/(r-l)      0              0             0 
0             2/(t-b)      0             0 
0             0              1/(zf-zn)  0 
(l+r)/(l-r) (t+b)/(b-t) zn/(zn-zf) 1

�⺻���� ������ ���� �����Ѵ�. 
l = -w/2 
r = w/2 
b = -h/2 
t = h/2
�ڵ�:
// ������ ���� �����ϸ� Ŭ���̾�Ʈ ������ ��ġ ��ų�� �ִ�.
// �� �����ϴ� �κ��� (0, 0) �̴�.
D3DXMatrixOrthoOffCenterLH ( &m_matProj, 0, m_dwWidth, 0, m_dwHeight, m_fNearZ, m_fFarZ);
 

���� ����� 0,0 ���� ������� (0~w, -h~0) ���� �����ߴµ� �ȵǳ׿�. 
�׳� ���� �ϴ����� ���°��� ������ +�������� ���� �����Ҽ� �����ϱ� ���ҵ��ϳ׿�.

UI�� �������� View , World ���� ������ķ� �����ϰ� 
z-buffer�� ���� �������Ͽ� �׻� ���� �ö���� �Ѵ�.
D3DFVF_XYZRHW - �� �÷��״� ��ȯ�� ������ ��ġ�� �����Ѵ�.
�̰��� X,Y��Ұ� ��ũ�� ������ ������ Z��Ҵ� �� ������κ����� �Ÿ��� ��Ÿ���� RHW��� �߰� �ε� �Ҽ� ������ ������ W��ǥ�� �����Ѵٴ� ���� �����Ѵ�.
�̰��� D3DFVF_NORMAL �÷��׿� ���� ���ϼ� ����.
RHW ���� ��ǥ���� w�� �̰��� ������ ��ȯ�� �Ϸ�� �����̴�. 
 
----------------------------------------------------------------------------------------

W�� Homogeneous coordinates�� �׹�° �����̰� homogeneous coordinates �� �츮���� ��ġ ��ǥ��� �մϴ�.
�Ϲ������� 3���� ��ǥ��ȯ ��ķ� 4*4 ����� ����ϴµ�.. �׷��� �Ǹ� ���ؽ� ��ǥ�� ���� (x,y,z,1)�� ����մϴ�.
perspective ��ȯ ����� �����ϰ� ���� ���ؽ� ��ǥ���� �׹�° ������ 1�� �ƴ� ���� ������ �Ǵµ�..
�̷��� ������� ��ǥ���� ���� (x,y,z,w)��� ǥ���մϴ�.
�̶� �̷� ��ǥ���� ��ġ ��ǥ��� �մϴ�. ������ ��ũ������ ��ǥ������ ����ϱ� ���ؼ��� ������ǥ�� �ƴ� �Ϲ����� ��ǥ�� ��ȯ�� �ؾ� �ϴµ�.. ��ǥ�� �������� w�� ����� ���ϰ� �˴ϴ�. ��, (x/w, y/w, z/w, w/w) = (x/w, y/w, z/w, 1) �� �ǰ� ��° ���� ���� 1�� �Ϲ����� ��ǥ�� �ٲ���.
rhw��� �ϴ� ���� reciprocal homogeneous w �� ���ڷ� ������ǥ 'w�� ����' ��� ���Դϴ�. ��, 1/w �� ������.
������ ������ǥ�� �Ϲ����� ��ǥ�� ��ȯ�ϱ� ���ؼ� w�� �������µ�, ��ǻ�Ϳ����� ������ ����� �����Ƿ� 1/w�� �ѹ��� ���ؼ� �����п��� 1/w�� ���ϴ� ������ ����� ó���մϴ�.
�׷��� direct3d������ w�� ������ rhw��� �̸��ϰ� ���� �����ϴ� ����.
 
�׷��� ���� ��� ��ȯ�� ó���� ������ �ƴ϶�� �̷� �κ��� ���� ���� ���ϴ��� ��ü�� ��ǥ�� ���� ������Ʈ ��ǥ���� �Ѱ��ָ� ������ ����� ������ �������� ��Ŀ� ���� �ڵ����� �˾Ƽ� ó�����ֹǷ� �Ű澲�� �ʾƵ� �˴ϴ�. ��ǥ��ȯ�� �������� ���� ó���Ұ� �ƴ϶�� rhw�� ũ�� �Ű澲�� �ʾƵ� �˴ϴ�. �׳� ��ȯ ��ĸ� ����� �����ϸ� ������.
*/