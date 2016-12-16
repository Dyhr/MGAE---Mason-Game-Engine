#pragma once

#include "Mason/Script.hpp"
#include "Mason/GameObject.hpp"
#include "Mason/Audio.hpp"

using namespace Mason;

class DSharpNoteController : public Script {
public:
	static Script* Create(std::shared_ptr<GameObject> gameObject)
	{
		return new DSharpNoteController(gameObject);
	}
	void OnUpdate() override {

	}
	void OnInput(SDL_Event event) override {
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_e) gameObject->getComponent<Audio>()->play();
		}
	}
protected:
	DSharpNoteController(std::shared_ptr<GameObject> gameObject) : Script(gameObject)
	{
	}
	friend GameObject;
private:
};