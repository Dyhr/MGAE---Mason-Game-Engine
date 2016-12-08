#include "Mason\CollisionListener.h"
#include <SRE/SimpleRenderEngine.hpp>
#include <iostream>
#include "Mason/Config.hpp"
#include "Mason/GameObject.hpp"
#include "Mason/Script.hpp"
#include <iostream>

using namespace Mason;
/*http://www.learn-cocos2d.com/api-ref/1.0/Box2D/html/classb2_contact_listener.html*/
void CollisionListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	const b2Manifold* manifold = contact->GetManifold();

	if (manifold->pointCount == 0)
	{
		return;
	}

	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();
	//fixtureA->GetBody; // we can get the body with this.
}

void Mason::CollisionListener::BeginContact(b2Contact * contact)
{
	auto gO = ((GameObject*)contact->GetFixtureA()->GetUserData());
	auto g1 = ((GameObject*)contact->GetFixtureB()->GetUserData());
	auto s1 = gO->getComponents<Script>();
	auto s2 = g1->getComponents<Script>();

	for (int i = 0; i < s1.size(); i++)
		s1[i]->OnCollisionEnter(g1);

	for (int i = 0; i < s2.size(); i++)
		s2[i]->OnCollisionEnter(gO);
}

void Mason::CollisionListener::EndContact(b2Contact * contact)
{
	auto gO = ((GameObject*)contact->GetFixtureA()->GetUserData());
	auto g1 = ((GameObject*)contact->GetFixtureB()->GetUserData());
	auto s1 = gO->getComponents<Script>();
	auto s2 = g1->getComponents<Script>();

	for (int i = 0; i < s1.size(); i++)
		s1[i]->OnCollisionExit(g1);

	for (int i = 0; i < s2.size(); i++)
		s2[i]->OnCollisionExit(gO);


}
void Mason::CollisionListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {

}