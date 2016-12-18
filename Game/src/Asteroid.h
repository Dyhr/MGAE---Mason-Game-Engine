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

	float randf(float min, float max) {
		if (!randomSeeded) {
			srand(int(time(nullptr)));
			randomSeeded = true;
		}
		auto res = min + static_cast <float> (rand()) / static_cast <float> (RAND_MAX / (max - min));
		return res;
	}
	bool randomSeeded = false;

	friend GameObject;
public:
	static Script* Create(std::shared_ptr<GameObject> gameObject)
	{
		return new Bullet(gameObject);
	}

	void OnCollisionEnter(GameObject* other) override
	{
		Scene::Destroy(getGameObject());
		if (other->getName().find("Asteroid") != std::string::npos) {
			other->getComponent<Audio>()->play();

			if(other->getName() == "Asteroid Big") {
				auto asteroid1 = Scene::Instantiate("asteroid_medium");
				auto asteroid2 = Scene::Instantiate("asteroid_medium");
				asteroid1->getTransform()->setPosition(other->getTransform()->getPosition());
				asteroid2->getTransform()->setPosition(other->getTransform()->getPosition());
				auto v = b2Vec2(randf(-1, 1)*100, randf(-1, 1)*100);
				asteroid1->getComponent<PhysicsBody2D>()->body->ApplyForceToCenter(v, true);
				asteroid2->getComponent<PhysicsBody2D>()->body->ApplyForceToCenter(b2Vec2(-v.x,-v.y), true);
			}
			if (other->getName() == "Asteroid Medium") {
				auto asteroid1 = Scene::Instantiate("asteroid_small");
				auto asteroid2 = Scene::Instantiate("asteroid_small");
				asteroid1->getTransform()->setPosition(other->getTransform()->getPosition());
				asteroid2->getTransform()->setPosition(other->getTransform()->getPosition());
				auto v = b2Vec2(randf(-1, 1) * 100, randf(-1, 1) * 100);
				asteroid1->getComponent<PhysicsBody2D>()->body->ApplyForceToCenter(v, true);
				asteroid2->getComponent<PhysicsBody2D>()->body->ApplyForceToCenter(b2Vec2(-v.x, -v.y), true);
			}
			Scene::Destroy(other);
		} else if (other->getName().find("Player") != std::string::npos){
			getGameObject()->getComponent<Audio>()->play();
			Scene::Destroy(other);
		}
	}
};
