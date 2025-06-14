// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>
#include <assert.h>

#include "spvm_native.h"

#include "spvm_api.h"
#include "spvm_api_type.h"

SPVM_API_TYPE* SPVM_API_TYPE_new_api() {
  
  void* native_apis_init[]  = {
    SPVM_API_can_assign,
    SPVM_API_get_type_width,
    SPVM_API_is_object_type,
    SPVM_API_is_any_object_type,
    SPVM_API_is_object_array_type,
    SPVM_API_is_any_object_array_type,
    SPVM_API_is_numeric_type,
    SPVM_API_is_class_type,
  };
  
  SPVM_API_TYPE* native_apis = calloc(1, sizeof(native_apis_init));
  
  memcpy(native_apis, native_apis_init, sizeof(native_apis_init));
  
  return native_apis;
}

void SPVM_API_TYPE_free_api(SPVM_API_TYPE* api) {
  
  free(api);
}

