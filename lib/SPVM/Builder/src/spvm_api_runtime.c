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
#include "spvm_class.h"
#include "spvm_method.h"

#include "spvm_list.h"
#include "spvm_hash.h"

#include "spvm_object.h"
#include "spvm_opcode.h"
#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_class.h"
#include "spvm_runtime_class_var.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime.h"
#include "spvm_runtime_method.h"
#include "spvm_runtime_constant_string.h"
#include "spvm_runtime_type.h"
#include "spvm_api_runtime.h"
































































SPVM_ENV_RUNTIME* SPVM_API_RUNTIME_new_env() {
  
  void* env_runtime_init[]  = {
    SPVM_API_RUNTIME_new_object,
    SPVM_API_RUNTIME_free_object,
    SPVM_API_RUNTIME_get_opcodes,
    SPVM_API_RUNTIME_get_opcodes_length,
    SPVM_API_RUNTIME_get_runtime_codes,
    SPVM_API_RUNTIME_get_runtime_codes_length,
    SPVM_API_RUNTIME_get_classes_length,
    SPVM_API_RUNTIME_get_constant_string_id,
    SPVM_API_RUNTIME_get_constant_string_value,
    SPVM_API_RUNTIME_get_name,
    SPVM_API_RUNTIME_get_basic_type_id_by_name,
    SPVM_API_RUNTIME_get_basic_type_name_id,
    SPVM_API_RUNTIME_get_basic_type_class_id,
    SPVM_API_RUNTIME_get_basic_type_category,
    SPVM_API_RUNTIME_get_type_basic_type_id,
    SPVM_API_RUNTIME_get_type_dimension,
    SPVM_API_RUNTIME_get_type_stack_length,
    SPVM_API_RUNTIME_get_type_is_object,
    SPVM_API_RUNTIME_get_type_is_ref,
    SPVM_API_RUNTIME_get_class_id_by_name,
    SPVM_API_RUNTIME_get_class_name_id,
    SPVM_API_RUNTIME_get_class_class_rel_file_id,
    SPVM_API_RUNTIME_get_class_class_path_id,
    SPVM_API_RUNTIME_get_class_is_anon,
    SPVM_API_RUNTIME_get_class_fields_base_id,
    SPVM_API_RUNTIME_get_class_fields_length,
    SPVM_API_RUNTIME_get_class_methods_base_id,
    SPVM_API_RUNTIME_get_class_methods_length,
    SPVM_API_RUNTIME_get_class_class_vars_base_id,
    SPVM_API_RUNTIME_get_class_class_vars_length,
    SPVM_API_RUNTIME_get_class_anon_methods_base_id,
    SPVM_API_RUNTIME_get_class_anon_methods_length,
    SPVM_API_RUNTIME_get_class_var_id_by_index,
    SPVM_API_RUNTIME_get_class_var_id_by_name,
    SPVM_API_RUNTIME_get_class_var_name_id,
    SPVM_API_RUNTIME_get_class_var_class_id,
    SPVM_API_RUNTIME_get_field_id_by_index,
    SPVM_API_RUNTIME_get_field_id_by_name,
    SPVM_API_RUNTIME_get_field_name_id,
    SPVM_API_RUNTIME_get_field_type_id,
    SPVM_API_RUNTIME_get_field_class_id,
    SPVM_API_RUNTIME_get_method_id_by_index,
    SPVM_API_RUNTIME_get_method_id_by_name,
    SPVM_API_RUNTIME_get_method_name_id,
    SPVM_API_RUNTIME_get_method_return_type_id,
    SPVM_API_RUNTIME_get_method_class_id,
    SPVM_API_RUNTIME_get_method_is_class_method,
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
    SPVM_API_RUNTIME_get_method_opcodes_base_id,
    SPVM_API_RUNTIME_get_method_opcodes_length,
    SPVM_API_RUNTIME_get_method_args_base_id,
    SPVM_API_RUNTIME_get_method_args_length,
    SPVM_API_RUNTIME_get_arg_type_id,
    SPVM_API_RUNTIME_get_anon_method_method_id,
    SPVM_API_RUNTIME_get_native_method_address,
    SPVM_API_RUNTIME_set_native_method_address,
    SPVM_API_RUNTIME_get_precompile_method_address,
    SPVM_API_RUNTIME_set_precompile_method_address,
    (void*)(intptr_t)sizeof(SPVM_OBJECT), // object_header_size
    (void*)(intptr_t)offsetof(SPVM_OBJECT, weaken_backref_head), // weaken_backref_head
    (void*)(intptr_t)offsetof(SPVM_OBJECT, ref_count), // object_ref_count_offset
    (void*)(intptr_t)offsetof(SPVM_OBJECT, basic_type_id), // object_basic_type_id_offset
    (void*)(intptr_t)offsetof(SPVM_OBJECT, type_dimension), // object_type_dimension_offset
    (void*)(intptr_t)offsetof(SPVM_OBJECT, flag), // object_flag_offset
    (void*)(intptr_t)offsetof(SPVM_OBJECT, length), // object_length_offset
    SPVM_API_RUNTIME_get_allocator,
    SPVM_API_RUNTIME_build,
    SPVM_API_RUNTIME_get_class_parent_class_id,
    SPVM_API_RUNTIME_get_method_required_args_length,
    SPVM_API_RUNTIME_get_class_is_pointer,
    SPVM_API_RUNTIME_get_method_is_enum,
    SPVM_API_RUNTIME_get_type_flag,
    SPVM_API_RUNTIME_is_object_type,
    SPVM_API_RUNTIME_get_class_version_string_id,
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

int32_t SPVM_API_RUNTIME_get_classes_length(SPVM_RUNTIME* runtime) {
  
  return runtime->classes_length;
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

int32_t SPVM_API_RUNTIME_get_basic_type_class_id(SPVM_RUNTIME* runtime, int32_t basic_type_id) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, basic_type_id);
  
  assert(basic_type);
  
  int32_t basic_type_class_id = basic_type->class_id;
  
  return basic_type_class_id;
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

SPVM_RUNTIME_TYPE* SPVM_API_RUNTIME_get_type(SPVM_RUNTIME* runtime, int32_t type_id) {
  
  if (type_id < 0) {
    return NULL;
  }
  
  if (type_id >= runtime->types_length) {
    return NULL;
  }

  SPVM_RUNTIME_TYPE* type = &runtime->types[type_id];
  
  return type;
}

int32_t SPVM_API_RUNTIME_get_type_basic_type_id(SPVM_RUNTIME* runtime, int32_t type_id) {
  
  SPVM_RUNTIME_TYPE* type = SPVM_API_RUNTIME_get_type(runtime, type_id);
  
  assert(type);
  
  int32_t type_basic_type_id = type->basic_type_id;
  
  return type_basic_type_id;
}

int32_t SPVM_API_RUNTIME_get_type_dimension(SPVM_RUNTIME* runtime, int32_t type_id) {
  
  SPVM_RUNTIME_TYPE* type = SPVM_API_RUNTIME_get_type(runtime, type_id);
  
  assert(type);
  
  int32_t type_dimension = type->dimension;
  
  return type_dimension;
}

int32_t SPVM_API_RUNTIME_get_type_stack_length(SPVM_RUNTIME* runtime, int32_t type_id) {
  
  SPVM_RUNTIME_TYPE* type = SPVM_API_RUNTIME_get_type(runtime, type_id);
  
  assert(type);
  
  int32_t type_stack_length = type->stack_length;
  
  return type_stack_length;
}

int32_t SPVM_API_RUNTIME_get_type_is_ref(SPVM_RUNTIME* runtime, int32_t type_id) {
  
  SPVM_RUNTIME_TYPE* type = SPVM_API_RUNTIME_get_type(runtime, type_id);
  
  assert(type);
  
  int32_t is_ref = type->flag & SPVM_NATIVE_C_TYPE_FLAG_REF;
  
  return is_ref;
}

int32_t SPVM_API_RUNTIME_get_type_flag(SPVM_RUNTIME* runtime, int32_t type_id) {
  
  SPVM_RUNTIME_TYPE* type = SPVM_API_RUNTIME_get_type(runtime, type_id);
  
  assert(type);
  
  int32_t type_flag = type->flag;
  
  return type_flag;
}

int32_t SPVM_API_RUNTIME_get_type_is_object(SPVM_RUNTIME* runtime, int32_t type_id) {
  
  SPVM_RUNTIME_TYPE* type = SPVM_API_RUNTIME_get_type(runtime, type_id);
  int32_t type_dimension = type->dimension;
  int32_t basic_type_id = type->basic_type_id;
  int32_t basic_type_category = SPVM_API_RUNTIME_get_basic_type_category(runtime, basic_type_id);
  
  assert(type);
  
  int32_t is_object;
  
  if (type_dimension == 0) {
    switch (basic_type_category) {
      case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_STRING:
      case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS:
      case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE:
      case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT:
      {
        is_object = 1;
        break;
      }
      default: {
        is_object = 0;
      }
    }
  }
  else if (type_dimension > 0) {
    is_object = 1;
  }
  else {
    assert(0);
  }
  
  return is_object;
}

SPVM_RUNTIME_CLASS* SPVM_API_RUNTIME_get_class_by_name(SPVM_RUNTIME* runtime, const char* class_name) {

  SPVM_RUNTIME_CLASS* class = (SPVM_RUNTIME_CLASS*)SPVM_HASH_get(runtime->class_symtable, class_name, strlen(class_name));
  
  return class;
}

int32_t SPVM_API_RUNTIME_get_class_id_by_name(SPVM_RUNTIME* runtime, const char* class_name) {

  SPVM_RUNTIME_CLASS* class = SPVM_HASH_get(runtime->class_symtable, class_name, strlen(class_name));

  int32_t class_id;
  if (class) {
    class_id = class->id;
  }
  else {
    class_id = -1;
  }

  return class_id;
}

int32_t SPVM_API_RUNTIME_get_class_name_id(SPVM_RUNTIME* runtime, int32_t class_id) {
  
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, class_id);
  
  assert(class);
  
  int32_t class_name_id = class->name_id;
  
  return class_name_id;
}

int32_t SPVM_API_RUNTIME_get_class_version_string_id(SPVM_RUNTIME* runtime, int32_t class_id) {
  
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, class_id);
  
  assert(class);
  
  int32_t class_version_string_id = class->version_string_id;
  
  return class_version_string_id;
}

