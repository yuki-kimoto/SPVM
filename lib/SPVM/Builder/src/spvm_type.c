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

const char* const* SPVM_TYPE_TYPE_CATEGORY_C_ID_NAMES(void) {

  static const char* const id_names[] = {
    "unknown"
    "fail_load",
    "undef"
    "void"
    "numeric"
    "mulnum"
    "string",
    "class",
    "interface",
    "callback",
    "any_obejct",
    "numeric_array"
    "mulnum_array"
    "string_array",
    "class_array",
    "interface_array",
    "callback_array",
    "any_obejct_array",
    "muldim_array",
    "numeric_ref"
    "mulnum_ref"
  };
  
  return id_names;
}

int32_t SPVM_TYPE_is_embedded_class_name(SPVM_COMPILER* compiler, const char* type_name) {
  int32_t is_embedded_class_name;
  if (strcmp(type_name, "Bool") == 0) {
    is_embedded_class_name = 1;
  }
  else if (strcmp(type_name, "Byte") == 0) {
    is_embedded_class_name = 1;
  }
  else if (strcmp(type_name, "Short") == 0) {
    is_embedded_class_name = 1;
  }
  else if (strcmp(type_name, "Int") == 0) {
    is_embedded_class_name = 1;
  }
  else if (strcmp(type_name, "Long") == 0) {
    is_embedded_class_name = 1;
  }
  else if (strcmp(type_name, "Float") == 0) {
    is_embedded_class_name = 1;
  }
  else if (strcmp(type_name, "Double") == 0) {
    is_embedded_class_name = 1;
  }
  else {
    is_embedded_class_name = 0;
  }
  
  return is_embedded_class_name;
}

int32_t SPVM_TYPE_get_type_category(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  int32_t type_category;
  if (SPVM_TYPE_is_void_type(compiler, basic_type_id, dimension, flag)) {
    type_category = SPVM_TYPE_C_CATEGORY_VOID;
  }
  else if (SPVM_TYPE_is_numeric_type(compiler, basic_type_id, dimension, flag)) {
    type_category = SPVM_TYPE_C_CATEGORY_NUMERIC;
  }
  else if (SPVM_TYPE_is_mulnum_type(compiler, basic_type_id, dimension, flag)) {
    type_category = SPVM_TYPE_C_CATEGORY_MULNUM;
  }
  else if (SPVM_TYPE_is_string_type(compiler, basic_type_id, dimension, flag)) {
    type_category = SPVM_TYPE_C_CATEGORY_STRING;
  }
  else if (SPVM_TYPE_is_class_type(compiler, basic_type_id, dimension, flag)) {
    type_category = SPVM_TYPE_C_CATEGORY_CLASS;
  }
  else if (SPVM_TYPE_is_interface_type(compiler, basic_type_id, dimension, flag)) {
    type_category = SPVM_TYPE_C_CATEGORY_INTERFACE;
  }
  else if (SPVM_TYPE_is_callback_type(compiler, basic_type_id, dimension, flag)) {
    type_category = SPVM_TYPE_C_CATEGORY_CALLBACK;
  }
  else if (SPVM_TYPE_is_any_object_type(compiler, basic_type_id, dimension, flag)) {
    type_category = SPVM_TYPE_C_CATEGORY_ANY_OBJECT;
  }
  else if (SPVM_TYPE_is_numeric_array_type(compiler, basic_type_id, dimension, flag)) {
    type_category = SPVM_TYPE_C_CATEGORY_NUMERIC_ARRAY;
  }
  else if (SPVM_TYPE_is_mulnum_array_type(compiler, basic_type_id, dimension, flag)) {
    type_category = SPVM_TYPE_C_CATEGORY_MULNUM_ARRAY;
  }
  else if (SPVM_TYPE_is_string_array_type(compiler, basic_type_id, dimension, flag)) {
    type_category = SPVM_TYPE_C_CATEGORY_STRING_ARRAY;
  }
  else if (SPVM_TYPE_is_any_object_array_type(compiler, basic_type_id, dimension, flag)) {
    type_category = SPVM_TYPE_C_CATEGORY_ANY_OBJECT_ARRAY;
  }
  else if (SPVM_TYPE_is_class_array_type(compiler, basic_type_id, dimension, flag)) {
    type_category = SPVM_TYPE_C_CATEGORY_CLASS_ARRAY;
  }
  else if (SPVM_TYPE_is_interface_array_type(compiler, basic_type_id, dimension, flag)) {
    type_category = SPVM_TYPE_C_CATEGORY_INTERFACE_ARRAY;
  }
  else if (SPVM_TYPE_is_callback_array_type(compiler, basic_type_id, dimension, flag)) {
    type_category = SPVM_TYPE_C_CATEGORY_CALLBACK_ARRAY;
  }
  else if (SPVM_TYPE_is_muldim_array_type(compiler, basic_type_id, dimension, flag)) {
    type_category = SPVM_TYPE_C_CATEGORY_MULDIM_ARRAY;
  }
  else if (SPVM_TYPE_is_numeric_ref_type(compiler, basic_type_id, dimension, flag)) {
    type_category = SPVM_TYPE_C_CATEGORY_NUMERIC_REF;
  }
  else if (SPVM_TYPE_is_mulnum_ref_type(compiler, basic_type_id, dimension, flag)) {
    type_category = SPVM_TYPE_C_CATEGORY_MULNUM_REF;
  }
  else if (SPVM_TYPE_is_undef_type(compiler, basic_type_id, dimension, flag)) {
    type_category = SPVM_TYPE_C_CATEGORY_UNDEF;
  }
  else if (SPVM_TYPE_is_unknown_type(compiler, basic_type_id, dimension, flag)) {
    type_category = SPVM_TYPE_C_CATEGORY_UNKNOWN;
  }
  else if (SPVM_TYPE_is_fail_load_type(compiler, basic_type_id, dimension, flag)) {
    type_category = SPVM_TYPE_C_CATEGORY_FAIL_LOAD;
  }
  else {
    assert(0);
  }
  
  return type_category;
}

