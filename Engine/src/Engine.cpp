#include "Mason/Engine.hpp"

#define SDL_MAIN_HANDLED

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

#include <chrono>
#include <iostream>
#include <SDL_timer.h>
#include <SRE/Mesh.hpp>
#include <SRE/Shader.hpp>
#include <SRE/SimpleRenderEngine.hpp>
#include <glm/glm.hpp>
#include <SDL.h>
#include <map>


using namespace SRE;
using namespace glm;


Engine::Engine()
{
	SDL_Init(SDL_INIT_VIDEO); 
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

	SimpleRenderEngine r{ window };
	physics = Physics::getInstance();
	audioManager = AudioManager::getInstance();
}
Engine::~Engine()
{
	// Close and destroy the window
	SDL_DestroyWindow(window);

	// Clean up
	SDL_Quit();
}


void Engine::setup() {
	std::map<int, std::shared_ptr<GameObject>> map_gameObjects;

	std::vector<GameObjectDescriptor> gameObjectDescriptors = SceneParser::parseFile("data/car_house_tree.json");
	Shader* shader = Shader::getStandard();
	auto cubeMesh = Mesh::createCube();
	auto planeMesh = Mesh::createQuad();
	auto sphereMesh = Mesh::createSphere();
	for (auto element : gameObjectDescriptors) {
		Mesh* mesh;
		if (element.meshName == "sphere") 
			mesh = sphereMesh;
		else if (element.meshName == "cube") 
			mesh = cubeMesh;
		else if (element.meshName == "plane") 
			mesh = planeMesh;
		else
			throw "Undefined mesh";

		auto gameObject = scene.addGameObject(element.meshName);
		auto transformComponent = gameObject->addComponent<Transform>();
		auto renderingComponent = gameObject->addComponent<Rendering>();

		renderingComponent->loadMesh(std::make_shared<Mesh>(*mesh));
		renderingComponent->loadShader(std::make_shared<Shader>(*shader));
		renderingComponent->setColor(element.color);
		transformComponent->setPosition(element.position);
		transformComponent->setRotation(element.rotationEuler);
		transformComponent->setScale(element.scale);

		map_gameObjects[element.uniqueId] = gameObject;
		
	}


	//Set up parent relationships between Transform components
	for (auto element : gameObjectDescriptors) {
		if (element.parentId != -1) {
			auto gameObject = map_gameObjects[element.uniqueId];
			auto parentGameObject = map_gameObjects[element.parentId];
			gameObject->getComponent<Transform>()->setParent(parentGameObject->getComponent<Transform>().get());
			
		}
	}

	//auto audioComponent = map_gameObjects[0]->addComponent<Audio>();
	//audioComponent->init("data/sounds/Alesis-Fusion-Acoustic-Bass-C2.wav", audioManager);
	//audioComponent->query();

	//auto anotherAudioComponent = map_gameObjects[1]->addComponent<Audio>();
	//anotherAudioComponent->init("data/sounds/Bass-Drum-1.wav", audioManager);
	//anotherAudioComponent->query();

	map_gameObjects[0]->addComponent<PlayerController>();

	auto g = vec3(0, -10, 0);

	auto emitter = map_gameObjects[0]->addComponent<ParticleEmitter>();
	emitter->init(ParticleEmitterConfig(0.5f, 6, vec3(3, 10, 0), g, 0.2f, vec4(0, 1, 1, 1)));
	emitter->start();

	emitter = map_gameObjects[16]->addComponent<ParticleEmitter>();
	emitter->init(ParticleEmitterConfig(8, 4, vec3(-5, 1, 0), g, 0.5f, vec4(0, 1, 0, 1), vec4(0, 1, 0, 0)));
	emitter->start();

	emitter = map_gameObjects[17]->addComponent<ParticleEmitter>();
	emitter->init(ParticleEmitterConfig(2, 1, vec3(0, 20, 0), g, 1.0f, 0.0f, vec4(0, 1, 1, 1)));
	emitter->start();

	// Load the spritesheet
	SpriteAtlas atlas("data/", "data/MarioPacked.json");

	auto sprite = map_gameObjects[0]->addComponent<SpriteRenderer>();
	sprite->sprite = atlas.getSprite("brick");


	auto camera = SimpleRenderEngine::instance->getCamera();
	camera->setPerspectiveProjection(60, 640, 480, 1, 1000);
	camera->lookAt(vec3(10, 10, 10), vec3(0, 0, 0), vec3(0, 1, 0));
	auto directionalLight = Light(LightType::Directional, vec3(0, 0, 0), vec3(1, 1, 1), vec3(1, 1, 1), 0, 20.0f);
	auto pointLight1 = Light(LightType::Point, vec3(-1, 1, 1), vec3(0, 0, 0), vec3(5, 0, 0), 5, 20.0f);
	auto pointLight2 = Light(LightType::Point, vec3(0,1,-2), vec3(0, 0, 0), vec3(3, 3, 3), 5, 20.0f);
	SimpleRenderEngine::instance->setLight(0, directionalLight);
	SimpleRenderEngine::instance->setLight(1, pointLight1);
	SimpleRenderEngine::instance->setLight(2, pointLight2);
   
}

void Engine::start() {
	physics->init();

    typedef std::chrono::high_resolution_clock Clock;
    auto t1 = Clock::now();
    int timePerFrameMillis = 1000/60;
	running = true;
    while (running) {
		using namespace std::chrono;

        auto t2 = Clock::now();
        // time since last update
        int deltaTimeMicSec = duration_cast<microseconds>(t2 - t1).count();
		float deltaTimeSec = deltaTimeMicSec / 1000000.0f;

		// Set the time
		Time::getInstance()->update(deltaTimeMicSec/1000);

		// Update the engine
        update(deltaTimeSec);

        int updateTimeMillis = static_cast<int>(duration_cast<milliseconds>(Clock::now() - t2).count());
        int wait = timePerFrameMillis - updateTimeMillis;
        if (wait > 0){
            SDL_Delay(wait);
        }
        t1 = t2;
    }
}

void Engine::update(float deltaTimeSec) {
    SimpleRenderEngine::instance->clearScreen({0,0,1,1});

	// step the physics
	physics->step(deltaTimeSec);

	// fetch input
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
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

	// update scripts
	for (auto & script : scene.getAllComponent<Script>()) {
		if (!script->started) {
			script->started = true;
			script->OnStart();
		}
		if (script) script->OnUpdate();
	}

    // render game object
	for (auto & rendering : scene.getAllComponent<Rendering>()) {
		if (rendering) {
			rendering->draw();
		}
    }

	// render sprites
	for (auto & sprite : scene.getAllComponent<SpriteRenderer>()) {
		if (sprite) {
			sprite->draw();
		}
	}

	// update and render particle emitters
	for (auto & particleEmitter : scene.getAllComponent<ParticleEmitter>()) {
		if (particleEmitter) {
			particleEmitter->update();
		}
	}

	audioManager->step();
	ParticleEmitter::render();

    SimpleRenderEngine::instance->swapWindow();
}
