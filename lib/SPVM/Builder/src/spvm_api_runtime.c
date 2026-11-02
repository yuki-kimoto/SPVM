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
    NULL, // method_begin_cb
    NULL, // method_end_cb
    (void*)offsetof(SPVM_OBJECT, data), // object_data_offset
    (void*)offsetof(SPVM_OBJECT, length), // object_length_offset
    (void*)offsetof(SPVM_OBJECT, capacity), // object_capacity_offset
    (void*)SPVM_API_C_STACK_INDEX_CALL_DEPTH, // stack_index_call_depth
    (void*)SPVM_API_C_STACK_INDEX_CALLER_INFO_STACK, // stack_index_caller_info_stack
    (void*)SPVM_API_C_STACK_INDEX_CALLER_INFO_STACK_RECORD_SIZE, // stack_index_caller_info_stack_record_size
    SPVM_API_RUNTIME_enable_record_object,
    SPVM_API_RUNTIME_disable_record_object,
    SPVM_API_RUNTIME_get_mutex,
    SPVM_API_RUNTIME_get_field_by_abs_name,
    SPVM_API_RUNTIME_get_class_var_by_abs_name,
    SPVM_API_RUNTIME_get_method_by_abs_name,
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
  SPVM_PRECOMPILE_build_class_source(precompile, string_buffer, module_basic_type);
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

void SPVM_API_RUNTIME_enable_record_object(SPVM_RUNTIME* runtime) {
  
  runtime->record_object = 1;
}

void SPVM_API_RUNTIME_disable_record_object(SPVM_RUNTIME* runtime) {
  
  runtime->record_object = 0;
}

SPVM_MUTEX* SPVM_API_RUNTIME_get_mutex(SPVM_RUNTIME* runtime) {
  
  return runtime->mutex;
}

SPVM_RUNTIME_FIELD* SPVM_API_RUNTIME_get_field_by_abs_name(SPVM_RUNTIME* runtime, const char* field_abs_name) {
  const char* sharp = strchr(field_abs_name, '#');
  if (!sharp) {
    return NULL;
  }
  
  int32_t basic_type_name_length = sharp - field_abs_name;
  const char* field_name = sharp + 1;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = NULL;
  for (int32_t i = 0; i < runtime->basic_types_length; i++) {
    SPVM_RUNTIME_BASIC_TYPE* candidate = runtime->basic_types[i];
    if (strlen(candidate->name) == basic_type_name_length && strncmp(candidate->name, field_abs_name, basic_type_name_length) == 0) {
      basic_type = candidate;
      break;
    }
  }
  if (!basic_type) {
    return NULL;
  }
  
  SPVM_RUNTIME_FIELD* found_field = NULL;
  if (basic_type->fields_length > 0) {
    for (int32_t field_index = 0; field_index < basic_type->fields_length; field_index++) {
      SPVM_RUNTIME_FIELD* field = SPVM_API_BASIC_TYPE_get_field_by_index(runtime, basic_type, field_index);
      const char* field_name_current = field->name;
      if (strcmp(field_name_current, field_name) == 0) {
        found_field = field;
        break;
      }
    }
  }
  
  return found_field;
}

SPVM_RUNTIME_CLASS_VAR* SPVM_API_RUNTIME_get_class_var_by_abs_name(SPVM_RUNTIME* runtime, const char* class_var_abs_name) {
  const char* sharp = strchr(class_var_abs_name, '#');
  if (!sharp) {
    return NULL;
  }

  int32_t basic_type_name_length = sharp - class_var_abs_name;
  const char* class_var_name = sharp + 1;

  SPVM_RUNTIME_BASIC_TYPE* basic_type = NULL;
  for (int32_t i = 0; i < runtime->basic_types_length; i++) {
    SPVM_RUNTIME_BASIC_TYPE* candidate = runtime->basic_types[i];
    if (strlen(candidate->name) == basic_type_name_length && strncmp(candidate->name, class_var_abs_name, basic_type_name_length) == 0) {
      basic_type = candidate;
      break;
    }
  }
  if (!basic_type) {
    return NULL;
  }

  SPVM_RUNTIME_CLASS_VAR* found_class_var = NULL;
  if (basic_type->class_vars_length > 0) {
    for (int32_t class_var_index = 0; class_var_index < basic_type->class_vars_length; class_var_index++) {
      SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_BASIC_TYPE_get_class_var_by_index(runtime, basic_type, class_var_index);
      const char* class_var_name_current = class_var->name;
      if (strcmp(class_var_name_current, class_var_name) == 0) {
        found_class_var = class_var;
        break;
      }
    }
  }

  return found_class_var;
}

SPVM_RUNTIME_METHOD* SPVM_API_RUNTIME_get_method_by_abs_name(SPVM_RUNTIME* runtime, const char* method_abs_name) {
  const char* sharp = strchr(method_abs_name, '#');
  if (!sharp) {
    return NULL;
  }

  int32_t basic_type_name_length = sharp - method_abs_name;
  const char* method_name = sharp + 1;

  SPVM_RUNTIME_BASIC_TYPE* basic_type = NULL;
  for (int32_t i = 0; i < runtime->basic_types_length; i++) {
    SPVM_RUNTIME_BASIC_TYPE* candidate = runtime->basic_types[i];
    if (strlen(candidate->name) == basic_type_name_length && strncmp(candidate->name, method_abs_name, basic_type_name_length) == 0) {
      basic_type = candidate;
      break;
    }
  }
  if (!basic_type) {
    return NULL;
  }

  SPVM_RUNTIME_METHOD* found_method = NULL;
  if (basic_type->methods_length > 0) {
    for (int32_t method_index = 0; method_index < basic_type->methods_length; method_index++) {
      SPVM_RUNTIME_METHOD* method = SPVM_API_BASIC_TYPE_get_method_by_index(runtime, basic_type, method_index);
      const char* method_name_current = method->name;
      if (strcmp(method_name_current, method_name) == 0) {
        found_method = method;
        break;
      }
    }
  }

  return found_method;
}
