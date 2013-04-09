#include <GL\glfw.h>

#include "cs455Utils.h"
#include "StatusBar.h"

StatusBar::StatusBar(float min, float max, float width, float height)
{
	minVal = min;
	maxVal = max;

	SetWidth(width);
	SetHeight(height);

	backgroundColor = new Vector455();
	*backgroundColor = Vector455::Zero();
	backgroundColor->r() = 0.5f;
	backgroundColor->g() = 0.5f;
	backgroundColor->b() = 0.5f;

	currentColor = new Vector455();
	*currentColor = Vector455::Zero();
	
	Update(0.0f);
}

StatusBar::~StatusBar(void)
{

}

void StatusBar::Update(float currentVal)
{
	this->currentVal = currentVal;

	calculateColor();
}

void StatusBar::Render(float x, float y, float z)
{
	glDisable(GL_BLEND);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(x, y, z);

	renderBar();
	renderBackground();

	glPopMatrix();
}

void StatusBar::SetWidth(float newWidth)
{
	width = newWidth;
	halfWidth = width / 2.0f;
}

void StatusBar::SetHeight(float newHeight)
{
	height = newHeight;
	halfHeight = height / 2.0f;
}

void StatusBar::calculateColor()
{
	float halfway = (maxVal - minVal) / 2.0f;

	if (currentVal < halfway)
	{
		currentColor->r() = 1.0f;
		currentColor->g() = currentVal / halfway;
	}
	else
	{
		currentColor->r() = 1.0f - ((currentVal - halfway) / halfway);
		currentColor->g() = 1.0f;
	}
}

void StatusBar::renderBackground()
{
	glColor4f(backgroundColor->r(), backgroundColor->g(), backgroundColor->b(), 1.0f);

	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(-halfWidth, -halfHeight, 0.0f);
		glVertex3f(halfWidth, -halfHeight, 0.0f);
		glVertex3f(-halfWidth, halfHeight, 0.0f);
		glVertex3f(halfWidth, halfHeight, 0.0f);
	glEnd();
}

void StatusBar::renderBar()
{
	glColor4f(currentColor->r(), currentColor->g(), currentColor->b(), 1.0f);
	float leftX =  -halfWidth;
	float rightX = leftX + ((currentVal / maxVal) * width);

	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(leftX, -halfHeight, 0.0f);
		glVertex3f(leftX, halfHeight, 0.0f);
		glVertex3f(rightX, -halfHeight, 0.0f);
		glVertex3f(rightX, halfHeight, 0.0f);
	glEnd();
}