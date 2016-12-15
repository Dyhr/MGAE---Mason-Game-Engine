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



SceneDescriptor SceneParser::parseFile(std::string filename) {
	std::fstream file(filename);
	picojson::value v;
	file >> v;

	SceneDescriptor scene;

	if (v.contains("scenename")) scene.name = v.get("scenename").get<std::string>();
	if (v.contains("imagepath")) scene.imagepath = v.get("imagepath").get<std::string>();
	if (v.contains("soundpath")) scene.soundpath = v.get("soundpath").get<std::string>();
	if (v.contains("sprites"))
		for (auto atlas : v.get("sprites").get<picojson::array>())
			scene.sprites.push_back(atlas.get<std::string>());

	for (auto o : v.get("gameobjects").get<picojson::array>()) {
		GameObjectDescriptor d;
		if (o.contains("name")) d.name = o.get("name").get<std::string>();
		if (o.contains("uniqueId")) d.uniqueId = int(o.get("uniqueId").get<double>());

		if (o.contains("transform")) {
			auto t = o.get("transform");
			if (t.contains("position")) d.transform.position = to_vec3(t.get("position"));
			if (t.contains("rotationEuler")) d.transform.rotationEuler = to_vec3(t.get("rotationEuler"));
			if (t.contains("scale")) d.transform.scale = to_vec3(t.get("scale"));
			if (t.contains("parentId")) d.transform.parentId = int(t.get("parentId").get<double>());
		}
		if (o.contains("boxcollider")) {
			auto bc = o.get("boxcollider");
			d.boxCollider.found = true;
			if (bc.contains("center")) d.boxCollider.center = to_vec2(bc.get("center"));
			if (bc.contains("width")) d.boxCollider.width = float(bc.get("width").get<double>());
			if (bc.contains("height")) d.boxCollider.height = float(bc.get("height").get<double>());
		}
		if (o.contains("circlecollider")) {
			auto cc = o.get("circlecollider");
			d.circleCollider.found = true;
			if (cc.contains("center")) d.circleCollider.center = to_vec2(cc.get("center"));
			if (cc.contains("radius")) d.circleCollider.radius = float(cc.get("radius").get<double>());
		}
		if (o.contains("physicsbody")) {
			auto pb = o.get("physicsbody");
			d.physicsBody2D.found = true;
			if (pb.contains("type")) {
				auto typeString = pb.get("type").get<std::string>();
				if (typeString == "static") d.physicsBody2D.type = b2BodyType::b2_staticBody;
					else if (typeString == "dynamic") d.physicsBody2D.type = b2BodyType::b2_dynamicBody;
					else if (typeString == "kinematic") d.physicsBody2D.type = b2BodyType::b2_kinematicBody;
			}
		}

		if (o.contains("sprite")) {
			d.sprite.found = true;
			auto s = o.get("sprite");
			if (s.contains("name")) d.sprite.name = s.get("name").get<std::string>();
			if (s.contains("color")) d.sprite.color = to_vec4(s.get("color"));
		}

		if (o.contains("camera")) {
			d.camera.found = true;
			auto c = o.get("camera");
			if (c.contains("viewportMin")) d.camera.viewportMin = to_vec2(c.get("viewportMin"));
			if (c.contains("viewportMax")) d.camera.viewportMax = to_vec2(c.get("viewportMax"));
		}

		if (o.contains("audio")) {
			d.audio.found = true;
			auto a = o.get("audio");
			if (a.contains("path")) d.audio.path = a.get("path").get<std::string>();
			if (a.contains("type")) {
				auto typeString = a.get("type").get<std::string>();
				if (typeString == "music") d.audio.type = SoundType::MUSIC;
					else d.audio.type = SoundType::EFFECT;
			}
		}

		if (o.contains("scripts") && o.get("scripts").is<picojson::array>()) {
			auto scripts = o.get("scripts").get<picojson::array>();
			for (auto s : scripts)
			{
				ScriptDescriptor script;
				if (s.contains("name")) script.name = s.get("name").get<std::string>();
				if (s.contains("properties")) {
					for (auto prop : s.get("properties").get<picojson::array>())
					{
						if(s.contains(prop.get<std::string>()))
						{
							auto p = s.get(prop.get<std::string>());
							if (p.is<std::string>()) script.strings[prop.get<std::string>()] = p.get<std::string>();
							if (p.is<double>()) script.numbers[prop.get<std::string>()] = p.get<double>();
						}
					}
				}
				d.scripts.push_back(script);
			}
		}

		if (o.contains("particles")) {
			d.particles.found = true;
			auto p = o.get("particles");
			if (p.contains("texturePath")) d.particles.texturePath = p.get("texturePath").get<std::string>();
			if (p.contains("rate")) d.particles.rate = float(p.get("rate").get<double>());
			if (p.contains("lifespan")) d.particles.lifespan = float(p.get("lifespan").get<double>());
			if (p.contains("velocity")) d.particles.velocity = to_vec3(p.get("velocity"));
			if (p.contains("minVelocity")) d.particles.minVelocity = to_vec3(p.get("minVelocity"));
			if (p.contains("maxVelocity")) d.particles.maxVelocity = to_vec3(p.get("maxVelocity"));
			if (p.contains("gravity")) d.particles.gravity = to_vec3(p.get("gravity"));
			if (p.contains("size")) d.particles.minSize = float(p.get("size").get<double>());
			if (p.contains("minSize")) d.particles.minSize = float(p.get("minSize").get<double>());
			if (p.contains("maxSize")) d.particles.maxSize = float(p.get("maxSize").get<double>());
			if (p.contains("rotation")) d.particles.minRotation = float(p.get("rotation").get<double>());
			if (p.contains("minRotation")) d.particles.minRotation = float(p.get("minRotation").get<double>());
			if (p.contains("maxRotation")) d.particles.minRotation = float(p.get("maxRotation").get<double>());
			if (p.contains("color")) d.particles.minColor = to_vec4(p.get("color"));
			if (p.contains("minColor")) d.particles.minColor = to_vec4(p.get("minColor"));
			if (p.contains("maxColor")) d.particles.maxColor = to_vec4(p.get("maxColor"));
			if (p.contains("initialSize")) d.particles.initialSize = float(p.get("initialSize").get<double>());
			if (p.contains("finalSize")) d.particles.finalSize = float(p.get("finalSize").get<double>());
			if (p.contains("initialRotation")) d.particles.initialRotation = float(p.get("initialRotation").get<double>());
			if (p.contains("finalRotation")) d.particles.finalRotation = float(p.get("finalRotation").get<double>());
			if (p.contains("initialSize")) d.particles.initialSize = float(p.get("initialSize").get<double>());
			if (p.contains("initialColor")) d.particles.initialColor = to_vec4(p.get("initialColor"));
			if (p.contains("finalColor")) d.particles.finalColor = to_vec4(p.get("finalColor"));
			if (p.contains("velocityState")) d.particles.velocityState = p.get("velocityState").get<std::string>();
			if (p.contains("rotationState")) d.particles.rotationState = p.get("rotationState").get<std::string>();
			if (p.contains("sizeState")) d.particles.sizeState = p.get("sizeState").get<std::string>();
			if (p.contains("colorState")) d.particles.colorState = p.get("colorState").get<std::string>();
			if (p.contains("splinePointsSize")) {
				std::vector<glm::vec2> points;
				auto arr = p.get("splinePointsSize").get<picojson::array>();
				for (int i = 0; i < arr.size(); i++) {
					points.push_back(to_vec2(arr[i]));
				}
				d.particles.splinePointsSize = points;
			}
			if (p.contains("splinePointsColor")) {
				std::vector<glm::vec2> points;
				auto arr = p.get("splinePointsColor").get<picojson::array>();
				for (int i = 0; i < arr.size(); i++) {
					points.push_back(to_vec2(arr[i]));
				}
				d.particles.splinePointsColor = points;

			}
			if (p.contains("splinePointsRotation")) {
				std::vector<glm::vec2> points;
				auto arr = p.get("splinePointsRotation").get<picojson::array>();
				for (int i = 0; i < arr.size(); i++) {
					points.push_back(to_vec2(arr[i]));
				}
				d.particles.splinePointsRotation = points;
			}
		}

		scene.gameobjects.push_back(d);
	}
	return scene;
}

