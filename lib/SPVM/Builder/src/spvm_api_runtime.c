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
#include "spvm_runtime_constant_string.h"
#include "spvm_api_runtime.h"
#include "spvm_runtime_arg.h"

































































SPVM_ENV_RUNTIME* SPVM_API_RUNTIME_new_env() {
  
  void* env_runtime_init[]  = {
    SPVM_API_RUNTIME_new_object,
    SPVM_API_RUNTIME_free_object,
    SPVM_API_RUNTIME_get_opcodes,
    SPVM_API_RUNTIME_get_opcodes_length,
    SPVM_API_RUNTIME_get_runtime_codes,
    SPVM_API_RUNTIME_get_runtime_codes_length,
    NULL, // reserved6
    SPVM_API_RUNTIME_get_constant_string_id,
    SPVM_API_RUNTIME_get_constant_string_value,
    SPVM_API_RUNTIME_get_name,
    SPVM_API_RUNTIME_get_basic_type_id_by_name,
    SPVM_API_RUNTIME_get_basic_type_name_id,
    NULL, // reserved12
    SPVM_API_RUNTIME_get_basic_type_category,
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
    SPVM_API_RUNTIME_get_class_var_id_by_index,
    SPVM_API_RUNTIME_get_class_var_id_by_name,
    SPVM_API_RUNTIME_get_class_var_name_id,
    NULL, // reserved35
    SPVM_API_RUNTIME_get_field_address_id_by_index,
    SPVM_API_RUNTIME_get_field_address_id_by_name,
    SPVM_API_RUNTIME_get_field_name_id,
    NULL, // reserved39
    NULL, // reserved40
    SPVM_API_RUNTIME_get_method_address_id_by_index,
    SPVM_API_RUNTIME_get_method_address_id_by_name,
    SPVM_API_RUNTIME_get_method_name_id,
    NULL, // reserved44,
    NULL, // reserved45,
    SPVM_API_RUNTIME_get_method_is_static,
    SPVM_API_RUNTIME_get_method_is_anon,
    SPVM_API_RUNTIME_get_method_is_native,
    SPVM_API_RUNTIME_get_method_is_precompile,
    SPVM_API_RUNTIME_get_method_call_stack_byte_vars_length,
    SPVM_API_RUNTIME_get_method_call_stack_short_vars_length,
    SPVM_API_RUNTIME_get_method_call_stack_int_vars_length,
    SPVM_API_RUNTIME_get_method_call_stack_long_vars_length,
    SPVM_API_RUNTIME_get_method_call_stack_float_vars_length,
    SPVM_API_RUNTIME_get_method_call_stack_double_vars_length,
    SPVM_API_RUNTIME_get_method_call_stack_object_vars_length,
    SPVM_API_RUNTIME_get_method_call_stack_ref_vars_length,
    SPVM_API_RUNTIME_get_method_mortal_stack_length,
    SPVM_API_RUNTIME_get_method_opcodes_base_address_id,
    SPVM_API_RUNTIME_get_method_opcodes_length,
    SPVM_API_RUNTIME_get_method_args_base_address_id,
    SPVM_API_RUNTIME_get_method_args_length,
    NULL, // reserved63
    NULL, // reserved64
    SPVM_API_RUNTIME_get_native_method_address,
    SPVM_API_RUNTIME_set_native_method_address,
    SPVM_API_RUNTIME_get_precompile_method_address,
    SPVM_API_RUNTIME_set_precompile_method_address,
    (void*)(intptr_t)sizeof(SPVM_OBJECT), // object_header_size
    (void*)(intptr_t)offsetof(SPVM_OBJECT, weaken_backref_head), // weaken_backref_head
    (void*)(intptr_t)offsetof(SPVM_OBJECT, ref_count), // object_ref_count_offset
    (void*)(intptr_t)-1, // object_basic_type_id_offset
    (void*)(intptr_t)offsetof(SPVM_OBJECT, type_dimension), // object_type_dimension_offset
    (void*)(intptr_t)offsetof(SPVM_OBJECT, flag), // object_flag_offset
    (void*)(intptr_t)offsetof(SPVM_OBJECT, length), // object_length_offset
    SPVM_API_RUNTIME_get_allocator,
    SPVM_API_RUNTIME_build,
    NULL, // reserved78
    SPVM_API_RUNTIME_get_method_required_args_length,
    NULL, // reserved80
    SPVM_API_RUNTIME_get_method_is_enum,
    NULL, // reserved82
    SPVM_API_RUNTIME_is_object_type,
    NULL, // reserved84
    (void*)NULL, // init_flags
    SPVM_API_RUNTIME_can_assign,
    SPVM_API_RUNTIME_get_basic_type_module_rel_file_id,
    SPVM_API_RUNTIME_get_basic_type_module_dir_id,
    SPVM_API_RUNTIME_get_basic_type_is_anon,
    SPVM_API_RUNTIME_get_basic_type_fields_base_address_id,
    SPVM_API_RUNTIME_get_basic_type_fields_length,
    SPVM_API_RUNTIME_get_basic_type_methods_base_address_id,
    SPVM_API_RUNTIME_get_basic_type_methods_length,
    SPVM_API_RUNTIME_get_basic_type_class_vars_base_address_id,
    SPVM_API_RUNTIME_get_basic_type_class_vars_length,
    NULL, // reserved96
    NULL, // reserved97
    NULL, // reserved98
    SPVM_API_RUNTIME_get_basic_types_length,
    SPVM_API_RUNTIME_get_field_basic_type_id,
    SPVM_API_RUNTIME_get_field_type_dimension,
    SPVM_API_RUNTIME_get_field_type_flag,
    SPVM_API_RUNTIME_get_class_var_basic_type_id,
    SPVM_API_RUNTIME_get_class_var_type_dimension,
    SPVM_API_RUNTIME_get_class_var_type_flag,
    SPVM_API_RUNTIME_get_method_return_basic_type_id,
    SPVM_API_RUNTIME_get_method_return_type_dimension,
    SPVM_API_RUNTIME_get_method_return_type_flag,
    SPVM_API_RUNTIME_get_arg_basic_type_id,
    SPVM_API_RUNTIME_get_arg_type_dimension,
    SPVM_API_RUNTIME_get_arg_type_flag,
    SPVM_API_RUNTIME_get_method_current_basic_type_id,
    SPVM_API_RUNTIME_get_field_current_basic_type_id,
    SPVM_API_RUNTIME_get_class_var_current_basic_type_id,
    SPVM_API_RUNTIME_get_basic_type_parent_id,
    SPVM_API_RUNTIME_get_basic_type_version_string_id,
  };
  SPVM_ENV_RUNTIME* env_runtime = calloc(1, sizeof(env_runtime_init));
  memcpy(env_runtime, env_runtime_init, sizeof(env_runtime_init));
  
  return env_runtime;
}

