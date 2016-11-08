#include "Time.hpp"

Time* Time::instance = nullptr;

Time* Time::getInstance()
{
	if (instance == nullptr) instance = new Time();
	return instance;
}

float Time::getTime() const
{
	return float(time) / 1000;
}
float Time::getDeltaTime() const
{
	return float(delta) / 1000;
}

void Time::update(int delta)
{

	this->time += delta;
	this->delta = delta;
}
