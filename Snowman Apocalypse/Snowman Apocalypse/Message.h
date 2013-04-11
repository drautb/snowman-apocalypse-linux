#pragma once

#include <GL\glfw.h>

class Message
{
public:

	int					x, y;
	int					width, height;
	float				alpha, alphaModifier;

	bool				active, fading;
	float				age, lifeSpan;

	GLuint				texture;

public:
	Message(void);
	~Message(void);

	void Update(float deltaTime);
	void Render();
};

