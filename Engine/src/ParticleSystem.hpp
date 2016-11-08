#pragma once

#include <SRE\ParticleMesh.hpp>
#include <SRE\Texture.hpp>
#include <SRE\SimpleRenderEngine.hpp>
#include <glm\glm.hpp>

#include <vector>
#include <SRE\Shader.hpp>

class Particle {
public:
    Particle(glm::vec3 position,glm::vec3 velocity,float timeOfBirth);
    glm::vec3 position;
    glm::vec3 velocity;
    float timeOfBirth;

};

class ParticleSystem {
public:
    ParticleSystem(int size);

    void emit(glm::vec3 position, glm::vec3 velocity, glm::vec4 color);
    void update(float deltaTime);
    void render();
private:
    const float gravity = -9.8f;
    float currentTime;
    int emissionIndex;
    SRE::ParticleMesh* mesh;
    std::vector<glm::vec3> finalPos;
    std::vector<float> particleSize;
    std::vector<Particle> particles;
	std::vector<glm::vec4> colors;
    SRE::Shader* shader;
};

