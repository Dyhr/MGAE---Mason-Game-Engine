#pragma once

#include "Collider2D.hpp"

namespace Mason {
	class CircleCollider2D : public Collider2D
	{
	public:
		void setCenter(float x, float y);
		void setSize(float rad);
		void setScale(float scale) override;
	protected:
		CircleCollider2D(GameObject* gameObject);
		friend class GameObject;
	private:
		b2CircleShape circleShape;
		//circleShape.m_p.Set(0, 0); //position, relative to body position
		//circleShape.m_radius = 1; //radius
		b2Vec2 center;
		float radiuslength;
	};
}
