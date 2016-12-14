
#include <Mason/Engine.hpp>
#include "Mason/ParticleEmitter.hpp"
#include "Mason/Script.hpp"
#include "AsteroidSpawner.h"

using namespace glm;
using namespace Mason;

int main(int argc, char** argv) {
	Engine e;

	Script::scripts["asteroid-spawner"] = AsteroidSpawner::Create;

	e.loadScene("data/game.json");
	e.start();

	return 0;
}
