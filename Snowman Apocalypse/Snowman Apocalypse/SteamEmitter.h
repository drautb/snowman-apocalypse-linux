#pragma once

#include "cs455Utils.h"
#include "ObjectManager.h"
#include "Particle.h"

class SteamEmitter : public ObjectManager<Particle>
{
private:

	const static int				PARTICLE_COUNT = 1000;

public:
	SteamEmitter(void);
	~SteamEmitter(void);

	void UpdateAll(float deltaTime);
	void RenderAll();

	void Emit(float x, float y, float z, int count);
};
