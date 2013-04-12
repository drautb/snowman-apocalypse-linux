#pragma once

#include <GL/glfw.h>

#include "SnowfallParticleEmitter.h"

class World
{
public:

	const static int			GROUND_Y	= 0;
	const static float			GRAVITY;	
	const static float			MIN_X;
	const static float			MIN_Z;
	const static float			MAX_X;
	const static float			MAX_Z;

private:

	GLuint				backgroundTexture;
	GLuint				sidewalkTexture;
	GLuint				streetTexture;

	SnowfallParticleEmitter		snowfall;

public:

	World(void);
	~World(void);

	void LoadTextures(void);
	void Update(float deltaTime);
	void Render();

private:

};