// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>

#include "spvm_native.h"

#include "spvm_api_cfunc.h"
#include "spvm_api.h"

SPVM_API_CFUNC* SPVM_API_CFUNC_new_api() {
  
  void* env_cfunc_init[]  = {
    SPVM_API_c_strlen,
    SPVM_API_c_memcpy,
    SPVM_API_c_memset,
    SPVM_API_c_memcmp,
    SPVM_API_c_strtoll,
    SPVM_API_c_strtof,
    SPVM_API_c_strtod,
    SPVM_API_c_fputs,
    SPVM_API_c_fgetc,
    SPVM_API_c_snprintf_len,
  };
  SPVM_API_CFUNC* env_cfunc = calloc(1, sizeof(env_cfunc_init));
  memcpy(env_cfunc, env_cfunc_init, sizeof(env_cfunc_init));
  
  return env_cfunc;
}

void SPVM_API_CFUNC_free_api(SPVM_API_CFUNC* api) {
  free(api);
}

