#pragma once

#include "Message.h"
#include "ObjectManager.h"

class MessageManager : public ObjectManager<Message>
{
private:

	const static int			MESSAGE_COUNT = 10;

private:
	MessageManager(void);

public:
	~MessageManager(void);

	static MessageManager *GetInstance();

	void UpdateAll(float deltaTime);
	void RenderAll();

	void AddMessage(int x, int y, int width, int height, GLuint texture, float lifeSpan);
};

