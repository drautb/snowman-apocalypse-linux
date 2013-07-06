#pragma once

#include <set>

#include <GLFW/glfw3.h>

#include "MovingObject.h"
#include "StatusBar.h"
#include "Renderable.h"

class Snowman : public MovingObject, public Renderable
{
public: 
	
	static GLuint				snowmanTexture;

private:

	bool						alive, melting;

	float						health, MAX_HEALTH;
	StatusBar					*healthBar;
	
	bool						facingRight;
	
	float						scaleX, scaleY;
	float						minScale, maxScale, scaleModifier;
	float						meltModifier;

	float						xVelModifier; // Speed will slow down with health

	static float				SNOWBALL_DAMAGE_FACTOR;
	static float				FLAME_DAMAGE_FACTOR;

public:

	static float				halfWidth, halfHeight;

public:

	/**
	 * Constructors/Destructors
	 */
	Snowman(void);
	~Snowman(void);

	void Respawn(set<float> *zValues);

	void Update(float deltaTime);
	void Render();
	void RenderHealthBar();

	bool HitWithSnowball();
	bool HitWithFlame(float deltaTime);

	bool IsAlive()const{return alive && !melting;}
	float x()const{return position->x();}
	float y()const{return position->y();}
	float z()const{return position->z();}
	float Z()const{return position->z();}

	void Kill(){alive=false;}

	static void LoadTextures();

private:

	void switchScaleDirection();
	void clampHealth();
};

