//幗蟒 薑爾
//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
// ≧收式 10-07-10, ④渦だ橾, Janus. 式收≧
//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
#include "stdafx.h"
#include "cMainGame.h"

//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
// ≧收式 10-07-10, 瞪羲滲熱, Janus. 式收≧
//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
char  		g_ClassName[128] = "Janus";		//贗楚蝶 檜葷
char  		g_WinName[128] = "Janus";			//孺紫辦 檜葷
cMainGame	g_MainGame;

//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
// ≧收式 10-07-10, л熱 Щ煎饜 顫殮, Janus. 式收≧(л熱曖 錳⑽ 摹樹)
//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
// ≧收式 10-07-10, 孺紫辦 詭檣 л熱, Janus. 式收≧
//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
// apientry			==  winmainл熱曖 ��轎 寞衝擊 曖嘐и棻
// hInstance		==	Щ煎斜極曖 檣蝶欐蝶 с菟檜棻(孺紫辦鍔 遴艙羹薯縑憮 薑п還 孺紫辦曖 囀萄廓��(堅嶸貲餌)).
// hPrevInstance	==	夥煎 擅縑 褒ч脹 Щ煎斜極曖 檣蝶欐蝶 с菟.
// lpszCmdParam		==	褒ч 霜�醴� 翮 だ橾曖 唳煎陛 瞪殖脹棻.
// nCmdShow			==  孺紫辦蒂 �飛橦� 轎溘й 寞徹(孺紫辦蒂 �側瘓� ж罹 爾罹遽棻塭朝 曖嘐,傳朝 獗曹棻.)
//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam, int nCmdShow)
{
	MSG			Message;		//詭撮雖 掘褻羹 摹樹
	WNDCLASS	WndClass;		//孺紫辦 贗楚蝶 摹樹
	int			nWidth, nHeight;//孺紫辦 觼晦 

	//孺紫辦璽 觼晦 虜菟晦.
	nWidth = WINSIZE_X + GetSystemMetrics(SM_CXFRAME) * 2;
	nHeight = WINSIZE_Y + GetSystemMetrics(SM_CYFRAME ) * 2 +
		GetSystemMetrics(SM_CYCAPTION);

	// 1 孺紫辦 贗楚蝶 濛撩 (孺紫辦曖 樓撩擊 薑曖 и棻)
	WndClass.cbClsExtra		= 0;									//孺紫辦鍔陛 頂睡瞳戲煎 餌辨й 罹碟詭賅葬	
	WndClass.cbWndExtra		= 0;									//孺紫辦鍔陛 頂睡瞳戲煎 餌辨й 罹碟詭賅葬
	WndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);	//寡唳儀鼻 雖薑
	WndClass.hCursor		= LoadCursor(NULL,IDC_ARROW);			//醴憮蒂 撲薑и棻(葬模蝶蒂 鱔п憮 錳ж朝 斜楚а蒂 蛔煙 й熱紫 氈棻)
	WndClass.hIcon			= LoadIcon(NULL,IDI_APPLICATION);		//嬴檜夔擊 檗朝棻(葬模蝶蒂 鱔п憮 錳ж朝 斜楚а蒂 蛔煙 й熱紫 氈棻)
	WndClass.hInstance		= hInstance;							//孺紫辦 贗楚蝶曖 檣蝶欐蝶(孺紫辦鍔 遴艙羹薯縑憮 薑п還 孺紫辦曖 囀萄廓��(堅嶸貲餌))
	WndClass.lpfnWndProc	= (WNDPROC)WndProc;						//孺紫辦 Щ煎衛盪曖 檜葷(孺紫辦曖 詭衛雖 籀葬 л熱蒂 雖薑)
	WndClass.lpszClassName	= g_ClassName;							//孺紫辦 贗楚蝶曖 檜葷(橫蛤梱雖釭 贗楚蝶 檜葷橾 閨檜棻)
	WndClass.lpszMenuName	= NULL;									//詭景曖 檜葷(葬模蝶 縑蛤攪 曖п 滌紫煎 虜菟橫颶, 餌辨擊 寰ж賊 NULL)
	WndClass.style			= CS_HREDRAW | CS_VREDRAW;				//孺紫辦曖 蝶顫橾(孺紫辦曖 觼晦陛 滲й陽 棻衛 斜萼棻.)

	// 2 贗楚蝶蒂 蛔煙и棻 (薑曖и 孺紫辦 贗楚蝶蒂 蛔煙и棻)
	RegisterClass(&WndClass);										

	//< 孺紫辦 �飛� 醞懈戲煎 
	INT		nFullX	= GetSystemMetrics(SM_CXFULLSCREEN);
	INT		nFullY	= GetSystemMetrics(SM_CYFULLSCREEN);

	INT		nStartX = nFullX/2 - WINSIZE_X/2;
	INT		nStartY = nFullY/2 - WINSIZE_Y/2;

	// 3 孺紫辦蒂 虜萇棻 (詭賅葬 鼻縑 孺紫辦蒂 儅撩и棻)
	HWND hWnd  = CreateWindow(g_ClassName,				// 孺紫辦贗楚蝶 僥濠翮 
						  g_WinName,				// 顫檜ぎ夥縑 釭顫陳 僥濠翮
						  WS_OVERLAPPEDWINDOW,		// 孺紫辦曖 ⑽鷓 褫暮(OR 翱骯濠 餌辨)顫檜ぎ夥, 蝶觼煤夥, 觼晦褻瞰陛棟 蛔蛔
						  nStartX, nStartY,			// 孺紫辦 衛濛嬪纂
						  nWidth, nHeight,			// 孺紫辦 觼晦
						  NULL,						// 睡賅孺紫辦曖 с菟 (睡賅 孺紫辦陛 橈堅 濠褐檜 譆鼻嬪 孺紫辦 橾陽 NULL)
						  (HMENU)NULL,				// 詭景曖 с菟 (詭景蒂 餌辨 寰ж嘎煎 NULL)			
						  hInstance,				// 檣蝶欐蝶
						  NULL);					// createStruct塭朝 掘褻羹曖 輿模 (罹楝偃曖 孺紫辦蒂 虜菟陽 餌辨 腎釭 剪曖 餌辨ж雖 彊朝棻.)
	
	//< D3D蟾晦��
	if( JN_Base3D::Init3D( hWnd , hInstance , TRUE, WINSIZE_X , WINSIZE_Y ) != S_OK )
	{
		JN_Base3D::Release();
		return 0;
	}

	///< 蟾晦��
	if( g_MainGame.InitWindow() == FALSE )
	{
		///< 褒ぬ衛 謙猿籀葬
		return 0;
	}
	
	// 4 孺紫辦蒂 �飛橦� 爾罹遽棻
	ShowWindow(hWnd, nCmdShow);


	while(true)
	{
        /// 詭衛雖聽縑 詭衛雖陛 氈戲賊 詭衛雖 籀葬
		if( PeekMessage( &Message, NULL, 0U, 0U, PM_REMOVE ) )
		{
			if(Message.message == WM_QUIT) break;
			TranslateMessage( &Message );
			DispatchMessage( &Message );
		}
		else
		{
			/// 籀葬й 詭衛雖陛 橈戲賊 Render()л熱 ��轎
			//  Process(), Update()
			//	Render();
			g_MainGame.Update();
			g_MainGame.Render();
		}
	}


	
	//GetMessage(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterJanus, UINT wMsgFilterMAx)詭衛雖聽縑憮 檗橫菟檣  詭撮雖陛 WM_QUIT賊 false 葬欐 釭該雖朝 true 葬欐
	//lpMsg : 詭衛雖曖 輿模
	//hWnd : 孺紫辦曖 с菟 0檜賊 賅萇 孺紫辦曖 詭衛雖蒂 陛螳螃堅, с菟 高擊 雖薑ж賊 斜с菟高縑 んл脹 詭衛雖虜 陛螳螞棻.
	//wMsgFilterJanus, wMsgFilterMAx : 詭衛雖蒂 檗橫菟橾 彰嬪 譆模高 譆渠高(餌辨й唳辦 衛蝶蠱檜 鼠и瑞Щ縑 緒韓熱 氈棻.)
	// 4 詭撮雖 瑞Щ(餌辨濠煎睡攪曖 詭衛雖蒂 籀葬и棻 !詭衛雖 掘翕衛蝶蠱)
	
	///< п薯
	g_MainGame.Release();
	

	
	return Message.wParam;
}


//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
// ≧收式 10-07-10, 孺紫辦 Щ煎衛盪, Janus.(詭撮雖 籀葬 л熱) 式收≧
//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	return g_MainGame.MainProc(hWnd, iMessage, wParam, lParam);
}