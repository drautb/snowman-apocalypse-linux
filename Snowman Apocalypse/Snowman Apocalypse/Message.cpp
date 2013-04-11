#include "Message.h"


Message::Message(void)
{
	x = y = width = height = 0;
	
	alpha = alphaModifier = 1.0f;

	active = true;
	fading = false;

	age = lifeSpan = 0.0f;

	texture = -1;
}

Message::~Message(void)
{

}

void Message::Update(float deltaTime)
{
	if (!active)
		return;

	if (fading)
	{
		alpha -= alphaModifier * deltaTime;
		if (alpha < 0.0f)
			active = false;
	}

	age += deltaTime;
	if (age > lifeSpan)
		fading = true;
}

void Message::Render()
{
	if (!active)
		return;

	glBindTexture(GL_TEXTURE_2D, texture);
	glColor4f(1.0f, 1.0f, 1.0f, alpha);
	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2i(0, 1);
		glVertex2i(x, y);
		glTexCoord2i(0, 0);
		glVertex2i(x, y + height);
		glTexCoord2i(1, 1);
		glVertex2i(x + width, y);
		glTexCoord2i(1, 0);
		glVertex2i(x + width, y + height);
	glEnd();
}
