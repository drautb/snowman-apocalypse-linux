#pragma once

#include "cs455Utils.h"
#include "Renderable.h"

class Flag : public Renderable
{
public:

	float				z;

	static GLuint		flagTexture;
	static GLuint		pileTexture;

public:

	Flag(void);
	~Flag(void);

	float Z()const{return z;}

	void Render();

	static void LoadTextures();
};

