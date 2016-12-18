#pragma once

#include "Mason/Script.hpp"
#include "Mason/Time.hpp"
#include <iostream>
#include "Mason/InputManager.h"

using namespace Mason;

class CameraController :public Script
{
protected:
	CameraController(std::shared_ptr<GameObject> gameObject) : Script(gameObject)
	{
	}

	friend GameObject;

public:
	static Script* Create(std::shared_ptr<GameObject> gameObject)
	{
		return new CameraController(gameObject);
	}
	void OnUpdate() override
	{
		directionX = rightDown - leftDown;
		directionY = upDown - downDown;

		auto pos = transform->getPosition();
		pos.x += directionX * speed * Time::getDeltaTime();
		pos.y += directionY * speed * Time::getDeltaTime();
		transform->setPosition(pos);
	}

	void OnInput(SDL_Event event) override
	{
		if(event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_a) leftDown = 1;
			if (event.key.keysym.sym == SDLK_d) rightDown = 1;
			if (event.key.keysym.sym == SDLK_w) upDown = 1;
			if (event.key.keysym.sym == SDLK_s) downDown = 1;
		}
		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_a) leftDown = 0;
			if (event.key.keysym.sym == SDLK_d) rightDown = 0;
			if (event.key.keysym.sym == SDLK_w) upDown = 0;
			if (event.key.keysym.sym == SDLK_s) downDown = 0;
		}
	}

	int leftDown = 0;
	int rightDown = 0;
	int downDown = 0;
	int upDown = 0;
	int directionX = 0;
	int directionY = 0;
	float speed = 100.0f;
};
