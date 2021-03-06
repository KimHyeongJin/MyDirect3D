// stdafx.h : 濠輿 餌辨ж雖虜 濠輿 滲唳腎雖朝 彊朝
// ル遽 衛蝶蠱 んл だ橾 塽 Щ煎薛お 婦溼 んл だ橾檜
// 菟橫 氈朝 んл だ橾殮棲棻.
//

#pragma once

//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
// ≧收式 晦獄④渦, Janus. 式收≧
//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 剪曖 餌辨腎雖 彊朝 頂辨擎 Windows ④渦縑憮 薯諼м棲棻.


// TODO: Щ煎斜極縑 в蹂и 蹺陛 ④渦朝 罹晦縑憮 霤褻м棲棻.
//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
// ≧收式 瞪羲 ④渦, Janus. 式收≧
//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
// Windows ④渦 だ橾:
#include <windows.h>

// C曖 楛顫歜 ④渦 だ橾殮棲棻.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>

#include <iostream>
//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
// ≧收式 3D ④渦, Janus. 式收≧
//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

//	晦獄 ④渦
#include "JN_Base3D.h"
using namespace JN_Base3D;

//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
// ≧收式 瞪羲 蛤だ檣, Janus. 式收≧
//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收

// 孺紫辦曖 觼晦 
#define		WINSIZE_X	1024 
#define		WINSIZE_Y	768


#define		SAFE_DELETE(p)			if( p != NULL ) { delete p; p = NULL;		}
#define		SAFE_DELETE_ARRAY(p)	if( p != NULL ) { delete [] p; p= NULL;		}
#define		SAFE_RELEASE(p)			if( p != NULL ) { p->Release(); p = NULL;	}

//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
// ≧收式 瞪羲 滲熱, Janus. 式收≧
//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收

//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
// ≧收式 瞪羲 掘褻羹 , Janus. 式收≧
//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收

//< 翕離謝ル啗 幗臢蝶
typedef struct	tagVerRhwColor
{
	float					x,y,z,rhw;		//< 翕離謝ル
	DWORD					dwColor;		//< 儀鼻 
	
	//< XYZ | 翕離謝ル啗 | �捉穇�
	enum  { FVF_VER_RHW_COLOR = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE) };

}sVER_RHW_COLOR,*LPVER_RHW_COLOR;

//<	橾奩謝ル啗 幗臢蝶
typedef struct	tagVerColor
{
	D3DXVECTOR3				vPos;		//< 謝ル
	DWORD					dwColor;	//< 儀鼻 
	
	//< XYZ | 翕離謝ル啗 | �捉穇�
	enum  { FVF_VER_COLOR = (D3DFVF_XYZ | D3DFVF_DIFFUSE) };

}sVER_COLOR,*LPVER_COLOR;

//<	橾奩謝ル啗 幗臢蝶
typedef struct	tagVerNormalTex
{
	D3DXVECTOR3				vPos;		//< 謝ル
	D3DXVECTOR3				vNormal;	//< 喻蜓漱攪( 徹摹 )
	D3DXVECTOR2				UV;			//<	臢撚謝ル
	
	//< XYZ | 翕離謝ル啗 | �捉穇�
	enum  { FVF_VER_NOR_TEX = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 ) };

}VER_NOR_TEX,*LPVER_NOR_TEX;
//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
// ≧收式 瞪羲 翮剪羹, Janus. 式收≧
//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收

//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
// ≧收式 餌辨濠 瞪羲 ④渦, Janus. 式收≧
//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
#include "JN_DXFontMgr.h"

#define	FONT_MGR		JN_DXFontMgr::GetInstance()








//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
// ≧收式 , Janus. 式收≧
//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收