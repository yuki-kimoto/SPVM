#ifndef SPVM_RUNTIME_H
#define SPVM_RUNTIME_H

#include "spvm_typedecl.h"

SPVM_RUNTIME* SPVM_RUNTIME_new();

void SPVM_RUNTIME_free(SPVM_RUNTIME* runtime);

struct spvm_runtime {
  // SPVM 32bit codes
  int32_t spvm_32bit_codes;
  
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

  // The length of anon method ids
  int32_t anon_method_methods_length;

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
  
  // Method cache symbol table
  SPVM_HASH* method_cache_symtable;
  
  // Field cache symbol table
  SPVM_HASH* field_cache_symtable;

  // Class variable cache symbol table
  SPVM_HASH* class_var_cache_symtable;
};

void SPVM_RUNTIME_prepare(SPVM_RUNTIME* runtime);

#endif
