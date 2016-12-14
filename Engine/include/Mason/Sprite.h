#pragma once

#include "glm/glm.hpp"
#include <SRE/Mesh.hpp>
#include <SRE/Texture.hpp>
#include <memory>
#include <Mason/Engine.hpp>


namespace Mason {
	
	class Sprite {

	public:
		int pixelsperunit = 1;
		Sprite(int x, int y, int width, int height, float anchorX, float anchorY, std::shared_ptr<SRE::Texture> texture);
		void draw(glm::vec3 position) const;
		std::shared_ptr<SRE::Texture> getTexture();
		void setTexture(std::shared_ptr<SRE::Texture> t);
	private:
		
		std::shared_ptr<SRE::Mesh> mesh;
		std::shared_ptr<SRE::Texture> texture;
	};
}

