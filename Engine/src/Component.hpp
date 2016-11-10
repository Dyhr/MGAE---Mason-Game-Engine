#ifndef COMPONENT_HPP
#define COMPONENT_HPP
class GameObject;
class Component {
public:
	virtual ~Component();
	GameObject* getGameObject();
protected:
	Component(GameObject *gameObject);
	GameObject *gameObject;

	friend class GameObject;
};
#endif // !COMPONENT_HPP




