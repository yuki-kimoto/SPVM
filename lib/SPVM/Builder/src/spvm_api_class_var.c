// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>

#include "spvm_native.h"

#include "spvm_api_class_var.h"

#include "spvm_allocator.h"
#include "spvm_runtime_class_var.h"

SPVM_API_CLASS_VAR* SPVM_API_CLASS_new_api() {
  
  void* native_apis_init[]  = {
    NULL,
  };
  
  SPVM_API_CLASS_VAR* native_apis = calloc(1, sizeof(native_apis_init));
  
  memcpy(native_apis, native_apis_init, sizeof(native_apis_init));
  
  return native_apis;
}

void SPVM_API_CLASS_VAR_free_api(SPVM_API_CLASS_VAR* api) {
  
  free(api);
}
