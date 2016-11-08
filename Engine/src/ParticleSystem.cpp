#include "ParticleSystem.hpp"


Particle::Particle(glm::vec3 position, glm::vec3 velocity, float timeOfBirth)
	: position(position), velocity(velocity), timeOfBirth(timeOfBirth) {
}

ParticleSystem::ParticleSystem(int size)
	: currentTime(0.0f), emissionIndex(0), mesh(nullptr) {
	shader = SRE::Shader::getStandardParticles();

	for (int i = 0; i<size; i++) {
		particles.push_back(Particle(glm::vec3{ 0,0,0 }, glm::vec3{ 0,-1,0 }, -999999));
		finalPos.push_back(glm::vec3{ 0,0,0 });
		particleSize.push_back(0.5f);
		colors.push_back(glm::vec4{ 1, 1, 1, 1 });
	}
	update(0);
}

void ParticleSystem::emit(glm::vec3 position, glm::vec3 velocity, glm::vec4 color) {
	particles[emissionIndex].timeOfBirth = currentTime;
	particles[emissionIndex].position = position;
	particles[emissionIndex].velocity = velocity;
	colors[emissionIndex] = color;
	emissionIndex = (emissionIndex + 1) % particles.size();
}

void ParticleSystem::update(float deltaTime) {
	glm::vec3 a(0, gravity, 0);

	for (int i = 0; i<finalPos.size(); i++) {
		float t = currentTime - particles[i].timeOfBirth;
		auto v0 = particles[i].velocity;
		auto p0 = particles[i].position;
		finalPos[i] = 0.5f*a*t*t + v0*t + p0;
	}
	//unused - using default values
	//std::vector<glm::vec4> colors;
	std::vector<glm::vec2> uvs;
	std::vector<float> uvSize;
	std::vector<float> uvRotation;

	if (mesh == nullptr) {
		mesh = new SRE::ParticleMesh(finalPos, colors, uvs, uvSize, uvRotation, particleSize);
	}
	else {
		mesh->update(finalPos, colors, uvs, uvSize, uvRotation, particleSize);
	}
	currentTime += deltaTime;
}

void ParticleSystem::render() {
	shader->set("tex", SRE::Texture::getSphereTexture());
	SRE::SimpleRenderEngine::instance->draw(mesh, glm::mat4(1), shader);
}