int32_t SPVM_TYPE_has_callback(
  SPVM_COMPILER* compiler,
  int32_t class_basic_type_id, int32_t class_type_dimension, int32_t class_type_flag,
  int32_t callback_basic_type_id, int32_t callback_type_dimension, int32_t callback_type_flag)
{
  (void)compiler;
  
  if (class_type_dimension > 0) {
    return 0;
  }
  
  if (class_type_flag & SPVM_TYPE_C_FLAG_REF) {
    return 0;
  }

  if (callback_type_dimension > 0) {
    return 0;
  }

  if (callback_type_flag & SPVM_TYPE_C_FLAG_REF) {
    return 0;
  }

  SPVM_BASIC_TYPE* class_basic_type = SPVM_LIST_get(compiler->basic_types, class_basic_type_id);
  SPVM_BASIC_TYPE* callback_basic_type = SPVM_LIST_get(compiler->basic_types, callback_basic_type_id);
  
  SPVM_CLASS* class = class_basic_type->class;
  SPVM_CLASS* callback = callback_basic_type->class;
  
  // Class which have only anon sub
  if (class->flag & SPVM_CLASS_C_FLAG_ANON_METHOD_CLASS) {
    assert(class->methods->length == 1);
    assert(callback->methods->length == 1);
    SPVM_METHOD* method_callback = SPVM_LIST_get(callback->methods, 0);
    SPVM_METHOD* found_method = SPVM_LIST_get(class->methods, 0);
    
    if (strcmp(method_callback->signature, found_method->signature) == 0) {
      return 1;
    }
    else {
      return 0;
    }
  }
  // Normal class
  else {
    assert(callback->methods->length == 1);
    SPVM_METHOD* method_callback = SPVM_LIST_get(callback->methods, 0);
    
    SPVM_METHOD* found_method = SPVM_HASH_get(class->method_symtable, method_callback->name, strlen(method_callback->name));
    if (!found_method) {
      return 0;
    }
    
    if (strcmp(method_callback->signature, found_method->signature) == 0) {
      return 1;
    }
    else {
      return 0;
    }
  }
}

