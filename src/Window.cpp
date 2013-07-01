#include <iostream>
#include <string>
#include <cmath>

#include <GL/glfw.h>
// #include <fmod.hpp>

#include "Window.h"
#include "Camera.h"
#include "cs455Utils.h"
#include "Snowball.h"
#include "Particle.h"
#include "Flag.h"

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
	glfwSwapInterval(0);

	// FMOD::System_Create(&fmod);
	// fmod->init(32, FMOD_INIT_NORMAL, 0);
	// fmod->createSound("audio/music.mp3", FMOD_LOOP_NORMAL, 0, &music);
	// music->setLoopCount(-1);
	// fmod->playSound(music, 0, false, &musicChannel); 
	// musicChannel->setVolume(0.4f);

	// fmod->createSound("audio/alarm.wav", FMOD_LOOP_NORMAL, 0, &alarm);
	// alarm->setLoopCount(-1);
	// fmod->playSound(alarm, 0, true, &alarmChannel);

	// fmod->createSound("audio/impact.wav", FMOD_DEFAULT, 0, &impact);

	// fmod->createSound("audio/brains.wav", FMOD_DEFAULT, 0, &brains);

	// fmod->createSound("audio/pain.wav", FMOD_DEFAULT, 0, &pain);

	// fmod->createSound("audio/flamethrower.wav", FMOD_LOOP_NORMAL, 0, &flamethrower);
	// flamethrower->setLoopCount(-1);
	// fmod->playSound(flamethrower, 0, true, &flamethrowerChannel);

	lastTime = timeElapsed = 0.0;

	flameFuelMeter = new StatusBar(0.0f, calvin.MaxFlameFuel(), 100.0f, 12.0f);
	snowballMeter = new StatusBar(0.0f, (float)calvin.MaxSnowballs(), 100.0f, 12.0f);

	frontFort.z = 0.09f;
	backFort.z = 0.91f;

	flag.z = 0.5f;

	resetGame();
}

Window::~Window(void)
{
	// music->release();
	// alarm->release();
	// impact->release();
	// flamethrower->release();
	// pain->release();
	// brains->release();
	// fmod->release();

	Snowball::ShutdownManager();

	SAFE_DELETE(flameFuelMeter);
	SAFE_DELETE(snowballMeter);

	// Close window and terminate GLFW
	glfwTerminate();
}

bool Window::Open(void)
{
	if (!glfwOpenWindow(WINDOW_WIDTH, WINDOW_HEIGHT, 8, 8, 8, 8, 1, 0, GLFW_WINDOW))
		return false;

	glfwSetWindowSizeCallback(ResizeCallback);
	glfwSetKeyCallback(KeyboardCallback);
	glfwSetMousePosCallback(MousePosCallback);
	glfwSetMouseButtonCallback(MouseButtonCallback);
	glfwSetWindowTitle("Snowman Apocalypse");

	glClearColor(0.0f, 0.5f, 1.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);

	loadTextures();

	gameWorld.LoadTextures();
	calvin.LoadTextures();
	Snowball::LoadTextures();
	Snowball::InitManager();
	Particle::LoadTextures();
	Snowman::LoadTextures();
	Fort::LoadTextures();
	Flag::LoadTextures();


	return true;
}

void Window::EnterMainLoop(void)
{
	bool running = true;
	double currentTime = 0.0;

	MessageManager::GetInstance()->AddMessage(100, 440, 600, 60, defendMsgTexture, 10.0f);

	while (running)
	{
		if (KEY_HIT(GLFW_KEY_ESC))
			running = false;

		if (gameOver && KEY_HIT(GLFW_KEY_SPACE))
			resetGame();

		currentTime = glfwGetTime();
		timeElapsed = (float)(currentTime - lastTime);
		lastTime = (float)currentTime;

		update();
		redraw();
		renderHUD();

		// fmod->update();

		glFlush();
		glfwSwapBuffers();
	}
}

void Window::resetGame()
{
	score = 0;
	waveNumber = 0;

	calvin.Reset();
	snowmanManager.Reset();
	MessageManager::GetInstance()->Reset();

	gameOver = false;
}

void Window::update()
{
	if (snowmanManager.AllDead())
	{
		snowmanManager.NextWave(waveNumber++);
		MessageManager::GetInstance()->AddMessage(200, 100, 400, 60, nextWaveMsgTexture, 5.0f);
		// fmod->playSound(brains, 0, false, &brainsChannel);
	}

	updateCollisions();

	if (gameOver)	// Gameplay freezes at Game over!
	{
		timeElapsed = 0.0f;
		// alarmChannel->setPaused(true);
	}

	gameWorld.Update(timeElapsed);

	calvin.Update(timeElapsed);
	flameFuelMeter->Update(calvin.FlameFuel());
	snowballMeter->Update((float)calvin.Snowballs());

	Snowball::UpdateAll(timeElapsed);
	
	snowmanManager.UpdateAll(timeElapsed);

	splashEmitter.UpdateAll(timeElapsed);
	steamEmitter.UpdateAll(timeElapsed);

	MessageManager::GetInstance()->UpdateAll(timeElapsed);

	//Camera::GetInstance()->PollKeyboard();
	Camera::GetInstance()->TrackPoint(calvin.x(), 1.3f, 2.5f);
	Camera::GetInstance()->Update(timeElapsed);
}

