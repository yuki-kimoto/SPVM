#ifndef SPVM_COMPILER_H
#define SPVM_COMPILER_H

#include <stdio.h>

#include "spvm_base.h"
#include "spvm_native.h"

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
  int32_t expect_sub_name;
  
  // Current enum value
  int32_t current_enum_value;
  
  // Temporary variable length
  int32_t tmp_var_length;
  
  // AST grammar
  SPVM_OP* op_grammar;
  
  // Syntax error count
  int32_t error_count;
  
  // Current case statements in switch statement
  SPVM_LIST* cur_op_cases;

  // Include pathes
  SPVM_LIST* module_include_pathes;

  // OP name symtable
  SPVM_HASH* name_symtable;

  // Class loading stack
  SPVM_LIST* op_use_stack;

  // Anonimous package length
  int32_t anon_package_length;

  // Operation codes
  SPVM_OPCODE_ARRAY* opcode_array;
  
  // Constants
  SPVM_LIST* op_constants;

  // Types
  SPVM_LIST* op_types;

  // Packages
  SPVM_LIST* packages;
  
  // OP package symtable
  SPVM_HASH* package_symtable;
  
  // Single types
  SPVM_LIST* basic_types;
  
  // Resolved type symbol table
  SPVM_HASH* basic_type_symtable;

  // OP our symtable
  SPVM_LIST* package_vars;

  // OP our symtable
  SPVM_HASH* package_var_symtable;

  // Subroutine ops
  SPVM_LIST* subs;
  
  // Subroutine absolute name symbol table
  SPVM_HASH* sub_symtable;

  // Field ops
  SPVM_LIST* fields;
  
  // Field absolute name symbol table
  SPVM_HASH* field_symtable;

  // Method signature
  SPVM_LIST* signatures;

  // Method signature symbol table
  SPVM_HASH* signature_symtable;
  
  char buffer1[UINT16_MAX * 2];
  char buffer2[UINT16_MAX * 2]
};

SPVM_COMPILER* SPVM_COMPILER_new();
void SPVM_COMPILER_compile(SPVM_COMPILER* compiler);
void SPVM_COMPILER_free(SPVM_COMPILER* compiler);
void SPVM_COMPILER_add_basic_types(SPVM_COMPILER* compiler);
SPVM_RUNTIME* SPVM_COMPILER_new_runtime(SPVM_COMPILER* compiler);
void SPVM_COMPILER_push_long_pool(SPVM_COMPILER* compiler, int64_t long_value);
void SPVM_COMPILER_push_string_pool(SPVM_COMPILER* compiler, const char* string, int32_t string_length);

#endif
