#pragma once
#include "Misc/Singleton.h"

#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_events.h>

class InputManager
{
	Singleton(InputManager)

	SDL_Event ProcessInput();
};

#define InputMgr InputManager::Instance()