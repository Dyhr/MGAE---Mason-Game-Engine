#pragma once

#include <map>
#include <SRE/Texture.hpp>
#include <memory>

namespace Mason {
	/** @class SpriteAtlas
	* @brief Manage different sprites packed in a single texture (spritesheet).
	*
	* The information about the location and pivot point of each sprite is stored in a JSON file
	*
	* @fn SpriteAtlas(std::string atlasJsonDataDirectory, std::string atlasJsonDataFile)
	* @brief Constructor to work with a specific SpriteAtlas
	* @param atlasJsonDataDirectory path to the directory where the JSON file with the info of the sprites is
	* @param atlasJsonDataFile name of the JSON file with the info of the sprites
	*
	* @fn getSprite(std::string name)
	* @brief get a specific sprite from the SpriteAtlas
	* @param name unique name that identifies the @see Sprite
	* @return a pointer to the @see Sprite
	*
	*  @file MarioPacked.json
	*  This is the JSON file for the SpriteAtlas used for the physics demo
	*  @verbinclude MarioPacked.json
	*/

	class Sprite;

	class SpriteAtlas {
	public:
		SpriteAtlas(std::string atlasJsonDataDirectory, std::string atlasJsonDataFile);

		std::shared_ptr<Sprite> getSprite(std::string name);
	private:
		std::map<std::string, std::shared_ptr<Sprite>> sprites;
		// Note: the json file has the origin in the upper left corner
		void init(std::string atlasJsonDataDirectory, std::string atlasJsonDataFile);
		std::shared_ptr<SRE::Texture> texture;
	};
}
