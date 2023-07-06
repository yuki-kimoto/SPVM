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
































































SPVM_ENV_RUNTIME* SPVM_API_RUNTIME_new_env() {
  
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
    SPVM_API_RUNTIME_get_basic_type_name,
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
    SPVM_API_RUNTIME_get_class_var,
    NULL, // reserved33,
    SPVM_API_RUNTIME_get_class_var_name,
    NULL, // reserved35
    NULL, // reserved36,
    NULL, // reserved37,
    SPVM_API_RUNTIME_get_field_name,
    NULL, // reserved39
    NULL, // reserved40
    NULL, // reserved41
    NULL, // reserved42
    SPVM_API_RUNTIME_get_method_name,
    NULL, // reserved44,
    NULL, // reserved45,
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
    SPVM_API_RUNTIME_get_method_opcodes_base,
    SPVM_API_RUNTIME_get_method_opcodes_length,
    SPVM_API_RUNTIME_get_method_args_base,
    SPVM_API_RUNTIME_get_method_args_length,
    NULL, // reserved63
    NULL, // reserved64
    SPVM_API_RUNTIME_get_native_method_address,
    SPVM_API_RUNTIME_set_native_method_address,
    SPVM_API_RUNTIME_get_precompile_method_address,
    SPVM_API_RUNTIME_set_precompile_method_address,
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
    SPVM_API_RUNTIME_get_method_required_args_length,
    NULL, // reserved80
    SPVM_API_RUNTIME_get_method_is_enum,
    NULL, // reserved82
    SPVM_API_RUNTIME_is_object_type,
    NULL, // reserved84
    NULL, // reserved85
    SPVM_API_RUNTIME_can_assign,
    SPVM_API_RUNTIME_get_basic_type_module_rel_file,
    SPVM_API_RUNTIME_get_basic_type_module_dir,
    SPVM_API_RUNTIME_get_basic_type_is_anon,
    SPVM_API_RUNTIME_get_basic_type_fields_base,
    SPVM_API_RUNTIME_get_basic_type_fields_length,
    SPVM_API_RUNTIME_get_basic_type_methods_base,
    SPVM_API_RUNTIME_get_basic_type_methods_length,
    SPVM_API_RUNTIME_get_basic_type_class_vars_base,
    SPVM_API_RUNTIME_get_basic_type_class_vars_length,
    NULL, // reserved96
    NULL, // reserved97
    NULL, // reserved98
    SPVM_API_RUNTIME_get_basic_types_length,
    SPVM_API_RUNTIME_get_field_basic_type,
    SPVM_API_RUNTIME_get_field_type_dimension,
    SPVM_API_RUNTIME_get_field_type_flag,
    SPVM_API_RUNTIME_get_class_var_basic_type,
    SPVM_API_RUNTIME_get_class_var_type_dimension,
    SPVM_API_RUNTIME_get_class_var_type_flag,
    SPVM_API_RUNTIME_get_method_return_basic_type,
    SPVM_API_RUNTIME_get_method_return_type_dimension,
    SPVM_API_RUNTIME_get_method_return_type_flag,
    SPVM_API_RUNTIME_get_arg_basic_type,
    SPVM_API_RUNTIME_get_arg_type_dimension,
    SPVM_API_RUNTIME_get_arg_type_flag,
    SPVM_API_RUNTIME_get_method_current_basic_type,
    SPVM_API_RUNTIME_get_field_current_basic_type,
    SPVM_API_RUNTIME_get_class_var_current_basic_type,
    SPVM_API_RUNTIME_get_basic_type_parent,
    SPVM_API_RUNTIME_get_basic_type_version_string,
    SPVM_API_RUNTIME_get_basic_type_by_id,
    SPVM_API_RUNTIME_get_field,
    SPVM_API_RUNTIME_get_method,
    NULL, // reserved120,
    NULL, // reserved121
    SPVM_API_RUNTIME_get_class_var_by_name,
    SPVM_API_RUNTIME_get_field_by_name,
    SPVM_API_RUNTIME_get_method_by_name,
    SPVM_API_RUNTIME_get_basic_type_id,
    NULL, // reserved126
    SPVM_API_RUNTIME_get_method_index,
    NULL, // reserved128,
    SPVM_API_RUNTIME_get_class_var_index,
    SPVM_API_RUNTIME_get_field_index,
    SPVM_API_RUNTIME_get_field_offset,
    SPVM_API_RUNTIME_get_arg,
    SPVM_API_RUNTIME_get_basic_type_by_name,
    SPVM_API_RUNTIME_get_basic_type_anon_basic_type,
    SPVM_API_PRECOMPILE_build_precompile_module_source,
    SPVM_API_PRECOMPILE_build_precompile_method_source,
  };
  SPVM_ENV_RUNTIME* env_runtime = calloc(1, sizeof(env_runtime_init));
  memcpy(env_runtime, env_runtime_init, sizeof(env_runtime_init));
  
  return env_runtime;
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
  int32_t basic_type_id = basic_type->id;
  
  return basic_type_id;
}

