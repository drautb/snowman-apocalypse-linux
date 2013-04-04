#pragma once

#include <vector>

#include <GL\glfw.h>

#include "MovingObject.h"

using namespace std;

class Snowball : public MovingObject
{
public:

	// Static Snowball Management
	static vector<Snowball*>	SnowballManager;
	static const int			SNOWBALL_COUNT = 50;
	static int					currentSnowball;

	// One texture for all snowballs
	static GLuint				snowballTexture;

private:

	bool						alive;


public:

	Snowball(void);
	~Snowball(void);

	void Update(float deltaTime);
	void Render(void);

	static void LoadTextures(void);
	static void InitManager(void);
	static void ShutdownManager(void);
	static void UpdateAll(float deltaTime);
	static void RenderAll(void);
	static void Throw(float x, float y, float z, float xVel, float yVel);
	static int NextSnowball();
};

