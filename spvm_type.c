#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "spvm_compiler.h"
#include "spvm_type.h"
#include "spvm_dynamic_array.h"
#include "spvm_op.h"
#include "spvm_compiler_allocator.h"
#include "spvm_hash.h"
#include "spvm_yacc_util.h"
#include "spvm_package.h"
#include "spvm_limit.h"
#include "spvm_package.h"

const char* const SPVM_TYPE_C_ID_NAMES[] = {
  "void",
  "byte",
  "short",
  "int",
  "long",
  "float",
  "double",
  "string",
  "byte[]",
  "short[]",
  "int[]",
  "long[]",
  "float[]",
  "double[]",
  "string[]",
};

SPVM_TYPE* SPVM_TYPE_new(SPVM_COMPILER* compiler) {
  SPVM_TYPE* type = SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, compiler->allocator, sizeof(SPVM_TYPE));
  
  type->id = SPVM_TYPE_C_ID_UNKNOWN;
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_get_byte_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_DYNAMIC_ARRAY_fetch(compiler->types, SPVM_TYPE_C_ID_BYTE);
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_get_short_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_DYNAMIC_ARRAY_fetch(compiler->types, SPVM_TYPE_C_ID_SHORT);
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_get_int_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_DYNAMIC_ARRAY_fetch(compiler->types, SPVM_TYPE_C_ID_INT);
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_get_long_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_DYNAMIC_ARRAY_fetch(compiler->types, SPVM_TYPE_C_ID_LONG);
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_get_float_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_DYNAMIC_ARRAY_fetch(compiler->types, SPVM_TYPE_C_ID_FLOAT);
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_get_double_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_DYNAMIC_ARRAY_fetch(compiler->types, SPVM_TYPE_C_ID_DOUBLE);
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_get_string_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_DYNAMIC_ARRAY_fetch(compiler->types, SPVM_TYPE_C_ID_STRING);
  
  assert(type);
  
  return type;
}

char* SPVM_TYPE_get_base_name(SPVM_COMPILER* compiler, const char* type_name) {
  int32_t type_name_length = (int32_t)strlen(type_name);
  char* type_base_name = SPVM_COMPILER_ALLOCATOR_alloc_string(compiler, compiler->allocator, type_name_length);
  
  char* found_ptr = strchr(type_name, '[');
  int32_t type_base_name_length;
  if (found_ptr) {
    type_base_name_length = (int32_t)(found_ptr - type_name);
  }
  else {
    type_base_name_length = type_name_length;
  }
  
  strncpy(type_base_name, type_name, type_base_name_length);
  type_base_name[type_base_name_length] = '\0';
  
  return type_base_name;
}

char* SPVM_TYPE_get_element_name(SPVM_COMPILER* compiler, const char* type_name) {
  int32_t type_name_length = (int32_t)strlen(type_name);
  char* type_base_name = SPVM_COMPILER_ALLOCATOR_alloc_string(compiler, compiler->allocator, type_name_length);
  
  char* found_ptr = rindex(type_name, '[');
  int32_t type_base_name_length;
  if (found_ptr) {
    type_base_name_length = (int32_t)(found_ptr - type_name);
  }
  else {
    return NULL;
  }
  
  strncpy(type_base_name, type_name, type_base_name_length);
  type_base_name[type_base_name_length] = '\0';
  
  return type_base_name;
}

// Create array name
char* SPVM_TYPE_create_array_name(SPVM_COMPILER* compiler, const char* base_name) {
  
  int32_t base_name_length = strlen(base_name);
  int32_t name_length = base_name_length + 2;
  char* type_name = SPVM_COMPILER_ALLOCATOR_alloc_string(compiler, compiler->allocator, name_length);
  
  int32_t cur_pos = 0;
  memcpy(type_name, base_name, base_name_length);
  type_name[base_name_length] = '[';
  type_name[base_name_length + 1] = ']';
  cur_pos += 2;
  type_name[name_length] = '\0';
  
  return type_name;
}

_Bool SPVM_TYPE_is_array(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  (void)compiler;
  
  return type->is_array;
}

_Bool SPVM_TYPE_is_array_numeric(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  (void)compiler;
  
  if (type && type->id >= SPVM_TYPE_C_ID_BYTE_ARRAY && type->id <= SPVM_TYPE_C_ID_DOUBLE_ARRAY)
  {
    return 1;
  }
  else {
    return 0;
  }
}

_Bool SPVM_TYPE_is_integral(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  (void)compiler;
  
  if (type && type->id >= SPVM_TYPE_C_ID_BYTE && type->id <= SPVM_TYPE_C_ID_LONG) {
    return 1;
  }
  else {
    return 0;
  }
}

_Bool SPVM_TYPE_is_numeric(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  (void)compiler;
  
  if (type && type->id >= SPVM_TYPE_C_ID_BYTE && type->id <= SPVM_TYPE_C_ID_DOUBLE) {
    return 1;
  }
  else {
    return 0;
  }
}
