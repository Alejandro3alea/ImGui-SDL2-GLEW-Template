#include "Editor.h"
#include "Graphics/WindowMgr.h"
#include "Input/InputMgr.h"
#include "Graphics/GfxMgr.h"
#include "ImGuiWidgets.h"

#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_opengl3.h"

ImGuiEditor* ImGuiEditor::mpInstance;

void ImGuiEditor::Initialize()
{
	const char* glsl_version = "#version 330";

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	mDockspaceFlags |= ImGuiDockNodeFlags_NoDockingInCentralNode;
	mDockspaceFlags |= ImGuiDockNodeFlags_PassthruCentralNode;

	SetImGuiStyle();

	Window* win = WindowMgr->mCurrentWindow.get();

	// Setup Platform/Renderer bindings
	ImGui_ImplSDL2_InitForOpenGL(*win, win);
	ImGui_ImplOpenGL3_Init(glsl_version);
}

void ImGuiEditor::Update()
{
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	Window* win = WindowMgr->mCurrentWindow.get();

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	Dockspace();
	MainMenu();

	ImGui::EndFrame();

	// Rendering
	ImGui::Render();
	glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiEditor::Shutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiEditor::ProcessSDLEvent(SDL_Event& event)
{
	ImGui_ImplSDL2_ProcessEvent(&event);
}

void ImGuiEditor::Dockspace()
{
	static bool opt_fullscreen_persistant = true;
	bool opt_fullscreen = opt_fullscreen_persistant;

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBackground;
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace", &mbDockWindowOpen, window_flags);
	ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);


	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("TestDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), mDockspaceFlags);
	}

	ImGui::End();
}

void ImGuiEditor::MainMenu()
{
	static bool ShowImGuiDemoWindow;

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Help"))
		{
			ShowImGuiDemoWindow = !ShowImGuiDemoWindow;
			ImGui::EndMenu();
		}
	}
	ImGui::EndMainMenuBar();

	if (ShowImGuiDemoWindow)
		ImGui::ShowDemoWindow();
}

void ImGuiEditor::SetImGuiStyle()
{
	ImGui::StyleColorsDark();

	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_Tab] = ImVec4(0.95f, 0.4f, 0.4f, 1.0f); // Tab color
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.0f, 0.6f, 0.6f, 1.0f); // Tab hover color
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.8f, 0.8f, 0.0f, 1.0f); // Active tab color

	// Text and widget bg
	style.Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.80f, 0.2f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.4f, 0.4f, 0.4, 0.4f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.47f, 0.07f, 0.69f, 0.40f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.44f, 0.12f, 0.45f, 0.69f);

	// Top Row
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.25f, 0.25f, 0.25f, 0.9f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.3f, 0.3f, 0.3f, 0.9f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.90f, 0.00f, 0.80f, 0.20f);
	
	//style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.40f, 0.90f, 0.55f, 0.80f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.5f, 0.5f, 0.5f, 0.6f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.5f, 0.6f, 0.5f, 0.5f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.6f, 0.6f, 0.6f, 0.6f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.5f, 0.5f, 0.5f, 0.8f);

	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.60f, 0.90f, 0.60f, 0.60f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.41f, 0.39f, 0.80f, 0.60f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.35f, 0.60f, 0.41f, 0.62f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.40f, 0.98f, 0.01f, 0.79f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.76f, 0.94f, 0.70f, 0.8f);

	style.Colors[ImGuiCol_Header] = ImVec4(0.40f, 0.40f, 0.40f, 0.0f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.45f, 0.90f, 0.45f, 0.80f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.53f, 0.87f, 0.53f, 0.0f);

	style.Colors[ImGuiCol_Separator] = ImVec4(0.40f, 0.40f, 0.40f, 0.60f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.60f, 0.60f, 0.70f, 1.00f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.70f, 0.70f, 0.90f, 1.00f);

	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.16f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.78f, 0.82f, 1.00f, 0.60f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.78f, 0.82f, 1.00f, 0.90f);

	style.Colors[ImGuiCol_Tab] = ImLerp(style.Colors[ImGuiCol_Header], style.Colors[ImGuiCol_TitleBgActive], 0.80f);
	style.Colors[ImGuiCol_TabHovered] = style.Colors[ImGuiCol_HeaderHovered];
	style.Colors[ImGuiCol_TabActive] = ImLerp(style.Colors[ImGuiCol_HeaderActive], style.Colors[ImGuiCol_TitleBgActive], 0.60f);
	style.Colors[ImGuiCol_TabUnfocused] = ImLerp(style.Colors[ImGuiCol_Tab], style.Colors[ImGuiCol_TitleBg], 0.80f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImLerp(style.Colors[ImGuiCol_TabActive], style.Colors[ImGuiCol_TitleBg], 0.40f);
	style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.0f, 0.70f, 0.90f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 1.00f, 0.00f, 0.35f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	style.Colors[ImGuiCol_NavHighlight] = style.Colors[ImGuiCol_HeaderHovered];
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);

	style.TabBorderSize = 0.50f; // Border size around tabs
	style.TabRounding = 0.5f; // Rounding of the tabs

	style.WindowPadding = ImVec2(10, 10);
	style.WindowRounding = 5.0f;
	style.FramePadding = ImVec2(5, 5);
	style.FrameRounding = 4.0f;
	style.ItemSpacing = ImVec2(8, 7);
	style.ItemInnerSpacing = ImVec2(8, 6);
	style.IndentSpacing = 25.0f;
	style.ScrollbarSize = 15.0f;
	style.ScrollbarRounding = 9.0f;
	style.GrabMinSize = 5.0f;
}