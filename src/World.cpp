#include <iostream>

#include <GLFW/glfw3.h>

#include "World.h"
#include "RenderManager.h"

const float World::GRAVITY = 25.0f;
const float World::MIN_X = 0.0f;
const float World::MIN_Z = 0.1f;
const float World::MAX_X = 10.0f;
const float World::MAX_Z = 0.9f;

World::World(void)
{
	snowfall.TurnOn();
}

World::~World(void)
{

}

void World::Update(float deltaTime)
{
	snowfall.UpdateAll(deltaTime);
}

void World::Render()
{
	glMatrixMode(GL_MODELVIEW);
	glColor3f(1.0f, 1.0f, 1.0f);

	// Ground
	glBindTexture(GL_TEXTURE_2D, groundTexture);
	glBegin(GL_TRIANGLE_STRIP);
		//glColor3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 4.0f);
		glVertex3f(-3.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-3.0f, 0.0f, 3.0f);
		glTexCoord2f(16.0f, 4.0f);
		glVertex3f(13.0f, 0.0f, 0.0f);
		glTexCoord2f(16.0f, 0.0f);
		glVertex3f(13.0f, 0.0f, 3.0f);
	glEnd();
	
	// Render Background
	glBindTexture(GL_TEXTURE_2D, backgroundTexture);
	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-3.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-3.0f, 6.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(13.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(13.0f, 6.0f, 0.0f);
	glEnd();

	snowfall.RenderAll();
}

void World::LoadTextures(void)
{
	backgroundTexture = LoadTexture2D("textures/forest.tga");

	groundTexture = LoadTexture2D("textures/ground.tga");
}