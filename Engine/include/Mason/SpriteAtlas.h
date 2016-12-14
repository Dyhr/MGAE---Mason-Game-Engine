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
		std::shared_ptr<SRE::Texture> texture;

		friend class Engine;
	};
}
