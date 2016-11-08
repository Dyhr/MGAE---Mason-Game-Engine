#pragma once

#include "Component.hpp"
#include <SRE/Mesh.hpp>
#include <SRE/Shader.hpp>
#include "GameObject.hpp"
#include "glm/glm.hpp"
#include "SRE/Texture.hpp"
#include "SRE/SimpleRenderEngine.hpp"

class Transform;

class SpriteRenderer : public Component {
public:
	void SpriteRenderer::draw();
	
	void SpriteRenderer::setPos(glm::vec2 pos);
	void SpriteRenderer::setColor(glm::vec4 color);
	void SpriteRenderer::setAnchorX(float ax);
	void SpriteRenderer::setAnchorY(float ay);

	glm::vec2 SpriteRenderer::getPos();
	glm::vec4 SpriteRenderer::getColor();
	float SpriteRenderer::getAnchorX();
	float SpriteRenderer::getAnchorY();

	void  SpriteRenderer::setWidth(int width);
	void  SpriteRenderer::setHeight(int height);

	int  SpriteRenderer::getWidth();
	int  SpriteRenderer::getHeight();

protected:
	SpriteRenderer(GameObject *gameObject);
	~SpriteRenderer();
	friend class GameObject;
	SRE::Texture* texture;
	SRE::SimpleRenderEngine* sre;
	std::shared_ptr<SRE::Shader> shader;
	std::shared_ptr<SRE::Mesh> mesh;
	std::shared_ptr<Transform> transform;
	glm::vec4 color;
	glm::vec2 pos;
	// position,width and height uses pixel values texture coordinates (between 0.0 and 1.0)
	// relative position of anchor where 0.0 means to the left of the sprite and 1.0 means to the right of the sprite
	int height;
	int width;
	float anchorX;
	float anchorY;
};