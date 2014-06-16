#pragma once

typedef	struct	tagVector
{
	float	x, y, z;
}VECTOR, *LPVECTOR;

class C3DCoordinateAxisMain
{
private:
	HBITMAP m_hBit, m_hOldBit;
	HDC m_hMemDc;
	VECTOR m_clickVecPt[CLICK_MAX];
	VECTOR m_crossVec;
	UINT m_clickCnt;
	float degree;
public:
	C3DCoordinateAxisMain(void);
	~C3DCoordinateAxisMain(void);
	VOID Init(VOID);
	VOID RegisterTimer();
	VOID UnregisterTimer();
	VOID Release();
	VOID Update();
	VOID PreRender(HDC hdc);
	VOID Render(HDC hdc);
	VOID PostRender(HDC hdc);
	VOID Work();
	LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	VOID D3DVecNormalize(LPVECTOR,LPVECTOR);
	float D3DVecLength(LPVECTOR);
	VOID D3DVecCross( LPVECTOR pOut, LPVECTOR pVec1, LPVECTOR pVec2 );
	float D3DVecDot( LPVECTOR pVec1, LPVECTOR pVec2 );
};
