
#include <Mason/Engine.hpp>
#include "Mason/InputManager.h"
#include "PlayerController.hpp"

using namespace glm;
using namespace Mason;

Engine engine;

int main(int argc, char** argv) {
	
	engine.loadScene("data/demoParticles.json");
	engine.scene->getGameObject(0)->addComponent<PlayerController>();
	engine.start();
	
	return 0;
}
