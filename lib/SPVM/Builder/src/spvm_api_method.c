// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>

#include "spvm_native.h"

#include "spvm_api_method.h"

#include "spvm_allocator.h"
#include "spvm_runtime_method.h"
#include "spvm_api_method.h"

SPVM_API_METHOD* SPVM_API_METHOD_new_api() {
  
  void* native_apis_init[]  = {
    NULL,
  };
  
  SPVM_API_METHOD* native_apis = calloc(1, sizeof(native_apis_init));
  
  memcpy(native_apis, native_apis_init, sizeof(native_apis_init));
  
  return native_apis;
}

void SPVM_API_METHOD_free_api(SPVM_API_METHOD* api) {
  
  free(api);
}
