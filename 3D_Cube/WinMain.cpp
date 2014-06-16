#include "stdafx.h"
#include "cMainGame.h"


LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );//prototype
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("3D_Cube");
cMainGame	g_MainGame;
HWND g_hwnd;

// apientry			==  winmain�Լ��� ȣ�� ����� �ǹ��Ѵ�
// hInstance		==	���α׷��� �ν��Ͻ� �ڵ��̴�(�������� �ü������ ������ �������� �ڵ��ȣ(�������)).
// hPrevInstance	==	�ٷ� �տ� ����� ���α׷��� �ν��Ͻ� �ڵ�.
// lpszCmdParam		==	���� ���Ŀ� �� ������ ��ΰ� ���޵ȴ�.
// nCmdShow			==  �����츦 ȭ�鿡 ����� ���(�����츦 Ȱ��ȭ �Ͽ� �����شٶ�� �ǹ�,�Ǵ� �����.)
int APIENTRY WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd )
{
	//HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	//Client Area�� 1024/768�� �������� ����, ���� ���� ���Ѵ�.
	UINT nWidth, nHeight;	
	nWidth = WIN_WIDTH + GetSystemMetrics(SM_CXFRAME)*2;
	nHeight = WIN_HEIGHT + GetSystemMetrics(SM_CYFRAME)*2 + GetSystemMetrics(SM_CYCAPTION);

	//�����츦 ��ũ�� �߾ӿ� ��ġ��Ű�� ���� x,y�� ���Ѵ�.
	UINT x,y;
	x = (GetSystemMetrics(SM_CXSCREEN) - nWidth) >> 1;
	y = (GetSystemMetrics(SM_CYSCREEN) - nHeight) >>1;

	//1.������ Ŭ���� �ۼ� (�������� �Ӽ��� ���� �Ѵ�)
	WndClass.cbClsExtra		= 0;									//������� ���������� ����� ���и޸�	
	WndClass.cbWndExtra		= 0;									//������� ���������� ����� ���и޸�
	WndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);	//������ ����
	WndClass.hCursor		= LoadCursor(NULL,IDC_ARROW);			//Ŀ���� �����Ѵ�(���ҽ��� ���ؼ� ���ϴ� �׷��ȸ� ��� �Ҽ��� �ִ�)
	WndClass.hIcon			= LoadIcon(NULL,IDI_APPLICATION);		//�������� �д´�(���ҽ��� ���ؼ� ���ϴ� �׷��ȸ� ��� �Ҽ��� �ִ�)
	WndClass.hInstance		= hInstance;							//������ Ŭ������ �ν��Ͻ�(�������� �ü������ ������ �������� �ڵ��ȣ(�������))
	WndClass.lpfnWndProc	= (WNDPROC)WndProc;						//������ ���ν����� �̸�(�������� �޽��� ó�� �Լ��� ����)
	WndClass.lpszClassName	= lpszClass;							//������ Ŭ������ �̸�(�������� Ŭ���� �̸��� ���̴�)
	WndClass.lpszMenuName	= NULL;									//�޴��� �̸�(���ҽ� ������ ���� ������ �������, ����� ���ϸ� NULL)
	WndClass.style			= CS_HREDRAW | CS_VREDRAW;				//�������� ��Ÿ��(�������� ũ�Ⱑ ���Ҷ� �ٽ� �׸���.)

	//2.������ Ŭ���� ���
	RegisterClass(&WndClass);

	//3.������ ����(�޸� �� �����츦 �����Ѵ�)
	g_hwnd  = CreateWindow(lpszClass,			// ������Ŭ���� ���ڿ� 
		lpszClass,							// Ÿ��Ʋ�ٿ� ��Ÿ�� ���ڿ�
		WS_OVERLAPPEDWINDOW,				// �������� ���� �ɼ�(OR ������ ���)Ÿ��Ʋ��, ��ũ�ѹ�, ũ���������� ���
		x, y,								// ������ ������ġ
		nWidth, nHeight,					// ������ ũ��
		NULL,								// �θ��������� �ڵ� (�θ� �����찡 ���� �ڽ��� �ֻ��� ������ �϶� NULL)
		(HMENU)NULL,						// �޴��� �ڵ� (�޴��� ��� ���ϹǷ� NULL)			
		hInstance,							// �ν��Ͻ�
		NULL);								// createStruct��� ����ü�� �ּ� (�������� �����츦 ���鶧 ��� �ǳ� ���� ������� �ʴ´�.)


	//< D3D�ʱ�ȭ
	if( g_MainGame.Init3D( g_hwnd , hInstance , TRUE, WIN_WIDTH , WIN_HEIGHT ) != S_OK )
	{
		g_MainGame.Release();
		return 0;
	}

	///< �ʱ�ȭ
	if( g_MainGame.InitWindow() == FALSE )
	{
		///< ���н� ����ó��
		return 0;
	}

	//4.������ �����ֱ�
	ShowWindow(g_hwnd,nShowCmd);

	//5.�޽��� ����
	//�޽��� ������ ���������� ��Ƽ�½�ŷ�� �����ϴ� ������ �߿��� ������ �ϸ� ���� ������� �����ϱ� ���� �ٽ� �����̴�.
	//�Լ� ���� > BOOL GetMessage(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax)
	//�޽��� ť���� �޽����� �о���δ�.
	//�о���� �޽����� ���α׷��� �����϶�� WM_QUIT�� ��� FALSE,�� ���� �޽����̸� TRUE�� �����Ѵ�.
	while(true)
	{
		if ( PeekMessage( &Message, NULL, 0U, 0U, PM_REMOVE ))
		{
			if(Message.message == WM_QUIT) break;
			//Ű������ ����(WN_KEYDOWN)�޽����� �߻��� �� ���ڰ� �ԷµǾ��ٴ� �޽���(WM_CHAR)�� ����� ������ �Ѵ�.
			//WM_CHAR �޽����� ���� ���� �ʿ䰡 ���ٸ� �����ص� �������.
			TranslateMessage(&Message);
			//�޽��� ť���� ���� �޽����� �������� �޽��� ó�� �Լ�(WndProc)�� �����Ѵ�.
			DispatchMessage(&Message);
		}
		else
		{
			/// ó���� �޽����� ������ Render()�Լ� ȣ��
			g_MainGame.Update();
			g_MainGame.Render();
		}
	}

	g_MainGame.Release();

	return int(Message.wParam);
}
/*
��������� ��Ʈ���� ��ٷ� ȭ�� DC�� ����ϴ� �Լ��� �������� �ʴ´�.
��Ʈ���� ȭ������ ���� ����� �� ������ �ݵ�� �޸� DC�� �̸� �غ��� ���� ����ؾ� �Ѵ�.
�޸� DC�� ȭ�� DC�� ������ Ư���� ������ �� ���ο� ��� ǥ���� ���� �޸� �����̴�.

�޸� DC�� ���� �׸��� �׸� �� ����� ���� �׷����� ������ ������ �ʰ� �� ����� ȭ������ ��� �����ϴ� ���(���� ���۸�)�� ���� ����Ѵ�.
*/

//WndProc�� �޽����� ó������ ��� �ݵ�� 0�� �����ؾ� �Ѵ�.
//���� DefWindowProc �Լ��� �޽����� ó��������� �� �Լ��� ������ ���� WndProc �Լ��� �ٽ� �����ؾ� �Ѵ�.
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//DefWindowProc �Լ��� WndProc���� ó������ ���� ������ �޽����� ���� ó���� �Ѵ�.
	return g_MainGame.MainProc(hWnd, iMsg, wParam, lParam);
}




