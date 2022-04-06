#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "spvm_compiler.h"
#include "spvm_type.h"
#include "spvm_list.h"
#include "spvm_op.h"
#include "spvm_allocator.h"
#include "spvm_hash.h"
#include "spvm_yacc_util.h"
#include "spvm_class.h"
#include "spvm_field.h"
#include "spvm_basic_type.h"
#include "spvm_method.h"
#include "spvm_constant.h"

int32_t SPVM_TYPE_get_type_name_length(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
  assert(basic_type);
  
  int32_t length = 0;
  
  // *
  if (flag & SPVM_TYPE_C_FLAG_MUTABLE) {
    length += strlen("mutable ");
  }
  
  // Basic type
  length += strlen(basic_type->name);
  
  // []
  length += dimension * 2;
  
  // *
  if (flag & SPVM_TYPE_C_FLAG_REF) {
    length += 1;
  }
  
  return length;
}

const char* SPVM_TYPE_new_type_name_with_eternal_flag(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag, int32_t is_eternal) {
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
  assert(basic_type);
  
  int32_t type_name_length = SPVM_TYPE_get_type_name_length(compiler, basic_type_id, dimension, flag);
  
  char* type_name;
  if (is_eternal) {
    type_name = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, type_name_length + 1);
  }
  else {
    type_name = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->allocator, type_name_length + 1);
  }
  
  char* cur = type_name;

  if (flag & SPVM_TYPE_C_FLAG_MUTABLE) {
    sprintf(cur, "mutable ");
    cur += strlen("mutable ");
  }
  
  sprintf(cur, "%s", basic_type->name);
  cur += strlen(basic_type->name);
  
  int32_t dim_index;
  for (dim_index = 0; dim_index < dimension; dim_index++) {
    sprintf(cur, "[]");
    cur += 2;
  }

  // Reference
  if (flag & SPVM_TYPE_C_FLAG_REF) {
    sprintf(cur, "*");
    cur += 1;
  }
  
  *cur = '\0';
  cur++;

  return type_name;
}

const char* SPVM_TYPE_new_type_name_tmp(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  int32_t is_eternal = 0;
  return SPVM_TYPE_new_type_name_with_eternal_flag(compiler, basic_type_id, dimension, flag, is_eternal);
}

const char* SPVM_TYPE_new_type_name(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  int32_t is_eternal = 1;
  return SPVM_TYPE_new_type_name_with_eternal_flag(compiler, basic_type_id, dimension, flag, is_eternal);
}

SPVM_TYPE* SPVM_TYPE_new(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  int32_t start_memory_blocks_count_tmp = compiler->allocator->memory_blocks_count_tmp;
  
  const char* type_name = SPVM_TYPE_new_type_name_tmp(compiler,  basic_type_id, dimension, flag);
  
  SPVM_TYPE* found_type = SPVM_HASH_get(compiler->type_symtable, type_name, strlen(type_name));
  SPVM_TYPE* type;
  if (found_type) {
    type = found_type;
  }
  else {
    type = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, sizeof(SPVM_TYPE));
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    type->id = compiler->types->length;
    type->basic_type = basic_type;
    type->dimension = dimension;
    type->flag = flag;
    type->name = SPVM_TYPE_new_type_name(compiler,  basic_type_id, dimension, flag);
    
    SPVM_LIST_push(compiler->types, type);
    SPVM_HASH_set(compiler->type_symtable, type_name, strlen(type_name), type);
  }
  
  SPVM_ALLOCATOR_free_memory_block_tmp(compiler->allocator, (void*)type_name);
  type_name = NULL;
  assert(compiler->allocator->memory_blocks_count_tmp == start_memory_blocks_count_tmp);
  
  return type;
}

int32_t SPVM_TYPE_is_ref_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  (void)basic_type_id;
  (void)dimension;
  
  return flag & SPVM_TYPE_C_FLAG_REF;
}

