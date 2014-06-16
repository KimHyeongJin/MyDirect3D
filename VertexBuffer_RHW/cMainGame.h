#pragma once

CONST INT VERTEX_MAX = 4;

class cMainGame
{
private:
	//< ������Ʈ ��� 
	TCHAR					m_strPath[_MAX_FNAME];

	//< ���ؽ� ����
	LPDIRECT3DVERTEXBUFFER9 m_pVB;

	//< ���ؽ� ����ü
	sVER_RHW_COLOR			m_sVer[VERTEX_MAX];
private:
	VOID InitVertexBuffer(VOID);
	VOID ReleaseVertexBuffer(VOID);
	VOID RenderVertexBuffer(VOID);

	//�� ���
	VOID UpdateVertexBuffer(VOID);
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
