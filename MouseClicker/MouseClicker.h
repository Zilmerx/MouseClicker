#pragma once

#include <random>
#include "MousePoint.h"


class MouseClicker
{
	std::mt19937 rng;

public:

	MouseClicker() = default;


	void LeftClick(MousePoint& mp);

	MousePoint GetMousePosition();
	MousePoint GetRandMousePosition(int rand);

	void SetMousePosition(MousePoint& mp);

	void Reproduce(MousePoint& mp);
};