const char* SPVM_API_RUNTIME_get_basic_type_constant_string_value_nolen(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t constant_string_index) {
  
  const char* constant_string_value = SPVM_API_RUNTIME_get_basic_type_constant_string_value(runtime, basic_type, constant_string_index, NULL);
  
  return constant_string_value;
}

const char* SPVM_API_RUNTIME_get_basic_type_constant_string_value(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t constant_string_index, int32_t* string_length) {
  if (constant_string_index < 0) {
    return NULL;
  }
  
  SPVM_RUNTIME_STRING* constant_string = &basic_type->constant_strings[constant_string_index];
  
  const char* constant_string_value = constant_string->value;
  
  if (string_length) {
    *string_length = constant_string->length;
  }
  
  return constant_string_value;
}

int32_t SPVM_API_RUNTIME_get_basic_type_category(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  int32_t basic_type_category = basic_type->category;
  
  return basic_type_category;
}

const char* SPVM_API_RUNTIME_get_basic_type_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  const char* basic_type_name = SPVM_API_RUNTIME_get_basic_type_constant_string_value_nolen(runtime, basic_type, basic_type->name_string_index);
  
  return basic_type_name;
}

const char* SPVM_API_RUNTIME_get_basic_type_version_string(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  const char* version_string = SPVM_API_RUNTIME_get_basic_type_constant_string_value_nolen(runtime, basic_type, basic_type->version_string_string_index);
  
  return version_string;
}

int32_t SPVM_API_RUNTIME_get_basic_type_is_pointer(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  int32_t is_pointer = basic_type->is_pointer;
  
  return is_pointer;
}

int32_t SPVM_API_RUNTIME_get_basic_type_anon_basic_types_base(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  int32_t anon_basic_types_base = basic_type->anon_basic_types_base;
  
  return anon_basic_types_base;
}

int32_t SPVM_API_RUNTIME_get_basic_type_anon_basic_types_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  int32_t anon_basic_types_length = basic_type->anon_basic_types_length;
  
  return anon_basic_types_length;
}

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_basic_type_anon_basic_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t anon_basic_type_index) {
  
  SPVM_RUNTIME_BASIC_TYPE* anon_basic_type = &basic_type->anon_basic_types[anon_basic_type_index];
  
  return anon_basic_type;
}

int32_t SPVM_API_RUNTIME_get_basic_type_is_anon(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  int32_t is_anon = basic_type->is_anon;
  
  return is_anon;
}

const char* SPVM_API_RUNTIME_get_basic_type_module_rel_file(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  const char* module_rel_file = SPVM_API_RUNTIME_get_basic_type_constant_string_value_nolen(runtime, basic_type, basic_type->module_rel_file_string_index);
  
  return module_rel_file;
}

const char* SPVM_API_RUNTIME_get_basic_type_module_dir(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  const char* module_dir = SPVM_API_RUNTIME_get_basic_type_constant_string_value_nolen(runtime, basic_type, basic_type->module_dir_string_index);
  
  return module_dir;
}

int32_t SPVM_API_RUNTIME_get_basic_type_fields_base(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  int32_t fields_base = basic_type->fields_base;
  
  return fields_base;
}

int32_t SPVM_API_RUNTIME_get_basic_type_fields_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  int32_t fields_length = basic_type->fields_length;
  
  return fields_length;
}

int32_t SPVM_API_RUNTIME_get_basic_type_methods_base(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  int32_t methods_base = basic_type->methods_base;
  
  return methods_base;
}

int32_t SPVM_API_RUNTIME_get_basic_type_methods_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  int32_t methods_length = basic_type->methods_length;
  
  return methods_length;
}

int32_t SPVM_API_RUNTIME_get_basic_type_class_vars_base(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  int32_t class_vars_base = basic_type->class_vars_base;
  
  return class_vars_base;
}

int32_t SPVM_API_RUNTIME_get_basic_type_class_vars_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  int32_t class_vars_length = basic_type->class_vars_length;
  
  return class_vars_length;
}

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_basic_type_parent(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  int32_t parent_basic_type_id = basic_type->parent_id;
  
  SPVM_RUNTIME_BASIC_TYPE* parent_basic_type = SPVM_API_RUNTIME_get_basic_type_by_id(runtime, parent_basic_type_id);
  
  return parent_basic_type;
}

