#include "GfxMgr.h"
#include "WindowMgr.h"

#include <SDL2/SDL_video.h>
#include <GL/glew.h>

#include <algorithm>
#include <iostream>


GraphicsManager* GraphicsManager::mpInstance;

void GraphicsManager::Initialize()
{
	// Initialize OpenGL library
 	glewExperimental = true;
	if (glewInit() != GLEW_OK) // Ensure causes errors
	{
		std::cout << "GLEW Error: Failed to init" << std::endl;
		abort();
	}
	std::string version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
	if (version.empty()) 
		std::cerr << "Unable to retrieve OpenGL version." << std::endl;
	else
		std::cout << "OpenGL Version: " << version << std::endl << std::endl;


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MULTISAMPLE);
}

void GraphicsManager::Render()
{
	ClearBuffer();
}

void GraphicsManager::SetClearColor(const f32 r, const f32 g, const f32 b)
{
	glClearColor(r, g, b, 1.0f);
}

void GraphicsManager::ClearBuffer()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}