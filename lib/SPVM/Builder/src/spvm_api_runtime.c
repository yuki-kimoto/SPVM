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

#include "spvm_list.h"
#include "spvm_hash.h"

#include "spvm_opcode.h"
#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_class.h"
#include "spvm_runtime_class_var.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime.h"
#include "spvm_runtime_manager.h"
#include "spvm_runtime_method.h"
#include "spvm_runtime_string.h"
#include "spvm_runtime_type.h"
#include "spvm_api_runtime.h"

SPVM_RUNTIME* SPVM_API_RUNTIME_new_runtime() {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_new();
  
  return runtime;
}

void SPVM_API_RUNTIME_prepare(SPVM_RUNTIME* runtime) {

  SPVM_RUNTIME_prepare(runtime);
}

void SPVM_API_RUNTIME_free_runtime(SPVM_RUNTIME* runtime) {

  SPVM_RUNTIME_free(runtime);
}

SPVM_OPCODE* SPVM_API_RUNTIME_get_opcodes(SPVM_RUNTIME* runtime) {

  return runtime->opcodes;
}

int32_t SPVM_API_RUNTIME_get_opcode_ids_length(SPVM_RUNTIME* runtime) {
  
  return runtime->opcode_ids_length;
}

int32_t SPVM_API_RUNTIME_get_basic_type_id(SPVM_RUNTIME* runtime, const char* basic_type_name) {
  (void)runtime;
  
  if (basic_type_name == NULL) {
    return -1;
  }
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type_with_name(runtime, basic_type_name);
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
  
  SPVM_RUNTIME_STRING* basic_type_name_string = (SPVM_RUNTIME_STRING*)&runtime->strings[basic_type->name_id];

  const char* basic_type_name = (const char*)&runtime->string_buffer[basic_type_name_string->string_buffer_id];
  
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

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_basic_type_with_name(SPVM_RUNTIME* runtime, const char* basic_type_name) {

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

int32_t SPVM_API_RUNTIME_get_type_width(SPVM_RUNTIME* runtime, int32_t type_id) {
  
  SPVM_RUNTIME_TYPE* type = SPVM_API_RUNTIME_get_type(runtime, type_id);
  
  assert(type);
  
  int32_t type_width = type->width;
  
  return type_width;
}

int32_t SPVM_API_RUNTIME_get_type_is_ref(SPVM_RUNTIME* runtime, int32_t type_id) {
  
  SPVM_RUNTIME_TYPE* type = SPVM_API_RUNTIME_get_type(runtime, type_id);
  
  assert(type);
  
  int32_t is_ref = type->flag & SPVM_TYPE_C_FLAG_REF;
  
  return is_ref;
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
      case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CALLBACK:
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

int32_t SPVM_API_RUNTIME_get_class_id(SPVM_RUNTIME* runtime, const char* class_name) {

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

int32_t SPVM_API_RUNTIME_get_class_anon_method_ids_base(SPVM_RUNTIME* runtime, int32_t class_id) {
  
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, class_id);
  
  assert(class);
  
  int32_t class_anon_method_ids_base = class->anon_method_ids_base;
  
  return class_anon_method_ids_base;
}

int32_t SPVM_API_RUNTIME_get_class_anon_method_ids_length(SPVM_RUNTIME* runtime, int32_t class_id) {
  
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, class_id);
  
  assert(class);
  
  int32_t class_anon_method_method_ids_length = class->anon_method_ids_length;
  
  return class_anon_method_method_ids_length;
}

int32_t SPVM_API_RUNTIME_get_class_is_anon(SPVM_RUNTIME* runtime, int32_t class_id) {
  
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, class_id);
  
  assert(class);
  
  int32_t class_is_anon = class->is_anon;
  
  return class_is_anon;
}

int32_t SPVM_API_RUNTIME_get_class_module_file_id(SPVM_RUNTIME* runtime, int32_t class_id) {
  
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, class_id);
  
  assert(class);
  
  int32_t class_module_file_id = class->module_file_id;
  
  return class_module_file_id;
}

int32_t SPVM_API_RUNTIME_get_class_field_ids_base(SPVM_RUNTIME* runtime, int32_t class_id) {
  
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, class_id);
  
  assert(class);
  
  int32_t class_field_ids_base = class->field_ids_base;
  
  return class_field_ids_base;
}

int32_t SPVM_API_RUNTIME_get_class_field_ids_length(SPVM_RUNTIME* runtime, int32_t class_id) {
  
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, class_id);
  
  assert(class);
  
  int32_t class_field_ids_length = class->field_ids_length;
  
  return class_field_ids_length;
}

int32_t SPVM_API_RUNTIME_get_class_method_ids_base(SPVM_RUNTIME* runtime, int32_t class_id) {
  
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, class_id);
  
  assert(class);
  
  int32_t class_method_ids_base = class->method_ids_base;
  
  return class_method_ids_base;
}

int32_t SPVM_API_RUNTIME_get_class_method_ids_length(SPVM_RUNTIME* runtime, int32_t class_id) {
  
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, class_id);
  
  assert(class);
  
  int32_t class_method_ids_length = class->method_ids_length;
  
  return class_method_ids_length;
}

int32_t SPVM_API_RUNTIME_get_class_class_var_ids_base(SPVM_RUNTIME* runtime, int32_t class_id) {
  
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, class_id);
  
  assert(class);
  
  int32_t class_class_var_ids_base = class->class_var_ids_base;
  
  return class_class_var_ids_base;
}

int32_t SPVM_API_RUNTIME_get_class_class_var_ids_length(SPVM_RUNTIME* runtime, int32_t class_id) {
  
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, class_id);
  
  assert(class);
  
  int32_t class_class_var_ids_length = class->class_var_ids_length;
  
  return class_class_var_ids_length;
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

int32_t SPVM_API_RUNTIME_get_class_var_signature_id(SPVM_RUNTIME* runtime, int32_t class_var_id) {
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var(runtime, class_var_id);

  assert(class_var);

  int32_t signature_id = class_var->signature_id;
  
  return signature_id;
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

int32_t SPVM_API_RUNTIME_get_field_signature_id(SPVM_RUNTIME* runtime, int32_t field_id) {
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);

  assert(field);

  int32_t signature_id = field->signature_id;
  
  return signature_id;
}