SPVM_TYPE* SPVM_TYPE_new_void_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_VOID);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_any_object_array_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_ANY_OBJECT);
  int32_t type_dimension = 1;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_undef_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_UNDEF);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_byte_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_short_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  

  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_int_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_INT);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_long_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  

  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_LONG);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_float_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_double_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_string_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_STRING);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_object_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_ANY_OBJECT);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_byte_object_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE_OBJECT);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_short_object_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT_OBJECT);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_int_object_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_INT_OBJECT);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_long_object_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_LONG_OBJECT);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_float_object_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT_OBJECT);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_double_object_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE_OBJECT);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_bool_object_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_BOOL_OBJECT);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_byte_ref_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE);
  int32_t type_dimension = 0;
  int32_t type_flag = SPVM_TYPE_C_FLAG_REF;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_short_ref_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT);
  int32_t type_dimension = 0;
  int32_t type_flag = SPVM_TYPE_C_FLAG_REF;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_int_ref_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_INT);
  int32_t type_dimension = 0;
  int32_t type_flag = SPVM_TYPE_C_FLAG_REF;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_long_ref_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_LONG);
  int32_t type_dimension = 0;
  int32_t type_flag = SPVM_TYPE_C_FLAG_REF;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_float_ref_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT);
  int32_t type_dimension = 0;
  int32_t type_flag = SPVM_TYPE_C_FLAG_REF;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);

  return type;
}

SPVM_TYPE* SPVM_TYPE_new_double_ref_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE);
  int32_t type_dimension = 0;
  int32_t type_flag = SPVM_TYPE_C_FLAG_REF;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_any_object_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_ANY_OBJECT);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_element_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_ANY_OBJECT);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

int32_t SPVM_TYPE_is_byte_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_void_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_VOID) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_short_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_int_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_long_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_float_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_double_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_numeric_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  int32_t basci_type_is_numeric_type = SPVM_BASIC_TYPE_is_numeric_type(compiler, basic_type_id);
  if (dimension == 0 && basci_type_is_numeric_type && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_numeric_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  int32_t basci_type_is_numeric_object_type = SPVM_BASIC_TYPE_is_numeric_object_type(compiler, basic_type_id);
  if (dimension == 0 && basci_type_is_numeric_object_type && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_byte_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE_OBJECT) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_short_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT_OBJECT) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_int_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT_OBJECT) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_long_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG_OBJECT) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_float_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT_OBJECT) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_double_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE_OBJECT) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_bool_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_BOOL_OBJECT) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_numeric_ref_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  int32_t basci_type_is_numeric_type = SPVM_BASIC_TYPE_is_numeric_type(compiler, basic_type_id);
  if (dimension == 0 && basci_type_is_numeric_type && (flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_integral_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  int32_t basci_type_is_integral_type = SPVM_BASIC_TYPE_is_integral_type(compiler, basic_type_id);
  if (dimension == 0 && basci_type_is_integral_type && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (SPVM_TYPE_is_array_type(compiler, basic_type_id, dimension, flag)) {
    return 1;
  }
  else if (SPVM_TYPE_is_basic_object_type(compiler, basic_type_id, dimension, flag)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_basic_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (SPVM_TYPE_is_string_type(compiler, basic_type_id, dimension, flag)) {
    return 1;
  }
  else if (SPVM_TYPE_is_class_type(compiler, basic_type_id, dimension, flag)) {
    return 1;
  }
  else if (SPVM_TYPE_is_callback_type(compiler, basic_type_id, dimension, flag)) {
    return 1;
  }
  else if (SPVM_TYPE_is_interface_type(compiler, basic_type_id, dimension, flag)) {
    return 1;
  }
  else if (SPVM_TYPE_is_any_object_type(compiler, basic_type_id, dimension, flag)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_basic_object_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (SPVM_TYPE_is_array_type(compiler, basic_type_id, dimension, flag)) {
    if (SPVM_TYPE_is_basic_object_type(compiler, basic_type_id, dimension - 1, flag)) {
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

int32_t SPVM_TYPE_is_any_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  return dimension == 0 && basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_ANY_OBJECT && !(flag & SPVM_TYPE_C_FLAG_REF);
}

int32_t SPVM_TYPE_is_class_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  int32_t is_class_type;
  int32_t basic_type_is_class_type = SPVM_BASIC_TYPE_is_class_type(compiler, basic_type_id);
  if (dimension == 0 && basic_type_is_class_type && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    is_class_type = 1;
  }
  // Array
  else {
    is_class_type = 0;
  }
  
  return is_class_type;
}

int32_t SPVM_TYPE_is_not_found_class_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  int32_t is_not_found_class_type;
  int32_t basic_type_is_not_found_class_type = SPVM_BASIC_TYPE_is_not_found_class_type(compiler, basic_type_id);
  if (dimension == 0 && basic_type_is_not_found_class_type && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    is_not_found_class_type = 1;
  }
  // Array
  else {
    is_not_found_class_type = 0;
  }
  
  return is_not_found_class_type;
}

int32_t SPVM_TYPE_is_callback_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  int32_t is_callback_type;
  int32_t basic_type_is_callback_type = SPVM_BASIC_TYPE_is_callback_type(compiler, basic_type_id);
  if (dimension == 0 && basic_type_is_callback_type && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    is_callback_type = 1;
  }
  // Array
  else {
    is_callback_type = 0;
  }
  
  return is_callback_type;
}

int32_t SPVM_TYPE_is_interface_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  int32_t is_interface_type;
  int32_t basic_type_is_interface_type = SPVM_BASIC_TYPE_is_interface_type(compiler, basic_type_id);
  if (dimension == 0 && basic_type_is_interface_type && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    is_interface_type = 1;
  }
  // Array
  else {
    is_interface_type = 0;
  }
  
  return is_interface_type;
}

int32_t SPVM_TYPE_is_string_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  return dimension == 0 && basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_STRING && !(flag & SPVM_TYPE_C_FLAG_REF);
}

int32_t SPVM_TYPE_is_byte_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  return dimension == 1 && basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE && !(flag & SPVM_TYPE_C_FLAG_REF);
}

