#pragma once

#include "Mason/Script.hpp"
#include "Mason/GameObject.hpp"
#include "Mason/Audio.hpp"

using namespace Mason;

class FNoteController : public Script {
public:
	static Script* Create(GameObject* gameObject)
	{
		return new FNoteController(gameObject);
	}
	void OnUpdate() override {

	}
	void OnInput(SDL_Event event) override {
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_f) gameObject->getComponent<Audio>()->play();
		}
	}
protected:
	FNoteController(GameObject* gameObject) : Script(gameObject)
	{
	}
	friend GameObject;
private:
};