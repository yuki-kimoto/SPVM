#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "spvm_compiler.h"
#include "spvm_type.h"
#include "spvm_list.h"
#include "spvm_op.h"
#include "spvm_compiler_allocator.h"
#include "spvm_hash.h"
#include "spvm_yacc_util.h"
#include "spvm_package.h"
#include "spvm_limit.h"
#include "spvm_package.h"
#include "spvm_basic_type.h"

const char* const SPVM_TYPE_C_ID_NAMES[] = {
  "unknown",
  "void",
  "undef",
  "byte",
  "short",
  "int",
  "long",
  "float",
  "double",
  "Object",
  "String",
  "byte[]",
  "short[]",
  "int[]",
  "long[]",
  "float[]",
  "double[]",
  "Object[]",
  "String[]",
};

int32_t SPVM_TYPE_get_type_name_length(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension) {
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
  assert(basic_type);
  
  int32_t length = strlen(basic_type->name) + dimension * 2;
}

int32_t SPVM_TYPE_fprint_type_name(SPVM_COMPILER* compiler, FILE* fh, int32_t basic_type_id, int32_t dimension) {
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
  assert(basic_type);
  
  fprintf(fh, "%s", basic_type->name);
  int32_t dim_index;
  for (dim_index = 0; dim_index < dimension; dim_index++) {
    fprintf(fh, "[]");
  }
}

int32_t SPVM_TYPE_sprint_type_name(SPVM_COMPILER* compiler, char* buffer, int32_t basic_type_id, int32_t dimension) {
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
  assert(basic_type);
  
  char* cur = buffer;
  
  sprintf(cur, "%s", basic_type->name);
  cur += strlen(basic_type->name);
  
  int32_t dim_index;
  for (dim_index = 0; dim_index < dimension; dim_index++) {
    sprintf(cur, "[]");
    cur += 2;
  }
  
  *cur = '\0';
  cur++;
}

SPVM_TYPE* SPVM_TYPE_new(SPVM_COMPILER* compiler) {
  SPVM_TYPE* type = SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, compiler->allocator, sizeof(SPVM_TYPE));
  
  type->id = SPVM_TYPE_C_ID_UNKNOWN;
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_get_void_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_HASH_search(compiler->basic_type_symtable, "void", strlen("void"));
  type->dimension = 0;
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_get_undef_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_HASH_search(compiler->basic_type_symtable, "undef", strlen("undef"));
  type->dimension = 0;
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_get_byte_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_HASH_search(compiler->type_symtable, "byte", strlen("byte"));
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_get_short_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_HASH_search(compiler->type_symtable, "short", strlen("short"));
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_get_int_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_HASH_search(compiler->type_symtable, "int", strlen("int"));
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_get_long_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_HASH_search(compiler->type_symtable, "long", strlen("long"));
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_get_float_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_HASH_search(compiler->type_symtable, "float", strlen("float"));
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_get_double_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_HASH_search(compiler->type_symtable, "double", strlen("double"));
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_get_byte_array_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_HASH_search(compiler->type_symtable, "byte[]", strlen("byte[]"));
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_get_string_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_HASH_search(compiler->type_symtable, "String", strlen("String"));
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_get_object_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_HASH_search(compiler->type_symtable, "Object", strlen("Object"));
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_search_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension) {
  
  SPVM_LIST* types = compiler->types;
  
  int32_t i;
  for (i = 0; i < types->length; i++) {
    SPVM_TYPE* type = SPVM_LIST_fetch(types, i);
    
    if (basic_type_id == type->basic_type->id && dimension == type->dimension) {
      return type;
    }
  }
  
  return NULL;
}

char* SPVM_TYPE_get_basic_type_name(SPVM_COMPILER* compiler, const char* type_name) {
  int32_t type_name_length = (int32_t)strlen(type_name);
  char* type_basic_type_name = SPVM_COMPILER_ALLOCATOR_alloc_string(compiler, compiler->allocator, type_name_length);
  
  char* found_ptr = strchr(type_name, '[');
  int32_t type_basic_type_name_length;
  if (found_ptr) {
    type_basic_type_name_length = (int32_t)(found_ptr - type_name);
  }
  else {
    type_basic_type_name_length = type_name_length;
  }
  
  strncpy(type_basic_type_name, type_name, type_basic_type_name_length);
  type_basic_type_name[type_basic_type_name_length] = '\0';
  
  return type_basic_type_name;
}