SPVM_RUNTIME* SPVM_API_RUNTIME_new_object() {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_new();
  
  return runtime;
}

void SPVM_API_RUNTIME_free_object(SPVM_RUNTIME* runtime) {

  SPVM_RUNTIME_free(runtime);
}

SPVM_OPCODE* SPVM_API_RUNTIME_get_opcodes(SPVM_RUNTIME* runtime) {

  return runtime->opcodes;
}

int32_t SPVM_API_RUNTIME_get_opcodes_length(SPVM_RUNTIME* runtime) {
  
  return runtime->opcodes_length;
}

int32_t SPVM_API_RUNTIME_get_basic_types_length(SPVM_RUNTIME* runtime) {
  
  return runtime->basic_types_length;
}

int32_t* SPVM_API_RUNTIME_get_runtime_codes(SPVM_RUNTIME* runtime) {

  return runtime->runtime_codes;
}

int32_t SPVM_API_RUNTIME_get_runtime_codes_length(SPVM_RUNTIME* runtime) {
  
  return runtime->runtime_codes_length;
}

const char* SPVM_API_RUNTIME_get_name(SPVM_RUNTIME* runtime, int32_t constant_string_id) {
  
  const char* name = SPVM_API_RUNTIME_get_constant_string_value(runtime, constant_string_id, NULL);
  
  return name;
}

const char* SPVM_API_RUNTIME_get_constant_string_value(SPVM_RUNTIME* runtime, int32_t constant_string_id, int32_t* string_length) {
  
  SPVM_RUNTIME_CONSTANT_STRING* constant_string = &runtime->constant_strings[constant_string_id];
  
  const char* constant_string_value = constant_string->value;
  
  if (string_length) {
    *string_length = constant_string->length;
  }
  
  return constant_string_value;
}

int32_t SPVM_API_RUNTIME_get_constant_string_id(SPVM_RUNTIME* runtime, const char* string) {

  SPVM_RUNTIME_CONSTANT_STRING* constant_string = SPVM_HASH_get(runtime->constant_string_symtable, string, strlen(string));

  int32_t constant_string_id;
  if (constant_string) {
    constant_string_id = constant_string->id;
  }
  else {
    constant_string_id = -1;
  }

  return constant_string_id;
}

int32_t SPVM_API_RUNTIME_get_basic_type_id_by_name(SPVM_RUNTIME* runtime, const char* basic_type_name) {
  (void)runtime;
  
  if (basic_type_name == NULL) {
    return -1;
  }
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type_by_name(runtime, basic_type_name);
  if (basic_type) {
    int32_t basic_type_id = basic_type->id;
    return basic_type_id;
  }
  else {
    return -1;
  }
}

