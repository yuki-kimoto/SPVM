// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "spvm_compiler.h"
#include "spvm_basic_type.h"
#include "spvm_allocator.h"
#include "spvm_class.h"
#include "spvm_list.h"
#include "spvm_hash.h"
#include "spvm_method.h"

const char* const* SPVM_NATIVE_C_BASIC_TYPE_ID_NAMES(void) {

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
    "Error",
    "CommandInfo",
    "Address",
  };
  
  return id_names;
}

const char* const* SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NAMES(void) {

  static const char* const id_names[] = {
    "unknown"
    "not_found_class",
    "undef"
    "void"
    "numeric"
    "mulnum"
    "string",
    "class",
    "interface",
    "any_obejct",
  };
  
  return id_names;
}

SPVM_BASIC_TYPE* SPVM_BASIC_TYPE_new(SPVM_COMPILER* compiler) {
  SPVM_BASIC_TYPE* basic_type = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, sizeof(SPVM_BASIC_TYPE));
  
  return basic_type;
}

const char* SPVM_BASIC_TYPE_get_basic_type_name(int32_t basic_type_id) {
  return (SPVM_NATIVE_C_BASIC_TYPE_ID_NAMES())[basic_type_id];
}

int32_t SPVM_TYPE_get_category(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_BASIC_TYPE_get_category(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  
  int32_t category;
  if (SPVM_BASIC_TYPE_is_void_type(compiler, basic_type_id)) {
    category = SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_VOID;
  }
  else if (SPVM_BASIC_TYPE_is_numeric_type(compiler, basic_type_id)) {
    category = SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC;
  }
  else if (SPVM_BASIC_TYPE_is_mulnum_type(compiler, basic_type_id)) {
    category = SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM;
  }
  else if (SPVM_BASIC_TYPE_is_string_type(compiler, basic_type_id)) {
    category = SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_STRING;
  }
  else if (SPVM_BASIC_TYPE_is_class_type(compiler, basic_type_id)) {
    category = SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS;
  }
  else if (SPVM_BASIC_TYPE_is_interface_type(compiler, basic_type_id)) {
    category = SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE;
  }
  else if (SPVM_BASIC_TYPE_is_any_object_type(compiler, basic_type_id)) {
    category = SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT;
  }
  else if (SPVM_BASIC_TYPE_is_undef_type(compiler, basic_type_id)) {
    category = SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_UNDEF;
  }
  else if (SPVM_BASIC_TYPE_is_unknown_type(compiler, basic_type_id)) {
    category = SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_UNKNOWN;
  }
  else if (SPVM_BASIC_TYPE_is_not_found_class_type(compiler, basic_type_id)) {
    category = SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NOT_FOUND_CLASS;
  }
  else {
    assert(0);
  }
  
  return category;
}

int32_t SPVM_BASIC_TYPE_is_void_type(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  (void)compiler;
  
  if (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_VOID) {
    return 1;
  }
  else {
    return 0;
  }
  
  return 1;
}

int32_t SPVM_BASIC_TYPE_is_numeric_type(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  (void)compiler;
  
  if (basic_type_id >= SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE && basic_type_id <= SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
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
  
  return basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_STRING;
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

int32_t SPVM_BASIC_TYPE_is_any_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  (void)compiler;
  
  return basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_ANY_OBJECT;
}


int32_t SPVM_BASIC_TYPE_is_undef_type(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  (void)compiler;
  
  if (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_UNDEF) {
    return 1;
  }
  else {
    return 0;
  }
}


int32_t SPVM_BASIC_TYPE_is_unknown_type(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  (void)compiler;
  
  if (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_UNKNOWN) {
    return 1;
  }
  else {
    return 0;
  }
}


int32_t SPVM_BASIC_TYPE_is_not_found_class_type(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
  
  int32_t is_not_found_class_type;
  const char* basic_type_name = basic_type->name;
  SPVM_CLASS* class = SPVM_HASH_get(compiler->not_found_class_class_symtable, basic_type_name, strlen(basic_type_name));
  // Class
  if (class) {
    is_not_found_class_type = 1;
  }
  // Numeric type
  else {
    is_not_found_class_type = 0;
  }

  return is_not_found_class_type;
}

int32_t SPVM_BASIC_TYPE_is_numeric_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  (void)compiler;
  
  if (basic_type_id >= SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE_CLASS && basic_type_id <= SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE_CLASS) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_BASIC_TYPE_is_integer_type(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  (void)compiler;
  
  if (basic_type_id >= SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE && basic_type_id <= SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_BASIC_TYPE_is_integer_type_within_int(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  (void)compiler;
  
  if (basic_type_id >= SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE && basic_type_id <= SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_BASIC_TYPE_has_interface(SPVM_COMPILER* compiler, int32_t class_basic_type_id, int32_t interface_basic_type_id) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* class_basic_type = SPVM_LIST_get(compiler->basic_types, class_basic_type_id);
  SPVM_CLASS* class = class_basic_type->class;

  SPVM_BASIC_TYPE* interface_basic_type = SPVM_LIST_get(compiler->basic_types, interface_basic_type_id);
  SPVM_CLASS* interface = interface_basic_type->class;

  assert(interface->required_method);
  SPVM_METHOD* method_interface = interface->required_method;

  SPVM_CLASS* parent_class = class;
  while (1) {
    if (!parent_class) {
      return 0;
    }
    
    SPVM_METHOD* method_class = SPVM_HASH_get(parent_class->method_symtable, method_interface->name, strlen(method_interface->name));
    if (method_class) {
      return 1;
    }
    
    const char* parent_class_name = parent_class->parent_class_name;
    if (parent_class_name) {
      parent_class = SPVM_HASH_get(compiler->class_symtable, parent_class_name, strlen(parent_class_name));
      assert(parent_class);
    }
    else {
      parent_class = NULL;
    }
  }
}

int32_t SPVM_BASIC_TYPE_is_super_class(SPVM_COMPILER* compiler, int32_t super_basic_type_id, int32_t child_basic_type_id) {
  
  SPVM_BASIC_TYPE* super_basic_type = SPVM_LIST_get(compiler->basic_types, super_basic_type_id);
  SPVM_BASIC_TYPE* child_basic_type = SPVM_LIST_get(compiler->basic_types, child_basic_type_id);
  
  SPVM_CLASS* super_class = super_basic_type->class;
  SPVM_CLASS* child_class = child_basic_type->class;
  
  const char* cur_parent_class_name = child_class->parent_class_name;
  while (1) {
    if (cur_parent_class_name) {
      if (strcmp(super_class->name, cur_parent_class_name) == 0) {
        return 1;
      }
      else {
        SPVM_CLASS* cur_parent_class = SPVM_HASH_get(compiler->class_symtable, cur_parent_class_name, strlen(cur_parent_class_name));
        assert(cur_parent_class);
        cur_parent_class_name = cur_parent_class->parent_class_name;
      }
    }
    else {
      return 0;
    }
  }
}
