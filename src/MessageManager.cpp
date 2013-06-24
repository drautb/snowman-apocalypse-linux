#include "MessageManager.h"
#include "Message.h"

MessageManager::MessageManager(void)
{
	Initialize(MESSAGE_COUNT);
}

MessageManager::~MessageManager(void)
{

}

MessageManager *MessageManager::GetInstance()
{
	static MessageManager instance;

	return &instance;
}

void MessageManager::Reset()
{
	for (int i=0; i<MESSAGE_COUNT; i++)
		objects[i]->Kill();
}

void MessageManager::UpdateAll(float deltaTime)
{
	for (int i=0; i<MESSAGE_COUNT; i++)
		objects[i]->Update(deltaTime);
}

void MessageManager::RenderAll()
{
	for (int i=0; i<MESSAGE_COUNT; i++)
		objects[i]->Render();
}

void MessageManager::AddMessage(int x, int y, int width, int height, GLuint texture, float lifeSpan)
{
	Message *m = objects[NextObject()];

	m->x = x;
	m->y = y;
	m->width = width;
	m->height = height;
	m->texture = texture;
	m->age = 0.0f;
	m->lifeSpan = lifeSpan;
	m->alpha = 1.0f;

	m->active = true;
	m->fading = false;
}
