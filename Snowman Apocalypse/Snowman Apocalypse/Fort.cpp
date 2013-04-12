#include <GL\glfw.h>

#include "cs455Utils.h"
#include "Fort.h"
#include "RenderManager.h"

GLuint Fort::fortTexture = -1;

Fort::Fort(void)
{
	z = 0.0f;

	RenderManager::GetInstance()->RegisterObject(this);
}

Fort::~Fort(void)
{

}

void Fort::Render()
{
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, fortTexture);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	
	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(4.3f, 0.0f, z);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(4.3f, 0.5f, z);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(5.7f, 0.0f, z);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(5.7f, 0.5f, z);
	glEnd();
}

void Fort::LoadTextures()
{
	glGenTextures(1, &fortTexture);
	glBindTexture(GL_TEXTURE_2D, fortTexture);
	glfwLoadTexture2D("fort.tga", GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}