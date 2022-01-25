#ifndef SPVM_COMPILER_H
#define SPVM_COMPILER_H

#include <stdio.h>

#include "spvm_typedecl.h"
#include "spvm_native.h"

enum {
  SPVM_TOKE_C_STATE_VAR_EXPANSION_DEFAULT,
  SPVM_TOKE_C_STATE_VAR_EXPANSION_FIRST_CONCAT,
  SPVM_TOKE_C_STATE_VAR_EXPANSION_VAR,
  SPVM_TOKE_C_STATE_VAR_EXPANSION_SECOND_CONCAT,
  SPVM_TOKE_C_STATE_VAR_EXPANSION_DOUBLE_QUOTE,
};

// Parser information
struct spvm_compiler {
  // Current parsed file name
  const char* cur_file;
  
  // Current parsed file relative name
  const char* cur_rel_file;

  // Current parsed class name
  const char* cur_rel_file_class_name;

  // Current parsed source
  char* cur_src;

  // Current parsed source
  int32_t cur_src_length;

  // Current line number
  int32_t cur_line;
  
  // Allocator
  SPVM_ALLOCATOR* allocator;

  // Line start position
  char* line_start_ptr;
  
  // Current buffer position
  char* bufptr;
  
  // Before buffer position
  char* befbufptr;

  // Expect method name
  int8_t expect_method_name;

  // Expect field name
  int8_t expect_field_name;
  
  // Before token is arrow
  int8_t before_token_is_arrow;

  // Expect variable expansion start
  int8_t state_var_expansion;
  
  // Current enum value
  int32_t current_enum_value;

  // Current class base;
  int32_t cur_class_base;
  
  // AST grammar
  SPVM_OP* op_grammar;
  
  // Syntax error count
  SPVM_LIST* error_messages;
  
  // Module searching directories
  SPVM_LIST* module_dirs;

  // Constant string symtable
  SPVM_HASH* const_string_symtable;

  // Class loading stack
  SPVM_LIST* op_use_stack;

  // Operation codes
  SPVM_OPCODE_ARRAY* opcode_array;
  
  // Constants
  SPVM_LIST* op_constants;

  // Types
  SPVM_LIST* op_types;

  // Classes
  SPVM_LIST* classes;

  // added_class_names tmp
  SPVM_LIST* added_class_names;

  // Used module symtable
  SPVM_HASH* used_class_symtable;
  
  // module file symtable
  SPVM_HASH* module_file_symtable;

  // module source symtable
  SPVM_HASH* module_source_symtable;
  
  // OP class symtable
  SPVM_HASH* class_symtable;
  
  // Single types
  SPVM_LIST* basic_types;
  
  // Resolved type symbol table
  SPVM_HASH* basic_type_symtable;

  // OP our symtable
  SPVM_LIST* class_vars;

  // Method ops
  SPVM_LIST* methods;
  
  // Method absolute name symbol table
  SPVM_HASH* method_symtable;

  // Field ops
  SPVM_LIST* fields;
  
  char* next_double_quote_start_bufptr;
};

SPVM_COMPILER* SPVM_COMPILER_new();
int32_t SPVM_COMPILER_compile(SPVM_COMPILER* compiler);
void SPVM_COMPILER_free(SPVM_COMPILER* compiler);
void SPVM_COMPILER_add_basic_types(SPVM_COMPILER* compiler);
SPVM_RUNTIME* SPVM_COMPILER_new_runtime(SPVM_COMPILER* compiler);
void SPVM_COMPILER_error(SPVM_COMPILER* compiler, const char* message, ...);

const char* SPVM_COMPILER_create_method_signature(SPVM_COMPILER* compiler, SPVM_METHOD* method);
const char* SPVM_COMPILER_create_field_signature(SPVM_COMPILER* compiler, SPVM_FIELD* field);
const char* SPVM_COMPILER_create_class_var_signature(SPVM_COMPILER* compiler, SPVM_CLASS_VAR* class_var);

int32_t SPVM_COMPILER_get_error_count(SPVM_COMPILER* compiler);

#endif
