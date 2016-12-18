#include <Mason/Engine.hpp>
#include "Mason/ParticleEmitter.hpp"
#include "Mason/InputManager.h"
#include "CameraController.hpp"
#include "ParticleController.hpp"

using namespace glm;
using namespace Mason;


int main(int argc, char** argv) {


	Engine e;
	Script::scripts["camera-controller"] = CameraController::Create;
	Script::scripts["particle-controller"] = ParticleController::Create;

	e.loadScene("data/demoparticles.json");
	e.start();

	return 0;
}
