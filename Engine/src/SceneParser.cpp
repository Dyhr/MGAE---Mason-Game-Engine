#include "Mason/SceneParser.hpp"
#include <fstream>
#include "picojson.h"

using namespace Mason;

glm::vec4 to_vec4(picojson::value v) {
	glm::vec4 res;
	auto array = v.get<picojson::array>();
	for (int i = 0; i < 4; i++) {
		res[i] = (float)array[i].get<double>();
	}
	return res;
}

glm::vec3 to_vec3(picojson::value v) {
	glm::vec3 res;
	auto array = v.get<picojson::array>();
	for (int i = 0; i < 3; i++) {
		res[i] = (float)array[i].get<double>();
	}
	return res;
}

glm::vec2 to_vec2(picojson::value v) {
	glm::vec2 res;
	auto array = v.get<picojson::array>();
	for (int i = 0; i < 2; i++) {
		res[i] = (float)array[i].get<double>();
	}
	return res;
}



std::vector<GameObjectDescriptor> SceneParser::parseFile(std::string filename) {
	std::fstream file(filename);
	picojson::value v;
	file >> v;

	std::vector<GameObjectDescriptor> res;
	for (auto o : v.get("gameobjects").get<picojson::array>()) {
		GameObjectDescriptor d;
		if(o.contains("name")) d.name = o.get("name").get<std::string>();
		if (o.contains("uniqueId")) d.uniqueId = int(o.get("uniqueId").get<double>());

		if (o.contains("transform")) {
			auto t = o.get("transform");
			if (t.contains("position")) d.transform.position = to_vec3(t.get("position"));
			if (t.contains("rotationEuler")) d.transform.rotationEuler = to_vec3(t.get("rotationEuler"));
			if (t.contains("scale")) d.transform.scale = to_vec3(t.get("scale"));
			if (t.contains("parentId")) d.transform.parentId = int(t.get("parentId").get<double>());
		}

		if (o.contains("mesh")) {
			d.mesh.found = true;
			auto m = o.get("mesh");
			if (m.contains("name")) d.mesh.name = m.get("name").get<std::string>();
			if (m.contains("color")) d.mesh.color = to_vec4(m.get("color"));
		}

		if (o.contains("sprite")) {
			d.sprite.found = true;
			auto m = o.get("sprite");
			if (m.contains("name")) d.sprite.name = m.get("name").get<std::string>();
			if (m.contains("color")) d.sprite.color = to_vec4(m.get("color"));
		}

		if (o.contains("camera")) {
			d.camera.found = true;
			auto m = o.get("camera");
			if (m.contains("viewportMin")) d.camera.viewportMin = to_vec2(m.get("viewportMin"));
			if (m.contains("viewportMax")) d.camera.viewportMax = to_vec2(m.get("viewportMax"));
		}

		//TODO audio components
		if (o.contains("audio")) {
			d.audio.found = true;
			auto m = o.get("audio");
			if (m.contains("path")) d.audio.path = m.get("path").get<std::string>();
			if (m.contains("type")) d.audio.soundEffect = m.get("type").get<bool>();
		}

		res.push_back(d);
	}
	return res;
}
