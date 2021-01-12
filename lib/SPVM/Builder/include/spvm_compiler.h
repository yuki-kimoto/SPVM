#ifndef SPVM_COMPILER_H
#define SPVM_COMPILER_H

#include <stdio.h>

#include "spvm_base.h"
#include "spvm_native.h"

enum {
  SPVM_TOKE_C_STATE_VAR_EXPANSION_DEFAULT,
  SPVM_TOKE_C_STATE_VAR_EXPANSION_FIRST_CONCAT,
  SPVM_TOKE_C_STATE_VAR_EXPANSION_VAR,
  SPVM_TOKE_C_STATE_VAR_EXPANSION_SECOND_CONCAT,
  SPVM_TOKE_C_STATE_VAR_EXPANSION_DOUBLE_QUOTE,
};

// Parser information
struct SPVM_compiler {
  // Current parsed file name
  const char* cur_file;
  
  // Current parsed file relative name
  const char* cur_rel_file;

  // Current parsed package name
  const char* cur_rel_file_package_name;

  // Current parsed source
  char* cur_src;

  // Current line number
  int32_t cur_line;
  
  // Allocator
  SPVM_COMPILER_ALLOCATOR* allocator;

  // Line start position
  char* line_start_ptr;
  
  // Current buffer position
  char* bufptr;
  
  // Before buffer position
  char* befbufptr;

  // Expect subroutine name
  int8_t expect_sub_name;

  // Expect field name
  int8_t expect_field_name;
  
  // Before token is arrow
  int8_t before_token_is_arrow;

  // Expect variable expansion start
  int8_t state_var_expansion;
  
  // Current enum value
  int32_t current_enum_value;

  // Current package base;
  int32_t cur_package_base;
  
  // AST grammar
  SPVM_OP* op_grammar;
  
  // Syntax error count
  int32_t error_count;
  
  // Include pathes
  SPVM_LIST* module_include_pathes;

  // OP name symtable
  SPVM_HASH* name_symtable;

  // Class loading stack
  SPVM_LIST* op_use_stack;

  // Operation codes
  SPVM_OPCODE_ARRAY* opcode_array;
  
  // Constants
  SPVM_LIST* op_constants;

  // Types
  SPVM_LIST* op_types;

  // Packages
  SPVM_LIST* packages;

  // added_package_names tmp
  SPVM_LIST* tmp_added_package_names;
  
  // added_packages
  SPVM_LIST* added_packages;

  // module file symtable
  SPVM_HASH* module_file_symtable;

  // module relative file symtable
  SPVM_HASH* module_rel_file_symtable;

  // module source symtable
  SPVM_HASH* module_source_symtable;
  
  // OP package symtable
  SPVM_HASH* package_symtable;
  
  // Single types
  SPVM_LIST* basic_types;
  
  // Resolved type symbol table
  SPVM_HASH* basic_type_symtable;

  // OP our symtable
  SPVM_LIST* package_vars;

  // Subroutine ops
  SPVM_LIST* subs;
  
  // Subroutine absolute name symbol table
  SPVM_HASH* sub_symtable;

  // Field ops
  SPVM_LIST* fields;
  
  // Search source code in module source symbol table instead of module directories
  int32_t is_search_module_source_symtable;
  
  char* next_double_quote_start_bufptr;

  SPVM_SOURCE* cur_source;
};

SPVM_COMPILER* SPVM_COMPILER_new();
void SPVM_COMPILER_compile(SPVM_COMPILER* compiler);
void SPVM_COMPILER_free(SPVM_COMPILER* compiler);
void SPVM_COMPILER_add_basic_types(SPVM_COMPILER* compiler);
SPVM_RUNTIME* SPVM_COMPILER_new_runtime(SPVM_COMPILER* compiler);
void SPVM_COMPILER_error(SPVM_COMPILER* compiler, const char* message, ...);

const char* SPVM_COMPILER_create_sub_signature(SPVM_COMPILER* compiler, SPVM_SUB* sub);
const char* SPVM_COMPILER_create_field_signature(SPVM_COMPILER* compiler, SPVM_FIELD* field);
const char* SPVM_COMPILER_create_package_var_signature(SPVM_COMPILER* compiler, SPVM_PACKAGE_VAR* package_var);

#endif