SPVM_RUNTIME_CLASS_VAR* SPVM_API_RUNTIME_get_class_var(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t class_var_index) {
  
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
      SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var(runtime, basic_type, class_var_index);
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
  
  int32_t index = class_var->index;
  
  return index;
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
  
  int32_t type_dimension = class_var->type_dimension;
  
  return type_dimension;
}

int32_t SPVM_API_RUNTIME_get_class_var_type_flag(SPVM_RUNTIME* runtime, SPVM_RUNTIME_CLASS_VAR* class_var) {
  
  int32_t type_flag = class_var->type_flag;
  
  return type_flag;
}

SPVM_RUNTIME_FIELD* SPVM_API_RUNTIME_get_field(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t field_index) {
  
  if (field_index < 0) {
    return NULL;
  }
  
  if (field_index >= basic_type->fields_length) {
    return NULL;
  }
  
  SPVM_RUNTIME_FIELD* field = &basic_type->fields[field_index];
  
  return field;
}

SPVM_RUNTIME_FIELD* SPVM_API_RUNTIME_get_field_by_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, const char* field_name) {
  
  SPVM_RUNTIME_FIELD* found_field = NULL;
  if (basic_type->fields_length > 0) {
    for (int32_t field_index = 0; field_index <  basic_type->fields_length; field_index++) {
      SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, basic_type, field_index);
      const char* field_name_current = SPVM_API_RUNTIME_get_field_name(runtime, field);
      if (strcmp(field_name_current, field_name) == 0) {
        found_field = field;
        break;
      }
    }
  }
  
  return found_field;
}

int32_t SPVM_API_RUNTIME_get_field_index(SPVM_RUNTIME* runtime, SPVM_RUNTIME_FIELD* field) {
  
  
  return field->index;
}

int32_t SPVM_API_RUNTIME_get_field_offset(SPVM_RUNTIME* runtime, SPVM_RUNTIME_FIELD* field) {
  
  return field->offset;
}

const char* SPVM_API_RUNTIME_get_field_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_FIELD* field) {
  
  return field->name;
}

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_field_current_basic_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_FIELD* field) {
  
  return field->current_basic_type;
}

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_field_basic_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_FIELD* field) {
  
  return field->basic_type;
}

int32_t SPVM_API_RUNTIME_get_field_type_dimension(SPVM_RUNTIME* runtime, SPVM_RUNTIME_FIELD* field) {
  
  return field->type_dimension;
}

int32_t SPVM_API_RUNTIME_get_field_type_flag(SPVM_RUNTIME* runtime, SPVM_RUNTIME_FIELD* field) {
  
  return  field->type_flag;
}

SPVM_RUNTIME_METHOD* SPVM_API_RUNTIME_get_method(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t method_index) {
  
  if (method_index < 0) {
    return NULL;
  }
  
  if (method_index >= basic_type->methods_length) {
    return NULL;
  }
  
  SPVM_RUNTIME_METHOD* method = &basic_type->methods[method_index];
  
  return method;
}

SPVM_RUNTIME_METHOD* SPVM_API_RUNTIME_get_method_by_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, const char* method_name) {
  
  SPVM_RUNTIME_METHOD* found_method = NULL;
  if (basic_type->methods_length > 0) {
    // Performe binary searching because methods are sorted by the names
    int32_t cur_min_index = 0;
    int32_t cur_max_index = basic_type->methods_length - 1;
    
    while (1) {
      if (cur_max_index < cur_min_index) {
        break;
      }
      
      int32_t cur_half_index = cur_min_index +(cur_max_index - cur_min_index) / 2;
      
      SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, basic_type, cur_half_index);
      const char* cur_half_method_name = SPVM_API_RUNTIME_get_method_name(runtime, method);
      
      int32_t cmp_result = strcmp(method_name, cur_half_method_name);
      
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

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_method_current_basic_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  int32_t current_basic_type_id = method->current_basic_type_id;
  
  SPVM_RUNTIME_BASIC_TYPE* current_basic_type = SPVM_API_RUNTIME_get_basic_type_by_id(runtime, current_basic_type_id);
  
  return current_basic_type;
}

int32_t SPVM_API_RUNTIME_get_method_opcodes_base(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  int32_t opcodes_base = method->opcodes_base;
  
  return opcodes_base;
}

int32_t SPVM_API_RUNTIME_get_method_opcodes_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  int32_t opcodes_length = method->opcodes_length;
  
  return opcodes_length;
}

