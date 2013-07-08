#include <GLFW/glfw3.h>

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
	fortTexture = LoadTexture2D("textures/fort.tga"); 
}