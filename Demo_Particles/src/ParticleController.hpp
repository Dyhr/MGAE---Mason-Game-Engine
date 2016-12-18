#pragma once
#include "Mason/Script.hpp"
#include "Mason/ParticleEmitter.hpp"
#include <iostream>
#include "Mason/GUI.hpp"
#include "Mason/Scene.hpp"
#include "Mason/InputManager.h"

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
	void OnGUI() override {
		auto name = gameObject->getName();
		if (name == "FirePlant") {
			GUI::Label("Press 'M' to stop the fire plant. 'N' to start.");
		}
		else if (name == "RainCloud") {
			GUI::Label("Press 'O' to stop the rain cloud. 'I' to start.");
		}
		else if (name == "BallLauncher") {
			GUI::Label("Press 'U' to stop the ball pipe. 'Y' to start.");
		}
		else if (name == "RainbowMario") {
			GUI::Label("Press 'L' to stop the rainbow. 'K' to start.");
			GUI::Label("Use 'W', 'A', 'S', 'D' to move the camera");
		}
			
	}
 	void OnInput(SDL_Event event) override {
		if (event.type == SDL_KEYDOWN)
		{
			if (char(event.key.keysym.sym == strings["stop"][0])) emitter->stop();
			if (char(event.key.keysym.sym == strings["start"][0])) emitter->start();
		}
	}
};