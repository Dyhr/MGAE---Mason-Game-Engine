#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <map>
#include "Mason/Audio.hpp"
#include "picojson.h"


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

	class BoxColliderDescriptor {
	public:
		glm::vec2 center = glm::vec2(0, 0);
		float width = 1;
		float height = 1;

		float density = 1;
		float friction = 0.1f;
	};

	class CircleColliderDescriptor {
	public:
		glm::vec2 center = glm::vec2(0, 0);
		float radius = 1;

		float density = 1;
		float friction = 0.1f;
	};

	class PhysicsBodyDescriptor {
	public:
		bool found = false;
		int type;
		std::vector<BoxColliderDescriptor> boxColliders;
		std::vector<CircleColliderDescriptor> circleColliders;
	};

	class TransformDescriptor {
	public:
		glm::vec3 position = glm::vec3(0, 0, 0);
		float rotation = 0.0f;
		float scale = 1.0f;
		int parentId = -1;
	};

	class AudioDescriptor {
	public:
		std::string path;
		//SoundEffect or Music?
		SoundType type;
		bool found = false;
	};

	class ScriptDescriptor {
	public:
		std::string name;
		std::map<std::string, std::string> strings;
		std::map<std::string, float> numbers;
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
		std::vector<ScriptDescriptor> scripts;
		PhysicsBodyDescriptor physicsBody2D;
	};


	class SceneDescriptor {
	public:
		std::string name = "Scene";

		std::string imagepath = "data/images";
		std::string soundpath = "data/sounds";
		std::string templatepath = "data/templates";

		std::vector<std::string> sprites;

		std::vector<GameObjectDescriptor> gameobjects;

		glm::vec2 gravity = glm::vec2(0, -10);
		float physicsScale = 100;
	};

	class SceneParser {
	protected:
		static SceneDescriptor parseFile(std::string filename);
		static GameObjectDescriptor parseTemplate(std::string name, std::string path);

		friend class Engine;
		friend class Scene;
	private:
		static GameObjectDescriptor parseObject(picojson::value o, std::string path);
	};
}
