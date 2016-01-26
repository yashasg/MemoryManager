#ifndef MONSTER_H
#define MONSTER_H
#include "Character.h"
namespace Engine{
	class Monster :public Character{
	public:
		bool isDead = false;
		int arrayPos = 0;
		Monster(){
			position.setX(-1000);
			position.setY( -1000);
		}
		Monster(Vector3 p){
			position = p;
		}
	};
}
#endif //!MONSTER_H