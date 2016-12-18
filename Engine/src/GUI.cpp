#include "Mason/GUI.hpp"
#include <SRE/imgui_sre.hpp>

using namespace Mason;

bool GUI::Button(std::string text)
{
	if (!ready) throw "GUI function called outside of OnGUI()";
	return ImGui::Button(text.c_str());
}
void GUI::Label(std::string text)
{
	if (!ready) throw "GUI function called outside of OnGUI()";
	ImGui::Text(text.c_str());
}

bool GUI::ready = false;
