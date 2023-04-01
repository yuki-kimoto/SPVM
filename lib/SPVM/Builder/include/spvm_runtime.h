// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_RUNTIME_H
#define SPVM_RUNTIME_H

#include "spvm_typedecl.h"

struct spvm_runtime {
  // SPVM 32bit codes
  int32_t* runtime_codes;

  // SPVM 32bit codes
  int32_t runtime_codes_length;
  
  // Allocator
  SPVM_ALLOCATOR* allocator;
  
  // Operation codes
  SPVM_OPCODE* opcodes;

  // The length of operation codes
  int32_t opcodes_length;

  // String buffer
  const char* constant_strings_buffer;

  // String buffer length
  int32_t constant_strings_buffer_length;

  // Strings
  SPVM_RUNTIME_CONSTANT_STRING* constant_strings;

  // The length of strings
  int32_t constant_strings_length;
  
  // Basic types
  SPVM_RUNTIME_BASIC_TYPE* basic_types;
  
  // The length of basic types
  int32_t basic_types_length;
  
  // Types
  SPVM_RUNTIME_TYPE* types;

  // The length of types
  int32_t types_length;
  
  // Classes
  SPVM_RUNTIME_CLASS* classes;
  
  // The length of classes
  int32_t classes_length;
  
  // Methods
  SPVM_RUNTIME_METHOD* methods;

  // Native method addresses
  void** method_native_addresses;

  // Precompile method addresses
  void** method_precompile_addresses;

  // The length of methods
  int32_t methods_length;

  // Method argument type ids
  int32_t* arg_type_ids;

  // The length of methods
  int32_t arg_types_length;

  // Anon nethod ids
  int32_t* anon_method_method_ids;

  // The length of anon methods
  int32_t anon_methods_length;

  // Class variables
  SPVM_RUNTIME_CLASS_VAR* class_vars;

  // The length of class variables
  int32_t class_vars_length;

  // Fields
  SPVM_RUNTIME_FIELD* fields;
  
  // The length of the fields
  int32_t fields_length;
  
  // String symtable
  SPVM_HASH* constant_string_symtable;

  // Runtime Basic type symbol table
  SPVM_HASH* basic_type_symtable;

  // Runtime class symbol table
  SPVM_HASH* class_symtable;
};

SPVM_RUNTIME* SPVM_RUNTIME_new();

void SPVM_RUNTIME_free(SPVM_RUNTIME* runtime);

void SPVM_RUNTIME_build_symbol_table(SPVM_RUNTIME* runtime);

SPVM_ALLOCATOR* SPVM_RUNTIME_get_allocator(SPVM_RUNTIME* runtime);

void SPVM_RUNTIME_build(SPVM_RUNTIME* runtime, int32_t* runtime_codes);

#endif
