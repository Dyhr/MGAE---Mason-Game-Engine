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
	auto transform = gameObject->getComponent<Transform>()->globalTransform();
	auto position = glm::vec3(transform[3]);

	glm::vec3 a(0, -10, 0);

	for (int i = 0; i<positions.size(); i++) {
		/*float t = Time::getInstance()->getTime() - particles[i].timeOfBirth;
		auto v0 = particles[i].velocity;
		auto p0 = particles[i].position;
		positions[i] = 0.5f*a*t*t + v0*t + p0;*/
	}
}

void ParticleEmitter::render() {
	mesh->update(positions, colors, uvs, uvSize, uvRotation, particleSize);
	shader->set("tex", SRE::Texture::getSphereTexture());
	SRE::SimpleRenderEngine::instance->draw(mesh, glm::mat4(1), shader);
}

void ParticleEmitter::setColor(glm::vec4 color) {
	this->color = color;
}

