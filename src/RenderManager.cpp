#include <list>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include <GLFW/glfw3.h>

#include "RenderManager.h"
#include "Renderable.h"

using namespace std;

bool sortPredicate(const Renderable *lhs, const Renderable *rhs)
{
	return lhs->Z() < rhs->Z();
}

GLuint LoadTexture2D(const char* filename)
{
	GLuint textureID = 0;
	ILuint ilTexId = 0;

	ilGenImages(1, &ilTexId);
	ilBindImage(ilTexId);
	if (ilLoadImage((const ILstring)filename))
	{
		if (ilConvertImage(IL_BGRA, IL_UNSIGNED_BYTE))
		{
			glGenTextures(1, &textureID);
			glBindTexture(GL_TEXTURE_2D, textureID);
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /* We will use linear interpolation for magnification filter */
   			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /* We will use linear interpolation for minifying filter */
   			
   			glTexImage2D(GL_TEXTURE_2D, 
   						 0, 
   						 ilGetInteger(IL_IMAGE_BPP), 
   						 ilGetInteger(IL_IMAGE_WIDTH),
     					 ilGetInteger(IL_IMAGE_HEIGHT), 
     					 0, 
     					 ilGetInteger(IL_IMAGE_FORMAT), 
     					 GL_UNSIGNED_BYTE, 
     					 ilGetData()); /* Texture specification */
		}
	}

	ilDeleteImages(1, &ilTexId);

	return textureID;
}

RenderManager::RenderManager(void)
{
	objectsToRender.clear();
}

RenderManager::~RenderManager(void)
{

}

RenderManager *RenderManager::GetInstance()
{
	static RenderManager instance;

	return &instance;
}

void RenderManager::RegisterObject(Renderable *obj)
{
	objectsToRender.push_back(obj);
}

void RenderManager::RenderAll()
{
	sort(objectsToRender.begin(), objectsToRender.end(), sortPredicate);

	for (vector<Renderable*>::const_iterator iter = objectsToRender.begin();
		iter != objectsToRender.end(); ++iter)
	{
		(*iter)->Render();
	}
}

