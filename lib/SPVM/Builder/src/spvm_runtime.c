// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

#include "spvm_allocator.h"
#include "spvm_runtime.h"
#include "spvm_hash.h"
#include "spvm_runtime_string.h"
#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime_class_var.h"
#include "spvm_runtime_method.h"
#include "spvm_runtime_arg.h"
#include "spvm_opcode.h"

SPVM_RUNTIME* SPVM_RUNTIME_new() {
  SPVM_RUNTIME* runtime = SPVM_ALLOCATOR_alloc_memory_block_unmanaged(sizeof(SPVM_RUNTIME));
  
  // Allocator
  SPVM_ALLOCATOR* allocator = SPVM_ALLOCATOR_new();
  runtime->allocator = allocator;
  
  return runtime;
}

SPVM_ALLOCATOR* SPVM_RUNTIME_get_allocator(SPVM_RUNTIME* runtime) {
  return runtime->allocator;
}

void SPVM_RUNTIME_free(SPVM_RUNTIME* runtime) {
  
  // Free allocator
  SPVM_ALLOCATOR_free(runtime->allocator);
  runtime->allocator = NULL;
}

void SPVM_RUNTIME_build(SPVM_RUNTIME* runtime, int32_t* runtime_codes) {

  SPVM_ALLOCATOR* allocator = runtime->allocator;
  
  // runtime_codes
  runtime->runtime_codes = runtime_codes;
  
  int32_t* runtime_codes_ptr = runtime->runtime_codes;
  
  // runtime_codes_length
  runtime->runtime_codes_length = *runtime_codes_ptr;
  runtime_codes_ptr++;
  
  // basic_types length
  runtime->basic_types_length = *runtime_codes_ptr;
  runtime_codes_ptr++;
  
  // basic_types
  runtime->basic_types = (SPVM_RUNTIME_BASIC_TYPE*)runtime_codes_ptr;
  runtime_codes_ptr += (sizeof(SPVM_RUNTIME_BASIC_TYPE) / sizeof(int32_t)) * (runtime->basic_types_length);
  
  // string_pool_length
  int32_t string_pool_length = *runtime_codes_ptr;
  runtime_codes_ptr++;
  
  // string_pool
  runtime->string_pool = (const char*)runtime_codes_ptr;
  runtime_codes_ptr += string_pool_length / sizeof(int32_t);
  
  // class_vars runtime codes length
  int32_t class_vars_length = *runtime_codes_ptr;
  runtime_codes_ptr++;
  
  // class_vars
  runtime->class_vars = (SPVM_RUNTIME_CLASS_VAR*)runtime_codes_ptr;
  runtime_codes_ptr += (sizeof(SPVM_RUNTIME_CLASS_VAR) / sizeof(int32_t)) * class_vars_length;
  
  // fields_length
  int32_t fields_length = *runtime_codes_ptr;
  runtime_codes_ptr++;
  
  // fields
  runtime->fields = (SPVM_RUNTIME_FIELD*)runtime_codes_ptr;
  runtime_codes_ptr += (sizeof(SPVM_RUNTIME_FIELD) / sizeof(int32_t)) * fields_length;
  
  // methods_length
  int32_t methods_length = *runtime_codes_ptr;
  runtime_codes_ptr++;
  
  // methods
  runtime->methods = (SPVM_RUNTIME_METHOD*)runtime_codes_ptr;
  runtime_codes_ptr += (sizeof(SPVM_RUNTIME_METHOD) / sizeof(int32_t)) * methods_length;
  
  // args_length
  int32_t args_length = *runtime_codes_ptr;
  runtime_codes_ptr++;
  
  // args
  runtime->args = (SPVM_RUNTIME_ARG*)runtime_codes_ptr;
  runtime_codes_ptr += (sizeof(SPVM_RUNTIME_ARG) / sizeof(int32_t)) * args_length;
  
  // opcodes length
  int32_t opcodes_length = *runtime_codes_ptr;
  runtime_codes_ptr++;
  
  // opcodes
  runtime->opcodes = (SPVM_OPCODE*)runtime_codes_ptr;
  runtime_codes_ptr += (sizeof(SPVM_OPCODE) / sizeof(int32_t)) * opcodes_length;
  
  // anon_basic_types_length
  int32_t anon_basic_types_length = *runtime_codes_ptr;
  runtime_codes_ptr++;
  
  // anon_basic_types_length
  runtime->anon_basic_type_ids = runtime_codes_ptr;
  runtime_codes_ptr += (sizeof(int32_t) / sizeof(int32_t)) * anon_basic_types_length;
  
  // constant_strings_length
  runtime->constant_strings_length = *runtime_codes_ptr;
  runtime_codes_ptr++;
  
  // constant_strings
  runtime->constant_strings = (SPVM_RUNTIME_STRING*)runtime_codes_ptr;
  runtime_codes_ptr += (sizeof(SPVM_RUNTIME_STRING) / sizeof(int32_t)) * runtime->constant_strings_length;
  
  // Runtime string symtable
  for (int32_t basic_type_id = 0; basic_type_id < runtime->basic_types_length; basic_type_id++) {
    SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];
    for (int32_t constant_string_index = 0; constant_string_index < basic_type->constant_strings_length; constant_string_index++) {
      SPVM_RUNTIME_STRING* runtime_string = &runtime->constant_strings[basic_type->constant_strings_base + constant_string_index];
      runtime_string->value = &runtime->string_pool[basic_type->string_pool_base + runtime_string->string_pool_index];
    }
  }
  
  // Runtime basic type symtable
  runtime->basic_type_symtable = SPVM_HASH_new_hash_permanent(allocator, runtime->basic_types_length);
  for (int32_t basic_type_id = 0; basic_type_id < runtime->basic_types_length; basic_type_id++) {
    SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];
    SPVM_RUNTIME_STRING* basic_type_name_string = (SPVM_RUNTIME_STRING*)&runtime->constant_strings[basic_type->constant_strings_base + basic_type->name_string_index];
    const char* basic_type_name = basic_type_name_string->value;
    SPVM_HASH_set(runtime->basic_type_symtable, basic_type_name, strlen(basic_type_name), basic_type);
  }
}