GameObjectDescriptor Mason::SceneParser::parseObjectFromJSON(std::string filename)
{
	std::fstream file(filename);
	picojson::value o;
	file >> o;

	GameObjectDescriptor d;

	if (o.contains("name")) d.name = o.get("name").get<std::string>();
	if (o.contains("uniqueId")) d.uniqueId = int(o.get("uniqueId").get<double>());

	if (o.contains("transform")) {
		auto t = o.get("transform");
		if (t.contains("position")) d.transform.position = to_vec3(t.get("position"));
		if (t.contains("rotationEuler")) d.transform.rotationEuler = to_vec3(t.get("rotationEuler"));
		if (t.contains("scale")) d.transform.scale = to_vec3(t.get("scale"));
		if (t.contains("parentId")) d.transform.parentId = int(t.get("parentId").get<double>());
	}
	if (o.contains("boxcollider")) {
		auto bc = o.get("boxcollider");
		d.boxCollider.found = true;
		if (bc.contains("center")) d.boxCollider.center = to_vec2(bc.get("center"));
		if (bc.contains("width")) d.boxCollider.width = float(bc.get("width").get<double>());
		if (bc.contains("height")) d.boxCollider.height = float(bc.get("height").get<double>());
	}
	if (o.contains("circlecollider")) {
		auto cc = o.get("circlecollider");
		d.circleCollider.found = true;
		if (cc.contains("center")) d.circleCollider.center = to_vec2(cc.get("center"));
		if (cc.contains("radius")) d.circleCollider.radius = float(cc.get("radius").get<double>());
	}
	if (o.contains("physicsbody")) {
		auto pb = o.get("physicsbody");
		d.physicsBody2D.found = true;
		if (pb.contains("type")) {
			auto typeString = pb.get("type").get<std::string>();
			if (typeString == "static") d.physicsBody2D.type = b2BodyType::b2_staticBody;
			else if (typeString == "dynamic") d.physicsBody2D.type = b2BodyType::b2_dynamicBody;
			else if (typeString == "kinematic") d.physicsBody2D.type = b2BodyType::b2_kinematicBody;
		}
	}

	if (o.contains("sprite")) {
		d.sprite.found = true;
		auto s = o.get("sprite");
		if (s.contains("name")) d.sprite.name = s.get("name").get<std::string>();
		if (s.contains("color")) d.sprite.color = to_vec4(s.get("color"));
	}

	if (o.contains("camera")) {
		d.camera.found = true;
		auto c = o.get("camera");
		if (c.contains("viewportMin")) d.camera.viewportMin = to_vec2(c.get("viewportMin"));
		if (c.contains("viewportMax")) d.camera.viewportMax = to_vec2(c.get("viewportMax"));
	}

	if (o.contains("audio")) {
		d.audio.found = true;
		auto a = o.get("audio");
		if (a.contains("path")) d.audio.path = a.get("path").get<std::string>();
		if (a.contains("type")) {
			auto typeString = a.get("type").get<std::string>();
			if (typeString == "music") d.audio.type = SoundType::MUSIC;
			else d.audio.type = SoundType::EFFECT;
		}
	}

	if (o.contains("scripts") && o.get("scripts").is<picojson::array>()) {
		auto scripts = o.get("scripts").get<picojson::array>();
		for (auto s : scripts)
		{
			ScriptDescriptor script;
			if (s.contains("name")) script.name = s.get("name").get<std::string>();
			if (s.contains("properties")) {
				for (auto prop : s.get("properties").get<picojson::array>())
				{
					if (s.contains(prop.get<std::string>()))
					{
						auto p = s.get(prop.get<std::string>());
						if (p.is<std::string>()) script.strings[prop.get<std::string>()] = p.get<std::string>();
						if (p.is<double>()) script.numbers[prop.get<std::string>()] = p.get<double>();
					}
				}
			}
			d.scripts.push_back(script);
		}
	}

	if (o.contains("particles")) {
		d.particles.found = true;
		auto p = o.get("particles");
		if (p.contains("texturePath")) d.particles.texturePath = p.get("texturePath").get<std::string>();
		if (p.contains("rate")) d.particles.rate = float(p.get("rate").get<double>());
		if (p.contains("lifespan")) d.particles.lifespan = float(p.get("lifespan").get<double>());
		if (p.contains("velocity")) d.particles.velocity = to_vec3(p.get("velocity"));
		if (p.contains("minVelocity")) d.particles.minVelocity = to_vec3(p.get("minVelocity"));
		if (p.contains("maxVelocity")) d.particles.maxVelocity = to_vec3(p.get("maxVelocity"));
		if (p.contains("gravity")) d.particles.gravity = to_vec3(p.get("gravity"));
		if (p.contains("size")) d.particles.minSize = float(p.get("size").get<double>());
		if (p.contains("minSize")) d.particles.minSize = float(p.get("minSize").get<double>());
		if (p.contains("maxSize")) d.particles.maxSize = float(p.get("maxSize").get<double>());
		if (p.contains("rotation")) d.particles.minRotation = float(p.get("rotation").get<double>());
		if (p.contains("minRotation")) d.particles.minRotation = float(p.get("minRotation").get<double>());
		if (p.contains("maxRotation")) d.particles.minRotation = float(p.get("maxRotation").get<double>());
		if (p.contains("color")) d.particles.minColor = to_vec4(p.get("color"));
		if (p.contains("minColor")) d.particles.minColor = to_vec4(p.get("minColor"));
		if (p.contains("maxColor")) d.particles.maxColor = to_vec4(p.get("maxColor"));
		if (p.contains("initialSize")) d.particles.initialSize = float(p.get("initialSize").get<double>());
		if (p.contains("finalSize")) d.particles.finalSize = float(p.get("finalSize").get<double>());
		if (p.contains("initialRotation")) d.particles.initialRotation = float(p.get("initialRotation").get<double>());
		if (p.contains("finalRotation")) d.particles.finalRotation = float(p.get("finalRotation").get<double>());
		if (p.contains("initialSize")) d.particles.initialSize = float(p.get("initialSize").get<double>());
		if (p.contains("initialColor")) d.particles.initialColor = to_vec4(p.get("initialColor"));
		if (p.contains("finalColor")) d.particles.finalColor = to_vec4(p.get("finalColor"));
		if (p.contains("velocityState")) d.particles.velocityState = p.get("velocityState").get<std::string>();
		if (p.contains("rotationState")) d.particles.rotationState = p.get("rotationState").get<std::string>();
		if (p.contains("sizeState")) d.particles.sizeState = p.get("sizeState").get<std::string>();
		if (p.contains("colorState")) d.particles.colorState = p.get("colorState").get<std::string>();
		if (p.contains("splinePointsSize")) {
			std::vector<glm::vec2> points;
			auto arr = p.get("splinePointsSize").get<picojson::array>();
			for (int i = 0; i < arr.size(); i++) {
				points.push_back(to_vec2(arr[i]));
			}
			d.particles.splinePointsSize = points;
		}
		if (p.contains("splinePointsColor")) {
			std::vector<glm::vec2> points;
			auto arr = p.get("splinePointsColor").get<picojson::array>();
			for (int i = 0; i < arr.size(); i++) {
				points.push_back(to_vec2(arr[i]));
			}
			d.particles.splinePointsColor = points;

		}
		if (p.contains("splinePointsRotation")) {
			std::vector<glm::vec2> points;
			auto arr = p.get("splinePointsRotation").get<picojson::array>();
			for (int i = 0; i < arr.size(); i++) {
				points.push_back(to_vec2(arr[i]));
			}
			d.particles.splinePointsRotation = points;
		}
	}
	return d;
}