int32_t SPVM_TYPE_has_interface(
  SPVM_COMPILER* compiler,
  int32_t class_basic_type_id, int32_t class_type_dimension, int32_t class_type_flag,
  int32_t interface_basic_type_id, int32_t interface_type_dimension, int32_t interface_type_flag)
{
  (void)compiler;
  if (class_type_dimension > 0) {
    return 0;
  }
  
  if (class_type_flag & SPVM_TYPE_C_FLAG_REF) {
    return 0;
  }

  if (interface_type_dimension > 0) {
    return 0;
  }

  if (interface_type_flag & SPVM_TYPE_C_FLAG_REF) {
    return 0;
  }
  
  SPVM_BASIC_TYPE* class_basic_type = SPVM_LIST_get(compiler->basic_types, class_basic_type_id);
  SPVM_BASIC_TYPE* interface_basic_type = SPVM_LIST_get(compiler->basic_types, interface_basic_type_id);
  
  SPVM_CLASS* class = class_basic_type->class;
  SPVM_CLASS* interface = interface_basic_type->class;

  if (strcmp(class->name, interface->name) == 0) {
    return 1;
  }
  
  SPVM_CLASS* found_interface_class = SPVM_HASH_get(class->interface_class_symtable, interface->name, strlen(interface->name));
  if (found_interface_class) {
    return 1;
  }
  else {
    return 0;
  }
}

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
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_VOID);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_any_object_array_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_ANY_OBJECT);
  int32_t type_dimension = 1;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_undef_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_UNDEF);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_byte_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_BYTE);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_short_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  

  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_SHORT);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_int_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_INT);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_long_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  

  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_LONG);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_float_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_FLOAT);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_double_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_DOUBLE);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_string_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_STRING);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_object_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_ANY_OBJECT);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_byte_object_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_BYTE_OBJECT);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_short_object_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_SHORT_OBJECT);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_int_object_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_INT_OBJECT);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_long_object_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_LONG_OBJECT);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_float_object_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_FLOAT_OBJECT);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_double_object_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_DOUBLE_OBJECT);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_bool_object_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_BOOL_OBJECT);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_byte_ref_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_BYTE);
  int32_t type_dimension = 0;
  int32_t type_flag = SPVM_TYPE_C_FLAG_REF;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_short_ref_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_SHORT);
  int32_t type_dimension = 0;
  int32_t type_flag = SPVM_TYPE_C_FLAG_REF;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_int_ref_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_INT);
  int32_t type_dimension = 0;
  int32_t type_flag = SPVM_TYPE_C_FLAG_REF;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_long_ref_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_LONG);
  int32_t type_dimension = 0;
  int32_t type_flag = SPVM_TYPE_C_FLAG_REF;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_float_ref_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_FLOAT);
  int32_t type_dimension = 0;
  int32_t type_flag = SPVM_TYPE_C_FLAG_REF;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);

  return type;
}

SPVM_TYPE* SPVM_TYPE_new_double_ref_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_DOUBLE);
  int32_t type_dimension = 0;
  int32_t type_flag = SPVM_TYPE_C_FLAG_REF;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_any_object_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_ANY_OBJECT);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_new_element_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_ANY_OBJECT);
  int32_t type_dimension = 0;
  int32_t type_flag = 0;
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, basic_type->id, type_dimension, type_flag);
  
  return type;
}

