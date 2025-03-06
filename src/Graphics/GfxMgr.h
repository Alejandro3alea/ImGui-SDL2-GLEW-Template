#pragma once
#include "Misc/Singleton.h"
#include "Misc/DataTypes.h"

class GraphicsManager
{
	Singleton(GraphicsManager);

public:
	void Initialize();
	void Render();
	void Shutdown();

	void SetClearColor(const f32 r, const f32 g, const f32 b);
	void ClearBuffer();
};

#define GfxMgr GraphicsManager::Instance()