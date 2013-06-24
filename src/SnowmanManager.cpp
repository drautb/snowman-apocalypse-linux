#include "SnowmanManager.h"
#include "World.h"

SnowmanManager::SnowmanManager(void)
{
	this->Initialize(SNOWMAN_COUNT);

	spawnTimer = 0.0f;
	spawnFrequency = 1.0f;

	Reset();
}


SnowmanManager::~SnowmanManager(void)
{

}

void SnowmanManager::Reset()
{
	leftToSpawn = 0;

	allDead = false;

	zValues.clear();

	for (int i=0; i<objectCount; i++)
		objects[i]->Kill();
}

void SnowmanManager::UpdateAll(float deltaTime)
{
	spawnTimer += deltaTime;
	if (spawnTimer > spawnFrequency)
	{
		if (leftToSpawn-- > 0)
			objects[NextObject()]->Respawn(&zValues);

		spawnTimer = 0.0f;

		// Don't let it go negative
		leftToSpawn = (leftToSpawn < 0 ? 0 : leftToSpawn);
	}

	for (int i=0; i<objectCount; i++)
		objects[i]->Update(deltaTime);
}

/*
void SnowmanManager::RenderAll()
{
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, Snowman::snowmanTexture);

	for (int i=0; i<objectCount; i++)
		objects[i]->Render();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	for (int i=0; i<objectCount; i++)
		objects[i]->RenderHealthBar();
}
*/

void SnowmanManager::RenderBlips(int x, int y, int width, int height)
{
	allDead = true;
	for (int i=0; i<SNOWMAN_COUNT; i++)
	{
		if (objects[i]->IsAlive())
		{
			allDead = false;
			glVertex2i(x + (int)((objects[i]->x() / World::MAX_X) * width), y + (int)((objects[i]->z() / World::MAX_Z) * height));
		}
	}
}

void SnowmanManager::NextWave(int waveNumber)
{
	leftToSpawn = waveNumber * 2 + 5;
	zValues.clear();
}
