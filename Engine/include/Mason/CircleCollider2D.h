#pragma once

#include "Collider2D.hpp"

namespace Mason {
	class CircleCollider2D : public Collider2D
	{
	public:
		void setCenter(float x, float y);
		void setSize(float rad);
		void setScale(float scale) override;
		void setDensity(float density) override;
		void setFriction(float friction) override;
	protected:
		CircleCollider2D(GameObject* gameObject);
		friend class GameObject;
	private:
		b2CircleShape circleShape;
		b2Vec2 center;
		float radius;
	};
}
