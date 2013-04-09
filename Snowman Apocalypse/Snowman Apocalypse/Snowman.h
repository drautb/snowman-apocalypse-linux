#pragma once

#include <GL\glfw.h>

#include "MovingObject.h"
#include "StatusBar.h"

class Snowman : public MovingObject
{
public: 
	
	static GLuint				snowmanTexture;

private:

	bool						alive;

	float						health, MAX_HEALTH;
	StatusBar					*healthBar;
	
	bool						facingRight;
	
	float						scaleX;
	float						minScale, maxScale, scaleModifier;

	float						xVelModifier; // Speed will slow down with health

	static float				halfWidth, halfHeight;

public:

	/**
	 * Constructors/Destructors
	 */
	Snowman(void);
	~Snowman(void);

	void Respawn();

	void Update(float deltaTime);
	void Render();

	static void LoadTextures();

private:

	void switchScaleDirection();
};

