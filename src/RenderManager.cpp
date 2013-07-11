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
	char* file = (char*)malloc(strlen(filename) + 1);
	strcpy(file, filename);
	GLuint textureID = ilutGLLoadImage(file);
	free(file);

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