int32_t SPVM_TYPE_is_byte_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_BASIC_TYPE_C_ID_BYTE) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_void_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_BASIC_TYPE_C_ID_VOID) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_short_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_BASIC_TYPE_C_ID_SHORT) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_int_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_BASIC_TYPE_C_ID_INT) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_long_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_BASIC_TYPE_C_ID_LONG) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_float_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_BASIC_TYPE_C_ID_FLOAT) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_double_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_BASIC_TYPE_C_ID_DOUBLE) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_numeric_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id >= SPVM_BASIC_TYPE_C_ID_BYTE && basic_type_id <= SPVM_BASIC_TYPE_C_ID_DOUBLE) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_numeric_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id >= SPVM_BASIC_TYPE_C_ID_BYTE_OBJECT && basic_type_id <= SPVM_BASIC_TYPE_C_ID_DOUBLE_OBJECT) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_byte_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_BASIC_TYPE_C_ID_BYTE_OBJECT) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_short_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_BASIC_TYPE_C_ID_SHORT_OBJECT) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_int_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_BASIC_TYPE_C_ID_INT_OBJECT) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_long_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_BASIC_TYPE_C_ID_LONG_OBJECT) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_float_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_BASIC_TYPE_C_ID_FLOAT_OBJECT) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_double_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_BASIC_TYPE_C_ID_DOUBLE_OBJECT) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_bool_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_BASIC_TYPE_C_ID_BOOL_OBJECT) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_numeric_ref_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id >= SPVM_BASIC_TYPE_C_ID_BYTE && basic_type_id <= SPVM_BASIC_TYPE_C_ID_DOUBLE) && (flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_integral_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id >= SPVM_BASIC_TYPE_C_ID_BYTE && basic_type_id <= SPVM_BASIC_TYPE_C_ID_LONG) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
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

int32_t SPVM_TYPE_is_object_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (SPVM_TYPE_is_array_type(compiler, basic_type_id, dimension, flag)) {
    if (SPVM_TYPE_is_any_object_array_type(compiler, basic_type_id, dimension, flag)) {
      return 1;
    }
    else {
      int32_t element_dimension = dimension - 1;
      if (SPVM_TYPE_is_ref_type(compiler, basic_type_id, element_dimension, flag)) {
        return 0;
      }
      else if (SPVM_TYPE_is_mulnum_type(compiler, basic_type_id, element_dimension, flag)) {
        return 0;
      }
      else if (SPVM_TYPE_is_array_type(compiler, basic_type_id, element_dimension, flag)) {
        return 1;
      }
      else if (SPVM_TYPE_is_string_type(compiler, basic_type_id, element_dimension, flag)) {
        return 1;
      }
      else if (SPVM_TYPE_is_class_type(compiler, basic_type_id, element_dimension, flag)) {
        return 1;
      }
      else if (SPVM_TYPE_is_callback_type(compiler, basic_type_id, element_dimension, flag)) {
        return 1;
      }
      else if (SPVM_TYPE_is_interface_type(compiler, basic_type_id, element_dimension, flag)) {
        return 1;
      }
      else if (SPVM_TYPE_is_any_object_type(compiler, basic_type_id, element_dimension, flag)) {
        return 1;
      }
      else {
        return 0;
      }
    }
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_any_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  return dimension == 0 && basic_type_id == SPVM_BASIC_TYPE_C_ID_ANY_OBJECT && !(flag & SPVM_TYPE_C_FLAG_REF);
}

int32_t SPVM_TYPE_is_class_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
  
  int32_t is_class_type;
  if (dimension == 0 && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    const char* basic_type_name = basic_type->name;
    SPVM_CLASS* class = SPVM_HASH_get(compiler->class_symtable, basic_type_name, strlen(basic_type_name));
    // Class
    if (class) {
      if (class->category == SPVM_CLASS_C_CATEGORY_CLASS) {
        is_class_type = 1;
      }
      else {
        is_class_type = 0;
      }
    }
    // Numeric type
    else {
      is_class_type = 0;
    }
  }
  // Array
  else {
    is_class_type = 0;
  }
  
  return is_class_type;
}

