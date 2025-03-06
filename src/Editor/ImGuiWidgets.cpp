#include "ImGuiWidgets.h"
#include "Editor.h"

#include <functional>

namespace ImGui
{
	const unsigned MaxCharCount = 256;


	bool OnGuiBase(const bool check, const std::function<void()>& then)
	{
		bool changed = false;
		if (check)
		{
			changed = true;
			then();
		}

		return changed;
	}

	bool OnGui(const std::string& label, bool& val)
	{
		return OnGuiBase(ImGui::Checkbox((label).c_str(), &val), []() {});
	}

	bool OnGui(const std::string& label, int& val, const int min, const int max)
	{
		return OnGuiBase(ImGui::SliderInt((label).c_str(), &val, min, max), []() {});
	}

	bool OnGui(const std::string& label, unsigned& val, const unsigned min, const unsigned max)
	{
		int intVal = static_cast<int>(val);
		return OnGuiBase(ImGui::SliderInt((label).c_str(), &intVal, min, max), [&val, intVal]()
		{
			val = static_cast<unsigned>(intVal);
		});
	}

	bool OnGui(const std::string& label, short& val)
	{
		int intVal = static_cast<int>(val);
		return OnGuiBase(ImGui::SliderInt((label).c_str(), &intVal, 0, 5000), [&val, intVal]()
			{
				val = static_cast<short>(intVal);
			});
	}

	bool OnGui(const std::string& label, long& val)
	{
		int intVal = static_cast<int>(val);
		return OnGuiBase(ImGui::SliderInt((label).c_str(), &intVal, 0, 5000), [&val, intVal]()
			{
				val = static_cast<unsigned>(intVal);
			});
	}

	bool OnGui(const std::string& label, float& val, const float rate, const float min, const float max)
	{
		return OnGuiBase(ImGui::DragFloat((label).c_str(), &val, rate, min, max), []() {});
	}

	bool OnGui(const std::string& label, double& val)
	{
		return OnGuiBase(ImGui::InputDouble((label).c_str(), &val), []() {});
	}

	bool OnGui(const std::string& label, std::string& val)
	{
		char c[MaxCharCount];
		for (unsigned i = 0; i < val.size(); i++)
			c[i] = val[i];
		c[val.size()] = '\0';
		return OnGuiBase(ImGui::InputText((label).c_str(), c, MaxCharCount), [&val, c]() { val = std::string(c); });
	}
}