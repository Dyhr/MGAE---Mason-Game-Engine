#include "ParticleEmitter.hpp"



ParticleEmitter::ParticleEmitter(GameObject * gameObject) : Component(gameObject) {
}	

void ParticleEmitter::setParticleSystem(ParticleSystem * system) {
	this->particleSystem = system;
}

void ParticleEmitter::setVelocity(glm::vec3 velocity) {
	this->velocity = velocity;
}

void ParticleEmitter::emit() {
	auto transform = gameObject->getComponent<Transform>()->globalTransform();
	auto position = glm::vec3(transform[3]);
	particleSystem->emit(position, velocity, color);
}

void ParticleEmitter::setColor(glm::vec4 color) {
	this->color = color;
}

