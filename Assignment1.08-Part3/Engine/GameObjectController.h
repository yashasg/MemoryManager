#ifndef GameObjectController_H
#define GameObjectController_H
#include "GameObject.h"

namespace Engine {
	class GameObjectController
	{
	protected:
		GameObject m_mygameObject; 
		GameObject *m_gameObject;
		const char* m_name;

	public:
		GameObjectController() {

			m_gameObject = &m_mygameObject;
		}
		inline virtual void MoveObject(Vector3 i_direction) = 0;



	};


}

#endif // !GameObject_H