int32_t SPVM_API_RUNTIME_get_basic_type_category(SPVM_RUNTIME* runtime, int32_t basic_type_id) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, basic_type_id);
  
  assert(basic_type);
  
  int32_t basic_type_category = basic_type->category;
  
  return basic_type_category;
}

const char* SPVM_API_RUNTIME_get_basic_type_name(SPVM_RUNTIME* runtime, int32_t basic_type_id) {
  
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = (SPVM_RUNTIME_BASIC_TYPE*)SPVM_API_RUNTIME_get_basic_type(runtime, basic_type_id);
  
  SPVM_RUNTIME_CONSTANT_STRING* basic_type_name_string = (SPVM_RUNTIME_CONSTANT_STRING*)&runtime->constant_strings[basic_type->name_id];

  const char* basic_type_name = (const char*)&runtime->constant_strings_buffer[basic_type_name_string->string_buffer_id];
  
  return basic_type_name;
}

int32_t SPVM_API_RUNTIME_get_basic_type_name_id(SPVM_RUNTIME* runtime, int32_t basic_type_id) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, basic_type_id);
  
  assert(basic_type);
  
  int32_t basic_type_name_id = basic_type->name_id;
  
  return basic_type_name_id;
}

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_basic_type_by_name(SPVM_RUNTIME* runtime, const char* basic_type_name) {

  SPVM_RUNTIME_BASIC_TYPE* basic_type = (SPVM_RUNTIME_BASIC_TYPE*)SPVM_HASH_get(runtime->basic_type_symtable, basic_type_name, strlen(basic_type_name));
  
  return basic_type;
}

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_basic_type(SPVM_RUNTIME* runtime, int32_t basic_type_id) {

  if (basic_type_id < 0) {
    return NULL;
  }
  
  if (basic_type_id >= runtime->basic_types_length) {
    return NULL;
  }

  SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];
  
  return basic_type;
}

int32_t SPVM_API_RUNTIME_get_basic_type_version_string_id(SPVM_RUNTIME* runtime, int32_t basic_type_id) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, basic_type_id);
  
  assert(basic_type);
  
  int32_t version_string_id = basic_type->version_string_id;
  
  return version_string_id;
}

int32_t SPVM_API_RUNTIME_get_basic_type_is_pointer(SPVM_RUNTIME* runtime, int32_t basic_type_id) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, basic_type_id);
  
  assert(basic_type);
  
  int32_t is_pointer = basic_type->is_pointer;
  
  return is_pointer;
}

int32_t SPVM_API_RUNTIME_get_basic_type_anon_basic_types_base_address_id(SPVM_RUNTIME* runtime, int32_t basic_type_id) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, basic_type_id);
  
  assert(basic_type);
  
  int32_t anon_basic_types_base_id = basic_type->anon_basic_types_base_id;
  
  return anon_basic_types_base_id;
}

int32_t SPVM_API_RUNTIME_get_basic_type_anon_basic_types_length(SPVM_RUNTIME* runtime, int32_t basic_type_id) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, basic_type_id);
  
  assert(basic_type);
  
  int32_t anon_basic_types_length = basic_type->anon_basic_types_length;
  
  return anon_basic_types_length;
}

int32_t SPVM_API_RUNTIME_get_basic_type_is_anon(SPVM_RUNTIME* runtime, int32_t basic_type_id) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, basic_type_id);
  
  assert(basic_type);
  
  int32_t is_anon = basic_type->is_anon;
  
  return is_anon;
}

int32_t SPVM_API_RUNTIME_get_basic_type_module_rel_file_id(SPVM_RUNTIME* runtime, int32_t basic_type_id) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, basic_type_id);
  
  assert(basic_type);
  
  int32_t rel_file_id = basic_type->module_rel_file_id;
  
  return rel_file_id;
}

int32_t SPVM_API_RUNTIME_get_basic_type_module_dir_id(SPVM_RUNTIME* runtime, int32_t basic_type_id) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, basic_type_id);
  
  assert(basic_type);
  
  int32_t include_dir_id = basic_type->module_dir_id;
  
  return include_dir_id;
}

int32_t SPVM_API_RUNTIME_get_basic_type_fields_base_address_id(SPVM_RUNTIME* runtime, int32_t basic_type_id) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, basic_type_id);
  
  assert(basic_type);
  
  int32_t fields_base_id = basic_type->fields_base_id;
  
  return fields_base_id;
}

int32_t SPVM_API_RUNTIME_get_basic_type_fields_length(SPVM_RUNTIME* runtime, int32_t basic_type_id) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, basic_type_id);
  
  assert(basic_type);
  
  int32_t fields_length = basic_type->fields_length;
  
  return fields_length;
}

int32_t SPVM_API_RUNTIME_get_basic_type_methods_base_address_id(SPVM_RUNTIME* runtime, int32_t basic_type_id) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, basic_type_id);
  
  assert(basic_type);
  
  int32_t methods_base_id = basic_type->methods_base_id;
  
  return methods_base_id;
}

