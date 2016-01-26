#ifndef PLAYER_H
#define PLAYER_H
#include "Character.h"
namespace Engine{
	class Player : public Character{
	public:
		Player(Vector3 p){

			position = p;
		}


	};

}
#endif //!PLAYER_H