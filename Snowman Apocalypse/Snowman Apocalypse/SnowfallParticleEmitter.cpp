#include <cmath>

#include "SnowfallParticleEmitter.h"

SnowfallParticleEmitter::SnowfallParticleEmitter(void)
{
	position = new Vector455();

	emissionTimer = 0.0f;
	emissionFrequency = 0.005f;

	Initialize(PARTICLE_COUNT);
}

SnowfallParticleEmitter::~SnowfallParticleEmitter(void)
{
	SAFE_DELETE(position);
}

void SnowfallParticleEmitter::UpdateAll(float deltaTime)
{
	emissionTimer += deltaTime;
	if (emissionTimer > emissionFrequency)
	{
		emit();
		emissionTimer = emissionTimer - emissionFrequency;
	}

	for (int i=0; i<objectCount; i++)
		objects[i]->Update(deltaTime);
}

void SnowfallParticleEmitter::RenderAll()
{
	glBindTexture(GL_TEXTURE_2D, Particle::particleTexture);

	glDepthMask(GL_FALSE);

	for (int i=0; i<objectCount; i++)
		objects[i]->Render();

	glDepthMask(GL_TRUE);
}

void SnowfallParticleEmitter::SetPosition(float x, float y, float z)
{
	position->x() = x;
	position->y() = y;
	position->z() = z;
}

void SnowfallParticleEmitter::SetVelocity(float xVel, float yVel, float zVel)
{
	velocity->x() = xVel;
	velocity->y() = yVel;
	velocity->z() = zVel;
}

void SnowfallParticleEmitter::emit()
{
	if (!on)
		return;

	Particle *p = objects[NextObject()];

	p->alive = true;
	p->age = 0.0f;
	p->lifespan = 5.0f;
	p->halfSize = 0.02f;

	p->color->r() = 1.0f;
	p->color->g() = 1.0f;
	p->color->b() = 1.0f;
	p->color->a() = 0.5f;

	p->position->x() = (float)((((rand() % 100) / 100.0f) * 16.0f) - 3.0f);
	p->position->y() = 2.8f;
	p->position->z() = (float)((rand() % 200) / 100.0f);
	
	p->velocity->y() = ((rand() % 100) / 100.0f) - 1.5f;
}