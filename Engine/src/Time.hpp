#pragma once

class Engine;

class Time
{
public:
	static float getTime()
	{
		return float(time) / 1000;
	}
	static float getDeltaTiem()
	{
		return delta;
	}
private:
	static int time;
	static int delta;
	static void update(int delta)
	{
		Time::time += delta;
		Time::delta = delta;
	}
	friend Engine;
};