int32_t SPVM_API_RUNTIME_get_method_index(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  int32_t index = method->index;
  
  return index;
}

const char* SPVM_API_RUNTIME_get_method_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  const char* method_name = SPVM_API_RUNTIME_get_basic_type_constant_string_value_nolen(runtime, SPVM_API_RUNTIME_get_method_current_basic_type(runtime, method), method->name_string_index);
  
  return method_name;
}

int32_t SPVM_API_RUNTIME_get_method_is_anon(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  int32_t is_anon = method->is_anon;
  
  return is_anon;
}

int32_t SPVM_API_RUNTIME_get_method_is_native(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  return method->is_native;
}

int32_t SPVM_API_RUNTIME_get_method_is_precompile(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  return method->is_precompile;
}

int32_t SPVM_API_RUNTIME_get_method_is_enum(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  return method->is_enum;
}

int32_t SPVM_API_RUNTIME_get_method_args_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  int32_t args_length = method->args_length;
  
  return args_length;
}

int32_t SPVM_API_RUNTIME_get_method_required_args_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  int32_t required_args_length = method->required_args_length;
  
  return required_args_length;
}

int32_t SPVM_API_RUNTIME_get_method_args_base(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  int32_t args_base = method->args_base;
  
  return args_base;
}

int32_t SPVM_API_RUNTIME_get_method_is_class_method(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  int32_t is_class_method = method->is_class_method;
  
  return is_class_method;
}

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_method_return_basic_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  int32_t return_basic_type_id = method->return_basic_type_id;
  
  SPVM_RUNTIME_BASIC_TYPE* return_basic_type = SPVM_API_RUNTIME_get_basic_type_by_id(runtime, return_basic_type_id);
  
  return return_basic_type;
}

int32_t SPVM_API_RUNTIME_get_method_return_type_dimension(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  int32_t return_type_dimension = method->return_type_dimension;
  
  return return_type_dimension;
}

int32_t SPVM_API_RUNTIME_get_method_return_type_flag(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  int32_t return_type_flag = method->return_type_flag;
  
  return return_type_flag;
}

int32_t SPVM_API_RUNTIME_get_method_call_stack_byte_vars_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  int32_t call_stack_byte_vars_length = method->call_stack_byte_vars_length;
  
  return call_stack_byte_vars_length;
}

int32_t SPVM_API_RUNTIME_get_method_call_stack_short_vars_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  int32_t call_stack_short_vars_length = method->call_stack_short_vars_length;
  
  return call_stack_short_vars_length;
}

int32_t SPVM_API_RUNTIME_get_method_call_stack_int_vars_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  int32_t call_stack_int_vars_length = method->call_stack_int_vars_length;
  
  return call_stack_int_vars_length;
}

int32_t SPVM_API_RUNTIME_get_method_call_stack_long_vars_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  int32_t call_stack_long_vars_length = method->call_stack_long_vars_length;
  
  return call_stack_long_vars_length;
}

int32_t SPVM_API_RUNTIME_get_method_call_stack_float_vars_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  int32_t call_stack_float_vars_length = method->call_stack_float_vars_length;
  
  return call_stack_float_vars_length;
}

int32_t SPVM_API_RUNTIME_get_method_call_stack_double_vars_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  int32_t call_stack_double_vars_length = method->call_stack_double_vars_length;
  
  return call_stack_double_vars_length;
}

int32_t SPVM_API_RUNTIME_get_method_call_stack_object_vars_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  int32_t call_stack_object_vars_length = method->call_stack_object_vars_length;
  
  return call_stack_object_vars_length;
}

int32_t SPVM_API_RUNTIME_get_method_call_stack_ref_vars_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  int32_t call_stack_ref_vars_length = method->call_stack_ref_vars_length;
  
  return call_stack_ref_vars_length;
}

int32_t SPVM_API_RUNTIME_get_method_mortal_stack_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  int32_t mortal_stack_length = method->mortal_stack_length;
  
  return mortal_stack_length;
}

SPVM_RUNTIME_ARG* SPVM_API_RUNTIME_get_arg(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method, int32_t arg_index) {
  
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
  
  int32_t type_dimension = arg->type_dimension;
  
  return type_dimension;
}

