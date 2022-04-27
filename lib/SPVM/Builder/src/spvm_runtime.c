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

SPVM_ALLOCATOR* SPVM_RUNTIME_get_allocator(SPVM_RUNTIME* runtime) {
  return runtime->allocator;
}

void SPVM_RUNTIME_prepare(SPVM_RUNTIME* runtime) {

  SPVM_ALLOCATOR* allocator = runtime->allocator;

  // Runtime string symtable
  runtime->constant_string_symtable = SPVM_HASH_new_hash_permanent(allocator, 0);
  for (int32_t constant_string_id = 0; constant_string_id < runtime->constant_strings_length; constant_string_id++) {
    SPVM_RUNTIME_CONSTANT_STRING* runtime_string = &runtime->constant_strings[constant_string_id];
    runtime_string->value = &runtime->constant_strings_buffer[runtime_string->string_buffer_id];
    SPVM_HASH_set(runtime->constant_string_symtable, runtime_string->value, strlen(runtime_string->value), runtime_string);
  }

  // Runtime basic type symtable
  runtime->basic_type_symtable = SPVM_HASH_new_hash_permanent(allocator, runtime->basic_types_length);
  for (int32_t basic_type_id = 0; basic_type_id < runtime->basic_types_length; basic_type_id++) {
    SPVM_RUNTIME_BASIC_TYPE* runtime_basic_type = &runtime->basic_types[basic_type_id];
    SPVM_RUNTIME_CONSTANT_STRING* basic_type_name_string = (SPVM_RUNTIME_CONSTANT_STRING*)&runtime->constant_strings[runtime_basic_type->name_id];
    const char* runtime_basic_type_name = (const char*)&runtime->constant_strings_buffer[basic_type_name_string->string_buffer_id];
    SPVM_HASH_set(runtime->basic_type_symtable, runtime_basic_type_name, strlen(runtime_basic_type_name), runtime_basic_type);
  }

  // Runtime class symtable
  runtime->class_symtable = SPVM_HASH_new_hash_permanent(allocator, 0);
  for (int32_t class_id = 0; class_id < runtime->classes_length; class_id++) {
    SPVM_RUNTIME_CLASS* runtime_class = &runtime->classes[class_id];
    SPVM_RUNTIME_CONSTANT_STRING* class_name_string = (SPVM_RUNTIME_CONSTANT_STRING*)&runtime->constant_strings[runtime_class->name_id];
    const char* runtime_class_name = (const char*)&runtime->constant_strings_buffer[class_name_string->string_buffer_id];
    SPVM_HASH_set(runtime->class_symtable, runtime_class_name, strlen(runtime_class_name), runtime_class);
  }
  
  // Cache symtables
  runtime->method_cache_symtable = SPVM_HASH_new_hash_permanent(allocator, 0);
  runtime->field_cache_symtable = SPVM_HASH_new_hash_permanent(allocator, 0);
  runtime->class_var_cache_symtable = SPVM_HASH_new_hash_permanent(allocator, 0);
}

void SPVM_RUNTIME_free(SPVM_RUNTIME* runtime) {
  
  // Free allocator
  SPVM_ALLOCATOR_free(runtime->allocator);
  runtime->allocator = NULL;
}

