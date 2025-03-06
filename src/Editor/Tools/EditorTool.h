#pragma once

#include "imgui/imgui.h"

struct EditorTool
{
	virtual void Initialize() {}
	virtual void Update() {}
	virtual void Shutdown() {}

	void Enable() { mbIsEnabled = true; }
	bool IsEnabled() { return mbIsEnabled; }

protected:
	bool mbIsEnabled;
};