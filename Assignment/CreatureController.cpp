#include "CreatureController.h"
#include "Utils.h"
#include "Content.h"
#include "Sphere.h"
#include "VectorDrawer.h"

using namespace BGE;

CreatureController :: CreatureController(float width, float height, float length){

	spawnPosition = glm :: vec3(0, 5, 0);
	elapsed = 0.0f;
	move = 1.0f;

	//Change legs max movment of legs
	alternate = true;
	force = 1000.0f;
	velocity = 10000000;
	strength = 10000000;
	CreateCreature(width, height, length);
}

/*glm::vec3 SceneGraphGame::NextPosition(float step, float steps)
{
	float radius = 30.0f;
	float y = 5.0f;
	float inc = (glm::pi<float>() * 2.0f) / steps;
	float angle = step * inc;
	glm::vec3 pos;
	
	pos.x = glm::sin(angle) * radius;
	pos.y = y;
	pos.z = - glm::cos(angle) * radius;
	waypoints.push_back(pos);
	return pos;
}
*/

CreatureController :: CreatureController(){

	spawnPosition = glm :: vec3(0, 10, 0);
	elapsed = 0.0f;
	move = 1.0f;

	//Change legs max movment of legs
	alternate = true;
	force = 1000.0f;
	velocity = 10000000;
	strength = 10000000;


	CreateCreature(5, 5, 10);
	body -> rigidBody -> setFriction(20);
	abdomen -> rigidBody -> setFriction(20);

}

CreatureController :: ~CreatureController(){


}

void CreatureController :: Update(){

	rotate = glm :: cross(body -> transform -> right*force, body -> transform -> look*4.0f);

	GameComponent :: Update();
}


void CreatureController :: Cleanup(){

	GameComponent :: Cleanup();
}

/*shared_ptr<PhysicsController> Assignment::CreateSeagull(glm::vec3 position, float scale)
{

	float scale = 5;
	float head_rad = scale / 1.5;
	shared_ptr<PhysicsController> head = physicsFactory->CreateSphere(head_rad, position + glm::vec3(0, scale + head_rad, scale), glm::quat());
	shared_ptr<PhysicsController> body = physicsFactory->CreateSphere(scale, position, glm::quat());
	//btHingeConstraint * head_body = new btHingeConstraint(*head->rigidBody, *body->rigidBody, GLToBtVector(glm::vec3(0, -(head_rad), -(head_rad))), GLToBtVector(glm::vec3(0, scale - 2, scale - 2)), btVector3(1, 0, 0), btVector3(1, 0, 0));	//	body hing bit thing is scale - 2 because head position and scale
	btTransform t1, t2;
	t1.setIdentity();
	t2.setIdentity();
	t1.setOrigin(btVector3(0, -(head_rad), -(head_rad)));
	t2.setOrigin(btVector3(0, scale - 2, scale - 2));
	btFixedConstraint * head_body = new btFixedConstraint(*head->rigidBody, *body->rigidBody, t1, t2);
	dynamicsWorld->addConstraint(head_body);SAME CONCEPT*/

