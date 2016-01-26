#include<iostream>
#include<new>
#define MAX 100
#define CHAR_STEP 1
#include "MonsterController.h"
#include "PlayerController.h"
#include "Vector3.h"
#include "Assert\Assert.h"
#include "HeapAllocator.h"

using namespace std;
using namespace Engine;
	class MonsterManager {

	public:
		int removeDeadMonsters(MonsterController* arrMonster[], int length) {
			for (int i = 0; i < length; i++) {
				if (arrMonster[i]->isDead)
				{
					cout << "One of the Monsters just Died,Good Job" << endl;
					length -= 1;
					for (int k = i; k < length; k++) {
						int temp = k + 1;
						arrMonster[k] = arrMonster[temp];
					}

				}
			}
			return length;
		}
	};

	HeapManager* m_pHeapManager;
	inline void* operator new(size_t size){
		return m_pHeapManager->alloc(size);
	}
void main(void)
	{
		//_CrtSetBreakAlloc(145);
		const size_t 		sizeHeap = 1024 * 1024;
		MonsterController* o_arrmonster[MAX];
		int i_numOfMonsters;
		char i_movement;
		bool m_playerQuit = false;
		bool m_playerDead = false;
		bool m_monsterBaby = false;

		void * pHeapMemory = _aligned_malloc(sizeHeap, 4);
		HeapManager * pHeapManager = HeapManager::Create(pHeapMemory, sizeHeap);
		m_pHeapManager = pHeapManager;
		PlayerController* o_player = new PlayerController;
		o_player->setPositionOfObject(Vector3(0.0f, 0.0f, 0.0f));													//reinterpret_cast<PlayerController*>(pHeapManager->alloc(sizeof(PlayerController)));			//new PlayerController();
		cout << "Welcome to Monster Chase" << endl << "How Many Monsters do you want?(MAX=100)" << endl;
		cin >> i_numOfMonsters;
		MessagedAssert(i_numOfMonsters > 1, "Too few Monsters");

		for (int i = 0; i < i_numOfMonsters; i++) {
			o_arrmonster[i] = new MonsterController;
			o_arrmonster[i]->setPositionOfObject(Vector3((float)i, (float)i_numOfMonsters, 0.0f));
			o_arrmonster[i]->arrayPos = i;


		}
	/*	for (int i = 0; i < i_numOfMonsters; i++) {
			pHeapManager->free(o_arrmonster[i]);

		}
		pHeapManager->free(o_player);
		pHeapManager->collect();
		delete pHeapManager;
		_aligned_free(pHeapMemory);
		*/
		while (!m_playerQuit )
		{
			MonsterManager manager = MonsterManager();
			cout << "Press A to move left, D to move right, W to move up, S to move down, Q to quit:";
			cin >> i_movement;
			switch (i_movement)
			{
			case 'A':
			case 'a':
				o_player->MoveObject(Vector3(-CHAR_STEP, 0, 0));
				break;
			case 'S':
			case 's':
				o_player->MoveObject(Vector3(0, -CHAR_STEP, 0));
				break;
			case 'D':
			case 'd':
				o_player->MoveObject(Vector3(CHAR_STEP, 0, 0));
				break;
			case 'W':
			case 'w':
				o_player->MoveObject(Vector3(0, CHAR_STEP, 0));
				break;
			case 'Q':
			case 'q':
				m_playerQuit = true;
				cout << "bye Bye Player"<<endl;
				MessagedAssert(false, "Bye Bye Player!");
				return;
				break;
			default:
				MessagedAssert(false, "Wrong Input my friend");
				break;
			}

			//move monsters
			Vector3 m_playerPosition = o_player->getPositionOfObject();
			for (int i = 0; i < i_numOfMonsters; i++){
				if (o_arrmonster[i]->getPositionOfObject().getX() < m_playerPosition.getX())
					o_arrmonster[i]->MoveObject(Vector3(CHAR_STEP, 0, 0));
				else if (o_arrmonster[i]->getPositionOfObject().getX() > m_playerPosition.getX())
					o_arrmonster[i]->MoveObject(Vector3(-CHAR_STEP, 0, 0));
				if (o_arrmonster[i]->getPositionOfObject().getY()<  m_playerPosition.getY())
					o_arrmonster[i]->MoveObject(Vector3(0, 1, 0));
				else if (o_arrmonster[i]->getPositionOfObject().getY() > m_playerPosition.getY())
					o_arrmonster[i]->MoveObject(Vector3(0, -1, 0));

				//Check if player collides with monster
				if (m_playerPosition==o_arrmonster[i]->getPositionOfObject())
				{
					o_arrmonster[i]->isDead = true;
					i_numOfMonsters = manager.removeDeadMonsters(o_arrmonster, i_numOfMonsters);
					MessagedAssert(false, "Removed a monster");
				}
			}

			if (!m_playerQuit)
			{


				cout << "Player Position: [" << o_player->getPositionOfObject() << "]" << endl;
				for (int i = 0; i < i_numOfMonsters; i++){
					cout << "Monster(" << i << ") Position: [" << o_arrmonster[i]->getPositionOfObject() << "]"<<endl;
				}

			}
			if (i_numOfMonsters==0){
				cout << "You Won,Monsters Lost" << endl;
				for (int i = 0; i < i_numOfMonsters;i++)
				delete o_arrmonster[i];
				delete o_player;

				break;
			}

		}

	}
