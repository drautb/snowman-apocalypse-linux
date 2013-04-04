#pragma once

#include <GL\glfw.h>

#include "cs455Utils.h"

class Calvin
{
private:

	GLuint					calvinSnowballTexture;
	GLuint					calvinFlamethrowerTexture;

	float					width, height;
	float					halfWidth;

	float					xVel, xVelModifier;
	float					yVel;
	float					zVel, zVelModifier;
	
	float					maxHorizontalVel, maxVerticalVel;

	Matrix455				*calvinTransform;

	float					yRot, yRotVel;

	float					facingRightYRot, facingLeftYRot;

	bool					facingRight;
	bool					canJump;
	bool					snowballsEquipped;

	int						targetX, targetY;

public:
	Calvin(void);
	~Calvin(void);

	void LoadTextures();
	void Update(float deltaTime);
	void Render();

	float &x(){return calvinTransform->x();}
	float &y(){return calvinTransform->y();}
	float &z(){return calvinTransform->z();}

	float CenterX()const{return calvinTransform->x() + width / 2.0f;}
	float CenterY()const{return calvinTransform->y() + height / 2.0f;}
	float CenterZ()const{return calvinTransform->z();}

private:

	void pollKeyboard();
};