int32_t SPVM_API_RUNTIME_get_basic_type_methods_length(SPVM_RUNTIME* runtime, int32_t basic_type_id) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, basic_type_id);
  // warn("GGG %d", basic_type_id);
  assert(basic_type);
  
  int32_t methods_length = basic_type->methods_length;
  
  return methods_length;
}

int32_t SPVM_API_RUNTIME_get_basic_type_class_vars_base_address_id(SPVM_RUNTIME* runtime, int32_t basic_type_id) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, basic_type_id);
  
  assert(basic_type);
  
  int32_t class_vars_base_id = basic_type->class_vars_base_id;
  
  return class_vars_base_id;
}

int32_t SPVM_API_RUNTIME_get_basic_type_class_vars_length(SPVM_RUNTIME* runtime, int32_t basic_type_id) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, basic_type_id);
  
  assert(basic_type);
  
  int32_t class_vars_length = basic_type->class_vars_length;
  
  return class_vars_length;
}

int32_t SPVM_API_RUNTIME_get_basic_type_parent_id(SPVM_RUNTIME* runtime, int32_t basic_type_id) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, basic_type_id);
  
  assert(basic_type);
  
  int32_t parent_basic_type_id = basic_type->parent_id;
  
  return parent_basic_type_id;
}

int32_t SPVM_API_RUNTIME_get_class_var_id_by_index(SPVM_RUNTIME* runtime, int32_t basic_type_id, int32_t class_var_index) {
  
  int32_t class_var_id = -1;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, basic_type_id);
  
  if (basic_type) {
    if (class_var_index >= 0 && class_var_index < basic_type->class_vars_length) {
      class_var_id = basic_type->class_vars_base_id + class_var_index;
    }
  }
  
  return class_var_id;
}

int32_t SPVM_API_RUNTIME_get_class_var_id_by_name(SPVM_RUNTIME* runtime, const char* basic_type_name, const char* class_var_name) {
  (void)runtime;
  
  int32_t class_var_id = -1;
  
  SPVM_RUNTIME_BASIC_TYPE* baisc_type = SPVM_API_RUNTIME_get_basic_type_by_name(runtime, basic_type_name);
  
  if (baisc_type) {
    SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var_address(runtime, baisc_type, class_var_name);
    if (class_var) {
      class_var_id = class_var->id;
    }
  }
  
  return class_var_id;
}

SPVM_RUNTIME_CLASS_VAR* SPVM_API_RUNTIME_get_class_var_address(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, const char* search_class_var_name) {
  
  SPVM_RUNTIME_CLASS_VAR* found_class_var = NULL;
  if (basic_type->class_vars_length > 0) {
    for (int32_t class_var_id = basic_type->class_vars_base_id; class_var_id <  basic_type->class_vars_base_id + basic_type->class_vars_length; class_var_id++) {
      SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var(runtime, class_var_id);
      const char* class_var_name = SPVM_API_RUNTIME_get_name(runtime, class_var->name_id);
      if (strcmp(class_var_name, search_class_var_name) == 0) {
        found_class_var = class_var;
        break;
      }
    }
  }
  
  return found_class_var;
}

int32_t SPVM_API_RUNTIME_get_class_var_name_id(SPVM_RUNTIME* runtime, int32_t class_var_id) {
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var(runtime, class_var_id);
  
  assert(class_var);
  
  int32_t name_id = class_var->name_id;
  
  return name_id;
}

int32_t SPVM_API_RUNTIME_get_class_var_current_basic_type_id(SPVM_RUNTIME* runtime, int32_t class_var_id) {
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var(runtime, class_var_id);
  
  assert(class_var);
  
  int32_t basic_type_id = class_var->current_basic_type_id;
  
  return basic_type_id;
}

SPVM_RUNTIME_CLASS_VAR* SPVM_API_RUNTIME_get_class_var(SPVM_RUNTIME* runtime, int32_t class_var_id) {
  
  if (class_var_id < 0) {
    return NULL;
  }
  
  if (class_var_id >= runtime->class_vars_length) {
    return NULL;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = &runtime->class_vars[class_var_id];
  
  return class_var;
}

int32_t SPVM_API_RUNTIME_get_class_var_basic_type_id(SPVM_RUNTIME* runtime, int32_t class_var_id) {
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var(runtime, class_var_id);
  
  assert(class_var);
  
  int32_t type_id = class_var->basic_type_id;
  
  return type_id;
}

int32_t SPVM_API_RUNTIME_get_class_var_type_dimension(SPVM_RUNTIME* runtime, int32_t class_var_id) {
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var(runtime, class_var_id);
  
  assert(class_var);
  
  int32_t type_id = class_var->type_dimension;
  
  return type_id;
}

int32_t SPVM_API_RUNTIME_get_class_var_type_flag(SPVM_RUNTIME* runtime, int32_t class_var_id) {
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var(runtime, class_var_id);
  
  assert(class_var);
  
  int32_t type_id = class_var->type_flag;
  
  return type_id;
}

SPVM_RUNTIME_FIELD* SPVM_API_RUNTIME_get_field(SPVM_RUNTIME* runtime, int32_t field_address_id) {
  
  if (field_address_id < 0) {
    return NULL;
  }
  
  if (field_address_id >= runtime->fields_length) {
    return NULL;
  }
  
  SPVM_RUNTIME_FIELD* field = &runtime->fields[field_address_id];
  
  return field;
}

int32_t SPVM_API_RUNTIME_get_field_current_basic_type_id(SPVM_RUNTIME* runtime, int32_t field_address_id) {
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_address_id);
  
  assert(field);
  
  int32_t current_basic_type_id = field->current_basic_type_id;
  
  return current_basic_type_id;
}

