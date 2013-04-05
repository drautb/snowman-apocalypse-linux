#include <cmath>

#include "FlameParticleEmitter.h"

FlameParticleEmitter::FlameParticleEmitter(void)
{
	position = new Vector455();

	emissionTimer = 0.0f;
	emissionFrequency = 0.005f;

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
	glBindTexture(GL_TEXTURE_2D, Particle::particleTexture);

	for (int i=0; i<objectCount; i++)
		objects[i]->Render();
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
	p->color->r() = 1.0f;
	p->color->g() = (float)(((rand() % 35) + 50) / 100.0f);
	p->color->b() = 0.0f;

	p->position->x() = this->position->x() + 0.3f * (facingRight ? 1.0f : -1.0f);
	p->position->y() = this->position->y();
	p->position->z() = this->position->z();

	p->velocity->x() = velocity->x() + (2.5f + ((rand() % 100) / 100.0f)) * (facingRight ? 1.0f : -1.0f);
	p->velocity->y() = ((rand() % 100) / 100.0f) - 0.5f;
	p->velocity->z() = ((rand() % 100) / 100.0f) - 0.5f;

	p->acceleration->y() = 1.0f;
}