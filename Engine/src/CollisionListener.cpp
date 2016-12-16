#include "Mason/CollisionListener.h"

#include "Mason/Config.hpp"
#include "Mason/GameObject.hpp"
#include "Mason/Script.hpp"

using namespace Mason;

/*http://www.learn-cocos2d.com/api-ref/1.0/Box2D/html/classb2_contact_listener.html*/
/*void CollisionListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	const b2Manifold* manifold = contact->GetManifold();

	if (manifold->pointCount == 0)
	{
		return;
	}

	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();
	//fixtureA->GetBody; // we can get the body with this.
}*/

void CollisionListener::ProcessEvents()
{
	for (auto enter : collisionEnters)
		std::get<0>(enter)->OnCollisionEnter(std::get<1>(enter));
	for (auto exit : collisionExits)
		std::get<0>(exit)->OnCollisionEnter(std::get<1>(exit));
}

void CollisionListener::BeginContact(b2Contact * contact)
{
	auto g0 = static_cast<GameObject*>(contact->GetFixtureA()->GetUserData());
	auto g1 = static_cast<GameObject*>(contact->GetFixtureB()->GetUserData());
	auto s0 = g0->getComponents<Script>();
	auto s1 = g1->getComponents<Script>();

	for (auto s : s0)
		collisionEnters.push_back(make_tuple(s, g1));

	for (auto s : s1)
		collisionEnters.push_back(make_tuple(s, g0));
}

void CollisionListener::EndContact(b2Contact * contact)
{
	auto g0 = static_cast<GameObject*>(contact->GetFixtureA()->GetUserData());
	auto g1 = static_cast<GameObject*>(contact->GetFixtureB()->GetUserData());
	auto s0 = g0->getComponents<Script>();
	auto s1 = g1->getComponents<Script>();

	for (auto s : s0)
		collisionExits.push_back(make_tuple(s, g1));

	for (auto s : s1)
		collisionExits.push_back(make_tuple(s, g0));
}/*
void CollisionListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {

}*/