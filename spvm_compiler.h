#ifndef SPVM_COMPILER_H
#define SPVM_COMPILER_H

#include <stdio.h>

#include "spvm_base.h"

// Parser information
struct SPVM_compiler {
  // Constant pool
  SPVM_CONSTANT_POOL* constant_pool;
  
  // Bytecodes
  SPVM_BYTECODE_ARRAY* bytecode_array;

  // Entry point package name
  const char* entry_point_package_name;
  
  // Entry point subroutine name
  const char* entry_point_sub_name;

  // Allocator
  SPVM_COMPILER_ALLOCATOR* allocator;
  
  // Before buffer position
  char* befbufptr;
  
  // Current buffer position
  char* bufptr;
  
  // Current file name
  const char* cur_file;
  
  // Source base_object
  char* cur_src;
  
  // AST grammar
  SPVM_OP* op_grammar;
  
  // Constants
  SPVM_DYNAMIC_ARRAY* op_constants;
  
  int64_t enum_default_value;
  int32_t enum_default_type_id;

  // Packages
  SPVM_DYNAMIC_ARRAY* op_packages;
  
  // OP package symtable
  SPVM_HASH* op_package_symtable;
  
  // Class loading stack
  SPVM_DYNAMIC_ARRAY* op_use_stack;
  
  // Include pathes
  SPVM_DYNAMIC_ARRAY* include_pathes;
  
  // Method absolute name symbol table
  SPVM_HASH* op_sub_symtable;
  
  // Field absolute name symbol table
  SPVM_HASH* op_field_symtable;
  
  // use symbol table
  SPVM_HASH* op_use_symtable;
  
  // Types
  SPVM_DYNAMIC_ARRAY* op_types;
  
  // Resovled types
  SPVM_DYNAMIC_ARRAY* types;
  
  // Resolved type symbol table
  SPVM_HASH* type_symtable;
  
  // Current case statements in switch statement
  SPVM_DYNAMIC_ARRAY* cur_op_cases;
  
  // Entry point subroutine name
  const char* start_sub_name;
  
  SPVM_DYNAMIC_ARRAY* cur_template_args;
  
  // Current line number
  int32_t cur_line;
  
  // Syntax error count
  int32_t error_count;
  
  // Current package count
  int32_t current_package_count;
  
  // Package indexes constant pool index
  int32_t package_indexes_constant_pool_index;

  // Type indexes constant pool index
  int32_t type_indexes_constant_pool_index;
  
  // Subroutine indexes constant pool index
  int32_t sub_indexes_constant_pool_index;
  
  // Subroutine length
  int32_t subs_length;
  
  // Native subroutines
  SPVM_DYNAMIC_ARRAY* native_subs;
  
  // Error is fatal
  _Bool fatal_error;
  
  _Bool debug;
};

SPVM_COMPILER* SPVM_COMPILER_new();
int32_t SPVM_COMPILER_compile(SPVM_COMPILER* compiler);
SPVM_RUNTIME* SPVM_COMPILER_new_runtime(SPVM_COMPILER* compiler);
void SPVM_COMPILER_free(SPVM_COMPILER* compiler);

#endif
