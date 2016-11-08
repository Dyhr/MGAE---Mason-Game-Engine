
#include "SpriteAtlas.h"
#include "SpriteRenderer.h"
#include "picojson.h"
#include <sstream>
#include <fstream>
#include <iostream>

SpriteAtlas::SpriteAtlas(std::string atlasJsonDataDirectory, std::string atlasJsonDataFile, SRE::SimpleRenderEngine * sre) {

	std::map<std::string, Sprite*> mapSpr;

	picojson::value v;
	std::string meta;

	std::string err = picojson::get_last_error();
	double textureH;

	if (err != "") {
		std::cerr << err << std::endl;
		return;
	}
	else {


		std::ifstream f(atlasJsonDataDirectory + atlasJsonDataFile);
		//std::stringstream ss;

		//parse JSON

		f >> v;
		//ss << f.rdbuf();
		//sprites= v.get<Sprite*>()["brick"].get<Sprite*>();
		//std::cout << "TestInt: " << v["brick"].get<Sprite*>() << endl;



		// obtain a const reference to the map, and print the contents
		double frame_X, frame_Y, frame_W, frame_H, pivot_X, pivot_Y;
		std::string filen;


		//get "meta": {		"image" : "MarioPacked.png", .-.. from JSON
		meta = v.get("meta").get("image").get<std::string>();
		meta = atlasJsonDataDirectory + meta;
		const char * c = meta.c_str();


		SRE::Texture* texture = SRE::Texture::createFromFile(c, false);
		texture->setFilterSampling(false);

		const picojson::value::object& obj = v.get<picojson::object>();

		for (picojson::value::object::const_iterator i = obj.begin(); i != obj.end(); ++i) {
			//i->first; //frame		i->second.to_str(); //meta


			//all the numbers in picojson are doubles
			//here we are getting data from the file

			picojson::array arrFrames = v.get(i->first).get<picojson::array>();


			for (auto it = arrFrames.begin(); it != arrFrames.end(); ++it)
			{
				filen = it->get("filename").get<std::string>();
				frame_X = it->get("frame").get("x").get<double>();
				frame_Y = it->get("frame").get("y").get<double>();
				frame_W = it->get("frame").get("w").get<double>();
				frame_H = it->get("frame").get("h").get<double>();
				pivot_X = it->get("pivot").get("x").get<double>();
				pivot_Y = it->get("pivot").get("y").get<double>();

				//change coordinates to our system: coord=textH-y-h, only in Y axis
				textureH = texture->getHeight();

				frame_Y = (int)(textureH)-frame_Y - frame_H;

				//other option:
				//mapSpr.insert(std::pair<std::string, Sprite*>(filen, new Sprite((int)frame_X, (int)frame_Y, (int)frame_W, (int)frame_H, (int)pivot_X, (int)pivot_Y, texture, sre)));

				mapSpr[filen] = new Sprite((int)frame_X, (int)frame_Y, (int)frame_W, (int)frame_H, (float)pivot_X, (float)pivot_Y, texture, sre);
			}
			break; //not very elegant -.-
		}

		//std::string filename = arrFrames[0].get("filename").get<std::string>();
		//std::cout << filename;
		//double frame_X = arrFrames[0].get("frame").get("x").get<double>();

		//Sprite sample1(170 * 2, 0, 170, 128, 0, 0, texture, sre);
		//sample1.draw(glm::vec2(170 * 2, 128));
		f.close();
	}
	this->sprites = mapSpr;
	this->texture = texture;
}


SpriteAtlas::~SpriteAtlas() {

}

Sprite* SpriteAtlas::getSprite(std::string name) {

	return sprites[name];
}

// Note: the json file has the origin in the upper left corner
void SpriteAtlas::init(std::string atlasJsonDataDirectory, std::string atlasJsonDataFile, SRE::SimpleRenderEngine * sre) {

}