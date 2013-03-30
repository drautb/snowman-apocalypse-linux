#include <iostream>

#include <cmath>

#include <GL/glfw.h>

#include "Window.h"
#include "cs455Utils.h"

using namespace std;
using namespace Eigen;

void GLFWCALL ResizeCallback(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	return;
}

Window::Window(void)
{
	glfwInit();

}

Window::~Window(void)
{
	// Close window and terminate GLFW
	glfwTerminate();
}

bool Window::Open(void)
{
	if (!glfwOpenWindow(WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 0, 0, 1, 0, GLFW_WINDOW ))
		return false;

	glfwSetWindowSizeCallback(ResizeCallback);
	glfwSetKeyCallback(KeyboardCallback);

	return true;
}

void Window::EnterMainLoop(void)
{
	bool running = true;

	while (running)
	{
		// redraw();

		if (KEY_DOWN(GLFW_KEY_ESC))
			running = false;
	}
}