//creates legs for the spider
shared_ptr<PhysicsController> CreatureController :: CreateLeg(bool leftLeg){

	glm :: vec3 position = spawnPosition;

	if (leftLeg){

		//Creates legs
		//shared_ptr<PhysicsController> left_wing_stick = physicsFactory->CreateBox(scale * 2, scale / 10, scale, left_wing_hinge + glm::vec3((scale)+2, 0, scale / 5), glm::quat());
		//Not sure if measurements are right as can't run but estimating
		position = glm :: vec3(7, 14, 0);
		shared_ptr<PhysicsController> part = Game :: Instance() -> physicsFactory -> CreateBox(5, .6, .6, position, glm :: quat());
		position = glm :: vec3(14, 14, 0);
		shared_ptr<PhysicsController> part2 = Game :: Instance() -> physicsFactory -> CreateBox(7, .6, .6, position, glm :: quat());
		part2 -> rigidBody -> setFriction(btScalar(0.0f));

		//Pivots
		btTransform t1, t2;
		t1.setIdentity();
		t2.setIdentity();
		t1.setOrigin(btVector3(3, 0, 0));
		t2.setRotation(GLToBtQuat(glm :: angleAxis(90.0f, glm::vec3(0, 0, 1))));
		t2.setOrigin(btVector3(-3, 0, 0));

		//Hinges
		//btHingeConstraint * body_l_shoulder = new btHingeConstraint(*body->rigidBody, *left_shoulder->rigidBody, GLToBtVector(glm::vec3(((scale + shoulder_rad) * (1 / glm::sqrt(2.0))), ((scale + shoulder_rad) * (1 / glm::sqrt(2.0))), 0)), GLToBtVector(glm::vec3(0, 0, 0)), btVector3(0, 0, 0), btVector3(0, 1, 0));
		btFixedConstraint* hinge2 = new btFixedConstraint(*part -> rigidBody, *part2 -> rigidBody, t1, t2);
		Game :: Instance() -> dynamicsWorld -> addConstraint(hinge2);

		return part;
	}
	else{

		//Not sure if measurements are right as can't run but estimating
		//shared_ptr<PhysicsController> left_wing_stick = physicsFactory->CreateBox(scale * 2, scale / 10, scale, left_wing_hinge + glm::vec3((scale)+2, 0, scale / 5), glm::quat());
		position = glm :: vec3(-7, 14, 0);
		shared_ptr<PhysicsController> part = Game :: Instance() -> physicsFactory -> CreateBox(4, .5, .5, position, glm::quat());
		position = glm :: vec3(-7, 14, 0);
		shared_ptr<PhysicsController> part2 = Game :: Instance() -> physicsFactory -> CreateBox(6, .5, .5, position, glm::quat());
		part2->rigidBody->setFriction(btScalar(0.0f));

		//Pivots
		btTransform t1, t2;
		t1.setIdentity();
		t2.setIdentity();
		t1.setOrigin(btVector3(-2.5, 0, 0));
		t2.setRotation(GLToBtQuat(glm :: angleAxis(-90.0f, glm::vec3(0, 0, 1))));
		t2.setOrigin(btVector3(2.5, 0, 0));
		
		//Hinges
		//btHingeConstraint * body_l_shoulder = new btHingeConstraint(*body->rigidBody, *left_shoulder->rigidBody, GLToBtVector(glm::vec3(((scale + shoulder_rad) * (1 / glm::sqrt(2.0))), ((scale + shoulder_rad) * (1 / glm::sqrt(2.0))), 0)), GLToBtVector(glm::vec3(0, 0, 0)), btVector3(0, 0, 0), btVector3(0, 1, 0));
		btFixedConstraint* hinge2 = new btFixedConstraint(*part -> rigidBody, *part2 -> rigidBody, t1, t2);
		Game :: Instance() -> dynamicsWorld -> addConstraint(hinge2);

		return part;
	}

}

