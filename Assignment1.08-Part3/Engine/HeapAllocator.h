#ifndef HeapAllocator_H
#define HeapAllocator_H
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
static unsigned char _myFreeMemory = 0xFF;
static unsigned char _myUnallocatedMemory=0xAA;
	class HeapManager{

		void Initialize(void * i_pMemory, size_t i_sizeMemory, unsigned int i_numDescriptors);
	public: static HeapManager* Create(void* i_pHeapMemory, size_t i_sizeHeap, unsigned int numOfDesc = MAXDISCRIPTORS);
	public: void* alloc(size_t i_allocSize);
	public: bool free(void* i_ptrToFree);
	public: void collect();
	
	
	private:
		typedef struct MemBlockDescriptor
		{
			size_t                      m_size;
			uint8_t *                   m_pBase;
			struct MemBlockDescriptor * m_pNext;
		} MemBlockDesc;

		void InitializeFreeDescriptors(MemBlockDesc * i_pFirstDescriptor, unsigned int i_numDescriptors);
		private: MemBlockDesc* removeFromAllocatedMemory(uint8_t* ptrToBase);
				 bool AttemptToCombineBlocks(MemBlockDesc & i_Block1, MemBlockDesc & i_Block2);
	private:int freeMemoryCount();
	private: void ReturnFreeDescriptor(MemBlockDesc & i_Block);
	private: void RemoveFromFreeMemory(MemBlockDesc & i_Block);
		private:bool addToFreeMemory(MemBlockDesc* ptrToBase);
		MemBlockDesc * GetFreeDescriptor();
		HeapManager* m_heapManager;

		MemBlockDesc * AllocateFromBlockEnd(MemBlockDesc & i_Block, size_t i_size);
		MemBlockDesc *       m_pFreeDescriptors;

		MemBlockDesc *       m_pFreeMemory;
		MemBlockDesc *       m_pAllocatedMemory;
	};

}
#endif //!HeapAllocator_H