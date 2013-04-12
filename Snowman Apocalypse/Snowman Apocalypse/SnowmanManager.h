#pragma once

#include <set>

#include "ObjectManager.h"
#include "Snowman.h"

using namespace std;

class SnowmanManager : public ObjectManager<Snowman>
{
public:

	const static int					SNOWMAN_COUNT = 100;

private:

	float								spawnTimer, spawnFrequency;
	int									leftToSpawn;
	bool								allDead;

	set<float>							zValues;

public:

	/**
	 * Constructor/Destructor
	 */
	SnowmanManager(void);
	~SnowmanManager(void);

	void Reset();

	void UpdateAll(float deltaTime);
	void RenderBlips(int x, int y, int width, int height);

	void NextWave(int waveNum);

	bool AllDead()const{return allDead && leftToSpawn == 0;}
};

