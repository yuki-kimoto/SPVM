// Copyright & License
// Copyright 2023 Yuki Kimoto. All Rights Reserved.
// MIT License.

#ifndef SPVM_API_ALLOCATOR_H
#define SPVM_API_ALLOCATOR_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_ENV_ALLOCATOR* SPVM_API_ALLOCATOR_new_env();

SPVM_ALLOCATOR* SPVM_API_ALLOCATOR_new_object();
void SPVM_API_ALLOCATOR_free_object(SPVM_ALLOCATOR* allocator);

#endif