void SPVM_RUNTIME_build(SPVM_RUNTIME* runtime, int32_t* spvm_32bit_codes) {

  SPVM_ALLOCATOR* allocator = runtime->allocator;
  
  // spvm_32bit_codes
  runtime->spvm_32bit_codes = spvm_32bit_codes;
  
  int32_t* spvm_32bit_codes_ptr = runtime->spvm_32bit_codes;

  // spvm_32bit_codes_length
  runtime->spvm_32bit_codes_length = *spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr++;

  // opcodes length
  runtime->opcodes_length = *spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr++;
  
  // opcodes 32bit length
  int32_t opcodes_32bit_length = *spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr++;
  
  // opcodes
  runtime->opcodes = (SPVM_OPCODE*)spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr += opcodes_32bit_length;
  
  // constant_strings_buffer length
  runtime->constant_strings_buffer_length = *spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr++;

  // constant_strings_buffer 32bit length
  int32_t constant_strings_buffer_32bit_length = *spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr++;
  
  // constant_strings_buffer
  runtime->constant_strings_buffer = (const char*)spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr += constant_strings_buffer_32bit_length;
  
  // constant_strings length
  runtime->constant_strings_length = *spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr++;

  // constant_strings 32bit length
  int32_t constant_strings_32bit_length = *spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr++;
  
  // constant_strings
  runtime->constant_strings = (SPVM_RUNTIME_CONSTANT_STRING*)spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr += constant_strings_32bit_length;

  // anon_method_methods length
  runtime->anon_methods_length = *spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr++;

  // anon_method_methods 32bit length
  int32_t anon_methods_32bit_length = *spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr++;

  // anon_method_method_ids
  runtime->anon_method_method_ids = spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr += anon_methods_32bit_length;

  // classes length
  runtime->classes_length = *spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr++;

  // classes 32bit length
  int32_t classes_32bit_length = *spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr++;
  
  // classes
  runtime->classes = (SPVM_RUNTIME_CLASS*)spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr += classes_32bit_length;

  // basic_types length
  runtime->basic_types_length = *spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr++;

  // basic_types 32bit length
  int32_t basic_types_32bit_length = *spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr++;
  
  // basic_types
  runtime->basic_types = (SPVM_RUNTIME_BASIC_TYPE*)spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr += basic_types_32bit_length;

  // types length
  runtime->types_length = *spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr++;

  // types 32bit length
  int32_t types_32bit_length = *spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr++;
  
  // types
  runtime->types = (SPVM_RUNTIME_TYPE*)spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr += types_32bit_length;

  // class_vars length
  runtime->class_vars_length = *spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr++;

  // class_vars 32bit length
  int32_t class_vars_32bit_length = *spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr++;
  
  // class_vars
  runtime->class_vars = (SPVM_RUNTIME_CLASS_VAR*)spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr += class_vars_32bit_length;

  // methods length
  runtime->methods_length = *spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr++;

  // methods 32bit length
  int32_t methods_32bit_length = *spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr++;
  
  // methods
  runtime->methods = (SPVM_RUNTIME_METHOD*)spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr += methods_32bit_length;

  // arg_types length
  runtime->arg_types_length = *spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr++;
  
  // arg_types 32bit length
  int32_t arg_types_32bit_length = *spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr++;
  
  // arg_type_ids
  runtime->arg_type_ids = spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr += arg_types_32bit_length;
  
  // fields length
  runtime->fields_length = *spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr++;

  // fields 32bit length
  int32_t fields_32bit_length = *spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr++;
  
  // fields
  runtime->fields = (SPVM_RUNTIME_FIELD*)spvm_32bit_codes_ptr;
  spvm_32bit_codes_ptr += fields_32bit_length;
  
  // Method native addresses
  runtime->method_native_addresses = SPVM_ALLOCATOR_alloc_memory_block_permanent(allocator, sizeof(void*) * runtime->methods_length);
  
  // Method precompile addresses
  runtime->method_precompile_addresses = SPVM_ALLOCATOR_alloc_memory_block_permanent(allocator, sizeof(void*) * runtime->methods_length);

#ifdef SPVM_DEBUG_RUNTIME
  fprintf(stderr, "[RUNTIME MEMORY SIZE]\n");
  fprintf(stderr, "opcodes size: %d bytes\n", (int32_t)(sizeof(SPVM_OPCODE) * runtime->opcodes_length));
  fprintf(stderr, "string_buffer size: %d bytes\n", (int32_t)(runtime->constant_strings_buffer_length));
  fprintf(stderr, "strings size: %d bytes\n", (int32_t)(sizeof(SPVM_RUNTIME_CONSTANT_STRING) * runtime->constant_strings_length));
  fprintf(stderr, "classes size: %d bytes\n", (int32_t)(sizeof(SPVM_RUNTIME_CLASS) * runtime->classes_length));
  fprintf(stderr, "basic_types size: %d bytes\n", (int32_t)(sizeof(SPVM_RUNTIME_BASIC_TYPE) * runtime->basic_types_length));
  fprintf(stderr, "types size: %d bytes\n", (int32_t)(sizeof(SPVM_RUNTIME_TYPE) * runtime->types_length));
  fprintf(stderr, "class_vars size: %d bytes\n", (int32_t)(sizeof(SPVM_RUNTIME_CLASS_VAR) * runtime->class_vars_length));
  fprintf(stderr, "methods size: %d bytes\n", (int32_t)(sizeof(SPVM_RUNTIME_METHOD) * runtime->methods_length));
  fprintf(stderr, "method_native_addresses size: %d bytes\n", (int32_t)(sizeof(void*) * runtime->methods_length));
  fprintf(stderr, "method_native_precompile size: %d bytes\n", (int32_t)(sizeof(void*) * runtime->methods_length));
  fprintf(stderr, "arg_type_ids size: %d bytes\n", (int32_t)(sizeof(int32_t) * runtime->arg_types_length));
  fprintf(stderr, "fields size: %d bytes\n", (int32_t)(sizeof(SPVM_RUNTIME_FIELD) * runtime->fields_length));
#endif

}
