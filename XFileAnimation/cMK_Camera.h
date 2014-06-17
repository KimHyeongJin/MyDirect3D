#pragma once

class cMK_Camera
{
protected:
	LPDIRECT3DDEVICE9	m_pd3dDevice;

	D3DXVECTOR3			m_vEye;
	D3DXVECTOR3			m_vLookAt;
	D3DXVECTOR3			m_vUp;
	D3DXVECTOR3			m_vRight;

	//	룩과 아이 사이의 거리
	float				m_fDist;

	D3DXMATRIXA16		m_matView;
	D3DXMATRIXA16		m_matProj;
	D3DXMATRIXA16		m_matViewProj;
	D3DXMATRIXA16		m_matBill;

protected:
	void		Update();

	void		SetMatrix();
	void		SetView();
	void		SetProj();
	void		SetViewProj();
	void		SetRight();
	void		SetBill();

	D3DXVECTOR3	RotateAxis_X( float	fAngleX );
	D3DXVECTOR3	RotateAxis_Y( float	fAngleY );

public:

	cMK_Camera(void);
	virtual ~cMK_Camera(void);

	//	카메라 초기화
	void	InitCam( LPDIRECT3DDEVICE9 pd3dDevice, D3DXVECTOR3 *pEye, D3DXVECTOR3	*pLookAt );

	void	SetUp( D3DXVECTOR3	*pEye, D3DXVECTOR3	*pLookAt, D3DXVECTOR3	*pUp );

	//////////////////////////////////////////////////////////////////////////

	//	자전
	void	Rotation_X( float	fAngleX );
	void	Rotation_Y( float	fAngleY );

	//	공전
	void	Revolution_X( float	fAngleX );
	void	Revolution_Y( float  fAngleY );

	//	줌
	void	ZoomInOut( float fDist );
	void	SetDist( float fDist );

	//////////////////////////////////////////////////////////////////////////
	D3DXVECTOR3		GetLookVector();

	D3DXVECTOR3*	GetEye(VOID)
	{
		return	&m_vEye;
	}

	D3DXVECTOR3*	GetLookAt()
	{
		return &m_vLookAt;
	}

	D3DXMATRIXA16*	GetView()
	{
		return &m_matView;
	}

	D3DXMATRIXA16*	GetProj()
	{
		return &m_matProj;
	}

	D3DXMATRIXA16*	GetBill()
	{
		return &m_matBill;
	}

	//////////////////////////////////////////////////////////////////////////
	virtual	void	KeyInput(VOID) {}
};
