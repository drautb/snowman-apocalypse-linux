#include "Mouse.h"

void MousePosCallback(int newXPos, int newYPos)
{
	Mouse::GetInstance().xPos = newXPos;
	Mouse::GetInstance().yPos = newYPos;
}

void MouseButtonCallback(int button, int pressed)
{
	Mouse::GetInstance().buttons[button] = pressed;
	Mouse::GetInstance().buttonLocks[button] = pressed > 0 ? true : false;
}

Mouse::Mouse(void)
{

}

Mouse::~Mouse()
{

}

bool Mouse::ButtonIsDown(int button)
{
	return buttons[button];
}

bool Mouse::ButtonIsHit(int button)
{
	bool hit = buttons[button] && buttonLocks[button];

	buttonLocks[button] = false;

	return hit;
}