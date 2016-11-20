#include "Mason/SceneParser.hpp"
#include <fstream>
#include "picojson.h"

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



std::vector<GameObjectDescriptor> SceneParser::parseFile(std::string filename) {
	std::fstream file(filename);
	picojson::value v;
	file >> v;

	std::vector<GameObjectDescriptor> res;
	for (auto o : v.get("gameobjects").get<picojson::array>()) {
		GameObjectDescriptor d;
		d.name = o.get("name").get<std::string>();
		d.uniqueId = int(o.get("uniqueId").get<double>());

		if (o.contains("transform")) {
			auto t = o.get("transform");
			if (t.contains("position")) d.transform.position = to_vec3(t.get("position"));
			if (t.contains("rotationEuler")) d.transform.rotationEuler = to_vec3(t.get("rotationEuler"));
			if (t.contains("scale")) d.transform.scale = to_vec3(t.get("scale"));
			if (t.contains("parentId")) d.transform.parentId = int(t.get("parentId").get<double>());
		}

		if (o.contains("mesh")) {
			auto m = o.get("mesh");
			if (m.contains("name")) d.mesh.name = m.get("name").get<std::string>();
			if (m.contains("color")) d.mesh.color = to_vec4(m.get("color"));
		}

		if (o.contains("sprite")) {
			auto m = o.get("mesh");
			if (m.contains("name")) d.sprite.name = m.get("name").get<std::string>();
			if (m.contains("color")) d.sprite.color = to_vec4(m.get("color"));
		}

		res.push_back(d);
	}
	return res;
}
