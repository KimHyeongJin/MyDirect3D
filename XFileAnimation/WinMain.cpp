//���� ����
//��������������������������������������������������������������������������������������������������������������
// �٦��� 10-07-10, �������, Janus. ������
//��������������������������������������������������������������������������������������������������������������
#include "stdafx.h"
#include "cMainGame.h"

//��������������������������������������������������������������������������������������������������������������
// �٦��� 10-07-10, ��������, Janus. ������
//��������������������������������������������������������������������������������������������������������������
char  		g_ClassName[128] = "Janus";		//Ŭ���� �̸�
char  		g_WinName[128] = "Janus";			//������ �̸�
cMainGame	g_MainGame;

//��������������������������������������������������������������������������������������������������������������
// �٦��� 10-07-10, �Լ� ������ Ÿ��, Janus. ������(�Լ��� ���� ����)
//��������������������������������������������������������������������������������������������������������������
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

//��������������������������������������������������������������������������������������������������������������
// �٦��� 10-07-10, ������ ���� �Լ�, Janus. ������
//��������������������������������������������������������������������������������������������������������������
// apientry			==  winmain�Լ��� ȣ�� ����� �ǹ��Ѵ�
// hInstance		==	���α׷��� �ν��Ͻ� �ڵ��̴�(�������� �ü������ ������ �������� �ڵ��ȣ(�������)).
// hPrevInstance	==	�ٷ� �տ� ����� ���α׷��� �ν��Ͻ� �ڵ�.
// lpszCmdParam		==	���� ���Ŀ� �� ������ ��ΰ� ���޵ȴ�.
// nCmdShow			==  �����츦 ȭ�鿡 ����� ���(�����츦 Ȱ��ȭ �Ͽ� �����شٶ�� �ǹ�,�Ǵ� �����.)
//��������������������������������������������������������������������������������������������������������������
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam, int nCmdShow)
{
	MSG			Message;		//�޼��� ����ü ����
	WNDCLASS	WndClass;		//������ Ŭ���� ����
	int			nWidth, nHeight;//������ ũ�� 

	//������â ũ�� �����.
	nWidth = WINSIZE_X + GetSystemMetrics(SM_CXFRAME) * 2;
	nHeight = WINSIZE_Y + GetSystemMetrics(SM_CYFRAME ) * 2 +
		GetSystemMetrics(SM_CYCAPTION);

	// 1 ������ Ŭ���� �ۼ� (�������� �Ӽ��� ���� �Ѵ�)
	WndClass.cbClsExtra		= 0;									//������� ���������� ����� ���и޸�	
	WndClass.cbWndExtra		= 0;									//������� ���������� ����� ���и޸�
	WndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);	//������ ����
	WndClass.hCursor		= LoadCursor(NULL,IDC_ARROW);			//Ŀ���� �����Ѵ�(���ҽ��� ���ؼ� ���ϴ� �׷��ȸ� ��� �Ҽ��� �ִ�)
	WndClass.hIcon			= LoadIcon(NULL,IDI_APPLICATION);		//�������� �д´�(���ҽ��� ���ؼ� ���ϴ� �׷��ȸ� ��� �Ҽ��� �ִ�)
	WndClass.hInstance		= hInstance;							//������ Ŭ������ �ν��Ͻ�(�������� �ü������ ������ �������� �ڵ��ȣ(�������))
	WndClass.lpfnWndProc	= (WNDPROC)WndProc;						//������ ���ν����� �̸�(�������� �޽��� ó�� �Լ��� ����)
	WndClass.lpszClassName	= g_ClassName;							//������ Ŭ������ �̸�(�������� Ŭ���� �̸��� ���̴�)
	WndClass.lpszMenuName	= NULL;									//�޴��� �̸�(���ҽ� ������ ���� ������ �������, ����� ���ϸ� NULL)
	WndClass.style			= CS_HREDRAW | CS_VREDRAW;				//�������� ��Ÿ��(�������� ũ�Ⱑ ���Ҷ� �ٽ� �׸���.)

	// 2 Ŭ������ ����Ѵ� (������ ������ Ŭ������ ����Ѵ�)
	RegisterClass(&WndClass);										

	//< ������ ȭ�� �߾����� 
	INT		nFullX	= GetSystemMetrics(SM_CXFULLSCREEN);
	INT		nFullY	= GetSystemMetrics(SM_CYFULLSCREEN);

	INT		nStartX = nFullX/2 - WINSIZE_X/2;
	INT		nStartY = nFullY/2 - WINSIZE_Y/2;

	// 3 �����츦 ����� (�޸� �� �����츦 �����Ѵ�)
	HWND hWnd  = CreateWindow(g_ClassName,				// ������Ŭ���� ���ڿ� 
						  g_WinName,				// Ÿ��Ʋ�ٿ� ��Ÿ�� ���ڿ�
						  WS_OVERLAPPEDWINDOW,		// �������� ���� �ɼ�(OR ������ ���)Ÿ��Ʋ��, ��ũ�ѹ�, ũ���������� ���
						  nStartX, nStartY,			// ������ ������ġ
						  nWidth, nHeight,			// ������ ũ��
						  NULL,						// �θ��������� �ڵ� (�θ� �����찡 ���� �ڽ��� �ֻ��� ������ �϶� NULL)
						  (HMENU)NULL,				// �޴��� �ڵ� (�޴��� ��� ���ϹǷ� NULL)			
						  hInstance,				// �ν��Ͻ�
						  NULL);					// createStruct��� ����ü�� �ּ� (�������� �����츦 ���鶧 ��� �ǳ� ���� ������� �ʴ´�.)
	
	//< D3D�ʱ�ȭ
	if( JN_Base3D::Init3D( hWnd , hInstance , TRUE, WINSIZE_X , WINSIZE_Y ) != S_OK )
	{
		JN_Base3D::Release();
		return 0;
	}

	///< �ʱ�ȭ
	if( g_MainGame.InitWindow() == FALSE )
	{
		///< ���н� ����ó��
		return 0;
	}
	
	// 4 �����츦 ȭ�鿡 �����ش�
	ShowWindow(hWnd, nCmdShow);


	while(true)
	{
        /// �޽���ť�� �޽����� ������ �޽��� ó��
		if( PeekMessage( &Message, NULL, 0U, 0U, PM_REMOVE ) )
		{
			if(Message.message == WM_QUIT) break;
			TranslateMessage( &Message );
			DispatchMessage( &Message );
		}
		else
		{
			/// ó���� �޽����� ������ Render()�Լ� ȣ��
			//  Process(), Update()
			//	Render();
			g_MainGame.Update();
			g_MainGame.Render();
		}
	}


	
	//GetMessage(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterJanus, UINT wMsgFilterMAx)�޽���ť���� �о����  �޼����� WM_QUIT�� false ���� �������� true ����
	//lpMsg : �޽����� �ּ�
	//hWnd : �������� �ڵ� 0�̸� ��� �������� �޽����� ��������, �ڵ� ���� �����ϸ� ���ڵ鰪�� ���Ե� �޽����� �����´�.
	//wMsgFilterJanus, wMsgFilterMAx : �޽����� �о���� ���� �ּҰ� �ִ밪(����Ұ�� �ý����� ���ѷ����� ������ �ִ�.)
	// 4 �޼��� ����(����ڷκ����� �޽����� ó���Ѵ� !�޽��� �����ý���)
	
	///< ����
	g_MainGame.Release();
	

	
	return Message.wParam;
}


//��������������������������������������������������������������������������������������������������������������
// �٦��� 10-07-10, ������ ���ν���, Janus.(�޼��� ó�� �Լ�) ������
//��������������������������������������������������������������������������������������������������������������
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	return g_MainGame.MainProc(hWnd, iMessage, wParam, lParam);
}