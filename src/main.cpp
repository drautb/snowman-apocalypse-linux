#include <iostream>
#include <cmath>
#include <ctime>
#include <IL/il.h>
#include <IL/ilut.h>

#include "cs455Utils.h"
#include "Window.h"

int main(int argc, char *argv[])
{
	Window *window = new Window();

	ilInit();
	iluInit();
	ilutRenderer(ILUT_OPENGL);

	time_t t;
	time(&t);
	srand((unsigned int)t);

	if (window->Open())
		window->EnterMainLoop();
	else
	{
		SAFE_DELETE(window);
		return -1;
	}

	SAFE_DELETE(window);

	return 0;
}
