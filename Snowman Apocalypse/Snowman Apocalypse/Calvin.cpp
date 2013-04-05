#include <iostream>

#include "cs455Utils.h"
#include "Window.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "World.h"
#include "Calvin.h"
#include "Snowball.h"

Calvin::Calvin(void)
{
	width = 0.6f;
	halfWidth = width / 2.0f;
	height = 0.8f;

	xVelModifier = 0.01f;
	yVelModifier = 0.0f;
	zVelModifier = 0.01f;

	maxHorizontalVel = 1.0f;
	maxVerticalVel = 8.0f;

	acceleration->x() = 0.0f;
	acceleration->y() = -World::GRAVITY;

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

	snowballs = 100;
	flameFuel = 100.0f;

	flamethrowing = false;
}

Calvin::~Calvin(void)
{

}

float Calvin::CenterX()
{
	float x = position->x();

	return x;
}

float Calvin::CenterY()
{
	float y = position->y() + height / 2.0f;

	return y;
}

float Calvin::CenterZ()
{
	float z = position->z();

	return z;
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

	if (velocity->x() > maxHorizontalVel) velocity->x() = maxHorizontalVel;
	else if (velocity->x() < -maxHorizontalVel) velocity->x() = -maxHorizontalVel;

	if (velocity->y() > maxVerticalVel) velocity->y() = maxVerticalVel;
	else if (velocity->y() < -maxVerticalVel) velocity->y() = -maxVerticalVel;

	if (velocity->z() > maxHorizontalVel) velocity->z() = maxHorizontalVel;
	else if (velocity->z() < -maxHorizontalVel) velocity->z() = -maxHorizontalVel;

	UpdateMovement(deltaTime);

	if (position->x() < World::MIN_X) position->x() = (float)World::MIN_X;
	else if (position->x() > World::MAX_X) position->x() = (float)World::MAX_X;

	if (position->y() < World::GROUND_Y)
	{
		position->y() = World::GROUND_Y;
		canJump = true;
	}

	if (position->z() < World::MIN_Z) position->z() = (float)World::MIN_Z;
	else if (position->z() > World::MAX_Z) position->z() = (float)World::MAX_Z;

	flameEmitter.SetPosition(position->x(), position->y() + 0.25f, position->z() - 0.01f);
	flameEmitter.SetVelocity(velocity->x(), velocity->y(), velocity->z());

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

	// If we're throwing flame, lose some fuel
	if (flamethrowing && flameFuel > 0.0f)
	{
		flameFuel -= 1.0f * deltaTime;
		flameEmitter.TurnOn();
	}
	else
		flameEmitter.TurnOff();

	flameEmitter.UpdateAll(deltaTime);
}

void Calvin::Render()
{	
	if (snowballsEquipped)
		glBindTexture(GL_TEXTURE_2D, calvinSnowballTexture);
	else
		glBindTexture(GL_TEXTURE_2D, calvinFlamethrowerTexture);
	
	glColor3f(1.0f, 1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(position->x(), position->y(), position->z());
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

	glPopMatrix();

	flameEmitter.RenderAll();
}

void Calvin::pollInput()
{
	targetX = MOUSE_X;
	targetY = MOUSE_Y;

	if (targetX < Window::WINDOW_WIDTH / 2)
		facingRight = false;
	else 
		facingRight = true;

	flameEmitter.SetBearing(facingRight);

	if (KEY_DOWN('W'))
		velocity->z() -= zVelModifier;
	else if (KEY_DOWN('S'))
		velocity->z() += zVelModifier;
	else
	{
		if (velocity->z() > 0.0) velocity->z() -= zVelModifier;
		else if (velocity->z() < 0.0) velocity->z() += zVelModifier;
	}

	if (KEY_DOWN('A'))
		velocity->x() -= xVelModifier;
	else if (KEY_DOWN('D'))
		velocity->x() += xVelModifier;
	else
	{
		if (velocity->x() > 0.0) velocity->x() -= xVelModifier;
		else if (velocity->x() < 0.0) velocity->x() += xVelModifier;
	}

	if (MOUSE_HIT(GLFW_MOUSE_BUTTON_2) && canJump)
	{
		velocity->y() = maxVerticalVel;
		canJump = false;
	}

	if (KEY_HIT('Q'))
	{
		snowballsEquipped = !snowballsEquipped;
	}

	if (snowballsEquipped && MOUSE_HIT(GLFW_MOUSE_BUTTON_1) && snowballs)
	{
		// Throw snowball
		Snowball::Throw(CenterX(), CenterY(), CenterZ() + 0.01f,
						6.0f * (facingRight ? 1.0f : -1.0f),
						5.0f); 
		snowballs--;
	}
	
	if (!snowballsEquipped && MOUSE_DOWN(GLFW_MOUSE_BUTTON_1))
	{
		// Activate flamethrower
		flamethrowing = true;
	}
	else
		flamethrowing = false;
}