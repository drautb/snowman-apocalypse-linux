#pragma once

#include "cs455Utils.h"
#include "ObjectManager.h"
#include "Particle.h"

class SnowSplashEmitter : public ObjectManager<Particle>
{
private:

	const static int				PARTICLE_COUNT = 50;

public:
	SnowSplashEmitter(void);
	~SnowSplashEmitter(void);

	void UpdateAll(float deltaTime);
	void RenderAll();

	void Emit(float x, float y, float z, int count);
};

