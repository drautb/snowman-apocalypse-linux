#pragma once

#include "cs455Utils.h"
#include "MovingObject.h"

class Particle : public MovingObject
{
public:

	bool				alive;
	
	Vector455			*color;

	float				age, lifespan;

	static GLuint		particleTexture;

public:

	Particle(void);
	~Particle(void);

	void Update(float deltaTime);

	void Render();

	static void LoadTextures(void);
};

