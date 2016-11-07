#include <SRE/SimpleRenderEngine.hpp>
#include "ParticleSystem.hpp"
#include "Transform.h"

Particle::Particle(glm::vec3 position, glm::vec3 velocity)
	:position(position), velocity(velocity)
{
}

ParticleSystem::ParticleSystem(GameObject * gameObject) : Component(gameObject), m_size(1024), emissionIndex(0)
{
	auto tmp = SRE::Shader::getStandardParticles();
	shader = std::make_shared<SRE::Shader>(*tmp);
}

void ParticleSystem::loadShader(std::shared_ptr<SRE::Shader> newShader)
{
	shader = newShader;
}

void ParticleSystem::init() {
	for (int i = 0; i<m_size; i++) {
		particles.push_back(Particle(glm::vec3{ 0,0,0 }, glm::vec3{ 0,-1,0 }));
		finalPos.push_back(glm::vec3{ 0,0,0 });
		particleSizes.push_back(0.5f);
	}
	update(0);
}

void ParticleSystem::loadMesh(std::shared_ptr<SRE::ParticleMesh> newMesh)
{
	mesh = newMesh;
}

void ParticleSystem::setSize(int size)
{
	m_size = size;
}

void ParticleSystem::emit(glm::vec3 velocity)
{
	particles[emissionIndex].position = gameObject->getComponent<Transform>()->getPosition();
	particles[emissionIndex].velocity = velocity;
	emissionIndex = (emissionIndex + 1) % particles.size();
}

void ParticleSystem::update(float deltaTime)
{
	glm::vec3 a(0, gravity, 0);
	for (int i = 0; i < finalPos.size(); i++) {
		glm::vec3 v = (1 - particles[i].drag) * particles[i].velocity + deltaTime * a;
		glm::vec3 p = particles[i].position + v * deltaTime;
		finalPos[i] = p;
	}
	//Not used so far. Using default values
	std::vector<glm::vec4> colors;
	std::vector<glm::vec2> uvs;
	std::vector<float> uvSize;
	std::vector<float> uvRotation;

	if (mesh == nullptr) {
		mesh = std::make_shared<SRE::ParticleMesh>(finalPos, colors, uvs, uvSize, uvRotation, particleSizes);
	}
	else {
		mesh->update(finalPos, colors, uvs, uvSize, uvRotation, particleSizes);
	}
	currentTime += deltaTime;
}

void ParticleSystem::render()
{
	if (mesh && shader) {
		SRE::SimpleRenderEngine::instance->draw(&*mesh, glm::mat4(1), &*shader);
	}
}
