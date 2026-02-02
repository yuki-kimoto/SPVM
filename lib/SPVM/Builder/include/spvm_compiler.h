// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_COMPILER_H
#define SPVM_COMPILER_H

#include <stdio.h>

#include "spvm_typedecl.h"
#include "spvm_native.h"

enum {
  SPVM_COMPILER_C_ERROR_REASON_SIZE = 1024,
};

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
  const char* current_class_dir;
  
  // Current parsed file name
  const char* current_file;
  
  // Current parsed file relative name
  const char* current_class_rel_file;
  
  // Current parsed basic type name
  const char* current_outmost_class_name;
  
  // Current parsed source
  char* current_class_content;
  
  // Current parsed source
  int32_t current_class_content_length;
  
  // Current line number
  int32_t current_line;
  
  // Current temporary variables length
  int32_t current_tmp_vars_length;
  
  int32_t current_monitor_vars_length;
  
  // Allocator
  SPVM_ALLOCATOR* global_allocator;
  
  SPVM_LIST* each_compile_allocators;
  
  SPVM_ALLOCATOR* current_each_compile_allocator;
  
  SPVM_ALLOCATOR* error_message_allocator;
  
  SPVM_ALLOCATOR* class_file_allocator;
  
  // Line start position
  char* line_begin_ch_ptr;
  
  char* line_begin_after_shebang_line_ch_ptr;
  
  // Char pointer of current source
  char* ch_ptr;
  
  // Char pointer of current source just before
  char* token_begin_ch_ptr;
  
  // Next double quote start position
  char* next_string_literal_ch_ptr;
  
  // Expect method name
  int8_t expect_method_name;
  
  // Expect field name
  int8_t expect_field_name;
  
  // Before token is arrow
  int8_t before_token_is_arrow;
  
  // Before token is arrow
  int8_t previous_token_is_heredoc;
  
  // End of file
  int8_t end_of_file;
  
  // State of variable expansion
  int8_t var_expansion_state;
  
  // Current enum value
  int32_t current_enum_value;
  
  // Current basic type base;
  int32_t basic_types_base_id;
  
  int32_t constant_strings_base_id;
  
  // Starting file the starting class is loaded
  const char* start_file;
  
  // Starting line the starting class is loaded
  int32_t start_line;
  
  SPVM_LIST* error_messages;
  
  SPVM_LIST* class_files;
  
  SPVM_LIST* class_file_class_names;
  
  SPVM_LIST* constant_strings;
  
  // String symtable
  SPVM_HASH* constant_string_symtable;
  
  SPVM_LIST* global_strings;
  
  // String symtable
  SPVM_HASH* global_string_symtable;
  
  // Fail load class symtable
  SPVM_HASH* if_require_not_found_basic_type_name_symtable;
  
  SPVM_LIST* current_anon_op_types;
  
  // Basic types
  SPVM_LIST* basic_types;
  
  // Basic type symbol table
  SPVM_HASH* basic_type_symtable;
  
  SPVM_RUNTIME* runtime;
  
  SPVM_MUTEX* mutex_compile;
  
  int32_t eval_anon_classes_length;
  
};

SPVM_COMPILER* SPVM_COMPILER_new();

void SPVM_COMPILER_free(SPVM_COMPILER* compiler);

SPVM_CLASS_FILE* SPVM_COMPILER_get_class_file(SPVM_COMPILER* compiler, const char* basic_type_name);

void SPVM_COMPILER_set_class_file(SPVM_COMPILER* compiler, const char* basic_type_name, SPVM_CLASS_FILE* class_file);

void SPVM_COMPILER_add_class_file(SPVM_COMPILER* compiler, const char* class_name);

void SPVM_COMPILER_delete_class_file(SPVM_COMPILER* compiler, const char* class_name);

void SPVM_COMPILER_free_class_file(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file);

void SPVM_COMPILER_add_basic_type_core(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t basic_type_category);

SPVM_BASIC_TYPE* SPVM_COMPILER_add_basic_type(SPVM_COMPILER* compiler, const char* basic_type_name);

void SPVM_COMPILER_add_basic_types(SPVM_COMPILER* compiler);

SPVM_RUNTIME* SPVM_COMPILER_new_object(SPVM_COMPILER* compiler);

void SPVM_COMPILER_error(SPVM_COMPILER* compiler, const char* message, ...);

const char* SPVM_COMPILER_get_start_file(SPVM_COMPILER* compiler);

void SPVM_COMPILER_set_start_file(SPVM_COMPILER* compiler, const char* start_file);

int32_t SPVM_COMPILER_get_start_line(SPVM_COMPILER* compiler);

void SPVM_COMPILER_set_start_line(SPVM_COMPILER* compiler, int32_t start_line);

void SPVM_COMPILER_add_include_dir(SPVM_COMPILER* compiler, const char* include_dir);

void SPVM_COMPILER_prepend_include_dir(SPVM_COMPILER* compiler, const char* include_dir);

int32_t SPVM_COMPILER_get_include_dirs_length(SPVM_COMPILER* compiler);

const char* SPVM_COMPILER_get_include_dir(SPVM_COMPILER* compiler, int32_t index);

void SPVM_COMPILER_clear_include_dirs(SPVM_COMPILER* compiler);

int32_t SPVM_COMPILER_get_error_messages_length(SPVM_COMPILER* compiler);

const char* SPVM_COMPILER_get_error_message(SPVM_COMPILER* compiler, int32_t index);

int32_t SPVM_COMPILER_compile(SPVM_COMPILER* compiler, const char* basic_type_name);

SPVM_RUNTIME* SPVM_COMPILER_build_runtime(SPVM_COMPILER* compiler);

SPVM_RUNTIME* SPVM_COMPILER_get_runtime(SPVM_COMPILER* compiler);

void SPVM_COMPILER_use_default_loaded_classes(SPVM_COMPILER* compiler);

void SPVM_COMPILER_set_default_loaded_class_files(SPVM_COMPILER* compiler);

void SPVM_COMPILER_set_class_file_with_members(SPVM_COMPILER* compiler, const char* class_name, const char* rel_file, const char* content);

void SPVM_COMPILER_assert_check_basic_type_ids(SPVM_COMPILER* compiler);

void SPVM_COMPILER_assert_check_basic_type_id(SPVM_COMPILER* compiler, int32_t basic_type_id);

void free_memory_each_compile(SPVM_COMPILER* compiler);

void SPVM_COMPILER_use(SPVM_COMPILER* compiler, const char* basic_type_name, const char* file, int32_t line);

void SPVM_COMPILER_free_memory_tmp_each_compile(SPVM_COMPILER* compiler);

void SPVM_COMPILER_clear_error_messages(SPVM_COMPILER* compiler);

int32_t SPVM_COMPILER_compile_common(SPVM_COMPILER* compiler, const char* basic_type_name, const char* source, const char** anon_basic_type_name);

int32_t SPVM_COMPILER_compile_script(SPVM_COMPILER* compiler, const char* source, const char** anon_basic_type_name);

int32_t SPVM_COMPILER_compile_anon_class(SPVM_COMPILER* compiler, const char* source, const char** anon_basic_type_name);

#endif
