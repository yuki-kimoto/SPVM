#ifndef SPVM_RUNTIME_ALLOCATOR_H
#define SPVM_RUNTIME_ALLOCATOR_H

#include "spvm_base.h"

void* SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(SPVM_RUNTIME* runtime, int32_t byte_size);
void SPVM_RUNTIME_ALLOCATOR_free_memory_block(SPVM_RUNTIME* runtime, void* block);

#endif
