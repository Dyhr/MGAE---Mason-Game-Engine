#include <SDL.h>
#include <string>
#include <vector>
#include "Component.hpp"
#include "GameObject.hpp"

class Audio : public Component {
public: 
	void play();
	bool stillGoing();
	void init(std::string file);
protected:
	Audio(GameObject *gameObject);
	friend class GameObject;
private:
	const char * path;
};