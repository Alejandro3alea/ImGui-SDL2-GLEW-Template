#include "InputMgr.h"
#include "Graphics/WindowMgr.h"

InputManager* InputManager::mpInstance;

SDL_Event InputManager::ProcessInput()
{
	SDL_Event event_sdl;

	while (SDL_PollEvent(&event_sdl))
	{
		switch (event_sdl.type)
		{
		case SDL_QUIT:
			WindowMgr->mCurrentWindow->Close();
			break;
		default:
			break;
		}
	}

	return event_sdl;
}
