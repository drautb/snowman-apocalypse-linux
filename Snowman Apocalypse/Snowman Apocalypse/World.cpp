#include <iostream>

#include <GL\glfw.h>

#include "World.h"

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

	// Render Street
	glBindTexture(GL_TEXTURE_2D, streetTexture);
	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-2.0f, -0.2f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-2.0f, -0.2f, 2.0f);
		glTexCoord2f(14.0f, 1.0f);
		glVertex3f(12.0f, -0.2f, 1.0f);
		glTexCoord2f(14.0f, 0.0f);
		glVertex3f(12.0f, -0.2f, 2.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
	glEnd();

	// Render Curbside
	glBindTexture(GL_TEXTURE_2D, sidewalkTexture);
	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-3.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.05f);
		glVertex3f(-3.0f, -0.2f, 1.0f);
		glTexCoord2f(16.0f, 0.0f);
		glVertex3f(13.0f, 0.0f, 1.0f);
		glTexCoord2f(16.0f, 0.05f);
		glVertex3f(13.0f, -0.2f, 1.0f);
	glEnd();

	// Render Sidewalk
	glBegin(GL_TRIANGLE_STRIP);
		//glColor3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-3.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-3.0f, 0.0f, 1.0f);
		glTexCoord2f(16.0f, 1.0f);
		glVertex3f(13.0f, 0.0f, 0.0f);
		glTexCoord2f(16.0f, 0.0f);
		glVertex3f(13.0f, 0.0f, 1.0f);
	glEnd();

	// Render Background
	glBindTexture(GL_TEXTURE_2D, backgroundTexture);
	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-3.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-3.0f, 3.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(13.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(13.0f, 3.0f, 0.0f);
	glEnd();

	// Fort
	glBindTexture(GL_TEXTURE_2D, fortTexture);
	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(4.3f, 0.0f, 0.1f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(4.3f, 0.5f, 0.1f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(5.7f, 0.0f, 0.1f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(5.7f, 0.5f, 0.1f);
	glEnd();

	snowfall.RenderAll();
}

void World::LoadTextures(void)
{
	glGenTextures(1, &backgroundTexture);
	glBindTexture(GL_TEXTURE_2D, backgroundTexture);
	glfwLoadTexture2D("forest.tga", GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenTextures(1, &sidewalkTexture);
	glBindTexture(GL_TEXTURE_2D, sidewalkTexture);
	glfwLoadTexture2D("sidewalk.tga", GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenTextures(1, &streetTexture);
	glBindTexture(GL_TEXTURE_2D, streetTexture);
	glfwLoadTexture2D("street.tga", GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenTextures(1, &fortTexture);
	glBindTexture(GL_TEXTURE_2D, fortTexture);
	glfwLoadTexture2D("fort.tga", GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}