#include "Mason/SpriteAtlas.h"

#include "Mason/Sprite.h"
#include "picojson.h"
#include <fstream>

using namespace Mason;

SpriteAtlas::SpriteAtlas(std::string atlasJsonDataDirectory, std::string atlasJsonDataFile) {
	using namespace picojson;

	// Load the json file
	value root;
	std::fstream file(atlasJsonDataFile);
	file >> root;

	std::string	err = get_last_error();
	if (err != "") {
		std::cerr << err << std::endl;
		return;
	}

	// Load the texture
	std::string dir = atlasJsonDataDirectory + root.get("meta").get("image").get<std::string>();
	this->texture = std::shared_ptr<SRE::Texture>(SRE::Texture::createFromFile(dir.c_str(), false));

	array frames = root.get("frames").get<array>();
	for (auto frame : frames) {
		value coords = frame.get("frame");
		value pivot = frame.get("pivot");
		value pixelsperunit = frame.get("pixelsperunit");

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

std::shared_ptr<Sprite> SpriteAtlas::getSprite(std::string name) {
	return this->sprites[name];
}