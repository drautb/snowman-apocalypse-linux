#include <cmath>

#include <GL\glfw.h>

#include "Snowman.h"

GLuint Snowman::snowmanTexture = -1;
float Snowman::halfWidth = 0.4f;
float Snowman::halfHeight = 0.5f;

Snowman::Snowman(void)
{
	alive = false;

	MAX_HEALTH = 50.0f;
	health = MAX_HEALTH;
	healthBar = new StatusBar(0.0f, MAX_HEALTH, 0.5f, 0.07f);
	
	facingRight = true;
	
	scaleX = 1.0f;

	minScale = 0.9f;
	maxScale = 1.1f;
	scaleModifier = 0.2f;

	xVelModifier = 0.2f;
}

Snowman::~Snowman(void)
{
	SAFE_DELETE(healthBar);
}

void Snowman::Respawn()
{
	// Pick a random side
	facingRight =  (rand() % 2) > 0;

	position->y() = halfHeight;
	position->z() = (float)(((rand() % 60) + 20) / 100.0f);

	if (facingRight)
	{
		position->x() = -3.0f + ((rand() % 100) / 100.0f);	
	}
	else
	{
		position->x() = 13.0f - ((rand() % 100) / 100.0f);
	}

	health = MAX_HEALTH;
	alive = true;
}

void Snowman::Update(float deltaTime)
{
	scaleX += scaleModifier * deltaTime;
	if (scaleX > maxScale || scaleX < minScale)
		switchScaleDirection();

	velocity->x() *= (facingRight ? 1.0f : -1.0f);

	UpdateMovement(deltaTime);
	healthBar->Update(health);
}

void Snowman::Render()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(position->x(), position->y(), position->z());

	healthBar->Render(0.0f, 0.6f, 0.0f);

	glScalef(scaleX, 1.0f, 1.0f);

	glEnable(GL_BLEND);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(0, 0);
		glVertex3f(-halfWidth, -halfHeight, 0.0f);
		glTexCoord2f(1, 0);
		glVertex3f(halfWidth, -halfHeight, 0.0f);
		glTexCoord2f(0, 1);
		glVertex3f(-halfWidth, halfHeight, 0.0f);
		glTexCoord2f(1, 1);
		glVertex3f(halfWidth, halfHeight, 0.0f);
	glEnd();

	glPopMatrix();
}

void Snowman::LoadTextures()
{
	glGenTextures(1, &snowmanTexture);
	glBindTexture(GL_TEXTURE_2D, snowmanTexture);
	glfwLoadTexture2D("snowman.tga", GLFW_BUILD_MIPMAPS_BIT | GL_RGBA);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Snowman::switchScaleDirection()
{
	scaleModifier *= -1.0f;
	if (scaleModifier > 0.0f)
		velocity->x() = 0.04f;
	else
		velocity->x() = xVelModifier;
}