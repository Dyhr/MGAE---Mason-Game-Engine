#pragma once

#include "Mason/Script.hpp"
#include <random>

using namespace Mason;

class Bullet :public Script
{
protected:
	Bullet(std::shared_ptr<GameObject> gameObject) : Script(gameObject)
	{
	}
	friend GameObject;
public:
	static Script* Create(std::shared_ptr<GameObject> gameObject)
	{
		return new Bullet(gameObject);
	}

	void OnCollisionEnter(GameObject* other) override
	{
		Scene::Destroy(getGameObject());
		if (other->getName() == "Asteroid") {
			Scene::Destroy(other);
		}
		else if (other->getName() == "Player")
		{
			Scene::Destroy(other);
		}
	}
};