int32_t SPVM_API_RUNTIME_get_class_is_pointer(SPVM_RUNTIME* runtime, int32_t class_id) {
  
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, class_id);
  
  assert(class);
  
  int32_t class_is_pointer = class->is_pointer;
  
  return class_is_pointer;
}

int32_t SPVM_API_RUNTIME_get_class_anon_methods_base_id(SPVM_RUNTIME* runtime, int32_t class_id) {
  
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, class_id);
  
  assert(class);
  
  int32_t class_anon_methods_base_id = class->anon_methods_base_id;
  
  return class_anon_methods_base_id;
}

int32_t SPVM_API_RUNTIME_get_class_anon_methods_length(SPVM_RUNTIME* runtime, int32_t class_id) {
  
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, class_id);
  
  assert(class);
  
  int32_t class_anon_methods_length = class->anon_methods_length;
  
  return class_anon_methods_length;
}

int32_t SPVM_API_RUNTIME_get_class_is_anon(SPVM_RUNTIME* runtime, int32_t class_id) {
  
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, class_id);
  
  assert(class);
  
  int32_t class_is_anon = class->is_anon;
  
  return class_is_anon;
}

int32_t SPVM_API_RUNTIME_get_class_class_rel_file_id(SPVM_RUNTIME* runtime, int32_t class_id) {
  
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, class_id);
  
  assert(class);
  
  int32_t class_class_rel_file_id = class->class_rel_file_id;
  
  return class_class_rel_file_id;
}

