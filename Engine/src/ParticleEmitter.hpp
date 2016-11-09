#pragma once

#include <glm/glm.hpp>
#include "Component.hpp"
#include "Transform.h"
#include <SRE/SimpleRenderEngine.hpp>

struct ParticleEmitterConfig
{
	float rate;
	float lifespan;
	
	glm::vec3 velocity;
	glm::vec3 gravity;
	
	float initialSize;
	float finalSize;
	glm::vec4 initialColor;
	glm::vec4 finalColor;


	ParticleEmitterConfig()
		: rate(0),
		lifespan(0),
		velocity(glm::vec3()),
		gravity(glm::vec3()),
		initialSize(0),
		finalSize(0),
		initialColor(glm::vec4()),
		finalColor(glm::vec4())
	{
	}

	ParticleEmitterConfig(float rate, float lifespan, glm::vec3 velocity, glm::vec3 gravity, float size, glm::vec4 color)
		: rate(rate),
		lifespan(lifespan),
		velocity(velocity),
		gravity(gravity),
		initialSize(size),
		finalSize(size),
		initialColor(color),
		finalColor(color)
	{
	}
	ParticleEmitterConfig(float rate, float lifespan, glm::vec3 velocity, glm::vec3 gravity, float initial_size, float final_size, glm::vec4 color)
		: rate(rate),
		lifespan(lifespan),
		velocity(velocity),
		gravity(gravity),
		initialSize(initial_size),
		finalSize(final_size),
		initialColor(color),
		finalColor(color)
	{
	}
	ParticleEmitterConfig(float rate, float lifespan, glm::vec3 velocity, glm::vec3 gravity, float size, glm::vec4 initial_color, glm::vec4 final_color)
		: rate(rate),
		lifespan(lifespan),
		velocity(velocity),
		gravity(gravity),
		initialSize(size),
		finalSize(size),
		initialColor(initial_color),
		finalColor(final_color)
	{
	}
	ParticleEmitterConfig(float rate, float lifespan, glm::vec3 velocity, glm::vec3 gravity, float initial_size, float final_size, glm::vec4 initial_color, glm::vec4 final_color)
		: rate(rate),
		  lifespan(lifespan),
		  velocity(velocity),
		  gravity(gravity),
		  initialSize(initial_size),
		  finalSize(final_size),
		  initialColor(initial_color),
		  finalColor(final_color)
	{
	}
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
protected:
	static SRE::ParticleMesh* mesh;
	static SRE::Shader* shader;

	static std::vector<glm::vec3> positions;
	static std::vector<float> sizes;
	static std::vector<glm::vec4> colors;
	static std::vector<glm::vec2> uvs;
	static std::vector<float> uvSize;
	static std::vector<float> uvRotation;
	static int totalParticles;

	static std::vector<float> birthTimes;
	static std::vector<float> times;
	static std::vector<glm::vec3> velocities;

	ParticleEmitter(GameObject *gameObject);

	ParticleEmitterConfig config;
	int numParticles, maxParticles, pos;
	float startTime;

	friend class GameObject;
};
