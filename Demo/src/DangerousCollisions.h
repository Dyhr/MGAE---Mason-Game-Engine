
#include "Mason/Script.hpp"
#include <iostream>
#include "Mason/SpriteRenderer.h"
#include "Mason/Scene.hpp"
#include "Mason/Engine.hpp"

using namespace Mason;

class DangerousCollisions :public Script
{
	bool done = false;
protected:
	DangerousCollisions(GameObject* gameObject) : Script(gameObject)
	{
	}

	friend GameObject;

public:

	static Script* Create(GameObject* gameObject)
	{
		return new DangerousCollisions(gameObject);
	}

	void OnCollisionEnter(GameObject* other) override
	{
		/*auto spr = other->getComponent<SpriteRenderer>()->sprite;
		auto tex = spr->getTexture();
		spr->setTexture();*/
	
			auto tr = other->getComponent<Transform>();
			auto scale = tr->getScale();
			tr->setScale(scale*2);
			other->getComponent<CircleCollider2D>()->setScale(4);
		
	}
	/*void OnCollisionExit(GameObject* other) override
	{
		
	}*/

	
};
