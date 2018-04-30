#include "Utils.h"
#include "Content.h"
#include "VectorDrawer.h"
#include "PhysicsFactory.h"
#include "Game.h" 
#include "Model.h"
#include "dirent.h"
#include "Capsule.h"
#include "PhysicsGame1.h"
#include "PhysicsController.h"
#include "Sphere.h"
#include "PhysicsCamera.h"
#include "Box.h"
#include "Cylinder.h"
#include "Steerable3DController.h"
#include "Ground.h"
#include "Content.h"
#include <btBulletDynamicsCommon.h>
#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>
#include <gtx/euler_angles.hpp>
#include <gtx/norm.hpp>
#include "Creature.h"

/*using namespace BGE;

Assignment::Assignment(void)
{
}

Assignment::~Assignment(void)
{
}


bool Assignment::Initialise()
{

	physicsFactory->CreateGroundPhysics();
	physicsFactory->CreateCameraPhysics();


	setGravity(glm::vec3(0, -9, 0));
	setGravity(glm::vec3(0, 0, 0)); SAME CONCEPT*/

using namespace BGE;

Creature :: Creature(void){

}

Creature :: ~Creature(void){

}

bool Creature :: Initialise(){

	//Physics stuff
	physicsFactory -> CreateGroundPhysics();
	physicsFactory -> CreateCameraPhysics();
	setGravity(glm :: vec3(0, -9, 0));

	elapsed = 0;
	time = 5.0f;
	count = 0;

	//Create animat TODO: make controller
	//CreateBird(glm::vec3(-10, 20, 0)); SAME CONCEPT*
	creature = make_shared<CreatureController>(5, 5, 20);

	return Game::Initialise();
}

void Creature :: Update()
{
	//Need controller for this
	glm::vec3 rotate = creature -> rotate;

	//Forward
	if (keyState[SDL_SCANCODE_UP]){

		creature -> forward();

	}
	//Rotate
	else if (keyState[SDL_SCANCODE_LEFT]){

		creature->left(rotate);

	}
	else if (keyState[SDL_SCANCODE_RIGHT]){

		creature->right(-rotate);

	}
	//Jump or fly
	else if (keyState[SDL_SCANCODE_SPACE]){

		creature -> jump();

	}
	
	else{

		//Use physics to stop animat
		creature -> body -> rigidBody -> setFriction(100);
		creature -> abdomen -> rigidBody -> setFriction(100);

	}

	
	creature -> Update();
	Game :: Update();
}

void Creature :: Cleanup(){

	Game :: Cleanup();
} 