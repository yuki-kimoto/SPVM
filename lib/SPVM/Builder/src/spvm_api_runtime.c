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
#include "spvm_runtime_basic_type.h"
#include "spvm_api_basic_type.h"































































SPVM_API_RUNTIME* SPVM_API_RUNTIME_new_api() {
  
  void* env_runtime_init[]  = {
    SPVM_API_RUNTIME_new_instance,
    SPVM_API_RUNTIME_free_instance,
    NULL, // reserved2
    NULL, // reserved3
    NULL, // reserved4
    NULL, // reserved5,
    NULL, // reserved6
    NULL, // reserved7,
    NULL, // reserved8,
    NULL, // reserved9
    NULL, // reserved10,
    NULL,
    NULL, // reserved12
    NULL,
    NULL, // reserved14
    NULL, // reserved15
    NULL, // reserve16
    NULL, // reserved17
    NULL, // reserved18
    NULL, // reserved19
    NULL, // reserved20
    NULL, // reserved21
    NULL, // reserved22
    NULL, // reserved23
    NULL, // reserved24
    NULL, // reserved25
    NULL, // reserved26
    NULL, // reserved27
    NULL, // reserved28
    NULL, // reserved29
    NULL, // reserved30
    NULL, // reserved31
    NULL,
    NULL, // reserved33,
    NULL,
    NULL, // reserved35
    NULL, // reserved36,
    NULL, // reserved37,
    NULL,
    NULL, // reserved39
    NULL, // reserved40
    NULL, // reserved41
    NULL, // reserved42
    NULL,
    NULL, // reserved44,
    NULL, // reserved45,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL, // reserved59
    NULL,
    NULL, // reserved 61
    NULL,
    NULL, // reserved63
    NULL, // reserved64
    NULL,
    NULL,
    NULL,
    NULL,
    NULL, // reserved69
    NULL, // reserved70
    (void*)(intptr_t)offsetof(SPVM_OBJECT, ref_count), // object_ref_count_offset
    NULL, // reserved72
    NULL, // reserved73
    NULL, // reserved74
    (void*)(intptr_t)offsetof(SPVM_OBJECT, length), // object_length_offset
    NULL, // reserved76
    NULL, // reserved77
    NULL, // reserved78
    NULL,
    NULL, // reserved80
    NULL,
    NULL, // reserved82
    SPVM_API_RUNTIME_is_object_type,
    NULL, // reserved84
    NULL, // reserved85
    SPVM_API_RUNTIME_can_assign,
    NULL,
    NULL,
    NULL,
    NULL, // reserved90
    NULL,
    NULL, // reserved92
    NULL,
    NULL, // reserved94
    NULL,
    NULL, // reserved96
    NULL, // reserved97
    NULL, // reserved98
    SPVM_API_RUNTIME_get_basic_types_length,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    SPVM_API_RUNTIME_get_basic_type_by_id,
    NULL,
    NULL,
    NULL, // reserved120,
    NULL, // reserved121
    NULL,
    NULL,
    NULL,
    NULL,
    NULL, // reserved126
    NULL,
    NULL, // reserved128,
    NULL,
    NULL,
    NULL,
    NULL,
    SPVM_API_RUNTIME_get_basic_type_by_name,
    NULL,
    SPVM_API_RUNTIME_build_precompile_module_source,
    SPVM_API_RUNTIME_build_precompile_method_source,
  };
  SPVM_API_RUNTIME* env_runtime = calloc(1, sizeof(env_runtime_init));
  memcpy(env_runtime, env_runtime_init, sizeof(env_runtime_init));
  
  return env_runtime;
}

void SPVM_API_RUNTIME_free_api(SPVM_API_RUNTIME* api) {
  free(api);
}

SPVM_RUNTIME* SPVM_API_RUNTIME_new_instance() {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_new();
  
  return runtime;
}

void SPVM_API_RUNTIME_free_instance(SPVM_RUNTIME* runtime) {
  
  SPVM_RUNTIME_free(runtime);
}

