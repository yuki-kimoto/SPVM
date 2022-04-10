#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

#include "spvm_allocator.h"
#include "spvm_runtime.h"
#include "spvm_hash.h"
#include "spvm_runtime_constant_string.h"
#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_class.h"

SPVM_RUNTIME* SPVM_RUNTIME_new() {
  SPVM_RUNTIME* runtime = SPVM_ALLOCATOR_alloc_memory_block_unmanaged(sizeof(SPVM_RUNTIME));
  
  // Allocator
  SPVM_ALLOCATOR* allocator = SPVM_ALLOCATOR_new();
  runtime->allocator = allocator;
  
  return runtime;
}

void SPVM_RUNTIME_prepare(SPVM_RUNTIME* runtime) {

  SPVM_ALLOCATOR* allocator = runtime->allocator;

  // Runtime string symtable
  runtime->constant_string_symtable = SPVM_HASH_new_hash_permanent(allocator, 0);
  for (int32_t constant_string_id = 0; constant_string_id < runtime->constant_strings_length; constant_string_id++) {
    SPVM_RUNTIME_CONSTANT_STRING* runtime_string = &runtime->constant_strings[constant_string_id];
    runtime_string->value = &runtime->string_buffer[runtime_string->string_buffer_id];
    SPVM_HASH_set(runtime->constant_string_symtable, runtime_string->value, strlen(runtime_string->value), runtime_string);
  }

  // Runtime basic type symtable
  runtime->basic_type_symtable = SPVM_HASH_new_hash_permanent(allocator, runtime->basic_types_length);
  for (int32_t basic_type_id = 0; basic_type_id < runtime->basic_types_length; basic_type_id++) {
    SPVM_RUNTIME_BASIC_TYPE* runtime_basic_type = &runtime->basic_types[basic_type_id];
    SPVM_RUNTIME_CONSTANT_STRING* basic_type_name_string = (SPVM_RUNTIME_CONSTANT_STRING*)&runtime->constant_strings[runtime_basic_type->name_id];
    const char* runtime_basic_type_name = (const char*)&runtime->string_buffer[basic_type_name_string->string_buffer_id];
    SPVM_HASH_set(runtime->basic_type_symtable, runtime_basic_type_name, strlen(runtime_basic_type_name), runtime_basic_type);
  }

  // Runtime class symtable
  runtime->class_symtable = SPVM_HASH_new_hash_permanent(allocator, 0);
  for (int32_t class_id = 0; class_id < runtime->classes_length; class_id++) {
    SPVM_RUNTIME_CLASS* runtime_class = &runtime->classes[class_id];
    SPVM_RUNTIME_CONSTANT_STRING* class_name_string = (SPVM_RUNTIME_CONSTANT_STRING*)&runtime->constant_strings[runtime_class->name_id];
    const char* runtime_class_name = (const char*)&runtime->string_buffer[class_name_string->string_buffer_id];
    SPVM_HASH_set(runtime->class_symtable, runtime_class_name, strlen(runtime_class_name), runtime_class);
  }
}

void SPVM_RUNTIME_free(SPVM_RUNTIME* runtime) {
  
  // Free allocator
  SPVM_ALLOCATOR_free(runtime->allocator);
  runtime->allocator = NULL;
}
