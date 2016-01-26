#ifndef PlayerController_H
#define PlayerController_H
#include "GameObjectController.h"

namespace Engine {
	class PlayerController:GameObjectController
	{

	public:
		PlayerController():GameObjectController() {
			Vector3 *gameObjectPosition = &m_gameObject->m_position;
			gameObjectPosition->setPosition(Vector3(0,0,0));
		}
		PlayerController(Vector3 i_position) {
			Vector3 *gameObjectPosition = &m_gameObject->m_position;
			gameObjectPosition->setPosition(i_position);
		}
		PlayerController(Vector3 i_position,char* i_name) {
			Vector3 *gameObjectPosition = &m_gameObject->m_position;
			gameObjectPosition->setPosition(i_position);
			m_gameObject->setName(i_name);
		}
		inline virtual void MoveObject(Vector3 i_direction) {
			Vector3 *gameObjectPosition = &m_gameObject->m_position;
			gameObjectPosition->setPosition(gameObjectPosition->getPosition() + i_direction);


		}
		inline virtual Vector3 getPositionOfObject() {
			Vector3 *gameObjectPosition = &m_gameObject->m_position;
			return gameObjectPosition->getPosition();


		}
		inline virtual void setPositionOfObject(Vector3 i_position) {
			Vector3 gameObjectPosition = m_gameObject->m_position;
			return gameObjectPosition.setPosition(i_position);


		}

	};


}

#endif // !PlayerController