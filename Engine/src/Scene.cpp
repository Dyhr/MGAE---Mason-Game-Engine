#include "Mason/Scene.hpp"
#include "Mason/Camera.hpp"
#include "Mason/Audio.hpp"
#include "Mason/BoxCollider2D.hpp"
#include "Mason/CircleCollider2D.h"
#include "Mason/ParticleEmitter.hpp"
#include "Mason/PhysicsBody2D.hpp"
#include "Mason/Script.hpp"
#include "Mason/SpriteRenderer.h"
#include "Mason/SpriteAtlas.h"
#include "Mason/Transform.h"

using namespace std;
using namespace Mason;

Scene* Scene::activeInstance = nullptr;

Mason::Scene::Scene() {
	activeInstance = this;
}

std::shared_ptr<GameObject> Mason::Scene::Instantiate(GameObjectDescriptor desc) {
	return activeInstance->loadGameObject(desc);
}

void Mason::Scene::Destroy(std::shared_ptr<GameObject> ptr)
{
	activeInstance->removeGameObject(ptr);
}

shared_ptr<GameObject> Scene::addGameObject(string name) {
    GameObject * go = new GameObject(name);
    auto res = shared_ptr<GameObject>(go);
	this->gameObjects.push_back(res);
    return res;
}

std::shared_ptr<GameObject> Mason::Scene::loadGameObject(GameObjectDescriptor element) {
	auto gameObject = addGameObject(element.name);
	map_gameObjects[element.uniqueId] = gameObject;
	if (element.camera.found)
	{
		loadCameraComponent(element, gameObject);
	}
	else {
		loadTransformComponent(element.transform, gameObject);
	}

	if (element.sprite.found)
	{
		loadSpriteComponent(element.sprite, gameObject);		
	}
	if (element.audio.found) {
		loadAudioComponent(element.audio, gameObject);
	}

	for (auto s : element.scripts)
	{
		loadScriptComponent(s, gameObject);
	}

	if (element.physicsBody2D.found) {
		loadPhysicsBodyComponent(element.physicsBody2D, gameObject);
	}
	if (element.boxCollider.found) {
		loadBoxColliderComponent(element.boxCollider, gameObject);
	}
	if (element.circleCollider.found) {
		loadCircleColliderComponenet(element.circleCollider, gameObject);
	}
	if (element.particles.found) {
		loadParticleComponent(element.particles, gameObject);		
	}
	return gameObject;
}

void Mason::Scene::setParentRelationship(int childId, int parentId) {
	auto gameObject = map_gameObjects[childId];
	auto parentGameObject = map_gameObjects[parentId];
	gameObject->getComponent<Transform>()->setParent(parentGameObject->getComponent<Transform>().get());
}

bool Scene::removeGameObject(shared_ptr<GameObject> ptr) {
    for (auto iter = this->gameObjects.begin();iter != this->gameObjects.end(); iter++){
        if (*iter == ptr){
			this->gameObjects.erase(iter);
            return true;
        }
    }
    // not found
    return false;
}

int Scene::getSize() {
    return (int) this->gameObjects.size();
}

shared_ptr<GameObject> Scene::getGameObject(int index) {
    return this->gameObjects.at(index);
}

vector<shared_ptr<GameObject>> Scene::getGameObjects() {
	return this->gameObjects;
}

void Mason::Scene::loadCameraComponent(GameObjectDescriptor element, std::shared_ptr<GameObject> go) {
	auto camera = go->addComponent<Camera>();
	camera->setPosition(element.transform.position);
	camera->setScale(element.transform.scale);
	camera->setViewportMin(element.camera.viewportMin);
	camera->setViewportMax(element.camera.viewportMax);
}