int32_t SPVM_API_RUNTIME_get_class_class_path_id(SPVM_RUNTIME* runtime, int32_t class_id) {
  
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, class_id);
  
  assert(class);
  
  int32_t class_class_path_id = class->class_path_id;
  
  return class_class_path_id;
}

int32_t SPVM_API_RUNTIME_get_class_fields_base_id(SPVM_RUNTIME* runtime, int32_t class_id) {
  
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, class_id);
  
  assert(class);
  
  int32_t class_fields_base_id = class->fields_base_id;
  
  return class_fields_base_id;
}

int32_t SPVM_API_RUNTIME_get_class_fields_length(SPVM_RUNTIME* runtime, int32_t class_id) {
  
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, class_id);
  
  assert(class);
  
  int32_t class_fields_length = class->fields_length;
  
  return class_fields_length;
}

int32_t SPVM_API_RUNTIME_get_class_methods_base_id(SPVM_RUNTIME* runtime, int32_t class_id) {
  
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, class_id);
  
  assert(class);
  
  int32_t class_methods_base_id = class->methods_base_id;
  
  return class_methods_base_id;
}

int32_t SPVM_API_RUNTIME_get_class_methods_length(SPVM_RUNTIME* runtime, int32_t class_id) {
  
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, class_id);
  // warn("GGG %d", class_id);
  assert(class);
  
  int32_t class_methods_length = class->methods_length;
  
  return class_methods_length;
}

