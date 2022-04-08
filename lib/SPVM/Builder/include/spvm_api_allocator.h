#ifndef SPVM_API_ALLOCATOR_H
#define SPVM_API_ALLOCATOR_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_ALLOCATOR* SPVM_API_ALLOCATOR_new_allocator();
void SPVM_API_ALLOCATOR_free_allocator(SPVM_ALLOCATOR* allocator);

#endif
