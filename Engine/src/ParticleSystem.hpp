#pragma once
#include <SRE\ParticleMesh.hpp>
#include <glm\glm.hpp>
#include <SRE\ParticleMesh.hpp>

#include <vector>
#include <SRE\Shader.hpp>
#include "Component.hpp"
#include "GameObject.hpp"
#include <memory>

class Particle {
public:
	Particle(glm::vec3 position, glm::vec3 velocity);
	glm::vec3 position;
	glm::vec3 velocity;
	float drag = 0.01;
};

class ParticleSystem : public Component {
public:	
	void loadShader(std::shared_ptr<SRE::Shader> newShader);
	void loadMesh(std::shared_ptr<SRE::ParticleMesh> newMesh);
	void setSize(int size);
	void emit(glm::vec3 velocity);
	void update(float deltaTime);
	void render();
	void init();
protected:
	ParticleSystem(GameObject *gameObject);
	friend class GameObject;
	std::shared_ptr<SRE::Shader> shader;
	std::shared_ptr<SRE::ParticleMesh> mesh;
	std::vector<glm::vec3> finalPos;
	std::vector<float> particleSizes;
	std::vector<Particle> particles;
private:
	const float gravity = -9.8f;
	float currentTime;
	int emissionIndex;
	int m_size;

};