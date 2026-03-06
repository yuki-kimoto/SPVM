// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>

#include "spvm_native.h"

#include "spvm_api_arg.h"

#include "spvm_allocator.h"
#include "spvm_runtime_arg.h"

SPVM_API_ARG* SPVM_API_ARG_new_api() {
  
  void* native_apis_init[]  = {
    SPVM_API_ARG_get_name,
    SPVM_API_ARG_get_index,
    SPVM_API_ARG_get_basic_type,
    SPVM_API_ARG_get_type_dimension,
    SPVM_API_ARG_get_type_flag,
    SPVM_API_ARG_get_stack_index,
    SPVM_API_ARG_get_current_method,
    SPVM_API_ARG_is_optional,
    SPVM_API_ARG_get_default_value,
  };
  
  SPVM_API_ARG* native_apis = calloc(1, sizeof(native_apis_init));
  
  memcpy(native_apis, native_apis_init, sizeof(native_apis_init));
  
  return native_apis;
}

void SPVM_API_ARG_free_api(SPVM_API_ARG* api) {
  
  free(api);
}

const char* SPVM_API_ARG_get_name(SPVM_NATIVE_RUNTIME* runtime, SPVM_NATIVE_ARG* arg) {
  
  return ((SPVM_RUNTIME_ARG*)arg)->name;
}

int32_t SPVM_API_ARG_get_index(SPVM_NATIVE_RUNTIME* runtime, SPVM_NATIVE_ARG* arg) {
  
  return ((SPVM_RUNTIME_ARG*)arg)->index;
}

SPVM_NATIVE_BASIC_TYPE* SPVM_API_ARG_get_basic_type(SPVM_NATIVE_RUNTIME* runtime, SPVM_NATIVE_ARG* arg) {
  
  return (SPVM_NATIVE_BASIC_TYPE*)((SPVM_RUNTIME_ARG*)arg)->basic_type;
}

int32_t SPVM_API_ARG_get_type_dimension(SPVM_NATIVE_RUNTIME* runtime, SPVM_NATIVE_ARG* arg) {
  
  return ((SPVM_RUNTIME_ARG*)arg)->type_dimension;
}

int32_t SPVM_API_ARG_get_type_flag(SPVM_NATIVE_RUNTIME* runtime, SPVM_NATIVE_ARG* arg) {
  
  return ((SPVM_RUNTIME_ARG*)arg)->type_flag;
}

int32_t SPVM_API_ARG_get_stack_index(SPVM_NATIVE_RUNTIME* runtime, SPVM_NATIVE_ARG* arg) {
  
  return ((SPVM_RUNTIME_ARG*)arg)->stack_index;
}

SPVM_NATIVE_METHOD* SPVM_API_ARG_get_current_method(SPVM_NATIVE_RUNTIME* runtime, SPVM_NATIVE_ARG* arg) {
  
  return (SPVM_NATIVE_METHOD*)((SPVM_RUNTIME_ARG*)arg)->current_method;
}

int32_t SPVM_API_ARG_is_optional(SPVM_NATIVE_RUNTIME* runtime, SPVM_NATIVE_ARG* arg) {
  
  return ((SPVM_RUNTIME_ARG*)arg)->is_optional;
}

SPVM_VALUE SPVM_API_ARG_get_default_value(SPVM_NATIVE_RUNTIME* runtime, SPVM_NATIVE_ARG* arg) {
  
  return ((SPVM_RUNTIME_ARG*)arg)->default_value;
}
