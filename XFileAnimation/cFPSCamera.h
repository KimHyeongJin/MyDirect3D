#pragma once

#include "cMK_Camera.h"

class cFPSCamera
	: public cMK_Camera
{
	POINT	m_ptMouse;

public:
	cFPSCamera(void);
	~cFPSCamera(void);

	void	KeyInput(VOID);
};
