// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_API_MUTEX_H
#define SPVM_API_MUTEX_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_API_MUTEX* SPVM_API_MUTEX_new_api();

void SPVM_API_MUTEX_free_api(SPVM_API_MUTEX* api);

SPVM_MUTEX* SPVM_API_MUTEX_new_instance(SPVM_ENV* env, SPVM_VALUE* stack);

void SPVM_API_MUTEX_free_instance(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_MUTEX* mutex);

void SPVM_API_MUTEX_lock(SPVM_ENV* env, SPVM_VALUE* stack, void* mutex);

void SPVM_API_MUTEX_unlock(SPVM_ENV* env, SPVM_VALUE* stack, void* mutex);

void SPVM_API_MUTEX_reader_lock(SPVM_ENV* env, SPVM_VALUE* stack, void* mutex);

void SPVM_API_MUTEX_reader_unlock(SPVM_ENV* env, SPVM_VALUE* stack, void* mutex);

#endif
