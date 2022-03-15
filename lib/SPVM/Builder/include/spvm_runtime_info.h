#ifndef SPVM_RUNTIME_INFO_H
#define SPVM_RUNTIME_INFO_H

#include "spvm_typedecl.h"

struct spvm_runtime_info {
  // Allocator
  SPVM_ALLOCATOR* allocator;

  // Operation codes
  SPVM_OPCODE* opcodes;

  // String buffer
  const char* string_buffer;

  // String buffer length
  int32_t string_buffer_length;

  // Strings
  SPVM_RUNTIME_STRING* strings;

  // The length of strings
  int32_t strings_length;
  
  // Basic types
  SPVM_RUNTIME_BASIC_TYPE* basic_types;
  
  // The length of basic types
  int32_t basic_types_length;
  
  // Types
  SPVM_RUNTIME_TYPE* types;

  // The length of types
  int32_t types_length;
  
  // Runtime class types
  SPVM_LIST* classes;
  
  // Runtime methods
  SPVM_LIST* methods;

  // Class variables
  SPVM_RUNTIME_CLASS_VAR* class_vars;

  // The length of class variables
  int32_t class_vars_length;

  // Runtime fields
  SPVM_LIST* fields;
  
  // Runtime methods of a class
  SPVM_RUNTIME_METHODS_OF_CLASS* methods_of_class;

  // Runtime fields of a class
  SPVM_RUNTIME_FIELDS_OF_CLASS* fields_of_class;

  // Runtime class variables of a class
  SPVM_RUNTIME_CLASS_VARS_OF_CLASS* class_vars_of_class;
  
  // String symtable
  SPVM_HASH* string_symtable;

  // Runtime Basic type symbol table
  SPVM_HASH* basic_type_symtable;

  // Runtime class symbol table
  SPVM_HASH* class_symtable;

};

#endif
