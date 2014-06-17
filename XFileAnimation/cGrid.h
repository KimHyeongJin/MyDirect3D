#pragma once



class cGrid
{
private:
	INT GRID_WIDTH;
	INT GRID_VERMAX;

private:
	LPDIRECT3DVERTEXBUFFER9		m_GridVB;
	LPDIRECT3DVERTEXBUFFER9		m_ArrowVB;

	//<	버텍스 구조체
	sVER_COLOR					*m_sGridVer;
	sVER_COLOR					m_sArrowVer[ 18 ];

	VOID						GridInit(VOID);
	VOID						ArrowInit(VOID);
	VOID						GridRender(VOID);
	VOID						ArrowRender(VOID);
public:
	cGrid(void);
	~cGrid(void);

	VOID						Init( INT nWidth );
	VOID						Render(VOID);
};
