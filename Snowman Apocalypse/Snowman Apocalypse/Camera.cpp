#include <cmath>

#include <GL\glfw.h>

#include "Keyboard.h"
#include "Camera.h"

Camera::Camera(void)
{
	velModifier = 0.001f;
	maxVelocity = 1.5f;
	minVelocity = -1.5f;

	Zero();
}

Camera::~Camera(void)
{

}

Camera *Camera::GetInstance(void)
{
	static Camera instance;

	return &instance;
}

void Camera::Zero(void)
{
	xPos = yPos = zPos = 0.0f;
	xRot = yRot = zRot = 0.0f;
}

void Camera::PollKeyboard()
{
	if (KEY_DOWN(GLFW_KEY_LEFT))
		xPosVel -= velModifier;
	else if (KEY_DOWN(GLFW_KEY_RIGHT))
		xPosVel += velModifier;

	if (KEY_DOWN(GLFW_KEY_DOWN))
		yPosVel -= velModifier;
	else if (KEY_DOWN(GLFW_KEY_UP))
		yPosVel += velModifier;
}

void Camera::Update(float deltaTime)
{
	clampVelocities();

	xPos += xPosVel * deltaTime;
	yPos += yPosVel * deltaTime;
	zPos += zPosVel * deltaTime;

	xRot += xRotVel * deltaTime;
	yRot += yRotVel * deltaTime;
	zRot += zRotVel * deltaTime;
}

void Camera::Use(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(zRot, 0.0f, 0.0f, 1.0f);

	glTranslatef(-xPos, -yPos, -zPos);
}

void Camera::clampVelocities(void)
{
	if (xPosVel < minVelocity) xPosVel = minVelocity;
	else if (xPosVel > maxVelocity) xPosVel = maxVelocity;

	if (yPosVel < minVelocity) yPosVel = minVelocity;
	else if (yPosVel > maxVelocity) yPosVel = maxVelocity;

	if (zPosVel < minVelocity) zPosVel = minVelocity;
	else if (zPosVel > maxVelocity) zPosVel = maxVelocity;
}