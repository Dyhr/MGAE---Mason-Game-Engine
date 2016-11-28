#pragma once

#include "Mason/Transform.h"
#include <memory>
#include <SRE/Camera.hpp>
#include <glm/glm.hpp>

namespace Mason {
	class Camera : public Transform {
	public:

		void setScale(glm::vec3 scale) override;
		void setPosition(glm::vec3 position) override;
		glm::vec3 getScale() override;
		glm::vec3 getPosition() override;

		glm::vec2 getViewportMin() const;
		void setViewportMin(glm::vec2 viewport_min);
		glm::vec2 getViewportMax() const;
		void setViewportMax(glm::vec2 viewport_max);

		~Camera();

	protected:
		Camera(GameObject *gameObject);

		void transformize() override;

		glm::vec2 viewportMin = glm::vec2(0, 0);
		glm::vec2 viewportMax = glm::vec2(1, 1);

		SRE::Camera* cam;

		friend class GameObject;
		friend class Engine;

	private:
		void setRotation(glm::vec3 rotation) override {}
	};
}
