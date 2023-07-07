// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_API_ALLOCATOR_H
#define SPVM_API_ALLOCATOR_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_API_ALLOCATOR* SPVM_API_ALLOCATOR_new_api();

SPVM_ALLOCATOR* SPVM_API_ALLOCATOR_new_instance();
void SPVM_API_ALLOCATOR_free_instance(SPVM_ALLOCATOR* allocator);

void SPVM_API_ALLOCATOR_free_api(SPVM_API_ALLOCATOR* api);

#endif
