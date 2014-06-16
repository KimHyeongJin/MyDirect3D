#include "stdafx.h"
#include "C3DCoordinateAxisMain.h"

C3DCoordinateAxisMain::C3DCoordinateAxisMain(void)
{
	ZeroMemory( m_clickVecPt, sizeof(VECTOR)*CLICK_MAX);
	m_clickCnt = 0;
	degree = 0.0f;
}

C3DCoordinateAxisMain::~C3DCoordinateAxisMain(void)
{
}

VOID C3DCoordinateAxisMain::Init(VOID)
{


	RegisterTimer();
}

VOID C3DCoordinateAxisMain::Release()
{
}

void C3DCoordinateAxisMain::Update()
{
	InvalidateRect(g_hWnd,NULL,false);
}

VOID C3DCoordinateAxisMain::Work()
{

}

VOID C3DCoordinateAxisMain::PreRender(HDC hdc)
{	
	//1. �޸� DC�� ����(ȭ�� DC�� �ڵ��� �ָ� �� ȭ�� DC�� ������ Ư���� ������ DC�� �޸𸮿� ����� �� �ڵ��� ����)
	m_hMemDc = CreateCompatibleDC(hdc);
	//2. DC�� ȣȯ ������ ��Ʈ���� �����Ѵ�.
	m_hBit = CreateCompatibleBitmap(hdc,WIN_WIDTH, WIN_HEIGHT);
	//3. �޸� DC�� ����� ��Ʈ���� �����ϰ� ���� ��Ʈ���� ���
	m_hOldBit = (HBITMAP)SelectObject(m_hMemDc, m_hBit);	

	RECT rt={0,0, WIN_WIDTH, WIN_HEIGHT};
	FillRect( m_hMemDc, &rt, (HBRUSH)GetStockObject(WHITE_BRUSH));
}


void C3DCoordinateAxisMain::Render(HDC hdc)//m_hMemDc�� �׷�����.
{
	//x��
	MoveToEx(hdc, 0, WIN_HEIGHT/2, NULL);
	LineTo( hdc, WIN_WIDTH, WIN_HEIGHT/2);

	//y��
	MoveToEx(hdc, WIN_WIDTH/2, 0, NULL);
	LineTo( hdc, WIN_WIDTH/2, WIN_HEIGHT);

	for(UINT i = 0; i < m_clickCnt ; i++)
	{
		VECTOR vec;
		vec.x = m_clickVecPt[i].x + WIN_WIDTH/2;
		vec.y = WIN_HEIGHT/2 - m_clickVecPt[i].y;
		vec.z = 0;
		MoveToEx(hdc, WIN_WIDTH/2, WIN_HEIGHT/2, NULL);
		LineTo( hdc, vec.x, vec.y);

		TCHAR szPt[256]={0,};
		sprintf_s(szPt,256, TEXT("��ǥ[ %d ] : %0.2f, %0.2f, %0.2f"),i, m_clickVecPt[i].x, m_clickVecPt[i].y,0);
		TextOut(hdc, vec.x, vec.y,szPt,lstrlen(szPt));
	}

	if( m_clickCnt == CLICK_MAX)
	{
		TCHAR log[256] = {0,};
		sprintf_s(log,256, TEXT("���� : %0.2f "),degree);
		TextOut(hdc, 0,0,log,lstrlen(log));

		sprintf_s(log,256, TEXT("���� : %0.2f, %0.2f, %0.2f "),m_crossVec.x, m_crossVec.y, m_crossVec.z );
		TextOut(hdc, 0,20,log,lstrlen(log));
	}
}

VOID C3DCoordinateAxisMain::PostRender(HDC hdc)
{
	BitBlt( hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT, m_hMemDc, 0, 0, SRCCOPY );
	SelectObject(m_hMemDc, m_hOldBit);
	DeleteObject(m_hBit);
	DeleteDC(m_hMemDc);
}



LRESULT CALLBACK C3DCoordinateAxisMain::WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	TCHAR log[256]={0,};
	//std::string info;
	HDC hdc;
	PAINTSTRUCT ps;
	//POINT pt;
	switch(iMsg)
	{
	case WM_TIMER:
		Update();
		return 0;
	case WM_LBUTTONDOWN:
		{
			POINT pt = {LOWORD(lParam), HIWORD(lParam)};
			if( m_clickCnt < CLICK_MAX )
			{
				m_clickVecPt[m_clickCnt].x = pt.x - WIN_WIDTH/2;
				m_clickVecPt[m_clickCnt].y = WIN_HEIGHT/2 - pt.y;
				m_clickVecPt[m_clickCnt].z = 0;


				m_clickCnt++;
				if(m_clickCnt == CLICK_MAX)
				{
					VECTOR tempVec[2];
					for (UINT i = 0 ; i < m_clickCnt ; i++ )
					{
						D3DVecNormalize( &tempVec[i], &m_clickVecPt[i]);
					}
					//cos0
					float cos = D3DVecDot( &tempVec[0], &tempVec[1] );
					
					//������ ����
					degree = acosf(cos)*180/PI;

					//����
					D3DVecCross(&m_crossVec, &tempVec[0], &tempVec[1]);
					D3DVecNormalize( &m_crossVec, &m_crossVec );
				}
			}
	
		}
		return 0;
	case WM_RBUTTONDOWN:
		if(m_clickCnt > 0)
		{
			m_clickCnt--;
		}
		return 0;
	case WM_PAINT:
		{			
			hdc = BeginPaint(hWnd,&ps);	
			PreRender(hdc);
			Render(m_hMemDc);
			PostRender(hdc);
			EndPaint(hWnd,&ps);
		}
		return 0;
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			UnregisterTimer();
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		UnregisterTimer();
		return 0;
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

VOID C3DCoordinateAxisMain::RegisterTimer()
{
	SetTimer(g_hWnd,TIMER_ID1,100,NULL);
}
VOID C3DCoordinateAxisMain::UnregisterTimer()
{
	KillTimer(g_hWnd,TIMER_ID1);
}

//	������ ũ��
float	C3DCoordinateAxisMain::D3DVecLength( LPVECTOR	pVec )
{
	return sqrt( pow( pVec->x, 2 ) + pow( pVec->y, 2 ) + pow( pVec->z, 2 )  );
}

//	��������
void	C3DCoordinateAxisMain::D3DVecNormalize( LPVECTOR pOut, LPVECTOR pSrc )
{
	float	fLength	=	D3DVecLength( pSrc );

	if( fLength == 0 )
	{
		return;
	}

	pOut->x	=	pSrc->x / fLength;
	pOut->y	=	pSrc->y / fLength;
	pOut->z	=	pSrc->z / fLength;
}


//	������ ����
float	C3DCoordinateAxisMain::D3DVecDot( LPVECTOR pVec1, LPVECTOR pVec2 )
{
	//A*B = |A|*|B|*cos
	//cos = (A/|A|)*(B/|B|)
	float	fDot = pVec1->x * pVec2->x + pVec1->y * pVec2->y +	pVec1->z * pVec2->z;	
	return fDot;
}


//	������ ����
void	C3DCoordinateAxisMain::D3DVecCross( LPVECTOR pOut, LPVECTOR pVec1, LPVECTOR pVec2 )
{
	VECTOR	fResult;

	fResult.x	=	pVec1->y * pVec2->z		-	pVec1->z * pVec2->y;
	fResult.y	=	pVec1->z * pVec2->x		-	pVec1->x * pVec2->z;
	fResult.z	=	pVec1->x * pVec2->y		-	pVec1->y * pVec2->x;

	*pOut	=	fResult;
}