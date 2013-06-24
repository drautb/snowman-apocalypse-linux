#include "Object.h"

int Object::nextId = 0;

Object::Object(void)
{
	id = nextId++;
}


Object::~Object(void)
{

}
