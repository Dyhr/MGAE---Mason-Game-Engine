#include <SDL.h>
#include <string>
#include <vector>
#include "Component.hpp"
#include "GameObject.hpp"

class Audio : public Component {
public: 
	void play();
	void cleanUp();
	void init(std::string file);
	bool isPlaying();
protected:
	Audio(GameObject *gameObject);
	friend class GameObject;
private:
	std::string path;
};