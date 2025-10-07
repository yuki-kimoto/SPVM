// Copyright (c) 2023 Yuki Kimoto
// MIT License

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
#include "spvm_basic_type.h"
#include "spvm_field.h"
#include "spvm_method.h"
#include "spvm_constant.h"
#include "spvm_var_decl.h"

int32_t SPVM_TYPE_is_ref_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  return flag & SPVM_NATIVE_C_TYPE_FLAG_REF;
}

int32_t SPVM_TYPE_is_byte_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  if (dimension == 0 && (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_void_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  if (dimension == 0 && (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_VOID) && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_short_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  if (dimension == 0 && (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_int_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  if (dimension == 0 && (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_long_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  if (dimension == 0 && (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_float_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  if (dimension == 0 && (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_double_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  if (dimension == 0 && (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_numeric_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  int32_t basic_type_is_numeric_type = SPVM_BASIC_TYPE_is_numeric_type(compiler, basic_type_id);
  if (dimension == 0 && basic_type_is_numeric_type && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_numeric_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  int32_t basic_type_is_numeric_object_type = SPVM_BASIC_TYPE_is_numeric_object_type(compiler, basic_type_id);
  if (dimension == 0 && basic_type_is_numeric_object_type && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_byte_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  if (dimension == 0 && (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE_CLASS) && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_short_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  if (dimension == 0 && (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT_CLASS) && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_int_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  if (dimension == 0 && (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT_CLASS) && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_long_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  if (dimension == 0 && (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG_CLASS) && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_float_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  if (dimension == 0 && (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT_CLASS) && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_double_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  if (dimension == 0 && (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE_CLASS) && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_bool_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  if (dimension == 0 && (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_BOOL_CLASS) && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_numeric_ref_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  int32_t basic_type_is_numeric_type = SPVM_BASIC_TYPE_is_numeric_type(compiler, basic_type_id);
  if (dimension == 0 && basic_type_is_numeric_type && (flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_integer_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  int32_t basic_type_is_integer_type = SPVM_BASIC_TYPE_is_integer_type(compiler, basic_type_id);
  if (dimension == 0 && basic_type_is_integer_type && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_integer_type_within_int(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  int32_t basic_type_is_integer_type_within_int = SPVM_BASIC_TYPE_is_integer_type_within_int(compiler, basic_type_id);
  if (dimension == 0 && basic_type_is_integer_type_within_int && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}


int32_t SPVM_TYPE_is_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
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
  
  if (SPVM_TYPE_is_string_type(compiler, basic_type_id, dimension, flag)) {
    return 1;
  }
  else if (SPVM_TYPE_is_class_type(compiler, basic_type_id, dimension, flag)) {
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

int32_t SPVM_TYPE_is_object_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  if (SPVM_TYPE_is_array_type(compiler, basic_type_id, dimension, flag)) {
    if (SPVM_TYPE_is_object_type(compiler, basic_type_id, dimension - 1, flag)) {
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
  
  return dimension == 0 && basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_ANY_OBJECT && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF);
}

int32_t SPVM_TYPE_is_class_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  int32_t is_class_type;
  int32_t basic_type_is_class_type = SPVM_BASIC_TYPE_is_class_type(compiler, basic_type_id);
  if (dimension == 0 && basic_type_is_class_type && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    is_class_type = 1;
  }
  // Array
  else {
    is_class_type = 0;
  }
  
  return is_class_type;
}

int32_t SPVM_TYPE_is_interface_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  int32_t is_interface_type;
  int32_t basic_type_is_interface_type = SPVM_BASIC_TYPE_is_interface_type(compiler, basic_type_id);
  if (dimension == 0 && basic_type_is_interface_type && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    is_interface_type = 1;
  }
  // Array
  else {
    is_interface_type = 0;
  }
  
  return is_interface_type;
}

int32_t SPVM_TYPE_is_string_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  return dimension == 0 && basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_STRING && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF);
}

int32_t SPVM_TYPE_is_byte_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  return dimension == 1 && basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF);
}

int32_t SPVM_TYPE_is_string_or_byte_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
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
  
  return dimension > 0 && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF);
}

int32_t SPVM_TYPE_is_string_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  int32_t is_string_array_type;
  int32_t basic_type_is_string_type = SPVM_BASIC_TYPE_is_string_type(compiler, basic_type_id);
  if (dimension == 1 && basic_type_is_string_type && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    is_string_array_type = 1;
  }
  // Array
  else {
    is_string_array_type = 0;
  }
  
  return is_string_array_type;
}

int32_t SPVM_TYPE_is_class_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  int32_t is_class_array_type;
  int32_t basic_type_is_class_type = SPVM_BASIC_TYPE_is_class_type(compiler, basic_type_id);
  if (dimension == 1 && basic_type_is_class_type && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    is_class_array_type = 1;
  }
  // Array
  else {
    is_class_array_type = 0;
  }
  
  return is_class_array_type;
}

int32_t SPVM_TYPE_is_interface_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  int32_t is_interface_array_type;
  int32_t basic_type_is_interface_type = SPVM_BASIC_TYPE_is_interface_type(compiler, basic_type_id);
  if (dimension == 1 && basic_type_is_interface_type && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    is_interface_array_type = 1;
  }
  // Array
  else {
    is_interface_array_type = 0;
  }
  
  return is_interface_array_type;
}

int32_t SPVM_TYPE_is_muldim_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  return dimension > 1 && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF);
}

int32_t SPVM_TYPE_is_any_object_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  if (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_ANY_OBJECT && dimension == 1 && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_numeric_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  int32_t is_numeric_array_type;
  int32_t basic_type_is_numeric_type = SPVM_BASIC_TYPE_is_numeric_type(compiler, basic_type_id);
  if (dimension == 1 && basic_type_is_numeric_type && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    is_numeric_array_type = 1;
  }
  // Array
  else {
    is_numeric_array_type = 0;
  }
  
  return is_numeric_array_type;
}

int32_t SPVM_TYPE_is_undef_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  if (dimension == 0 && basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_UNDEF && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_unknown_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  if (dimension == 0 && basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_UNKNOWN && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_mulnum_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  int32_t basic_type_is_mulnum_type = SPVM_BASIC_TYPE_is_mulnum_type(compiler, basic_type_id);
  if (dimension == 0 && basic_type_is_mulnum_type && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_mulnum_ref_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  int32_t basic_type_is_mulnum_type = SPVM_BASIC_TYPE_is_mulnum_type(compiler, basic_type_id);
  if (dimension == 0 && basic_type_is_mulnum_type && (flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_mulnum_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  int32_t is_mulnum_array_type;
  int32_t basic_type_is_mulnum_type = SPVM_BASIC_TYPE_is_mulnum_type(compiler, basic_type_id);
  if (dimension == 1 && basic_type_is_mulnum_type && !(flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    is_mulnum_array_type = 1;
  }
  // Array
  else {
    is_mulnum_array_type = 0;
  }
  
  return is_mulnum_array_type;
}

int32_t SPVM_TYPE_is_user_defined_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  int32_t is_user_defined_type
    =  SPVM_TYPE_is_class_type(compiler, basic_type_id, dimension, flag)
    || SPVM_TYPE_is_interface_type(compiler, basic_type_id, dimension, flag)
    || SPVM_TYPE_is_mulnum_type(compiler, basic_type_id, dimension, flag);
  
  return is_user_defined_type;
}

int32_t SPVM_TYPE_get_type_name_length(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
  assert(basic_type);
  
  int32_t length = 0;
  
  // *
  if (flag & SPVM_NATIVE_C_TYPE_FLAG_MUTABLE) {
    length += strlen("mutable ");
  }
  
  // Basic type
  length += strlen(basic_type->name);
  
  // []
  length += dimension * 2;
  
  // *
  if (flag & SPVM_NATIVE_C_TYPE_FLAG_REF) {
    length += 1;
  }
  
  return length;
}

const char* SPVM_TYPE_new_type_name_with_eternal_flag(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag, int32_t is_permanent) {
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
  assert(basic_type);
  
  int32_t type_name_length = SPVM_TYPE_get_type_name_length(compiler, basic_type_id, dimension, flag);
  
  char* type_name;
  if (is_permanent) {
    type_name = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->current_each_compile_allocator, type_name_length + 1);
  }
  else {
    type_name = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->current_each_compile_allocator, type_name_length + 1);
  }
  
  char* cur = type_name;

  if (flag & SPVM_NATIVE_C_TYPE_FLAG_MUTABLE) {
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
  if (flag & SPVM_NATIVE_C_TYPE_FLAG_REF) {
    sprintf(cur, "*");
    cur += 1;
  }
  
  *cur = '\0';
  cur++;

  return type_name;
}

const char* SPVM_TYPE_new_type_name_tmp(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  int32_t is_permanent = 0;
  return SPVM_TYPE_new_type_name_with_eternal_flag(compiler, basic_type_id, dimension, flag, is_permanent);
}

const char* SPVM_TYPE_new_type_name(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  int32_t is_permanent = 1;
  return SPVM_TYPE_new_type_name_with_eternal_flag(compiler, basic_type_id, dimension, flag, is_permanent);
}

SPVM_TYPE* SPVM_TYPE_new(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  SPVM_TYPE* type = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->current_each_compile_allocator, sizeof(SPVM_TYPE));
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
  if (basic_type_id > 0) {
    type->unresolved_basic_type_name = basic_type->name;
  }
  type->basic_type = basic_type;
  type->dimension = dimension;
  type->flag = flag;
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_uninitialized(SPVM_COMPILER* compiler) {
  
  SPVM_TYPE* type = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->current_each_compile_allocator, sizeof(SPVM_TYPE));
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_unresolved_type(SPVM_COMPILER* compiler, const char* unresolved_basic_type_name, int32_t dimension, int32_t flag) {
  
  SPVM_TYPE* type = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->current_each_compile_allocator, sizeof(SPVM_TYPE));
  type->unresolved_basic_type_name = unresolved_basic_type_name;
  type->basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_UNKNOWN);
  type->dimension = dimension;
  type->flag = flag;
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_void_type(SPVM_COMPILER* compiler) {
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_VOID);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_any_object_array_type(SPVM_COMPILER* compiler) {
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_ANY_OBJECT);
  int32_t type_dimension = 1;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_undef_type(SPVM_COMPILER* compiler) {
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_UNDEF);
  
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_byte_type(SPVM_COMPILER* compiler) {
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_short_type(SPVM_COMPILER* compiler) {
  

  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_int_type(SPVM_COMPILER* compiler) {
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_INT);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_long_type(SPVM_COMPILER* compiler) {
  

  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_LONG);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_float_type(SPVM_COMPILER* compiler) {
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_double_type(SPVM_COMPILER* compiler) {
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_string_type(SPVM_COMPILER* compiler) {
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_STRING);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_object_type(SPVM_COMPILER* compiler) {
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_ANY_OBJECT);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_byte_object_type(SPVM_COMPILER* compiler) {
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE_CLASS);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_short_object_type(SPVM_COMPILER* compiler) {
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT_CLASS);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_int_object_type(SPVM_COMPILER* compiler) {
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_INT_CLASS);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_long_object_type(SPVM_COMPILER* compiler) {
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_LONG_CLASS);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_float_object_type(SPVM_COMPILER* compiler) {
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT_CLASS);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_double_object_type(SPVM_COMPILER* compiler) {
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE_CLASS);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_bool_object_type(SPVM_COMPILER* compiler) {
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_BOOL_CLASS);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_byte_ref_type(SPVM_COMPILER* compiler) {
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE);
  int32_t type_dimension = 0;
  int32_t type_flag = SPVM_NATIVE_C_TYPE_FLAG_REF;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_short_ref_type(SPVM_COMPILER* compiler) {
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT);
  int32_t type_dimension = 0;
  int32_t type_flag = SPVM_NATIVE_C_TYPE_FLAG_REF;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_int_ref_type(SPVM_COMPILER* compiler) {
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_INT);
  int32_t type_dimension = 0;
  int32_t type_flag = SPVM_NATIVE_C_TYPE_FLAG_REF;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_long_ref_type(SPVM_COMPILER* compiler) {
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_LONG);
  int32_t type_dimension = 0;
  int32_t type_flag = SPVM_NATIVE_C_TYPE_FLAG_REF;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_float_ref_type(SPVM_COMPILER* compiler) {
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT);
  int32_t type_dimension = 0;
  int32_t type_flag = SPVM_NATIVE_C_TYPE_FLAG_REF;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);

  return type;
}

SPVM_TYPE* SPVM_TYPE_new_double_ref_type(SPVM_COMPILER* compiler) {
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE);
  int32_t type_dimension = 0;
  int32_t type_flag = SPVM_NATIVE_C_TYPE_FLAG_REF;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_any_object_type(SPVM_COMPILER* compiler) {
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_ANY_OBJECT);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_element_type(SPVM_COMPILER* compiler) {
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_NATIVE_C_BASIC_TYPE_ID_ANY_OBJECT);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

int32_t SPVM_TYPE_get_type_width(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  int32_t is_mulnum_type = SPVM_TYPE_is_mulnum_type(compiler, basic_type_id, dimension, flag);
  
  int32_t type_width = -1;
  if (is_mulnum_type) {
    
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    assert(basic_type);
    
    type_width = basic_type->fields->length;
  }
  else {
    type_width = 1;
  }
  
  return type_width;
}

int32_t SPVM_TYPE_get_field_order(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  int32_t is_mulnum_type = SPVM_TYPE_is_mulnum_type(compiler, basic_type_id, dimension, flag);
  
  int32_t type_order = 100;
  if (SPVM_TYPE_is_object_type(compiler, basic_type_id, dimension, flag)) {
    type_order = 1;
  }
  else if (SPVM_TYPE_is_double_type(compiler, basic_type_id, dimension, flag)) {
    type_order = 2;
  }
  else if (SPVM_TYPE_is_long_type(compiler, basic_type_id, dimension, flag)) {
    type_order = 3;
  }
  else if (SPVM_TYPE_is_float_type(compiler, basic_type_id, dimension, flag)) {
    type_order = 4;
  }
  else if (SPVM_TYPE_is_int_type(compiler, basic_type_id, dimension, flag)) {
    type_order = 5;
  }
  else if (SPVM_TYPE_is_short_type(compiler, basic_type_id, dimension, flag)) {
    type_order = 6;
  }
  else if (SPVM_TYPE_is_byte_type(compiler, basic_type_id, dimension, flag)) {
    type_order = 7;
  }
  
  return type_order;
}

int32_t SPVM_TYPE_get_mulnum_field_basic_type_id(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  int32_t mulnum_field_basic_type_id;
  if (SPVM_TYPE_is_mulnum_type(compiler, basic_type_id, dimension, flag) || SPVM_TYPE_is_mulnum_ref_type(compiler, basic_type_id, dimension, flag)) {
    
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    assert(basic_type);
    
    assert(basic_type->fields->length > 0);
    
    SPVM_FIELD* mulnum_field = SPVM_LIST_get(basic_type->fields, 0);
    
    SPVM_TYPE* mulnum_field_type = mulnum_field->type;
    
    mulnum_field_basic_type_id = mulnum_field_type->basic_type->id;
  }
  else {
    mulnum_field_basic_type_id = -1;
  }
  
  return mulnum_field_basic_type_id;
}

int32_t SPVM_TYPE_satisfy_assignment_requirement(
  SPVM_COMPILER* compiler,
  int32_t dist_type_basic_type_id, int32_t dist_type_dimension, int32_t dist_type_flag,
  int32_t src_type_basic_type_id, int32_t src_type_dimension, int32_t src_type_flag,
  int32_t* need_data_conversion, int32_t allow_narrowing_conversion, int32_t interface_match,
  char* error_reason)
{
  
  // Dist type is numeric type
  int32_t can_assign = 0;
  if (SPVM_TYPE_is_numeric_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Soruce type is numeric type
    if (SPVM_TYPE_is_numeric_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      // Dist type is same as source type
      if (src_type_basic_type_id == dist_type_basic_type_id) {
        can_assign = 1;
      }
      // Dist type is more wide than source type
      else if (dist_type_basic_type_id > src_type_basic_type_id) {
        can_assign = 1;
        *need_data_conversion = 1;
      }
      // Dist type is narrow than source type
      else if (dist_type_basic_type_id < src_type_basic_type_id) {
        if (allow_narrowing_conversion) {
          can_assign = 1;
          *need_data_conversion = 1;
        }
        else {
          can_assign = 0;
        }
      }
    }
    // Source type is object type
    else if (SPVM_TYPE_is_object_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      // Source type is the corresponding numeric object type
      if (SPVM_TYPE_is_numeric_object_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
        if (src_type_basic_type_id == dist_type_basic_type_id + SPVM_BASIC_TYPE_C_NUMERIC_OBJECT_UPGRADE_SHIFT) {
          can_assign = 1;
          *need_data_conversion = 1;
        }
        else {
          can_assign = 0;
        }
      }
      // Source type is any object type
      else if (SPVM_TYPE_is_any_object_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
        can_assign = 1;
        *need_data_conversion = 1;
      }
      else {
        can_assign = 0;
      }
    }
    // Source type is other type
    else {
      can_assign = 0;
    }
  }
  // Dist type is multi numeric type
  else if (SPVM_TYPE_is_mulnum_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type is multi numeric type
    if (SPVM_TYPE_is_mulnum_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      if (SPVM_TYPE_equals(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
        can_assign = 1;
      }
      else {
        can_assign = 0;
      }
    }
    // Source type is other type
    else {
      can_assign = 0;
    }
  }
  // Dist type is referece type
  else if (SPVM_TYPE_is_ref_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type is referece type
    if (SPVM_TYPE_is_ref_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      if (SPVM_TYPE_equals(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
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
    // Source type is other type
    else {
      can_assign = 0;
    }
  }
  // Dist type is string type
  else if (SPVM_TYPE_is_string_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type is string
    if (SPVM_TYPE_is_string_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      // Mutable check
      if(dist_type_flag & SPVM_NATIVE_C_TYPE_FLAG_MUTABLE && !(src_type_flag & SPVM_NATIVE_C_TYPE_FLAG_MUTABLE)) {
        can_assign = 0;
      }
      else {
        can_assign = 1;
      }
    }
    // Source type is numeric type
    else if (SPVM_TYPE_is_numeric_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = 1;
      *need_data_conversion = 1;
    }
    // Source type is undef type
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = 1;
    }
    // Source type is other type
    else {
      can_assign = 0;
    }
  }
  // Dist type is numeric object type
  else if (SPVM_TYPE_is_numeric_object_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type is numeric type
    if (SPVM_TYPE_is_numeric_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      if (dist_type_basic_type_id == src_type_basic_type_id + SPVM_BASIC_TYPE_C_NUMERIC_OBJECT_UPGRADE_SHIFT) {
        can_assign = 1;
        *need_data_conversion = 1;
      }
      else {
        can_assign = 0;
      }
    }
    // Source type is numeric object type
    else if (SPVM_TYPE_is_numeric_object_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      if (src_type_basic_type_id == dist_type_basic_type_id) {
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
    // Source type is other type
    else {
      can_assign = 0;
    }
  }
  // Dist type is class
  else if (SPVM_TYPE_is_class_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type is class type
    if (SPVM_TYPE_is_class_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      if (src_type_basic_type_id == dist_type_basic_type_id) {
        can_assign = 1;
      }
      else if (SPVM_BASIC_TYPE_is_super_class(compiler, dist_type_basic_type_id, src_type_basic_type_id)) {
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
    // Source type is other type
    else {
      can_assign = 0;
    }
  }
  // Dist type is interface type
  else if (SPVM_TYPE_is_interface_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    if (interface_match) {
      // Source type is interface type
      if (SPVM_TYPE_is_object_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
        if (SPVM_TYPE_equals(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
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
      // Source type is other type
      else {
        can_assign = 0;
      }
    }
    else {
      // Source type is interface type
      if (SPVM_TYPE_is_interface_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
        if (SPVM_TYPE_equals(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
          can_assign = 1;
        }
        else {
          can_assign = SPVM_BASIC_TYPE_has_interface(compiler, src_type_basic_type_id, dist_type_basic_type_id, error_reason);
        }
      }
      // Source type is class type
      else if (SPVM_TYPE_is_class_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
        can_assign = SPVM_BASIC_TYPE_has_interface(compiler, src_type_basic_type_id, dist_type_basic_type_id, error_reason);
      }
      // Source type is undef type
      else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
        can_assign = 1;
      }
      // Source type is other type
      else {
        can_assign = 0;
      }
    }
  }
  // Dist type is any object type
  else if (SPVM_TYPE_is_any_object_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type is numeric type
    if (SPVM_TYPE_is_numeric_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = 1;
      *need_data_conversion = 1;
    }
    // Source type is object type
    else if (SPVM_TYPE_is_object_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = 1;
    }
    // Source type is undef type
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = 1;
    }
    // Source type is void type
    else if (SPVM_TYPE_is_void_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = 1;
    }
    // Source type is other type
    else {
      can_assign = 0;
    }
  }
  // Dist type is undef type
  else if (SPVM_TYPE_is_undef_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    can_assign = 0;
  }
  // Dist type is numeric array type
  else if (SPVM_TYPE_is_numeric_array_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type is numeric array type
    if (SPVM_TYPE_is_numeric_array_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      if (SPVM_TYPE_equals(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
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
    // Source type is other type
    else {
      can_assign = 0;
    }
  }
  // Dist type is multi-numeric array type
  else if (SPVM_TYPE_is_mulnum_array_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type is mulnum array type
    if (SPVM_TYPE_is_mulnum_array_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      if (SPVM_TYPE_equals(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
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
    // Source type is other type
    else {
      can_assign = 0;
    }
  }
  // Dist type is string array type
  else if (SPVM_TYPE_is_string_array_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type is string array type
    if (SPVM_TYPE_is_string_array_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = 1;
    }
    // Source type is undef type
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = 1;
    }
    // Source type is other type
    else {
      can_assign = 0;
    }
  }
  // Dist type is class array type
  else if (SPVM_TYPE_is_class_array_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type is class array type
    if (SPVM_TYPE_is_class_array_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      if (SPVM_TYPE_equals(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
        can_assign = 1;
      }
      else if (SPVM_BASIC_TYPE_is_super_class(compiler, dist_type_basic_type_id, src_type_basic_type_id)) {
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
    // Source type is other type
    else {
      can_assign = 0;
    }
  }
  // Dist type is interface array type
  else if (SPVM_TYPE_is_interface_array_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type is interface array type
    if (SPVM_TYPE_is_interface_array_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      if (SPVM_TYPE_equals(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
        can_assign = 1;
      }
      else {
        can_assign = SPVM_BASIC_TYPE_has_interface(compiler, src_type_basic_type_id, dist_type_basic_type_id, error_reason);
      }
    }
    // Source type is class array type
    else if (SPVM_TYPE_is_class_array_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = SPVM_BASIC_TYPE_has_interface(compiler, src_type_basic_type_id, dist_type_basic_type_id, error_reason);
    }
    // Source type is undef type
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = 1;
    }
    // Source type is other type
    else {
      can_assign = 0;
    }
  }
  // Dist type is any object array
  else if (SPVM_TYPE_is_any_object_array_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type is object array type
    if (SPVM_TYPE_is_object_array_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = 1;
    }
    // Source type is undef type
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = 1;
    }
    // Source type is other type
    else {
      can_assign = 0;
    }
  }
  // Dist type is multi-dimensional array type
  else if (SPVM_TYPE_is_muldim_array_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type is multi-dimensional array type
    if (SPVM_TYPE_is_muldim_array_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      // Source type dimension equals dist type dimension
      if (src_type_dimension == dist_type_dimension) {
        // Source base type equals dist basic type
        if (src_type_basic_type_id == dist_type_basic_type_id) {
          can_assign = 1;
        }
        // Source basic type is a sub class of dist type
        else if (SPVM_BASIC_TYPE_is_super_class(compiler, dist_type_basic_type_id, src_type_basic_type_id)) {
          can_assign = 1;
        }
        else {
          // Dist basic type is interface type
          if (SPVM_BASIC_TYPE_is_interface_type(compiler, dist_type_basic_type_id)) {
            // Source basic type is interface type
            if (SPVM_BASIC_TYPE_is_interface_type(compiler, src_type_basic_type_id)) {
              can_assign = SPVM_BASIC_TYPE_has_interface(compiler, src_type_basic_type_id, dist_type_basic_type_id, error_reason);
            }
            // Source basic type is class type
            else if (SPVM_BASIC_TYPE_is_class_type(compiler, src_type_basic_type_id)) {
              can_assign = SPVM_BASIC_TYPE_has_interface(compiler, src_type_basic_type_id, dist_type_basic_type_id, error_reason);
            }
            // Source basic type is other type
            else {
              can_assign = 0;
            }
          }
          // Dist basic type is other type
          else {
            can_assign = 0;
          }
        }
      }
      // Source type dimension doesn't equal dist type dimension
      else {
        can_assign = 0;
      }
    }
    // Source type is undef type
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = 1;
    }
    // Source type is other type
    else {
      can_assign = 0;
    }
  }
  // Dist type is the void type
  else if (SPVM_TYPE_is_void_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    if (SPVM_TYPE_is_void_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_assign = 1;
    }
    else {
      can_assign = 0;
    }
  }
  else {
    fprintf(stderr, "[Unexpected Error]Unexpected Type:Basic Type ID:%d, Type Dimension:%d, Type Flag:%d\n", dist_type_basic_type_id, dist_type_dimension, dist_type_flag);
    assert(0);
  }
  
  return can_assign;
}

int32_t SPVM_TYPE_satisfy_assignment_requirement_without_data_conversion(
  SPVM_COMPILER* compiler,
  int32_t dist_type_basic_type_id, int32_t dist_type_dimension, int32_t dist_type_flag,
  int32_t src_type_basic_type_id, int32_t src_type_dimension, int32_t src_type_flag,
  char* error_reason)
{
  int32_t need_data_conversion = 0;
  int32_t allow_narrowing_conversion = 0;
  int32_t interface_match = 0;
  
  int32_t satisfy_assignment_requirement = SPVM_TYPE_satisfy_assignment_requirement(
    compiler,
    dist_type_basic_type_id, dist_type_dimension, dist_type_flag,
    src_type_basic_type_id, src_type_dimension, src_type_flag,
    &need_data_conversion, allow_narrowing_conversion, interface_match,
    error_reason
  );
  
  int32_t satisfy_assignment_requirement_without_data_conversion = 0;
  if (satisfy_assignment_requirement && !need_data_conversion) {
    satisfy_assignment_requirement_without_data_conversion = 1;
  }
  
  return satisfy_assignment_requirement_without_data_conversion;
}

int32_t SPVM_TYPE_satisfy_assignment_requirement_without_data_conversion_with_interface_match(
  SPVM_COMPILER* compiler,
  int32_t dist_type_basic_type_id, int32_t dist_type_dimension, int32_t dist_type_flag,
  int32_t src_type_basic_type_id, int32_t src_type_dimension, int32_t src_type_flag,
  char* error_reason)
{
  int32_t need_data_conversion = 0;
  int32_t allow_narrowing_conversion = 0;
  int32_t interface_match = 1;
  
  int32_t satisfy_assignment_requirement = SPVM_TYPE_satisfy_assignment_requirement(
    compiler,
    dist_type_basic_type_id, dist_type_dimension, dist_type_flag,
    src_type_basic_type_id, src_type_dimension, src_type_flag,
    &need_data_conversion, allow_narrowing_conversion, interface_match,
    error_reason
  );
  
  int32_t satisfy_assignment_requirement_without_data_conversion_with_interface_match = 0;
  if (satisfy_assignment_requirement && !need_data_conversion) {
    satisfy_assignment_requirement_without_data_conversion_with_interface_match = 1;
  }
  
  return satisfy_assignment_requirement_without_data_conversion_with_interface_match;
}

int32_t SPVM_TYPE_satisfy_cast_requirement(
  SPVM_COMPILER* compiler,
  int32_t dist_type_basic_type_id, int32_t dist_type_dimension, int32_t dist_type_flag,
  int32_t src_type_basic_type_id, int32_t src_type_dimension, int32_t src_type_flag,
  char* error_reason)
{
  int32_t can_cast;
  
  // Dist type is numeric type
  if (SPVM_TYPE_is_numeric_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type is numeric type
    if (SPVM_TYPE_is_numeric_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is numeric object type
    else if (SPVM_TYPE_is_numeric_object_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      if (dist_type_basic_type_id + SPVM_BASIC_TYPE_C_NUMERIC_OBJECT_UPGRADE_SHIFT == src_type_basic_type_id) {
        can_cast = 1;
      }
      else {
        can_cast = 0;
      }
    }
    // Source type is any object type
    else if (SPVM_TYPE_is_any_object_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is string type
    else if (SPVM_TYPE_is_string_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is other type
    else {
      can_cast = 0;
    }
  }
  // Dist type is multi-numeric type
  else if (SPVM_TYPE_is_mulnum_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type equals dist type
    if (SPVM_TYPE_equals(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag, src_type_basic_type_id, src_type_dimension, src_type_flag) && dist_type_flag == src_type_flag) {
      can_cast = 1;
    }
    // Source type is other type
    else {
      can_cast = 0;
    }
  }
  // Dist type is reference type
  else if (SPVM_TYPE_is_ref_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type equals dist type
    if (SPVM_TYPE_equals(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag, src_type_basic_type_id, src_type_dimension, src_type_flag) && dist_type_flag == src_type_flag) {
      can_cast = 1;
    }
    // Source type is undef type
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is other type
    else {
      can_cast = 0;
    }
  }
  // Dist type is string type
  else if (SPVM_TYPE_is_string_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type is string type
    if (SPVM_TYPE_is_string_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is numeric type
    else if (SPVM_TYPE_is_numeric_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is byte array type
    else if (SPVM_TYPE_is_byte_array_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is any object type
    else if (SPVM_TYPE_is_any_object_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is undef type
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is other type
    else {
      can_cast = 0;
    }
  }
  // Dist type is numeric object type
  else if (SPVM_TYPE_is_numeric_object_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type is numeric type
    if (SPVM_TYPE_is_numeric_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      if (dist_type_basic_type_id == src_type_basic_type_id + SPVM_BASIC_TYPE_C_NUMERIC_OBJECT_UPGRADE_SHIFT) {
        can_cast = 1;
      }
      else {
        can_cast = 0;
      }
    }
    // Source type is any object type
    else if (SPVM_TYPE_is_any_object_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is undef type
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is other type
    else {
      can_cast = 0;
    }
  }
  // Dist type is class type
  else if (SPVM_TYPE_is_class_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type is class type
    if (SPVM_TYPE_is_class_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      if (src_type_basic_type_id == dist_type_basic_type_id) {
        can_cast = 1;
      }
      else if (SPVM_BASIC_TYPE_is_super_class(compiler, dist_type_basic_type_id, src_type_basic_type_id)) {
        can_cast = 1;
      }
      else if (SPVM_BASIC_TYPE_is_super_class(compiler, src_type_basic_type_id, dist_type_basic_type_id)) {
        can_cast = 1;
      }
      else {
        can_cast = 0;
      }
    }
    // Source type is interface type
    else if (SPVM_TYPE_is_interface_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = SPVM_BASIC_TYPE_has_interface(compiler, dist_type_basic_type_id, src_type_basic_type_id, error_reason);
    }
    // Source type is any object type
    else if (SPVM_TYPE_is_any_object_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is undef type
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is other type
    else {
      can_cast = 0;
    }
  }
  // Dist type is interface type
  else if (SPVM_TYPE_is_interface_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type is class type
    if (SPVM_TYPE_is_class_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = SPVM_BASIC_TYPE_has_interface(compiler, src_type_basic_type_id, dist_type_basic_type_id, error_reason);
    }
    // Source type is interface type
    else if (SPVM_TYPE_is_interface_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = SPVM_BASIC_TYPE_has_interface(compiler, src_type_basic_type_id, dist_type_basic_type_id, error_reason);
    }
    // Source type is any object type
    else if (SPVM_TYPE_is_any_object_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is undef type
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is other type
    else {
      can_cast = 0;
    }
  }
  // Dist type is any object type
  else if (SPVM_TYPE_is_any_object_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type is numeric type
    if (SPVM_TYPE_is_numeric_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is object type
    else if (SPVM_TYPE_is_object_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is undef type
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is other type
    else {
      can_cast = 0;
    }
  }
  // Dist type is undef type
  else if (SPVM_TYPE_is_undef_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    assert(0);
  }
  // Dist type is byte array type
  else if (SPVM_TYPE_is_byte_array_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type is string type
    if (SPVM_TYPE_is_string_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is byte array type
    else if (SPVM_TYPE_is_byte_array_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is any object type
    else if (SPVM_TYPE_is_any_object_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is undef type
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is other type
    else {
      can_cast = 0;
    }
  }
  // Dist type is numeric array type(except for byte array)
  else if (SPVM_TYPE_is_numeric_array_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type equals dist type
    if (src_type_basic_type_id == dist_type_basic_type_id) {
      can_cast = 1;
    }
    // Source type is any object type
    else if (SPVM_TYPE_is_any_object_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is undef type
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is other type
    else {
      can_cast = 0;
    }
  }
  // Dist type is multi-numeric array
  else if (SPVM_TYPE_is_mulnum_array_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type equals dist type
    if (src_type_basic_type_id == dist_type_basic_type_id) {
      can_cast = 1;
    }
    // Source type is any object type
    else if (SPVM_TYPE_is_any_object_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is undef type
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is other type
    else {
      can_cast = 0;
    }
  }
  // Dist type is string array
  else if (SPVM_TYPE_is_string_array_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type is string type
    if (SPVM_TYPE_is_string_array_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is any object type
    else if (SPVM_TYPE_is_any_object_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is any object array type
    else if (SPVM_TYPE_is_any_object_array_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is undef type
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is other type
    else {
      can_cast = 0;
    }
  }
  // Dist type is class array type
  else if (SPVM_TYPE_is_class_array_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type is class array type
    if (SPVM_TYPE_is_class_array_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      if (src_type_basic_type_id == dist_type_basic_type_id) {
        can_cast = 1;
      }
      else if (SPVM_BASIC_TYPE_is_super_class(compiler, dist_type_basic_type_id, src_type_basic_type_id)) {
        can_cast = 1;
      }
      else if (SPVM_BASIC_TYPE_is_super_class(compiler, src_type_basic_type_id, dist_type_basic_type_id)) {
        can_cast = 1;
      }
      else {
        can_cast = 0;
      }
    }
    // Source type is interface array type
    else if (SPVM_TYPE_is_interface_array_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = SPVM_BASIC_TYPE_has_interface(compiler, dist_type_basic_type_id, src_type_basic_type_id, error_reason);
    }
    // Source type is any object type
    else if (SPVM_TYPE_is_any_object_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is any object array type
    else if (SPVM_TYPE_is_any_object_array_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is undef type
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is other type
    else {
      can_cast = 0;
    }
  }
  // Dist type is interface array type
  else if (SPVM_TYPE_is_interface_array_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type is class array type
    if (SPVM_TYPE_is_class_array_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = SPVM_BASIC_TYPE_has_interface(compiler, src_type_basic_type_id, dist_type_basic_type_id, error_reason);
    }
    // Source type is interface array type
    else if (SPVM_TYPE_is_interface_array_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = SPVM_BASIC_TYPE_has_interface(compiler, src_type_basic_type_id, dist_type_basic_type_id, error_reason);
    }
    // Source type is any object type
    else if (SPVM_TYPE_is_any_object_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is any object array type
    else if (SPVM_TYPE_is_any_object_array_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is undef type
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is other type
    else {
      can_cast = 0;
    }
  }
  // Dist type is any object array type
  else if (SPVM_TYPE_is_any_object_array_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type is any object type
    if (SPVM_TYPE_is_any_object_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is object array type
    else if (SPVM_TYPE_is_object_array_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is undef type
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is other type
    else {
      can_cast = 0;
    }
  }
  // Dist type is multi-dimensional array type
  else if (SPVM_TYPE_is_muldim_array_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
    // Source type is multi-dimensional array type
    if (SPVM_TYPE_is_muldim_array_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      // Source type dimension equals dist type dimension
      if (src_type_dimension == dist_type_dimension) {
        // Source base type equals dist basic type
        if (src_type_basic_type_id == dist_type_basic_type_id) {
          can_cast = 1;
        }
        // Source basic type is a sub class of dist type
        else if (SPVM_BASIC_TYPE_is_super_class(compiler, dist_type_basic_type_id, src_type_basic_type_id)) {
          can_cast = 1;
        }
        // Source basic type is a super class of dist type
        else if (SPVM_BASIC_TYPE_is_super_class(compiler, src_type_basic_type_id, dist_type_basic_type_id)) {
          can_cast = 1;
        }
        else {
          // Dist basic type is class type
          if (SPVM_BASIC_TYPE_is_class_type(compiler, dist_type_basic_type_id)) {
            // Source basic type is interface type
            if (SPVM_BASIC_TYPE_is_interface_type(compiler, src_type_basic_type_id)) {
              can_cast = SPVM_BASIC_TYPE_has_interface(compiler, src_type_basic_type_id, dist_type_basic_type_id, error_reason);
            }
            // Source basic type is other type
            else {
              can_cast = 0;
            }
          }
          // Dist basic type is interface type
          else if (SPVM_BASIC_TYPE_is_interface_type(compiler, dist_type_basic_type_id)) {
            // Source basic type is class type
            if (SPVM_BASIC_TYPE_is_class_type(compiler, src_type_basic_type_id)) {
              can_cast = SPVM_BASIC_TYPE_has_interface(compiler, src_type_basic_type_id, dist_type_basic_type_id, error_reason);
            }
            // Source basic type is interface type
            else if (SPVM_BASIC_TYPE_is_interface_type(compiler, src_type_basic_type_id)) {
              can_cast = SPVM_BASIC_TYPE_has_interface(compiler, src_type_basic_type_id, dist_type_basic_type_id, error_reason);
            }
            // Source basic type is other type
            else {
              can_cast = 0;
            }
          }
          // Dist basic type is other type
          else {
            can_cast = 0;
          }
        }
      }
      // Source type dimension doesn't equal dist type dimension
      else {
        can_cast = 0;
      }
    }
    // Source type is any object type
    else if (SPVM_TYPE_is_any_object_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is any object array type
    else if (SPVM_TYPE_is_any_object_array_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is undef type
    else if (SPVM_TYPE_is_undef_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
      can_cast = 1;
    }
    // Source type is other type
    else {
      can_cast = 0;
    }
  }
  else {
    assert(0);
  }
  
  return can_cast;
}

int32_t SPVM_TYPE_equals(SPVM_COMPILER* compiler, int32_t basic_type_id1, int32_t type_dimension1, int32_t type_flag1, int32_t basic_type_id2, int32_t type_dimension2, int32_t type_flag2) {
  
  if (basic_type_id1 == basic_type_id2 && type_dimension1 == type_dimension2 && type_flag1 == type_flag2) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_satisfy_interface_method_requirement(SPVM_COMPILER* compiler, SPVM_METHOD* dist_method, SPVM_METHOD* src_method, char* error_reason) {
  
  assert(src_method);
  
  assert(dist_method);
  
  SPVM_BASIC_TYPE* dist_basic_type = dist_method->current_basic_type;
  
  SPVM_BASIC_TYPE* src_basic_type = src_method->current_basic_type;
  
  const char* dist_basic_type_category_name = NULL;
  if (dist_basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS) {
    dist_basic_type_category_name = "class";
  }
  else if (dist_basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE) {
    dist_basic_type_category_name = "interface";
  }
  
  const char* src_basic_type_category_name = NULL;
  if (src_basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS) {
    src_basic_type_category_name = "class";
  }
  else if (src_basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE) {
    src_basic_type_category_name = "interface";
  }
  
  SPVM_LIST* src_method_var_decls = src_method->var_decls;
  
  SPVM_LIST* dist_method_var_decls = dist_method->var_decls;
  
  if (src_method->is_class_method) {
    if (error_reason) {
      snprintf(error_reason, SPVM_COMPILER_C_ERROR_REASON_SIZE, "%s#%s method must be an instance method because its interface method is defined in %s %s.\n  at %s line %d", src_basic_type->name, src_method->name, dist_basic_type->name, dist_basic_type_category_name, src_method->op_method->file, src_method->op_method->line);
    }
    return 0;
  }
  
  if (dist_method->is_class_method) {
    if (error_reason) {
      snprintf(error_reason, SPVM_COMPILER_C_ERROR_REASON_SIZE, "%s#%s method must be an instance method.\n  at %s line %d", dist_basic_type->name, dist_method->name, dist_method->op_method->file, dist_method->op_method->line);
    }
    return 0;
  }
  
  if (!(dist_method->args_length >= src_method->required_args_length)) {
    
    if (error_reason) {
      snprintf(error_reason, SPVM_COMPILER_C_ERROR_REASON_SIZE, "The length of the arguments of %s#%s method must be greater than or equal to the length of the required arguments of %s#%s method.\n  at %s line %d", dist_basic_type->name, dist_method->name, src_basic_type->name, src_method->name, dist_method->op_method->file, dist_method->op_method->line);
    }
    return 0;
  }

  for (int32_t arg_index = 1; arg_index < dist_method->args_length; arg_index++) {
    if (arg_index > src_method->args_length - 1) {
      break;
    }
    
    SPVM_VAR_DECL* src_method_var_decl = SPVM_LIST_get(src_method_var_decls, arg_index);
    SPVM_VAR_DECL* dist_method_var_decl = SPVM_LIST_get(dist_method_var_decls, arg_index);
    
    SPVM_TYPE* src_method_var_decl_type = src_method_var_decl->type;
    SPVM_TYPE* dist_method_var_decl_type = dist_method_var_decl->type;
    
    int32_t can_assign = SPVM_TYPE_satisfy_assignment_requirement_without_data_conversion_with_interface_match(
      compiler,
      dist_method_var_decl_type->basic_type->id, dist_method_var_decl_type->dimension, dist_method_var_decl_type->flag,
      src_method_var_decl_type->basic_type->id, src_method_var_decl_type->dimension, src_method_var_decl_type->flag,
      NULL
    );
    
    if (!can_assign) {
      const char* src_method_var_decl_type_name = SPVM_TYPE_new_type_name(compiler, src_method_var_decl_type->basic_type->id, src_method_var_decl_type->dimension, src_method_var_decl_type->flag);
      const char* dist_method_var_decl_type_name = SPVM_TYPE_new_type_name(compiler, dist_method_var_decl_type->basic_type->id, dist_method_var_decl_type->dimension, dist_method_var_decl_type->flag);
      
      if (error_reason) {
        snprintf(error_reason, SPVM_COMPILER_C_ERROR_REASON_SIZE, "The %dth argument(%s type) of %s#%s method must be able to be assigned to the %dth argument(%s type) of %s#%s method.\n  at %s line %d", arg_index, src_method_var_decl_type_name, src_basic_type->name, src_method->name, arg_index, dist_method_var_decl_type_name, dist_basic_type->name, dist_method->name, src_method->op_method->file, src_method->op_method->line);
      }
      
      return 0;
    }
  }
  
  SPVM_TYPE* src_method_return_type = src_method->return_type;
  SPVM_TYPE* dist_method_return_type = dist_method->return_type;
  
  int32_t can_assign = SPVM_TYPE_satisfy_assignment_requirement_without_data_conversion_with_interface_match(
    compiler,
    dist_method_return_type->basic_type->id, dist_method_return_type->dimension, dist_method_return_type->flag,
    src_method_return_type->basic_type->id, src_method_return_type->dimension, src_method_return_type->flag,
    NULL
  );
  
  if (!can_assign) {
    const char* src_method_return_type_name = SPVM_TYPE_new_type_name(compiler, src_method_return_type->basic_type->id, src_method_return_type->dimension, src_method_return_type->flag);
    const char* dist_method_return_type_name = SPVM_TYPE_new_type_name(compiler, dist_method_return_type->basic_type->id, dist_method_return_type->dimension, dist_method_return_type->flag);
    
    if (error_reason) {
      snprintf(error_reason, SPVM_COMPILER_C_ERROR_REASON_SIZE, "The return type(%s type) of %s#%s method must be able to be assigned to the return type(%s type) of %s#%s method.\n  at %s line %d", src_method_return_type_name, src_basic_type->name, src_method->name, dist_method_return_type_name, dist_basic_type->name, dist_method->name, src_method->op_method->file, src_method->op_method->line);
    }
    
    return 0;
  }
  
  return 1;
}

int32_t SPVM_TYPE_has_interface(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag, int32_t interface_basic_type_id) {
  
  int32_t has_interface = 0;
  
  if (SPVM_TYPE_is_class_type(compiler, basic_type_id, dimension, flag) || SPVM_TYPE_is_interface_type(compiler, basic_type_id, dimension, flag)) {
    has_interface = SPVM_BASIC_TYPE_has_interface(compiler, basic_type_id, interface_basic_type_id, NULL);
  }
  
  return has_interface;
}

int32_t SPVM_TYPE_is_mutable_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  if (flag & SPVM_NATIVE_C_TYPE_FLAG_MUTABLE) {
    return 1;
  }
  else {
    if (SPVM_TYPE_is_array_type(compiler, basic_type_id, dimension, flag)) {
      return 1;
    }
    else {
      return 0;
    }
  }
}

