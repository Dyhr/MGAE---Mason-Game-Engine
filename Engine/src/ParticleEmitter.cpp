#include "Mason/ParticleEmitter.hpp"

#include "Mason/Time.hpp"
#include <SRE/SimpleRenderEngine.hpp>
#include <SRE/ParticleMesh.hpp>
#include <SRE/Texture.hpp>
#include <SRE/Shader.hpp>
#include <iostream>
#include "Mason/Transform.h"
#include "Mason/GameObject.hpp"
#include <math.h>
#include <time.h>
#include <random>
#include <glm/gtx/compatibility.hpp>

using namespace Mason;

glm::vec2 ParticleEmitter::cubicBezier(float t, std::vector<glm::vec2> splinePoints)
{
	if (splinePoints.size() == 1) {
		return splinePoints[0];
	}
	std::vector<glm::vec2> deeper;

	for (unsigned int i = 0; i < splinePoints.size() - 1; i++) {
		deeper.push_back(lerp(splinePoints[i], splinePoints[i + 1], t));
	}
	return cubicBezier(t, deeper);
}

void ParticleEmitter::updateModel(float deltaTimeSec)
{
	if (!running()) return;

	auto position = glm::vec3(gameObject->getComponent<Transform>()->globalTransform()[3]);

	float currenttime = Time::getTime();
	float timeSinceStart = currenttime - startTime;

	numParticles = int(ceil(timeSinceStart * config.rate));

	if (numParticles > maxParticles) numParticles = maxParticles;
	//std::cout << pos << ", " << numParticles << std::endl;

	for (int i = pos; i < pos + numParticles; i++) {

		if (age[i] + deltaTimeSec >= config.lifespan) {
			birthTimes[i] = age[i] = -1.0f;
			colors[i] = glm::vec4();		
		}

		if (birthTimes[i] < 0)
		{
			positions[i] = position;
			birthTimes[i] = timeSinceStart;
			age[i] = 0.0f;

			if (config.sizeState == RANDOM) {
				sizes[i] = glm::lerp(config.minSize, config.maxSize, static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
			}
			if (config.colorState == RANDOM) {
				glm::vec4 color;
				color[0] = glm::lerp(config.minColor[0], config.maxColor[0], static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
				color[1] = glm::lerp(config.minColor[1], config.maxColor[1], static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
				color[2] = glm::lerp(config.minColor[2], config.maxColor[2], static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
				color[3] = glm::lerp(config.minColor[3], config.maxColor[3], static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
				colors[i] = color;
			}
			if (config.rotationState == RANDOM) {
				uvRotation[i] = glm::lerp(config.minRotation, config.maxRotation, static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
			}
			if (config.velocityState == RANDOM) {
				glm::vec3 velocity;
				velocity[0] = glm::lerp(config.minVelocity[0], config.maxVelocity[0], static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
				velocity[1] = glm::lerp(config.minVelocity[1], config.maxVelocity[1], static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
				velocity[2] = glm::lerp(config.minVelocity[2], config.maxVelocity[2], static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
				velocities[i] = velocity;
			}
			else {
				velocities[i] = config.velocity;
			}
		}

		auto p0 = positions[i];
		auto v0 = velocities[i];

		velocities[i] = config.gravity*deltaTimeSec + v0;
		positions[i] = velocities[i]*deltaTimeSec + p0;		

		glm::vec4 newColor = colors[i];
		float newSize = sizes[i];

		float newRotation = uvRotation[i];

		switch (config.colorState) {
		case FIXED:
			newColor = config.initialColor;
			break;
		case RANDOM:
			break;
		case LINEAR:
			newColor[0] = glm::lerp(config.initialColor[0], config.finalColor[0], age[i] / config.lifespan);
			newColor[1] = glm::lerp(config.initialColor[1], config.finalColor[1], age[i] / config.lifespan);
			newColor[2] = glm::lerp(config.initialColor[2], config.finalColor[2], age[i] / config.lifespan);
			newColor[3] = glm::lerp(config.initialColor[3], config.finalColor[3], age[i] / config.lifespan);
			break;
		case SPLINE:
			auto colorMod = cubicBezier(age[i] / config.lifespan, config.splinePointsColor);
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
			newSize = glm::lerp(config.initialSize, config.finalSize, age[i] / config.lifespan);
			break;
		case SPLINE:
			auto sizeMod = cubicBezier(age[i] / config.lifespan, config.splinePointsSize);
			newSize = glm::lerp(config.initialSize, config.finalSize, sizeMod.y);
			break;
		}

		switch (config.rotationState) {
		case FIXED:
			newRotation = config.initialRotation;
			break;
		case RANDOM:
			break;
		case LINEAR:
			newRotation = glm::lerp(config.initialRotation, config.finalRotation, age[i] / config.lifespan);
			break;
		case SPLINE:
			auto rotationMod = cubicBezier(age[i] / config.lifespan, config.splinePointsRotation);
			newRotation = glm::lerp(config.initialRotation, config.finalRotation, rotationMod.y);
			break;
		}
		colors[i] = newColor;
		sizes[i] = newSize;
		uvRotation[i] = newRotation;
		age[i] = age[i] + deltaTimeSec;
	}
}

ParticleEmitter::ParticleEmitter(GameObject * gameObject) : Component(gameObject) {
}

void ParticleEmitter::update(float deltaTimeSec)
{
	//float dtInner = 1/60; // 16.67 ms ?
	//float min_dtInner = 0.01; // 10ms
	//int max_innerCount = 50;

	//int innerCount = int(ceil(deltaTimeSec / dtInner));
	//if (innerCount > max_innerCount) {
	//	innerCount = max_innerCount;
	//	dtInner = deltaTimeSec / innerCount;
	//}
	//if (dtInner < min_dtInner) {
	//	dtInner = min_dtInner;
	//	innerCount = deltaTimeSec / dtInner;
	//}

	//for (int i = 0; i<innerCount; i++) {
	//	updateModel(dtInner);
	//}

	if (deltaTimeSec > 10) {
		deltaTimeSec = 10;
	}
	int iterations = int(ceil(60 * deltaTimeSec));
	for (int i = 0; i < iterations; i++) {
		if (i > 1) std::cout << i << std::endl;
		updateModel(deltaTimeSec / iterations);
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
	if (shader == nullptr)
		shader = SRE::Shader::getStandardParticles();
	if (mesh == nullptr)
		mesh = new SRE::ParticleMesh(positions, colors, uvs, uvSize, uvRotation, sizes);
	mesh->update(positions, colors, uvs, uvSize, uvRotation, sizes);
	if (config.tex) {
		shader->set("tex", config.tex);
	}
	else {
		shader->set("tex", SRE::Texture::getSphereTexture());
	}
	
	SRE::SimpleRenderEngine::instance->draw(mesh, glm::mat4(1), shader);
}

void ParticleEmitter::clear() // TODO actual garbage collection
{
	positions = std::vector<glm::vec3>();
	sizes = std::vector<float>();
	colors = std::vector<glm::vec4>();
	uvs = std::vector<glm::vec2>();
	uvSize = std::vector<float>();
	//uv rotation in radians -> from 0 to 2*pi
	uvRotation = std::vector<float>();

	totalParticles = 0;

	birthTimes = std::vector<float>();
	age = std::vector<float>();
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
	std::cout << maxParticles << std::endl;
	numParticles = 0;
	startTime = -1.0f;

	pos = totalParticles;
	for(int i = 0; i < maxParticles; i++)
	{
		totalParticles++;
		birthTimes.push_back(-1.0f);
		age.push_back(-1.0f);
		positions.push_back(glm::vec3());
		velocities.push_back(glm::vec3());
		colors.push_back(glm::vec4());
		sizes.push_back(0.5f);
		uvRotation.push_back(3.0f);
		
		//uvs.push_back(glm::vec2());
		//uvSize.push_back(0.0f);
		//uvRotation.push_back(0.0f);
		
	}
}
