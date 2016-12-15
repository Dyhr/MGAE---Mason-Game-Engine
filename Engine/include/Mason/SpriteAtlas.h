#pragma once

#include <map>
#include <SRE/Texture.hpp>
#include <memory>

namespace Mason {
	/** @class SpriteAtlas
	* @brief Manage different sprites packed in a single texture (spritesheet).
	*
	*
	* @file MarioPacked.json
	* This is the JSON file for the SpriteAtlas used for the physics demo
	* @verbinclude MarioPacked.json
	*/

	class Sprite;

	class SpriteAtlas {
	public:
		/** @brief Constructor to work with a specific SpriteAtlas
		* @param atlasJsonDataDirectory path to the directory where the JSON file with the info of the sprites is
		* @param atlasJsonDataFile name of the JSON file with the info of the sprites
		*/
		SpriteAtlas(std::string atlasJsonDataDirectory, std::string atlasJsonDataFile);

		/** @brief get a specific sprite from the SpriteAtlas
	* @param name unique name that identifies the Sprite
	* @return a pointer to the Sprite
	*/
		std::shared_ptr<Sprite> getSprite(std::string name);
	private:
		std::map<std::string, std::shared_ptr<Sprite>> sprites;
		std::shared_ptr<SRE::Texture> texture;

		friend class Engine;
	};
}
