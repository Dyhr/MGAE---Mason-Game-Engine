
#include <Mason/Engine.hpp>
#include <Mason/ParticleEmitter.hpp>
#include <Mason/Script.hpp>

#include "AsteroidSpawner.h"
#include "Player.h"
#include "Asteroid.h"

using namespace glm;
using namespace Mason;

int main(int argc, char** argv) {
	Engine e;

	Script::scripts["asteroid-spawner"] = AsteroidSpawner::Create;
	Script::scripts["player"] = Player::Create;
	Script::scripts["bullet"] = Bullet::Create;

	e.loadScene("data/game.json");
	e.start();

	return 0;
}
