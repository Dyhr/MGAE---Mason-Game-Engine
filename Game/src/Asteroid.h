#pragma once

#include "Mason/Script.hpp"
#include <random>

using namespace Mason;

class Asteroid :public Script
{
protected:
	Asteroid(std::shared_ptr<GameObject> gameObject) : Script(gameObject)
	{
	}
	friend GameObject;
public:
	static Script* Create(std::shared_ptr<GameObject> gameObject)
	{
		return new Asteroid(gameObject);
	}

	void OnCollisionEnter(GameObject* other) override
	{
		if (other->getName() == "Asteroid")
			Scene::Destroy(std::shared_ptr<GameObject>(getGameObject()));
	}
};