int32_t SPVM_TYPE_is_string_or_byte_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  int32_t is_string_or_byte_array;
  if (SPVM_TYPE_is_string_type(compiler, basic_type_id, dimension, flag) || SPVM_TYPE_is_byte_array_type(compiler, basic_type_id, dimension, flag)) {
    is_string_or_byte_array = 1;
  }
  else {
    is_string_or_byte_array = 0;
  }
  
  return is_string_or_byte_array;
}

int32_t SPVM_TYPE_is_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  return dimension > 0 && !(flag & SPVM_TYPE_C_FLAG_REF);
}

int32_t SPVM_TYPE_is_string_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  int32_t is_string_array_type;
  int32_t basic_type_is_string_type = SPVM_BASIC_TYPE_is_string_type(compiler, basic_type_id);
  if (dimension == 1 && basic_type_is_string_type && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    is_string_array_type = 1;
  }
  // Array
  else {
    is_string_array_type = 0;
  }
  
  return is_string_array_type;
}

int32_t SPVM_TYPE_is_class_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  int32_t is_class_array_type;
  int32_t basic_type_is_class_type = SPVM_BASIC_TYPE_is_class_type(compiler, basic_type_id);
  if (dimension == 1 && basic_type_is_class_type && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    is_class_array_type = 1;
  }
  // Array
  else {
    is_class_array_type = 0;
  }
  
  return is_class_array_type;
}

int32_t SPVM_TYPE_is_interface_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  int32_t is_interface_array_type;
  int32_t basic_type_is_interface_type = SPVM_BASIC_TYPE_is_interface_type(compiler, basic_type_id);
  if (dimension == 1 && basic_type_is_interface_type && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    is_interface_array_type = 1;
  }
  // Array
  else {
    is_interface_array_type = 0;
  }
  
  return is_interface_array_type;
}

int32_t SPVM_TYPE_is_callback_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  int32_t is_callback_array_type;
  int32_t basic_type_is_callback_type = SPVM_BASIC_TYPE_is_callback_type(compiler, basic_type_id);
  if (dimension == 1 && basic_type_is_callback_type && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    is_callback_array_type = 1;
  }
  // Array
  else {
    is_callback_array_type = 0;
  }
  
  return is_callback_array_type;
}

int32_t SPVM_TYPE_is_muldim_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  return dimension > 1 && !(flag & SPVM_TYPE_C_FLAG_REF);
}

int32_t SPVM_TYPE_is_any_object_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_ANY_OBJECT && dimension == 1 && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_numeric_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  int32_t is_numeric_array_type;
  int32_t basic_type_is_numeric_type = SPVM_BASIC_TYPE_is_numeric_type(compiler, basic_type_id);
  if (dimension == 1 && basic_type_is_numeric_type && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    is_numeric_array_type = 1;
  }
  // Array
  else {
    is_numeric_array_type = 0;
  }
  
  return is_numeric_array_type;
}

