#pragma once

#include "Mason/Transform.h"
#include "Mason/GameObject.hpp"
#include "Time.hpp"
#include <SDL.h>
#include <iostream>
#include <map>

namespace Mason {

	class Script : public Component
	{
	public:

		static std::map<std::string, Script*(*)(std::shared_ptr<GameObject>)> scripts;

		Script(std::shared_ptr<GameObject> gameObject) :Component(gameObject)
		{
			this->transform = gameObject->getComponent<Transform>();
		}

		std::shared_ptr<GameObject> gameobject;
		Transform* transform;

		std::map<std::string, std::string> strings;
		std::map<std::string, float> numbers;

		virtual void OnStart() {}
		virtual void OnUpdate() {}
		virtual void OnCollisionEnter(Mason::GameObject* other) {}
		//virtual void OnCollisionStay() {}
		virtual void OnCollisionExit(GameObject* other) {}
		virtual void OnInput(SDL_Event event) {} // TODO refactor to better input system
	private:
		bool started = false;
		friend Engine;
	};
}
