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

// flag
// 0 : all
// 1 : native method
// 2 : precompile method
int32_t SPVM_API_COMPILER_get_next_method_id_flag(SPVM_COMPILER* compiler, const char* method_abs_name, int32_t start_index, int32_t flag) {  
  SPVM_LIST* methods = compiler->methods;
  int32_t found_index = -1;
  for (int32_t method_index = start_index; method_index < methods->length; method_index++) {
    SPVM_METHOD* method = SPVM_LIST_get(methods, method_index);
    
    if (!method) {
      break;
    }
    
    // Native method
    if (flag == 0 || flag == 1) {
      if (method->flag & SPVM_METHOD_C_FLAG_NATIVE) {
        found_index = method_index;
        break;
      }
    }
    
    // Precompile method
    if (flag == 0 || flag == 2) {
      if (method->flag & SPVM_METHOD_C_FLAG_PRECOMPILE) {
        found_index = method_index;
        break;
      }
    }
    
    // Normal method
    if (flag == 0) {
      found_index = method_index;
      break;
    }
  }  
  return found_index;
}

int32_t SPVM_API_COMPILER_get_class_id(SPVM_COMPILER* compiler, const char* class_name) {
  
  SPVM_CLASS* class = SPVM_HASH_get(compiler->class_symtable, class_name, strlen(class_name));
  int32_t class_id;
  if (class) {
    class_id = class->id;
  }
  else {
    class_id = -1;
  }  
  return class_id;
}

int32_t SPVM_API_COMPILER_get_classes_length(SPVM_COMPILER* compiler) {
  
  int32_t classes_length= compiler->classes->length;
  return classes_length;
}

const char* SPVM_API_COMPILER_get_class_name(SPVM_COMPILER* compiler, int32_t class_id) {
  
  SPVM_CLASS* class = SPVM_LIST_get(compiler->classes, class_id);
  assert(class);
  const char* class_name = class->name;
  return class_name;
}

const char* SPVM_API_COMPILER_get_class_module_file(SPVM_COMPILER* compiler, int32_t class_id) {
  
  SPVM_CLASS* class = SPVM_LIST_get(compiler->classes, class_id);
  assert(class);
  const char* class_module_file = class->module_file;
  return class_module_file;
}

int32_t SPVM_API_COMPILER_get_method_class_id(SPVM_COMPILER* compiler, int32_t method_id) {
  
  SPVM_METHOD* method = SPVM_LIST_get(compiler->methods, method_id);
  int32_t method_class_id;
  if (method) {
    method_class_id = method->class->id;
  }
  else {
    method_class_id = -1;
  }

  return method_class_id;
}

int32_t SPVM_API_COMPILER_is_anon_class(SPVM_COMPILER* compiler, int32_t class_id) {
  
  SPVM_CLASS* class = SPVM_LIST_get(compiler->classes, class_id);
  return class->is_anon;
}

int32_t SPVM_API_COMPILER_get_methods_length(SPVM_COMPILER* compiler, int32_t class_id) {
  
  SPVM_CLASS* class = SPVM_LIST_get(compiler->classes, class_id);
  int32_t methods_length = class->methods->length;
  return methods_length;
}

int32_t SPVM_API_COMPILER_get_method_id(SPVM_COMPILER* compiler, int32_t class_id, int32_t method_index_of_class) {
  
  SPVM_CLASS* class = SPVM_LIST_get(compiler->classes, class_id);
  int32_t method_id;
  if (class) {
    SPVM_METHOD* method = SPVM_LIST_get(class->methods, method_index_of_class);
    if (method) {
      method_id = method->id;
    }
    else {
      method_id = -2;
    }
  }
  else {
    method_id = -1;
  }  
  return method_id;
}

int32_t SPVM_API_COMPILER_get_method_id_by_name(SPVM_COMPILER* compiler, const char* class_name, const char* method_name) {
  
  SPVM_CLASS* class = SPVM_HASH_get(compiler->class_symtable, class_name, strlen(class_name));
  int32_t method_id;
  if (class) {
    SPVM_METHOD* method_symtable = SPVM_HASH_get(class->method_symtable, method_name, strlen(method_name));
    if (method_symtable) {
      method_id = method_symtable->id;
    }
    else {
      method_id = -2;
    }
  }
  else {
    method_id = -1;
  }  
  return method_id;
}

