#include "MovingObject.h"


MovingObject::MovingObject(void)
{
	position = new Vector455();
	velocity = new Vector455();
	acceleration = new Vector455();

	*position = Vector455::Zero();
	*velocity = Vector455::Zero();
	*acceleration = Vector455::Zero();
}


MovingObject::~MovingObject(void)
{
	SAFE_DELETE(position);
	SAFE_DELETE(velocity);
	SAFE_DELETE(acceleration);
}

void MovingObject::UpdateMovement(float deltaTime)
{
	*velocity += *acceleration * deltaTime;
	*position += *velocity * deltaTime;
}