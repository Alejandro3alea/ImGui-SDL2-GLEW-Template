#include "Graphics/WindowMgr.h"
#include "Graphics/GfxMgr.h"
#include "Editor/Editor.h"
#include "Input/InputMgr.h"

#undef main
int main(void) {

	WindowMgr->Initialize("ImGui Template");
	GfxMgr->Initialize();
	Editor->Initialize();
    InputMgr->Initialize();

    GfxMgr->SetClearColor(0.2f, 0.2f, 0.2f);

	while (!WindowMgr->IsCurrentWindowClosed())
	{
		SDL_Event sdlEvent = InputMgr->ProcessInput();
        
		GfxMgr->Render();
		Editor->Update();

		WindowMgr->SwapWindow();
	}
    
    InputMgr->Shutdown();
    return 0;
}