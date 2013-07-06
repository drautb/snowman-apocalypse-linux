#include <iostream>

#include "cs455Utils.h"
#include "Window.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "World.h"
#include "Calvin.h"
#include "Snowball.h"
#include "MessageManager.h"
#include "Window.h"
#include "RenderManager.h"

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

	flameChargeFactor = 10.0f;

	Reset();

	RenderManager::GetInstance()->RegisterObject(this);
}

Calvin::~Calvin(void)
{

}

void Calvin::Reset()
{
	x() = 5.0f - width / 2.0f;
	y() = 0.0f;
	z() = 0.6f;

	yRot = 0.0f;
	yRotVel = 1000.0f;

	facingRightYRot = 0.0f;
	facingLeftYRot = -180.0f;

	facingRight = true;
	canJump = true;
	snowballsEquipped = true;

	snowballs = maxSnowballs = 50.0f;
	flameFuel = maxFlameFuel = 100.0f;

	flamethrowing = false;
}

float Calvin::CenterX()const
{
	float x = position->x();

	return x;
}

float Calvin::CenterY()const
{
	float y = position->y() + height / 2.0f;

	return y;
}

float Calvin::CenterZ()const
{
	float z = position->z();

	return z;
}

void Calvin::LoadTextures()
{
	calvinSnowballTexture = LoadTexture2D("textures/calvin-snowball.tga");

	calvinFlamethrowerTexture = LoadTexture2D("textures/calvin-flamethrower.tga");
	
	overheatedMsgTexture = LoadTexture2D("textures/overheated.tga");
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
	if (flamethrowing && flameFuel > 0.0f && (yRot == facingLeftYRot || yRot == facingRightYRot))
	{
		flameFuel -= 2 * flameChargeFactor * deltaTime;
		flameEmitter.TurnOn();
	}
	else if (flamethrowing && flameFuel < 0.0f)
	{
		// Holding button, but no fuel
		flameFuel -= flameChargeFactor * deltaTime;
		flameEmitter.TurnOff();
	}
	else
	{
		flameEmitter.TurnOff();
		flameFuel += flameChargeFactor * deltaTime;
	}

	flameEmitter.UpdateAll(deltaTime);

	clampSnowballs();
	clampFlameFuel();
}

void Calvin::Render()
{	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

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

	if (MOUSE_HIT(GLFW_MOUSE_BUTTON_1) && flameFuel < 0.0f)
		MessageManager::GetInstance()->AddMessage(250, 300, 300, 50, overheatedMsgTexture, 3.0f);
}

void Calvin::HitSnowmanWithSnowball()
{
	snowballs += 1.2f;
}

void Calvin::clampSnowballs()
{
	if (snowballs < 0.0f)
		snowballs = 0.0f;
	else if (snowballs > maxSnowballs)
		snowballs = maxSnowballs;
}

void Calvin::clampFlameFuel()
{
	if (flameFuel > maxFlameFuel)
		flameFuel = maxFlameFuel;
}