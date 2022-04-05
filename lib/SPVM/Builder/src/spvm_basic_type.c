#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "spvm_compiler.h"
#include "spvm_basic_type.h"
#include "spvm_allocator.h"
#include "spvm_class.h"
#include "spvm_list.h"
#include "spvm_hash.h"

const char* const* SPVM_BASIC_TYPE_C_ID_NAMES(void) {

  static const char* const id_names[] = {
    "unknown",
    "undef",
    "void",
    "byte",
    "short",
    "int",
    "long",
    "float",
    "double",
    "string",
    "object",
    "Byte",
    "Short",
    "Int",
    "Long",
    "Float",
    "Double",
    "Bool",
  };
  
  return id_names;
}

const char* const* SPVM_BASIC_TYPE_C_CATEGORY_NAMES(void) {

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
  };
  
  return id_names;
}

SPVM_BASIC_TYPE* SPVM_BASIC_TYPE_new(SPVM_COMPILER* compiler) {
  SPVM_BASIC_TYPE* basic_type = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, sizeof(SPVM_BASIC_TYPE));
  
  return basic_type;
}

const char* SPVM_BASIC_TYPE_get_basic_type_name(int32_t basic_type_id) {
  return (SPVM_BASIC_TYPE_C_ID_NAMES())[basic_type_id];
}

int32_t SPVM_TYPE_get_category(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_BASIC_TYPE_get_category(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  
  int32_t category;
  if (SPVM_BASIC_TYPE_is_void_type(compiler, basic_type_id)) {
    category = SPVM_BASIC_TYPE_C_CATEGORY_VOID;
  }
  else if (SPVM_BASIC_TYPE_is_numeric_type(compiler, basic_type_id)) {
    category = SPVM_BASIC_TYPE_C_CATEGORY_NUMERIC;
  }
  else if (SPVM_BASIC_TYPE_is_mulnum_type(compiler, basic_type_id)) {
    category = SPVM_BASIC_TYPE_C_CATEGORY_MULNUM;
  }
  else if (SPVM_BASIC_TYPE_is_string_type(compiler, basic_type_id)) {
    category = SPVM_BASIC_TYPE_C_CATEGORY_STRING;
  }
  else if (SPVM_BASIC_TYPE_is_class_type(compiler, basic_type_id)) {
    category = SPVM_BASIC_TYPE_C_CATEGORY_CLASS;
  }
  else if (SPVM_BASIC_TYPE_is_interface_type(compiler, basic_type_id)) {
    category = SPVM_BASIC_TYPE_C_CATEGORY_INTERFACE;
  }
  else if (SPVM_BASIC_TYPE_is_callback_type(compiler, basic_type_id)) {
    category = SPVM_BASIC_TYPE_C_CATEGORY_CALLBACK;
  }
  else if (SPVM_BASIC_TYPE_is_any_object_type(compiler, basic_type_id)) {
    category = SPVM_BASIC_TYPE_C_CATEGORY_ANY_OBJECT;
  }
  else if (SPVM_BASIC_TYPE_is_undef_type(compiler, basic_type_id)) {
    category = SPVM_BASIC_TYPE_C_CATEGORY_UNDEF;
  }
  else if (SPVM_BASIC_TYPE_is_unknown_type(compiler, basic_type_id)) {
    category = SPVM_BASIC_TYPE_C_CATEGORY_UNKNOWN;
  }
  else if (SPVM_BASIC_TYPE_is_fail_load_type(compiler, basic_type_id)) {
    category = SPVM_BASIC_TYPE_C_CATEGORY_FAIL_LOAD;
  }
  else {
    assert(0);
  }
  
  return category;
}

int32_t SPVM_BASIC_TYPE_is_void_type(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  (void)compiler;
  
  if (basic_type_id == SPVM_BASIC_TYPE_C_ID_VOID) {
    return 1;
  }
  else {
    return 0;
  }
  
  return 1;
}

int32_t SPVM_BASIC_TYPE_is_numeric_type(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  (void)compiler;
  
  if (basic_type_id >= SPVM_BASIC_TYPE_C_ID_BYTE && basic_type_id <= SPVM_BASIC_TYPE_C_ID_DOUBLE) {
    return 1;
  }
  else {
    return 0;
  }
  
  return 1;
}


int32_t SPVM_BASIC_TYPE_is_mulnum_type(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
  
  int32_t is_mulnum_t;
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
  
  return is_mulnum_t;
}

int32_t SPVM_BASIC_TYPE_is_string_type(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  (void)compiler;
  
  return basic_type_id == SPVM_BASIC_TYPE_C_ID_STRING;
}

int32_t SPVM_BASIC_TYPE_is_class_type(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
  
  int32_t is_class_type;
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
  
  return is_class_type;
}

int32_t SPVM_BASIC_TYPE_is_interface_type(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
  
  int32_t is_interface_type;
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
  
  return is_interface_type;
}

int32_t SPVM_BASIC_TYPE_is_callback_type(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
  
  int32_t is_class_type;
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
  
  return is_class_type;
}

int32_t SPVM_BASIC_TYPE_is_any_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  (void)compiler;
  
  return basic_type_id == SPVM_BASIC_TYPE_C_ID_ANY_OBJECT;
}


int32_t SPVM_BASIC_TYPE_is_undef_type(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  (void)compiler;
  
  if (basic_type_id == SPVM_BASIC_TYPE_C_ID_UNDEF) {
    return 1;
  }
  else {
    return 0;
  }
}


int32_t SPVM_BASIC_TYPE_is_unknown_type(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  (void)compiler;
  
  if (basic_type_id == SPVM_BASIC_TYPE_C_ID_UNKNOWN) {
    return 1;
  }
  else {
    return 0;
  }
}


int32_t SPVM_BASIC_TYPE_is_fail_load_type(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
  
  int32_t is_fail_load_type;
  const char* basic_type_name = basic_type->name;
  SPVM_CLASS* class = SPVM_HASH_get(compiler->fail_load_class_symtable, basic_type_name, strlen(basic_type_name));
  // Class
  if (class) {
    is_fail_load_type = 1;
  }
  // Numeric type
  else {
    is_fail_load_type = 0;
  }

  return is_fail_load_type;
}
