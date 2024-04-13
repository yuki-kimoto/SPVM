// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>
#include <assert.h>

#include "spvm_native.h"

#include "spvm_api_type.h"
#include "spvm_api_basic_type.h"

#include "spvm_compiler.h"
#include "spvm_type.h"
#include "spvm_allocator.h"
#include "spvm_runtime.h"
#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_field.h"
#include "spvm_hash.h"
#include "spvm_mutex.h"

SPVM_API_TYPE* SPVM_API_TYPE_new_api() {
  
  void* native_apis_init[]  = {
    SPVM_API_TYPE_can_assign,
    SPVM_API_TYPE_get_type_width,
    SPVM_API_TYPE_is_object_type,
    SPVM_API_TYPE_is_any_object_type,
    SPVM_API_TYPE_is_object_array_type,
    SPVM_API_TYPE_is_any_object_array_type,
  };
  
  SPVM_API_TYPE* native_apis = calloc(1, sizeof(native_apis_init));
  
  memcpy(native_apis, native_apis_init, sizeof(native_apis_init));
  
  return native_apis;
}

void SPVM_API_TYPE_free_api(SPVM_API_TYPE* api) {
  
  free(api);
}

int32_t SPVM_API_TYPE_is_object_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t type_flag) {
  
  int32_t is_object_type;
  if (type_dimension == 0) {
    int32_t basic_type_category = basic_type->category;
    
    switch (basic_type_category) {
      case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_STRING:
      case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS:
      case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE:
      case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT:
      {
        is_object_type = 1;
        break;
      }
      default: {
        is_object_type = 0;
      }
    }
  }
  else if (type_dimension >= 1) {
    is_object_type = 1;
  }
  else {
    assert(0);
  }
  
  return is_object_type;
}

int32_t SPVM_API_TYPE_is_any_object_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t type_flag) {
  
  int32_t is_any_object_type;
  if (type_dimension == 0) {
    int32_t basic_type_category = basic_type->category;
    
    switch (basic_type_category) {
      case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT:
      {
        is_any_object_type = 1;
        break;
      }
      default: {
        is_any_object_type = 0;
      }
    }
  }
  else if (type_dimension >= 1) {
    is_any_object_type = 1;
  }
  else {
    assert(0);
  }
  
  return is_any_object_type;
}

int32_t SPVM_API_TYPE_is_object_array_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t type_flag) {
  
  if (type_dimension > 0) {
    if (SPVM_API_TYPE_is_object_type(runtime, basic_type, type_dimension - 1, type_flag)) {
      return 1;
    }
    else {
      return 0;
    }
  }
  else {
    return 0;
  }
}

int32_t SPVM_API_TYPE_is_any_object_array_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t type_flag) {
  
  int32_t is_any_object_array_type;
  if (type_dimension == 1) {
    int32_t basic_type_category = basic_type->category;
    
    switch (basic_type_category) {
      case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT:
      {
        is_any_object_array_type = 1;
        break;
      }
      default: {
        is_any_object_array_type = 0;
      }
    }
  }
  else {
    is_any_object_array_type = 0;
  }
  
  return is_any_object_array_type;
}

int32_t SPVM_API_TYPE_get_type_width(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t type_flag) {
  
  int32_t basic_type_category = basic_type->category;
  
  int32_t type_width = -1;
  if (basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM) {
    type_width = basic_type->fields_length;
  }
  else {
    type_width = 1;
  }
  
  return type_width;
}

int32_t SPVM_API_TYPE_can_assign(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* dist_basic_type, int32_t dist_type_dimension, int32_t dist_type_flag, SPVM_RUNTIME_BASIC_TYPE* src_basic_type, int32_t src_type_dimension, int32_t src_type_flag) {
  
  int32_t isa = 0;
  
  char assinability_key[256] = {0};
  snprintf(assinability_key, 255, "%d-%d-%d-%d-%d-%d", dist_basic_type->id, dist_type_dimension, dist_type_flag, src_basic_type->id, src_type_dimension, src_type_flag);
  
  SPVM_MUTEX* runtime_mutex = runtime->mutex;
  
  SPVM_MUTEX_reader_lock(runtime_mutex);
  
  int32_t can_assign = (intptr_t)SPVM_HASH_get(runtime->assignment_requirement_symtable, assinability_key, strlen(assinability_key));
  
  SPVM_MUTEX_reader_unlock(runtime_mutex);
  
  if (can_assign > 0) {
    isa = 1;
  }
  else if (can_assign < 0) {
    isa = 0;
  }
  else {
    
    SPVM_COMPILER* compiler = runtime->compiler;
    
    isa = SPVM_TYPE_satisfy_assignment_requirement_without_data_conversion(
      compiler,
      dist_basic_type->id, dist_type_dimension, 0,
      src_basic_type->id, src_type_dimension, 0,
      NULL
    );
    
    SPVM_MUTEX_lock(runtime_mutex);
    
    SPVM_HASH_set(runtime->assignment_requirement_symtable, assinability_key, strlen(assinability_key), (void*)(intptr_t)(isa ? 1 : -1));
    
    SPVM_MUTEX_unlock(runtime_mutex);
  }
  
  return isa;
}

