#pragma once
#include "Misc/Singleton.h"
#include "Misc/DataTypes.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>

#include <memory>
#include <string>

struct Window
{
	Window(const std::string& winName, const unsigned winWidth, const unsigned winHeight);
	~Window();

	void Close() { mbIsClosed = true; }
	bool IsClosed() { return mbIsClosed; }

	std::pair<u32, u32> Size() { return mSize; }
	float AspectRatio() { return mAspectRatio; }

	operator SDL_GLContext() const { return mWinContext; }
	operator SDL_Window*() const { return mWindow_SDL; }

	void Resize(std::pair<u32, u32> newSize) { mSize = newSize; }

private:
	std::pair<u32, u32> mSize;
	SDL_Window* mWindow_SDL;
	SDL_GLContext mWinContext;
	float mAspectRatio;

	bool mbIsClosed = false;
};

class WindowManager
{
	Singleton(WindowManager);

public:
	void Initialize(const std::string& windowName);

	void SwapWindow();

	inline bool IsCurrentWindowClosed() { return mCurrentWindow->IsClosed(); }

public:
	std::shared_ptr<Window> mCurrentWindow;
};

#define WindowMgr WindowManager::Instance()