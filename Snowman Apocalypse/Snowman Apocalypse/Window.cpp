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

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	return true;
}

void Window::EnterMainLoop(void)
{
	bool running = true;
	double currentTime = 0.0;

	while (running)
	{
		currentTime = glfwGetTime();
		timeElapsed = currentTime - lastTime;
		lastTime = currentTime;

		Camera::GetInstance()->PollKeyboard();

		redraw();
	}
}

void Window::redraw(void)
{
	//  Clear screen and Z-buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(90, WINDOW_WIDTH / WINDOW_HEIGHT, 0.1, 10.0);

	Camera::GetInstance()->PollKeyboard();
	Camera::GetInstance()->Update(timeElapsed);
	Camera::GetInstance()->Use();

	renderEnvironment();

	glFlush();
	glfwSwapBuffers();
}

void Window::renderEnvironment(void)
{
	glBegin(GL_QUADS);
		glColor3f(   1.0,  1.0, 1.0 );
		glVertex3f(  0.5, -0.5, 0.5 );
		glVertex3f(  0.5,  0.5, 0.5 );
		glVertex3f( -0.5,  0.5, 0.5 );
		glVertex3f( -0.5, -0.5, 0.5 );
	glEnd();
 
	// Purple side - RIGHT
	glBegin(GL_QUADS);
		glColor3f(  1.0,  0.0,  1.0 );
		glVertex3f( 0.5, -0.5, -0.5 );
		glVertex3f( 0.5,  0.5, -0.5 );
		glVertex3f( 0.5,  0.5,  0.5 );
		glVertex3f( 0.5, -0.5,  0.5 );
	glEnd();
 
	// Green side - LEFT
	glBegin(GL_QUADS);
		glColor3f(   0.0,  1.0,  0.0 );
		glVertex3f( -0.5, -0.5,  0.5 );
		glVertex3f( -0.5,  0.5,  0.5 );
		glVertex3f( -0.5,  0.5, -0.5 );
		glVertex3f( -0.5, -0.5, -0.5 );
	glEnd();
 
	// Blue side - TOP
	glBegin(GL_QUADS);
		glColor3f(   0.0,  0.0,  1.0 );
		glVertex3f(  0.5,  0.5,  0.5 );
		glVertex3f(  0.5,  0.5, -0.5 );
		glVertex3f( -0.5,  0.5, -0.5 );
		glVertex3f( -0.5,  0.5,  0.5 );
	glEnd();
 
	// Red side - BOTTOM
	glBegin(GL_QUADS);
		glColor3f(   1.0,  0.0,  0.0 );
		glVertex3f(  0.5, -0.5, -0.5 );
		glVertex3f(  0.5, -0.5,  0.5 );
		glVertex3f( -0.5, -0.5,  0.5 );
		glVertex3f( -0.5, -0.5, -0.5 );
	glEnd();
 
}
