#ifndef SPVM_COMPILER_H
#define SPVM_COMPILER_H

#include <stdio.h>

#include "spvm_base.h"

// Parser information
struct SPVM_compiler {
  // Current parsed file name
  const char* cur_file;

  // Current parsed source
  char* cur_src;

  // Current line number
  int32_t cur_line;
  
  // Allocator
  SPVM_COMPILER_ALLOCATOR* allocator;
  
  // Current buffer position
  char* bufptr;
  
  // Before buffer position
  char* befbufptr;

  // Expect subroutine name
  _Bool expect_sub_name;
  
  // Current enum value
  int32_t current_enum_value;
  
  // Temporary variable length
  int32_t tmp_var_length;
  
  // Current case statements in switch statement
  SPVM_LIST* cur_op_cases;

  // Include pathes
  SPVM_LIST* module_include_pathes;

  // OP name symtable
  SPVM_HASH* name_symtable;

  // Class loading stack
  SPVM_LIST* op_use_stack;
  
  // Constants
  SPVM_LIST* op_constants;

  // Packages
  SPVM_LIST* op_packages;
  
  // OP package symtable
  SPVM_HASH* op_package_symtable;
  
  // JIT package symtable
  SPVM_HASH* jit_package_name_symtable;

  // JIT package names
  SPVM_LIST* jit_package_names;
  
  // Anonimous package length
  int32_t anon_package_length;
  
  // Single types
  SPVM_LIST* basic_types;
  
  // Resolved type symbol table
  SPVM_HASH* basic_type_symtable;
  
  // Types
  SPVM_LIST* op_types;

  // OP our symtable
  SPVM_HASH* op_our_symtable;

  // Package Variable length
  int32_t package_var_length;
  
  // Subroutine ops
  SPVM_LIST* op_subs;
  
  // Subroutine absolute name symbol table
  SPVM_HASH* op_sub_symtable;

  // Method signature
  SPVM_LIST* method_signatures;

  // Method signature symbol table
  SPVM_HASH* method_signature_symtable;
  
  // AST grammar
  SPVM_OP* op_grammar;
  
  // Entry point subroutine name
  const char* start_sub_name;
  
  // Syntax error count
  int32_t error_count;
  
  // Error is fatal
  _Bool fatal_error;
  
  // Temporary buffer
  char tmp_buffer[UINT16_MAX];
  
  // Operation codes
  SPVM_OPCODE_ARRAY* opcode_array;
};

SPVM_COMPILER* SPVM_COMPILER_new();
int32_t SPVM_COMPILER_compile(SPVM_COMPILER* compiler);
SPVM_RUNTIME* SPVM_COMPILER_new_runtime(SPVM_COMPILER* compiler);
void SPVM_COMPILER_free(SPVM_COMPILER* compiler);
void SPVM_COMPILER_add_basic_types(SPVM_COMPILER* compiler);

#endif
