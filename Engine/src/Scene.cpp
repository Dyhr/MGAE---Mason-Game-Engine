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

#include "Box2D/Box2D.h"

using namespace std;
using namespace Mason;

Scene* Scene::activeInstance = nullptr;

Scene::Scene() {
	activeInstance = this;
}

shared_ptr<GameObject> Scene::Instantiate(std::string name) {
	return activeInstance->loadGameObject(SceneParser::parseTemplate(name, activeInstance->templatepath));
}

void Scene::Destroy(shared_ptr<GameObject> ptr)
{
	activeInstance->removeGameObject(ptr);
}

shared_ptr<GameObject> Scene::addGameObject(string name) {
	GameObject* go = new GameObject(name);
	auto res = new shared_ptr<GameObject>(go);
	go->me = res;
	this->gameObjects.push_back(*res);
	return *res;
}

shared_ptr<GameObject> Scene::loadGameObject(GameObjectDescriptor element) {
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
		for (auto box : element.physicsBody2D.boxColliders)
			loadBoxColliderComponent(box, gameObject);
		for (auto circle : element.physicsBody2D.circleColliders)
			loadCircleColliderComponenet(circle, gameObject);
		gameObject->getComponent<PhysicsBody2D>()->UpdateFixtures();
	}
	if (element.particles.found) {
		loadParticleComponent(element.particles, gameObject);
	}
	return gameObject;
}

void Scene::setParentRelationship(int childId, int parentId) {
	auto gameObject = map_gameObjects[childId];
	auto parentGameObject = map_gameObjects[parentId];
	gameObject->getComponent<Transform>()->setParent(parentGameObject->getComponent<Transform>());
}

bool Scene::removeGameObject(shared_ptr<GameObject> ptr) {
	for (auto iter = this->gameObjects.begin(); iter != this->gameObjects.end(); iter++) {
		if (*iter == ptr) {
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

void Scene::loadCameraComponent(GameObjectDescriptor element, shared_ptr<GameObject> go) {
	auto camera = go->addComponent<Camera>();
	go->transform = camera;
	camera->setViewportMin(element.camera.viewportMin);
	camera->setViewportMax(element.camera.viewportMax);
	camera->setPosition(element.transform.position);
	camera->setScale(element.transform.scale);
}

void Scene::loadParticleComponent(ParticleDescriptor element, shared_ptr<GameObject> go) {
	ParticleEmitter* emitter = go->addComponent<ParticleEmitter>();
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

void Scene::loadSpriteComponent(SpriteDescriptor element, shared_ptr<GameObject> go) {
	auto spriteRenderer = go->addComponent<SpriteRenderer>();
	spriteRenderer->sprite = sprites[element.name];
	// TODO support changing color of sprite
}

void Scene::loadPhysicsBodyComponent(PhysicsBodyDescriptor element, shared_ptr<GameObject> go) {
	auto physicsBody2D = go->addComponent<PhysicsBody2D>();
	physicsBody2D->body->SetType(b2BodyType(element.type));

	auto pos = go->getComponent<Transform>()->getPosition();
	auto rot = go->getComponent<Transform>()->getRotation();
	physicsBody2D->body->SetTransform(b2Vec2(pos.x / Physics::instance->phScale, pos.y / Physics::instance->phScale), rot * float(M_PI/180));
}

void Scene::loadBoxColliderComponent(BoxColliderDescriptor element, shared_ptr<GameObject> go) {
	auto box = go->addComponent<BoxCollider2D>();
	box->setDensity(element.density);
	box->setFriction(element.friction);
	box->setCenter(element.center.x, element.center.y);
	box->setSize(element.width, element.height);
}

void Scene::loadCircleColliderComponenet(CircleColliderDescriptor element, shared_ptr<GameObject> go) {
	auto circle = go->addComponent<CircleCollider2D>();
	circle->setDensity(element.density);
	circle->setFriction(element.friction);
	circle->setCenter(element.center.x, element.center.y);
	circle->setSize(element.radius);
}

void Scene::loadTransformComponent(TransformDescriptor element, shared_ptr<GameObject> go) {
	auto transformComponent = go->addComponent<Transform>();
	transformComponent->setPosition(element.position);
	transformComponent->setRotation(element.rotation);
	transformComponent->setScale(element.scale);
	go->transform = transformComponent;
}

void Scene::loadAudioComponent(AudioDescriptor element, shared_ptr<GameObject> go) {
	auto audio = go->addComponent<Audio>();
	audio->init(element.path, element.type, AudioManager::getInstance());
}

void Scene::loadScriptComponent(ScriptDescriptor element, shared_ptr<GameObject> go) {
	auto script = go->addScript(element.name);
	script->strings = element.strings;
	script->numbers = element.numbers;
}