int32_t SPVM_API_RUNTIME_get_class_class_vars_base_id(SPVM_RUNTIME* runtime, int32_t class_id) {
  
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, class_id);
  
  assert(class);
  
  int32_t class_class_vars_base_id = class->class_vars_base_id;
  
  return class_class_vars_base_id;
}

int32_t SPVM_API_RUNTIME_get_class_class_vars_length(SPVM_RUNTIME* runtime, int32_t class_id) {
  
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, class_id);
  
  assert(class);
  
  int32_t class_class_vars_length = class->class_vars_length;
  
  return class_class_vars_length;
}

int32_t SPVM_API_RUNTIME_get_class_parent_class_id(SPVM_RUNTIME* runtime, int32_t class_id) {
  
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, class_id);
  
  assert(class);
  
  int32_t class_parent_class_id = class->parent_class_id;
  
  return class_parent_class_id;
}

SPVM_RUNTIME_CLASS* SPVM_API_RUNTIME_get_class(SPVM_RUNTIME* runtime, int32_t class_id) {
  
  if (class_id < 0) {
    return NULL;
  }
  
  if (class_id >= runtime->classes_length) {
    return NULL;
  }

  SPVM_RUNTIME_CLASS* class = &runtime->classes[class_id];
  
  return class;
}

int32_t SPVM_API_RUNTIME_get_class_var_name_id(SPVM_RUNTIME* runtime, int32_t class_var_id) {
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var(runtime, class_var_id);

  assert(class_var);

  int32_t name_id = class_var->name_id;
  
  return name_id;
}

int32_t SPVM_API_RUNTIME_get_class_var_class_id(SPVM_RUNTIME* runtime, int32_t class_var_id) {
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var(runtime, class_var_id);

  assert(class_var);

  int32_t class_id = class_var->class_id;
  
  return class_id;
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

SPVM_RUNTIME_FIELD* SPVM_API_RUNTIME_get_field(SPVM_RUNTIME* runtime, int32_t field_id) {
  
  if (field_id < 0) {
    return NULL;
  }
  
  if (field_id >= runtime->fields_length) {
    return NULL;
  }

  SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
  
  return field;
}

int32_t SPVM_API_RUNTIME_get_field_class_id(SPVM_RUNTIME* runtime, int32_t field_id) {
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);

  assert(field);

  int32_t class_id = field->class_id;
  
  return class_id;
}

