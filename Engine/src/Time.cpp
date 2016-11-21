#include "Mason/Time.hpp"

using namespace Mason;

Time* Time::instance = nullptr;

float Time::getTime()
{
	return float(instance->time) / 1000;
}
float Time::getDeltaTime()
{
	return float(instance->delta) / 1000;
}

void Time::init(long time)
{
	if (instance != nullptr) throw "Error: Multiple Times started.";
	instance = new Time();
	instance->time = time;
	instance->delta = 0;
}

void Time::update(int delta)
{
	this->time += delta;
	this->delta = delta;
}
