#pragma once

namespace Mason {
	class Engine;

	class Time
	{
	public:
		static float getTime();
		static float getDeltaTime();
	private:
		static Time* instance;

		long time = 0;
		int delta = 0;

		static void init(long time);
		void update(int delta);

		friend Engine;
	};
}
