#pragma once

#include <string>
#include <map>
#include <memory>
#include <SRE/SimpleRenderEngine.hpp>
#include "SRE/Texture.hpp"

class Sprite;

class SpriteAtlas {
public:
	SpriteAtlas(std::string atlasJsonDataDirectory, std::string atlasJsonDataFile, SRE::SimpleRenderEngine * sre);
	~SpriteAtlas();

	Sprite* getSprite(std::string name);
private:
	std::map<std::string, Sprite*> sprites;
	// Note: the json file has the origin in the upper left corner
	void init(std::string atlasJsonDataDirectory, std::string atlasJsonDataFile, SRE::SimpleRenderEngine * sre);
	SRE::Texture* texture;
};


