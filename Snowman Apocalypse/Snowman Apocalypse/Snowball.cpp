#include <vector>

#include "Snowball.h"
#include "World.h"

using namespace std;

vector<Snowball*> Snowball::SnowballManager;
GLuint Snowball::snowballTexture;
int Snowball::currentSnowball = 0;

Snowball::Snowball(void)
{
	alive = false;
}


Snowball::~Snowball(void)
{

}

void Snowball::Update(float deltaTime)
{
	if (!alive)
		return;

	UpdateMovement(deltaTime);

	if (position->y() < World::GROUND_Y)
		alive = false;
}

void Snowball::Render(void)
{
	if (!alive)
		return;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(position->x(), position->y(), position->z());

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
	glGenTextures(1, &snowballTexture);
	glBindTexture(GL_TEXTURE_2D, snowballTexture);
	glfwLoadTexture2D("snowball.tga", GLFW_BUILD_MIPMAPS_BIT | GL_RGBA);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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

void Snowball::RenderAll(void)
{
	glBindTexture(GL_TEXTURE_2D, snowballTexture);

	for (int s=0; s<SNOWBALL_COUNT; s++)
		SnowballManager[s]->Render();
}

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