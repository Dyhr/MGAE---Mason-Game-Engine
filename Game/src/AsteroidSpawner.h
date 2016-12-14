#pragma once

#include "Mason/Script.hpp"

#include <iostream>

using namespace Mason;

class AsteroidSpawner :public Script
{
protected:
	AsteroidSpawner(GameObject* gameObject) : Script(gameObject)
	{
	}

	friend GameObject;

public:
	static Script* Create(GameObject* gameObject)
	{
		return new AsteroidSpawner(gameObject);
	}

	void OnStart() override
	{
		std::cout << "Asteroid spawned: " << numbers["amount"] << std::endl;
	}

};
