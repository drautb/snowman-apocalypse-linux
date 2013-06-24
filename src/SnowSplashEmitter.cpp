#include "SnowSplashEmitter.h"
#include "World.h"

SnowSplashEmitter::SnowSplashEmitter(void)
{
	Initialize(PARTICLE_COUNT);
}


SnowSplashEmitter::~SnowSplashEmitter(void)
{

}

void SnowSplashEmitter::UpdateAll(float deltaTime)
{
	for (int i=0; i<objectCount; i++)
		objects[i]->Update(deltaTime);
}

void SnowSplashEmitter::RenderAll()
{
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Particle::particleTexture);

	glDepthMask(GL_FALSE);

	for (int i=0; i<objectCount; i++)
		objects[i]->Render();

	glDepthMask(GL_TRUE);
}

void SnowSplashEmitter::Emit(float x, float y, float z, int count)
{
	for (int i=0; i<count; i++)
	{
		Particle *p = objects[NextObject()];

		p->alive = true;
		p->age = 0.0f;
		p->lifespan = 1.0f;
		p->halfSize = 0.02f;

		p->color->r() = 0.0f;
		p->color->g() = 0.6f;
		p->color->b() = 1.0f;
		p->color->a() = 1.0f;

		p->colorDecay->a() = 1.5f;

		p->position->x() = x;
		p->position->y() = y;
		p->position->z() = z;

		p->velocity->x() = (((rand() % 50) + 50) / 100.0f + 0.0f) * (rand() % 10 > 4 ? 1.0f : -1.0f);
		p->velocity->y() = (((rand() % 50) + 50) / 100.0f + 3.0f) * (rand() % 10 > 4 ? 1.0f : -1.0f);
		p->velocity->z() = (((rand() % 50) + 50) / 100.0f + 0.0f) * (rand() % 10 > 4 ? 1.0f : -1.0f);

		p->acceleration->y() = -World::GRAVITY;
	}
}