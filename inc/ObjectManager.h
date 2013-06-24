#pragma once

#include <vector>

#include "cs455Utils.h"

using namespace std;

template <typename T>
class ObjectManager
{
public:

	vector<T*>				objects;

protected:

	int						objectCount;

	int						nextObject;

public:

	ObjectManager()
	{
		objectCount = 0;
		nextObject = 0;
	}

	~ObjectManager(void)
	{
		for (int i=0; i<objectCount; i++)
			SAFE_DELETE(objects[i]);

		objects.clear();
	}

	void Initialize(int objectCount)
	{
		this->objectCount = objectCount;

		for (int i=0; i<objectCount; i++)
			objects.push_back(new T());

		nextObject = 0;
	}

	int NextObject()
	{
		nextObject++;
		if (nextObject >= objectCount)
			nextObject = 0;

		return nextObject;
	}
};

