#pragma once

#include <glm/glm.hpp>
#include "Component.hpp"
#include "Transform.h"
#include "ParticleSystem.hpp"

class ParticleEmitter : public Component {
public:
	static void render();

	void setVelocity(glm::vec3 velocity);
	void update();
	void setColor(glm::vec4 color);
protected:
	static SRE::ParticleMesh* mesh;
	static SRE::Shader* shader;

	ParticleEmitter(GameObject *gameObject);

	glm::vec3 velocity;
	glm::vec4 color;

	std::vector<float> particleSize;
	std::vector<Particle> particles;
	std::vector<glm::vec4> colors;

	friend class GameObject;
};