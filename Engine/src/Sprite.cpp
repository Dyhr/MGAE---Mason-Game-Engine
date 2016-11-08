
#include "Sprite.h"
#include <SRE\Shader.hpp>
#include <glm\gtc\matrix_transform.hpp>
using namespace SRE;

Sprite::Sprite(int x, int y, int width, int height, float anchorX, float anchorY, SRE::Texture * texture, SRE::SimpleRenderEngine * sre)
{
	this->texture = texture;
	this->sre = sre;


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
	// Normals are not used for 2D graphics
	std::vector<glm::vec3> normals;
	// UVs containts the normalized texture coordinates.
	std::vector<glm::vec2> uvs({
		glm::vec2{ higher_x, lower_y }, glm::vec2{ higher_x, higher_y }, glm::vec2{ lower_x, lower_y },
		glm::vec2{ lower_x, lower_y }, glm::vec2{ higher_x, higher_y }, glm::vec2{ lower_x, higher_y }
	});

	this->mesh = new Mesh(vertices, normals, uvs);

}

Sprite::~Sprite()
{
	delete this->mesh;
}

void Sprite::draw(glm::vec2 position)
{
	Shader* shader = Shader::getUnlitSprite();
	// Assign the texture to the shader
	shader->setTexture("tex", texture);
	sre->draw(mesh, glm::translate(glm::mat4(1), glm::vec3(position.x, position.y, 0)), shader);
}
