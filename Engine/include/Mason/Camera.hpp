#pragma once

#include "Mason/Transform.h"
#include <memory>
#include <glm/glm.hpp>

namespace SRE{
	class Camera;
}

namespace Mason {
	/** @class Camera
	* @brief We need to translate and scale the camera (not rotate because it is 2D) and setup the viewport plane.
	* Inherites from Transform and override its functions
	*/
	class Camera : public Transform {
	public:

		void setScale(float scale) override;
		void setPosition(glm::vec3 position) override;
		float getScale() override;
		glm::vec3 getPosition() override;

		glm::vec2 getViewportMin() const;
		void setViewportMin(glm::vec2 viewport_min);
		glm::vec2 getViewportMax() const;
		void setViewportMax(glm::vec2 viewport_max);

		/** @brief Destructor
		*/
		~Camera();

	protected:
		/** @brief Constructor
		*/
		Camera(std::shared_ptr<GameObject> gameObject);

		/** @brief scales to the size of the window
		* called on the methods setViewportMin() and setViewportMax(). Uses orthogonal projection for 2D.
		*/
		void transformize() override;

		glm::vec2 viewportMin = glm::vec2(0, 0); ///< sets the left-bottom corner as (0,0)
		glm::vec2 viewportMax = glm::vec2(1, 1); ///< sets the right-top corner as (1,1)

		SRE::Camera* cam; ///< uses the SRE Camera, that supports a special case of orthogonal projection where z=[-1:1] (depth). 

		friend class GameObject;
		friend class Engine;

	private:
		glm::vec3 offset() const;
		void setRotation(float rotation) override {}
	};
}
