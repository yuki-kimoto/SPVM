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
    SPVM_API_TYPE_is_numeric_type,
    SPVM_API_TYPE_is_class_type,
  };
  
  SPVM_API_TYPE* native_apis = calloc(1, sizeof(native_apis_init));
  
  memcpy(native_apis, native_apis_init, sizeof(native_apis_init));
  
  return native_apis;
}

void SPVM_API_TYPE_free_api(SPVM_API_TYPE* api) {
  
  free(api);
}

int32_t SPVM_API_TYPE_is_object_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t type_flag) {
  
  SPVM_COMPILER* compiler = runtime->compiler;
  
  int32_t is_object_type = SPVM_TYPE_is_object_type(compiler, basic_type->id, type_dimension, type_flag);
  
  return is_object_type;
}

int32_t SPVM_API_TYPE_is_any_object_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t type_flag) {
  
  SPVM_COMPILER* compiler = runtime->compiler;
  
  int32_t is_any_object_type = SPVM_TYPE_is_any_object_type(compiler, basic_type->id, type_dimension, type_flag);
  
  return is_any_object_type;
}

int32_t SPVM_API_TYPE_is_object_array_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t type_flag) {
  
  SPVM_COMPILER* compiler = runtime->compiler;
  
  int32_t is_object_array_type = SPVM_TYPE_is_object_array_type(compiler, basic_type->id, type_dimension, type_flag);
  
  return is_object_array_type;
}

int32_t SPVM_API_TYPE_is_any_object_array_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t type_flag) {
  
  SPVM_COMPILER* compiler = runtime->compiler;
  
  int32_t is_any_object_array_type = SPVM_TYPE_is_any_object_array_type(compiler, basic_type->id, type_dimension, type_flag);
  
  return is_any_object_array_type;
}

int32_t SPVM_API_TYPE_get_type_width(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t type_flag) {
  
  SPVM_COMPILER* compiler = runtime->compiler;
  
  int32_t type_width = SPVM_TYPE_get_type_width(compiler, basic_type->id, type_dimension, type_flag);
  
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

int32_t SPVM_API_TYPE_is_numeric_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t type_flag) {
  
  SPVM_COMPILER* compiler = runtime->compiler;
  
  int32_t is_numeric_type = SPVM_TYPE_is_numeric_type(compiler, basic_type->id, type_dimension, type_flag);
  
  return is_numeric_type;
}

int32_t SPVM_API_TYPE_is_class_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t type_flag) {
  
  SPVM_COMPILER* compiler = runtime->compiler;
  
  int32_t is_class_type = SPVM_TYPE_is_class_type(compiler, basic_type->id, type_dimension, type_flag);
  
  return is_class_type;
}

