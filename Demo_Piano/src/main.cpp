
#include <Mason/Engine.hpp>
#include "Mason/InputManager.h"
#include "ANoteController.hpp"
#include "BNoteController.hpp"
#include "CNoteController.hpp"
#include "DNoteController.hpp"
#include "ENoteController.hpp"
#include "FNoteController.hpp"
#include "GNoteController.hpp"

using namespace glm;
using namespace Mason;

Engine engine;

int main(int argc, char** argv) {
	
	engine.loadScene("data/demoPiano.json");
	engine.scene->getGameObject(1)->addComponent<ANoteController>();
	engine.scene->getGameObject(2)->addComponent<BNoteController>();
	engine.scene->getGameObject(3)->addComponent<CNoteController>();
	engine.scene->getGameObject(4)->addComponent<DNoteController>();
	engine.scene->getGameObject(5)->addComponent<ENoteController>();
	engine.scene->getGameObject(6)->addComponent<FNoteController>();
	engine.scene->getGameObject(7)->addComponent<GNoteController>();
	engine.start();

	return 0;
}
