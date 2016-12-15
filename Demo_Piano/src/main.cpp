
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
	
	
	Script::scripts["a-note-controller"] =			ANoteController::Create;
	Script::scripts["a-sharp-note-controller"] =	ASharpNoteController::Create;
	Script::scripts["b-note-controller"] =			BNoteController::Create;
	Script::scripts["c-note-controller"] =			CNoteController::Create;
	Script::scripts["c-next-note-controller"] =		CNextNoteController::Create;
	Script::scripts["c-sharp-note-controller"] =	CSharpNoteController::Create;
	Script::scripts["d-note-controller"] =			DNoteController::Create;
	Script::scripts["d-sharp-note-controller"] =	DSharpNoteController::Create;
	Script::scripts["e-note-controller"] =			ENoteController::Create;
	Script::scripts["f-note-controller"] =			FNoteController::Create;
	Script::scripts["f-sharp-note-controller"] =	FSharpNoteController::Create;
	Script::scripts["g-note-controller"] =			GNoteController::Create;
	Script::scripts["g-sharp-note-controller"] =	GSharpNoteController::Create;

	engine.loadScene("data/demoPiano.json");

	engine.start();

	return 0;
}
