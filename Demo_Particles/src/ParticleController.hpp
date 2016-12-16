#pragma once
#include "Mason/Script.hpp"
#include "Mason/ParticleEmitter.hpp"
#include <iostream>

using namespace Mason;

class ParticleController : public Script {
protected:
	ParticleController(GameObject* go) : Script(go) {

	}
	friend GameObject;
	std::shared_ptr<ParticleEmitter> emitter;
public:
	static Script* Create(GameObject* gameObject)
	{
		return new ParticleController(gameObject);
	}

	void OnStart() override {
		emitter = gameObject->getComponent<ParticleEmitter>();
	}
 	void OnInput(SDL_Event event) override {
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_n) emitter->stop();
			if (event.key.keysym.sym == SDLK_m) emitter->start();
		}
	}
};