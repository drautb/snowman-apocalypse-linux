#include <vector>

#include "Snowball.h"
#include "World.h"
#include "RenderManager.h"

using namespace std;

vector<Snowball*> Snowball::SnowballManager;
GLuint Snowball::snowballTexture;
int Snowball::currentSnowball = 0;

Snowball::Snowball(void)
{
	alive = false;

	RenderManager::GetInstance()->RegisterObject(this);
}


Snowball::~Snowball(void)
{

}

void Snowball::Update(float deltaTime)
{
	if (!alive)
		return;

	UpdateMovement(deltaTime);
}

void Snowball::Render(void)
{
	if (!alive)
		return;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(position->x(), position->y(), position->z());

	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, snowballTexture);

	glBegin(GL_TRIANGLE_STRIP);
		glColor3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.1f, -0.1f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.1f, -0.1f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.1f, 0.1f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.1f, 0.1f, 0.0f);
	glEnd();

	glPopMatrix();
}

void Snowball::LoadTextures(void)
{
	snowballTexture = LoadTexture2D("textures/snowball.tga");
}

void Snowball::InitManager(void)
{
	for (int s=0; s<SNOWBALL_COUNT; s++)
		SnowballManager.push_back(new Snowball());
}

void Snowball::ShutdownManager(void)
{
	for (int s=0; s<SNOWBALL_COUNT; s++)
		SAFE_DELETE(SnowballManager[s]);

	SnowballManager.clear();
}

void Snowball::UpdateAll(float deltaTime)
{
	for (int s=0; s<SNOWBALL_COUNT; s++)
		SnowballManager[s]->Update(deltaTime);
}

/*
void Snowball::RenderAll(void)
{
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, snowballTexture);

	for (int s=0; s<SNOWBALL_COUNT; s++)
		SnowballManager[s]->Render();
}
*/

void Snowball::Throw(float x, float y, float z, float xVel, float yVel)
{
	Snowball *sb = SnowballManager[NextSnowball()];

	sb->position->x() = x;
	sb->position->y() = y;
	sb->position->z() = z;

	sb->velocity->x() = xVel;
	sb->velocity->y() = yVel;
	
	sb->acceleration->y() = -World::GRAVITY;

	sb->alive = true;
}

int Snowball::NextSnowball()
{
	currentSnowball++;
	if (currentSnowball >= SNOWBALL_COUNT)
		currentSnowball = 0;

	return currentSnowball;
}