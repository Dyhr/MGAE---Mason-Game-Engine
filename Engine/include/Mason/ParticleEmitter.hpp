#pragma once

#include <glm/glm.hpp>
#include "Component.hpp"
#include <SRE/SimpleRenderEngine.hpp>
#include <math.h>
#include <SRE/Texture.hpp>


namespace Mason {

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

		glm::vec2 *splinePointsColor;
		glm::vec2 *splinePointsSize;
		glm::vec2 *splinePointsRotation;

		AttributeState colorState;
		AttributeState sizeState;
		AttributeState rotationState;
		glm::vec2 *normalize(glm::vec2 input[4]) {
			auto minX = input[0].x;
			auto maxX = input[0].x;
			auto minY = input[0].y;
			auto maxY = input[0].x;
			for (int i = 1; i < 4; i++) {
				if (input[i].x < minX) {
					minX= input[i].x;
				}
				if (input[i].x > maxX) {
					maxX = input[i].x;
				}
				if (input[i].y < minY) {
					minY = input[i].y;
				}
				if (input[i].y > minY) {
					maxY = input[i].y;
				}
			}
			input[0].x = (input[0].x - minX) / (maxX - minX);
			input[1].x = (input[1].x - minX) / (maxX - minX);
			input[2].x = (input[2].x - minX) / (maxX - minX);
			input[3].x = (input[3].x - minX) / (maxX - minX);
			input[0].y = (input[0].y - minY) / (maxY - minY);
			input[1].y = (input[1].y - minY) / (maxY - minY);
			input[2].y = (input[2].y - minY) / (maxY - minY);
			input[3].y = (input[3].y - minY) / (maxY - minY);
			return input;
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
		void setSplineInterpSize(float initial, float final, glm::vec2 splinePoints[4]) {
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
		void setSplineInterpColor(glm::vec4 initial, glm::vec4 final, glm::vec2 splinePoints[4]) {
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
		void setSplineInterpRotation(float initial, float final, glm::vec2 splinePoints[4]) {
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
		static void render(SRE::Texture * tex);
		static void clear();

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

		static glm::vec2 cubicBezier(float t, glm::vec2 splinePoints[4]);

		ParticleEmitter(GameObject *gameObject);

		ParticleEmitterConfig config;
		int numParticles, maxParticles, pos;
		float startTime;

		friend class GameObject;
	};
}