void Window::updateCollisions()
{
	if (calvin.CenterX() > 4.8f && calvin.CenterX() < 5.2f &&
		calvin.CenterZ() > 0.45f && calvin.CenterZ() < 0.55f)
		calvin.FillSnowballs();

	for (int i=0; i<Snowball::SNOWBALL_COUNT; i++)
	{
		Snowball *s = Snowball::SnowballManager[i];

		if (!s->IsAlive())
			continue;

		// Check against snowmen
		for (int m=0; m<SnowmanManager::SNOWMAN_COUNT; m++)
		{
			Snowman *snowman = snowmanManager.objects[m];

			if (!snowman->IsAlive())
				continue;

			if (collides(s->position->x(), s->position->y(), s->position->z(), 0.1f, 0.1f,
				snowman->position->x(), snowman->position->y(), snowman->position->z(), snowman->halfWidth, snowman->halfHeight,
				0.1f))
			{
				s->alive = false;
				splashEmitter.Emit(s->position->x(), s->position->y(), s->position->z(), 10);
				if (snowman->HitWithSnowball())
				{
					score++;
					// fmod->playSound(pain, 0, false, &painChannel);
				}
				calvin.HitSnowmanWithSnowball();
				// fmod->playSound(impact, 0, false, &impactChannel);
				// impactChannel->setVolume(2.0f);
			}
		}

		// Check for ground boundary
		if (s->IsAlive() && s->position->y() < World::GROUND_Y)
		{
			s->alive = false;
			splashEmitter.Emit(s->position->x(), s->position->y(), s->position->z(), 10);
			// fmod->playSound(impact, 0, false, &impactChannel);
			// impactChannel->setVolume(2.0f);
		}
	}

	if (calvin.IsFlamethrowing())
	{
		// flamethrowerChannel->setPaused(false);

		float flameBoxX = calvin.CenterX() + (calvin.IsFacingRight() ? 0.8f : -0.8f);
		float flameBoxY = calvin.CenterY();
		float flameBoxZ = calvin.CenterZ();
		float flameBoxHW = 0.8f;
		float flameBoxHH = 0.4f;

		// Check against snowmen
		for (int m=0; m<SnowmanManager::SNOWMAN_COUNT; m++)
		{
			Snowman *snowman = snowmanManager.objects[m];

			if (!snowman->IsAlive())
				continue;

			if (collides(flameBoxX, flameBoxY, flameBoxZ, flameBoxHW, flameBoxHH,
				snowman->position->x(), snowman->position->y(), snowman->position->z(), snowman->halfWidth, snowman->halfHeight,
				0.2f))
			{
				if (snowman->HitWithFlame(timeElapsed))
				{
					score++;
					// fmod->playSound(pain, 0, false, &painChannel);
				}

				steamEmitter.Emit(snowman->x(), snowman->y(), snowman->z(), 1);
			}
		}
	}
	else
		// flamethrowerChannel->setPaused(true);

	// Check for game over!
	// alarmChannel->setPaused(true);
	for (int m=0; m<SnowmanManager::SNOWMAN_COUNT; m++)
	{
		Snowman *snowman = snowmanManager.objects[m];

		if (!snowman->IsAlive())
			continue;

		if (abs(snowman->x() - 5.0f) < 1.5f)
			// alarmChannel->setPaused(false);

		if (abs(snowman->x() - 5.0f) < 0.01f)
		{
			gameOver = true;
			Camera::GetInstance()->SetX(5.0f);
			MessageManager::GetInstance()->AddMessage(100, 200, 600, 200, gameOverMsgTexture, 10.0f);

			return;
		}
	}
}

