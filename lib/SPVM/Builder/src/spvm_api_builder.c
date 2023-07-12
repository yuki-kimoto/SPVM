// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>

#include "spvm_native.h"

#include "spvm_api_builder.h"

#include "spvm_allocator.h"

SPVM_API_BUILDER* SPVM_API_BUILDER_new_api() {
  
  void* native_apis_init[]  = {
    SPVM_API_BUILDER_new_env,
    SPVM_API_BUILDER_free_env,
    SPVM_API_BUILDER_call_init_methods,
    SPVM_API_BUILDER_set_command_info_program_name,
    SPVM_API_BUILDER_set_command_info_argv,
    SPVM_API_BUILDER_set_command_info_base_time,
    SPVM_API_BUILDER_destroy_class_vars,
  };
  
  SPVM_API_BUILDER* native_apis = calloc(1, sizeof(native_apis_init));
  
  memcpy(native_apis, native_apis_init, sizeof(native_apis_init));
  
  return native_apis;
}

void SPVM_API_BUILDER_free_api(SPVM_API_BUILDER* api) {
  
  free(api);
}

