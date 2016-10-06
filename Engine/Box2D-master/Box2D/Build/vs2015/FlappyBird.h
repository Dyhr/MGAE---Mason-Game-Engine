#pragma once

#include "Testbed\Framework\Test.h"

class FlappyBird : public Test
{
	public:
		b2Body* birdbody;
		bool hasLeftTheGround = false;
		bool reset = false;

		FlappyBird(){ 
		
			b2PolygonShape pillar1bottom;
			b2PolygonShape pillar1top;
			b2PolygonShape pillar2bottom;
			b2PolygonShape pillar2top;
			b2PolygonShape pillar3;
			b2PolygonShape pillar4top;
			b2PolygonShape pillar4bottom;
			
			b2EdgeShape floor;
			floor.Set(b2Vec2(-20.0f, 0.0f), b2Vec2(20.0f, 0.0f));

			b2EdgeShape ceiling;
			ceiling.Set(b2Vec2(-20.0f, 10.0f), b2Vec2(20.0f, 10.0f));


			pillar1bottom.SetAsBox(1.0f,2.0f, b2Vec2(-5.0f, 2.0f), 0.0f);
			pillar1top.SetAsBox(1.0f, 1.5f, b2Vec2(-5.0f, 8.5f), 0.0f);
			pillar2bottom.SetAsBox(1.0f, 2.5f, b2Vec2(5.0f, 2.5f), 0.0f);
			pillar2top.SetAsBox(1.0f, 1.0f, b2Vec2(5.0f, 9.0f), 0.0f);
			pillar3.SetAsBox(1.0f, 4.0f, b2Vec2(12.5f, 4.0f), 0.0f);
			pillar4bottom.SetAsBox(1.0f, 2.0f, b2Vec2(20.0f, 2.0f), 0.0f);
			pillar4top.SetAsBox(1.0f, 2.0f, b2Vec2(20.0f, 8.0f), 0.0f);


			b2BodyDef birdbd;
			birdbd.position.Set(-19.0f, 1.0f);
			birdbd.type = b2_dynamicBody;
			birdbd.fixedRotation = true;
			birdbody = m_world->CreateBody(&birdbd);

			b2CircleShape bird;
			bird.m_radius = 0.5f;
			b2FixtureDef fd;
			fd.shape = &bird;
			fd.density = 20.0f;
			fd.friction = 1.0f;

			birdbody->CreateFixture(&fd);


			b2BodyDef bd;
			b2Body* ground = m_world->CreateBody(&bd);//ground includes all the elements in the game world

			ground->CreateFixture(&pillar1bottom,0.0f);
			ground->CreateFixture(&pillar1top, 0.0f);
			ground->CreateFixture(&pillar2bottom, 0.0f);
			ground->CreateFixture(&pillar2top, 0.0f);
			ground->CreateFixture(&pillar3, 0.0f);
			ground->CreateFixture(&pillar4top, 0.0f);
			ground->CreateFixture(&pillar4bottom, 0.0f);
			ground->CreateFixture(&floor, 0.0f);
			ground->CreateFixture(&ceiling, 0.0f);

		}

		void Step(Settings* settings) {

			//run the default physics and rendering

			Test::Step(settings);

			if (reset) {
				reset = false;
				birdbody->SetTransform(b2Vec2(-19, 1), 0);
				hasLeftTheGround = 0;
				birdbody->SetLinearVelocity(b2Vec2(0, 0));
			}

			if (hasLeftTheGround) {
				b2Vec2 v = birdbody->GetLinearVelocity();
				v.x = 5;
				birdbody->SetLinearVelocity(v);
			}
	}

		static Test* Create()
		{
			return new FlappyBird;
		}

		void Keyboard(int key) {
			if (key == GLFW_KEY_W) {
				float impulse = birdbody->GetMass()*300;
				birdbody->ApplyForceToCenter(b2Vec2(0, impulse), true);
				hasLeftTheGround = true;
			}
		}

		void BeginContact(b2Contact* contact) {
			if (hasLeftTheGround) {
				reset = true;
			}
		}
};
