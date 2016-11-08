#include <glm/glm.hpp>
#include <SRE/Mesh.hpp>
#include <SRE/Texture.hpp>
#include <SRE/SimpleRenderEngine.hpp>


class Sprite {
public:
	// x,y,width and height uses pixel values texture coordinates (between 0.0 and 1.0)
	// relative position of anchor where 0.0 means to the left of the sprite and 1.0 means to the right of the sprite
	// relative position of anchor where 0.0 means to the bottom of the sprite and 1.0 means to the top of the sprite
	Sprite(int x, int y, int width, int height, float anchorX, float anchorY, SRE::Texture * texture, SRE::SimpleRenderEngine* sre);
	virtual ~Sprite();
	void draw(glm::vec2 position);
private:
	SRE::Mesh* mesh;
	SRE::Texture* texture;
	SRE::SimpleRenderEngine* sre;
};

