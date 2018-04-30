#include "Box.h"
#include "Game.h"
#include "PhysicsController.h"
#include "PhysicsFactory.h"
#include <btBulletDynamicsCommon.h>
#include "SnowEffect.h"
#include "CreatureController.h"

/*namespace BGE
{
	class Assignment :
		public Game
	{
	private:

	public:
		Assignment(void);
		~Assignment(void);
		bool Initialise();
		void Update();
		void Cleanup();
		void CreateWall();
		shared_ptr<PhysicsController> bird;
		shared_ptr<PhysicsController> CreateSeagull(glm::vec3 position, float scale = 5);
		shared_ptr<PhysicsController> CreateSeagull2(glm::vec3 position);
	};
}
SAME CONCEPT*/

namespace BGE{

	class Creature :
		public Game{

	private:

	public:
		
		Creature(void);
		~Creature(void);
		bool Initialise();
		void Update();
		void Cleanup();
		float elapsed;
		float time;
		int count;
		
		//TODO: make controller
		shared_ptr<CreatureController> creature;

	};
}