#pragma once

#include "Transform.h"
#include <SRE/Mesh.hpp>
#include <SRE/Shader.hpp>
#include "GameObject.hpp"

class Transform;

class Rendering : public Component {
public:
	void draw();
	void loadMesh(std::shared_ptr<SRE::Mesh> mesh);
	void loadShader(std::shared_ptr<SRE::Shader> shader);
	void setColor(glm::vec4 color);
protected:
	Rendering(GameObject *gameObject);
	friend class GameObject;
	std::shared_ptr<SRE::Shader> shader;
	std::shared_ptr<SRE::Mesh> mesh;
	std::shared_ptr<Transform> transform;
	glm::vec4 color;
};