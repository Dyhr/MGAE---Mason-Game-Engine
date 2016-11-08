#pragma once

#include <glm/glm.hpp>
#include "Component.hpp"
#include "Transform.h"
#include <SRE/SimpleRenderEngine.hpp>

class ParticleEmitter : public Component {
public:
	static void render();

	void setVelocity(glm::vec3 velocity);
	void update();
	void setColor(glm::vec4 color);
protected:
	static SRE::ParticleMesh* mesh;
	static SRE::Shader* shader;

	static std::vector<glm::vec3> positions;
	static std::vector<float> particleSize;
	static std::vector<glm::vec4> colors;
	static std::vector<glm::vec2> uvs;
	static std::vector<float> uvSize;
	static std::vector<float> uvRotation;

	ParticleEmitter(GameObject *gameObject);

	glm::vec3 velocity;
	glm::vec4 color;

	friend class GameObject;
};