/*
		wings
	

float shoulder_rad = glm::abs((glm::sqrt(2 * (scale * scale)) - scale) / 2);

glm::vec3 left_wing_hinge = position + glm::vec3(((scale + shoulder_rad) * (1 / glm::sqrt(2.0))), ((scale + shoulder_rad) * (1 / glm::sqrt(2.0))), 0);
glm::vec3 right_wing_hinge = position + glm::vec3(-((scale + shoulder_rad) * (1 / glm::sqrt(2.0))), ((scale + shoulder_rad) * (1 / glm::sqrt(2.0))), 0);

//shared_ptr<PhysicsController> left_shoulder = physicsFactory->CreateBox(scale * 2, scale / 5, scale, left_wing_hinge + glm::vec3((scale + shoulder_rad), 0, 0), glm::quat());

glm::quat shoulder_rot = glm::angleAxis(90.0F, glm::vec3(1, 0, 0));
shared_ptr<PhysicsController> left_shoulder = physicsFactory->CreateCylinder(shoulder_rad - 0.5, scale / 5, left_wing_hinge, shoulder_rot);
btHingeConstraint * body_l_shoulder = new btHingeConstraint(*body->rigidBody, *left_shoulder->rigidBody, GLToBtVector(glm::vec3(((scale + shoulder_rad) * (1 / glm::sqrt(2.0))), ((scale + shoulder_rad) * (1 / glm::sqrt(2.0))), 0)), GLToBtVector(glm::vec3(0, 0, 0)), btVector3(0, 0, 0), btVector3(0, 1, 0));
Game::dynamicsWorld->addConstraint(body_l_shoulder);
body_l_shoulder->enableAngularMotor(true, 20, 20);


shared_ptr<PhysicsController> left_wing_stick = physicsFactory->CreateBox(scale, scale / 10, scale / 10, left_wing_hinge + glm::vec3(scale / 2, 0, scale / 5), glm::quat());
btHingeConstraint * l_shoulder_stick = new btHingeConstraint(*left_shoulder->rigidBody, *left_wing_stick->rigidBody, btVector3(shoulder_rad, 0, 0), btVector3(-(scale - 0.5), 0, 0), btVector3(0, 1, 0), btVector3(0, 0, 1));
Game::dynamicsWorld->addConstraint(l_shoulder_stick);



shared_ptr<PhysicsController> left_wing_stable1 = physicsFactory->CreateBox(scale / 10, scale / 10, scale / 5, left_wing_hinge + glm::vec3(scale / 2, -(scale / 5), scale / 5), glm::quat());
shared_ptr<PhysicsController> left_wing_stable2 = physicsFactory->CreateBox(scale / 10, scale / 10, scale / 5, left_wing_hinge + glm::vec3(scale / 2, -(scale / 5), scale / 5), glm::quat());
btTransform t7, t8;
t7.setIdentity();
t8.setIdentity();
t7.setOrigin(GLToBtVector(left_wing_hinge + glm::vec3(scale / 1.5, (scale / 5), 0) - position));
//t7.setOrigin(GLToBtVector(left_wing_hinge - position));
t8.setOrigin(btVector3(0, 0, 0));
btFixedConstraint * left_wing_stable1_h = new btFixedConstraint(*body->rigidBody, *left_wing_stable1->rigidBody, t7, t8);
dynamicsWorld->addConstraint(left_wing_stable1_h);

btTransform t9, t10;
t9.setIdentity();
t10.setIdentity();
t9.setOrigin(GLToBtVector(left_wing_hinge + glm::vec3(scale / 1.5, -(scale / 5), 0) - position));
t10.setOrigin(btVector3(0, 0, 0));
btFixedConstraint * left_wing_stable2_h = new btFixedConstraint(*body->rigidBody, *left_wing_stable2->rigidBody, t9, t10);
dynamicsWorld->addConstraint(left_wing_stable2_h);



shared_ptr<PhysicsController> left_wing_stick = physicsFactory->CreateBox(scale * 2, scale / 10, scale / 10, left_wing_hinge + glm::vec3((scale) + 2, 0, scale / 5), glm::quat());
shared_ptr<PhysicsController> left_wing_stick = physicsFactory->CreateBox(scale * 2, scale / 10, scale, left_wing_hinge + glm::vec3((scale)+2, 0, scale / 5), glm::quat());
btHingeConstraint * l_shoulder_stick = new btHingeConstraint(*left_shoulder->rigidBody, *left_wing_stick->rigidBody, btVector3(shoulder_rad, 0, 0), btVector3(-((scale * 2) - shoulder_rad), 0, 0), btVector3(0, 1, 0), btVector3(0, 0, 1));
Game::dynamicsWorld->addConstraint(l_shoulder_stick);


btTransform t13, t14;
t13.setIdentity();
t14.setIdentity();
t13.setOrigin(GLToBtVector(left_wing_hinge - position + glm::vec3((scale) + 2, 0, 0)));
t14.setOrigin(GLToBtVector(glm::vec3( -((scale / 2) + 2), 0, 0)));
//btFixedConstraint * left_stick_stable = new btFixedConstraint(*body->rigidBody, *left_wing_stick->rigidBody, t13, t14);
btHingeConstraint * left_stick_stable = new btHingeConstraint(*body->rigidBody, *left_wing_stick->rigidBody, GLToBtVector(left_wing_hinge - position + glm::vec3((scale)+2, 0, 0)), GLToBtVector(glm::vec3(-((scale / 2) + 2), 0, 0)), btVector3(0, 0, 1), btVector3(0, 0, 1));
dynamicsWorld->addConstraint(left_stick_stable);




shared_ptr<PhysicsController> left_wing = physicsFactory->CreateBox(scale * 2, scale / 5, scale, left_wing_hinge + glm::vec3((scale + shoulder_rad), 0, 0) + glm::vec3((scale / 2) + 2, 0, scale / 5), glm::quat());

btTransform t11, t12;
t11.setIdentity();
t12.setIdentity();
t11.setOrigin(GLToBtVector(left_wing_hinge + glm::vec3((scale) + 2, 0, 0)));
//t12.setOrigin(GLToBtVector(left_wing_hinge + glm::vec3(((scale)+shoulder_rad), 0, 0) - position));
t12.setOrigin(GLToBtVector(left_wing_hinge + glm::vec3((scale * 2 ) + 2 + shoulder_rad, 0, 0)));
btFixedConstraint * left_stick_wing = new btFixedConstraint(*left_wing_stick->rigidBody, *left_wing->rigidBody, t11, t12);
dynamicsWorld->addConstraint(left_stick_wing);


shared_ptr<PhysicsController> right_shoulder = physicsFactory->CreateBox(scale * 2, scale / 5, scale, right_wing_hinge + glm::vec3(-(scale + shoulder_rad), 0, 0), glm::quat());


shared_ptr<PhysicsController> right_shoulder = physicsFactory->CreateCylinder(shoulder_rad - 0.5, scale / 5, right_wing_hinge, shoulder_rot);
btHingeConstraint * body_r_shoulder = new btHingeConstraint(*body->rigidBody, *right_shoulder->rigidBody, GLToBtVector(glm::vec3(-((scale + shoulder_rad) * (1 / glm::sqrt(2.0))), ((scale + shoulder_rad) * (1 / glm::sqrt(2.0))), 0)), GLToBtVector(glm::vec3(0, 0, 0)), btVector3(0, 0, 0), btVector3(0, 1, 0));
Game::dynamicsWorld->addConstraint(body_r_shoulder);
body_r_shoulder->enableAngularMotor(true, -20, 20);

shared_ptr<PhysicsController> right_wing_stick = physicsFactory->CreateBox(scale * 2, scale / 10, scale, right_wing_hinge + glm::vec3(-(scale / 2), 0, scale / 5), glm::quat());
btHingeConstraint * r_shoulder_stick = new btHingeConstraint(*right_shoulder->rigidBody, *right_wing_stick->rigidBody, btVector3(-shoulder_rad, 0, 0), btVector3((scale * 2) - shoulder_rad, 0, 0), btVector3(0, 1, 0), btVector3(0, 0, 1));
Game::dynamicsWorld->addConstraint(r_shoulder_stick);


shared_ptr<PhysicsController> left_wing = physicsFactory->CreateBox(scale * 2, scale / 5, scale, left_wing_hinge + glm::vec3((scale + shoulder_rad), 0, 0), glm::quat());
shared_ptr<PhysicsController> right_wing = physicsFactory->CreateBox(scale * 2, scale / 5, scale, right_wing_hinge + glm::vec3(-(scale + shoulder_rad), 0, 0), glm::quat());
btHingeConstraint * body_l_wing = new btHingeConstraint(*body->rigidBody, *left_wing->rigidBody, GLToBtVector(glm::vec3(((scale + shoulder_rad) * (1 / glm::sqrt(2.0))), ((scale + shoulder_rad) * (1 / glm::sqrt(2.0))), 0)), GLToBtVector(glm::vec3(-(scale + shoulder_rad), 0, 0)), btVector3(0, 0, 1), btVector3(0, 0, 1));
btHingeConstraint * body_r_wing = new btHingeConstraint(*body->rigidBody, *right_wing->rigidBody, GLToBtVector(glm::vec3(-((scale + shoulder_rad) * (1 / glm::sqrt(2.0))), ((scale + shoulder_rad) * (1 / glm::sqrt(2.0))), 0)), GLToBtVector(glm::vec3((scale + shoulder_rad), 0, 0)), btVector3(0, 0, 1), btVector3(0, 0, 1));

body_l_wing->enableAngularMotor(true, -5, 5);
body_r_wing->enableAngularMotor(true, 5, 5);
body_l_wing->;

Game::dynamicsWorld->addConstraint(body_l_wing);
Game::dynamicsWorld->addConstraint(body_r_wing);

SAME CONCEPT*/

