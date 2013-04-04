#include <iostream>

#include <GL\glfw.h>

#include "World.h"

const float World::GRAVITY = 0.05f;
const float World::MIN_X = 0.0f;
const float World::MIN_Z = 0.1f;
const float World::MAX_X = 10.0f;
const float World::MAX_Z = 0.9f;

World::World(void)
{

}

World::~World(void)
{

}

void World::Render()
{
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	
	// Render Street
	glBindTexture(GL_TEXTURE_2D, streetTexture);
	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.0f, -0.2f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.0f, -0.2f, 2.0f);
		glTexCoord2f(10.0f, 1.0f);
		glVertex3f(10.0f, -0.2f, 1.0f);
		glTexCoord2f(10.0f, 0.0f);
		glVertex3f(10.0f, -0.2f, 2.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
	glEnd();

	// Render Curbside
	glBindTexture(GL_TEXTURE_2D, sidewalkTexture);
	glBegin(GL_TRIANGLE_STRIP);
		//glColor3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.05f);
		glVertex3f(0.0f, -0.2f, 1.0f);
		glTexCoord2f(10.0f, 0.0f);
		glVertex3f(10.0f, 0.0f, 1.0f);
		glTexCoord2f(10.0f, 0.05f);
		glVertex3f(10.0f, -0.2f, 1.0f);
	glEnd();

	// Render Sidewalk
	glBegin(GL_TRIANGLE_STRIP);
		//glColor3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(10.0f, 1.0f);
		glVertex3f(10.0f, 0.0f, 0.0f);
		glTexCoord2f(10.0f, 0.0f);
		glVertex3f(10.0f, 0.0f, 1.0f);
	glEnd();

	// Render Background
	glBindTexture(GL_TEXTURE_2D, backgroundTexture);
	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.0f, 3.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(10.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(10.0f, 3.0f, 0.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void World::LoadTextures(void)
{
	glGenTextures(1, &backgroundTexture);
	glBindTexture(GL_TEXTURE_2D, backgroundTexture);
	glfwLoadTexture2D("background.tga", GLFW_BUILD_MIPMAPS_BIT);
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
}