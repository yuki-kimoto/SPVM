#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "spvm_native.h"

#include "spvm_compiler.h"
#include "spvm_api_compiler.h"
#include "spvm_list.h"
#include "spvm_hash.h"
#include "spvm_method.h"
#include "spvm_class.h"
#include "spvm_string_buffer.h"
#include "spvm_allocator.h"

SPVM_COMPILER* SPVM_API_COMPILER_new_compiler() {
  
  SPVM_COMPILER* compiler = SPVM_COMPILER_new();
  return compiler;
}

void SPVM_API_COMPILER_free_compiler(SPVM_COMPILER* compiler) {
  
  SPVM_COMPILER_free(compiler);
}

void SPVM_API_COMPILER_set_start_line(SPVM_COMPILER* compiler, int32_t start_line) {
  
  compiler->start_line = start_line;
}

int32_t SPVM_API_COMPILER_get_start_line(SPVM_COMPILER* compiler) {  
  return compiler->start_line;
}

void SPVM_API_COMPILER_set_start_file(SPVM_COMPILER* compiler, const char* start_file) {
  
  compiler->start_file = start_file;
}

const char* SPVM_API_COMPILER_get_start_file(SPVM_COMPILER* compiler) {  
  return compiler->start_file;
}

void SPVM_API_COMPILER_add_module_dir(SPVM_COMPILER* compiler, const char* module_dir) {  
  SPVM_LIST_push(compiler->module_dirs, (void*)module_dir);
}

int32_t SPVM_API_COMPILER_get_module_dirs_length (SPVM_COMPILER* compiler) {  
  SPVM_LIST* module_dirs = compiler->module_dirs;
  int32_t module_dirs_length = module_dirs->length;
  return module_dirs_length;
}

const char* SPVM_API_COMPILER_get_module_dir (SPVM_COMPILER* compiler, int32_t module_dir_id) {  
  const char* module_dir = SPVM_LIST_get(compiler->module_dirs, module_dir_id);
  return module_dir;
}

int32_t SPVM_API_COMPILER_compile_spvm(SPVM_COMPILER* compiler, const char* class_name) {
  
  int32_t error_code = SPVM_COMPILER_compile_spvm(compiler, class_name);
  return error_code;
}

void SPVM_API_COMPILER_build_runtime(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime) {  
  SPVM_COMPILER_build_runtime(compiler, runtime);
}

int32_t SPVM_API_COMPILER_get_error_messages_length(SPVM_COMPILER* compiler) {  
  return SPVM_COMPILER_get_error_messages_length(compiler);
}

const char* SPVM_API_COMPILER_get_error_message(SPVM_COMPILER* compiler, int32_t index) {  
  return  SPVM_COMPILER_get_error_message(compiler, index);
}

const char* SPVM_API_COMPILER_get_module_source_by_name(SPVM_COMPILER* compiler, const char* class_name) {  
  const char* module_source = SPVM_HASH_get(compiler->module_source_symtable, class_name, strlen(class_name));
  return module_source;
}
