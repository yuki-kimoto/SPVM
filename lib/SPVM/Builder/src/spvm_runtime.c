// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

#include "spvm_allocator.h"
#include "spvm_runtime.h"
#include "spvm_hash.h"
#include "spvm_runtime_constant_string.h"
#include "spvm_runtime_basic_type.h"

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
  
  // string_pool runtime codes length
  int32_t string_pool_runtime_codes_length = *runtime_codes_ptr;
  runtime_codes_ptr++;
  
  // string_pool
  runtime->string_pool = (const char*)runtime_codes_ptr;
  runtime_codes_ptr += string_pool_runtime_codes_length;
  
  // constant_strings length
  runtime->constant_strings_length = *runtime_codes_ptr;
  runtime_codes_ptr++;
  
  // constant_strings runtime codes length
  int32_t constant_strings_runtime_codes_length = *runtime_codes_ptr;
  runtime_codes_ptr++;
  
  // constant_strings
  runtime->constant_strings = (SPVM_RUNTIME_CONSTANT_STRING*)runtime_codes_ptr;
  runtime_codes_ptr += constant_strings_runtime_codes_length;
  
  // basic_types length
  runtime->basic_types_length = *runtime_codes_ptr;
  runtime_codes_ptr++;
  
  // basic_types runtime codes length
  int32_t basic_types_runtime_codes_length = *runtime_codes_ptr;
  runtime_codes_ptr++;
  
  // basic_types
  runtime->basic_types = (SPVM_RUNTIME_BASIC_TYPE*)runtime_codes_ptr;
  runtime_codes_ptr += basic_types_runtime_codes_length;
  
  // class_vars runtime codes length
  int32_t class_vars_runtime_codes_length = *runtime_codes_ptr;
  runtime_codes_ptr++;
  
  // class_vars
  runtime->class_vars = (SPVM_RUNTIME_CLASS_VAR*)runtime_codes_ptr;
  runtime_codes_ptr += class_vars_runtime_codes_length;
  
  // fields runtime codes length
  int32_t fields_runtime_codes_length = *runtime_codes_ptr;
  runtime_codes_ptr++;
  
  // fields
  runtime->fields = (SPVM_RUNTIME_FIELD*)runtime_codes_ptr;
  runtime_codes_ptr += fields_runtime_codes_length;
  
  // opcodes runtime codes length
  int32_t opcodes_runtime_codes_length = *runtime_codes_ptr;
  runtime_codes_ptr++;
  
  // opcodes
  runtime->opcodes = (SPVM_OPCODE*)runtime_codes_ptr;
  runtime_codes_ptr += opcodes_runtime_codes_length;
  
  // methods runtime codes length
  int32_t methods_runtime_codes_length = *runtime_codes_ptr;
  runtime_codes_ptr++;
  
  // methods
  runtime->methods = (SPVM_RUNTIME_METHOD*)runtime_codes_ptr;
  runtime_codes_ptr += methods_runtime_codes_length;
  
  // args runtime codes length
  int32_t args_runtime_codes_length = *runtime_codes_ptr;
  runtime_codes_ptr++;
  
  // args
  runtime->args = (SPVM_RUNTIME_ARG*)runtime_codes_ptr;
  runtime_codes_ptr += args_runtime_codes_length;
  
  // anon_basic_type_basic_types runtime codes length
  int32_t anon_basic_types_runtime_codes_length = *runtime_codes_ptr;
  runtime_codes_ptr++;
  
  // anon_basic_type_ids
  runtime->anon_basic_type_ids = runtime_codes_ptr;
  runtime_codes_ptr += anon_basic_types_runtime_codes_length;
  
  // Runtime string symtable
  for (int32_t constant_string_id = 0; constant_string_id < runtime->constant_strings_length; constant_string_id++) {
    SPVM_RUNTIME_CONSTANT_STRING* runtime_string = &runtime->constant_strings[constant_string_id];
    runtime_string->value = &runtime->string_pool[runtime_string->string_pool_address_id];
  }
  
  // Runtime basic type symtable
  runtime->basic_type_symtable = SPVM_HASH_new_hash_permanent(allocator, runtime->basic_types_length);
  for (int32_t basic_type_id = 0; basic_type_id < runtime->basic_types_length; basic_type_id++) {
    SPVM_RUNTIME_BASIC_TYPE* runtime_basic_type = &runtime->basic_types[basic_type_id];
    SPVM_RUNTIME_CONSTANT_STRING* basic_type_name_string = (SPVM_RUNTIME_CONSTANT_STRING*)&runtime->constant_strings[runtime_basic_type->name_string_address_id];
    const char* runtime_basic_type_name = (const char*)&runtime->string_pool[basic_type_name_string->string_pool_address_id];
    SPVM_HASH_set(runtime->basic_type_symtable, runtime_basic_type_name, strlen(runtime_basic_type_name), runtime_basic_type);
  }
}
