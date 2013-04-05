#pragma once

#include "cs455Utils.h"
#include "ObjectManager.h"
#include "Particle.h"

class FlameParticleEmitter : public ObjectManager<Particle>, public MovingObject
{
private:

	const static int				PARTICLE_COUNT = 600;

	float							emissionFrequency, emissionTimer;

	bool							facingRight;

	bool							on;

public:

	FlameParticleEmitter(void);
	~FlameParticleEmitter(void);

	void Update(float deltaTime){}
	void Render(){}

	void UpdateAll(float deltaTime);
	void RenderAll();

	void SetPosition(float x, float y, float z);
	void SetVelocity(float xVel, float yVel, float zVel);
	void SetBearing(bool facingRight){this->facingRight = facingRight;}

	void TurnOn(){on = true;}
	void TurnOff(){on = false;}

private:

	void emit();
};

