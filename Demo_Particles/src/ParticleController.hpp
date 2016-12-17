#pragma once
#include "Mason/Script.hpp"
#include "Mason/ParticleEmitter.hpp"
#include <iostream>

using namespace Mason;

class ParticleController : public Script {
protected:
	ParticleController(std::shared_ptr<GameObject> go) : Script(go) {

	}
	friend GameObject;
	ParticleEmitter* emitter;
public:
	static Script* Create(std::shared_ptr<GameObject> gameObject)
	{
		return new ParticleController(gameObject);
	}

	void OnStart() override {
		emitter = gameObject->getComponent<ParticleEmitter>();

	}
 	void OnInput(SDL_Event event) override {
		if (event.type == SDL_KEYDOWN)
		{
			if (char(event.key.keysym.sym == strings["stop"][0])) emitter->stop();
			if (char(event.key.keysym.sym == strings["start"][0])) emitter->start();
		}
	}
};