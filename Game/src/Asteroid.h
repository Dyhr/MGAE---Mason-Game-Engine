#pragma once

#include "Mason/Script.hpp"
#include <random>

using namespace Mason;

class Asteroid :public Script
{
protected:
	Asteroid(GameObject* gameObject) : Script(gameObject)
	{
	}
	friend GameObject;
public:
	static Script* Create(GameObject* gameObject)
	{
		return new Asteroid(gameObject);
	}

	void OnCollisionEnter(GameObject* other) override
	{
	}
};
