#pragma once

#include <glm/glm.hpp>
#include "Component.hpp"
#include <SRE/SimpleRenderEngine.hpp>
#include <math.h>
#include <SRE/Texture.hpp>
#include <vector>
#include <iostream>


namespace Mason {

	enum AttributeState {
		FIXED, RANDOM, LINEAR, SPLINE
	};

	struct ParticleEmitterConfig
	{
		SRE::Texture *tex = nullptr;
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
		glm::vec3 minVelocity;
		glm::vec3 maxVelocity;

		//Used for interpolation
		float initialSize;
		float finalSize;
		glm::vec4 initialColor;
		glm::vec4 finalColor;
		float initialRotation;
		float finalRotation;

		std::vector<glm::vec2> splinePointsColor;
		std::vector<glm::vec2> splinePointsSize;
		std::vector<glm::vec2> splinePointsRotation;

		AttributeState colorState;
		AttributeState sizeState;
		AttributeState rotationState;
		AttributeState velocityState;
		AttributeState attributeFromString(std::string str) {
			if (str == "fixed") return AttributeState::FIXED;
			if (str == "random") return AttributeState::RANDOM;
			if (str == "linear") return AttributeState::LINEAR;
			if (str == "spline") return AttributeState::SPLINE;
			return AttributeState::FIXED;
		}
		std::vector<glm::vec2> normalize(std::vector<glm::vec2>  input) {

			auto minX = input[0].x;
			auto maxX = input[0].x;
			auto minY = input[0].y;
			auto maxY = input[0].x;
			for (auto v : input) {
				if (v.x < minX) {
					minX= v.x;
				}
				if (v.x > maxX) {
					maxX = v.x;
				}
				if (v.y < minY) {
					minY = v.y;
				}
				if (v.y > minY) {
					maxY = v.y;
				}
			}
			for (auto v : input) {
				v.x = (v.x - minX) / ( maxX - minX);
			}
			return input;
		}
		void setTexture(SRE::Texture *_tex) {
			tex = _tex;
		}
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
		void setFixedVelocity(glm::vec3 vel) {
			velocity = vel;
			velocityState = FIXED;
		}
		void setRandomVelocity(glm::vec3 minVel, glm::vec3 maxVel) {
			minVelocity = minVel;
			maxVelocity = maxVel;
			velocityState = RANDOM;
		}
		//SIZE SETTERS
		void setFixedSize(float size) {
			initialSize = size;
			finalSize = size;
			sizeState = FIXED;
		}
		void setRandomSize(float min, float max) {
			minSize = min;
			maxSize = max;
			sizeState = RANDOM;
		}
		void setLERPSize(float initial, float final) {
			initialSize = initial;
			finalSize = final;
			sizeState = LINEAR;
		}
		void setSplineInterpSize(float initial, float final, std::vector<glm::vec2>  splinePoints) {
			initialSize = initial;
			finalSize = final;
			splinePointsSize = normalize(splinePoints);
			sizeState = SPLINE;
		}
		//COLOR SETTERS
		void setFixedColor(glm::vec4 color) {
			initialColor = color;
			finalColor = color;
			colorState = FIXED;
		}
		void setRandomColor(glm::vec4 min, glm::vec4 max) {
			minColor = min;
			maxColor = max;
			colorState = RANDOM;
		}
		void setLERPColor(glm::vec4 initial, glm::vec4 final) {
			initialColor = initial;
			finalColor = final;
			colorState = LINEAR;
		}
		void setSplineInterpColor(glm::vec4 initial, glm::vec4 final, std::vector<glm::vec2>  splinePoints) {
			initialColor = initial;
			finalColor = final;
			splinePointsColor = normalize(splinePoints);
			colorState = SPLINE;
		}
		//ROTATION SETTERS
		void setFixedRotation(float rotation) {
			initialRotation = rotation;
			finalRotation = rotation;
			rotationState = FIXED;
		}
		void setRandomRotation(float min, float max) {
			minRotation = min;
			maxRotation = max;
			rotationState = RANDOM;
		}
		void setLERPRotation(float initial, float final) {
			initialRotation = initial;
			finalRotation = final;
			rotationState = LINEAR;
		}
		void setSplineInterpRotation(float initial, float final, std::vector<glm::vec2> splinePoints) {
			initialRotation = initial;
			finalRotation = final;
			splinePointsRotation = normalize(splinePoints);
			rotationState = SPLINE;
		}

		ParticleEmitterConfig()
			: rate(0),
			lifespan(0),
			velocity(glm::vec3()),
			gravity(glm::vec3()),
			initialSize(0),
			finalSize(0),
			initialColor(glm::vec4()),
			finalColor(glm::vec4()),
			initialRotation(0),
			finalRotation (0)
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
		void render();
		void clear();

		~ParticleEmitter();

		void init(ParticleEmitterConfig config);
		void update(float deltaTimeSec);
		void start();
		void stop();
		bool running();
	protected:
		SRE::ParticleMesh* mesh = nullptr;
		SRE::Shader* shader = nullptr;

		std::vector<glm::vec3> positions = std::vector<glm::vec3>();
		std::vector<float> sizes = std::vector<float>();
		std::vector<glm::vec4> colors = std::vector<glm::vec4>();
		std::vector<glm::vec2> uvs = std::vector<glm::vec2>();
		std::vector<float> uvSize = std::vector<float>();
		std::vector<float> uvRotation = std::vector<float>();
		int totalParticles = 0;
		std::vector<float> birthTimes = std::vector<float>();
		std::vector<float> age = std::vector<float>();
		std::vector<glm::vec3> velocities = std::vector<glm::vec3>();

		glm::vec2 cubicBezier(float t, std::vector<glm::vec2> splinePoints);
		void updateModel(float deltaTimeSec);
		ParticleEmitter(GameObject *gameObject);

		ParticleEmitterConfig config;
		int numParticles, maxParticles, pos;
		float startTime;
		float lastUpdateTime = 0;
		friend class GameObject;
	};
}