#pragma once

#include <map>
#include <SRE/Texture.hpp>
#include <memory>

namespace Mason {

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
