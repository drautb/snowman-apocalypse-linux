
#include "Particle.h"
#include "cs455Utils.h"

GLuint Particle::particleTexture = -1;

Particle::Particle(void)
{
	alive = false;

	color = new Vector455();
	*color = Vector455::Identity();

	colorDecay = new Vector455();
	*colorDecay = Vector455::Zero();

	lifespan = 100.0f;
	age = 0.0f;

	halfSize = 0.05f;
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

	*color -= (*colorDecay * deltaTime);
}

void Particle::Render()
{
	if (!alive)
		return;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(position->x(), position->y(), position->z());

	glBegin(GL_TRIANGLE_STRIP);
		glColor4f(color->r(), color->g(), color->b(), color->a());
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-halfSize, -halfSize, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(halfSize, -halfSize, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-halfSize, halfSize, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(halfSize, halfSize, 0.0f);
	glEnd();

	glPopMatrix();
}

void Particle::LoadTextures(void)
{
	glGenTextures(1, &particleTexture);
	glBindTexture(GL_TEXTURE_2D, particleTexture);
	glfwLoadTexture2D("textures/particle.tga", GLFW_BUILD_MIPMAPS_BIT | GL_RGBA);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}