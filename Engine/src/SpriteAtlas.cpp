#include "Mason/SpriteAtlas.h"

#include "Mason/Sprite.h"
#include "picojson.h"
#include <fstream>

using namespace Mason;

SpriteAtlas::SpriteAtlas(std::string atlasJsonDataDirectory, std::string atlasJsonDataFile) {
	using namespace picojson;

	if (atlasJsonDataDirectory[atlasJsonDataDirectory.length()-1] != '/')
		atlasJsonDataDirectory += '/';

	// Load the json file
	value root;
	std::fstream file(atlasJsonDataDirectory + atlasJsonDataFile);
	file >> root;

	std::string	err = get_last_error();
	if (err != "") {
		std::cerr << err << std::endl;
		return;
	}

	// Load the texture
	if (!root.is<array>()) { // Sprite atlas from exercise texture packer
		std::string dir = atlasJsonDataDirectory + root.get("meta").get("image").get<std::string>();
		this->texture = std::shared_ptr<SRE::Texture>(SRE::Texture::createFromFile(dir.c_str(), false));

		array frames = root.get("frames").get<array>();
		for (auto frame : frames) {
			value coords = frame.get("frame");
			value pivot = frame.get("pivot");

			sprites[frame.get("filename").get<std::string>()] = std::make_shared<Sprite>(
				int(coords.get("x").get<double>()),
				this->texture->getHeight() - int(coords.get("y").get<double>()) - int(coords.get("h").get<double>()),
				int(coords.get("w").get<double>()),
				int(coords.get("h").get<double>()),
				float(pivot.get("x").get<double>()),
				float(pivot.get("y").get<double>()),
				texture);
		}
	}
	else // Sprite atlas from https://www.leshylabs.com/apps/sstool/
	{
		std::string dir = atlasJsonDataDirectory + atlasJsonDataFile.replace(atlasJsonDataFile.end()-5, atlasJsonDataFile.end(), ".png");
		this->texture = std::shared_ptr<SRE::Texture>(SRE::Texture::createFromFile(dir.c_str(), false));

		array frames = root.get<array>();
		for (auto frame : frames) {
			sprites[frame.get("name").get<std::string>()] = std::make_shared<Sprite>(
				int(frame.get("x").get<double>()),
				this->texture->getHeight() - int(frame.get("y").get<double>()) - int(frame.get("height").get<double>()),
				int(frame.get("width").get<double>()),
				int(frame.get("height").get<double>()),
				0.5f,
				0.5f,
				texture);
		}
	}
}

std::shared_ptr<Sprite> SpriteAtlas::getSprite(std::string name) {
	return this->sprites[name];
}