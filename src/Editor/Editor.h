#pragma once
#include "Misc/Singleton.h"
#include <SDL2/SDL_events.h>

#include "imgui/imgui.h"

class ImGuiEditor
{
	Singleton(ImGuiEditor);

public:
	void Initialize();
	void Update();
	void Shutdown();

	void ProcessSDLEvent(SDL_Event& event);

	void Dockspace();
	void MainMenu();

	void SetImGuiStyle();

public:
	bool mbDockWindowOpen;
	ImGuiDockNodeFlags mDockspaceFlags = ImGuiDockNodeFlags_None;
};

#define Editor ImGuiEditor::Instance()