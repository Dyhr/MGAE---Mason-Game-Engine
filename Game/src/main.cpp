
#include <Mason/Engine.hpp>
#include "Mason/ParticleEmitter.hpp"

using namespace glm;
using namespace Mason;

int main(int argc, char** argv) {
	Engine e;

	e.loadScene("data/car_house_tree.json");


	auto directionalLight = SRE::Light(SRE::LightType::Directional, vec3(0, 0, 0), vec3(1, 1, 1), vec3(1, 1, 1), 0);
	auto pointLight1 = SRE::Light(SRE::LightType::Point, vec3(-1, 1, 1), vec3(0, 0, 0), vec3(5, 0, 0), 5);
	auto pointLight2 = SRE::Light(SRE::LightType::Point, vec3(0, 1, -2), vec3(0, 0, 0), vec3(3, 3, 3), 5);
	e.sre->setLight(0, directionalLight);
	e.sre->setLight(1, pointLight1);
	e.sre->setLight(2, pointLight2);

	auto g = vec3(0, -10, 0);

	auto emitter = e.scene->getGameObject(0)->addComponent<ParticleEmitter>();
	ParticleEmitterConfig config0(0.5f, 6, vec3(3, 10, 0), g);
	config0.setFixedSize(0.2f);
	config0.setFixedColor(vec4(0, 1, 1, 1));
	emitter->init(config0);
	emitter->start();

	emitter = e.scene->getGameObject(16)->addComponent<ParticleEmitter>();
	ParticleEmitterConfig config16(8, 4, vec3(-5, 1, 0), g);
	config16.setFixedSize(0.5f);
	config16.setLERPColor(vec4(0, 1, 0, 1), vec4(0, 1, 0, 0));
	emitter->init(config16);
	emitter->start();

	emitter = e.scene->getGameObject(17)->addComponent<ParticleEmitter>();
	ParticleEmitterConfig config17(2, 1, vec3(0, 20, 0), g);
	config17.setLERPSize(1.0f, 0.0f);
	config17.setFixedColor(vec4(0, 1, 1, 1));
	emitter->init(config17);
	emitter->start();


	e.start();

	return 0;
}