int32_t SPVM_API_RUNTIME_get_field_type_id(SPVM_RUNTIME* runtime, int32_t field_id) {
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);
  
  assert(field);
  
  int32_t field_type_id = field->type_id;
  
  return field_type_id;
}

int32_t SPVM_API_RUNTIME_get_field_name_id(SPVM_RUNTIME* runtime, int32_t field_id) {
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);
  
  assert(field);
  
  int32_t field_name_id = field->name_id;
  
  return field_name_id;
}

int32_t SPVM_API_RUNTIME_get_method_id_by_name(SPVM_RUNTIME* runtime, const char* class_name, const char* method_name) {
  (void)runtime;
  
  // Method ID
  int32_t method_id = -1;
  
  // Class
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class_by_name(runtime, class_name);
  if (class) {
    // Method
    SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method_by_class_id_and_method_name(runtime, class->id, method_name);
    if (method) {
      method_id = method->id;
    }
  }
  
  return method_id;
}

int32_t SPVM_API_RUNTIME_get_class_var_id_by_index(SPVM_RUNTIME* runtime, int32_t class_id, int32_t class_var_index) {
  
  int32_t class_var_id;
  
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, class_id);
  if (class) {
    if (class_var_index >= 0 && class_var_index < class->class_vars_length) {
      class_var_id = class->class_vars_base_id + class_var_index;
    }
    else {
      class_var_id = -1;
    }
  }
  else {
    class_var_id = -1;
  }
  
  return class_var_id;
}

int32_t SPVM_API_RUNTIME_get_class_var_id_by_name(SPVM_RUNTIME* runtime, const char* class_name, const char* class_var_name) {
  (void)runtime;
  
  // Method ID
  int32_t class_var_id;
  
  // Class
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class_by_name(runtime, class_name);
  if (class) {
    // Class variable
    SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var_by_class_id_and_class_var_name(runtime, class->id, class_var_name);
    if (class_var) {
      class_var_id = class_var->id;
    }
  }
  
  return class_var_id;
}

int32_t SPVM_API_RUNTIME_get_field_id_by_index(SPVM_RUNTIME* runtime, int32_t class_id, int32_t field_index) {
  
  int32_t field_id;
  
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, class_id);
  if (class) {
    if (field_index >= 0 && field_index < class->fields_length) {
      field_id = class->fields_base_id + field_index;
    }
    else {
      field_id = -1;
    }
  }
  else {
    field_id = -1;
  }
  
  return field_id;
}

int32_t SPVM_API_RUNTIME_get_field_id_by_name(SPVM_RUNTIME* runtime, const char* class_name, const char* field_name) {
  (void)runtime;
  
  // Method ID
  int32_t field_id;
  
  // Class
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class_by_name(runtime, class_name);
  if (class) {
    // Field
    SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field_by_class_id_and_field_name(runtime, class->id, field_name);
    if (field) {
      field_id = field->id;
    }
  }
  
  return field_id;
}

int32_t SPVM_API_RUNTIME_get_method_id_by_index(SPVM_RUNTIME* runtime, int32_t class_id, int32_t method_index) {
  
  int32_t method_id;
  
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, class_id);
  if (class) {
    if (method_index >= 0 && method_index < class->methods_length) {
      method_id = class->methods_base_id + method_index;
    }
    else {
      method_id = -1;
    }
  }
  else {
    method_id = -1;
  }
  
  return method_id;
}

