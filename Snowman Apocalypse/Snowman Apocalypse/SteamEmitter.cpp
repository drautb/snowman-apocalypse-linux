#include "SteamEmitter.h"
#include "Snowman.h"
#include "World.h"

SteamEmitter::SteamEmitter(void)
{
	Initialize(PARTICLE_COUNT);
}


SteamEmitter::~SteamEmitter(void)
{

}

void SteamEmitter::UpdateAll(float deltaTime)
{
	for (int i=0; i<objectCount; i++)
		objects[i]->Update(deltaTime);
}

void SteamEmitter::RenderAll()
{
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Particle::particleTexture);

	glDepthMask(GL_FALSE);

	for (int i=0; i<objectCount; i++)
		objects[i]->Render();

	glDepthMask(GL_TRUE);
}

void SteamEmitter::Emit(float x, float y, float z, int count)
{
	for (int i=0; i<count; i++)
	{
		Particle *p = objects[NextObject()];

		p->alive = true;
		p->age = 0.0f;
		p->lifespan = 0.8f;
		p->halfSize = 0.02f;

		p->color->r() = 0.6f;
		p->color->g() = 0.6f;
		p->color->b() = 1.0f;
		p->color->a() = 0.8f;

		p->colorDecay->a() = 2.0f;

		p->position->x() = x + (((rand() % 100) / 100.0f) * Snowman::halfWidth) * (rand() % 10 > 4 ? 1.0f : -1.0f);
		p->position->y() = y + (((rand() % 100) / 100.0f) * Snowman::halfHeight);
		p->position->z() = z + 0.01f;

		p->velocity->x() = 0.0f;
		p->velocity->y() = (((rand() % 50) + 50) / 100.0f + 2.0f);
		p->velocity->z() = 0.0f;
	}
}