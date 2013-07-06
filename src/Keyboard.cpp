#include <GLFW/glfw3.h>

#include "Keyboard.h"

void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Keyboard::GetInstance().keys[key] = action == GLFW_PRESS;
	Keyboard::GetInstance().keyLocks[key] = (action == GLFW_PRESS) ? true : false;
}

Keyboard::Keyboard(void)
{
	for (int k=0; k<KEY_COUNT; k++)
		keyLocks[k] = false;
}

/** 
 * Destructor
 */
Keyboard::~Keyboard(void)
{

}

/**
 * Other Methods
 */
bool Keyboard::KeyIsDown(char key)
{
	return KeyIsDown((int)key);
}

bool Keyboard::KeyIsDown(int key)
{
	return keys[key] == GLFW_PRESS;
}

bool Keyboard::KeyIsHit(char key)
{
	return KeyIsHit((int)key);
}

bool Keyboard::KeyIsHit(int key)
{
	bool hit = keys[key] && keyLocks[key];

	keyLocks[key] = false;

	return hit;
}






