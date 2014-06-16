// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
// Windows 헤더 파일:
#include <windows.h>

// C의 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <mmsystem.h>
#include <iostream>
#include <Shellapi.h>
#include <XInput.h>
#include <assert.h>
// 3D 헤더
#include <d3d9.h>
#include <d3dx9.h>
//#pragma comment( lib, "d3d9.lib" )
//#pragma comment( lib, "d3dx9.lib" )

//	기본 헤더

//GFx 헤더

//사용자 정의 헤더



//전역 디파인
#define		PI	3.141592f
//해상도 사이즈 정의
#define		WIN_WIDTH	1024
#define		WIN_HEIGHT	768




#define		SAFE_DELETE(p)			if( p != NULL ) { delete p; p = NULL;		}
#define		SAFE_DELETE_ARRAY(p)	if( p != NULL ) { delete [] p; p= NULL;		}
#define		SAFE_RELEASE(p)			if( p != NULL ) { p->Release(); p = NULL;	}


//전역 변수
//전역 구조체

//< 동차좌표계 버텍스
typedef struct	tagVerRhwColor
{
	float					x,y,z,rhw;		//< 동차좌표
	DWORD					dwColor;		//< 색상 
	
	//< XYZ | 동차좌표계 | 확산광
	enum  { FVF_VER_RHW_COLOR = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE) };

}sVER_RHW_COLOR,*LPVER_RHW_COLOR;

//<	일반좌표계 버텍스
typedef struct	tagVerColor
{
	D3DXVECTOR3				vPos;		//< 좌표
	DWORD					dwColor;	//< 색상 
	
	//< XYZ | 동차좌표계 | 확산광
	enum  { FVF_VER_COLOR = (D3DFVF_XYZ | D3DFVF_DIFFUSE) };

}sVER_COLOR,*LPVER_COLOR;




//전역 열거체
//사용자 전역 헤더
