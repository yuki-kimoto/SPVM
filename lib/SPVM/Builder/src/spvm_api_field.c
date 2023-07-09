// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>

#include "spvm_native.h"

#include "spvm_api_field.h"

#include "spvm_allocator.h"
#include "spvm_runtime_field.h"

SPVM_API_FIELD* SPVM_API_FIELD_new_api() {
  
  void* native_apis_init[]  = {
    SPVM_API_FIELD_get_name,
    SPVM_API_FIELD_get_index,
    SPVM_API_FIELD_get_offset,
    SPVM_API_FIELD_get_basic_type,
    SPVM_API_FIELD_get_type_dimension,
    SPVM_API_FIELD_get_type_flag,
    SPVM_API_FIELD_get_current_basic_type,
  };
  
  SPVM_API_FIELD* native_apis = calloc(1, sizeof(native_apis_init));
  
  memcpy(native_apis, native_apis_init, sizeof(native_apis_init));
  
  return native_apis;
}

void SPVM_API_FIELD_free_api(SPVM_API_FIELD* api) {
  
  free(api);
}

const char* SPVM_API_FIELD_get_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_FIELD* field) {
  
  return field->name;
}

int32_t SPVM_API_FIELD_get_index(SPVM_RUNTIME* runtime, SPVM_RUNTIME_FIELD* field) {
  
  return field->index;
}

int32_t SPVM_API_FIELD_get_offset(SPVM_RUNTIME* runtime, SPVM_RUNTIME_FIELD* field) {
  
  return field->offset;
}

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_FIELD_get_basic_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_FIELD* field) {
  
  return field->basic_type;
}

int32_t SPVM_API_FIELD_get_type_dimension(SPVM_RUNTIME* runtime, SPVM_RUNTIME_FIELD* field) {
  
  return field->type_dimension;
}

int32_t SPVM_API_FIELD_get_type_flag(SPVM_RUNTIME* runtime, SPVM_RUNTIME_FIELD* field) {
  
  return  field->type_flag;
}

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_FIELD_get_current_basic_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_FIELD* field) {
  
  return field->current_basic_type;
}
