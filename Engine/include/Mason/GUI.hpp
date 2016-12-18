#pragma once
#include <vector>

namespace Mason {
	class GUI
	{
	public:
		static void Label(std::string text);
		static bool Button(std::string text);

	private:
		static bool ready;

		friend class Engine;
	};
}
