
#include "ScreenResolution.h"
#include "MouseClicker.h"



void MouseClicker::LeftClick(MousePoint& mp)
{
	INPUT Input = { 0 };

	if (mp.leftClick)
	{
		Input.type = INPUT_MOUSE;
		Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		SendInput(1, &Input, sizeof(INPUT));
	}
	else
	{
		Input.type = INPUT_MOUSE;
		Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		SendInput(1, &Input, sizeof(INPUT));
	}
}

MousePoint MouseClicker::GetMousePosition()
{
	MousePoint mpt;

	POINT pt;
	GetCursorPos(&pt);
	mpt.loc = pt;

	if ((GetKeyState(VK_LBUTTON) & 0x100) != 0)
	{
		mpt.leftClick = true;
	}

	return mpt;
}

MousePoint MouseClicker::GetRandMousePosition(int rand)
{
	MousePoint pt = GetMousePosition();

	std::uniform_int_distribution<int> distribution{ -rand, rand };

	pt.loc.x += distribution(rng);
	pt.loc.y += distribution(rng);

	return pt;
}

void MouseClicker::SetMousePosition(MousePoint& mp)
{

	// http://msdn.microsoft.com/en-us/library/ms646260(VS.85).aspx
	// If MOUSEEVENTF_ABSOLUTE value is specified, dx and dy contain normalized absolute coordinates between 0 and 65,535.
	// The event procedure maps these coordinates onto the display surface.
	// Coordinate (0,0) maps onto the upper-left corner of the display surface, (65535,65535) maps onto the lower-right corner.
	float fx = mp.loc.x * (65535.0f / ScreenResolution::get()->GetWidth());
	float fy = mp.loc.y * (65535.0f / ScreenResolution::get()->GetHeight());

	INPUT Input = { 0 };
	Input.type = INPUT_MOUSE;

	Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;

	Input.mi.dx = (long)fx;
	Input.mi.dy = (long)fy;

	SendInput(1, &Input, sizeof(INPUT));
}


void MouseClicker::Reproduce(MousePoint& mp)
{
	SetMousePosition(mp);

	LeftClick(mp);
}