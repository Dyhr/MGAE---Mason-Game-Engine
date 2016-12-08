
#include "Mason/Script.hpp"
#include <iostream>
#include "Mason/Scene.hpp"

using namespace Mason;

class DangerousCollisions :public Script
{
protected:
	DangerousCollisions(GameObject* gameObject) : Script(gameObject)
	{
	}

	friend GameObject;

public:
	void OnCollisionEnter(GameObject* other) override
	{
		Scene sc;
		//bool removeMario = sc.removeGameObject((std::shared_ptr<GameObject>)other);
		counter++;
		std::cout << counter;
	}
	/*void OnCollisionExit(GameObject* other) override
	{
		
	}*/

	int counter = 0;

};