int32_t SPVM_TYPE_is_fail_load_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
  
  int32_t is_class_type;
  if (dimension == 0 && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    const char* basic_type_name = basic_type->name;
    SPVM_CLASS* class = SPVM_HASH_get(compiler->fail_load_class_symtable, basic_type_name, strlen(basic_type_name));
    // Class
    if (class) {
      is_class_type = 1;
    }
    // Numeric type
    else {
      is_class_type = 0;
    }
  }
  // Array
  else {
    is_class_type = 0;
  }
  
  return is_class_type;
}

int32_t SPVM_TYPE_is_callback_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
  
  int32_t is_class_type;
  if (dimension == 0 && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    const char* basic_type_name = basic_type->name;
    SPVM_CLASS* class = SPVM_HASH_get(compiler->class_symtable, basic_type_name, strlen(basic_type_name));
    // Class
    if (class) {
      if (class->category == SPVM_CLASS_C_CATEGORY_CALLBACK) {
        is_class_type = 1;
      }
      else {
        is_class_type = 0;
      }
    }
    // Numeric type
    else {
      is_class_type = 0;
    }
  }
  // Array
  else {
    is_class_type = 0;
  }
  
  return is_class_type;
}

int32_t SPVM_TYPE_is_interface_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
  
  int32_t is_interface_type;
  if (dimension == 0 && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    const char* basic_type_name = basic_type->name;
    SPVM_CLASS* class = SPVM_HASH_get(compiler->class_symtable, basic_type_name, strlen(basic_type_name));
    // Class
    if (class) {
      if (class->category == SPVM_CLASS_C_CATEGORY_INTERFACE) {
        is_interface_type = 1;
      }
      else {
        is_interface_type = 0;
      }
    }
    // Numeric type
    else {
      is_interface_type = 0;
    }
  }
  // Array
  else {
    is_interface_type = 0;
  }
  
  return is_interface_type;
}

int32_t SPVM_TYPE_is_string_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  return dimension == 0 && basic_type_id == SPVM_BASIC_TYPE_C_ID_STRING && !(flag & SPVM_TYPE_C_FLAG_REF);
}

int32_t SPVM_TYPE_is_byte_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  return dimension == 1 && basic_type_id == SPVM_BASIC_TYPE_C_ID_BYTE && !(flag & SPVM_TYPE_C_FLAG_REF);
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
  if (SPVM_TYPE_is_object_array_type(compiler, basic_type_id, dimension, flag)) {
    int32_t element_dimension = dimension - 1;
    if (SPVM_TYPE_is_string_type(compiler, basic_type_id, element_dimension, flag)) {
      is_string_array_type = 1;
    }
    else {
      is_string_array_type = 0;
    }
  }
  else {
    is_string_array_type = 0;
  }
  
  return is_string_array_type;
}

int32_t SPVM_TYPE_is_class_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  int32_t is_class_array_type;
  if (SPVM_TYPE_is_object_array_type(compiler, basic_type_id, dimension, flag)) {
    int32_t element_dimension = dimension - 1;
    if (SPVM_TYPE_is_class_type(compiler, basic_type_id, element_dimension, flag)) {
      is_class_array_type = 1;
    }
    else {
      is_class_array_type = 0;
    }
  }
  else {
    is_class_array_type = 0;
  }
  
  return is_class_array_type;
}

int32_t SPVM_TYPE_is_interface_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  int32_t is_interface_array_type;
  if (SPVM_TYPE_is_object_array_type(compiler, basic_type_id, dimension, flag)) {
    int32_t element_dimension = dimension - 1;
    if (SPVM_TYPE_is_interface_type(compiler, basic_type_id, element_dimension, flag)) {
      is_interface_array_type = 1;
    }
    else {
      is_interface_array_type = 0;
    }
  }
  else {
    is_interface_array_type = 0;
  }
  
  return is_interface_array_type;
}

