#pragma once

#include "Mason/Script.hpp"
#include "Mason/GameObject.hpp"
#include "Mason/Audio.hpp"

using namespace Mason;

class GSharpNoteController : public Script {
public:
	static Script* Create(GameObject* gameObject)
	{
		return new GSharpNoteController(gameObject);
	}
	void OnUpdate() override {

	}
	void OnInput(SDL_Event event) override {
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_y) gameObject->getComponent<Audio>()->play();
		}
	}
protected:
	GSharpNoteController(GameObject* gameObject) : Script(gameObject)
	{
	}
	friend GameObject;
private:
};