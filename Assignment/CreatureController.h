#pragma once
#include "Game.h"
#include "GameComponent.h"
#include "PhysicsController.h"
#include "PhysicsFactory.h"
#include <btBulletDynamicsCommon.h>
#include <vector>
#include <iostream>
#include "Content.h"
#include "VectorDrawer.h"
#include "XBoxController.h"
#include "Steerable3DController.h"
#include "SteeringControler.h"
#include "Params.h"
#include "FountainEffect.h"
#include "Box.h"
#include "SnowEffect.h"

namespace BGE
{
	class CreatureController :
		public GameComponent{

	private:
		
		//Make Creature
		//shared_ptr<PhysicsController> bird = CreateSeagull(glm::vec3(-10, 30, 0), 5); SAME CONCEPT*
		shared_ptr<PhysicsController> CreateLeg(bool leftLeg);
		shared_ptr<PhysicsController> CreateBody(vector<shared_ptr<PhysicsController>> limbs, glm :: vec3 scale);
		glm :: vec3 spawnPosition;

	public:
		
		CreatureController(float length, float width, float height);
		CreatureController(glm :: vec3 position);
		CreatureController();
		~CreatureController();

		void Update();
		void Cleanup();
		//Parts for assignment*
		void forward();
		void jump();
		void left(glm :: vec3 rotate);
		void right(glm :: vec3 rotate);
		void creatureWalk(bool inverse);
		void virtualise();


		
		shared_ptr<PhysicsController> CreateCreature(float width, float height, float length);

		//For creature body parts MAYBE: GIVE WINGS?
		/*glm::vec3 left_wing_hinge = position + glm::vec3(((scale + shoulder_rad) * (1 / glm::sqrt(2.0))), ((scale + shoulder_rad) * (1 / glm::sqrt(2.0))), 0);
		glm::vec3 right_wing_hinge = position + glm::vec3(-((scale + shoulder_rad) * (1 / glm::sqrt(2.0))), ((scale + shoulder_rad) * (1 / glm::sqrt(2.0))), 0);*/

		/*glm::vec3 NextPosition(float step, float steps);
		vector<glm::vec3> waypoints;
		shared_ptr<GameComponent> selfExample;
		shared_ptr<GameComponent> station;
		shared_ptr<GameComponent> ship1; SAME CONCEPT*/

		vector<shared_ptr<PhysicsController>> limbs;
		vector<btHingeConstraint*> joints;
		shared_ptr<PhysicsController> body;
		shared_ptr<PhysicsController> abdomen;
		shared_ptr<PhysicsController> wings;
		shared_ptr<PhysicsController> creature;

		//For rotation/turning
		glm::vec3 rotate;

		//For movement of legs
		bool alternate;
		float elapsed;
		float move;
		int velocity;
		int strength;
		float force;
		
	};
}