int32_t SPVM_API_RUNTIME_get_field_basic_type_id(SPVM_RUNTIME* runtime, int32_t field_address_id) {
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_address_id);
  
  assert(field);
  
  int32_t basic_type_id = field->basic_type_id;
  
  return basic_type_id;
}

int32_t SPVM_API_RUNTIME_get_field_type_dimension(SPVM_RUNTIME* runtime, int32_t field_address_id) {
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_address_id);
  
  assert(field);
  
  int32_t type_dimension = field->type_dimension;
  
  return type_dimension;
}

int32_t SPVM_API_RUNTIME_get_field_type_flag(SPVM_RUNTIME* runtime, int32_t field_address_id) {
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_address_id);
  
  assert(field);
  
  int32_t type_flag = field->type_flag;
  
  return type_flag;
}

int32_t SPVM_API_RUNTIME_get_field_name_id(SPVM_RUNTIME* runtime, int32_t field_address_id) {
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_address_id);
  
  assert(field);
  
  int32_t name_id = field->name_id;
  
  return name_id;
}

int32_t SPVM_API_RUNTIME_get_method_address_id_by_name(SPVM_RUNTIME* runtime, const char* basic_type_name, const char* method_name) {
  (void)runtime;
  
  int32_t method_address_id = -1;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type_by_name(runtime, basic_type_name);
  
  if (basic_type) {
    SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method_address(runtime, basic_type, method_name);
    
    if (method) {
      method_address_id = method->id;
    }
  }
  
  return method_address_id;
}

int32_t SPVM_API_RUNTIME_get_field_address_id_by_index(SPVM_RUNTIME* runtime, int32_t basic_type_id, int32_t field_index) {
  
  int32_t field_address_id = -1;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, basic_type_id);
  
  if (basic_type) {
    if (field_index >= 0 && field_index < basic_type->fields_length) {
      field_address_id = basic_type->fields_base_id + field_index;
    }
  }
  
  return field_address_id;
}

int32_t SPVM_API_RUNTIME_get_field_address_id_by_name(SPVM_RUNTIME* runtime, const char* basic_type_name, const char* field_name) {
  (void)runtime;
  
  int32_t field_address_id = -1;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type_by_name(runtime, basic_type_name);
  
  if (basic_type) {
    SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field_address(runtime, basic_type, field_name);
    if (field) {
      field_address_id = field->id;
    }
  }
  
  return field_address_id;
}

int32_t SPVM_API_RUNTIME_get_method_address_id_by_index(SPVM_RUNTIME* runtime, int32_t basic_type_id, int32_t method_index) {
  
  int32_t method_address_id = -1;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, basic_type_id);
  
  if (basic_type_id) {
    if (method_index >= 0 && method_index < basic_type->methods_length) {
      method_address_id = basic_type->methods_base_id + method_index;
    }
  }
  
  return method_address_id;
}

SPVM_RUNTIME_METHOD* SPVM_API_RUNTIME_get_method_address(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, const char* search_method_name) {
  
  SPVM_RUNTIME_METHOD* found_method = NULL;
  if (basic_type->methods_length > 0) {
    // Performe binary searching because methods are sorted by the names
    int32_t cur_min_index = basic_type->methods_base_id;
    int32_t cur_max_index = cur_min_index + basic_type->methods_length - 1;
    
    while (1) {
      if (cur_max_index < cur_min_index) {
        break;
      }
      
      int32_t cur_half_index = cur_min_index + (cur_max_index - cur_min_index) / 2;
      
      SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, cur_half_index);
      const char* cur_half_method_name = SPVM_API_RUNTIME_get_name(runtime, method->name_id);
      
      int32_t cmp_result = strcmp(search_method_name, cur_half_method_name);
      
      if (cmp_result > 0) {
        cur_min_index = cur_half_index + 1;
      }
      else if (cmp_result < 0) {
        cur_max_index = cur_half_index - 1;
      }
      else {
        found_method = method;
        break;
      }
    }
  }
  
  return found_method;
}

