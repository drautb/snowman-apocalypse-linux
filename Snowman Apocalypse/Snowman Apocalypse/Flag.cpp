#include <GL\glfw.h>

#include "cs455Utils.h"
#include "Flag.h"
#include "RenderManager.h"

GLuint Flag::flagTexture = -1;

Flag::Flag(void)
{
	z = 0.0f;

	RenderManager::GetInstance()->RegisterObject(this);
}

Flag::~Flag(void)
{

}

void Flag::Render()
{
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, flagTexture);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	
	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(4.9f, 0.0f, z);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(4.9f, 1.5f, z);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(5.5f, 0.0f, z);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(5.5f, 1.5f, z);
	glEnd();
}

void Flag::LoadTextures()
{
	glGenTextures(1, &flagTexture);
	glBindTexture(GL_TEXTURE_2D, flagTexture);
	glfwLoadTexture2D("flag.tga", GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}