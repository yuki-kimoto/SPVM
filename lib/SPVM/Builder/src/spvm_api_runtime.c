// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <inttypes.h>
#include <stdarg.h>

#include "spvm_native.h"

#include "spvm_type.h"
#include "spvm_method.h"

#include "spvm_list.h"
#include "spvm_hash.h"

#include "spvm_object.h"
#include "spvm_opcode.h"
#include "spvm_runtime_basic_type.h"

#include "spvm_runtime_class_var.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime.h"
#include "spvm_runtime_method.h"
#include "spvm_runtime_string.h"
#include "spvm_api_runtime.h"
#include "spvm_runtime_arg.h"
#include "spvm_precompile.h"
#include "spvm_api.h"
#include "spvm_type.h"
#include "spvm_runtime_basic_type.h"
#include "spvm_api_basic_type.h"
#include "spvm_mutex.h"
#include "spvm_compiler.h"


























































SPVM_API_RUNTIME* SPVM_API_RUNTIME_new_api() {
  
  void* env_runtime_init[]  = {
    SPVM_API_RUNTIME_get_object_data_offset,
    SPVM_API_RUNTIME_get_object_ref_count_offset,
    SPVM_API_RUNTIME_get_object_length_offset,
    SPVM_API_RUNTIME_get_basic_type_by_id,
    SPVM_API_RUNTIME_get_basic_type_by_name,
    SPVM_API_RUNTIME_get_basic_types_length,
    SPVM_API_RUNTIME_build_precompile_class_source,
    SPVM_API_RUNTIME_build_precompile_method_source,
    SPVM_API_RUNTIME_get_compiler,
    SPVM_API_RUNTIME_set_compiler,
    SPVM_API_RUNTIME_get_spvm_stdin,
    SPVM_API_RUNTIME_get_spvm_stdout,
    SPVM_API_RUNTIME_get_spvm_stderr,
    SPVM_API_RUNTIME_get_env,
    SPVM_API_RUNTIME_get_object_capacity_offset,
  };
  SPVM_API_RUNTIME* env_runtime = calloc(1, sizeof(env_runtime_init));
  memcpy(env_runtime, env_runtime_init, sizeof(env_runtime_init));
  
  return env_runtime;
}

void SPVM_API_RUNTIME_free_api(SPVM_API_RUNTIME* api) {
  free(api);
}

int32_t SPVM_API_RUNTIME_get_object_data_offset(SPVM_RUNTIME* runtime) {
  return offsetof(SPVM_OBJECT, data);
}

int32_t SPVM_API_RUNTIME_get_object_ref_count_offset(SPVM_RUNTIME* runtime) {
  
  return offsetof(SPVM_OBJECT, ref_count);
}

int32_t SPVM_API_RUNTIME_get_object_length_offset(SPVM_RUNTIME* runtime) {
  
  return offsetof(SPVM_OBJECT, length);
}

int32_t SPVM_API_RUNTIME_get_object_capacity_offset(SPVM_RUNTIME* runtime) {
  
  return offsetof(SPVM_OBJECT, capacity);
}

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_basic_type_by_id(SPVM_RUNTIME* runtime, int32_t basic_type_id) {
  
  if (basic_type_id < 0) {
    return NULL;
  }
  
  if (basic_type_id >= runtime->basic_types_length) {
    return NULL;
  }
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = runtime->basic_types[basic_type_id];
  
  assert(basic_type);
  
  return basic_type;
}

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_basic_type_by_name(SPVM_RUNTIME* runtime, const char* basic_type_name) {

  SPVM_RUNTIME_BASIC_TYPE* basic_type = (SPVM_RUNTIME_BASIC_TYPE*)SPVM_HASH_get(runtime->basic_type_symtable, basic_type_name, strlen(basic_type_name));
  
  return basic_type;
}

int32_t SPVM_API_RUNTIME_get_basic_types_length(SPVM_RUNTIME* runtime) {
  
  return runtime->basic_types_length;
}

int32_t SPVM_API_RUNTIME_is_any_object_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t flag) {
  
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

int32_t SPVM_API_RUNTIME_is_object_array_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t dimension, int32_t flag) {
  
  if (dimension > 0) {
    if (SPVM_TYPE_is_object_type(runtime->compiler, basic_type->id, dimension - 1, flag)) {
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

int32_t SPVM_API_RUNTIME_is_any_object_array_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t flag) {
  
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

void SPVM_API_RUNTIME_build_precompile_class_source(SPVM_RUNTIME* runtime, SPVM_STRING_BUFFER* string_buffer, SPVM_RUNTIME_BASIC_TYPE* module_basic_type) {
  SPVM_PRECOMPILE* precompile = SPVM_PRECOMPILE_new();
  SPVM_PRECOMPILE_set_runtime(precompile, runtime);
  SPVM_PRECOMPILE_build_module_source(precompile, string_buffer, module_basic_type);
  SPVM_PRECOMPILE_free(precompile);
}

void SPVM_API_RUNTIME_build_precompile_method_source(SPVM_RUNTIME* runtime, SPVM_STRING_BUFFER* string_buffer, SPVM_RUNTIME_METHOD* method) {
  SPVM_PRECOMPILE* precompile = SPVM_PRECOMPILE_new();
  SPVM_PRECOMPILE_set_runtime(precompile, runtime);
  SPVM_PRECOMPILE_build_method_source(precompile, string_buffer, method->current_basic_type, method);
  SPVM_PRECOMPILE_free(precompile);
}

SPVM_COMPILER* SPVM_API_RUNTIME_get_compiler(SPVM_RUNTIME* runtime) {
  
  return runtime->compiler;
}

void SPVM_API_RUNTIME_set_compiler(SPVM_RUNTIME* runtime, SPVM_COMPILER* compiler) {
  
  runtime->compiler = compiler;
}

FILE* SPVM_API_RUNTIME_get_spvm_stdin(SPVM_RUNTIME* runtime) {
  
  return runtime->spvm_stdin;
}

FILE* SPVM_API_RUNTIME_get_spvm_stdout(SPVM_RUNTIME* runtime) {
  
  return runtime->spvm_stdout;
}

FILE* SPVM_API_RUNTIME_get_spvm_stderr(SPVM_RUNTIME* runtime) {
  
  return runtime->spvm_stderr;
}

SPVM_ENV* SPVM_API_RUNTIME_get_env(SPVM_RUNTIME* runtime) {
  
  return runtime->env;
}