SPVM_RUNTIME_FIELD* SPVM_API_RUNTIME_get_field_address(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, const char* search_field_name) {
  
  SPVM_RUNTIME_FIELD* found_field = NULL;
  if (basic_type->fields_length > 0) {
    for (int32_t field_address_id = basic_type->fields_base_id; field_address_id <  basic_type->fields_base_id + basic_type->fields_length; field_address_id++) {
      SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_address_id);
      const char* field_name = SPVM_API_RUNTIME_get_name(runtime, field->name_id);
      if (strcmp(field_name, search_field_name) == 0) {
        found_field = field;
        break;
      }
    }
  }
  
  return found_field;
}

SPVM_RUNTIME_METHOD* SPVM_API_RUNTIME_get_method(SPVM_RUNTIME* runtime, int32_t method_address_id) {
  
  if (method_address_id < 0) {
    return NULL;
  }
  
  if (method_address_id >= runtime->methods_length) {
    return NULL;
  }
  
  SPVM_RUNTIME_METHOD* method = &runtime->methods[method_address_id];
  
  return method;
}

int32_t SPVM_API_RUNTIME_get_method_current_basic_type_id(SPVM_RUNTIME* runtime, int32_t method_address_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_address_id);
  
  assert(method);
  
  int32_t basic_type_id = method->current_basic_type_id;
  
  return basic_type_id;
}

int32_t SPVM_API_RUNTIME_get_method_opcodes_base_address_id(SPVM_RUNTIME* runtime, int32_t method_address_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_address_id);
  
  assert(method);
  
  int32_t opcodes_base_id = method->opcodes_base_id;
  
  return opcodes_base_id;
}

int32_t SPVM_API_RUNTIME_get_method_opcodes_length(SPVM_RUNTIME* runtime, int32_t method_address_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_address_id);
  
  assert(method);
  
  int32_t opcodes_length = method->opcodes_length;
  
  return opcodes_length;
}

int32_t SPVM_API_RUNTIME_get_method_name_id(SPVM_RUNTIME* runtime, int32_t method_address_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_address_id);
  
  assert(method);
  
  int32_t name_id = method->name_id;
  
  return name_id;
}

int32_t SPVM_API_RUNTIME_get_method_is_anon(SPVM_RUNTIME* runtime, int32_t method_address_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_address_id);
  
  assert(method);
  
  int32_t is_anon = method->is_anon;
  
  return is_anon;
}

int32_t SPVM_API_RUNTIME_get_method_is_native(SPVM_RUNTIME* runtime, int32_t method_address_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_address_id);
  
  return method->is_native;
}

int32_t SPVM_API_RUNTIME_get_method_is_precompile(SPVM_RUNTIME* runtime, int32_t method_address_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_address_id);
  return method->is_precompile;
}

int32_t SPVM_API_RUNTIME_get_method_is_enum(SPVM_RUNTIME* runtime, int32_t method_address_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_address_id);
  return method->is_enum;
}

int32_t SPVM_API_RUNTIME_get_method_args_length(SPVM_RUNTIME* runtime, int32_t method_address_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_address_id);
  
  assert(method);
  
  int32_t args_length = method->args_length;
  
  return args_length;
}

int32_t SPVM_API_RUNTIME_get_method_required_args_length(SPVM_RUNTIME* runtime, int32_t method_address_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_address_id);
  
  assert(method);
  
  int32_t required_args_length = method->required_args_length;
  
  return required_args_length;
}

int32_t SPVM_API_RUNTIME_get_method_args_base_address_id(SPVM_RUNTIME* runtime, int32_t method_address_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_address_id);
  
  assert(method);
  
  int32_t args_base_id = method->args_base_id;
  
  return args_base_id;
}

int32_t SPVM_API_RUNTIME_get_method_is_static(SPVM_RUNTIME* runtime, int32_t method_address_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_address_id);
  
  assert(method);
  
  int32_t is_static = method->is_static;
  
  return is_static;
}

int32_t SPVM_API_RUNTIME_get_method_return_basic_type_id(SPVM_RUNTIME* runtime, int32_t method_address_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_address_id);
  
  assert(method);
  
  int32_t return_basic_type_id = method->return_basic_type_id;
  
  return return_basic_type_id;
}

int32_t SPVM_API_RUNTIME_get_method_return_type_dimension(SPVM_RUNTIME* runtime, int32_t method_address_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_address_id);
  
  assert(method);
  
  int32_t return_type_dimension = method->return_type_dimension;
  
  return return_type_dimension;
}

int32_t SPVM_API_RUNTIME_get_method_return_type_flag(SPVM_RUNTIME* runtime, int32_t method_address_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_address_id);
  
  assert(method);
  
  int32_t return_type_flag = method->return_type_flag;
  
  return return_type_flag;
}

