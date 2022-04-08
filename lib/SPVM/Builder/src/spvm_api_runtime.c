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

