#include <performance!/memory_test.h>
#include <performance!/profiler.h>

#include <stdlib.h>
#include <stdio.h>

#define REAL_TOTAL_MEM_SIZE Gigabyte(8) // <---- total amount of ram used on the computer as nothing here is freed
#define TOTAL_MEM_SIZE      (REAL_TOTAL_MEM_SIZE / 2) // <---- total amount of memory used per test (there are 2)
#define SEGMENT_MEM_SIZE    Kilobyte(1024) // <---- what size chunks we are requesting allocations in
#define NUM_SEGMENTS        (TOTAL_MEM_SIZE / SEGMENT_MEM_SIZE) // <--- how many chunks fills our total mem size

internal void normal_malloc_test();
internal void better_malloc_test();

void memory_test() {
	normal_malloc_test();
	better_malloc_test();
}

internal void normal_malloc_test() {
	u64 start_time = get_system_milliseconds();

	for (int i = 0; i < NUM_SEGMENTS; i++) {
		void* alloc = malloc(SEGMENT_MEM_SIZE);
	}

	u64 end_time = get_system_milliseconds();
	printf("Malloc Test took %llu ms \n", end_time - start_time);
}

typedef struct Memory_Block {
	u8* base_pointer;
	u64 size;
	u64 total_used;
} Memory_Block;

bool memory_block_initialize(u64 size, Memory_Block* out_block) {
	if (!out_block) return false;

	u8* alloc = (u8*)malloc(size); 
	if (!alloc) return false;

	out_block->base_pointer = alloc;
	out_block->size		    = size;
	out_block->total_used   = 0;

	return true;
}

void* memory_block_allocate(Memory_Block* block, u64 size) {
	if (!block || !block->base_pointer || block->size <= 0) return 0;

	if (block->total_used + size > block->size) return 0;

	void* alloc = (void*)(block->base_pointer + block->total_used);
	block->total_used += size;

	return alloc;
}

#define memory_block_allocate_type(block, type) (type*)memory_block_allocate(block, sizeof(type))

internal void better_malloc_test() {
	// This step would be assumed to have been performed at application startup 
	// and not during runtime. As this is a test of "Runtime Allocation Speed" it is fair
	// that the timer for this function begins AFTER the initialization. 
	Memory_Block block;
	if (!memory_block_initialize(TOTAL_MEM_SIZE, &block)) return;

	u64 start_time = get_system_milliseconds();

	for (int i = 0; i < NUM_SEGMENTS; i++) {
		void* alloc = memory_block_allocate(&block, SEGMENT_MEM_SIZE);
	}

	u64 end_time = get_system_milliseconds();
	printf("Better malloc Test took %llu ms \n", end_time - start_time);
}