#include "Mason/Engine.hpp"

#include "Mason/SceneParser.hpp"
#include "Mason/Transform.h"
#include "Mason/Physics.hpp"
#include "Mason/ParticleEmitter.hpp"
#include "Mason/Time.hpp"
#include "Mason/SpriteRenderer.h"
#include "Mason/SpriteAtlas.h"
#include "Mason/LeakDetection.h"
#include "Mason/Camera.hpp"
#include "Mason/InputManager.h"
#include "Mason/Script.hpp"
#include "Mason/PhysicsBody2D.hpp"
#include "Mason/BoxCollider2D.hpp"
#include "Mason/CircleCollider2D.h"


#include <chrono>
#include <iostream>
#include <map>

#include <SDL_timer.h>
#include <SRE/Shader.hpp>
#include <SRE/SimpleRenderEngine.hpp>
#include <glm/glm.hpp>
#include <SDL.h>
#include <imgui.h>
#include <SRE/imgui_sre.hpp>

using namespace glm;
using namespace Mason;


bool show_another_window;
int numberSprites;

Engine::Engine()
{
	Config::init();
	Time::init(0);

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		throw SDL_GetError();
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	windowWidth = Config::getInt("window-width");
	windowHeight = Config::getInt("window-height");
	if (*windowWidth == 0) *windowWidth = 640;
	if (*windowHeight == 0) *windowHeight = 480;

	// Create an application window with the following settings:
	window = SDL_CreateWindow(
		"An SDL2 window",                  // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		*windowWidth,                               // width, in pixels
		*windowHeight,                               // height, in pixels
		SDL_WINDOW_OPENGL                  // flags - see below
	);

	SDL_SetWindowTitle(window, "Mason");

	if (window == nullptr) {
		printf("Could not create window: %s/n", SDL_GetError());
		throw "Error";
	}

	sre = new SRE::SimpleRenderEngine(window);
	physics = Physics::getInstance();
	audioManager = AudioManager::getInstance();

	srand(uint(time(nullptr)));

	//GUI
	showDebugGUI = false;
	ImGui_SRE_Init(window);
	show_another_window = true;

	running = paused = false;
	scene = new Scene();
}
Engine::~Engine()
{
	delete scene;
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Engine::start() {
	physics->init();

	typedef std::chrono::high_resolution_clock Clock;
	auto t1 = Clock::now();
	int timePerFrameMillis = 1000 / 60;
	running = true;

	while (running) {
		using namespace std::chrono;

		auto t2 = Clock::now();
		// time since last update
		long deltaTimeMicSec = long(duration_cast<microseconds>(t2 - t1).count());
		float deltaTimeSec = deltaTimeMicSec / 1000000.0f;

		// Set the time
		Time::instance->update(deltaTimeMicSec / 1000);

		// Update the engine
		update(deltaTimeSec);

		int updateTimeMillis = static_cast<int>(duration_cast<milliseconds>(Clock::now() - t2).count());
		int wait = timePerFrameMillis - updateTimeMillis;
		if (wait > 0) {
			SDL_Delay(wait);
		}
		t1 = t2;
	}
}

void Engine::loadScene(std::string path)
{
	delete scene;
	scene = new Scene();

	auto sceneDescriptor = SceneParser::parseFile(path);
	SDL_SetWindowTitle(window, sceneDescriptor.name.c_str());
	scene->imagepath = sceneDescriptor.imagepath;
	scene->soundpath = sceneDescriptor.soundpath;
	scene->templatepath = sceneDescriptor.templatepath;

	std::map<std::string, SpriteAtlas> map_spriteatlas;
	for (auto atlasname : sceneDescriptor.sprites)
	{
		SpriteAtlas atlas(sceneDescriptor.imagepath, atlasname + ".json");
		for (auto sprite : atlas.sprites)
			scene->sprites[sprite.first] = sprite.second;
	}

	auto gameObjectDescriptors = sceneDescriptor.gameobjects;
	for (auto element : gameObjectDescriptors) {
		scene->loadGameObject(element);
	}

	//Set up parent relationships between Transform components
	for (auto element : gameObjectDescriptors) {
		if (element.transform.parentId != -1) {
			scene->setParentRelationship(element.uniqueId, element.transform.parentId);			
		}
	}
}

void Engine::update(float deltaTimeSec) {
	sre->clearScreen({ 0,0,0,1 });
	numberSprites = 0;

	InputManager::getInstance()->Handle(this);

	if (!paused) {
		for (auto & script : scene->getAllComponent<Script>()) {
			if (!script->started) {
				script->started = true;
				script->OnStart();
			}
			script->OnUpdate();
		}

		// update particle emitters
		for (auto & particleEmitter : scene->getAllComponent<ParticleEmitter>()) {
			if (particleEmitter) {
				particleEmitter->update(deltaTimeSec);
			}
		}

		physics->step(deltaTimeSec);
		audioManager->step();
	}

	for (auto & camera : scene->getAllComponent<Camera>()) {

		sre->setCamera(camera->cam);

		// render sprites
		for (auto & sprite : scene->getAllComponent<SpriteRenderer>()) {
			if (sprite) {
				sprite->draw();
				numberSprites++;
			}
		}

		// render particle emitters
		for (auto & particleEmitter : scene->getAllComponent<ParticleEmitter>()) {
			if (particleEmitter) {				
				particleEmitter->render();
			}
		}

		physics->world.DrawDebugData();
	}

	if (showDebugGUI) DebugUI();
	sre->swapWindow();

}

void Engine::DebugUI()
{
	ImGui_SRE_NewFrame(this->window);

	ImGui::Begin("Game Debug GUI");
	{
		ImGui::Text("Number of models rendered : %i", numberSprites);
		if (ImGui::Button("Pause Game")) paused = !paused;
		if (ImGui::Button("Memory Stats")) show_another_window = !show_another_window;
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	}
	ImGui::End();

	if (show_another_window)
	{
		ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_FirstUseEver);
		ImGui::Begin("Memory Stats", &show_another_window);
		//memory stat
		LeakDetection leakd;
		int64_t totv = leakd.TotalVirtualMem();
		int64_t currv = leakd.CurrentVirtualMem();
		int64_t projectv = leakd.VirtualMemByCurrentProccess();
		ImGui::Text("Virtual Memory Used: %lld Mb (out of Total: %lld Mb)", currv, totv);
		ImGui::Text("Virtual Memory Used by the GE: %lld Mb", projectv);
		int64_t totp = leakd.TotalPhysMem();
		int64_t currp = leakd.CurrentPhysMem();
		int64_t projectp = leakd.PhysMemByCurrentProccess();
		ImGui::Text("Physical Memory Used: %lld Mb (out of Total: %lld Mb)", currp, totp);
		ImGui::Text("Physical Memory Used by the GE: %lld Mb", projectp);

		ImGui::End();
	}

	ImGui::Render();
}
