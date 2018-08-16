#ifndef SPVM_UTIL_ALLOCATOR_H
#define SPVM_UTIL_ALLOCATOR_H

void* SPVM_UTIL_ALLOCATOR_safe_malloc(size_t byte_size);
void* SPVM_UTIL_ALLOCATOR_safe_malloc_zero(size_t byte_size);

const char* SPVM_UTIL_ALLOCATOR_clone_string(const char* string);

#endif
