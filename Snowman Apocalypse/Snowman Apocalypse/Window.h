#pragma once

#include <map>

#include <GL/glfw.h>

#include "Keyboard.h"
#include "Camera.h"
#include "cs455Utils.h"

#include "World.h"
#include "Calvin.h"

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
public:
	/**
	 * Class constants
	 */
	const static int WINDOW_WIDTH			= 800;
	const static int WINDOW_HEIGHT			= 600;

private:

	/**
	 * Other Members
	 */
	float									lastTime, timeElapsed;

	World									gameWorld;
	Calvin									calvin;

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

private: 

	void update();

	/**
	 * Rendering Methods
	 */
	void redraw();
	void renderEnvironment();
};

