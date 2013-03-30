#pragma once

#include <map>

#include <GL/glfw.h>

#include "Keyboard.h"
#include "cs455Utils.h"

using namespace Eigen;

void GLFWCALL ResizeCallback(int width, int height);

/**
 * Window class
 * Encapsulates all the glfw window setup for this program
 *
 * Jan. 9, 2012
 */
class Window
{
private:
	/**
	 * Class constants
	 */
	const static int WINDOW_WIDTH			= 800;
	const static int WINDOW_HEIGHT			= 480;

private:
	/**
	 * Other Members
	 */
	

public:
	/**
	 * Constructor
	 */
	Window(void);

	/**
	 * Destructor
	 */
	~Window(void);

	/**
	 * Other Methods
	 */
	bool Open(void);

	void EnterMainLoop(void);
};

