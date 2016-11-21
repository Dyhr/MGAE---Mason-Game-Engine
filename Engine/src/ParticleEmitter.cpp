#include "Mason/ParticleEmitter.hpp"

#include "Mason/Time.hpp"
#include <SRE/SimpleRenderEngine.hpp>
#include <SRE/ParticleMesh.hpp>
#include <SRE/Texture.hpp>
#include <SRE/Shader.hpp>
#include <iostream>
#include "Mason/Transform.h"
#include "Mason/GameObject.hpp"
#include <time.h>
#include <random>
#include <glm/gtx/compatibility.hpp>

using namespace Mason;

SRE::ParticleMesh* ParticleEmitter::mesh = nullptr;
SRE::Shader* ParticleEmitter::shader = nullptr;

std::vector<glm::vec3> ParticleEmitter::positions = std::vector<glm::vec3>();
std::vector<float> ParticleEmitter::sizes = std::vector<float>();
std::vector<glm::vec4> ParticleEmitter::colors = std::vector<glm::vec4>();
std::vector<glm::vec2> ParticleEmitter::uvs = std::vector<glm::vec2>();
std::vector<float> ParticleEmitter::uvSize = std::vector<float>();
std::vector<float> ParticleEmitter::uvRotation = std::vector<float>();

int ParticleEmitter::totalParticles = 0;

std::vector<float> ParticleEmitter::birthTimes = std::vector<float>();
std::vector<float> ParticleEmitter::times = std::vector<float>();
std::vector<glm::vec3> ParticleEmitter::velocities = std::vector<glm::vec3>();

float ParticleEmitter::maybeWrongLerp(float f1, float f2, float perc)
{
	auto diff = f2 - f1;
	return f1 + (diff * perc);
}

float ParticleEmitter::cubicBezier(float t, float splinePoints[4])
{
	auto a1 = glm::lerp(splinePoints[0], splinePoints[1], t);
	auto b1 = glm::lerp(splinePoints[1], splinePoints[2], t);
	auto c1 = glm::lerp(splinePoints[2], splinePoints[3], t);

	auto a2 = glm::lerp(a1, b1, t);
	auto b2 = glm::lerp(b1, c1, t);

	return glm::lerp(a2, b2, t);
}

ParticleEmitter::ParticleEmitter(GameObject * gameObject) : Component(gameObject) {
	if(shader == nullptr)
		shader = SRE::Shader::getStandardParticles();
	if (mesh == nullptr)
		mesh = new SRE::ParticleMesh(positions, colors, uvs, uvSize, uvRotation, sizes);
}

void ParticleEmitter::update()
{
	if (!running()) return;

	auto position = glm::vec3(gameObject->getComponent<Transform>()->globalTransform()[3]);

	glm::vec3 a(0, -9.8f, 0);
	float currenttime = Time::getTime();
	float timeSinceStart = currenttime - startTime;

	numParticles = int(ceil(timeSinceStart * config.rate));
	if (numParticles > maxParticles) numParticles = maxParticles;

	for (int i = pos; i < pos+numParticles; i++) {
		if (times[i] > config.lifespan) {
			birthTimes[i] = times[i] = -1.0f;
			colors[i] = glm::vec4();
		}

		if(birthTimes[i] < 0)
		{
			positions[i] = position;
			velocities[i] = config.velocity;
			birthTimes[i] = timeSinceStart;
			times[i] = 0.0f;
		}

		float timeSinceBirth = timeSinceStart - birthTimes[i];
		float timeSinceUpdate = timeSinceBirth - times[i];

		auto p0 = positions[i];
		auto v0 = velocities[i];

		auto dt = timeSinceUpdate;
		positions[i] = 0.5f*a*dt*dt + v0*dt + p0;
		velocities[i] = a*dt + v0;
		
		glm::vec4 newColor = colors[i];
		float newSize = sizes[i];

		switch (config.colorState) {
			case FIXED:
				newColor = config.initialColor;
				break;
			case RANDOM:
				newColor.x = glm::lerp(config.initialColor.x, config.finalColor.x, static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
				newColor.y = glm::lerp(config.initialColor.y, config.finalColor.y, static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
				newColor.z = glm::lerp(config.initialColor.z, config.finalColor.z, static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
				newColor.w = glm::lerp(config.initialColor.w, config.finalColor.w, static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
				break;
			case LINEAR:
				newColor.x = glm::lerp(config.initialColor.x, config.finalColor.x, times[i] / config.lifespan);
				newColor.y = glm::lerp(config.initialColor.y, config.finalColor.y, times[i] / config.lifespan);
				newColor.z = glm::lerp(config.initialColor.z, config.finalColor.z, times[i] / config.lifespan);
				newColor.w = glm::lerp(config.initialColor.w, config.finalColor.w, times[i] / config.lifespan);
				break;
			case SPLINE:
				auto colorMod = cubicBezier(times[i] / config.lifespan, config.splinePointsColor);
				newColor.x = glm::lerp(config.initialColor.x, config.finalColor.x, colorMod);
				newColor.y = glm::lerp(config.initialColor.y, config.finalColor.y, colorMod);
				newColor.z = glm::lerp(config.initialColor.z, config.finalColor.z, colorMod);
				newColor.w = glm::lerp(config.initialColor.w, config.finalColor.w, colorMod);

				break;
		}

		switch (config.sizeState) {
			case FIXED:
				newSize = config.initialSize;
				break;
			case RANDOM:
				newSize = glm::lerp(config.initialSize, config.finalSize, static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
				break;
			case LINEAR:
				newSize = glm::lerp(config.initialSize, config.finalSize, times[i]/config.lifespan);
				break;
			case SPLINE:
				auto sizeMod = cubicBezier(times[i], config.splinePointsSize);
				newSize = glm::lerp(config.initialSize, config.finalSize, sizeMod);
				break;
		}

		colors[i] = newColor;
		sizes[i] = newSize;

		times[i] = timeSinceBirth;
	}
}

void ParticleEmitter::start()
{
	startTime = Time::getTime();
}

void ParticleEmitter::stop()
{
	numParticles = 0;
	startTime = -1.0f;
}

bool ParticleEmitter::running()
{
	return startTime >= 0.0f;
}

void ParticleEmitter::render() {
	mesh->update(positions, colors, uvs, uvSize, uvRotation, sizes);
	shader->set("tex", SRE::Texture::getSphereTexture());
	SRE::SimpleRenderEngine::instance->draw(mesh, glm::mat4(1), shader);
}

ParticleEmitter::~ParticleEmitter()
{
	// TODO clean up on removal. very important 
}

void ParticleEmitter::init(ParticleEmitterConfig config)
{
	this->config = config;
	maxParticles = int(ceil(config.lifespan * config.rate));
	numParticles = 0;
	startTime = -1.0f;

	pos = totalParticles;
	for(int i = 0; i < maxParticles; i++)
	{
		totalParticles++;
		birthTimes.push_back(-1.0f);
		times.push_back(-1.0f);
		positions.push_back(glm::vec3());
		velocities.push_back(glm::vec3());
		colors.push_back(glm::vec4());
		//uvs.push_back(glm::vec2());
		//uvSize.push_back(0.0f);
		//uvRotation.push_back(0.0f);
		sizes.push_back(0.5f);
	}
}
