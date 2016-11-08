#pragma once
#include "Script.hpp"

class PlayerController :public Script
{
protected:
	PlayerController(GameObject* gameObject) : Script(gameObject)
	{
	}

public:
	void OnUpdate() override
	{
		auto pos = transform->getPosition();
		pos.x += direction * speed * Time::getInstance()->getDeltaTime();
	}

	void OnInput(SDL_Event event) override
	{
		if(event.type == SDL_KEYDOWN)
		{
			
		}
	}

	int direction = 1;
	int speed = 5;
};
