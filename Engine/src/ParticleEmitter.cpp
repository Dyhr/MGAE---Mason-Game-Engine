#include "ParticleEmitter.hpp"

#include "Time.hpp"
#include <SRE/SimpleRenderEngine.hpp>
#include <SRE/ParticleMesh.hpp>
#include <SRE/Texture.hpp>


SRE::ParticleMesh* ParticleEmitter::mesh = nullptr;
SRE::Shader* ParticleEmitter::shader = nullptr;

std::vector<glm::vec3> ParticleEmitter::positions = std::vector<glm::vec3>();
std::vector<float> ParticleEmitter::particleSize = std::vector<float>();
std::vector<glm::vec4> ParticleEmitter::colors = std::vector<glm::vec4>();
std::vector<glm::vec2> ParticleEmitter::uvs = std::vector<glm::vec2>();
std::vector<float> ParticleEmitter::uvSize = std::vector<float>();
std::vector<float> ParticleEmitter::uvRotation = std::vector<float>();

int ParticleEmitter::totalParticles = 0;

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

	auto position = gameObject->getComponent<Transform>()->getPosition();

	glm::vec3 a(0, -10, 0);
	float time = Time::getInstance()->getTime();
	float dt = time - startTime;

	numParticles = ceil(dt * config.rate);
	if (numParticles > maxParticles) numParticles = maxParticles;
	if (numParticles == maxParticles) mark = floor(fmod(dt, config.lifespan)/config.rate);

	for (int i = 0; i < numParticles; i++) {
		float t = fmod(dt + ((i+mark)%maxParticles)*(1/config.rate), config.lifespan);
		auto v0 = velocity;
		auto p0 = position;

		auto index = (i+mark) % maxParticles + pos;
		positions[index] = 0.5f*a*t*t + v0*t + p0;
		colors[index] = color;
	}
}

void ParticleEmitter::start()
{
	startTime = Time::getInstance()->getTime();
}

void ParticleEmitter::stop()
{
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

void ParticleEmitter::init(ParticleEmitterConfig config)
{
	this->config = config;
	maxParticles = ceil(config.lifespan * config.rate);
	numParticles = mark = 0;
	startTime = -1.0f;

	pos = totalParticles;
	for(int i = 0; i < maxParticles; i++)
	{
		totalParticles++;
		positions.push_back(glm::vec3());
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

