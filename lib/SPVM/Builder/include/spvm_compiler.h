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
  SPVM_LIST* class_paths;

  // Class loading stack
  SPVM_LIST* op_use_stack;

  // Types
  SPVM_LIST* op_types;
  
  // Directory of curreparsed file
  const char* cur_dir;
  
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

  // Next double quote start position
  char* next_string_literal_bufptr;

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

  // Current class base;
  int32_t cur_class_base;
  
  // Starting file the starting class is loaded
  const char* start_file;
  
  // Starting line the starting class is loaded
  int32_t start_line;
  
  // Syntax error count
  SPVM_LIST* error_messages;
  
  // Strings - string literals and symbol names
  SPVM_LIST* constant_strings;
  
  // String symtable
  SPVM_HASH* constant_string_symtable;

  // String Buffer
  SPVM_STRING_BUFFER* constant_strings_buffer;
  
  // Used class symtable
  SPVM_HASH* used_class_symtable;

  // Fail load class symtable
  SPVM_HASH* not_found_class_class_symtable;
  
  // Operation codes
  SPVM_OPCODE_ARRAY* opcode_array;
  
  // Basic types
  SPVM_LIST* basic_types;
  
  // Basic type symbol table
  SPVM_HASH* basic_type_symtable;

  // Types
  SPVM_LIST* types;
  
  // Types symbol table
  SPVM_HASH* type_symtable;
  
  // Classes
  SPVM_LIST* classes;

  // OP class symtable
  SPVM_HASH* class_symtable;

  // Anon methods
  SPVM_LIST* anon_methods;
  
  // Method ops
  SPVM_LIST* methods;

  // Argments
  SPVM_LIST* args;

  // OP our symtable
  SPVM_LIST* class_vars;

  // Field ops
  SPVM_LIST* fields;
  
  // Switch 
  SPVM_LIST* switch_infos;
  
  // class source symtable
  SPVM_HASH* class_source_symtable;
  
  // SPVM 32bit codes
  int32_t* runtime_codes;
};

SPVM_COMPILER* SPVM_COMPILER_new();
void SPVM_COMPILER_free(SPVM_COMPILER* compiler);
void SPVM_COMPILER_add_basic_types(SPVM_COMPILER* compiler);
SPVM_RUNTIME* SPVM_COMPILER_new_object(SPVM_COMPILER* compiler);
void SPVM_COMPILER_error(SPVM_COMPILER* compiler, const char* message, ...);

void SPVM_COMPILER_print_error_messages(SPVM_COMPILER* compiler, FILE* fh);

const char* SPVM_COMPILER_get_start_file(SPVM_COMPILER* compiler);
void SPVM_COMPILER_set_start_file(SPVM_COMPILER* compiler, const char* start_file);
int32_t SPVM_COMPILER_get_start_line(SPVM_COMPILER* compiler);
void SPVM_COMPILER_set_start_line(SPVM_COMPILER* compiler, int32_t start_line);

void SPVM_COMPILER_add_class_path(SPVM_COMPILER* compiler, const char* class_path);
int32_t SPVM_COMPILER_get_class_paths_length(SPVM_COMPILER* compiler);
const char* SPVM_COMPILER_get_class_path(SPVM_COMPILER* compiler, int32_t index);
void SPVM_COMPILER_clear_class_paths(SPVM_COMPILER* compiler);

int32_t SPVM_COMPILER_get_error_messages_length(SPVM_COMPILER* compiler);
const char* SPVM_COMPILER_get_error_message(SPVM_COMPILER* compiler, int32_t index);

int32_t SPVM_COMPILER_compile(SPVM_COMPILER* compiler, const char* class_name);

int32_t SPVM_COMPILER_calculate_runtime_codes_length(SPVM_COMPILER* compiler);
int32_t* SPVM_COMPILER_create_runtime_codes(SPVM_COMPILER* compiler, SPVM_ALLOCATOR* allocator);

#endif
