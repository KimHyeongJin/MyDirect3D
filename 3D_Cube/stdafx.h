// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C�� ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <mmsystem.h>
#include <iostream>
#include <Shellapi.h>
#include <XInput.h>
#include <assert.h>
// 3D ���
#include <d3d9.h>
#include <d3dx9.h>
//#pragma comment( lib, "d3d9.lib" )
//#pragma comment( lib, "d3dx9.lib" )

//	�⺻ ���

//GFx ���

//����� ���� ���



//���� ������
#define		PI	3.141592f
//�ػ� ������ ����
#define		WIN_WIDTH	1024
#define		WIN_HEIGHT	768




#define		SAFE_DELETE(p)			if( p != NULL ) { delete p; p = NULL;		}
#define		SAFE_DELETE_ARRAY(p)	if( p != NULL ) { delete [] p; p= NULL;		}
#define		SAFE_RELEASE(p)			if( p != NULL ) { p->Release(); p = NULL;	}


//���� ����
//���� ����ü

//< ������ǥ�� ���ؽ�
typedef struct	tagVerRhwColor
{
	float					x,y,z,rhw;		//< ������ǥ
	DWORD					dwColor;		//< ���� 
	
	//< XYZ | ������ǥ�� | Ȯ�걤
	enum  { FVF_VER_RHW_COLOR = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE) };

}sVER_RHW_COLOR,*LPVER_RHW_COLOR;

//<	�Ϲ���ǥ�� ���ؽ�
typedef struct	tagVerColor
{
	D3DXVECTOR3				vPos;		//< ��ǥ
	DWORD					dwColor;	//< ���� 
	
	//< XYZ | ������ǥ�� | Ȯ�걤
	enum  { FVF_VER_COLOR = (D3DFVF_XYZ | D3DFVF_DIFFUSE) };

}sVER_COLOR,*LPVER_COLOR;




//���� ����ü
//����� ���� ���
