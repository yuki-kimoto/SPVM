#ifndef SPVM_RUNTIME_INFO_H
#define SPVM_RUNTIME_INFO_H

#include "spvm_typedecl.h"

struct spvm_runtime_info {
  // Strings - string literals and symbol names
  SPVM_LIST* runtime_strings;
  
  // String symtable
  SPVM_HASH* runtime_string_symtable;

  // Runtime Basic types
  SPVM_LIST* runtime_basic_types;
  
  // Runtime Basic type symbol table
  SPVM_HASH* runtime_basic_type_symtable;

  // Runtime Basic types
  SPVM_LIST* runtime_types;
  
  // Runtime Basic type symbol table
  SPVM_HASH* runtime_type_symtable;

  // Runtime class types
  SPVM_LIST* runtime_classes;
  
  // Runtime class symbol table
  SPVM_HASH* runtime_class_symtable;

  // Runtime methods
  SPVM_LIST* runtime_methods;

  // Runtime class variables
  SPVM_LIST* runtime_class_vars;

  // Runtime fields
  SPVM_LIST* runtime_fields;
  
  // Runtime methods of a class
  SPVM_RUNTIME_METHODS_OF_CLASS* runtime_methods_of_class;

  // Runtime fields of a class
  SPVM_RUNTIME_FIELDS_OF_CLASS* runtime_fields_of_class;

  // Runtime class variables of a class
  SPVM_RUNTIME_CLASS_VARS_OF_CLASS* runtime_class_vars_of_class;
};

#endif
