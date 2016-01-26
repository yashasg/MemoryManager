#include "HeapAllocator.h"

bool AttemptToCombineBlocks(MemBlockDesc & i_Block1, MemBlockDesc & i_Block2)
{
	// See if Block1 ends at the address right before Block2 starts
	// If so consume Block2's memory into Block1 and return
	// Block2's descriptor to the free descriptor pool
	
	if( (i_Block1.m_pBase + i_Block1.m_size) == (i_Block2.m_pBase - 1))
	{
		// Expand Block1 to consume Block2's memory
		i_Block1.m_size += i_Block1.m_size;
		// Return Block2's descriptor to the free descriptor pool
		// since it's memory was consumed into Block1 and it's
		// descriptor is of no need
		ReturnFreeDescriptor( i_Block2 );
		
		return true;
	}
	
	return false;
}


bool HeapManager_UnitTest()
{
	const size_t 		sizeHeap = 1024 * 1024;
	const unsigned int 	numDescriptors = 2048;
	
	// Allocate memory for my test heap.
	void * pHeapMemory = _aligned_malloc(sizeHeap, 4);
	assert( pHeapMemory );
	
	// Create a heap manager for my test heap.
	HeapManager * pHeapManager = HeapManager::create( pHeapMemory, sizeHeap, numDescriptors );
	assert( pHeapManager );
	
	if( pHeapManager == NULL )
		return false;
	
	std::vector<void *> AllocatedAddresses;
	
	bool done = false;
	
	// allocate memory of random sizes up to 1024 bytes from the heap manager
	// until it runs out of memory
	do
	{
		void * pPtr = pHeapManager->_alloc( rand() & 1023 ); // max allocation = 1024;

		if( pPtr)
			AllocatedAddresses.push_back( pPtr );
		else
			done = true;

	} while( !done );
	
	// now free those blocks in a random order
	if( !AllocatedAddresses.empty() )
	{
		// randomize the addresses
		std::random_shuffle( AllocatedAddresses.begin(), AllocatedAddresses.end() );
		
		// return them back to the heap manager
		while( !AllocatedAddresses.empty() )
		{
			void * pPtr = AllocatedAddresses.pop_back();
			pHeapManager->_free( pPtr );
		}
		
		// do garbage collection
		pHeapManager->collect();
		// our heap should be one single block, all the memory it started with
		
		// do a large test allocation to see if garbage collection worked
		void * pPtr = pHeapManager->_alloc( sizeHeap / 2 );
		assert( pPtr );
		
		if( pPtr )
		{
			pHeapManager->_free( pPtr );
			delete pHeapManager;
			
			_aligned_free( pHeapMemory );
			
			// we succeeded
			return true;
		}
	}

	// something caused a failure
	return false;
}