//¹öÁ¯ Á¤º¸
//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
// ¡Ù¦¬¦¡ 10-07-10, Çì´õÆÄÀÏ, Janus. ¦¡¦¬¡Ù
//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
#include "stdafx.h"
#include "cMainGame.h"

//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
// ¡Ù¦¬¦¡ 10-07-10, Àü¿ªº¯¼ö, Janus. ¦¡¦¬¡Ù
//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
char  		g_ClassName[128] = "Janus";		//Å¬·¡½º ÀÌ¸§
char  		g_WinName[128] = "Janus";			//À©µµ¿ì ÀÌ¸§
cMainGame	g_MainGame;

//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
// ¡Ù¦¬¦¡ 10-07-10, ÇÔ¼ö ÇÁ·ÎÅä Å¸ÀÔ, Janus. ¦¡¦¬¡Ù(ÇÔ¼öÀÇ ¿øÇü ¼±¾ð)
//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
// ¡Ù¦¬¦¡ 10-07-10, À©µµ¿ì ¸ÞÀÎ ÇÔ¼ö, Janus. ¦¡¦¬¡Ù
//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
// apientry			==  winmainÇÔ¼öÀÇ È£Ãâ ¹æ½ÄÀ» ÀÇ¹ÌÇÑ´Ù
// hInstance		==	ÇÁ·Î±×·¥ÀÇ ÀÎ½ºÅÏ½º ÇÚµéÀÌ´Ù(À©µµ¿ìÁî ¿î¿µÃ¼Á¦¿¡¼­ Á¤ÇØÁÙ À©µµ¿ìÀÇ ÄÚµå¹øÈ£(°íÀ¯¸í»ç)).
// hPrevInstance	==	¹Ù·Î ¾Õ¿¡ ½ÇÇàµÈ ÇÁ·Î±×·¥ÀÇ ÀÎ½ºÅÏ½º ÇÚµé.
// lpszCmdParam		==	½ÇÇà Á÷ÈÄ¿¡ ¿­ ÆÄÀÏÀÇ °æ·Î°¡ Àü´ÞµÈ´Ù.
// nCmdShow			==  À©µµ¿ì¸¦ È­¸é¿¡ Ãâ·ÂÇÒ ¹æ¹ý(À©µµ¿ì¸¦ È°¼ºÈ­ ÇÏ¿© º¸¿©ÁØ´Ù¶ó´Â ÀÇ¹Ì,¶Ç´Â ¼û±ä´Ù.)
//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam, int nCmdShow)
{
	MSG			Message;		//¸Þ¼¼Áö ±¸Á¶Ã¼ ¼±¾ð
	WNDCLASS	WndClass;		//À©µµ¿ì Å¬·¡½º ¼±¾ð
	int			nWidth, nHeight;//À©µµ¿ì Å©±â 

	//À©µµ¿ìÃ¢ Å©±â ¸¸µé±â.
	nWidth = WINSIZE_X + GetSystemMetrics(SM_CXFRAME) * 2;
	nHeight = WINSIZE_Y + GetSystemMetrics(SM_CYFRAME ) * 2 +
		GetSystemMetrics(SM_CYCAPTION);

	// 1 À©µµ¿ì Å¬·¡½º ÀÛ¼º (À©µµ¿ìÀÇ ¼Ó¼ºÀ» Á¤ÀÇ ÇÑ´Ù)
	WndClass.cbClsExtra		= 0;									//À©µµ¿ìÁî°¡ ³»ºÎÀûÀ¸·Î »ç¿ëÇÒ ¿©ºÐ¸Þ¸ð¸®	
	WndClass.cbWndExtra		= 0;									//À©µµ¿ìÁî°¡ ³»ºÎÀûÀ¸·Î »ç¿ëÇÒ ¿©ºÐ¸Þ¸ð¸®
	WndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);	//¹è°æ»ö»ó ÁöÁ¤
	WndClass.hCursor		= LoadCursor(NULL,IDC_ARROW);			//Ä¿¼­¸¦ ¼³Á¤ÇÑ´Ù(¸®¼Ò½º¸¦ ÅëÇØ¼­ ¿øÇÏ´Â ±×·¡ÇÈ¸¦ µî·Ï ÇÒ¼öµµ ÀÖ´Ù)
	WndClass.hIcon			= LoadIcon(NULL,IDI_APPLICATION);		//¾ÆÀÌÄÜÀ» ÀÐ´Â´Ù(¸®¼Ò½º¸¦ ÅëÇØ¼­ ¿øÇÏ´Â ±×·¡ÇÈ¸¦ µî·Ï ÇÒ¼öµµ ÀÖ´Ù)
	WndClass.hInstance		= hInstance;							//À©µµ¿ì Å¬·¡½ºÀÇ ÀÎ½ºÅÏ½º(À©µµ¿ìÁî ¿î¿µÃ¼Á¦¿¡¼­ Á¤ÇØÁÙ À©µµ¿ìÀÇ ÄÚµå¹øÈ£(°íÀ¯¸í»ç))
	WndClass.lpfnWndProc	= (WNDPROC)WndProc;						//À©µµ¿ì ÇÁ·Î½ÃÀúÀÇ ÀÌ¸§(À©µµ¿ìÀÇ ¸Þ½ÃÁö Ã³¸® ÇÔ¼ö¸¦ ÁöÁ¤)
	WndClass.lpszClassName	= g_ClassName;							//À©µµ¿ì Å¬·¡½ºÀÇ ÀÌ¸§(¾îµð±îÁö³ª Å¬·¡½º ÀÌ¸§ÀÏ »ÓÀÌ´Ù)
	WndClass.lpszMenuName	= NULL;									//¸Þ´ºÀÇ ÀÌ¸§(¸®¼Ò½º ¿¡µðÅÍ ÀÇÇØ º°µµ·Î ¸¸µé¾îÁü, »ç¿ëÀ» ¾ÈÇÏ¸é NULL)
	WndClass.style			= CS_HREDRAW | CS_VREDRAW;				//À©µµ¿ìÀÇ ½ºÅ¸ÀÏ(À©µµ¿ìÀÇ Å©±â°¡ º¯ÇÒ¶§ ´Ù½Ã ±×¸°´Ù.)

	// 2 Å¬·¡½º¸¦ µî·ÏÇÑ´Ù (Á¤ÀÇÇÑ À©µµ¿ì Å¬·¡½º¸¦ µî·ÏÇÑ´Ù)
	RegisterClass(&WndClass);										

	//< À©µµ¿ì È­¸é Áß¾ÓÀ¸·Î 
	INT		nFullX	= GetSystemMetrics(SM_CXFULLSCREEN);
	INT		nFullY	= GetSystemMetrics(SM_CYFULLSCREEN);

	INT		nStartX = nFullX/2 - WINSIZE_X/2;
	INT		nStartY = nFullY/2 - WINSIZE_Y/2;

	// 3 À©µµ¿ì¸¦ ¸¸µç´Ù (¸Þ¸ð¸® »ó¿¡ À©µµ¿ì¸¦ »ý¼ºÇÑ´Ù)
	HWND hWnd  = CreateWindow(g_ClassName,				// À©µµ¿ìÅ¬·¡½º ¹®ÀÚ¿­ 
						  g_WinName,				// Å¸ÀÌÆ²¹Ù¿¡ ³ªÅ¸³¯ ¹®ÀÚ¿­
						  WS_OVERLAPPEDWINDOW,		// À©µµ¿ìÀÇ ÇüÅÂ ¿É¼Ç(OR ¿¬»êÀÚ »ç¿ë)Å¸ÀÌÆ²¹Ù, ½ºÅ©·Ñ¹Ù, Å©±âÁ¶Àý°¡´É µîµî
						  nStartX, nStartY,			// À©µµ¿ì ½ÃÀÛÀ§Ä¡
						  nWidth, nHeight,			// À©µµ¿ì Å©±â
						  NULL,						// ºÎ¸ðÀ©µµ¿ìÀÇ ÇÚµé (ºÎ¸ð À©µµ¿ì°¡ ¾ø°í ÀÚ½ÅÀÌ ÃÖ»óÀ§ À©µµ¿ì ÀÏ¶§ NULL)
						  (HMENU)NULL,				// ¸Þ´ºÀÇ ÇÚµé (¸Þ´º¸¦ »ç¿ë ¾ÈÇÏ¹Ç·Î NULL)			
						  hInstance,				// ÀÎ½ºÅÏ½º
						  NULL);					// createStruct¶ó´Â ±¸Á¶Ã¼ÀÇ ÁÖ¼Ò (¿©·¯°³ÀÇ À©µµ¿ì¸¦ ¸¸µé¶§ »ç¿ë µÇ³ª °ÅÀÇ »ç¿ëÇÏÁö ¾Ê´Â´Ù.)
	
	//< D3DÃÊ±âÈ­
	if( JN_Base3D::Init3D( hWnd , hInstance , TRUE, WINSIZE_X , WINSIZE_Y ) != S_OK )
	{
		JN_Base3D::Release();
		return 0;
	}

	///< ÃÊ±âÈ­
	if( g_MainGame.InitWindow() == FALSE )
	{
		///< ½ÇÆÐ½Ã Á¾·áÃ³¸®
		return 0;
	}
	
	// 4 À©µµ¿ì¸¦ È­¸é¿¡ º¸¿©ÁØ´Ù
	ShowWindow(hWnd, nCmdShow);


	while(true)
	{
        /// ¸Þ½ÃÁöÅ¥¿¡ ¸Þ½ÃÁö°¡ ÀÖÀ¸¸é ¸Þ½ÃÁö Ã³¸®
		if( PeekMessage( &Message, NULL, 0U, 0U, PM_REMOVE ) )
		{
			if(Message.message == WM_QUIT) break;
			TranslateMessage( &Message );
			DispatchMessage( &Message );
		}
		else
		{
			/// Ã³¸®ÇÒ ¸Þ½ÃÁö°¡ ¾øÀ¸¸é Render()ÇÔ¼ö È£Ãâ
			//  Process(), Update()
			//	Render();
			g_MainGame.Update();
			g_MainGame.Render();
		}
	}


	
	//GetMessage(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterJanus, UINT wMsgFilterMAx)¸Þ½ÃÁöÅ¥¿¡¼­ ÀÐ¾îµéÀÎ  ¸Þ¼¼Áö°¡ WM_QUIT¸é false ¸®ÅÏ ³ª¸ÓÁö´Â true ¸®ÅÏ
	//lpMsg : ¸Þ½ÃÁöÀÇ ÁÖ¼Ò
	//hWnd : À©µµ¿ìÀÇ ÇÚµé 0ÀÌ¸é ¸ðµç À©µµ¿ìÀÇ ¸Þ½ÃÁö¸¦ °¡Á®¿À°í, ÇÚµé °ªÀ» ÁöÁ¤ÇÏ¸é ±×ÇÚµé°ª¿¡ Æ÷ÇÔµÈ ¸Þ½ÃÁö¸¸ °¡Á®¿Â´Ù.
	//wMsgFilterJanus, wMsgFilterMAx : ¸Þ½ÃÁö¸¦ ÀÐ¾îµéÀÏ ¹üÀ§ ÃÖ¼Ò°ª ÃÖ´ë°ª(»ç¿ëÇÒ°æ¿ì ½Ã½ºÅÛÀÌ ¹«ÇÑ·çÇÁ¿¡ ºüÁú¼ö ÀÖ´Ù.)
	// 4 ¸Þ¼¼Áö ·çÇÁ(»ç¿ëÀÚ·ÎºÎÅÍÀÇ ¸Þ½ÃÁö¸¦ Ã³¸®ÇÑ´Ù !¸Þ½ÃÁö ±¸µ¿½Ã½ºÅÛ)
	
	///< ÇØÁ¦
	g_MainGame.Release();
	

	
	return Message.wParam;
}


//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
// ¡Ù¦¬¦¡ 10-07-10, À©µµ¿ì ÇÁ·Î½ÃÀú, Janus.(¸Þ¼¼Áö Ã³¸® ÇÔ¼ö) ¦¡¦¬¡Ù
//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	return g_MainGame.MainProc(hWnd, iMessage, wParam, lParam);
}