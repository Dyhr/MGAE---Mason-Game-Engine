
#include <Mason/Engine.hpp>
#include "Mason/InputManager.h"
#include "ANoteController.hpp"
#include "ASharpNoteController.hpp"
#include "BNoteController.hpp"
#include "CNoteController.hpp"
#include "CSharpNoteController.hpp"
#include "DNoteController.hpp"
#include "DSharpNoteController.hpp"
#include "ENoteController.hpp"
#include "FNoteController.hpp"
#include "FSharpNoteController.hpp"
#include "GNoteController.hpp"
#include "GSharpNoteController.hpp"
#include "CNextNoteController.hpp" 

using namespace glm;
using namespace Mason;

Engine engine;

int main(int argc, char** argv) {
	
	engine.loadScene("data/demoPiano.json");		
	engine.scene->getGameObject(1)->addComponent<ANoteController>();
	engine.scene->getGameObject(2)->addComponent<ASharpNoteController>();
	engine.scene->getGameObject(3)->addComponent<BNoteController>();
	engine.scene->getGameObject(4)->addComponent<CNoteController>();
	engine.scene->getGameObject(5)->addComponent<CSharpNoteController>();
	engine.scene->getGameObject(6)->addComponent<DNoteController>();
	engine.scene->getGameObject(7)->addComponent<DSharpNoteController>();
	engine.scene->getGameObject(8)->addComponent<ENoteController>();
	engine.scene->getGameObject(9)->addComponent<FNoteController>();
	engine.scene->getGameObject(10)->addComponent<FSharpNoteController>();
	engine.scene->getGameObject(11)->addComponent<GNoteController>();
	engine.scene->getGameObject(12)->addComponent<GSharpNoteController>();
	engine.scene->getGameObject(13)->addComponent<CNextNoteController>();

	engine.start();

	return 0;
}
