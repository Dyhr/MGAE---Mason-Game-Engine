#pragma once

#include <glm/glm.hpp>
#include "Component.hpp"
#include <SRE/SimpleRenderEngine.hpp>

enum AttributeState {
	FIXED, RANDOM, LINEAR, SPLINE
};

struct ParticleEmitterConfig
{
	float rate;
	float lifespan;
	
	glm::vec3 velocity;
	glm::vec3 gravity;
	
	//Used for random
	float minSize;
	float maxSize;
	float minRotation;
	float maxRotation;
	glm::vec4 minColor;
	glm::vec4 maxColor;
	
	//Used for interpolation
	float initialSize;
	float finalSize;
	glm::vec4 initialColor;
	glm::vec4 finalColor;
	float initialRotation;
	float finalRotation;

	AttributeState colorState;
	AttributeState sizeState;
	AttributeState rotationState;
	
	void setRate(float _rate) {
		rate = _rate;
	}
	void setLifespan(float _lifespan) {
		lifespan = _lifespan;
	}
	void setVelocity(glm::vec3 _velocity) {
		velocity = _velocity;
	}
	void setGravity(glm::vec3 _gravity) {
		gravity = _gravity;
	}
	//SIZE SETTERS
	void setFixedSize(float size) {
		initialSize = size;
		finalSize = size;
		sizeState = AttributeState::FIXED;
	}
	void setRandomSize(float min, float max) {
		minSize = min;
		maxSize = max;
		sizeState = AttributeState::RANDOM;
	}
	void setLERPSize(float initial, float final) {
		initialSize = initial;
		finalSize = final;
		sizeState = AttributeState::LINEAR;
	}
	void setSplineInterpSize(float initial, float final) {
		initialSize = initial;
		finalSize = final;
		sizeState = AttributeState::SPLINE;
	}
	//COLOR SETTERS
	void setFixedColor(glm::vec4 color) {
		initialColor = color;
		finalColor = color;
		colorState = AttributeState::FIXED;
	}
	void setRandomColor(glm::vec4 min, glm::vec4 max) {
		minColor = min;
		maxColor = max;
		colorState = AttributeState::RANDOM;
	}
	void setLERPColor(glm::vec4 initial, glm::vec4 final) {
		initialColor = initial;
		finalColor = final;
		colorState = AttributeState::LINEAR;
	}
	void setSplineInterpColor(glm::vec4 initial, glm::vec4 final) {
		initialColor = initial;
		finalColor = final;
		colorState = AttributeState::SPLINE;
	}
	//ROTATION SETTERS
	void setFixedRotation(float rotation) {
		initialRotation = rotation;
		finalRotation = rotation;
		rotationState = AttributeState::FIXED;
	}
	void setRandomRotation(float min, float max) {
		minRotation = min;
		maxRotation = max;
		rotationState = AttributeState::RANDOM;
	}
	void setLERPRotation(float initial, float final) {
		initialRotation = initial;
		finalRotation = final;
		rotationState = AttributeState::LINEAR;
	}
	void setSplineInterpRotation(float initial, float final) {
		initialRotation = initial;
		finalRotation = final;
		rotationState = AttributeState::SPLINE;
	}	

	ParticleEmitterConfig()
		: rate(0),
		lifespan(0),
		velocity(glm::vec3()),
		gravity(glm::vec3()),
		initialSize(0),
		finalSize(0),
		initialColor(glm::vec4()),
		finalColor(glm::vec4())
	{
	}

	ParticleEmitterConfig(float rate, float lifespan, glm::vec3 velocity, glm::vec3 gravity)
		: rate(rate),
		lifespan(lifespan),
		velocity(velocity),
		gravity(gravity)
	{
	}
};

class ParticleEmitter : public Component {
public:
	static void render();

	~ParticleEmitter();

	void init(ParticleEmitterConfig config);
	void update();
	void start();
	void stop();
	bool running();
protected:
	static SRE::ParticleMesh* mesh;
	static SRE::Shader* shader;

	static std::vector<glm::vec3> positions;
	static std::vector<float> sizes;
	static std::vector<glm::vec4> colors;
	static std::vector<glm::vec2> uvs;
	static std::vector<float> uvSize;
	static std::vector<float> uvRotation;
	static int totalParticles;

	static std::vector<float> birthTimes;
	static std::vector<float> times;
	static std::vector<glm::vec3> velocities;

	ParticleEmitter(GameObject *gameObject);

	ParticleEmitterConfig config;
	int numParticles, maxParticles, pos;
	float startTime;

	friend class GameObject;
};
