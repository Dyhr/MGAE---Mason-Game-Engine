#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "Mason/ParticleEmitter.hpp"
#include "Mason/Collider2D.hpp"
#include "Box2D/Box2D.h"
#include "Audio.hpp"


namespace Mason {
	class CameraDescriptor {
	public:
		bool found = false;
		glm::vec2 viewportMin = glm::vec2(0, 0);
		glm::vec2 viewportMax = glm::vec2(1, 1);
	};

	class ParticleDescriptor
	{
	public:
		bool found = false;
		std::string texturePath = "";
		float rate;
		float lifespan;
		glm::vec3 velocity;
		glm::vec3 gravity;
		//Used for random
		float minSize;
		float maxSize;
		float minRotation;
		float maxRotation;
		glm::vec3 minVelocity;
		glm::vec3 maxVelocity;
		glm::vec4 minColor;
		glm::vec4 maxColor;
		//Used for interpolation
		float initialSize;
		float finalSize;
		glm::vec4 initialColor;
		glm::vec4 finalColor;
		float initialRotation;
		float finalRotation;

		std::string velocityState;
		std::string rotationState;
		std::string sizeState;
		std::string colorState;
		std::vector<glm::vec2> splinePointsSize;
		std::vector<glm::vec2> splinePointsColor;
		std::vector<glm::vec2> splinePointsRotation;
	};

	class SpriteDescriptor {
	public:
		bool found = false;
		std::string name = "";
		glm::vec4 color = glm::vec4(1, 1, 1, 1);
	};

	class PhysicsBodyDescriptor {
	public:
		bool found = false;
		b2BodyType type;		
	};

	class BoxColliderDescriptor {
	public:
		bool found = false;
		glm::vec2 center;
		float width;
		float height;
	};

	class CircleColliderDescriptor {
	public:
		bool found = false;
		glm::vec2 center = glm::vec2(0, 0);
		float radius = 1;
	};

	class TransformDescriptor {
	public:
		glm::vec3 position = glm::vec3(0, 0, 0);
		glm::vec3 rotationEuler = glm::vec3(0, 0, 0);
		glm::vec3 scale = glm::vec3(1, 1, 1);
		int parentId = -1;
	};

	class AudioDescriptor {
	public:
		std::string path;
		//SoundEffect or Music?
		SoundType type;
		bool found = false;
	};

	class GameObjectDescriptor {
	public:
		std::string name = "Object";
		int uniqueId = 0;

		TransformDescriptor transform;
		SpriteDescriptor sprite;
		CameraDescriptor camera;
		AudioDescriptor audio;
		ParticleDescriptor particles;
		CircleColliderDescriptor circleCollider;
		BoxColliderDescriptor boxCollider;
		PhysicsBodyDescriptor physicsBody2D;
	};


	class SceneDescriptor {
	public:
		std::string name = "Scene";

		std::string imagepath = "data/images";
		std::string soundpath = "data/sounds";

		std::vector<GameObjectDescriptor> gameobjects;
	};



	class SceneParser {
	public:
		static SceneDescriptor parseFile(std::string filename);
	};
}
