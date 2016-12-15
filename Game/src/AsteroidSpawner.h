#pragma once

#include "Mason/Script.hpp"
#include "Mason/Scene.hpp"
#include "Mason/CircleCollider2D.h"
#include "Mason/Sprite.h"
#include <glm/glm.hpp>
#include <memory>
#include <random>
#include <vector>
#include <time.h>
#include "Mason/SceneParser.hpp"

#include <iostream>

using namespace Mason;

class AsteroidSpawner :public Script
{
protected:
	AsteroidSpawner(GameObject* gameObject) : Script(gameObject)
	{
	}

	friend GameObject;
private: 
	glm::vec3 GetRandomPosition(glm::vec2 min, glm::vec2 max) {
		
		return glm::vec3(randf(min.x, max.x), randf(min.y, max.y), 0);
	}

	float randf(float min, float max) {
		if (!randomSeeded) {
			srand(time(nullptr));
			randomSeeded = true;
		}
		auto res = min + static_cast <float> (rand()) / static_cast <float> (RAND_MAX / (max - min));
		return res;
	}
	bool randomSeeded = false;

	std::vector<std::shared_ptr<GameObject>> asteroids;
public:
	static Script* Create(GameObject* gameObject)
	{
		return new AsteroidSpawner(gameObject);
	}

	void OnStart() override
	{
		auto desc = SceneParser::parseObjectFromJSON("data/asteroid.json");
		auto name = desc.name;
		auto id = desc.uniqueId;
		for (int i = 0; i < numbers["amount"]; i++) {			
			desc.name = name + " " + std::to_string(i);
			desc.uniqueId = id + i;
			desc.transform.position.x = randf(-600, -600);
			desc.transform.position.y = randf(-100, 100);
			asteroids.push_back(Scene::Instantiate(desc));
		}
		std::cout << "Asteroid spawned: " << numbers["amount"] << std::endl;
	}
};
