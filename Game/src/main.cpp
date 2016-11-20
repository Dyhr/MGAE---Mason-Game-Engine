
#include <Mason/Engine.hpp>

int main(int argc, char** argv) {

	Engine e;

	e.loadScene("data/car_house_tree.json");

	e.start();

	return 0;
}
