#include<iostream>
#include "HeapAllocator.h"
#include "FixedSizeAllocator.h"
#include "Assert\Assert.h"
using namespace Engine;
void mainx(char i_cargv, char** i_parg) {
	const size_t sizeOfHeap = 80;
	void* pHeapMemory = malloc(sizeOfHeap);
	MessagedAssert(pHeapMemory != NULL, "Memory not available on your wooden PC");

	FixedSizeAllocator* pHeap = FixedSizeAllocator::Create(pHeapMemory, sizeOfHeap,20);
	MessagedAssert(pHeap, "Never created the heap,Bruh!");
	int* ptr=static_cast<int*>(pHeap->alloc());
	*ptr = 4;
	pHeap->free(ptr);

	void* alloc = pHeap->alloc();
	int i=1;

	unsigned int totalAllocations = 0;
	long sizeAllocations = 0;
	unsigned int totalDeallocations=0;
	void * pMemory = 0;
	do
	{
		size_t sizeAlloc = static_cast<size_t>(rand());  

		pMemory = pHeap->alloc();

		if (pMemory)
		{
			sizeAllocations += sizeAlloc;
			totalAllocations++;
		}
		if (pHeap->free(pMemory)) {
			totalDeallocations++;
			
		}
	} while (pMemory != NULL);
	
	char string[50];
	sprintf(string, "Made %d allocations totaling %d from heap of %d\nTotal Dellocations: %u", totalAllocations, sizeAllocations, sizeOfHeap,totalDeallocations);
	MessagedAssert(false, string);
	getchar();
}

