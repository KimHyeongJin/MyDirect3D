#include "stdafx.h"
#include "cMainGame.h"


LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );//prototype
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("3D_Cube");
cMainGame	g_MainGame;
HWND g_hwnd;

// apientry			==  winmain함수의 호출 방식을 의미한다
// hInstance		==	프로그램의 인스턴스 핸들이다(윈도우즈 운영체제에서 정해줄 윈도우의 코드번호(고유명사)).
// hPrevInstance	==	바로 앞에 실행된 프로그램의 인스턴스 핸들.
// lpszCmdParam		==	실행 직후에 열 파일의 경로가 전달된다.
// nCmdShow			==  윈도우를 화면에 출력할 방법(윈도우를 활성화 하여 보여준다라는 의미,또는 숨긴다.)
int APIENTRY WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd )
{
	//HWND hWnd;
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

	//1.윈도우 클래스 작성 (윈도우의 속성을 정의 한다)
	WndClass.cbClsExtra		= 0;									//윈도우즈가 내부적으로 사용할 여분메모리	
	WndClass.cbWndExtra		= 0;									//윈도우즈가 내부적으로 사용할 여분메모리
	WndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);	//배경색상 지정
	WndClass.hCursor		= LoadCursor(NULL,IDC_ARROW);			//커서를 설정한다(리소스를 통해서 원하는 그래픽를 등록 할수도 있다)
	WndClass.hIcon			= LoadIcon(NULL,IDI_APPLICATION);		//아이콘을 읽는다(리소스를 통해서 원하는 그래픽를 등록 할수도 있다)
	WndClass.hInstance		= hInstance;							//윈도우 클래스의 인스턴스(윈도우즈 운영체제에서 정해줄 윈도우의 코드번호(고유명사))
	WndClass.lpfnWndProc	= (WNDPROC)WndProc;						//윈도우 프로시저의 이름(윈도우의 메시지 처리 함수를 지정)
	WndClass.lpszClassName	= lpszClass;							//윈도우 클래스의 이름(어디까지나 클래스 이름일 뿐이다)
	WndClass.lpszMenuName	= NULL;									//메뉴의 이름(리소스 에디터 의해 별도로 만들어짐, 사용을 안하면 NULL)
	WndClass.style			= CS_HREDRAW | CS_VREDRAW;				//윈도우의 스타일(윈도우의 크기가 변할때 다시 그린다.)

	//2.윈도우 클래스 등록
	RegisterClass(&WndClass);

	//3.윈도우 생성(메모리 상에 윈도우를 생성한다)
	g_hwnd  = CreateWindow(lpszClass,			// 윈도우클래스 문자열 
		lpszClass,							// 타이틀바에 나타날 문자열
		WS_OVERLAPPEDWINDOW,				// 윈도우의 형태 옵션(OR 연산자 사용)타이틀바, 스크롤바, 크기조절가능 등등
		x, y,								// 윈도우 시작위치
		nWidth, nHeight,					// 윈도우 크기
		NULL,								// 부모윈도우의 핸들 (부모 윈도우가 없고 자신이 최상위 윈도우 일때 NULL)
		(HMENU)NULL,						// 메뉴의 핸들 (메뉴를 사용 안하므로 NULL)			
		hInstance,							// 인스턴스
		NULL);								// createStruct라는 구조체의 주소 (여러개의 윈도우를 만들때 사용 되나 거의 사용하지 않는다.)


	//< D3D초기화
	if( g_MainGame.Init3D( g_hwnd , hInstance , TRUE, WIN_WIDTH , WIN_HEIGHT ) != S_OK )
	{
		g_MainGame.Release();
		return 0;
	}

	///< 초기화
	if( g_MainGame.InitWindow() == FALSE )
	{
		///< 실패시 종료처리
		return 0;
	}

	//4.윈도우 보여주기
	ShowWindow(g_hwnd,nShowCmd);

	//5.메시지 루프
	//메시지 루프는 윈도우즈의 멀티태스킹을 지원하는 굉장히 중요한 역할을 하며 따라서 윈도우즈를 이해하기 위한 핵심 루프이다.
	//함수 원형 > BOOL GetMessage(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax)
	//메시지 큐에서 메시지를 읽어들인다.
	//읽어들인 메시지가 프로그램을 종료하라는 WM_QUIT일 경우 FALSE,그 외의 메시지이면 TRUE를 리턴한다.
	while(true)
	{
		if ( PeekMessage( &Message, NULL, 0U, 0U, PM_REMOVE ))
		{
			if(Message.message == WM_QUIT) break;
			//키보드의 눌림(WN_KEYDOWN)메시지가 발생할 때 문자가 입력되었다는 메시지(WM_CHAR)를 만드는 역할을 한다.
			//WM_CHAR 메시지를 전혀 받을 필요가 없다면 생략해도 상관없다.
			TranslateMessage(&Message);
			//메시지 큐에서 꺼낸 메시지를 윈도우의 메시지 처리 함수(WndProc)로 전달한다.
			DispatchMessage(&Message);
		}
		else
		{
			/// 처리할 메시지가 없으면 Render()함수 호출
			g_MainGame.Update();
			g_MainGame.Render();
		}
	}

	g_MainGame.Release();

	return int(Message.wParam);
}
/*
윈도우즈는 비트맵을 곧바로 화면 DC로 출력하는 함수는 제공하지 않는다.
비트맵은 화면으로 직접 출력할 수 없으며 반드시 메모리 DC에 미리 준비해 놓고 사용해야 한다.
메모리 DC란 화면 DC와 동일한 특성을 가지며 그 내부에 출력 표면을 가진 메모리 영역이다.

메모리 DC에 먼저 그림을 그린 후 사용자 눈에 그려지는 과정은 보옂지 않고 그 결과만 화면으로 고속 복사하는 방법(더블 버퍼링)을 많이 사용한다.
*/

//WndProc은 메시지를 처리했을 경우 반드시 0을 리턴해야 한다.
//또한 DefWindowProc 함수가 메시지를 처리했을경우 이 함수가 리턴한 값을 WndProc 함수가 다시 리턴해야 한다.
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//DefWindowProc 함수는 WndProc에서 처리하지 않은 나머지 메시지에 관한 처리를 한다.
	return g_MainGame.MainProc(hWnd, iMsg, wParam, lParam);
}




