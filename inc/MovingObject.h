#pragma once

#include "cs455Utils.h"
#include "Object.h"

class MovingObject : public Object
{
public:

	Vector455			*position;
	Vector455			*velocity;
	Vector455			*acceleration;

public:

	/**
	 * Constructor/Destructor
	 */
	MovingObject(void);
	~MovingObject(void);

	void UpdateMovement(float deltaTime);

	virtual void Update(float deltaTime)=0;
	virtual void Render()=0;
};

