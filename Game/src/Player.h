#pragma once

#include "Mason/Script.hpp"
#include "Mason/Scene.hpp"
#include <memory>
#include <random>
#include <time.h>
#include "Mason/SceneParser.hpp"

using namespace Mason;

class Player :public Script
{
protected:
	Player(GameObject* gameObject) : Script(gameObject)
	{
	}
	friend GameObject;
public:
	static Script* Create(GameObject* gameObject)
	{
		return new Player(gameObject);
	}

	void OnInput(SDL_Event e) override
	{
	}
};
