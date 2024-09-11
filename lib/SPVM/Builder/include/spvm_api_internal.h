// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_API_INTERNAL_H
#define SPVM_API_INTERNAL_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_API_INTERNAL* SPVM_API_INTERNAL_new_api();

void SPVM_API_INTERNAL_free_api(SPVM_API_INTERNAL* internal);

int32_t SPVM_API_INTERNAL_get_ref_count(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);

void SPVM_API_INTERNAL_inc_ref_count(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);

void SPVM_API_INTERNAL_dec_ref_count(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);

void SPVM_API_INTERNAL_leave_scope_local(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT** object_vars, int32_t* mortal_stack, int32_t* mortal_stack_top_ptr, int32_t original_mortal_stack_top);

void SPVM_API_INTERNAL_lock_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);

void SPVM_API_INTERNAL_unlock_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);

char* SPVM_API_INTERNAL_get_stack_tmp_buffer(SPVM_ENV* env, SPVM_VALUE* stack);

#endif
