#pragma once

#include <glm/glm.hpp>
#include <SRE/Mesh.hpp>
#include <SRE/Texture.hpp>
#include <memory>


namespace Mason {
	/** @class Sprite
	* @brief rectangular images rendered at a specific position.
	* A mesh contains the width and height of the Sprite. The image of the Sprite is loaded as a SRE Texture. This Texture is assigned to the SRE shader @see SRE.
	*/
	class Sprite {

	public:

		int pixelsperunit = 1; ///< For the moment used as a global variable. Same value for every Sprite.
		
							   /** @brief Sprite constructor
	* Sets up the mesh to be rendered (with vertices defined in windows coordinates, normals (not used in 2D graphics) and UVs with the normalize texture coordinates)
	* @param x x coordenate of the Sprite
	* @param y y coordenate of the Sprite
	* @param witdh witdh of the Sprite. Used to make it fit in a mesh with its dimesions.
	* @param height height of the Sprite. Used to make it fit in a mesh with its dimesions.
	* @param anchorX x coordenate of the pivot point situation on the Sprite
	* @param anchorY y coordenate of the pivot point situation on the Sprite
	* @param texture image uploaded to the GPU for 2D graphics.  @see SRE (also supports 3D graphics)
	*/
		Sprite(int x, int y, int width, int height, float anchorX, float anchorY, std::shared_ptr<SRE::Texture> texture);
		
		/** @brief why is it const ?
		*sets the texture in a SRE shader and calls the SRE draw(), providing the mesh, the position given by the SpriteRenderer and the shader. @see SRE
		*/
		void draw(glm::vec3 position) const;
		
		/** @return SRE texture that stores colors, shadows, geometry data and others @see SRE
		*/
		std::shared_ptr<SRE::Texture> getTexture();

		/** @brief sets the texture of the Sprite @see SRE
		*/
		void setTexture(std::shared_ptr<SRE::Texture> t);

	private:
		
		std::shared_ptr<SRE::Mesh> mesh;
		std::shared_ptr<SRE::Texture> texture;
	};
}

