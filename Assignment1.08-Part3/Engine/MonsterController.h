#ifndef MonsterController_H
#define MonsterController_H
#include "Assert\Assert.h"
#include "GameObjectController.h"
#include <string>

namespace Engine {
	class MonsterController :GameObjectController
	{
	public:
		
		MonsterController():GameObjectController() {
		}
		MonsterController(Vector3 i_position) :GameObjectController() {
			m_gameObject->setPos(i_position);
		}
		MonsterController(Vector3 i_position,char* i_name) :GameObjectController() {
			m_gameObject->setPos(i_position);
			m_gameObject->setName(i_name);
		}

		bool isDead = false;
		int arrayPos = 0;
		inline virtual void MoveObject(Vector3 i_direction) {
		 m_gameObject->m_position;
		 m_gameObject->setPos(m_gameObject->getPos() + i_direction);

		}
		inline virtual Vector3 getPositionOfObject() {
			Vector3 gameObjectPosition = m_gameObject->m_position;
			return gameObjectPosition.getPosition();


		}
		inline virtual void setPositionOfObject(Vector3 i_position) {
			Vector3 gameObjectPosition = m_gameObject->m_position;
			return gameObjectPosition.setPosition(i_position);


		}

	};


}
#endif //!MonsterController