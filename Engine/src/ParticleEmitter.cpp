#include "ParticleEmitter.hpp"


SRE::ParticleMesh* ParticleEmitter::mesh = nullptr;
SRE::Shader* ParticleEmitter::shader = nullptr;

ParticleEmitter::ParticleEmitter(GameObject * gameObject) : Component(gameObject) {
	if(shader == nullptr)
		shader = SRE::Shader::getStandardParticles();
	if (mesh == nullptr)
		mesh = nullptr;//new SRE::ParticleMesh(finalPos, colors, uvs, uvSize, uvRotation, particleSize);
}

void ParticleEmitter::setVelocity(glm::vec3 velocity) {
	this->velocity = velocity;
}

void ParticleEmitter::update()
{
	auto transform = gameObject->getComponent<Transform>()->globalTransform();
	auto position = glm::vec3(transform[3]);
}

void ParticleEmitter::render() {
	shader->set("tex", SRE::Texture::getSphereTexture());
	SRE::SimpleRenderEngine::instance->draw(mesh, glm::mat4(1), shader);
}

void ParticleEmitter::setColor(glm::vec4 color) {
	this->color = color;
}

