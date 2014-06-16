#pragma once


#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <cmath>
#include <stdio.h>


#define		PI			3.14159265
#define		WIN_WIDTH	800
#define		WIN_HEIGHT	800
#define		TIMER_ID1	1
#define		TIMER_ID2	2
#define		CLICK_MAX	2

using namespace std;
#include "C3DCoordinateAxisMain.h"


#define SAFE_DELETE(p)	{if(p){delete (p);(p)=NULL;}}
#define SAFE_DELETE_ARRAY {if(p){delete[] (p);(p)=NULL; }}
#define	RADIAN(a) ((FLOAT)(((a)*((FLOAT)(PI)))/(180)))
#define	ANGLE(r) ((FLOAT)(((r)*(180))/((FLOAT)(PI))))
#define SQRT(x,y) sqrt((pow(x,2))+ (pow(y,2)))

extern HWND g_hWnd;
extern HINSTANCE g_hInst;
extern POINT g_ptMouse;