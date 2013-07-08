#include <iostream>
#include <set>
#include <cmath>

#include <GLFW/glfw3.h>

#include "Snowman.h"
#include "RenderManager.h"

GLuint Snowman::snowmanTexture = -1;
float Snowman::halfWidth = 0.45f;
float Snowman::halfHeight = 0.7f;
float Snowman::SNOWBALL_DAMAGE_FACTOR = 10.0f;
float Snowman::FLAME_DAMAGE_FACTOR = 30.0f;

Snowman::Snowman(void)
{
	alive = false;

	MAX_HEALTH = 50.0f;
	health = MAX_HEALTH;
	healthBar = new StatusBar(0.0f, MAX_HEALTH, 0.5f, 0.04f);
	
	facingRight = true;
	
	scaleX = scaleY = 1.0f;

	minScale = 0.9f;
	maxScale = 1.1f;
	scaleModifier = 0.2f;
	meltModifier = 1.5f;

	xVelModifier = 0.1f + (rand() % 100) / 500.0f;

	RenderManager::GetInstance()->RegisterObject(this);
}

Snowman::~Snowman(void)
{
	SAFE_DELETE(healthBar);
}

void Snowman::Respawn(set<float> *zValues)
{
	*velocity = Vector455::Zero();
	*acceleration = Vector455::Zero();

	scaleX = scaleY = 1.0f;

	// Pick a random side
	facingRight = (rand() % 100) < 49;

	position->y() = halfHeight;
	
	float z = (float)(((rand() % 80) + 10) / 100.0f);
	while (zValues->find(z) != zValues->end())
		z = (float)(((rand() % 80) + 10) / 100.0f);
	position->z() = z;

	xVelModifier = 0.1f + (rand() % 100) / 500.0f;

	if (facingRight)
	{
		position->x() = -3.0f + ((rand() % 100) / 100.0f);	
		velocity->x() = xVelModifier;
	}
	else
	{
		position->x() = 13.0f - ((rand() % 100) / 100.0f);
		velocity->x() = -xVelModifier;
	}

	health = MAX_HEALTH;
	melting = false;
	alive = true;
}

void Snowman::Update(float deltaTime)
{
	if (health == 0.0f)
		melting = true;

	if (scaleY <= 0.0f)
		alive = false;

	if (!alive)
		return;

	if (melting)
	{
		scaleY -= meltModifier * deltaTime;
		return;
	}

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

	glScalef(scaleX, scaleY, 1.0f);

	float xVal = (facingRight ? 1.0f : -1.0f);

	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, Snowman::snowmanTexture);

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

	RenderHealthBar();
}

void Snowman::RenderHealthBar()
{
	if (!alive || melting)
		return;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(position->x(), position->y(), position->z());

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	healthBar->Render(0.0f, 0.8f, 0.0f);

	glPopMatrix();
}

void Snowman::LoadTextures()
{
	snowmanTexture = LoadTexture2D("textures/snowman.tga");
}

bool Snowman::HitWithSnowball()
{
	health -= SNOWBALL_DAMAGE_FACTOR;

	clampHealth();

	if (health == 0.0f)
		return true;

	return false;
}

bool Snowman::HitWithFlame(float deltaTime)
{
	health -= FLAME_DAMAGE_FACTOR * deltaTime;
	
	clampHealth();

	if (health == 0.0f)
		return true;

	return false;
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