int32_t SPVM_API_RUNTIME_get_basic_types_length(SPVM_RUNTIME* runtime) {
  
  return runtime->basic_types_length;
}

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_basic_type_by_id(SPVM_RUNTIME* runtime, int32_t basic_type_id) {
  
  if (basic_type_id < 0) {
    return NULL;
  }
  
  if (basic_type_id >= runtime->basic_types_length) {
    return NULL;
  }
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];
  
  return basic_type;
}

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_basic_type_by_name(SPVM_RUNTIME* runtime, const char* basic_type_name) {

  SPVM_RUNTIME_BASIC_TYPE* basic_type = (SPVM_RUNTIME_BASIC_TYPE*)SPVM_HASH_get(runtime->basic_type_symtable, basic_type_name, strlen(basic_type_name));
  
  return basic_type;
}

int32_t SPVM_API_RUNTIME_get_basic_type_id(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return basic_type->id;
}

int32_t SPVM_API_RUNTIME_get_basic_type_category(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return basic_type->category;
}

const char* SPVM_API_RUNTIME_get_basic_type_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return  basic_type->name;
}

const char* SPVM_API_RUNTIME_get_basic_type_version_string(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return basic_type->version_string;
}

int32_t SPVM_API_RUNTIME_get_basic_type_is_pointer(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return basic_type->is_pointer;
}

int32_t SPVM_API_RUNTIME_get_basic_type_anon_basic_types_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return basic_type->anon_basic_types_length;
}

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_basic_type_anon_basic_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t anon_basic_type_index) {
  
  if (anon_basic_type_index < 0) {
    return NULL;
  }
  
  if (anon_basic_type_index >= basic_type->anon_basic_types_length) {
    return NULL;
  }
  
  SPVM_RUNTIME_BASIC_TYPE* anon_basic_type = &basic_type->anon_basic_types[anon_basic_type_index];
  
  return anon_basic_type;
}

int32_t SPVM_API_RUNTIME_get_basic_type_is_anon(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return basic_type->is_anon;
}

const char* SPVM_API_RUNTIME_get_basic_type_module_rel_file(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return basic_type->module_rel_file;
}

const char* SPVM_API_RUNTIME_get_basic_type_module_dir(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return basic_type->module_dir;
}

int32_t SPVM_API_RUNTIME_get_basic_type_fields_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return basic_type->fields_length;
}

int32_t SPVM_API_RUNTIME_get_basic_type_methods_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return basic_type->methods_length;
}

int32_t SPVM_API_RUNTIME_get_basic_type_class_vars_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return basic_type->class_vars_length;
}

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_basic_type_parent(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return basic_type->parent;
}

SPVM_RUNTIME_CLASS_VAR* SPVM_API_RUNTIME_get_class_var_by_index(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t class_var_index) {
  
  if (class_var_index < 0) {
    return NULL;
  }
  
  if (class_var_index >= basic_type->class_vars_length) {
    return NULL;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = &basic_type->class_vars[class_var_index];
  
  return class_var;
}

SPVM_RUNTIME_CLASS_VAR* SPVM_API_RUNTIME_get_class_var_by_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, const char* class_var_name) {
  
  SPVM_RUNTIME_CLASS_VAR* found_class_var = NULL;
  if (basic_type->class_vars_length > 0) {
    for (int32_t class_var_index = 0; class_var_index <  basic_type->class_vars_length; class_var_index++) {
      SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var_by_index(runtime, basic_type, class_var_index);
      const char* class_var_name_current = SPVM_API_RUNTIME_get_class_var_name(runtime, class_var);
      if (strcmp(class_var_name_current, class_var_name) == 0) {
        found_class_var = class_var;
        break;
      }
    }
  }
  
  return found_class_var;
}

int32_t SPVM_API_RUNTIME_get_class_var_index(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* class_var) {
  
  return class_var->index;
}

const char* SPVM_API_RUNTIME_get_class_var_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_CLASS_VAR* class_var) {
  
  return class_var->name;
}

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_class_var_current_basic_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_CLASS_VAR* class_var) {
  
  return class_var->current_basic_type;
}

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_class_var_basic_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_CLASS_VAR* class_var) {
  
  return class_var->basic_type;
}

int32_t SPVM_API_RUNTIME_get_class_var_type_dimension(SPVM_RUNTIME* runtime, SPVM_RUNTIME_CLASS_VAR* class_var) {
  
  return class_var->type_dimension;
}

