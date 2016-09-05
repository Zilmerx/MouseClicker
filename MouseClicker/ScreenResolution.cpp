
#include <windows.h>

#include "ScreenResolution.h"


ScreenResolution *ScreenResolution::singleton = new ScreenResolution;


int ScreenResolution::GetHeight()
{
	return height;
}

int ScreenResolution::GetWidth()
{
	return width;
}

ScreenResolution::ScreenResolution()
{
	width = GetSystemMetrics(SM_CXSCREEN) - 1;
	height = GetSystemMetrics(SM_CYSCREEN) - 1;
}