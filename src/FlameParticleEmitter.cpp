#include <cmath>

#include "FlameParticleEmitter.h"

FlameParticleEmitter::FlameParticleEmitter(void)
{
	position = new Vector455();

	emissionTimer = 0.0f;
	emissionFrequency = 0.004f;

	Initialize(PARTICLE_COUNT);
}

FlameParticleEmitter::~FlameParticleEmitter(void)
{
	SAFE_DELETE(position);
}

void FlameParticleEmitter::UpdateAll(float deltaTime)
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

void FlameParticleEmitter::RenderAll()
{
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, Particle::particleTexture);

	glDepthMask(GL_FALSE);

	for (int i=0; i<objectCount; i++)
		objects[i]->Render();

	glDepthMask(GL_TRUE);
}

void FlameParticleEmitter::SetPosition(float x, float y, float z)
{
	position->x() = x;
	position->y() = y;
	position->z() = z;
}

void FlameParticleEmitter::SetVelocity(float xVel, float yVel, float zVel)
{
	velocity->x() = xVel;
	velocity->y() = yVel;
	velocity->z() = zVel;
}

void FlameParticleEmitter::emit()
{
	if (!on)
		return;

	Particle *p = objects[NextObject()];

	p->alive = true;
	p->age = 0.0f;
	p->lifespan = 0.6f;
	p->halfSize = 0.06f;

	p->color->r() = 1.0f;
	p->color->g() = (float)(((rand() % 40) + 50) / 100.0f);
	p->color->b() = 0.0f;
	p->color->a() = 0.8f;

	p->colorDecay->g() = 2.0f;
	p->colorDecay->a() = 1.5f;

	p->position->x() = this->position->x() + 0.3f * (facingRight ? 1.0f : -1.0f);
	p->position->y() = this->position->y();
	p->position->z() = this->position->z();

	p->velocity->x() = velocity->x() + (2.5f + ((rand() % 100) / 100.0f)) * (facingRight ? 1.0f : -1.0f);
	p->velocity->y() = ((rand() % 100) / 100.0f) - 0.5f;
	p->velocity->z() = ((rand() % 100) / 100.0f) - 0.5f;

	p->acceleration->y() = 2.0f;
}