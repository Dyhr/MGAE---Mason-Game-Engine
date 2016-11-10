#include "GameObject.hpp"
#include <SRE\SimpleRenderEngine.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "SpriteRenderer.h"
using namespace SRE;

SpriteRenderer::SpriteRenderer(GameObject *gameObject):Component(gameObject) {
	transform = gameObject->getComponent<Transform>();

	//provisional position
	float x = 0, y = 0;
	//(transform-position, int width, int height, float anchorX, float anchorY, SRE::Texture * texture, SRE::SimpleRenderEngine * sre)
	//need to read the size of the Mesh from a file 
	this->width = width;
	this->height = height;

	float fwidth = (float)texture->getWidth();
	float fheight = (float)texture->getHeight();

	float lower_x = (float)x / fwidth;
	float lower_y = (float)y / fheight;

	float higher_x = lower_x + (float)width / fwidth;
	float higher_y = lower_y + (float)height / fheight;

	//we move the pivot point to the centre as anchorX and anchorY indicate.
	//we are actually moving the whole sprite (the mesh) to make its centre meet the rotation point that is right now at (0,0)
	//depending of where we situate the pivot, the object will act different 


	int minX = 0 - (width*anchorX);
	int maxX = width - (width*anchorX);
	int minY = 0 - (height*anchorY);
	int maxY = height - (height*anchorY);

	// The coordinates used for rendering, two triangles is used to create a square defined in windows coordinates
	std::vector<glm::vec3> vertices({
		glm::vec3{ maxX, minY, 0 }, glm::vec3{ maxX, maxY, 0 },glm::vec3{ minX, minY, 0 },
		glm::vec3{ minX, minY, 0 }, glm::vec3{ maxX, maxY, 0 }, glm::vec3{ minX, maxY, 0 }
	});
	// Normals are not used for 2D graphics, refer to the direction where the object faces
	std::vector<glm::vec3> normals;
	// UVs containts the normalized texture coordinates.
	std::vector<glm::vec2> uvs({
		glm::vec2{ higher_x, lower_y }, glm::vec2{ higher_x, higher_y }, glm::vec2{ lower_x, lower_y },
		glm::vec2{ lower_x, lower_y }, glm::vec2{ higher_x, higher_y }, glm::vec2{ lower_x, higher_y }
	});

	this->mesh = std::shared_ptr<Mesh>(new Mesh(vertices, normals, uvs));
}


SpriteRenderer::~SpriteRenderer()
{

}
void SpriteRenderer::draw() {
	if (transform) {
		shader->setVector("color", color);
		SRE::SimpleRenderEngine::instance->draw(&*mesh, transform->globalTransform(), &*shader);
	}
}

void SpriteRenderer::setPos(glm::vec2 pos) {
	this->pos = pos;
}

void SpriteRenderer::setColor(glm::vec4 color) {
	this->color = color;
}

void SpriteRenderer::setAnchorX(float ax) {
	this->anchorX=ax;
}

void SpriteRenderer::setAnchorY(float ay) {
	this->anchorY=ay;
}

glm::vec2 SpriteRenderer::getPos() {
	return this->pos;
}

glm::vec4 SpriteRenderer::getColor() {
	return this->color;
}
float SpriteRenderer::getAnchorX() {
	return this->anchorX;
}
float SpriteRenderer::getAnchorY() {
	return this->anchorY;
}

void  SpriteRenderer::setWidth(int width) {
	this->width = width;

}
void  SpriteRenderer::setHeight(int height) {
	this->height = height;
}

int  SpriteRenderer::getWidth() {
	return this->width;
}
int  SpriteRenderer::getHeight() {
	return this->height;
}
