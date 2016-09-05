#pragma once

#include <windows.h>

struct MousePoint
{
	POINT loc;
	bool leftClick;

	MousePoint()
	{
		loc.x = 0;
		loc.y = 0;

		leftClick = false;
	}
};