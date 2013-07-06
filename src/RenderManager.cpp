#define ILUT_USE_OPENGL

#include <list>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include <GLFW/glfw3.h>

#include "RenderManager.h"
#include "Renderable.h"

using namespace std;

bool sortPredicate(const Renderable *lhs, const Renderable *rhs)
{
	return lhs->Z() < rhs->Z();
}

GLuint LoadTexture2D(const char* filename)
{
	ILuint imageID;				// Create an image ID as a ULuint
 
	GLuint textureID;			// Create a texture ID as a GLuint
 
	ILboolean success;			// Create a flag to keep track of success/failure
 
	ILenum error;				// Create a flag to keep track of the IL error state
 
	ilGenImages(1, &imageID); 		// Generate the image ID
 
	ilBindImage(imageID); 			// Bind the image
 
	success = ilLoadImage(filename); 	// Load the image file
 
	// If we managed to load the image, then we can start to do things with it...
	if (success)
	{
		// If the image is flipped (i.e. upside-down and mirrored, flip it the right way up!)
		ILinfo ImageInfo;
		iluGetImageInfo(&ImageInfo);
		if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
		{
			iluFlipImage();
		}
 
		// Convert the image into a suitable format to work with
		// NOTE: If your image contains alpha channel you can replace IL_RGB with IL_RGBA
		success = ilConvertImage(IL_RGBA, IL_SIGNED_BYTE);
 
		// Quit out if we failed the conversion
		if (!success)
		{
			error = ilGetError();
			std::cout << "Image conversion failed - IL reports error: " << error << " - " << iluErrorString(error) << std::endl;
			exit(-1);
		}
 
		// Generate a new texture
		glGenTextures(1, &textureID);
 
		// Bind the texture to a name
		glBindTexture(GL_TEXTURE_2D, textureID);
 
		// Set texture clamping method
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
 
		// Set texture interpolation method to use linear interpolation (no MIPMAPS)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
 
		// Specify the texture specification
		glTexImage2D(GL_TEXTURE_2D, 				// Type of texture
					 0,				// Pyramid level (for mip-mapping) - 0 is the top level
					 ilGetInteger(IL_IMAGE_BPP),	// Image colour depth
					 ilGetInteger(IL_IMAGE_WIDTH),	// Image width
					 ilGetInteger(IL_IMAGE_HEIGHT),	// Image height
					 0,				// Border width in pixels (can either be 1 or 0)
					 ilGetInteger(IL_IMAGE_FORMAT),	// Image format (i.e. RGB, RGBA, BGR etc.)
					 GL_UNSIGNED_BYTE,		// Image data type
					 ilGetData());			// The actual image data itself
 	}
  	else // If we failed to open the image file in the first place...
  	{
		error = ilGetError();
		std::cout << "Image load failed - IL reports error: " << error << " - " << iluErrorString(error) << std::endl;
		exit(-1);
  	}
 
 	ilDeleteImages(1, &imageID); // Because we have already copied image data into texture data we can release memory used by image.
 
	std::cout << "Texture creation successful." << std::endl;
 
	return textureID; // Return the GLuint to the texture so you can use it!

	// char* file = (char*)malloc(filename.length() + 1);
	// strcpy(file, filename.c_str());
	// GLuint textureID = ilutGLLoadImage(file);
	// free(file);

	// return textureID;
}

RenderManager::RenderManager(void)
{
	objectsToRender.clear();
}

RenderManager::~RenderManager(void)
{

}

RenderManager *RenderManager::GetInstance()
{
	static RenderManager instance;

	return &instance;
}

void RenderManager::RegisterObject(Renderable *obj)
{
	objectsToRender.push_back(obj);
}

void RenderManager::RenderAll()
{
	//objectsToRender.sort(&RenderManager::sortPredicate);
	sort(objectsToRender.begin(), objectsToRender.end(), sortPredicate);

	for (vector<Renderable*>::const_iterator iter = objectsToRender.begin();
		iter != objectsToRender.end(); ++iter)
	{
		(*iter)->Render();
	}
}

