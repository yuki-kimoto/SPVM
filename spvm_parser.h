#ifndef SPVM_PARSER_H
#define SPVM_PARSER_H

#include <stdio.h>

#include "spvm_base.h"

// Parser information
struct SPVM_parser {
  // Constant pool
  SPVM_CONSTANT_POOL* constant_pool;
  
  // Bytecodes
  SPVM_BYTECODE_ARRAY* bytecode_array;
  
  // Entry point subroutine name
  const char* entry_point_sub_name;

  // Allocator
  SPVM_PARSER_ALLOCATOR* allocator;
  
  // Before buffer position
  const char* befbufptr;
  
  // Current buffer position
  const char* bufptr;
  
  // Current file name
  const char* cur_module_path;
  
  // Source data
  const char* cur_src;
  
  // AST grammar
  SPVM_OP* op_grammar;
  
  // Packages
  SPVM_ARRAY* op_packages;
  
  // OP package symtable
  SPVM_HASH* op_package_symtable;
  
  // Class loading stack
  SPVM_ARRAY* op_use_stack;
  
  // Include pathes
  SPVM_ARRAY* include_pathes;
  
  // Method absolute name symbol table
  SPVM_HASH* op_sub_symtable;
  
  // Field absolute name symbol table
  SPVM_HASH* op_field_symtable;
  
  // use symbol table
  SPVM_HASH* op_use_symtable;
  
  // Types
  SPVM_ARRAY* op_types;
  
  // Resovled types
  SPVM_ARRAY* resolved_types;
  
  // Resolved type symbol table
  SPVM_HASH* resolved_type_symtable;
  
  // Current case statements in switch statement
  SPVM_ARRAY* cur_op_cases;
  
  // Entry point subroutine name
  const char* start_sub_name;
  
  // Current line number
  int32_t cur_line;
  
  // Syntax error count
  int32_t error_count;
  
  // Current package count
  int32_t current_package_count;
  
  // Error is fatal
  _Bool fatal_error;
};

SPVM_PARSER* SPVM_PARSER_new(SPVM_* spvm);
int32_t SPVM_PARSER_parse(SPVM_* spvm, const char* package_name);

void SPVM_PARSER_free(SPVM_* spvm, SPVM_PARSER* parser);

#endif