SPVM_RUNTIME_METHOD* SPVM_API_RUNTIME_get_method_by_class_id_and_method_name(SPVM_RUNTIME* runtime, int32_t class_id, const char* search_method_name) {
  
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, class_id);
  
  SPVM_RUNTIME_METHOD* found_method = NULL;
  if (class->methods_length > 0) {
    // Performe binary searching because methods are sorted by the names
    int32_t cur_min_index = class->methods_base_id;
    int32_t cur_max_index = cur_min_index + class->methods_length - 1;
    
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

SPVM_RUNTIME_FIELD* SPVM_API_RUNTIME_get_field_by_class_id_and_field_name(SPVM_RUNTIME* runtime, int32_t class_id, const char* search_field_name) {
  
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, class_id);
  
  SPVM_RUNTIME_FIELD* found_field = NULL;
  if (class->fields_length > 0) {
    for (int32_t field_id = class->fields_base_id; field_id <  class->fields_base_id + class->fields_length; field_id++) {
      SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);
      const char* field_name = SPVM_API_RUNTIME_get_name(runtime, field->name_id);
      if (strcmp(field_name, search_field_name) == 0) {
        found_field = field;
        break;
      }
    }
  }
  
  return found_field;
}

SPVM_RUNTIME_CLASS_VAR* SPVM_API_RUNTIME_get_class_var_by_class_id_and_class_var_name(SPVM_RUNTIME* runtime, int32_t class_id, const char* search_class_var_name) {
  
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, class_id);
  
  SPVM_RUNTIME_CLASS_VAR* found_class_var = NULL;
  if (class->class_vars_length > 0) {
    for (int32_t class_var_id = class->class_vars_base_id; class_var_id <  class->class_vars_base_id + class->class_vars_length; class_var_id++) {
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

SPVM_RUNTIME_METHOD* SPVM_API_RUNTIME_get_method(SPVM_RUNTIME* runtime, int32_t method_id) {
  
  if (method_id < 0) {
    return NULL;
  }
  
  if (method_id >= runtime->methods_length) {
    return NULL;
  }

  SPVM_RUNTIME_METHOD* method = &runtime->methods[method_id];
  
  return method;
}

int32_t SPVM_API_RUNTIME_get_method_class_id(SPVM_RUNTIME* runtime, int32_t method_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_id);

  assert(method);

  int32_t class_id = method->class_id;
  
  return class_id;
}

int32_t SPVM_API_RUNTIME_get_method_opcodes_base_id(SPVM_RUNTIME* runtime, int32_t method_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_id);

  assert(method);

  int32_t opcodes_base_id = method->opcodes_base_id;
  
  return opcodes_base_id;
}

int32_t SPVM_API_RUNTIME_get_method_opcodes_length(SPVM_RUNTIME* runtime, int32_t method_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_id);

  assert(method);

  int32_t opcodes_length = method->opcodes_length;
  
  return opcodes_length;
}

int32_t SPVM_API_RUNTIME_get_method_name_id(SPVM_RUNTIME* runtime, int32_t method_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_id);

  assert(method);

  int32_t name_id = method->name_id;
  
  return name_id;
}

int32_t SPVM_API_RUNTIME_get_method_is_anon(SPVM_RUNTIME* runtime, int32_t method_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_id);

  assert(method);

  int32_t is_anon = method->is_anon;
  
  return is_anon;
}

int32_t SPVM_API_RUNTIME_get_method_is_native(SPVM_RUNTIME* runtime, int32_t method_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_id);
  
  return method->is_native;
}

int32_t SPVM_API_RUNTIME_get_method_is_precompile(SPVM_RUNTIME* runtime, int32_t method_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_id);
  return method->is_precompile;
}

int32_t SPVM_API_RUNTIME_get_method_is_enum(SPVM_RUNTIME* runtime, int32_t method_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_id);
  return method->is_enum;
}

int32_t SPVM_API_RUNTIME_get_method_args_length(SPVM_RUNTIME* runtime, int32_t method_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_id);

  assert(method);

  int32_t args_length = method->args_length;
  
  return args_length;
}