void Mason::Scene::loadParticleComponent(ParticleDescriptor element, std::shared_ptr<GameObject> go) {
	auto emitter = go->addComponent<ParticleEmitter>();
	ParticleEmitterConfig config(element.rate, element.lifespan, element.velocity, element.gravity);
	AttributeState sizeState = config.attributeFromString(element.sizeState);
	AttributeState rotationState = config.attributeFromString(element.rotationState);
	AttributeState colorState = config.attributeFromString(element.colorState);
	AttributeState velocityState = config.attributeFromString(element.velocityState);
	switch (velocityState) {
	case RANDOM:
		config.setRandomVelocity(element.minVelocity, element.maxVelocity);
		break;
	case FIXED:
		config.setFixedVelocity(element.velocity);
		break;
	default:
		break;
	}
	switch (sizeState) {
	case FIXED:
		config.setFixedSize(element.minSize);
		break;
	case RANDOM:
		config.setRandomSize(element.minSize, element.maxSize);
		break;
	case LINEAR:
		config.setLERPSize(element.initialSize, element.finalSize);
		break;
	case SPLINE:
		config.setSplineInterpSize(element.initialSize, element.finalSize, element.splinePointsSize);
		break;
	}
	switch (rotationState) {
	case FIXED:
		config.setFixedRotation(element.minRotation);
		break;
	case RANDOM:
		config.setRandomRotation(element.minRotation, element.maxRotation);
		break;
	case LINEAR:
		config.setLERPRotation(element.initialRotation, element.finalRotation);
		break;
	case SPLINE:
		config.setSplineInterpRotation(element.initialRotation, element.finalRotation, element.splinePointsRotation);
		break;
	}
	switch (colorState) {
	case FIXED:
		config.setFixedColor(element.minColor);
		break;
	case RANDOM:
		config.setRandomColor(element.minColor, element.maxColor);
		break;
	case LINEAR:
		config.setLERPColor(element.initialColor, element.finalColor);
		break;
	case SPLINE:
		config.setSplineInterpColor(element.initialColor, element.finalColor, element.splinePointsColor);
		break;
	}
	if (element.texturePath != "") config.setTexture(SRE::Texture::createFromFile(element.texturePath.c_str(), false));
	emitter->init(config);
	//This is done here for testing. Could be done from scripts in a real scenario.
	emitter->start();
}

void Mason::Scene::loadSpriteComponent(SpriteDescriptor element, std::shared_ptr<GameObject> go) {
	auto sprite = go->addComponent<SpriteRenderer>();
	sprite->sprite = sprites[element.name];
	// TODO support changing color of sprite
}

void Mason::Scene::loadPhysicsBodyComponent(PhysicsBodyDescriptor element, std::shared_ptr<GameObject> go) {
	auto physicsBody2D = go->addComponent<PhysicsBody2D>();
	physicsBody2D->body->SetType(element.type);
}

void Mason::Scene::loadBoxColliderComponent(BoxColliderDescriptor element, std::shared_ptr<GameObject> go) {
	auto box = go->addComponent<BoxCollider2D>();
	box->setCenter(element.center.x, element.center.y);
	box->setSize(element.width, element.height);
}

void Mason::Scene::loadCircleColliderComponenet(CircleColliderDescriptor element, std::shared_ptr<GameObject> go) {
	auto circle = go->addComponent<CircleCollider2D>();
	circle->setCenter(element.center.x, element.center.y);
	circle->setSize(element.radius);
}

void Mason::Scene::loadTransformComponent(TransformDescriptor element, std::shared_ptr<GameObject> go) {
	auto transformComponent = go->addComponent<Transform>();
	transformComponent->setPosition(element.position);
	transformComponent->setRotation(element.rotationEuler);
	transformComponent->setScale(element.scale);
}

void Mason::Scene::loadAudioComponent(AudioDescriptor element, std::shared_ptr<GameObject> go) {
	auto audio = go->addComponent<Audio>();
	audio->init(element.path, element.type, AudioManager::getInstance());
}

void Mason::Scene::loadScriptComponent(ScriptDescriptor element, std::shared_ptr<GameObject> go) {
	auto script = go->addScript(element.name);
	script->strings = element.strings;
	script->numbers = element.numbers;
}
