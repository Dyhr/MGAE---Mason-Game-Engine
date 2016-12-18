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

	auto position = glm::vec3(gameObject->getComponent<Transform>()->getPosition());

	runTime += deltaTimeSec;
	numParticles = int(ceil(runTime * config.rate));
	if (numParticles > maxParticles) numParticles = maxParticles;
	
	for (int i = 0; i < numParticles; i++) {

		if (ages[i] + deltaTimeSec >= config.lifespan) {
			ages[i] = -1.0f;
			colors[i] = glm::vec4();			
			bodyCount--;
		}

		if (ages[i] < 0)
		{			
			if (emitNewParticles) {
				positions[i] = position;
				ages[i] = 0.0f;
				bodyCount++;

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
				velocities[i] = glm::vec3(gameObject->getTransform()->globalTransform() * glm::vec4(velocities[i].x, velocities[i].y, velocities[i].z, 0));
			}			
		}
		else {
			auto p0 = positions[i];
			auto v0 = velocities[i];

			velocities[i] = config.gravity * deltaTimeSec + v0;
			positions[i] = velocities[i] * deltaTimeSec + p0;

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
				newColor[0] = glm::lerp(config.initialColor[0], config.finalColor[0], ages[i] / config.lifespan);
				newColor[1] = glm::lerp(config.initialColor[1], config.finalColor[1], ages[i] / config.lifespan);
				newColor[2] = glm::lerp(config.initialColor[2], config.finalColor[2], ages[i] / config.lifespan);
				newColor[3] = glm::lerp(config.initialColor[3], config.finalColor[3], ages[i] / config.lifespan);
				break;
			case SPLINE:
				auto colorMod = cubicBezier(ages[i] / config.lifespan, config.splinePointsColor);
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
				newSize = glm::lerp(config.initialSize, config.finalSize, ages[i] / config.lifespan);
				break;
			case SPLINE:
				auto sizeMod = cubicBezier(ages[i] / config.lifespan, config.splinePointsSize);
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
				newRotation = glm::lerp(config.initialRotation, config.finalRotation, ages[i] / config.lifespan);
				break;
			case SPLINE:
				auto rotationMod = cubicBezier(ages[i] / config.lifespan, config.splinePointsRotation);
				newRotation = glm::lerp(config.initialRotation, config.finalRotation, rotationMod.y);
				break;
			}
			colors[i] = newColor;
			sizes[i] = newSize;
			uvRotation[i] = newRotation;
			ages[i] = ages[i] + deltaTimeSec;
		}
	}
	if (bodyCount == 0 && !emitNewParticles) {
		runTime = 0;
	}	
}

ParticleEmitter::ParticleEmitter(std::shared_ptr<GameObject> gameObject) : Component(gameObject) {
}

void ParticleEmitter::update(float deltaTimeSec)
{
	if (deltaTimeSec > 10) {
		deltaTimeSec = 10;
	}
	int iterations = int(ceil(60 * deltaTimeSec));
	for (int i = 0; i < iterations; i++) {
		updateModel(deltaTimeSec / iterations);
	}	
}

void ParticleEmitter::start()
{	
	if (!emitNewParticles && bodyCount == 0) {		
		emitNewParticles = true;
	}	
}

void ParticleEmitter::stop()
{
	if (emitNewParticles) {
		emitNewParticles = false;
	}
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

ParticleEmitter::~ParticleEmitter()
{
	// TODO clean up on removal. very important
	emitNewParticles = false;
	mesh = nullptr;
	shader = nullptr;
	positions.clear();
	sizes.clear();
	colors.clear();
	uvs.clear();
	uvSize.clear();
	uvRotation.clear();
	ages.clear();
	velocities.clear();
}

void ParticleEmitter::init(ParticleEmitterConfig config)
{
	this->config = config;
	maxParticles = int(ceil(config.lifespan * config.rate));
	numParticles = 0;
	startTime = -1.0f;	
	for(int i = 0; i < maxParticles; i++)
	{	
		ages.push_back(-1.0f);
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
