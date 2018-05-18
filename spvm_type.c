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

int32_t SPVM_TYPE_get_type_name_length(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension) {
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
  assert(basic_type);
  
  int32_t length = strlen(basic_type->name) + dimension * 2;
  
  return length;
}

void SPVM_TYPE_fprint_type_name(SPVM_COMPILER* compiler, FILE* fh, int32_t basic_type_id, int32_t dimension) {
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
  assert(basic_type);
  
  fprintf(fh, "%s", basic_type->name);
  int32_t dim_index;
  for (dim_index = 0; dim_index < dimension; dim_index++) {
    fprintf(fh, "[]");
  }
}

void SPVM_TYPE_sprint_type_name(SPVM_COMPILER* compiler, char* buffer, int32_t basic_type_id, int32_t dimension) {
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
  SPVM_TYPE* type = SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, sizeof(SPVM_TYPE));
  
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
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_HASH_search(compiler->basic_type_symtable, "byte", strlen("byte"));
  type->dimension = 0;
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_get_short_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_HASH_search(compiler->basic_type_symtable, "short", strlen("short"));
  type->dimension = 0;
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_get_int_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_HASH_search(compiler->basic_type_symtable, "int", strlen("int"));
  type->dimension = 0;
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_get_long_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_HASH_search(compiler->basic_type_symtable, "long", strlen("long"));
  type->dimension = 0;
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_get_float_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_HASH_search(compiler->basic_type_symtable, "float", strlen("float"));
  type->dimension = 0;
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_get_double_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_HASH_search(compiler->basic_type_symtable, "double", strlen("double"));
  type->dimension = 0;
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_get_string_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_HASH_search(compiler->basic_type_symtable, "String", strlen("String"));
  type->dimension = 0;
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_get_object_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_HASH_search(compiler->basic_type_symtable, "Object", strlen("Object"));
  type->dimension = 0;
  
  assert(type);
  
  return type;
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
  
  if (type->dimension == 0 && (type->basic_type->id >= SPVM_BASIC_TYPE_C_ID_BYTE && type->basic_type->id <= SPVM_BASIC_TYPE_C_ID_DOUBLE)) {
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
