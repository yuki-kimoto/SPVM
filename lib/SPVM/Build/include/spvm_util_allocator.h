#ifndef SPVM_UTIL_ALLOCATOR_H
#define SPVM_UTIL_ALLOCATOR_H

void* SPVM_UTIL_ALLOCATOR_safe_malloc(int64_t byte_size);
void* SPVM_UTIL_ALLOCATOR_safe_malloc_zero(int64_t byte_size);

#endif
