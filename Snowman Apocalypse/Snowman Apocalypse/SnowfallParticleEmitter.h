#pragma once

#include "cs455Utils.h"
#include "ObjectManager.h"
#include "Particle.h"

class SnowfallParticleEmitter : public ObjectManager<Particle>, public MovingObject
{
private:

	const static int				PARTICLE_COUNT = 800;

	float							emissionFrequency, emissionTimer;

	bool							on;

public:

	SnowfallParticleEmitter(void);
	~SnowfallParticleEmitter(void);

	void Update(float deltaTime){}
	void Render(){}

	void UpdateAll(float deltaTime);
	void RenderAll();

	void SetPosition(float x, float y, float z);
	void SetVelocity(float xVel, float yVel, float zVel);

	void TurnOn(){on = true;}
	void TurnOff(){on = false;}

private:

	void emit();
};

