#include "HeapAllocator.h"
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
namespace Engine {

		void HeapManager::Initialize(void * i_pMemory, size_t i_sizeMemory, unsigned int i_numDescriptors)
	{
		assert(i_pMemory);
		assert(i_sizeMemory);
		assert(i_numDescriptors * sizeof(MemBlockDesc) < i_sizeMemory);

		MemBlockDesc * pMemBlocks = reinterpret_cast<MemBlockDesc *>(i_pMemory);
		InitializeFreeDescriptors(pMemBlocks, i_numDescriptors);

		uint8_t * pFreeMemoryStart = reinterpret_cast<uint8_t *>(pMemBlocks + i_numDescriptors);
		uint8_t * pFreeMemoryEnd = reinterpret_cast<uint8_t *>(i_pMemory) + i_sizeMemory;

		m_pFreeMemory = GetFreeDescriptor();
		assert(m_pFreeMemory);

		m_pFreeMemory->m_pBase = reinterpret_cast<uint8_t *>(ROUND_UP(pFreeMemoryStart, 4));
		m_pFreeMemory->m_size = pFreeMemoryEnd - m_pFreeMemory->m_pBase;
		m_pFreeMemory->m_pNext = NULL;

		m_pAllocatedMemory = NULL;
	}

		 HeapManager* HeapManager::Create(void * i_pHeapMemory, size_t i_sizeHeap,unsigned int numOfDesc)
		{
			HeapManager* heapManager =reinterpret_cast<HeapManager*>( malloc (sizeof(HeapManager)));
			heapManager->Initialize(i_pHeapMemory, i_sizeHeap, numOfDesc);
			return heapManager;
		}


 bool Engine::HeapManager::free(void * i_ptrToFree)
 {
	 uint8_t* ptrToBase = reinterpret_cast<uint8_t*>(i_ptrToFree);
	 int freecounter = freeMemoryCount();
				 return addToFreeMemory(removeFromAllocatedMemory(ptrToBase));
		 }
 void HeapManager::collect()
 {

	 int freecounter= freeMemoryCount();
	 bool combined = false;
	 for (MemBlockDesc* head = m_pFreeMemory; head != NULL;) {
		 combined = false;
		 uint8_t* memAddress = head->m_pBase + head->m_size;
		 MemBlockDesc* nextOfIter;
		 for (MemBlockDesc* iterator = m_pFreeMemory; iterator != NULL; iterator = nextOfIter) {
			 nextOfIter = iterator->m_pNext;
			 if (memAddress == iterator->m_pBase) {

				 if (AttemptToCombineBlocks(*head, *iterator)) {
					 combined = true;
					 freecounter=freeMemoryCount();
				 }


			 }

		 }
		head = combined ? head : head->m_pNext;
	 }

 }


 bool HeapManager::addToFreeMemory(MemBlockDesc * ptrToBase)
 {
	 if (ptrToBase == NULL) { 
		 return false;
	 }

	 ptrToBase->m_pNext = m_pFreeMemory;
	 m_pFreeMemory = ptrToBase;
	 return true;
 }
 HeapManager::MemBlockDesc* HeapManager::removeFromAllocatedMemory(uint8_t * ptrToBase)
 {
	 MemBlockDesc* prevPtr=NULL, *nextPtr=NULL;
	 MemBlockDesc* tempPtr = m_pAllocatedMemory;
	 for (tempPtr; tempPtr != NULL; tempPtr = tempPtr->m_pNext) {
		 nextPtr = tempPtr->m_pNext;
		 if (tempPtr->m_pBase == ptrToBase) {
			 if (prevPtr == NULL && nextPtr==NULL) {
				 m_pAllocatedMemory = NULL;
				 return tempPtr;
			 }
			 else if (prevPtr == NULL) {
				 m_pAllocatedMemory = nextPtr;
				 return tempPtr;
			 }
			 else if (nextPtr == NULL) {
				 prevPtr->m_pNext = NULL;
				 return tempPtr;
			 }
			 else {
				 prevPtr->m_pNext = nextPtr;
				 return tempPtr;
			 }
			 
			// prevPtr->m_pNext = nextPtr;
			 //return tempPtr;
		 }
		 prevPtr = tempPtr;
	 }

	 return NULL;
 }

		 void * HeapManager::alloc(size_t i_allocSize)
		 {
			 MemBlockDesc* returnedDesc = AllocateFromBlockEnd(*m_pFreeMemory, i_allocSize);
			 if (!returnedDesc) {
				 return NULL;
			 }
			 returnedDesc->m_pNext = m_pAllocatedMemory;
			 m_pAllocatedMemory = returnedDesc;
			 return m_pAllocatedMemory->m_pBase;

		 }