int32_t SPVM_API_RUNTIME_get_method_call_stack_byte_vars_length(SPVM_RUNTIME* runtime, int32_t method_address_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_address_id);
  
  assert(method);
  
  int32_t call_stack_byte_vars_length = method->call_stack_byte_vars_length;
  
  return call_stack_byte_vars_length;
}

int32_t SPVM_API_RUNTIME_get_method_call_stack_short_vars_length(SPVM_RUNTIME* runtime, int32_t method_address_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_address_id);
  
  assert(method);
  
  int32_t call_stack_short_vars_length = method->call_stack_short_vars_length;
  
  return call_stack_short_vars_length;
}

int32_t SPVM_API_RUNTIME_get_method_call_stack_int_vars_length(SPVM_RUNTIME* runtime, int32_t method_address_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_address_id);
  
  assert(method);
  
  int32_t call_stack_int_vars_length = method->call_stack_int_vars_length;
  
  return call_stack_int_vars_length;
}

int32_t SPVM_API_RUNTIME_get_method_call_stack_long_vars_length(SPVM_RUNTIME* runtime, int32_t method_address_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_address_id);
  
  assert(method);
  
  int32_t call_stack_long_vars_length = method->call_stack_long_vars_length;
  
  return call_stack_long_vars_length;
}

int32_t SPVM_API_RUNTIME_get_method_call_stack_float_vars_length(SPVM_RUNTIME* runtime, int32_t method_address_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_address_id);
  
  assert(method);
  
  int32_t call_stack_float_vars_length = method->call_stack_float_vars_length;
  
  return call_stack_float_vars_length;
}

int32_t SPVM_API_RUNTIME_get_method_call_stack_double_vars_length(SPVM_RUNTIME* runtime, int32_t method_address_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_address_id);
  
  assert(method);
  
  int32_t call_stack_double_vars_length = method->call_stack_double_vars_length;
  
  return call_stack_double_vars_length;
}

int32_t SPVM_API_RUNTIME_get_method_call_stack_object_vars_length(SPVM_RUNTIME* runtime, int32_t method_address_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_address_id);
  
  assert(method);
  
  int32_t call_stack_object_vars_length = method->call_stack_object_vars_length;
  
  return call_stack_object_vars_length;
}

int32_t SPVM_API_RUNTIME_get_method_call_stack_ref_vars_length(SPVM_RUNTIME* runtime, int32_t method_address_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_address_id);
  
  assert(method);
  
  int32_t call_stack_ref_vars_length = method->call_stack_ref_vars_length;
  
  return call_stack_ref_vars_length;
}

int32_t SPVM_API_RUNTIME_get_method_mortal_stack_length(SPVM_RUNTIME* runtime, int32_t method_address_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_address_id);
  
  assert(method);
  
  int32_t mortal_stack_length = method->mortal_stack_length;
  
  return mortal_stack_length;
}

SPVM_RUNTIME_ARG* SPVM_API_RUNTIME_get_arg(SPVM_RUNTIME* runtime, int32_t arg_id) {
  
  if (arg_id < 0) {
    return NULL;
  }
  
  if (arg_id >= runtime->args_length) {
    return NULL;
  }

  SPVM_RUNTIME_ARG* arg = &runtime->args[arg_id];
  
  return arg;
}

int32_t SPVM_API_RUNTIME_get_arg_basic_type_id(SPVM_RUNTIME* runtime, int32_t arg_id) {
  
  SPVM_RUNTIME_ARG* arg = SPVM_API_RUNTIME_get_arg(runtime, arg_id);
  
  assert(arg);
  
  int32_t basic_type_id = arg->basic_type_id;
  
  return basic_type_id;
}

int32_t SPVM_API_RUNTIME_get_arg_type_dimension(SPVM_RUNTIME* runtime, int32_t arg_id) {
  
  SPVM_RUNTIME_ARG* arg = SPVM_API_RUNTIME_get_arg(runtime, arg_id);
  
  assert(arg);
  
  int32_t type_dimension = arg->type_dimension;
  
  return type_dimension;
}

int32_t SPVM_API_RUNTIME_get_arg_type_flag(SPVM_RUNTIME* runtime, int32_t arg_id) {
  
  SPVM_RUNTIME_ARG* arg = SPVM_API_RUNTIME_get_arg(runtime, arg_id);
  
  assert(arg);
  
  int32_t type_flag = arg->type_flag;
  
  return type_flag;
}

int32_t SPVM_API_RUNTIME_get_anon_basic_type_id(SPVM_RUNTIME* runtime, int32_t anon_basic_type_address_id) {
  
  int32_t anon_basic_type_id = runtime->anon_basic_type_ids[anon_basic_type_address_id];
  
  return anon_basic_type_id;
}