//Makes body and attaches legs
shared_ptr<PhysicsController> CreatureController :: CreateBody(vector<shared_ptr<PhysicsController>> limbs, glm :: vec3 scale){

	glm :: vec3 position = spawnPosition;
	glm :: vec3 offset;

	float width = scale.x;
	float height = scale.y;
	float length = scale.z;
	float turningAngle = glm :: half_pi<float>() / 4;
	offset = glm :: vec3(0, 0, length + 1);

	/*TODO: MAYBE ADD WINGS?
	glm::vec3 left_wing_hinge = position + glm::vec3(((scale + shoulder_rad) * (1 / glm::sqrt(2.0))), ((scale + shoulder_rad) * (1 / glm::sqrt(2.0))), 0);
	glm::vec3 right_wing_hinge = position + glm::vec3(-((scale + shoulder_rad) * (1 / glm::sqrt(2.0))), ((scale + shoulder_rad) * (1 / glm::sqrt(2.0))), 0);
	*/
	shared_ptr<PhysicsController> body = Game::Instance()->physicsFactory->CreateBox(width, height, length, position, glm::quat());
	abdomen = Game::Instance()->physicsFactory->CreateBox(width + 1, height + 1, length / 2, position + offset, glm::quat());
	btFixedConstraint* body_abdomen;

	btTransform transformA;
	btTransform transformB;

	//Attach body parts
	transformA.setIdentity();
	transformB.setIdentity();
	transformA.setOrigin(btVector3(0, 0, length));
	transformB.setOrigin(btVector3(0, 0, 0));
	body_abdomen = new btFixedConstraint(*body->rigidBody, *abdomen->rigidBody, transformA, transformB);
	Game::Instance()->dynamicsWorld->addConstraint(body_abdomen);

	//Attach legs
	for (int i = 0; i < 6; i++)
	{
		if (i<3) {
			//Left legs
			//Not sure if measurements are right as can't run but estimating
			btVector3 bodyPivot = btVector3(-width - 1, 1, (length / 2) - ((length / 4)*i));
			btVector3 legPivot = btVector3(0, 0, 0);

			//btHingeConstraint * head_body = new btHingeConstraint(*head->rigidBody, *body->rigidBody, GLToBtVector(glm::vec3(0, -(head_rad), -(head_rad))), GLToBtVector(glm::vec3(0, scale - 2, scale - 2)), btVector3(1, 0, 0), btVector3(1, 0, 0));	//	body hing bit thing is scale - 2 because head position and scale
			btHingeConstraint* rightHinge = new btHingeConstraint(*body->rigidBody, *limbs.at(i)->rigidBody, bodyPivot, legPivot, btVector3(0, 1, 0), btVector3(-1, 1, 0), true);
			rightHinge->setLimit(-turningAngle, turningAngle);
			joints.push_back(rightHinge);
			Game::Instance()->dynamicsWorld->addConstraint(rightHinge);
		}
		else{

			//Right legs 
			//Not sure if measurements are right as can't run but estimating
			btVector3 bodyPivot = btVector3(width + 1, 1, (length / 2) - ((length / 4)*(i - 4)));
			btVector3 legPivot = btVector3(0, 0, 0);
			
			//btHingeConstraint * head_body = new btHingeConstraint(*head->rigidBody, *body->rigidBody, GLToBtVector(glm::vec3(0, -(head_rad), -(head_rad))), GLToBtVector(glm::vec3(0, scale - 2, scale - 2)), btVector3(1, 0, 0), btVector3(1, 0, 0));	//	body hing bit thing is scale - 2 because head position and scale
			btHingeConstraint* leftHinge = new btHingeConstraint(*body->rigidBody, *limbs.at(i)->rigidBody, bodyPivot, legPivot, btVector3(0, 1, 0), btVector3(1, 1, 0), true);
			leftHinge->setLimit(-turningAngle, turningAngle);
			joints.push_back(leftHinge);
			Game::Instance()->dynamicsWorld->addConstraint(leftHinge);
		}
	}

	return body;
}

