#pragma once

class Engine;

class Time
{
public:
	static float getTime()
	{
		return float(instance->time) / 1000;
	}
	static float getDeltaTime()
	{
		return instance->delta;
	}
private:
	static Time* instance;
	int time = 0;
	int delta = 0;

	static void update(int delta)
	{
		if (instance == nullptr) instance = new Time();

		instance->time += delta;
		instance->delta = delta;
	}

	friend Engine;
};