	 bool HeapManager::AttemptToCombineBlocks(MemBlockDesc & i_Block1, MemBlockDesc & i_Block2)
		 {	
			 // See if Block1 ends at the address right before Block2 starts
			 // If so consume Block2's memory into Block1 and return
			 // Block2's descriptor to the free descriptor pool

				 // Expand Block1 to consume Block2's memory
				 i_Block1.m_size += i_Block2.m_size;
				 // Return Block2's descriptor to the free descriptor pool
				 // since it's memory was consumed into Block1 and it's
				 // descriptor is of no need
				 RemoveFromFreeMemory(i_Block2);
				 ReturnFreeDescriptor(i_Block2);

				 return true;
			 }


	 int HeapManager::freeMemoryCount()
	 {
		 int counter=0;
		 MemBlockDesc* temp = m_pFreeMemory;


		 while (temp!=NULL)
		 {
			 counter++;
			 temp = temp->m_pNext;
		 }
		 return counter;
		 
	 }

	 void HeapManager::ReturnFreeDescriptor(MemBlockDesc & i_Block)
	 {

		 i_Block.m_pNext = m_pFreeDescriptors;
		 i_Block.m_size = 0;
		 m_pFreeDescriptors = &i_Block;

	 }

	 void HeapManager::RemoveFromFreeMemory(MemBlockDesc & i_Block)
	 {
		 MemBlockDesc* prevPtr = NULL, *nextPtr = NULL;
		 MemBlockDesc* tempPtr = m_pFreeMemory;
		 for (tempPtr; tempPtr != NULL; tempPtr = tempPtr->m_pNext) {
			 nextPtr = tempPtr->m_pNext;
			 if (tempPtr == &i_Block) {
				 if (prevPtr == NULL && nextPtr == NULL) {
					 m_pFreeMemory = NULL;
					 return;
				 }
				 else if (prevPtr == NULL) {
					 m_pFreeMemory = nextPtr;
					 return;
				 }
				 else if (nextPtr == NULL) {
					 prevPtr->m_pNext = NULL;
					 return;
				 }
				 else {
					 prevPtr->m_pNext = nextPtr;
					 return;
				 }

			 }
			 prevPtr = tempPtr;
		 }

	 }
			 

		 

		void HeapManager::InitializeFreeDescriptors(MemBlockDesc * i_pFirstDescriptor, unsigned int i_numDescriptors)
		{
			
			MemBlockDesc * tempDesc = i_pFirstDescriptor;
			for (unsigned int i = 1; i <= i_numDescriptors; i++) {
				tempDesc->m_pBase = (uint8_t*)0xCDCDCDCD;
				tempDesc->m_size = 0;
				tempDesc->m_pNext = tempDesc+1;
				tempDesc++;
			}
			tempDesc->m_pNext = NULL;
			m_pFreeDescriptors= i_pFirstDescriptor;
		}
		
		HeapManager::MemBlockDesc * HeapManager::GetFreeDescriptor()
		{
			if (m_pFreeDescriptors->m_pNext)
			{
				MemBlockDesc* temp = m_pFreeDescriptors;
				m_pFreeDescriptors = m_pFreeDescriptors->m_pNext;
				return temp;
			}
			else return NULL;
		}

		HeapManager::MemBlockDesc * HeapManager::AllocateFromBlockEnd(MemBlockDesc & i_Block, size_t i_size)
{
		uint8_t * pNewBlockStart = i_Block.m_pBase + i_Block.m_size - i_size;
		pNewBlockStart = reinterpret_cast<uint8_t *>(ROUND_DOWN(pNewBlockStart, 4));

		// ensure that, after rounding, this block is big enough
		//assert(pNewBlockStart >= i_Block.m_pBase);

		if (pNewBlockStart < i_Block.m_pBase)
			return NULL;

		MemBlockDesc * pDesc = GetFreeDescriptor();
//		assert(pDesc,"No free descriptors");

		if (!pDesc)
			return NULL;

		pDesc->m_size = i_Block.m_pBase + i_Block.m_size - pNewBlockStart;
		pDesc->m_pBase = pNewBlockStart;
		pDesc->m_pNext = NULL;
		uint8_t* addressStart = reinterpret_cast<uint8_t*>(pNewBlockStart);
		uint8_t* addressEnd= reinterpret_cast<uint8_t*>(pNewBlockStart+pDesc->m_size);
		for (uint8_t* i = addressStart; i < addressEnd; i++)
			*i = _myFreeMemory;

		i_Block.m_size = pNewBlockStart - i_Block.m_pBase;
		

		return pDesc;
	}
}