//Attachments
shared_ptr<PhysicsController> CreatureController :: CreateCreature(float _width, float _height, float _length){

	float width = _width;
	float height = _height;
	float length = _length;

	glm :: vec3 scale = glm :: vec3(width, height, length);
	/*ship4Controller->route->waypoints.push_back(ship4Controller->transform->position);
	ship4Controller->route->waypoints.push_back(ship4Controller->transform->position + glm::vec3(15, 0, 0));
	ship4Controller->route->waypoints.push_back(ship4Controller->transform->position + glm::vec3(15, 0, -15));
	ship4Controller->route->waypoints.push_back(ship4Controller->transform->position + glm::vec3(0, 0, -15));
	ship4Controller->route->looped = true; SAME CONCEPT*/
	//Limbs and body together
	for (int i = 0; i < 6; i++){

		limbs.push_back(CreateLeg(false));

	}
	for (int i = 0; i < 6; i++){

		limbs.push_back(CreateLeg(true));

	}

	body = CreateBody(limbs, scale);

	return body;
}

//Move forward
void CreatureController :: forward(){

	/*Applying Forces:
	You can call applyForce to apply force to a point on a rigidbody or
	applyCentralForce or applyTorque:*/
	body -> rigidBody -> setFriction(0);
	abdomen -> rigidBody -> setFriction(0);
	body -> rigidBody->applyCentralForce(GLToBtVector(body->transform->look * force));
	virtualise();
}