char* SPVM_TYPE_get_element_name(SPVM_COMPILER* compiler, const char* type_name) {
  int32_t type_basic_type_name_length;
  if (strchr(type_name, '[')) {
    type_basic_type_name_length = strlen(type_name) - 2;
  }
  else {
    return NULL;
  }

  char* type_basic_type_name = SPVM_COMPILER_ALLOCATOR_alloc_string(compiler, compiler->allocator, type_basic_type_name_length);
  
  strncpy(type_basic_type_name, type_name, type_basic_type_name_length);
  type_basic_type_name[type_basic_type_name_length] = '\0';
  
  return type_basic_type_name;
}

char* SPVM_TYPE_get_parent_name(SPVM_COMPILER* compiler, const char* type_name) {
  int32_t type_name_length = (int32_t)strlen(type_name);
  int32_t type_parent_name_length = type_name_length + 2;
  char* type_parent_name = SPVM_COMPILER_ALLOCATOR_alloc_string(compiler, compiler->allocator, type_parent_name_length);
  
  strncpy(type_parent_name, type_name, type_name_length);
  type_parent_name[type_name_length] = '[';
  type_parent_name[type_name_length + 1] = ']';
  type_parent_name[type_parent_name_length] = '\0';
  
  return type_parent_name;
}

// Create array name
char* SPVM_TYPE_create_array_name(SPVM_COMPILER* compiler, const char* basic_type_name) {
  
  int32_t basic_type_name_length = strlen(basic_type_name);
  int32_t name_length = basic_type_name_length + 2;
  char* type_name = SPVM_COMPILER_ALLOCATOR_alloc_string(compiler, compiler->allocator, name_length);
  
  int32_t cur_pos = 0;
  memcpy(type_name, basic_type_name, basic_type_name_length);
  type_name[basic_type_name_length] = '[';
  type_name[basic_type_name_length + 1] = ']';
  cur_pos += 2;
  type_name[name_length] = '\0';
  
  return type_name;
}

_Bool SPVM_TYPE_is_array(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  (void)compiler;
  
  return type->dimension > 0;
}

_Bool SPVM_TYPE_is_any_object(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  (void)compiler;
  
  return type && type->dimension == 0 && type->basic_type->id == SPVM_BASIC_TYPE_C_ID_ANY_OBJECT;
}


_Bool SPVM_TYPE_is_string(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  (void)compiler;
  
  return type && type->dimension == 0 && type->basic_type->id == SPVM_BASIC_TYPE_C_ID_STRING;
}

_Bool SPVM_TYPE_is_package(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  (void)compiler;
  
  _Bool is_package = (type->dimension == 0 && type->basic_type->id >= SPVM_BASIC_TYPE_C_ID_STRING);
  
  return is_package;
}

_Bool SPVM_TYPE_is_array_numeric(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  (void)compiler;
  
  assert(type);
  
  if (type->dimension == 1 && (type->basic_type->id >= SPVM_BASIC_TYPE_C_ID_BYTE && type->basic_type->id <= SPVM_BASIC_TYPE_C_ID_DOUBLE))
  {
    return 1;
  }
  else {
    return 0;
  }
}

_Bool SPVM_TYPE_is_integral(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  (void)compiler;
  
  assert(type);
  
  if (type->dimension == 0 && (type->basic_type->id >= SPVM_BASIC_TYPE_C_ID_BYTE && type->basic_type->id <= SPVM_BASIC_TYPE_C_ID_LONG)) {
    return 1;
  }
  else {
    return 0;
  }
}

_Bool SPVM_TYPE_is_numeric(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  (void)compiler;
  
  assert(type);
  
  if (type->dimension == 0 && (type->id >= SPVM_BASIC_TYPE_C_ID_BYTE && type->id <= SPVM_BASIC_TYPE_C_ID_DOUBLE)) {
    return 1;
  }
  else {
    return 0;
  }
}

_Bool SPVM_TYPE_equal(SPVM_COMPILER* compiler, SPVM_TYPE* type1, SPVM_TYPE* type2) {
  if (type1->basic_type->id == type2->basic_type->id && type1->dimension == type2->dimension) {
    return 1;
  }
  else {
    return 0;
  }
}

_Bool SPVM_TYPE_is_int(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  
  if (type->dimension == 0 && type->basic_type->id == SPVM_BASIC_TYPE_C_ID_INT) {
    return 1;
  }
  else {
    return 0;
  }
}

_Bool SPVM_TYPE_is_object(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  (void)compiler;
  
  if (type->dimension > 0 || (type->dimension == 0 && type->basic_type->id > SPVM_BASIC_TYPE_C_ID_DOUBLE)) {
    return 1;
  }
  else {
    return 0;
  }
}

_Bool SPVM_TYPE_is_undef(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  (void)compiler;
  
  if (type->dimension == 0 && type->basic_type->id == SPVM_BASIC_TYPE_C_ID_UNDEF) {
    return 1;
  }
  else {
    return 0;
  }
}
