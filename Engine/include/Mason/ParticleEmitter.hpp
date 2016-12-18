#pragma once

#include <glm/glm.hpp>
#include "Component.hpp"
#include <math.h>
#include <vector>
#include <iostream>

namespace SRE
{
	class Texture;
	class ParticleMesh;
	class Shader;
}

namespace Mason {
	/** @enum AttributeState
	* @param Used for velocity (FIXED | RANDOM), size (FIXED | RANDOM | LINEAR | SPLINE), color (FIXED | RANDOM | LINEAR | SPLINE), and rotation (FIXED | RANDOM | LINEAR | SPLINE) behavior.
	*/
	enum AttributeState {
		FIXED, RANDOM, LINEAR, SPLINE
	};
	/** @class ParticleEmitterConfig
	* @brief Struct used for configuring a ParticleEmitter component.
	*/
	struct ParticleEmitterConfig
	{

		SRE::Texture* tex = nullptr; ///< Particle texture pointer. see @SRE
		float rate; ///< Emission rate in particles/second
		float lifespan; ///< Allowed lifetime for particles in seconds.

		glm::vec3 velocity; ///< Velocity of particles at emission. ONLY USED FOR VelocityState == AttributeState::FIXED
		glm::vec3 gravity; ///< Acceleration acting on particles during lifespan.

		//Used for random
		float minSize; ///< Minimum size of particles at emission. ONLY used when SizeState == AttributeState::RANDOM or AttributeState::FIXED
		float maxSize; ///< Maximum size of particles at emission. ONLY used when SizeState == AttributeState::RANDOM or AttributeState::FIXED
		float minRotation; ///< Minimum rotation of particles at emission. ONLY used when RotationState == AttributeState::RANDOM or AttributeState::FIXED, uses radians
		float maxRotation; ///< Minimum rotation of particles at emission. ONLY used when RotationState == AttributeState::RANDOM or AttributeState::FIXED, uses radians
		glm::vec4 minColor; ///< Minimum color of particles at emission. ONLY used when ColorState == AttributeState::RANDOM or AttributeState::FIXED
		glm::vec4 maxColor; ///< Maximum color of particles at emission. ONLY used when ColorState == AttributeState::RANDOM or AttributeState::FIXED
		glm::vec3 minVelocity; ///< Minimum velocity of particles at emission. ONLY used when VelocityState == AttributeState::RANDOM
		glm::vec3 maxVelocity; ///< Maximum velocity of particles at emission. ONLY used when VelocityState == AttributeState::RANDOM

		//Used for interpolation
		float initialSize; ///< Initial size of particles at emission. ONLY used when SizeState == AttributeState::LINEAR or AttributeState::SPLINE
		float finalSize; ///< Final size of particles at end of lifespan. ONLY used when SizeState == AttributeState::LINEAR or AttributeState::SPLINE
 		glm::vec4 initialColor; ///< Initial color of particles at emission. ONLY used when ColorState == AttributeState::LINEAR or AttributeState::SPLINE
		glm::vec4 finalColor; ///< Final color of particles at end of lifespan. ONLY used when ColorState == AttributeState::LINEAR or AttributeState::SPLINE
		float initialRotation; ///< Initial rotation of particles at emission. ONLY used when RotationState == AttributeState::LINEAR or AttributeState::SPLINE, uses radians
		float finalRotation; ///< Final rotation of particles at end of lifespan. ONLY used when RotationState == AttributeState::LINEAR or AttributeState::SPLINE, uses radians

		std::vector<glm::vec2> splinePointsColor; ///< List of points used for spline interpolation between initial and final colors
		std::vector<glm::vec2> splinePointsSize; ///< List of points used for spline interpolation between initial and final sizes
		std::vector<glm::vec2> splinePointsRotation; ///< List of points used for spline interpolation between initial and final rotations

