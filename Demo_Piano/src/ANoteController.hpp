#pragma once

#include "Mason/Script.hpp"
#include "Mason/GameObject.hpp"
#include "Mason/Audio.hpp"
#include "Mason/GUI.hpp"

using namespace Mason;

class ANoteController : public Script { 
public:
	static Script* Create(std::shared_ptr<GameObject> gameObject)
	{
		return new ANoteController(gameObject);
	}

	void OnUpdate() override {

	}
	void OnInput(SDL_Event event) override {
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_h) gameObject->getComponent<Audio>()->play();
		}
	}
	void OnGUI() override {		
		GUI::Label("Play the 1-octave-Piano!");
		GUI::Label("Major keys are: a, s, d, f, g, h, j, k");
		GUI::Label("Sharp keys are: w, e, t, y, u");

	}
protected:
	ANoteController(std::shared_ptr<GameObject> gameObject) : Script(gameObject)
	{
	}
	friend GameObject;
private:
};