int32_t SPVM_TYPE_is_undef_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_UNDEF && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_unknown_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_UNKNOWN && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_mulnum_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  int32_t basci_type_is_mulnum_type = SPVM_BASIC_TYPE_is_mulnum_type(compiler, basic_type_id);
  if (dimension == 0 && basci_type_is_mulnum_type && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_mulnum_ref_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  int32_t basci_type_is_mulnum_type = SPVM_BASIC_TYPE_is_mulnum_type(compiler, basic_type_id);
  if (dimension == 0 && basci_type_is_mulnum_type && (flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_mulnum_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  int32_t is_mulnum_array_type;
  int32_t basic_type_is_mulnum_type = SPVM_BASIC_TYPE_is_mulnum_type(compiler, basic_type_id);
  if (dimension == 1 && basic_type_is_mulnum_type && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    is_mulnum_array_type = 1;
  }
  // Array
  else {
    is_mulnum_array_type = 0;
  }
  
  return is_mulnum_array_type;
}

int32_t SPVM_TYPE_get_width(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  int32_t is_mulnum_type = SPVM_TYPE_is_mulnum_type(compiler, basic_type_id, dimension, flag);
  
  int32_t width;
  if (is_mulnum_type) {
    
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    assert(basic_type);
    
    SPVM_CLASS* class = basic_type->class;
    
    assert(class);
    
    width = class->fields->length;
  }
  else {
    width = 1;
  }
  
  return width;
}

int32_t SPVM_TYPE_get_mulnum_field_basic_type_id(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  int32_t mulnum_field_basic_type_id;
  if (SPVM_TYPE_is_mulnum_type(compiler, basic_type_id, dimension, flag) || SPVM_TYPE_is_mulnum_ref_type(compiler, basic_type_id, dimension, flag)) {
    
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    assert(basic_type);
    
    SPVM_CLASS* class = basic_type->class;
    
    assert(class->fields->length > 0);
    
    SPVM_FIELD* mulnum_field = SPVM_LIST_get(class->fields, 0);
    
    SPVM_TYPE* mulnum_field_type = mulnum_field->type;
    
    mulnum_field_basic_type_id = mulnum_field_type->basic_type->id;
  }
  else {
    mulnum_field_basic_type_id = -1;
  }
  
  return mulnum_field_basic_type_id;
}

int32_t SPVM_TYPE_can_assign(
  SPVM_COMPILER* compiler,
  int32_t dist_type_basic_type_id, int32_t dist_type_dimension, int32_t dist_type_flag,
  int32_t src_type_basic_type_id, int32_t src_type_dimension, int32_t src_type_flag,
  SPVM_CONSTANT* src_constant, int32_t* need_implicite_conversion, int32_t* narrowing_conversion_error, int32_t* mutable_invalid)
{
  // Dist type is numeric type
  int32_t can_assign = 0;
  if (SPVM_TYPE_is_numeric_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Soruce type is numeric type
    if (SPVM_TYPE_is_numeric_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      // Dist type is same as source type
      if (dist_type_basic_type_id == src_type_basic_type_id) {
        can_assign = 1;
      }
      // Dist type is more wide than source type
      else if (dist_type_basic_type_id > src_type_basic_type_id) {
        can_assign = 1;
        *need_implicite_conversion = 1;
      }
      // Dist type is narrow than source type
      else if (dist_type_basic_type_id < src_type_basic_type_id) {
        int32_t can_narrowing_conversion = 0;
        if (src_constant) {
          assert(src_type_dimension == 0);
          if (src_type_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT || src_type_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
            int64_t src_constant_value;
            if (src_type_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
              src_constant_value = src_constant->value.ival;
            }
            else if (src_type_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
              src_constant_value = src_constant->value.lval;
            }
            else {
              assert(0);
            }
            
            if (dist_type_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
              if (src_constant_value >= INT8_MIN && src_constant_value <= INT8_MAX) {
                can_narrowing_conversion = 1;
              }
              else {
                can_narrowing_conversion = 0;
              }
            }
            else if (dist_type_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
              if (src_constant_value >= INT16_MIN && src_constant_value <= INT16_MAX) {
                can_narrowing_conversion = 1;
              }
              else {
                can_narrowing_conversion = 0;
              }
            }
            else if (dist_type_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
              if (src_constant_value >= INT32_MIN && src_constant_value <= INT32_MAX) {
                can_narrowing_conversion = 1;
              }
              else {
                can_narrowing_conversion = 0;
              }
            }
            else {
              assert(0);
            }
          }
          else {
            can_narrowing_conversion = 0;
          }
        }
        else {
          can_assign = 0;
        }
        
        if (can_narrowing_conversion) {
          *need_implicite_conversion = 1;
          can_assign = 1;
        }
        else {
          *narrowing_conversion_error = 1;
          can_assign = 0;
        }
      }
    }
    else if (SPVM_TYPE_is_object_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      if (SPVM_TYPE_is_any_object_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
        can_assign = 1;
        *need_implicite_conversion = 1;
      }
      else if (SPVM_TYPE_is_numeric_object_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
        if (src_type_basic_type_id == dist_type_basic_type_id + SPVM_BASIC_TYPE_C_NUMERIC_OBJECT_UPGRADE_SHIFT) {
          can_assign = 1;
          *need_implicite_conversion = 1;
        }
        else {
          can_assign = 0;
        }
      }
      else {
        can_assign = 0;
      }
    }
    else {
      can_assign = 0;
    }
  }
  // Dist type is referece type
  else if (SPVM_TYPE_is_ref_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    if (SPVM_TYPE_is_ref_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      if (dist_type_basic_type_id == src_type_basic_type_id && dist_type_dimension == src_type_dimension) {
        can_assign = 1;
      }
      else {
        can_assign = 0;
      }
    }
    else {
      can_assign = 0;
    }
  }
  // Dist type is multi numeric type
  else if (SPVM_TYPE_is_mulnum_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    if (SPVM_TYPE_is_mulnum_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      if (dist_type_basic_type_id == src_type_basic_type_id && dist_type_dimension == src_type_dimension) {
        can_assign = 1;
      }
      else {
        can_assign = 0;
      }
    }
    else {
      can_assign = 0;
    }
  }
  // Dist type is numeric array type
  else if (SPVM_TYPE_is_numeric_array_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    if (SPVM_TYPE_is_numeric_array_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      if (dist_type_basic_type_id == src_type_basic_type_id && dist_type_dimension == src_type_dimension) {
        can_assign = 1;
      }
      else {
        can_assign = 0;
      }
    }
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = 1;
    }
    else {
      can_assign = 0;
    }
  }
  // Dist type is mulnum array type
  else if (SPVM_TYPE_is_mulnum_array_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    if (SPVM_TYPE_is_mulnum_array_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      if (dist_type_basic_type_id == src_type_basic_type_id && dist_type_dimension == src_type_dimension) {
        can_assign = 1;
      }
      else {
        can_assign = 0;
      }
    }
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = 1;
    }
    else {
      can_assign = 0;
    }
  }
  // Dist type is any object type
  else if (SPVM_TYPE_is_any_object_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type is object type
    if (SPVM_TYPE_is_object_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = 1;
    }
    // Source type is numeric type
    else if (SPVM_TYPE_is_numeric_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = 1;
      *need_implicite_conversion = 1;
    }
    // Source type is undef type
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = 1;
    }
    else {
      can_assign = 0;
    }
  }
  // Dist type is string type
  else if (SPVM_TYPE_is_string_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type is string
    if (SPVM_TYPE_is_string_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = 1;
    }
    // Source type is number
    else if (SPVM_TYPE_is_numeric_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = 1;
      *need_implicite_conversion = 1;
    }
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = 1;
    }
    else {
      can_assign = 0;
    }
  }
  // Dist type is numeric object type
  else if (SPVM_TYPE_is_numeric_object_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    if (SPVM_TYPE_is_numeric_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      if (dist_type_basic_type_id == src_type_basic_type_id + SPVM_BASIC_TYPE_C_NUMERIC_OBJECT_UPGRADE_SHIFT) {
        can_assign = 1;
        *need_implicite_conversion = 1;
      }
      else {
        can_assign = 0;
      }
    }
    else if (SPVM_TYPE_is_numeric_object_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      if (src_type_basic_type_id == dist_type_basic_type_id) {
        can_assign = 1;
      }
      else {
        can_assign = 0;
      }
    }
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = 1;
    }
    else {
      can_assign = 0;
    }
  }
  // Dist type is class
  else if (SPVM_TYPE_is_class_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    if (SPVM_TYPE_is_class_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      if (dist_type_basic_type_id == src_type_basic_type_id) {
        can_assign = 1;
      }
      else {
        can_assign = 0;
      }
    }
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = 1;
    }
    else {
      can_assign = 0;
    }
  }
  // Dist type is interface
  else if (SPVM_TYPE_is_interface_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    if (SPVM_TYPE_is_basic_object_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      if (dist_type_basic_type_id == src_type_basic_type_id && dist_type_dimension == src_type_dimension) {
        can_assign = 1;
      }
      else {
        if (SPVM_TYPE_is_class_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
          can_assign = SPVM_BASIC_TYPE_has_interface(compiler, src_type_basic_type_id, dist_type_basic_type_id);
        }
        else {
          can_assign = 0;
        }
      }
    }
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = 1;
    }
    else {
      can_assign = 0;
    }
  }
  // Dist type is callback
  else if (SPVM_TYPE_is_callback_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    if (SPVM_TYPE_is_basic_object_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      if (dist_type_basic_type_id == src_type_basic_type_id && dist_type_dimension == src_type_dimension) {
        can_assign = 1;
      }
      else {
        if (SPVM_TYPE_is_class_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
          can_assign = SPVM_BASIC_TYPE_has_callback(compiler, src_type_basic_type_id, dist_type_basic_type_id);
        }
        else {
          can_assign = 0;
        }
      }
    }
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = 1;
    }
    else {
      can_assign = 0;
    }
  }
  // Dist type is string array type
  else if (SPVM_TYPE_is_string_array_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type is string
    if (SPVM_TYPE_is_string_array_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = 1;
    }
    // Source type is undef type
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = 1;
    }
    else {
      can_assign = 0;
    }
  }
  // Dist type is class array type
  else if (SPVM_TYPE_is_class_array_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type is class
    if (SPVM_TYPE_is_class_array_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      if (dist_type_basic_type_id == src_type_basic_type_id && dist_type_dimension == src_type_dimension) {
        can_assign = 1;
      }
      else {
        can_assign = 0;
      }
    }
    // Source type is undef type
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = 1;
    }
    else {
      can_assign = 0;
    }
  }
  // Dist type is interface array type
  else if (SPVM_TYPE_is_interface_array_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    if (dist_type_basic_type_id == src_type_basic_type_id && dist_type_dimension == src_type_dimension) {
      can_assign = 1;
    }
    else if (SPVM_TYPE_is_basic_object_array_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = SPVM_BASIC_TYPE_has_interface(compiler, src_type_basic_type_id, dist_type_basic_type_id);
    }
    // Source type is undef type
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = 1;
    }
    else {
      can_assign = 0;
    }
  }
  // Dist type is callback array type
  else if (SPVM_TYPE_is_callback_array_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    if (dist_type_basic_type_id == src_type_basic_type_id && dist_type_dimension == src_type_dimension) {
      can_assign = 1;
    }
    else if (SPVM_TYPE_is_basic_object_array_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = SPVM_BASIC_TYPE_has_callback(compiler, src_type_basic_type_id, dist_type_basic_type_id);
    }
    // Source type is undef type
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = 1;
    }
    else {
      can_assign = 0;
    }
  }
  // Dist type is any object array(object[])
  else if (SPVM_TYPE_is_any_object_array_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    
    if (SPVM_TYPE_is_basic_object_array_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = 1;
    }
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = 1;
    }
    else {
      can_assign = 0;
    }
  }
  // Dist type is muldim array type
  else if (SPVM_TYPE_is_muldim_array_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type is muldim
    if (SPVM_TYPE_is_object_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      if (dist_type_basic_type_id == src_type_basic_type_id && dist_type_dimension == src_type_dimension) {
        can_assign = 1;
      }
      else {
        can_assign = 0;
      }
    }
    // Source type is undef type
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = 1;
    }
    else {
      can_assign = 0;
    }
  }
  else if (SPVM_TYPE_is_undef_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    can_assign = 0;
  }
  else {
    assert(0);
  }
  
  // Mutable check
  if(dist_type_flag & SPVM_TYPE_C_FLAG_MUTABLE && !(src_type_flag & SPVM_TYPE_C_FLAG_MUTABLE)) {
    can_assign = 0;
    *mutable_invalid = 1;
  }
  
  return can_assign;
}
