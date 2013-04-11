#pragma once

#include <map>

#include <GL/glfw.h>

#include "Keyboard.h"
#include "Mouse.h"
#include "Camera.h"
#include "cs455Utils.h"

#include "World.h"
#include "Calvin.h"
#include "StatusBar.h"
#include "Snowman.h"
#include "SnowmanManager.h"
#include "SnowSplashEmitter.h"
#include "SteamEmitter.h"
#include "MessageManager.h"

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

	SnowmanManager							snowmanManager;

	SnowSplashEmitter						splashEmitter;
	SteamEmitter							steamEmitter;

	StatusBar								*flameFuelMeter;
	StatusBar								*snowballMeter;

	int										score, waveNumber;

	GLuint									waveTexture, scoreTexture;
	GLuint									numbersTexture;
	GLuint									defendMsgTexture, nextWaveMsgTexture;

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
	void updateCollisions();

	/**
	 * Rendering Methods
	 */
	void redraw();
	void renderEnvironment();
	void renderHUD();

	void loadTextures();
	
	void printNumber(int number, int x, int y, int digitWidth, int digitHeight);
	
	bool collides(float cX1, float cY1, float cZ1, float hW1, float hH1,
				  float cX2, float cY2, float cZ2, float hW2, float hH2, float zDepth);
};

