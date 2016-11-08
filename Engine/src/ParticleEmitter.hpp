#pragma once

#include <glm/glm.hpp>
#include "Component.hpp"
#include "Transform.h"
#include <SRE/SimpleRenderEngine.hpp>

struct ParticleEmitterConfig
{
	float rate;
	float lifespan;
};

class ParticleEmitter : public Component {
public:
	static void render();

	~ParticleEmitter();

	void init(ParticleEmitterConfig config);
	void update();
	void start();
	void stop();
	bool running();

	void setVelocity(glm::vec3 velocity);
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
	static int totalParticles;

	ParticleEmitter(GameObject *gameObject);

	ParticleEmitterConfig config;
	int numParticles, maxParticles, pos, mark;
	float startTime;

	glm::vec3 velocity;
	glm::vec4 color;

	friend class GameObject;
};
