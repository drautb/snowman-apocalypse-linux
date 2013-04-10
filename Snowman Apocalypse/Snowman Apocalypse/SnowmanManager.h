#pragma once

#include "ObjectManager.h"
#include "Snowman.h"

class SnowmanManager : public ObjectManager<Snowman>
{
public:

	const static int					SNOWMAN_COUNT = 100;

private:

	float								spawnTimer, spawnFrequency;
	int									leftToSpawn;

public:

	/**
	 * Constructor/Destructor
	 */
	SnowmanManager(void);
	~SnowmanManager(void);

	void UpdateAll(float deltaTime);
	void RenderAll();
	void RenderBlips(int x, int y, int width, int height);

	void NextWave(int waveNum);
};

