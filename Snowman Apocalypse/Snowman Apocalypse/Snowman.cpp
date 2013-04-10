#include <iostream>
#include <cmath>

#include <GL\glfw.h>

#include "Snowman.h"

GLuint Snowman::snowmanTexture = -1;
float Snowman::halfWidth = 0.45f;
float Snowman::halfHeight = 0.7f;
float Snowman::SNOWBALL_DAMAGE_FACTOR = 7.0f;

Snowman::Snowman(void)
{
	alive = false;

	MAX_HEALTH = 50.0f;
	health = MAX_HEALTH;
	healthBar = new StatusBar(0.0f, MAX_HEALTH, 0.5f, 0.06f);
	
	facingRight = true;
	
	scaleX = 1.0f;

	minScale = 0.9f;
	maxScale = 1.1f;
	scaleModifier = 0.2f;

	xVelModifier = 0.1f + (rand() % 100) / 500.0f;
}

Snowman::~Snowman(void)
{
	SAFE_DELETE(healthBar);
}

void Snowman::Respawn()
{
	*velocity = Vector455::Zero();
	*acceleration = Vector455::Zero();

	// Pick a random side
	facingRight = (rand() % 100) < 49;

	position->y() = halfHeight;
	position->z() = (float)(((rand() % 80) + 10) / 100.0f);

	xVelModifier = 0.1f + (rand() % 100) / 500.0f;

	if (facingRight)
	{
		position->x() = -2.0f + ((rand() % 100) / 100.0f);	
		velocity->x() = xVelModifier;
	}
	else
	{
		position->x() = 12.0f - ((rand() % 100) / 100.0f);
		velocity->x() = -xVelModifier;
	}

	health = MAX_HEALTH;
	alive = true;
}

void Snowman::Update(float deltaTime)
{
	if (health == 0.0f)
		alive = false;

	if (!alive)
		return;

	scaleX += scaleModifier * deltaTime;
	if (scaleX > maxScale || scaleX < minScale)
		switchScaleDirection();

	UpdateMovement(deltaTime);
	healthBar->Update(health);
}

void Snowman::Render()
{
	if (!alive)
		return;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(position->x(), position->y() - halfHeight, position->z());	

	glScalef(scaleX, 1.0f, 1.0f);

	float xVal = (facingRight ? 1.0f : -1.0f);

	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(0, 0);
		glVertex3f(-halfWidth, 0.0f, 0.0f);
		glTexCoord2f(xVal, 0);
		glVertex3f(halfWidth, 0, 0.0f);
		glTexCoord2f(0, 1);
		glVertex3f(-halfWidth, 2*halfHeight, 0.0f);
		glTexCoord2f(xVal, 1);
		glVertex3f(halfWidth, 2*halfHeight, 0.0f);
	glEnd();

	glPopMatrix();
}

void Snowman::RenderHealthBar()
{
	if (!alive)
		return;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(position->x(), position->y(), position->z());

	healthBar->Render(0.0f, 0.8f, 0.0f);

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

void Snowman::HitWithSnowball()
{
	health -= SNOWBALL_DAMAGE_FACTOR;

	clampHealth();
}

void Snowman::switchScaleDirection()
{
	scaleModifier *= -1.0f;
	if (scaleModifier > 0.0f)
		velocity->x() = (facingRight ? 0.05f : -0.05f);
	else
		velocity->x() = (facingRight ? xVelModifier : -xVelModifier);
}

void Snowman::clampHealth()
{
	if (health < 0.0f)
		health = 0.0f;
	else if (health > MAX_HEALTH)
		health = MAX_HEALTH;
}