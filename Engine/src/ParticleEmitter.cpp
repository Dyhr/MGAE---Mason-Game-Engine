#include "ParticleEmitter.hpp"

#include "Time.hpp"
#include <SRE/SimpleRenderEngine.hpp>
#include <SRE/ParticleMesh.hpp>
#include <SRE/Texture.hpp>
#include <iostream>


SRE::ParticleMesh* ParticleEmitter::mesh = nullptr;
SRE::Shader* ParticleEmitter::shader = nullptr;

std::vector<glm::vec3> ParticleEmitter::positions = std::vector<glm::vec3>();
std::vector<float> ParticleEmitter::particleSize = std::vector<float>();
std::vector<glm::vec4> ParticleEmitter::colors = std::vector<glm::vec4>();
std::vector<glm::vec2> ParticleEmitter::uvs = std::vector<glm::vec2>();
std::vector<float> ParticleEmitter::uvSize = std::vector<float>();
std::vector<float> ParticleEmitter::uvRotation = std::vector<float>();

int ParticleEmitter::totalParticles = 0;

std::vector<float> ParticleEmitter::birthTimes = std::vector<float>();
std::vector<float> ParticleEmitter::times = std::vector<float>();
std::vector<glm::vec3> ParticleEmitter::velocities = std::vector<glm::vec3>();

ParticleEmitter::ParticleEmitter(GameObject * gameObject) : Component(gameObject) {
	if(shader == nullptr)
		shader = SRE::Shader::getStandardParticles();
	if (mesh == nullptr)
		mesh = new SRE::ParticleMesh(positions, colors, uvs, uvSize, uvRotation, particleSize);
}

void ParticleEmitter::setVelocity(glm::vec3 velocity) {
	this->velocity = velocity;
}

void ParticleEmitter::update()
{
	if (!running()) return;

	auto position = glm::vec3(gameObject->getComponent<Transform>()->globalTransform()[3]);

	glm::vec3 a(0, -9.8f, 0);
	float currenttime = Time::getInstance()->getTime();
	float timeSinceStart = currenttime - startTime;

	numParticles = ceil(timeSinceStart * config.rate);
	if (numParticles > maxParticles) numParticles = maxParticles;

	for (int i = pos; i < pos+numParticles; i++) {
		if (times[i] > config.lifespan) birthTimes[i] = times[i] = -1.0f;

		if(birthTimes[i] < 0)
		{
			positions[i] = position;
			velocities[i] = velocity;
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
		times[i] = timeSinceBirth;
		colors[i] = color;
	}
}

void ParticleEmitter::start()
{
	startTime = Time::getInstance()->getTime();
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
	mesh->update(positions, colors, uvs, uvSize, uvRotation, particleSize);
	shader->set("tex", SRE::Texture::getSphereTexture());
	SRE::SimpleRenderEngine::instance->draw(mesh, glm::mat4(1), shader);
}

ParticleEmitter::~ParticleEmitter()
{
	// TODO very important to clean up on removal
}

void ParticleEmitter::init(ParticleEmitterConfig config)
{
	this->config = config;
	maxParticles = ceil(config.lifespan * config.rate);
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
		particleSize.push_back(0.5f);
	}
}

void ParticleEmitter::setColor(glm::vec4 color) {
	this->color = color;
}

