#pragma once
#include "Misc/DataTypes.h"

#include <string>

namespace ImGui
{
	bool OnGui(const std::string& label, bool& val);
	bool OnGui(const std::string& label, int& val, const int min = 0, const int max = 5000);
	bool OnGui(const std::string& label, unsigned& val, const unsigned min = 0, const unsigned max = 5000);
	bool OnGui(const std::string& label, short& val);
	bool OnGui(const std::string& label, long& val);
	bool OnGui(const std::string& label, float& val, const float rate = 0.01f, const float min = -F32_MAX, const float max = F32_MAX);
	bool OnGui(const std::string& label, double& val);

	bool OnGui(const std::string& label, std::string& val);
}