int32_t SPVM_API_RUNTIME_get_method_required_args_length(SPVM_RUNTIME* runtime, int32_t method_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_id);
  
  assert(method);
  
  int32_t required_args_length = method->required_args_length;
  
  return required_args_length;
}

int32_t SPVM_API_RUNTIME_get_method_args_base_id(SPVM_RUNTIME* runtime, int32_t method_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_id);

  assert(method);

  int32_t args_base_id = method->args_base_id;
  
  return args_base_id;
}

int32_t SPVM_API_RUNTIME_get_method_is_class_method(SPVM_RUNTIME* runtime, int32_t method_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_id);
  
  assert(method);
  
  int32_t is_class_method = method->is_class_method;
  
  return is_class_method;
}

int32_t SPVM_API_RUNTIME_get_method_return_type_id(SPVM_RUNTIME* runtime, int32_t method_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_id);
  
  assert(method);
  
  int32_t return_type_id = method->return_type_id;
  
  return return_type_id;
}

int32_t SPVM_API_RUNTIME_get_method_call_stack_byte_vars_length(SPVM_RUNTIME* runtime, int32_t method_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_id);
  
  assert(method);
  
  int32_t call_stack_byte_vars_length = method->call_stack_byte_vars_length;
  
  return call_stack_byte_vars_length;
}

int32_t SPVM_API_RUNTIME_get_method_call_stack_short_vars_length(SPVM_RUNTIME* runtime, int32_t method_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_id);
  
  assert(method);
  
  int32_t call_stack_short_vars_length = method->call_stack_short_vars_length;
  
  return call_stack_short_vars_length;
}

int32_t SPVM_API_RUNTIME_get_method_call_stack_int_vars_length(SPVM_RUNTIME* runtime, int32_t method_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_id);
  
  assert(method);
  
  int32_t call_stack_int_vars_length = method->call_stack_int_vars_length;
  
  return call_stack_int_vars_length;
}

int32_t SPVM_API_RUNTIME_get_method_call_stack_long_vars_length(SPVM_RUNTIME* runtime, int32_t method_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_id);
  
  assert(method);
  
  int32_t call_stack_long_vars_length = method->call_stack_long_vars_length;
  
  return call_stack_long_vars_length;
}

int32_t SPVM_API_RUNTIME_get_method_call_stack_float_vars_length(SPVM_RUNTIME* runtime, int32_t method_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_id);
  
  assert(method);
  
  int32_t call_stack_float_vars_length = method->call_stack_float_vars_length;
  
  return call_stack_float_vars_length;
}

int32_t SPVM_API_RUNTIME_get_method_call_stack_double_vars_length(SPVM_RUNTIME* runtime, int32_t method_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_id);
  
  assert(method);
  
  int32_t call_stack_double_vars_length = method->call_stack_double_vars_length;
  
  return call_stack_double_vars_length;
}

int32_t SPVM_API_RUNTIME_get_method_call_stack_object_vars_length(SPVM_RUNTIME* runtime, int32_t method_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_id);
  
  assert(method);
  
  int32_t call_stack_object_vars_length = method->call_stack_object_vars_length;
  
  return call_stack_object_vars_length;
}

int32_t SPVM_API_RUNTIME_get_method_call_stack_ref_vars_length(SPVM_RUNTIME* runtime, int32_t method_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_id);
  
  assert(method);
  
  int32_t call_stack_ref_vars_length = method->call_stack_ref_vars_length;
  
  return call_stack_ref_vars_length;
}

int32_t SPVM_API_RUNTIME_get_method_mortal_stack_length(SPVM_RUNTIME* runtime, int32_t method_id) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_id);
  
  assert(method);
  
  int32_t mortal_stack_length = method->mortal_stack_length;
  
  return mortal_stack_length;
}

int32_t SPVM_API_RUNTIME_get_arg_type_id(SPVM_RUNTIME* runtime, int32_t arg_id) {

  int32_t arg_type_id = runtime->arg_type_ids[arg_id];
  
  return arg_type_id;
}

