#include "stdafx.h"
#include "C3DCoordinateAxisMain.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("3D��ǥ��������");
HWND g_hWnd;
POINT g_ptMouse;

C3DCoordinateAxisMain g_main;

int APIENTRY WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd )
{
	HWND hWnd;
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

	//1.������ Ŭ���� ����
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW|CS_VREDRAW;

	//2.������ Ŭ���� ���
	RegisterClass(&WndClass);

	//3.������ ����
	hWnd = CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW,x,y,nWidth,nHeight,NULL,NULL,hInstance,NULL);
	g_hWnd = hWnd;
	//4.������ �����ֱ�
	ShowWindow(hWnd,nShowCmd);

	g_main.Init();
	//5.�޽��� ����
	//�޽��� ������ ���������� ��Ƽ�½�ŷ�� �����ϴ� ������ �߿��� ������ �ϸ� ���� ������� �����ϱ� ���� �ٽ� �����̴�.
	//�Լ� ���� > BOOL GetMessage(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax)
	//�޽��� ť���� �޽����� �о���δ�.
	//�о���� �޽����� ���α׷��� �����϶�� WM_QUIT�� ��� FALSE,�� ���� �޽����̸� TRUE�� �����Ѵ�.
	while(GetMessage(&Message,0,0,0))
	{
		//Ű������ ����(WN_KEYDOWN)�޽����� �߻��� �� ���ڰ� �ԷµǾ��ٴ� �޽���(WM_CHAR)�� ����� ������ �Ѵ�.
		//WM_CHAR �޽����� ���� ���� �ʿ䰡 ���ٸ� �����ص� �������.
		TranslateMessage(&Message);
		//�޽��� ť���� ���� �޽����� �������� �޽��� ó�� �Լ�(WndProc)�� �����Ѵ�.
		DispatchMessage(&Message);
	}

	return int(Message.wParam);
}
/*
��������� ��Ʈ���� ��ٷ� ȭ�� DC�� ����ϴ� �Լ��� �������� �ʴ´�.
��Ʈ���� ȭ������ ���� ����� �� ������ �ݵ�� �޸� DC�� �̸� �غ��� ���� ����ؾ� �Ѵ�.
�޸� DC�� ȭ�� DC�� ������ Ư���� ������ �� ���ο� ��� ǥ���� ���� �޸� �����̴�.

�޸� DC�� ���� �׸��� �׸� �� ����� ���� �׷����� ������ �������� �ʰ� �� ����� ȭ������ ��� �����ϴ� ���(���� ���۸�)�� ���� ����Ѵ�.
*/


//*
//���� ȭ���� ���
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//DefWindowProc �Լ��� WndProc���� ó������ ���� ������ �޽����� ���� ó���� �Ѵ�.
	return g_main.WndProc(hWnd, iMsg, wParam, lParam);
}
