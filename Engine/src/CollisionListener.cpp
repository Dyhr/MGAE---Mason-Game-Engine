#include "Mason\CollisionListener.h"
#include <SRE/SimpleRenderEngine.hpp>
#include <iostream>
#include "Mason/Config.hpp"
#include "Mason\GameObject.hpp"
#include <iostream>

using namespace Mason;

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
	std::cout<<gO->getName();
	std::cout << g1->getName();
}

void Mason::CollisionListener::EndContact(b2Contact * contact)
{
	auto gO = ((GameObject*)contact->GetFixtureA()->GetUserData());
	auto g1 = ((GameObject*)contact->GetFixtureB()->GetUserData());
	std::cout << gO->getName();
	std::cout << g1->getName();
}