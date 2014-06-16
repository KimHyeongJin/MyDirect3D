#include "stdafx.h"
#include "C3DCoordinateAxisMain.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("3D좌표축의이해");
HWND g_hWnd;
POINT g_ptMouse;

C3DCoordinateAxisMain g_main;

int APIENTRY WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd )
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	//Client Area가 1024/768인 윈도우의 가로, 세로 값을 구한다.
	UINT nWidth, nHeight;	
	nWidth = WIN_WIDTH + GetSystemMetrics(SM_CXFRAME)*2;
	nHeight = WIN_HEIGHT + GetSystemMetrics(SM_CYFRAME)*2 + GetSystemMetrics(SM_CYCAPTION);

	//윈도우를 스크린 중앙에 위치시키기 위해 x,y를 구한다.
	UINT x,y;
	x = (GetSystemMetrics(SM_CXSCREEN) - nWidth) >> 1;
	y = (GetSystemMetrics(SM_CYSCREEN) - nHeight) >>1;

	//1.윈도우 클래스 설정
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

	//2.윈도우 클래스 등록
	RegisterClass(&WndClass);

	//3.윈도우 생성
	hWnd = CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW,x,y,nWidth,nHeight,NULL,NULL,hInstance,NULL);
	g_hWnd = hWnd;
	//4.윈도우 보여주기
	ShowWindow(hWnd,nShowCmd);

	g_main.Init();
	//5.메시지 루프
	//메시지 루프는 윈도우즈의 멀티태스킹을 지원하는 굉장히 중요한 역할을 하며 따라서 윈도우즈를 이해하기 위한 핵심 루프이다.
	//함수 원형 > BOOL GetMessage(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax)
	//메시지 큐에서 메시지를 읽어들인다.
	//읽어들인 메시지가 프로그램을 종료하라는 WM_QUIT일 경우 FALSE,그 외의 메시지이면 TRUE를 리턴한다.
	while(GetMessage(&Message,0,0,0))
	{
		//키보드의 눌림(WN_KEYDOWN)메시지가 발생할 때 문자가 입력되었다는 메시지(WM_CHAR)를 만드는 역할을 한다.
		//WM_CHAR 메시지를 전혀 받을 필요가 없다면 생략해도 상관없다.
		TranslateMessage(&Message);
		//메시지 큐에서 꺼낸 메시지를 윈도우의 메시지 처리 함수(WndProc)로 전달한다.
		DispatchMessage(&Message);
	}

	return int(Message.wParam);
}
/*
윈도우즈는 비트맵을 곧바로 화면 DC로 출력하는 함수는 제공하지 않는다.
비트맵은 화면으로 직접 출력할 수 없으며 반드시 메모리 DC에 미리 준비해 놓고 사용해야 한다.
메모리 DC란 화면 DC와 동일한 특성을 가지며 그 내부에 출력 표면을 가진 메모리 영역이다.

메모리 DC에 먼저 그림을 그린 후 사용자 눈에 그려지는 과정은 보여지지 않고 그 결과만 화면으로 고속 복사하는 방법(더블 버퍼링)을 많이 사용한다.
*/


//*
//가상 화면을 사용
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//DefWindowProc 함수는 WndProc에서 처리하지 않은 나머지 메시지에 관한 처리를 한다.
	return g_main.WndProc(hWnd, iMsg, wParam, lParam);
}
