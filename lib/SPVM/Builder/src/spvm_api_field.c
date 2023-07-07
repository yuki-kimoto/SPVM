// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>

#include "spvm_native.h"

#include "spvm_api_field.h"

#include "spvm_allocator.h"
#include "spvm_runtime_field.h"

SPVM_API_FIELD* SPVM_API_FIELD_new_api() {
  
  void* native_apis_init[]  = {
    NULL,
  };
  
  SPVM_API_FIELD* native_apis = calloc(1, sizeof(native_apis_init));
  
  memcpy(native_apis, native_apis_init, sizeof(native_apis_init));
  
  return native_apis;
}

void SPVM_API_FIELD_free_api(SPVM_API_FIELD* api) {
  
  free(api);
}