//Move left 
void CreatureController :: left(glm::vec3 rotate){

	/*Applying Forces:
	You can call applyForce to apply force to a point on a rigidbody or
	applyCentralForce or applyTorque:*/
	body -> rigidBody -> setFriction(0);
	abdomen -> rigidBody -> setFriction(0);
	body -> rigidBody -> applyTorque(GLToBtVector(rotate));
	virtualise();
}

//Move right
void CreatureController :: right(glm::vec3 rotate){

	/*Applying Forces:
	You can call applyForce to apply force to a point on a rigidbody or
	applyCentralForce or applyTorque:*/
	body -> rigidBody -> setFriction(0);
	abdomen -> rigidBody -> setFriction(0);
	body -> rigidBody -> applyTorque(GLToBtVector(rotate));
	virtualise();
}


//Make movements look real
void CreatureController :: virtualise(){

	if (elapsed > move){

		creatureWalk(alternate);
		alternate = !alternate;
		elapsed = 0;

	}
	else {

		elapsed += Time :: deltaTime;

	}
}


//Make creature jump/fly
void CreatureController::jump(){

	/*Applying Forces:
	You can call applyForce to apply force to a point on a rigidbody or
	applyCentralForce or applyTorque:*/
	body -> rigidBody -> setFriction(0);
	abdomen -> rigidBody -> setFriction(0);
	body -> rigidBody -> applyCentralForce(GLToBtVector(body->transform->up * (force * 10)));

}

//Make animat walk
void CreatureController::creatureWalk(bool inverse){

	if (inverse)
	{
		for (int i = 0; i < 6; i++){

			//Modulus to switch legs
			if (i % 2 == 0){

				joints.at(i)->enableAngularMotor(true, velocity, strength);

			}
			else{

				joints.at(i)->enableAngularMotor(true, -velocity, strength);
			}
		}
	}
	else{

		for (int i = 0; i < 6; i++){

			//Modulus to switch legs
			if (i % 2 == 0){

				joints.at(i)->enableAngularMotor(true, -velocity, strength);

			}
			else{

				joints.at(i)->enableAngularMotor(true, velocity, strength);

			}
		}
	}

}