int32_t SPVM_TYPE_is_callback_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  int32_t is_callback_array_type;
  if (SPVM_TYPE_is_object_array_type(compiler, basic_type_id, dimension, flag)) {
    int32_t element_dimension = dimension - 1;
    if (SPVM_TYPE_is_callback_type(compiler, basic_type_id, element_dimension, flag)) {
      is_callback_array_type = 1;
    }
    else {
      is_callback_array_type = 0;
    }
  }
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
  
  if (basic_type_id == SPVM_BASIC_TYPE_C_ID_ANY_OBJECT && dimension == 1 && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_numeric_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 1 && (basic_type_id >= SPVM_BASIC_TYPE_C_ID_BYTE && basic_type_id <= SPVM_BASIC_TYPE_C_ID_DOUBLE) && !(flag & SPVM_TYPE_C_FLAG_REF))
  {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_undef_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && basic_type_id == SPVM_BASIC_TYPE_C_ID_UNDEF && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_unknown_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && basic_type_id == SPVM_BASIC_TYPE_C_ID_UNKNOWN && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_mulnum_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
  
  int32_t is_mulnum_t;
  if (dimension == 0 && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    const char* basic_type_name = basic_type->name;
    SPVM_CLASS* class = SPVM_HASH_get(compiler->class_symtable, basic_type_name, strlen(basic_type_name));
    // Class
    if (class) {
      if (class->category == SPVM_CLASS_C_CATEGORY_MULNUM) {
        is_mulnum_t = 1;
      }
      else {
        is_mulnum_t = 0;
      }
    }
    // Numeric type
    else {
      is_mulnum_t = 0;
    }
  }
  // Array
  else {
    is_mulnum_t = 0;
  }
  
  return is_mulnum_t;
}

int32_t SPVM_TYPE_is_mulnum_ref_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
  
  int32_t is_mulnum_ref_type;
  if (dimension == 0 && (flag & SPVM_TYPE_C_FLAG_REF)) {
    const char* basic_type_name = basic_type->name;
    SPVM_CLASS* class = SPVM_HASH_get(compiler->class_symtable, basic_type_name, strlen(basic_type_name));
    // Class
    if (class) {
      if (class->category == SPVM_CLASS_C_CATEGORY_MULNUM) {
        is_mulnum_ref_type = 1;
      }
      else {
        is_mulnum_ref_type = 0;
      }
    }
    // Numeric type
    else {
      is_mulnum_ref_type = 0;
    }
  }
  // Array
  else {
    is_mulnum_ref_type = 0;
  }
  
  return is_mulnum_ref_type;
}

int32_t SPVM_TYPE_is_mulnum_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;

  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
  
  int32_t is_value_array_type;
  if (dimension == 1 && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    const char* basic_type_name = basic_type->name;
    SPVM_CLASS* class = SPVM_HASH_get(compiler->class_symtable, basic_type_name, strlen(basic_type_name));
    // Class
    if (class) {
      if (class->category == SPVM_CLASS_C_CATEGORY_MULNUM) {
        is_value_array_type = 1;
      }
      else {
        is_value_array_type = 0;
      }
    }
    // Numeric type
    else {
      is_value_array_type = 0;
    }
  }
  // Array
  else {
    is_value_array_type = 0;
  }
  
  return is_value_array_type;
}

int32_t SPVM_TYPE_basic_type_is_mulnum_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  (void)dimension;

  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
  
  int32_t is_basic_type_mulnum_t;
  const char* basic_type_name = basic_type->name;
  SPVM_CLASS* class = SPVM_HASH_get(compiler->class_symtable, basic_type_name, strlen(basic_type_name));
  
  // Class
  if (class) {
    if (class->category == SPVM_CLASS_C_CATEGORY_MULNUM) {
      is_basic_type_mulnum_t = 1;
    }
    else {
      is_basic_type_mulnum_t = 0;
    }
  }
  // Numeric type
  else {
    is_basic_type_mulnum_t = 0;
  }
  
  return is_basic_type_mulnum_t;
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

