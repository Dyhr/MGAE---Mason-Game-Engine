#pragma once

#include "Mason/Script.hpp"
#include "Mason/Scene.hpp"
#include <glm/glm.hpp>
#include <memory>
#include <random>
#include <vector>
#include <time.h>

#include <iostream>

using namespace Mason;

class AsteroidSpawner :public Script
{
protected:
	AsteroidSpawner(std::shared_ptr<GameObject> gameObject) : Script(gameObject)
	{
	}

	friend GameObject;
private:
	glm::vec3 GetRandomPosition(glm::vec2 min, glm::vec2 max) {

		return glm::vec3(randf(min.x, max.x), randf(min.y, max.y), 0);
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

	std::vector<std::shared_ptr<GameObject>> asteroids;
public:
	static Script* Create(std::shared_ptr<GameObject> gameObject)
	{
		return new AsteroidSpawner(gameObject);
	}

	void OnStart() override
	{
		for (int i = 0; i < numbers["amountBig"]; i++) {
			auto asteroid = Scene::Instantiate("asteroid_big");
			asteroid->getTransform()->setPosition(glm::vec3(
				randf(-numbers["rangeX"], numbers["rangeX"]),
				randf(-numbers["rangeY"], numbers["rangeY"]),
				0));
			asteroid->getTransform()->setRotation(randf(0,360));
			asteroids.push_back(asteroid);
		}
		for (int i = 0; i < numbers["amountMedium"]; i++) {
			auto asteroid = Scene::Instantiate("asteroid_medium");
			asteroid->getTransform()->setPosition(glm::vec3(
				randf(-numbers["rangeX"], numbers["rangeX"]),
				randf(-numbers["rangeY"], numbers["rangeY"]),
				0));
			asteroid->getTransform()->setRotation(randf(0, 360));
			asteroids.push_back(asteroid);
		}
		for (int i = 0; i < numbers["amountSmall"]; i++) {
			auto asteroid = Scene::Instantiate("asteroid_small");
			asteroid->getTransform()->setPosition(glm::vec3(
				randf(-numbers["rangeX"], numbers["rangeX"]),
				randf(-numbers["rangeY"], numbers["rangeY"]),
				0));
			asteroid->getTransform()->setRotation(randf(0, 360));
			asteroids.push_back(asteroid);
		}
		std::cout << "Asteroid spawned: " << numbers["amountBig"]+ numbers["amountMedium"]+ numbers["amountSmall"] << std::endl;
	}
};
