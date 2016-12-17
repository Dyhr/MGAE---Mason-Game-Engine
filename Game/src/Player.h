#pragma once

#include "Mason/Script.hpp"
#include "Mason/Scene.hpp"
#include <memory>
#include <random>
#include <time.h>
#include "Mason/PhysicsBody2D.hpp"

#include "Box2D/Box2D.h"

using namespace Mason;

class Player :public Script
{
protected:
	Player(std::shared_ptr<GameObject> gameObject) : Script(gameObject)
	{
	}
	friend GameObject;
public:
	static Script* Create(std::shared_ptr<GameObject> gameObject)
	{
		return new Player(gameObject);
	}

	bool thrust = false;
	bool turnLeft = false;
	bool turnRight = false;

	void Shoot()
	{
		auto body = getGameObject()->getComponent<PhysicsBody2D>()->body;
		auto x = cos(transform->getRotation() * M_PI / 180);
		auto y = sin(transform->getRotation() * M_PI / 180);

		auto bullet = Scene::Instantiate("bullet");
		bullet->getTransform()->setPosition(transform->getPosition() + glm::vec3(-y, x, 0)*20.0f);

		bullet->getComponent<PhysicsBody2D>()->body->ApplyForceToCenter(b2Vec2(-y * 80, x * 80) + body->GetLinearVelocity(), true);
	}

	void OnUpdate() override 
	{
		auto body = getGameObject()->getComponent<PhysicsBody2D>()->body;
		auto x = cos(transform->getRotation() * M_PI / 180);
		auto y = sin(transform->getRotation() * M_PI / 180);

		if (thrust)
			body->ApplyForceToCenter(b2Vec2(-y * 50, x * 50), true);
		if (turnLeft && !turnRight)
			body->ApplyTorque(50, false);
		if (turnRight && !turnLeft)
			body->ApplyTorque(-50, false);
	}

	void OnInput(SDL_Event e) override
	{
		if (e.type == SDL_KEYDOWN && char(e.key.keysym.sym) == strings["shoot"][0]) Shoot();

		if(char(e.key.keysym.sym) == strings["thrust"][0])
		{
			if (e.type == SDL_KEYDOWN) thrust = true;
			if (e.type == SDL_KEYUP) thrust = false;
		}
		if (char(e.key.keysym.sym) == strings["left"][0])
		{
			if (e.type == SDL_KEYDOWN) turnLeft = true;
			if (e.type == SDL_KEYUP) turnLeft = false;
		}
		if (char(e.key.keysym.sym) == strings["right"][0])
		{
			if (e.type == SDL_KEYDOWN) turnRight = true;
			if (e.type == SDL_KEYUP) turnRight = false;
		}
	}
};
