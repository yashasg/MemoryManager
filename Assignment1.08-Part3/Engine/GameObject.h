#ifndef GameObject_H
#define GameObject_H
#include"Vector3.h"

namespace Engine{

	class GameObject {
	public:
		Vector3 m_position;
		 char* const  m_name;
		 GameObject() :m_name{ NULL } {

		}
		char* getName() {
			char* o_name = m_name;
			return o_name;
		}
		void setName(char * i_name) {
			strcpy(m_name, i_name);
		}
		Vector3 getPos(){
			return m_position;
		}
		void setPos(Vector3& p){
			m_position = p;
		}

	};
}

#endif // !GameObject_H