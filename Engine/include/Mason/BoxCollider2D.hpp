#pragma once

#include "Collider2D.hpp"

class b2PolygonShape;
struct b2Vec2;

namespace Mason {
	class BoxCollider2D : public Collider2D
	{
	public:
		void setCenter(float x, float y) const;
		void setSize(float width, float height) const;
		~BoxCollider2D();
	protected:
		BoxCollider2D(std::shared_ptr<GameObject> gameObject);
		friend class GameObject;
	private:
		b2PolygonShape* polyShape;
		b2Vec2* center;
		b2Vec2* size;

	};
}
