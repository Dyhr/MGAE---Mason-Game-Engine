#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>


class CameraDescriptor {
public:
	bool found = false;
	float fieldOfView = 60;
	float nearClip = 0.1f;
	float farClip = 1000;
};

class LightDescriptor
{
public:
	bool found = false;
};

class ParticleDescriptor
{
public:
	bool found = false;
};

class MeshDescriptor {
public:
	bool found = false;
	std::string name = "";
	glm::vec4 color = glm::vec4(1, 1, 1, 1);
};

class SpriteDescriptor {
public:
	bool found = false;
	std::string name = "";
	glm::vec4 color = glm::vec4(1, 1, 1, 1);
};

class TransformDescriptor{
public:
    glm::vec3 position = glm::vec3(0, 0, 0);
    glm::vec3 rotationEuler = glm::vec3(0, 0, 0);
    glm::vec3 scale = glm::vec3(1,1,1);
    int parentId = -1;
};

class GameObjectDescriptor {
public:
	std::string name = "Object";
	int uniqueId = 0;

	TransformDescriptor transform;
	MeshDescriptor mesh;
	SpriteDescriptor sprite;
	CameraDescriptor camera;
	LightDescriptor light;
};



class SceneParser{
public:
    static std::vector<GameObjectDescriptor> parseFile(std::string filename);
};
