#ifndef SPRITEATLAS_H
#define SPRITEATLAS_H
#include <string>
#include <map>
#include <memory>
#include <SRE/SimpleRenderEngine.hpp>
#include <SRE/Texture.hpp>

class Sprite;

class SpriteAtlas {
public:
	SpriteAtlas(std::string atlasJsonDataDirectory, std::string atlasJsonDataFile, SRE::SimpleRenderEngine * sre);
	~SpriteAtlas();

	SpriteRenderer* getSprite(std::string name);//make sense?
private:
	//A map will sort members alphabetically. not repeated keys
	//don't need to be initialized in constructor
	std::map<std::string, SpriteRenderer*> sprites;
	// Note: the json file has the origin in the upper left corner
	void init(std::string atlasJsonDataDirectory, std::string atlasJsonDataFile, SRE::SimpleRenderEngine * sre);
	SRE::Texture* texture;
};



#endif // !SPRITEATLAS_H

