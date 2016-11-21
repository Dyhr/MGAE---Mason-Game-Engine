#include "Mason/Engine.hpp"

#include "Mason/SceneParser.hpp"
#include "Mason/Transform.h"
#include "Mason/Rendering.h"
#include "Mason/Physics.hpp"
#include "Mason/ParticleEmitter.hpp"
#include "Mason/Script.hpp"
#include "Mason/Time.hpp"
#include "Mason/PlayerController.hpp"
#include "Mason/SpriteRenderer.h"
#include "Mason/SpriteAtlas.h"
#include "Mason/LeakDetection.h"
#include "Mason/Camera.hpp"
#include "Mason/InputManager.h"

#include <chrono>
#include <iostream>
#include <SDL_timer.h>
#include <SRE/Mesh.hpp>
#include <SRE/Shader.hpp>
#include <SRE/SimpleRenderEngine.hpp>
#include <glm/glm.hpp>
#include <SDL.h>
#include <map>
#include <imgui.h>
#include "SRE/imgui_sre.hpp"

using namespace glm;
using namespace Mason;


ImVec4 clear_color;
bool show_another_window;
int numberSprites;

Engine::Engine()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		throw SDL_GetError();
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	int width = 640;
	int height = 480;

	// Create an application window with the following settings:
	window = SDL_CreateWindow(
		"An SDL2 window",                  // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		width,                               // width, in pixels
		height,                               // height, in pixels
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
	ImGui_SRE_Init(window);
	show_another_window = true;
	clear_color = ImColor(114, 144, 154);

	Time::init(0);
	running = paused = false;
}
Engine::~Engine()
{
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
	std::map<int, std::shared_ptr<GameObject>> map_gameObjects;

	std::vector<GameObjectDescriptor> gameObjectDescriptors = SceneParser::parseFile(path);

	SpriteAtlas atlas("data/", "data/MarioPacked.json"); // TODO asset pipeline
	SRE::Shader* shader = SRE::Shader::getStandard();
	auto cubeMesh = SRE::Mesh::createCube();
	auto planeMesh = SRE::Mesh::createQuad();
	auto sphereMesh = SRE::Mesh::createSphere();
	for (auto element : gameObjectDescriptors) {

		auto gameObject = scene.addGameObject(element.name);

		if (element.camera.found)
		{
			auto camera = gameObject->addComponent<Camera>();

			camera->setPosition(element.transform.position);
			camera->setRotation(element.transform.rotationEuler);
			camera->setScale(element.transform.scale);

			camera->setPerspectiveProjection(element.camera.fieldOfView, 640, 480, element.camera.nearClip, element.camera.farClip);
			camera->lookAt(vec3(0, 0, 0), vec3(0, 1, 0));

			gameObject->addComponent<PlayerController>();
		}
		else {
			auto transformComponent = gameObject->addComponent<Transform>();
			transformComponent->setPosition(element.transform.position);
			transformComponent->setRotation(element.transform.rotationEuler);
			transformComponent->setScale(element.transform.scale);
		}

		if (element.mesh.found) {
			SRE::Mesh* mesh;
			if (element.mesh.name == "sphere")
				mesh = sphereMesh;
			else if (element.mesh.name == "cube")
				mesh = cubeMesh;
			else if (element.mesh.name == "plane")
				mesh = planeMesh;
			else
				throw "Undefined mesh";

			auto renderingComponent = gameObject->addComponent<Rendering>();

			renderingComponent->loadMesh(std::make_shared<SRE::Mesh>(*mesh));
			renderingComponent->loadShader(std::make_shared<SRE::Shader>(*shader));
			renderingComponent->setColor(element.mesh.color);
		}

		if (element.sprite.found)
		{
			auto sprite = gameObject->addComponent<SpriteRenderer>();
			sprite->sprite = atlas.getSprite(element.sprite.name);
			// TODO support changing color of sprite
		}

		map_gameObjects[element.uniqueId] = gameObject;
	}


	//Set up parent relationships between Transform components
	for (auto element : gameObjectDescriptors) {
		if (element.transform.parentId != -1) {
			auto gameObject = map_gameObjects[element.uniqueId];
			auto parentGameObject = map_gameObjects[element.transform.parentId];
			gameObject->getComponent<Transform>()->setParent(parentGameObject->getComponent<Transform>().get());
		}
	}
}

void Engine::update(float deltaTimeSec) {
	sre->clearScreen({ 0,0,1,1 });

	// fetch input
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			InputManager::getInstance()->KeyDown(event);
		case SDL_KEYUP:
		case SDL_MOUSEMOTION:
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEWHEEL:
			for (auto & script : scene.getAllComponent<Script>())
				if (script) script->OnInput(event);
			break;
		case SDL_QUIT:
			running = false;
			break;
		default: break;
		}
	}

	if (!paused) {
		physics->step(deltaTimeSec);
		audioManager->step();
	}

	for (auto & camera : scene.getAllComponent<Camera>()) {

		sre->setCamera(camera->cam);

		// render game object
		for (auto & rendering : scene.getAllComponent<Rendering>()) {
			if (rendering) {
				rendering->draw();
				numberSprites++;
			}
		}

		// render sprites
		for (auto & sprite : scene.getAllComponent<SpriteRenderer>()) {
			if (sprite) {
				sprite->draw();
				numberSprites++;
			}
		}

		// update and render particle emitters
		for (auto & particleEmitter : scene.getAllComponent<ParticleEmitter>()) {
			if (particleEmitter) {
				particleEmitter->update();
			}
		}
		ParticleEmitter::render();
	}

	sre->swapWindow();
}

void Engine::DebugUI()
{
	ImGui_SRE_NewFrame(this->window);
	ImGui::Begin("Game Debug GUI");
	// 1. Show a simple window
	// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
	{
		static float f = 0.0f;
		ImGui::Text("Number of models rendered : %i", numberSprites);
		//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		if (ImGui::Button("Pause Game")) {
			paused = !paused;
		}
		//ImGui::ColorEdit3("clear color", (float*)&clear_color);
		if (ImGui::Button("Memory Stats")) show_another_window ^= 1;
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	}
	ImGui::End();

	// 2. Show another simple window, this time using an explicit Begin/End pair
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
