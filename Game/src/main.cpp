
#include <Mason/Engine.hpp>
#include "Mason/ParticleEmitter.hpp"

using namespace glm;
using namespace Mason;

int main(int argc, char** argv) {
	Engine e;

	e.loadScene("data/game.json");
	e.start();

	return 0;
}