void SPVM_API_RUNTIME_set_native_method_address(SPVM_RUNTIME* runtime, int32_t method_address_id, void* address) {

  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_address_id);
  
  runtime->method_native_addresses[method->id] = address;
}

void SPVM_API_RUNTIME_set_precompile_method_address(SPVM_RUNTIME* runtime, int32_t method_address_id, void* address) {

  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_address_id);
  
  runtime->method_precompile_addresses[method->id] = address;
}

void* SPVM_API_RUNTIME_get_native_method_address(SPVM_RUNTIME* runtime, int32_t method_address_id) {

  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_address_id);
  
  void* native_method_address = runtime->method_native_addresses[method->id];
  
  return native_method_address;
}

void* SPVM_API_RUNTIME_get_precompile_method_address(SPVM_RUNTIME* runtime, int32_t method_address_id) {

  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_address_id);
  
  void* precompile_method_address = runtime->method_precompile_addresses[method->id];
  
  return precompile_method_address;
}

int32_t SPVM_API_RUNTIME_has_interface_by_id(SPVM_RUNTIME* runtime, int32_t basic_type_id, int32_t interface_basic_type_id) {

  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, basic_type_id);
  SPVM_RUNTIME_BASIC_TYPE* interface_basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, interface_basic_type_id);
  
  if (!(basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS || basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE)) {
    return 0;
  }
  
  if (!(interface_basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS || interface_basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE)) {
    return 0;
  }
  
  SPVM_RUNTIME_METHOD* method_interface = SPVM_API_RUNTIME_get_method(runtime, interface_basic_type->required_method_address_id);
  
  const char* method_interface_name =  SPVM_API_RUNTIME_get_constant_string_value(runtime, method_interface->name_id, NULL);
  
  SPVM_RUNTIME_METHOD* found_method = SPVM_API_RUNTIME_get_method_address(runtime, basic_type, method_interface_name);
  if (found_method) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_API_RUNTIME_is_super_by_id(SPVM_RUNTIME* runtime, int32_t super_basic_type_id, int32_t child_basic_type_id) {

  int32_t is_super_basic_type = 0;
  
  SPVM_RUNTIME_BASIC_TYPE* super_basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, super_basic_type_id);
  SPVM_RUNTIME_BASIC_TYPE* child_basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, child_basic_type_id);
  
  if (!(super_basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS)) {
    return 0;
  }
  
  if (!(child_basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS)) {
    return 0;
  }
  
  int32_t parent_basic_type_id = child_basic_type->parent_id;
  while (1) {
    if (parent_basic_type_id > 0) {
      SPVM_RUNTIME_BASIC_TYPE* parent_basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, parent_basic_type_id);
      if (parent_basic_type->id == super_basic_type->id) {
        is_super_basic_type = 1;
        break;
      }
      else {
        parent_basic_type_id = parent_basic_type->parent_id;
      }
    }
    else {
      is_super_basic_type = 0;
      break;
    }
  }
  
  return is_super_basic_type;
}

SPVM_ALLOCATOR* SPVM_API_RUNTIME_get_allocator(SPVM_RUNTIME* runtime) {
  return SPVM_RUNTIME_get_allocator(runtime);
}

void SPVM_API_RUNTIME_build(SPVM_RUNTIME* runtime, int32_t* runtime_codes) {
  SPVM_RUNTIME_build(runtime, runtime_codes);
}

int32_t SPVM_API_RUNTIME_is_object_type(SPVM_RUNTIME* runtime, int32_t basic_type_id, int32_t type_dimension, int32_t flag) {
  
  int32_t is_object_type;
  if (type_dimension == 0) {
    int32_t basic_type_category = SPVM_API_RUNTIME_get_basic_type_category(runtime, basic_type_id);
    
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

int32_t SPVM_API_RUNTIME_can_assign(SPVM_RUNTIME* runtime, int32_t dist_basic_type_id, int32_t dist_type_dimension, int32_t dist_type_flag, int32_t src_basic_type_id, int32_t src_type_dimension, int32_t src_type_flag) {
  
  int32_t isa = 0;
  
  int32_t dist_basic_type_category = SPVM_API_RUNTIME_get_basic_type_category(runtime, dist_basic_type_id);
  int32_t src_basic_type_category = SPVM_API_RUNTIME_get_basic_type_category(runtime, src_basic_type_id);
  
  if (dist_basic_type_id == src_basic_type_id && dist_type_dimension == src_type_dimension) {
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
      isa = SPVM_API_RUNTIME_has_interface_by_id(runtime, src_basic_type_id, dist_basic_type_id);
    }
    else if (dist_basic_type_category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS) {
      isa = SPVM_API_RUNTIME_is_super_by_id(runtime, dist_basic_type_id, src_basic_type_id);
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
