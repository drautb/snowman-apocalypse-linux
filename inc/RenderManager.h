#pragma once

#include <vector>
#include <string>
#include <GLFW/glfw3.h>

#include "Renderable.h"

using namespace std;

bool sortPredicate(const Renderable *lhs, const Renderable *rhs);

GLuint LoadTexture2D(const char* filename);

class RenderManager
{
private:

	vector<Renderable*>			objectsToRender;

private:
	RenderManager(void); // Singleton

public:
	
	~RenderManager(void);

	static RenderManager *GetInstance();

	void RegisterObject(Renderable *obj);
	void RenderAll();

private:
};

