#include <iostream>

#include "cs455Utils.h"
#include "Window.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "World.h"
#include "Calvin.h"

Calvin::Calvin(void)
{
	width = 0.6f;
	halfWidth = width / 2.0f;
	height = 0.8f;

	xVel = 0.0f;
	xVelModifier = 0.01f;

	yVel = 0.0f;

	zVel = 0.0f;
	zVelModifier = 0.01f;

	maxHorizontalVel = 1.0f;
	maxVerticalVel = 8.0f;

	calvinTransform = new Matrix455();
	*calvinTransform = Matrix455::Identity();
	x() = 5.0f - width / 2.0f;
	y() = 0.0f;
	z() = 0.5f;

	yRot = 0.0f;
	yRotVel = 1000.0f;

	facingRightYRot = 0.0f;
	facingLeftYRot = -180.0f;

	facingRight = true;
	canJump = true;
	snowballsEquipped = true;
}

Calvin::~Calvin(void)
{
	SAFE_DELETE(calvinTransform);
}

void Calvin::LoadTextures()
{
	glGenTextures(1, &calvinSnowballTexture);
	glBindTexture(GL_TEXTURE_2D, calvinSnowballTexture);
	glfwLoadTexture2D("calvin-snowball.tga", GLFW_BUILD_MIPMAPS_BIT | GL_RGBA);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenTextures(1, &calvinFlamethrowerTexture);
	glBindTexture(GL_TEXTURE_2D, calvinFlamethrowerTexture);
	glfwLoadTexture2D("calvin-flamethrower.tga", GLFW_BUILD_MIPMAPS_BIT | GL_RGBA);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Calvin::Update(float deltaTime)
{
	pollInput();

	if (xVel > maxHorizontalVel) xVel = maxHorizontalVel;
	else if (xVel < -maxHorizontalVel) xVel = -maxHorizontalVel;

	yVel -= World::GRAVITY;
	if (yVel > maxVerticalVel) yVel = maxVerticalVel;
	else if (yVel < -maxVerticalVel) yVel = -maxVerticalVel;

	if (zVel > maxHorizontalVel) zVel = maxHorizontalVel;
	else if (zVel < -maxHorizontalVel) zVel = -maxHorizontalVel;

	calvinTransform->x() += xVel * deltaTime;
	calvinTransform->z() += zVel * deltaTime;
	calvinTransform->y() += yVel * deltaTime;

	if (calvinTransform->x() < World::MIN_X) calvinTransform->x() = (float)World::MIN_X;
	else if (calvinTransform->x() > World::MAX_X) calvinTransform->x() = (float)World::MAX_X;

	if (calvinTransform->y() < World::GROUND_Y)
	{
		calvinTransform->y() = World::GROUND_Y;
		canJump = true;
	}

	if (calvinTransform->z() < World::MIN_Z) calvinTransform->z() = (float)World::MIN_Z;
	else if (calvinTransform->z() > World::MAX_Z) calvinTransform->z() = (float)World::MAX_Z;

	// Rotation Stuff
	if (facingRight)
	{
		if (yRot != facingRightYRot)
		{
			yRot += yRotVel * deltaTime;
			if (yRot > facingRightYRot)
				yRot = facingRightYRot;
		}
	}
	else if (!facingRight)
	{
		if (yRot != facingLeftYRot)
		{
			yRot -= yRotVel * deltaTime;
			if (yRot < facingLeftYRot)
				yRot = facingLeftYRot;
		}
	}
}

void Calvin::Render()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	if (snowballsEquipped)
		glBindTexture(GL_TEXTURE_2D, calvinSnowballTexture);
	else
		glBindTexture(GL_TEXTURE_2D, calvinFlamethrowerTexture);
	
	glColor3f(1.0f, 1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glTranslatef(calvinTransform->x(), calvinTransform->y(), calvinTransform->z());
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	
	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-halfWidth, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(halfWidth, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-halfWidth, height, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(halfWidth, height, 0.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void Calvin::pollInput()
{
	targetX = MOUSE_X;
	targetY = MOUSE_Y;

	if (targetX < Window::WINDOW_WIDTH / 2)
		facingRight = false;
	else 
		facingRight = true;

	if (KEY_DOWN('W'))
		zVel -= zVelModifier;
	else if (KEY_DOWN('S'))
		zVel += zVelModifier;
	else
	{
		if (zVel > 0.0) zVel -= zVelModifier;
		else if (zVel < 0.0) zVel += zVelModifier;
	}

	if (KEY_DOWN('A'))
		xVel -= xVelModifier;
	else if (KEY_DOWN('D'))
		xVel += xVelModifier;
	else
	{
		if (xVel > 0.0) xVel -= xVelModifier;
		else if (xVel < 0.0) xVel += xVelModifier;
	}

	if (MOUSE_HIT(GLFW_MOUSE_BUTTON_2) && canJump)
	{
		yVel = maxVerticalVel;
		canJump = false;
	}

	if (KEY_HIT('Q'))
	{
		snowballsEquipped = !snowballsEquipped;
	}

	if (snowballsEquipped && MOUSE_HIT(GLFW_MOUSE_BUTTON_1))
	{
		// Throw snowball

	}
	
	if (!snowballsEquipped && MOUSE_DOWN(GLFW_MOUSE_BUTTON_1))
	{
		// Activate FlameThrower

	}
}