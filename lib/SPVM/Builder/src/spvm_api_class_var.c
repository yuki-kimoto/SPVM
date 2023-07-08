// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>

#include "spvm_native.h"

#include "spvm_api_class_var.h"

#include "spvm_allocator.h"
#include "spvm_runtime_class_var.h"

SPVM_API_CLASS_VAR* SPVM_API_CLASS_VAR_new_api() {
  
  void* native_apis_init[]  = {
    SPVM_API_CLASS_VAR_get_name,
    SPVM_API_CLASS_VAR_get_current_basic_type,
    SPVM_API_CLASS_VAR_get_basic_type,
    SPVM_API_CLASS_VAR_get_type_dimension,
    SPVM_API_CLASS_VAR_get_type_flag,
  };
  
  SPVM_API_CLASS_VAR* native_apis = calloc(1, sizeof(native_apis_init));
  
  memcpy(native_apis, native_apis_init, sizeof(native_apis_init));
  
  return native_apis;
}

void SPVM_API_CLASS_VAR_free_api(SPVM_API_CLASS_VAR* api) {
  
  free(api);
}

const char* SPVM_API_CLASS_VAR_get_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_CLASS_VAR* class_var) {
  
  return class_var->name;
}

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_CLASS_VAR_get_current_basic_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_CLASS_VAR* class_var) {
  
  return class_var->current_basic_type;
}

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_CLASS_VAR_get_basic_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_CLASS_VAR* class_var) {
  
  return class_var->basic_type;
}

int32_t SPVM_API_CLASS_VAR_get_type_dimension(SPVM_RUNTIME* runtime, SPVM_RUNTIME_CLASS_VAR* class_var) {
  
  return class_var->type_dimension;
}

int32_t SPVM_API_CLASS_VAR_get_type_flag(SPVM_RUNTIME* runtime, SPVM_RUNTIME_CLASS_VAR* class_var) {
  
  return class_var->type_flag;
}