const char* SPVM_API_COMPILER_get_method_name(SPVM_COMPILER* compiler, int32_t method_id) {
  
  SPVM_METHOD* method = SPVM_LIST_get(compiler->methods, method_id);
  return method->name;
}

int32_t SPVM_API_COMPILER_is_anon_method(SPVM_COMPILER* compiler, int32_t method_id) {
  
  SPVM_METHOD* method = SPVM_LIST_get(compiler->methods, method_id);
  return method->flag & SPVM_METHOD_C_FLAG_ANON;
}

int32_t SPVM_API_COMPILER_is_init_block_method(SPVM_COMPILER* compiler, int32_t method_id) {
  
  SPVM_METHOD* method = SPVM_LIST_get(compiler->methods, method_id);
  return method->is_init;
}

int32_t SPVM_API_COMPILER_is_native_method(SPVM_COMPILER* compiler, int32_t method_id) {
  
  SPVM_METHOD* method = SPVM_LIST_get(compiler->methods, method_id);
  return method->flag & SPVM_METHOD_C_FLAG_NATIVE;
}

int32_t SPVM_API_COMPILER_is_precompile_method(SPVM_COMPILER* compiler, int32_t method_id) {
  
  SPVM_METHOD* method = SPVM_LIST_get(compiler->methods, method_id);
  return method->flag & SPVM_METHOD_C_FLAG_PRECOMPILE;
}

const char* SPVM_API_COMPILER_get_method_signature(SPVM_COMPILER* compiler, int32_t method_id) {
  
  SPVM_METHOD* method = SPVM_LIST_get(compiler->methods, method_id);
  return method->signature;
}

void* SPVM_API_COMPILER_get_native_method_address(SPVM_COMPILER* compiler, int32_t method_id) {
  
  SPVM_METHOD* method = SPVM_LIST_get(compiler->methods, method_id);
  void* native_method_address = method->native_address;
  return native_method_address;
}

void* SPVM_API_COMPILER_get_precompile_method_address(SPVM_COMPILER* compiler, int32_t method_id) {
  
  SPVM_METHOD* method = SPVM_LIST_get(compiler->methods, method_id);
  void* precompile_method_address = method->precompile_address;
  return precompile_method_address;
}

void SPVM_API_COMPILER_set_native_method_address(SPVM_COMPILER* compiler, int32_t method_id, void* address) {
  
  SPVM_METHOD* method = SPVM_LIST_get(compiler->methods, method_id);
  method->native_address = address;
}

void SPVM_API_COMPILER_set_precompile_method_address(SPVM_COMPILER* compiler, int32_t method_id, void* address) {
  
  SPVM_METHOD* method = SPVM_LIST_get(compiler->methods, method_id);
  method->precompile_address = address;
}

const char* SPVM_API_COMPILER_get_method_abs_name(SPVM_COMPILER* compiler, int32_t method_id) {
  
  SPVM_METHOD* method = SPVM_LIST_get(compiler->methods, method_id);
  const char* method_abs_name = method->abs_name;
  return method_abs_name;
}

SPVM_COMPILER* SPVM_API_COMPILER_new() {
  
  SPVM_COMPILER* compiler = SPVM_COMPILER_new();
  return compiler;
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

void SPVM_API_COMPILER_free(SPVM_COMPILER* compiler) {
  
  SPVM_COMPILER_free(compiler);
}

const char* SPVM_API_COMPILER_get_module_source(SPVM_COMPILER* compiler, const char* class_name) {  
  const char* module_source = SPVM_HASH_get(compiler->module_source_symtable, class_name, strlen(class_name));
  return module_source;
}

int32_t SPVM_API_COMPILER_get_error_messages_length(SPVM_COMPILER* compiler) {  
  return SPVM_COMPILER_get_error_messages_length(compiler);
}

const char* SPVM_API_COMPILER_get_error_message(SPVM_COMPILER* compiler, int32_t index) {  
  return  SPVM_COMPILER_get_error_message(compiler, index);
}

SPVM_ALLOCATOR* SPVM_API_COMPILER_get_allocator(SPVM_COMPILER* compiler) {  
  return compiler->allocator;
}
