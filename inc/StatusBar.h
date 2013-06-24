#pragma once

#include "cs455Utils.h"

class StatusBar
{
private:

	float						minVal, maxVal;
	float						currentVal;

	float						width, height;
	float						halfWidth, halfHeight;
	
	Vector455					*backgroundColor;

	Vector455					*currentColor;
	
public:

	/**
	 * Constructor/Destructor
	 */
	StatusBar(float min, float max, float width, float height);
	~StatusBar(void);

	void Update(float currentVal);
	void Render(float x, float y, float z);

	void SetWidth(float newWidth);
	void SetHeight(float newHeight);

private:

	void calculateColor();

	void renderBackground();
	void renderBar();
};

