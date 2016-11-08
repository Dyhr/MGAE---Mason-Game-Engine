#pragma once
#include "GameObject.hpp"
#include "Component.hpp"
#include "glm/glm.hpp"
#include "ParticleSystem.hpp"

class ParticleEmitter : public Component {
public:
	void setParticleSystem(ParticleSystem *system);
	void setVelocity(glm::vec3 velocity);
	void emit();
	void setColor(glm::vec4 color);
protected:
	ParticleEmitter(GameObject *gameObject);
	friend class GameObject;
	glm::vec3 velocity;
	glm::vec4 color;
	ParticleSystem *particleSystem;
};