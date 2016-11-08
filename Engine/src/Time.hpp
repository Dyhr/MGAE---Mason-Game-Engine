#pragma once

class Engine;

class Time
{
public:
	static Time* Time::getInstance();

	float getTime() const;
	float getDeltaTime() const;
private:
	static Time* instance;

	int time = 0;
	int delta = 0;

	void update(int delta);

	friend Engine;
};