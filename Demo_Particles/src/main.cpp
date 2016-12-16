
#include <Mason/Engine.hpp>
#include "CameraController.hpp"
#include "ParticleController.hpp"

using namespace glm;
using namespace Mason;

Engine engine;

int main(int argc, char** argv) {
	
	Script::scripts["camera-controller"] = CameraController::Create;
	Script::scripts["particle-controller"] = ParticleController::Create;

	engine.loadScene("data/demoParticles.json");
	
	engine.start();
	
	return 0;
}
