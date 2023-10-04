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

void* SPVM_API_new_mutex(SPVM_ENV* env, SPVM_VALUE* stack);

void SPVM_API_free_mutex(SPVM_ENV* env, SPVM_VALUE* stack, void* mutex);

int32_t SPVM_API_lock(SPVM_ENV* env, SPVM_VALUE* stack, void* mutex);

int32_t SPVM_API_unlock(SPVM_ENV* env, SPVM_VALUE* stack, void* mutex);

int32_t SPVM_API_reader_lock(SPVM_ENV* env, SPVM_VALUE* stack, void* mutex);

int32_t SPVM_API_reader_unlock(SPVM_ENV* env, SPVM_VALUE* stack, void* mutex);


#endif