int32_t SPVM_API_RUNTIME_get_anon_method_method_id(SPVM_RUNTIME* runtime, int32_t anon_method_id) {

  int32_t anon_method_method_id = runtime->anon_method_method_ids[anon_method_id];
  
  return anon_method_method_id;
}

void SPVM_API_RUNTIME_set_native_method_address(SPVM_RUNTIME* runtime, int32_t method_id, void* address) {

  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_id);
  
  runtime->method_native_addresses[method->id] = address;
}

void SPVM_API_RUNTIME_set_precompile_method_address(SPVM_RUNTIME* runtime, int32_t method_id, void* address) {

  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_id);
  
  runtime->method_precompile_addresses[method->id] = address;
}

void* SPVM_API_RUNTIME_get_native_method_address(SPVM_RUNTIME* runtime, int32_t method_id) {

  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_id);
  
  void* native_method_address = runtime->method_native_addresses[method->id];
  
  return native_method_address;
}

void* SPVM_API_RUNTIME_get_precompile_method_address(SPVM_RUNTIME* runtime, int32_t method_id) {

  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_id);
  
  void* precompile_method_address = runtime->method_precompile_addresses[method->id];
  
  return precompile_method_address;
}

int32_t SPVM_API_RUNTIME_has_interface_by_id(SPVM_RUNTIME* runtime, int32_t class_basic_type_id, int32_t interface_basic_type_id) {

  SPVM_RUNTIME_BASIC_TYPE* class_basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, class_basic_type_id);
  SPVM_RUNTIME_BASIC_TYPE* interface_basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, interface_basic_type_id);
  
  if (class_basic_type->class_id < 0) {
    return 0;
  }
  
  if (interface_basic_type->class_id < 0) {
    return 0;
  }
  
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, class_basic_type->class_id);
  SPVM_RUNTIME_CLASS* interface = SPVM_API_RUNTIME_get_class(runtime, interface_basic_type->class_id);
  
  assert(interface->required_method_id >= 0);
  
  SPVM_RUNTIME_METHOD* method_interface = SPVM_API_RUNTIME_get_method(runtime, interface->required_method_id);
  
  const char* method_interface_name =  SPVM_API_RUNTIME_get_constant_string_value(runtime, method_interface->name_id, NULL);
  
  SPVM_RUNTIME_METHOD* found_method = SPVM_API_RUNTIME_get_method_by_class_id_and_method_name(runtime, class->id, method_interface_name);
  if (found_method) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_API_RUNTIME_is_super_class_by_id(SPVM_RUNTIME* runtime, int32_t super_class_basic_type_id, int32_t child_class_basic_type_id) {

  int32_t is_super_class = 0;
  
  SPVM_RUNTIME_BASIC_TYPE* super_class_basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, super_class_basic_type_id);
  SPVM_RUNTIME_BASIC_TYPE* child_class_basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, child_class_basic_type_id);
  
  if (super_class_basic_type->class_id < 0) {
    return 0;
  }
  
  if (child_class_basic_type->class_id < 0) {
    return 0;
  }
  
  SPVM_RUNTIME_CLASS* super_class = SPVM_API_RUNTIME_get_class(runtime, super_class_basic_type->class_id);
  SPVM_RUNTIME_CLASS* child_class = SPVM_API_RUNTIME_get_class(runtime, child_class_basic_type->class_id);
  
  int32_t parent_class_id = child_class->parent_class_id;
  while (1) {
    if (parent_class_id > 0) {
      SPVM_RUNTIME_CLASS* parent_class = SPVM_API_RUNTIME_get_class(runtime, parent_class_id);
      if (parent_class->id == super_class->id) {
        is_super_class = 1;
        break;
      }
      else {
        parent_class_id = parent_class->parent_class_id;
      }
    }
    else {
      is_super_class = 0;
      break;
    }
  }
  
  return is_super_class;
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
