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

SRE::ParticleMesh* ParticleEmitter::mesh = nullptr;
SRE::Shader* ParticleEmitter::shader = nullptr;

glm::vec2 ParticleEmitter::cubicBezier(float t, std::vector<glm::vec2> splinePoints)
{
	if (splinePoints.size() == 1) {
		return splinePoints[0];
	}
	std::vector<glm::vec2> deeper;

	for (int i = 0; i < splinePoints.size() - 1; i++) {
		deeper.push_back(glm::lerp(splinePoints[i], splinePoints[i + 1], t));
	}

	//auto ax = glm::lerp(splinePoints[0].x, splinePoints[1].x, t);
	//auto ay = glm::lerp(splinePoints[0].y, splinePoints[1].y, t);
	//auto bx = glm::lerp(splinePoints[1].x, splinePoints[2].x, t);
	//auto by = glm::lerp(splinePoints[1].y, splinePoints[2].y, t);
	//auto cx = glm::lerp(splinePoints[2].x, splinePoints[3].x, t);
	//auto cy = glm::lerp(splinePoints[2].y, splinePoints[3].y, t);

	//auto ix = glm::lerp(ax, bx, t);
	//auto iy = glm::lerp(ay, by, t);
	//auto jx = glm::lerp(bx, cx, t);
	//auto jy = glm::lerp(by, cy, t);

	//auto px = glm::lerp(ix, jx, t);
	//auto py = glm::lerp(iy, jy, t);

	return cubicBezier(t, deeper);
}

ParticleEmitter::ParticleEmitter(GameObject * gameObject) : Component(gameObject) {
}

void ParticleEmitter::update()
{
	if (!running()) return;

	auto position = glm::vec3(gameObject->getComponent<Transform>()->globalTransform()[3]);

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
			if (config.sizeState == AttributeState::RANDOM) {
				sizes[i] = glm::lerp(config.minSize, config.maxSize, static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
			}
			if (config.colorState == AttributeState::RANDOM) {
				glm::vec4 color;
				color[0] = glm::lerp(config.minColor[0], config.maxColor[0], static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
				color[1] = glm::lerp(config.minColor[1], config.maxColor[1], static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
				color[2] = glm::lerp(config.minColor[2], config.maxColor[2], static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
				color[3] = glm::lerp(config.minColor[3], config.maxColor[3], static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
				colors[i] = color;
			}
			

		}

		float timeSinceBirth = timeSinceStart - birthTimes[i];
		float timeSinceUpdate = timeSinceBirth - times[i];

		auto p0 = positions[i];
		auto v0 = velocities[i];

		auto dt = timeSinceUpdate;
		positions[i] = 0.5f*config.gravity*dt*dt + v0*dt + p0;
		velocities[i] = config.gravity*dt + v0;
		
		glm::vec4 newColor = colors[i];
		float newSize = sizes[i];

		switch (config.colorState) {
			case FIXED:
				newColor = config.initialColor;
				break;
			case RANDOM:
				break;
			case LINEAR:
				newColor[0] = glm::lerp(config.initialColor[0], config.finalColor[0], times[i] / config.lifespan);
				newColor[1] = glm::lerp(config.initialColor[1], config.finalColor[1], times[i] / config.lifespan);
				newColor[2] = glm::lerp(config.initialColor[2], config.finalColor[2], times[i] / config.lifespan);
				newColor[3] = glm::lerp(config.initialColor[3], config.finalColor[3], times[i] / config.lifespan);
				break;
			case SPLINE:
				auto colorMod = cubicBezier(times[i] / config.lifespan, config.splinePointsColor);
				newColor[0] = glm::lerp(config.initialColor[0], config.finalColor[0], colorMod.y);
				newColor[1] = glm::lerp(config.initialColor[1], config.finalColor[1], colorMod.y);
				newColor[2] = glm::lerp(config.initialColor[2], config.finalColor[2], colorMod.y);
				newColor[3] = glm::lerp(config.initialColor[3], config.finalColor[3], colorMod.y);
				break;
		}

		switch (config.sizeState) {
			case FIXED:
				newSize = config.initialSize;
				break;
			case RANDOM:
				break;
			case LINEAR:
				newSize = glm::lerp(config.initialSize, config.finalSize, times[i]/config.lifespan);
				break;
			case SPLINE:
				auto sizeMod = cubicBezier(times[i] / config.lifespan, config.splinePointsSize);
				newSize = glm::lerp(config.initialSize, config.finalSize, sizeMod.y);
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

void ParticleEmitter::render(SRE::Texture * tex) {
	if (shader == nullptr)
		shader = SRE::Shader::getStandardParticles();
	if (mesh == nullptr)
		mesh = new SRE::ParticleMesh(positions, colors, uvs, uvSize, uvRotation, sizes);

	mesh->update(positions, colors, uvs, uvSize, uvRotation, sizes);
	shader->set("tex", tex);
	SRE::SimpleRenderEngine::instance->draw(mesh, glm::mat4(1), shader);
}

void ParticleEmitter::clear() // TODO actual garbage collection
{
	positions = std::vector<glm::vec3>();
	sizes = std::vector<float>();
	colors = std::vector<glm::vec4>();
	uvs = std::vector<glm::vec2>();
	uvSize = std::vector<float>();
	uvRotation = std::vector<float>();

	totalParticles = 0;

	birthTimes = std::vector<float>();
	times = std::vector<float>();
	velocities = std::vector<glm::vec3>();
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
		sizes.push_back(0.5f);
		
		//uvs.push_back(glm::vec2());
		//uvSize.push_back(0.0f);
		//uvRotation.push_back(0.0f);
		
	}
}