		AttributeState colorState; ///< Enum defining color behavior, either FIXED, RANDOM, LINEAR, or SPLINE
		AttributeState sizeState; ///< Enum defining size behavior, either FIXED, RANDOM, LINEAR, or SPLINE
		AttributeState rotationState; ///< Enum defining rotation behavior, either FIXED, RANDOM, LINEAR, or SPLINE
		AttributeState velocityState; ///< Enum defining velocity behavior, either FIXED or RANDOM
		/** @brief Convert string value to enum value for AttributeStates. Returns FIXED as default.
		* @param str attribute state string to be converted.
		*/
		AttributeState attributeFromString(std::string str) {
			if (str == "fixed") return FIXED;
			if (str == "random") return RANDOM;
			if (str == "linear") return LINEAR;
			if (str == "spline") return SPLINE;
			return FIXED;
		}
		/** @brief Normalizes list of points to have values between 0 and 1
		* @param input list of points
		*/
		std::vector<glm::vec2> normalize(std::vector<glm::vec2> input) {

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
		/** @brief Set the tex pointer
		* @param _tex see @SRE
		*/
		void setTexture(SRE::Texture *_tex) {
			tex = _tex;
		}
		/** @brief Set the emission rate.
		* @param _rate emission rate in particles/second.
		*/
		void setRate(float _rate) {
			rate = _rate;
		}
		/** @brief Set the particle lifespan.
		* @param _lifespan particle lifespan in seconds.
		*/
		void setLifespan(float _lifespan) {
			lifespan = _lifespan;
		}
		/** @brief Set the acceleration acting on particles
		* @param _gravity acceleration in pixels pr. second squared. Use .z = 0 for 2D
		*/
		void setGravity(glm::vec3 _gravity) {
			gravity = _gravity;
		}
		/** @brief Set the fixed emission velocity
		* @param vel velocity in pixels pr. second. Use .z = 0 for 2D
		*/
		void setFixedVelocity(glm::vec3 vel) {
			velocity = vel;
			velocityState = FIXED;
		}
		/** @brief Set emission velocity interval 
		* @param minVel minimum velocity in pixels pr. second. Use .z = 0 for 2D
		* @param maxVel maximum velocity in pixels pr. second. Use .z = 0 for 2D
		*/
		void setRandomVelocity(glm::vec3 minVel, glm::vec3 maxVel) {
			minVelocity = minVel;
			maxVelocity = maxVel;
			velocityState = RANDOM;
		}
		//SIZE SETTERS
		/** @brief Set the fixed size of particles
		* @param size fixed size of particles
		*/
		void setFixedSize(float size) {
			initialSize = size;
			finalSize = size;
			sizeState = FIXED;
		}
		/** @brief Set the interval for random size
		* @param min minimum size for random
		* @param min maximum size for random
		*/
		void setRandomSize(float min, float max) {
			minSize = min;
			maxSize = max;
			sizeState = RANDOM;
		}
		/** @brief Set initial and final size for linear interpolation
		* @param initial initial size
		* @param final final size
		*/
		void setLERPSize(float initial, float final) {
			initialSize = initial;
			finalSize = final;
			sizeState = LINEAR;
		}
		/** @brief Set initial and final size for spline interpolation using the given points to interpolate between
		* @param initial initial size
		* @param final final size
		* @param splinePoints list of N points for interpolation
		*/
		void setSplineInterpSize(float initial, float final, std::vector<glm::vec2>  splinePoints) {
			initialSize = initial;
			finalSize = final;
			splinePointsSize = normalize(splinePoints);
			sizeState = SPLINE;
		}
		//COLOR SETTERS
		/** @brief Set the fixed color of particles
		* @param color fixed color of particles
		*/
		void setFixedColor(glm::vec4 color) {
			initialColor = color;
			finalColor = color;
			colorState = FIXED;
		}
		/** @brief Set the interval for random color
		* @param min minimum color for random
		* @param min maximum color for random
		*/
		void setRandomColor(glm::vec4 min, glm::vec4 max) {
			minColor = min;
			maxColor = max;
			colorState = RANDOM;
		}
		/** @brief Set initial and final color for linear interpolation
		* @param initial initial color
		* @param final final color
		*/
		void setLERPColor(glm::vec4 initial, glm::vec4 final) {
			initialColor = initial;
			finalColor = final;
			colorState = LINEAR;
		}
		/** @brief Set initial and final color for spline interpolation using the given points to interpolate between
		* @param initial initial color
		* @param final final color
		* @param splinePoints list of N points for interpolation
		*/
		void setSplineInterpColor(glm::vec4 initial, glm::vec4 final, std::vector<glm::vec2>  splinePoints) {
			initialColor = initial;
			finalColor = final;
			splinePointsColor = normalize(splinePoints);
			colorState = SPLINE;
		}
		//ROTATION SETTERS
		/** @brief Set the fixed rotation of particles
		* @param rotation fixed rotation of particles
		*/
		void setFixedRotation(float rotation) {
			initialRotation = rotation;
			finalRotation = rotation;
			rotationState = FIXED;
		}
		/** @brief Set the interval for random rotation
		* @param min minimum rotation for random
		* @param min maximum rotation for random
		*/
		void setRandomRotation(float min, float max) {
			minRotation = min;
			maxRotation = max;
			rotationState = RANDOM;
		}
		/** @brief Set initial and final rotation for linear interpolation
		* @param initial initial rotation
		* @param final final rotation
		*/
		void setLERPRotation(float initial, float final) {
			initialRotation = initial;
			finalRotation = final;
			rotationState = LINEAR;
		}
		/** @brief Set initial and final rotation for spline interpolation using the given points to interpolate between
		* @param initial initial rotation
		* @param final final rotation
		* @param splinePoints list of N points for interpolation
		*/
		void setSplineInterpRotation(float initial, float final, std::vector<glm::vec2> splinePoints) {
			initialRotation = initial;
			finalRotation = final;
			splinePointsRotation = normalize(splinePoints);
			rotationState = SPLINE;
		}
		/** @brief Constructor
		*/
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
		/** @brief Constructor
		* @param rate emission rate in particles/second
		* @param lifespan particle lifespan in seconds
		* @param velocity initial fixed particle velocity. pixels per second
		* @param gravity acceleration acting on particles through lifespan. pixels per second squared
		*/
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
		/** @brief Renders the current model for the ParticleEmitter.
		*/
		void render();		
		/** @brief Destructor.
		*/
		~ParticleEmitter();
		/** @brief Initialize a particle emitter
		* @param config An instance of the ParticleEmitterConfig struct that configures the ParticleEmitter.
		*/
		void init(ParticleEmitterConfig config);
		/** @brief Called once every frame. Updates the model of the particleemitter.
		* @param amount of time since last update
		*/
		void update(float deltaTimeSec);
		/** @brief Start emitting particles. Will not have any effect if the emitter has particles that have not expired yet.
		*/
		void start();
		/** @brief Stop emitting new particles. Spawned particles will go through their lifespan and expire naturally.
		*/
		void stop();
	private:

		SRE::ParticleMesh* mesh = nullptr; 
		SRE::Shader* shader = nullptr; 

		std::vector<glm::vec3> positions = std::vector<glm::vec3>(); 
		std::vector<float> sizes = std::vector<float>(); 
		std::vector<glm::vec4> colors = std::vector<glm::vec4>(); 
		std::vector<glm::vec2> uvs = std::vector<glm::vec2>(); 
		std::vector<float> uvSize = std::vector<float>();
		std::vector<float> uvRotation = std::vector<float>();
		std::vector<float> ages = std::vector<float>();	
		std::vector<glm::vec3> velocities = std::vector<glm::vec3>(); 

		glm::vec2 cubicBezier(float t, std::vector<glm::vec2> splinePoints); 
		void updateModel(float deltaTimeSec);
		ParticleEmitter(std::shared_ptr<GameObject> gameObject);

		ParticleEmitterConfig config;
		int numParticles, maxParticles;
		int bodyCount = 0;
		float runTime = 0;
		float startTime = -1;
		float stopTime;
		float lastUpdateTime = 0;
		bool emitNewParticles = false;
		friend class GameObject;
	};
}