int32_t SPVM_API_RUNTIME_get_arg_type_flag(SPVM_RUNTIME* runtime, SPVM_RUNTIME_ARG* arg) {
  
  int32_t type_flag = arg->type_flag;
  
  return type_flag;
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

int32_t SPVM_API_RUNTIME_has_interface_by_id(SPVM_RUNTIME* runtime, int32_t basic_type_id, int32_t interface_basic_type_id) {

  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type_by_id(runtime, basic_type_id);
  SPVM_RUNTIME_BASIC_TYPE* interface_basic_type = SPVM_API_RUNTIME_get_basic_type_by_id(runtime, interface_basic_type_id);
  
  if (!(basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS || basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE)) {
    return 0;
  }
  
  if (!(interface_basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS || interface_basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE)) {
    return 0;
  }
  
  SPVM_RUNTIME_METHOD* method_interface = SPVM_API_RUNTIME_get_method(runtime, interface_basic_type, interface_basic_type->required_method_index);
  
  const char* method_interface_name =  SPVM_API_RUNTIME_get_basic_type_constant_string_value(runtime, SPVM_API_RUNTIME_get_method_current_basic_type(runtime, method_interface), method_interface->name_string_index, NULL);
  
  SPVM_RUNTIME_METHOD* found_method = SPVM_API_RUNTIME_get_method_by_name(runtime, basic_type, method_interface_name);
  if (found_method) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_API_RUNTIME_has_interface(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, SPVM_RUNTIME_BASIC_TYPE* interface_basic_type) {

  if (!(basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS || basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE)) {
    return 0;
  }
  
  if (!(interface_basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS || interface_basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE)) {
    return 0;
  }
  
  SPVM_RUNTIME_METHOD* method_interface = SPVM_API_RUNTIME_get_method(runtime, interface_basic_type, interface_basic_type->required_method_index);
  
  const char* method_interface_name =  SPVM_API_RUNTIME_get_basic_type_constant_string_value(runtime, SPVM_API_RUNTIME_get_method_current_basic_type(runtime, method_interface), method_interface->name_string_index, NULL);
  
  SPVM_RUNTIME_METHOD* found_method = SPVM_API_RUNTIME_get_method_by_name(runtime, basic_type, method_interface_name);
  if (found_method) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_API_RUNTIME_is_super(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* super_basic_type, SPVM_RUNTIME_BASIC_TYPE* child_basic_type) {

  int32_t is_super_basic_type = 0;
  
  if (!(super_basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS)) {
    return 0;
  }
  
  if (!(child_basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS)) {
    return 0;
  }
  
  int32_t parent_basic_type_id = child_basic_type->parent_id;
  while (1) {
    if (parent_basic_type_id > 0) {
      SPVM_RUNTIME_BASIC_TYPE* parent_basic_type = SPVM_API_RUNTIME_get_basic_type_by_id(runtime, parent_basic_type_id);
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

int32_t SPVM_API_RUNTIME_is_object_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t flag) {
  
  int32_t is_object_type;
  if (type_dimension == 0) {
    int32_t basic_type_category = SPVM_API_RUNTIME_get_basic_type_category(runtime, basic_type);
    
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
  
  int32_t dist_basic_type_category = SPVM_API_RUNTIME_get_basic_type_category(runtime, dist_basic_type);
  int32_t src_basic_type_category = SPVM_API_RUNTIME_get_basic_type_category(runtime, src_basic_type);
  
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
      isa = SPVM_API_RUNTIME_has_interface(runtime, src_basic_type, dist_basic_type);
    }
    else if (dist_basic_type_category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS) {
      isa = SPVM_API_RUNTIME_is_super(runtime, dist_basic_type, src_basic_type);
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

void SPVM_API_PRECOMPILE_build_precompile_module_source(SPVM_RUNTIME* runtime, SPVM_STRING_BUFFER* string_buffer, const char* module_name) {
  SPVM_PRECOMPILE* precompile = SPVM_PRECOMPILE_new(precompile);
  SPVM_PRECOMPILE_set_runtime(precompile, runtime);
  SPVM_PRECOMPILE_build_module_source(precompile, string_buffer, module_name);
  SPVM_PRECOMPILE_free(precompile);
}

void SPVM_API_PRECOMPILE_build_precompile_method_source(SPVM_RUNTIME* runtime, SPVM_STRING_BUFFER* string_buffer, const char* module_name, const char* method_name) {
  SPVM_PRECOMPILE* precompile = SPVM_PRECOMPILE_new(precompile);
  SPVM_PRECOMPILE_set_runtime(precompile, runtime);
  SPVM_PRECOMPILE_build_method_source(precompile, string_buffer, module_name, method_name);
  SPVM_PRECOMPILE_free(precompile);
}
