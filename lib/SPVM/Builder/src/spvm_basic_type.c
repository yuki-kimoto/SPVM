// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "spvm_compiler.h"
#include "spvm_basic_type.h"
#include "spvm_allocator.h"
#include "spvm_list.h"
#include "spvm_hash.h"
#include "spvm_method.h"
#include "spvm_string_buffer.h"
#include "spvm_string.h"
#include "spvm_op.h"
#include "spvm_type.h"
#include "spvm_var_decl.h"

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
    "Error",
    "Error::System",
    "Error::NotSupported",
    "CommandInfo",
    "Address",
  };
  
  return id_names;
}

const char* const* SPVM_BASIC_TYPE_C_CATEGORY_NAMES(void) {

  static const char* const id_names[] = {
    "unknown"
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
  SPVM_BASIC_TYPE* basic_type = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->current_each_compile_allocator, sizeof(SPVM_BASIC_TYPE));
  
  basic_type->constant_strings = SPVM_LIST_new_list_permanent(compiler->current_each_compile_allocator, 128);
  basic_type->constant_string_symtable = SPVM_HASH_new_hash_permanent(compiler->current_each_compile_allocator, 128);
  basic_type->string_pool = SPVM_STRING_BUFFER_new(compiler->current_each_compile_allocator, 8192, SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT);
  
  // Fields
  basic_type->unmerged_fields = SPVM_LIST_new_list_permanent(compiler->current_each_compile_allocator, 0);
  basic_type->unmerged_field_symtable = SPVM_HASH_new_hash_permanent(compiler->current_each_compile_allocator, 0);
  
  basic_type->field_symtable = SPVM_HASH_new_hash_permanent(compiler->current_each_compile_allocator, 0);
  
  // Class variables
  basic_type->class_vars = SPVM_LIST_new_list_permanent(compiler->current_each_compile_allocator, 0);
  basic_type->class_var_symtable = SPVM_HASH_new_hash_permanent(compiler->current_each_compile_allocator, 0);
  
  // Methods
  basic_type->methods = SPVM_LIST_new_list_permanent(compiler->current_each_compile_allocator, 0);
  basic_type->method_symtable = SPVM_HASH_new_hash_permanent(compiler->current_each_compile_allocator, 0);
  
  // Interfaces
  basic_type->interface_basic_types = SPVM_LIST_new_list_permanent(compiler->current_each_compile_allocator, 0);
  basic_type->interface_basic_symtable = SPVM_HASH_new_hash_permanent(compiler->current_each_compile_allocator, 0);
  
  basic_type->allows = SPVM_LIST_new_list_permanent(compiler->current_each_compile_allocator, 0);
  basic_type->interface_decls = SPVM_LIST_new_list_permanent(compiler->current_each_compile_allocator, 0);
  basic_type->anon_unresolved_basic_type_names = SPVM_LIST_new_list_permanent(compiler->current_each_compile_allocator, 0);
  basic_type->anon_basic_types = SPVM_LIST_new_list_permanent(compiler->current_each_compile_allocator, 0);
  basic_type->alias_symtable = SPVM_HASH_new_hash_permanent(compiler->current_each_compile_allocator, 0);
  
  basic_type->use_basic_type_names = SPVM_LIST_new_list_permanent(compiler->current_each_compile_allocator, 0);
  
  return basic_type;
}

const char* SPVM_BASIC_TYPE_get_basic_type_name(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  return (SPVM_BASIC_TYPE_C_ID_NAMES())[basic_type_id];
}

int32_t SPVM_BASIC_TYPE_is_void_type(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  
  if (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_VOID) {
    return 1;
  }
  else {
    return 0;
  }
  
  return 1;
}

int32_t SPVM_BASIC_TYPE_is_numeric_type(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  
  if (basic_type_id >= SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE && basic_type_id <= SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
    return 1;
  }
  else {
    return 0;
  }
  
  return 1;
}


int32_t SPVM_BASIC_TYPE_is_mulnum_type(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
  
  int32_t is_mulnum_type = (basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM);
  
  return is_mulnum_type;
}

int32_t SPVM_BASIC_TYPE_is_string_type(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  
  return basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_STRING;
}

