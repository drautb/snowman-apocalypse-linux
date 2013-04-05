#pragma once

#include "cs455Utils.h"
#include "MovingObject.h"

class Particle : public MovingObject
{
public:

	bool				alive;
	
	Vector455			*color;
	Vector455			*colorDecay;

	float				age, lifespan;
	
	float				halfSize;

	static GLuint		particleTexture;

public:

	Particle(void);
	~Particle(void);

	void Update(float deltaTime);

	void Render();

	static void LoadTextures(void);
};

