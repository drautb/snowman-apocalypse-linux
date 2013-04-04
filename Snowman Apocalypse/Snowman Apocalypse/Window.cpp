#include <iostream>

#include <cmath>

#include <GL/glfw.h>

#include "Window.h"
#include "Camera.h"
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

	lastTime = timeElapsed = 0.0;
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
	glfwSetWindowTitle("Snowman Apocalypse");

	glClearColor(0.0f, 0.5f, 1.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	gameWorld.LoadTextures();
	calvin.LoadTextures();

	return true;
}

void Window::EnterMainLoop(void)
{
	bool running = true;
	double currentTime = 0.0;

	while (running)
	{
		currentTime = glfwGetTime();
		timeElapsed = (float)(currentTime - lastTime);
		lastTime = (float)currentTime;

		update();
		redraw();
	}
}

void Window::update()
{
	calvin.Update(timeElapsed);

	//Camera::GetInstance()->PollKeyboard();
	Camera::GetInstance()->TrackPoint(calvin.x(), 1.0f, 2.15f);
	Camera::GetInstance()->Update(timeElapsed);
}

void Window::redraw(void)
{
	//  Clear screen and Z-buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	Camera::GetInstance()->Use();
	renderEnvironment();	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(90, WINDOW_WIDTH / WINDOW_HEIGHT, 0.1, 10.0);

	glFlush();
	glfwSwapBuffers();
}

void Window::renderEnvironment(void)
{
	gameWorld.Render();
	calvin.Render();
}
