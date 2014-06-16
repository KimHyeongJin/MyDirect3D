#pragma once

//#include "cVertexBuffer.h"

CONST INT VERTEX_MAX	=	36;

class cMainGame
{
private:
	//< ������Ʈ ��� 
	TCHAR					m_strPath[_MAX_FNAME];

	//<	���ؽ� ����ü
	sVER_COLOR				m_sVer[VERTEX_MAX];

	//	HP
	int						m_nNowHP;

	//cVertexBuffer			m_VB;


	//	��ȯ�� ����
	D3DXVECTOR3				m_vTrans;	//	�̵����� �����ϴ� ����
	D3DXVECTOR3				m_vScale;	//	ũ�⸦ �����ϴ� ����
	D3DXVECTOR3				m_vRot;		//	ȸ�� ����


	LPDIRECT3DDEVICE9			m_pd3dDevice;//< ��ġ ����̽����
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	DWORD						m_dwFVFSize;	//	FVF����üũ��


	//HINSTANCE			m_hInst;	//�ν��Ͻ��� �ڵ鼱��(�ü������ ������ ��ȣ)
	HWND				m_hWnd;	//�������� �ڵ�(�����츦 ��ǥ�ϴ� ��ȣ)
	LPDIRECT3D9			m_pd3d;	//< iDirect ��ü �������̽� ���



	HRESULT	InitCamera();
	
private:
	VOID	InitVertexBuffer(VOID);

public:
	cMainGame( VOID );
	~cMainGame( VOID );
	/************************************************************************/
	/* Init                                                                 */
	/************************************************************************/
	//< d3d�ʱ�ȭ
	HRESULT Init3D( HWND hWnd , HINSTANCE hInst, BOOL bWindowMode, INT nWidth, INT nHeight );
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