int32_t SPVM_TYPE_get_mulnum_basic_type_id(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  int32_t mulnum_basic_type_id;
  if (SPVM_TYPE_is_mulnum_type(compiler, basic_type_id, dimension, flag) || SPVM_TYPE_is_mulnum_ref_type(compiler, basic_type_id, dimension, flag)) {
    
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    assert(basic_type);
    
    SPVM_CLASS* class = basic_type->class;
    
    assert(class->fields->length > 0);
    
    SPVM_FIELD* mulnum_field = SPVM_LIST_get(class->fields, 0);
    
    SPVM_TYPE* mulnum_field_type = mulnum_field->type;
    
    mulnum_basic_type_id = mulnum_field_type->basic_type->id;
  }
  else {
    mulnum_basic_type_id = -1;
  }
  
  return mulnum_basic_type_id;
}

int32_t SPVM_TYPE_get_elem_byte_size(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  assert(!(flag & SPVM_TYPE_C_FLAG_REF));
  
  int32_t elem_byte_size;
  if (SPVM_TYPE_is_string_type(compiler, basic_type_id, dimension, flag)) {
    elem_byte_size = 1;
  }
  else if (SPVM_TYPE_is_numeric_array_type(compiler, basic_type_id, dimension, flag)) {
    if (basic_type_id == SPVM_BASIC_TYPE_C_ID_BYTE) {
      elem_byte_size = 1;
    }
    else if (basic_type_id == SPVM_BASIC_TYPE_C_ID_SHORT) {
      elem_byte_size = 2;
    }
    else if (basic_type_id == SPVM_BASIC_TYPE_C_ID_INT || basic_type_id == SPVM_BASIC_TYPE_C_ID_FLOAT) {
      elem_byte_size = 4;
    }
    else if (basic_type_id == SPVM_BASIC_TYPE_C_ID_LONG || basic_type_id == SPVM_BASIC_TYPE_C_ID_DOUBLE) {
      elem_byte_size = 8;
    }
    else {
      assert(0);
    }
  }
  else if (SPVM_TYPE_is_mulnum_array_type(compiler, basic_type_id, dimension, flag)) {
    
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    if (!basic_type) {
      elem_byte_size = 0;
    }
    
    SPVM_CLASS* class = basic_type->class;
    
    int32_t width = class->fields->length;
    SPVM_FIELD* mulnum_field = (SPVM_FIELD*)SPVM_LIST_get(class->fields, 0);
    int32_t mulnum_field_basic_type_id = mulnum_field->type->basic_type->id;
    
    if (mulnum_field_basic_type_id == SPVM_BASIC_TYPE_C_ID_BYTE) {
      elem_byte_size = 1 * width;
    }
    else if (mulnum_field_basic_type_id == SPVM_BASIC_TYPE_C_ID_SHORT) {
      elem_byte_size = 2 * width;
    }
    else if (mulnum_field_basic_type_id == SPVM_BASIC_TYPE_C_ID_INT || mulnum_field_basic_type_id == SPVM_BASIC_TYPE_C_ID_FLOAT) {
      elem_byte_size = 4 * width;
    }
    else if (mulnum_field_basic_type_id == SPVM_BASIC_TYPE_C_ID_LONG || mulnum_field_basic_type_id == SPVM_BASIC_TYPE_C_ID_DOUBLE) {
      elem_byte_size = 8 * width;
    }
    else {
      assert(0);
    }
  }
  else if (SPVM_TYPE_is_object_array_type(compiler, basic_type_id, dimension, flag)) {
    elem_byte_size = sizeof(void*);
  }
  else {
    assert(0);
  }
  
  return elem_byte_size;
}
