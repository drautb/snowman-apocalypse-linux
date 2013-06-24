#pragma once

#include <GL\glfw.h>

#include "cs455Utils.h"
#include "MovingObject.h"
#include "FlameParticleEmitter.h"
#include "StatusBar.h"
#include "Renderable.h"

class Calvin : public MovingObject, public Renderable
{
public:

	GLuint					calvinSnowballTexture;
	GLuint					calvinFlamethrowerTexture;
	GLuint					overheatedMsgTexture;

private:

	float					width, height;
	float					halfWidth;
	
	float					xVelModifier, yVelModifier, zVelModifier;
	float					maxHorizontalVel, maxVerticalVel;
	float					yRot, yRotVel;

	float					facingRightYRot, facingLeftYRot;

	bool					facingRight;
	bool					canJump;
	bool					snowballsEquipped;

	int						targetX, targetY;

	// Ammo!
	float					snowballs, maxSnowballs;
	float					flameFuel, maxFlameFuel, flameChargeFactor;

	bool					flamethrowing;

	FlameParticleEmitter	flameEmitter;

public:
	Calvin(void);
	~Calvin(void);

	void Reset();

	void LoadTextures();
	void Update(float deltaTime);
	void Render();

	float &x(){return position->x();}
	float &y(){return position->y();}
	float &z(){return position->z();}

	float CenterX()const;
	float CenterY()const;
	float CenterZ()const;

	float Z()const{return CenterZ();}

	float Snowballs()const{return snowballs;}
	float MaxSnowballs()const{return maxSnowballs;}
	void FillSnowballs(){snowballs = maxSnowballs;}
	void  HitSnowmanWithSnowball();

	float FlameFuel()const{return flameFuel;}
	float MaxFlameFuel()const{return maxFlameFuel;}

	bool IsFlamethrowing()const{return flamethrowing && flameFuel > 0.0f;}
	bool IsFacingRight()const{return facingRight;}

private:

	void pollInput();
	void clampSnowballs();
	void clampFlameFuel();
};

