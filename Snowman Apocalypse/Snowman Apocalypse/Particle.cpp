
#include "Particle.h"
#include "cs455Utils.h"

GLuint Particle::particleTexture = -1;

Particle::Particle(void)
{
	alive = false;

	color = new Vector455();
	*color = Vector455::Identity();

	lifespan = 100.0f;
	age = 0.0f;
}

Particle::~Particle(void)
{
	SAFE_DELETE(color);
}

void Particle::Update(float deltaTime)
{
	if (!alive)
		return;
	
	UpdateMovement(deltaTime);

	age += deltaTime;

	if (age > lifespan)
		alive = false;
}

void Particle::Render()
{
	if (!alive)
		return;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(position->x(), position->y(), position->z());

	glBegin(GL_TRIANGLE_STRIP);
		glColor4f(color->r(), color->g(), color->b(), 0.6f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.05f, -0.05f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.05f, -0.05f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.05f, 0.05f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.05f, 0.05f, 0.0f);
	glEnd();

	glPopMatrix();
}

void Particle::LoadTextures(void)
{
	glGenTextures(1, &particleTexture);
	glBindTexture(GL_TEXTURE_2D, particleTexture);
	glfwLoadTexture2D("particle.tga", GLFW_BUILD_MIPMAPS_BIT | GL_RGBA);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}