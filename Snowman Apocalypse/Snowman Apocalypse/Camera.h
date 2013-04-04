#pragma once

#include "Keyboard.h"
#include "cs455Utils.h"

class Camera
{
private:
	float					velModifier;
	float					maxVelocity;
	float					minVelocity;

	float					xPos, yPos, zPos;	// Postion
	float					xRot, yRot, zRot;	// Rotation

	float					xPosVel, yPosVel, zPosVel;
	float					xRotVel, yRotVel, zRotVel;


private: 
	/**
	 * Private Constructor/Destructor for singleton
	 */
	Camera(void);
	~Camera(void);

public:
	static Camera *GetInstance(void);

	void Zero(void);

	void PollKeyboard();
	void TrackPoint(float x, float y, float z);

	void Update(float deltaTime);
	void Use(void);

private:

	void clampVelocities(void);

};

