// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_COMPILER_H
#define SPVM_COMPILER_H

#include <stdio.h>

#include "spvm_typedecl.h"
#include "spvm_native.h"

// Parser information
struct spvm_compiler {
  // OPs
  SPVM_LIST* ops;
  
  // Class paths
  SPVM_LIST* include_dirs;
  
  // Class loading stack
  SPVM_LIST* op_use_stack;
  
  // Types
  SPVM_LIST* op_types;
  
  // Directory of curreparsed file
  const char* cur_include_dir;
  
  // Current parsed file name
  const char* cur_file;
  
  // Current parsed file relative name
  const char* cur_rel_file;
  
  // Current parsed basic type name
  const char* cur_rel_file_basic_type_name;
  
  // Current parsed source
  char* cur_source;
  
  // Current parsed source
  int32_t cur_source_length;
  
  // Current line number
  int32_t cur_line;
  
  // Current temporary variables length
  int32_t cur_tmp_vars_length;
  
  // Allocator
  SPVM_ALLOCATOR* allocator;
  
  // Line start position
  char* line_begin_ptr;
  
  // Char pointer of current source
  char* ch_ptr;
  
  // Char pointer of current source just before
  char* before_ch_ptr;
  
  // Next double quote start position
  char* next_string_literal_ch_ptr;
  
  // Expect method name
  int8_t expect_method_name;
  
  // Expect field name
  int8_t expect_field_name;
  
  // Before token is arrow
  int8_t before_token_is_arrow;
  
  // Parsing is not started
  int8_t parse_not_started;
  
  // State of variable expansion
  int8_t var_expansion_state;
  
  // Current enum value
  int32_t current_enum_value;
  
  // Current basic type base;
  int32_t cur_basic_type_base;
  
  // Starting file the starting class is loaded
  const char* start_file;
  
  // Starting line the starting class is loaded
  int32_t start_line;
  
  // Syntax error count
  SPVM_LIST* error_messages;
  
  // Module source symtable
  SPVM_HASH* source_symtable;
  
  // Strings - string literals and symbol names
  SPVM_LIST* constant_strings;
  
  // String symtable
  SPVM_HASH* constant_string_symtable;
  
  // String Buffer
  SPVM_STRING_BUFFER* constant_strings_buffer;
  
  // Fail load class symtable
  SPVM_HASH* if_require_not_found_basic_type_name_symtable;
  
  // Operation codes
  SPVM_OPCODE_ARRAY* opcode_array;
  
  // Basic types
  SPVM_LIST* basic_types;
  
  // Basic type symbol table
  SPVM_HASH* basic_type_symtable;
  
  // Class variables
  SPVM_LIST* class_vars;
  
  // Field ops
  SPVM_LIST* fields;
  
  // Method ops
  SPVM_LIST* methods;
  
  // Anon methods
  SPVM_LIST* anon_methods;
  
  // Anon basic types
  SPVM_LIST* anon_basic_types;
  
  SPVM_LIST* cur_anon_op_types;
  
  // Argments
  SPVM_LIST* args;
  
  // Switch 
  SPVM_LIST* switch_infos;
  
  // SPVM runtime codes
  int32_t* runtime_codes;
  
};

SPVM_COMPILER* SPVM_COMPILER_new();
void SPVM_COMPILER_free(SPVM_COMPILER* compiler);
void SPVM_COMPILER_add_source(SPVM_COMPILER* compiler, const char* basic_type_name, const char* source, int32_t length);
void SPVM_COMPILER_add_basic_type_core(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t basic_type_category);
SPVM_BASIC_TYPE* SPVM_COMPILER_add_basic_type(SPVM_COMPILER* compiler, const char* basic_type_name);
void SPVM_COMPILER_add_basic_types(SPVM_COMPILER* compiler);
SPVM_RUNTIME* SPVM_COMPILER_new_object(SPVM_COMPILER* compiler);
void SPVM_COMPILER_error(SPVM_COMPILER* compiler, const char* message, ...);

void SPVM_COMPILER_print_error_messages(SPVM_COMPILER* compiler, FILE* fh);

const char* SPVM_COMPILER_get_start_file(SPVM_COMPILER* compiler);
void SPVM_COMPILER_set_start_file(SPVM_COMPILER* compiler, const char* start_file);
int32_t SPVM_COMPILER_get_start_line(SPVM_COMPILER* compiler);
void SPVM_COMPILER_set_start_line(SPVM_COMPILER* compiler, int32_t start_line);

void SPVM_COMPILER_add_include_dir(SPVM_COMPILER* compiler, const char* include_dir);
int32_t SPVM_COMPILER_get_include_dirs_length(SPVM_COMPILER* compiler);
const char* SPVM_COMPILER_get_include_dir(SPVM_COMPILER* compiler, int32_t index);
void SPVM_COMPILER_clear_include_dirs(SPVM_COMPILER* compiler);

int32_t SPVM_COMPILER_get_error_messages_length(SPVM_COMPILER* compiler);
const char* SPVM_COMPILER_get_error_message(SPVM_COMPILER* compiler, int32_t index);

int32_t SPVM_COMPILER_compile(SPVM_COMPILER* compiler, const char* basic_type_name);

int32_t SPVM_COMPILER_calculate_runtime_codes_length(SPVM_COMPILER* compiler);
int32_t* SPVM_COMPILER_create_runtime_codes(SPVM_COMPILER* compiler, SPVM_ALLOCATOR* allocator);

#endif
