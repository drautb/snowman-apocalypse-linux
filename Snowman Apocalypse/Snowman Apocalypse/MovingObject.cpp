#include "MovingObject.h"


MovingObject::MovingObject(void)
{
	position = Vector455::Zero();
	velocity = Vector455::Zero();
	acceleration = Vector455::Zero();
}


MovingObject::~MovingObject(void)
{

}

void MovingObject::Update(float deltaTime)
{
	velocity += acceleration * deltaTime;
	position += velocity * deltaTime;
}