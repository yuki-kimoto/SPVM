// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>

#include "spvm_native.h"

#include "spvm_api_internal.h"
#include "spvm_api.h"

SPVM_API_INTERNAL* SPVM_API_INTERNAL_new_api() {
  
  // Env Allocator
  void* env_internal_init[]  = {
    SPVM_API_get_ref_count,
    SPVM_API_inc_ref_count,
    SPVM_API_dec_ref_count,
    SPVM_API_get_stack_tmp_buffer,
    SPVM_API_leave_scope_local,
  };
  SPVM_API_INTERNAL* env_internal = calloc(1, sizeof(env_internal_init));
  memcpy(env_internal, env_internal_init, sizeof(env_internal_init));
  
  return env_internal;
}

void SPVM_API_INTERNAL_free_api(SPVM_API_INTERNAL* api) {
  free(api);
}