void Window::redraw(void)
{
	//  Clear screen and Z-buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Camera::GetInstance()->Use();
	renderEnvironment();	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(90, WINDOW_WIDTH / WINDOW_HEIGHT, 0.1, 10.0);

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void Window::renderEnvironment(void)
{
	gameWorld.Render();

	RenderManager::GetInstance()->RenderAll();

	splashEmitter.RenderAll();
	steamEmitter.RenderAll();
}

void Window::renderHUD(void)
{
	// Set up orthographic rendering...
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	// Draw Snowball and flamethrower meters
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, calvin.calvinFlamethrowerTexture);
	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2i(0, 1);
		glVertex2i(10, 10);
		glTexCoord2i(1, 1);
		glVertex2i(40, 10);
		glTexCoord2i(0, 0);
		glVertex2i(10, 40);
		glTexCoord2i(1, 0);
		glVertex2i(40, 40);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, calvin.calvinSnowballTexture);
	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2i(0, 1);
		glVertex2i(10, 50);
		glTexCoord2i(1, 1);
		glVertex2i(40, 50);
		glTexCoord2i(0, 0);
		glVertex2i(10, 80);
		glTexCoord2i(1, 0);
		glVertex2i(40, 80);
	glEnd();

	flameFuelMeter->Render(100, 25, 0);
	snowballMeter->Render(100, 65, 0);
	
	// Draw entities on radar
	glPointSize(5.0f);
	glBegin(GL_POINTS);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2i(560 + (int)((calvin.x() / World::MAX_X) * 200), 10 + (int)((calvin.z() / World::MAX_Z) * 50));
		glColor3f(1.0f, 0.0f, 0.0f);
		snowmanManager.RenderBlips(560, 10, 200, 50);
		
		// Flag
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2i(660, 35);

	glEnd();

	// Draw radar box
	glEnable(GL_BLEND);
	glBegin(GL_TRIANGLE_STRIP);
		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
		glVertex2i(560, 10);
		glVertex2i(760, 10);
		glVertex2i(560, 60);
		glVertex2i(760, 60);
	glEnd();

	// Draw score and wave number
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, waveTexture);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2i(0, 1);
		glVertex2i(10, 520);
		glTexCoord2i(1, 1);
		glVertex2i(130, 520);
		glTexCoord2i(0, 0);
		glVertex2i(10, 550);
		glTexCoord2i(1, 0);
		glVertex2i(130, 550);
	glEnd();

	printNumber(waveNumber, 140, 520, 20, 30);

	glBindTexture(GL_TEXTURE_2D, scoreTexture);
	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2i(0, 1);
		glVertex2i(10, 560);
		glTexCoord2i(1, 1);
		glVertex2i(130, 560);
		glTexCoord2i(0, 0);
		glVertex2i(10, 590);
		glTexCoord2i(1, 0);
		glVertex2i(130, 590);
	glEnd();

	printNumber(score, 140, 560, 20, 30);

	MessageManager::GetInstance()->RenderAll();

	glDisable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}

void Window::loadTextures()
{
	glGenTextures(1, &waveTexture);
	glBindTexture(GL_TEXTURE_2D, waveTexture);
	glfwLoadTexture2D("textures/wave.tga", GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenTextures(1, &scoreTexture);
	glBindTexture(GL_TEXTURE_2D, scoreTexture);
	glfwLoadTexture2D("textures/score.tga", GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenTextures(1, &numbersTexture);
	glBindTexture(GL_TEXTURE_2D, numbersTexture);
	glfwLoadTexture2D("textures/numbers.tga", GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenTextures(1, &defendMsgTexture);
	glBindTexture(GL_TEXTURE_2D, defendMsgTexture);
	glfwLoadTexture2D("textures/defend.tga", GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenTextures(1, &nextWaveMsgTexture);
	glBindTexture(GL_TEXTURE_2D, nextWaveMsgTexture);
	glfwLoadTexture2D("textures/nextwave.tga", GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenTextures(1, &gameOverMsgTexture);
	glBindTexture(GL_TEXTURE_2D, gameOverMsgTexture);
	glfwLoadTexture2D("textures/gameover.tga", GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Window::printNumber(int number, int x, int y, int digitWidth, int digitHeight)
{
	std::string s = std::to_string(number);
	int asciiCode, offset;

	float textureDigitWidth = 0.1f;	// Each digit in the texture is 1/10 of the whole width.

	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, numbersTexture);

	for (unsigned int i=0; i<s.length(); i++)
	{
		asciiCode = (int)s[i];
		offset = asciiCode - 48; // 48 is the ascii code for '0'

		glBegin(GL_TRIANGLE_STRIP);
		
			// Top Left
			glTexCoord2f(offset * textureDigitWidth, 1.0f);
			glVertex2i(x + (i * digitWidth), y);

			// Top Right
			glTexCoord2f(offset * textureDigitWidth + textureDigitWidth, 1.0f);
			glVertex2i(x + ((i + 1) * digitWidth), y);

			// Bottom Left
			glTexCoord2f(offset * textureDigitWidth, 0.0f);
			glVertex2i(x + (i * digitWidth), y + digitHeight);

			// Bottom Right
			glTexCoord2f(offset * textureDigitWidth + textureDigitWidth, 0.0f);
			glVertex2i(x + ((i + 1) * digitWidth), y + digitHeight);			

		glEnd();
	}
}

bool Window::collides(float cX1, float cY1, float cZ1, float hW1, float hH1,
					  float cX2, float cY2, float cZ2, float hW2, float hH2, float zDepth)
{
	// Make sure that they're close enough in Z...
	if (abs(cZ2 - cZ1) > zDepth)
		return false;

	if (cX1 + hW1 < cX2 - hW2) return false; // a is left of b
    if (cX1 - hW1 > cX2 + hW2) return false; // a is right of b
    if (cY1 + hH1 < cY2 - hH2) return false; // a is above b
    if (cY1 - hH1 > cY2 + hH2) return false; // a is below b

    return true; // boxes overlap
}