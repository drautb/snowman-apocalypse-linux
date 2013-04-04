#pragma once

#include <GL\glfw.h>

#include "cs455Utils.h"
#include "MovingObject.h"

class Calvin : public MovingObject
{
private:

	GLuint					calvinSnowballTexture;
	GLuint					calvinFlamethrowerTexture;

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
	int						snowballs;
	float					flameFuel;

public:
	Calvin(void);
	~Calvin(void);

	void LoadTextures();
	void Update(float deltaTime);
	void Render();

	float &x(){return position->x();}
	float &y(){return position->y();}
	float &z(){return position->z();}

	float CenterX();
	float CenterY();
	float CenterZ();

private:

	void pollInput();
};

