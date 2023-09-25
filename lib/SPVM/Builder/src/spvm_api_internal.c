// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>

#include "spvm_native.h"

#include "spvm_api_internal.h"
#include "spvm_api.h"

SPVM_API_INTERNAL* SPVM_API_INTERNAL_new_api() {
  
  // Env Allocator
  void* env_internal_init[]  = {
    SPVM_API_INTERNAL_get_ref_count,
    SPVM_API_INTERNAL_inc_ref_count,
    SPVM_API_INTERNAL_dec_ref_count,
    SPVM_API_INTERNAL_leave_scope_local,
    SPVM_API_INTERNAL_lock_object,
    SPVM_API_INTERNAL_unlock_object,
  };
  SPVM_API_INTERNAL* env_internal = calloc(1, sizeof(env_internal_init));
  memcpy(env_internal, env_internal_init, sizeof(env_internal_init));
  
  return env_internal;
}

void SPVM_API_INTERNAL_free_api(SPVM_API_INTERNAL* api) {
  free(api);
}

int32_t SPVM_API_INTERNAL_get_ref_count(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  return SPVM_API_get_ref_count(env, stack, object);
}

void SPVM_API_INTERNAL_inc_ref_count(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  SPVM_API_inc_ref_count(env, stack, object);
}

void SPVM_API_INTERNAL_dec_ref_count(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  SPVM_API_dec_ref_count(env, stack, object);
}

void SPVM_API_INTERNAL_leave_scope_local(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT** object_vars, int32_t* mortal_stack, int32_t* mortal_stack_top_ptr, int32_t original_mortal_stack_top) {
  
  SPVM_API_leave_scope_local(env, stack, object_vars, mortal_stack, mortal_stack_top_ptr, original_mortal_stack_top);
}

void SPVM_API_INTERNAL_lock_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  SPVM_API_lock_object(env, stack, object);
}

void SPVM_API_INTERNAL_unlock_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  SPVM_API_unlock_object(env, stack, object);
}
