#pragma once

#include "cs455Utils.h"
#include "Renderable.h"

class Fort : public Renderable
{
public:

	float				z;

	static GLuint		fortTexture;

public:

	Fort(void);
	~Fort(void);

	float Z()const{return z;}

	void Render();

	static void LoadTextures();
};

