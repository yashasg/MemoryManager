#ifndef CHARACTER_H
#define CHARACTER_H
#include"Vector3.h"

namespace Engine{

	class Character{
	public:
		Vector3 position;
		Character(){

		}

		Vector3 getPos(){
			return position;
		}
		void setPos(Vector3 p){
			position = p;
		}
		bool collidesWith(Character character)
		{
			if (position.getX() == character.position.getX() && position.getY() == character.position.getY())
				return true;
			return false;
		}

	};
}

#endif // !CHARACTER_H