int32_t SPVM_API_RUNTIME_get_class_var_type_flag(SPVM_RUNTIME* runtime, SPVM_RUNTIME_CLASS_VAR* class_var) {
  
  return class_var->type_flag;
}

SPVM_RUNTIME_ARG* SPVM_API_RUNTIME_get_arg_by_index(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method, int32_t arg_index) {
  
  if (arg_index < 0) {
    return NULL;
  }
  
  if (arg_index >= method->args_length) {
    return NULL;
  }
  
  SPVM_RUNTIME_ARG* arg = &method->args[arg_index];
  
  return arg;
}

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_arg_basic_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_ARG* arg) {
  
  return arg->basic_type;
}

int32_t SPVM_API_RUNTIME_get_arg_type_dimension(SPVM_RUNTIME* runtime, SPVM_RUNTIME_ARG* arg) {
  
  return arg->type_dimension;
}

int32_t SPVM_API_RUNTIME_get_arg_type_flag(SPVM_RUNTIME* runtime, SPVM_RUNTIME_ARG* arg) {
  
  return arg->type_flag;
}

void* SPVM_API_RUNTIME_get_native_method_address(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {

  return method->native_address;
}

void SPVM_API_RUNTIME_set_native_method_address(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method, void* address) {
  
  method->native_address = address;
}

void* SPVM_API_RUNTIME_get_precompile_method_address(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {

  return method->precompile_address;
}

void SPVM_API_RUNTIME_set_precompile_method_address(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method, void* address) {

  method->precompile_address = address;
}

int32_t SPVM_API_RUNTIME_is_object_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t flag) {
  
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

int32_t SPVM_API_RUNTIME_can_assign(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* dist_basic_type, int32_t dist_type_dimension, int32_t dist_type_flag, SPVM_RUNTIME_BASIC_TYPE* src_basic_type, int32_t src_type_dimension, int32_t src_type_flag) {
  
  int32_t isa = 0;
  
  int32_t dist_basic_type_category = dist_basic_type->category;
  int32_t src_basic_type_category = src_basic_type->category;
  
  if (dist_basic_type->id == src_basic_type->id && dist_type_dimension == src_type_dimension) {
    isa = 1;
  }
  else if (dist_type_dimension == 0 && dist_basic_type_category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT) {
    assert(src_type_dimension >= 0);
    isa = 1;
  }
  else if (dist_type_dimension == 1 && dist_basic_type_category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT) {
    if (src_type_dimension >= 1) {
      isa = 1;
    }
    else {
      isa = 0;
    }
  }
  else if (dist_type_dimension == src_type_dimension) {
    if (dist_basic_type_category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE) {
      isa = SPVM_API_BASIC_TYPE_has_interface(runtime, src_basic_type, dist_basic_type);
    }
    else if (dist_basic_type_category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS) {
      isa = SPVM_API_BASIC_TYPE_is_super_class(runtime, dist_basic_type, src_basic_type);
    }
    else {
      isa = 0;
    }
  }
  else {
    isa = 0;
  }
  
  return isa;
}

void SPVM_API_RUNTIME_build_precompile_module_source(SPVM_RUNTIME* runtime, SPVM_STRING_BUFFER* string_buffer, const char* module_name) {
  SPVM_PRECOMPILE* precompile = SPVM_PRECOMPILE_new(precompile);
  SPVM_PRECOMPILE_set_runtime(precompile, runtime);
  SPVM_PRECOMPILE_build_module_source(precompile, string_buffer, module_name);
  SPVM_PRECOMPILE_free(precompile);
}

void SPVM_API_RUNTIME_build_precompile_method_source(SPVM_RUNTIME* runtime, SPVM_STRING_BUFFER* string_buffer, const char* module_name, const char* method_name) {
  SPVM_PRECOMPILE* precompile = SPVM_PRECOMPILE_new(precompile);
  SPVM_PRECOMPILE_set_runtime(precompile, runtime);
  SPVM_PRECOMPILE_build_method_source(precompile, string_buffer, module_name, method_name);
  SPVM_PRECOMPILE_free(precompile);
}

