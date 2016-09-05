#pragma once

#include "Incopiable.h"

class ScreenResolution : Incopiable
{
	int height;
	int width;

	static ScreenResolution *singleton;
	ScreenResolution();

public:
	static ScreenResolution *get() noexcept
	{
		return singleton;
	}

	int GetHeight();

	int GetWidth();

};