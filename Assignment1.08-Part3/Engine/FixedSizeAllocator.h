#ifndef FIXEDSIZEALLOCATOR_H
#define FIXEDSIZEALLOCATOR_H
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
namespace Engine {
#define ROUND_UP(addr,align) ((reinterpret_cast<uintptr_t>(addr) + (align - 1)) & ~(align - 1))
#define ROUND_DOWN(addr,align) (reinterpret_cast<uintptr_t>(addr) & ~(align - 1))
#define MAXDISCRIPTORS 1000
//	static unsigned char _myFreeMemory = 0xFF;
//	static unsigned char _myUnallocatedMemory = 0xAA;
	class FixedSizeAllocator {

	private: void Initialize(void * i_pMemory, size_t i_sizeMemory, unsigned int i_numDescriptors);
	public: static FixedSizeAllocator* Create(void* i_pHeapMemory, size_t i_sizeHeap, unsigned int numOfDesc = MAXDISCRIPTORS);
	public: void* alloc();
	public: bool free(void* i_ptrToFree);


		void InitializeBlocks(void * i_pFirstBlock, unsigned int i_numDescriptors, uint8_t* endmemory, unsigned int blockSize);
	private: int* removeFromAllocatedMemory(uint8_t* ptrToBase);
	private:int freeMemoryCount();
	private:bool addToFreeMemory(int* ptrToBase);
			int * GetFreeDescriptor();


			uint8_t*       m_pFreeMemory;
			uint8_t*       m_pAllocatedMemory;
	};

}
#endif //!HeapAllocator_H