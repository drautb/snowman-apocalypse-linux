#pragma once

#include <vector>

#include <GL\glfw.h>

#include "MovingObject.h"
#include "Renderable.h"

using namespace std;

class Snowball : public MovingObject, public Renderable
{
public:

	// Static Snowball Management
	static vector<Snowball*>	SnowballManager;
	static const int			SNOWBALL_COUNT = 50;
	static int					currentSnowball;

	// One texture for all snowballs
	static GLuint				snowballTexture;

public:

	bool						alive;


public:

	Snowball(void);
	~Snowball(void);

	void Update(float deltaTime);
	void Render(void);
	bool IsAlive()const{return alive;}

	float Z()const{return position->z();}

	static void LoadTextures(void);
	static void InitManager(void);
	static void ShutdownManager(void);
	static void UpdateAll(float deltaTime);
	//static void RenderAll(void);
	static void Throw(float x, float y, float z, float xVel, float yVel);
	static int NextSnowball();
};