int32_t SPVM_BASIC_TYPE_is_class_type(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
  
  int32_t is_class_type = (basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS);
  
  return is_class_type;
}

int32_t SPVM_BASIC_TYPE_is_interface_type(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
  
  int32_t is_interface_type = (basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE);
  
  return is_interface_type;
}

int32_t SPVM_BASIC_TYPE_is_any_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  
  return basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_ANY_OBJECT;
}


int32_t SPVM_BASIC_TYPE_is_undef_type(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  
  if (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_UNDEF) {
    return 1;
  }
  else {
    return 0;
  }
}


int32_t SPVM_BASIC_TYPE_is_unknown_type(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  
  if (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_UNKNOWN) {
    return 1;
  }
  else {
    return 0;
  }
}


int32_t SPVM_BASIC_TYPE_is_numeric_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  
  if (basic_type_id >= SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE_CLASS && basic_type_id <= SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE_CLASS) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_BASIC_TYPE_is_integer_type(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  
  if (basic_type_id >= SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE && basic_type_id <= SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_BASIC_TYPE_is_integer_type_within_int(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  
  if (basic_type_id >= SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE && basic_type_id <= SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_BASIC_TYPE_has_interface(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t interface_basic_type_id) {
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
  
  SPVM_BASIC_TYPE* interface_basic_type = SPVM_LIST_get(compiler->basic_types, interface_basic_type_id);
  
  if (!(interface_basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE)) {
    return 0;
  }
  
  if (!(basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS || basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE)) {
    return 0;
  }
  
  for (int32_t interface_method_index = 0; interface_method_index < interface_basic_type->methods->length; interface_method_index++) {
    SPVM_METHOD* interface_method = SPVM_LIST_get(interface_basic_type->methods, interface_method_index);
    
    for (int32_t method_index = 0; method_index < basic_type->methods->length; method_index++) {
      SPVM_METHOD* method = SPVM_HASH_get(basic_type->method_symtable, interface_method->name, strlen(interface_method->name));
      
      int32_t can_override = SPVM_METHOD_satisfy_interface_method_requirement(compiler, interface_basic_type, interface_method, basic_type, method, "interface");
      
      if (can_override == 0) {
        return 0;
      }
    }
  }
  
  return 1;
}

int32_t SPVM_BASIC_TYPE_is_super_class(SPVM_COMPILER* compiler, int32_t super_basic_type_id, int32_t child_basic_type_id) {
  
  SPVM_BASIC_TYPE* super_basic_type = SPVM_LIST_get(compiler->basic_types, super_basic_type_id);
  SPVM_BASIC_TYPE* child_basic_type = SPVM_LIST_get(compiler->basic_types, child_basic_type_id);
  
  const char* current_parent_basic_type_name = child_basic_type->parent_name;
  while (1) {
    if (current_parent_basic_type_name) {
      if (strcmp(super_basic_type->name, current_parent_basic_type_name) == 0) {
        return 1;
      }
      else {
        SPVM_BASIC_TYPE* current_parent_basic_type = SPVM_HASH_get(compiler->basic_type_symtable, current_parent_basic_type_name, strlen(current_parent_basic_type_name));
        assert(current_parent_basic_type);
        current_parent_basic_type_name = current_parent_basic_type->parent_name;
      }
    }
    else {
      return 0;
    }
  }
}

SPVM_STRING* SPVM_BASIC_TYPE_add_constant_string(SPVM_COMPILER* compiler, SPVM_BASIC_TYPE* basic_type, const char* value, int32_t length) {
  
  SPVM_STRING* found_string = SPVM_HASH_get(basic_type->constant_string_symtable, value, length);
  if (found_string) {
    return found_string;
  }
  else {
    int32_t string_pool_index = basic_type->string_pool->length;
    
    SPVM_STRING_BUFFER_add_len_nullstr(basic_type->string_pool, (char*)value, length);
    
    SPVM_STRING* string = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->current_each_compile_allocator, sizeof(SPVM_STRING));
    string->value = value;
    string->length = length;
    string->index = basic_type->constant_strings->length;
    string->string_pool_index = string_pool_index;
    
    SPVM_LIST_push(basic_type->constant_strings, string);
    SPVM_HASH_set(basic_type->constant_string_symtable, string->value, length, string);
    
    return string;
  }
}
