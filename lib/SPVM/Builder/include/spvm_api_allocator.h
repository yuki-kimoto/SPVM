#ifndef SPVM_API_ALLOCATOR_H
#define SPVM_API_ALLOCATOR_H

#include "spvm_typedecl.h"
#include "spvm_native.h"


SPVM_ENV_ALLOCATOR* SPVM_API_ALLOCATOR_new_env_raw();
SPVM_ENV_ALLOCATOR* SPVM_API_ALLOCATOR_new();
void SPVM_API_ALLOCATOR_free(SPVM_ENV_ALLOCATOR* env_allocator);

#endif
