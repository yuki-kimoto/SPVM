#ifndef SPVM_UTIL_ALLOCATOR_H
#define SPVM_UTIL_ALLOCATOR_H

void* SPVM_UTIL_ALLOCATOR_safe_malloc(int64_t byte_size);

void* SPVM_UTIL_ALLOCATOR_safe_malloc_i32(int32_t count, int32_t size);
void* SPVM_UTIL_ALLOCATOR_safe_malloc_i32_zero(int32_t count, int32_t size);

#endif
