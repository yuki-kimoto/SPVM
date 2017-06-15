#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../spvm_compiler.h"
#include "../spvm_hash.h"
#include "../spvm_array.h"
#include "../spvm_util_allocator.h"
#include "../spvm_constant_pool.h"
#include "../spvm_bytecode_array.h"
#include "../spvm_runtime.h"
#include "../spvm_runtime_api.h"
#include "../spvm_runtime_allocator.h"
#include "../spvm_op.h"
#include "../spvm_sub.h"
#include "../spvm_data_api.h"

int main(int argc, char *argv[])
{
  if (argc < 2) {
    fprintf(stderr, "Not script\n");
    exit(1);
  }
  
  // Package name
  const char* package_name = argv[1];
  
  // Create compiler
  SPVM_COMPILER* compiler = SPVM_COMPILER_new();
  
  compiler->entry_point_package_name = package_name;
  
  SPVM_ARRAY_push(compiler->include_pathes, "lib");
  SPVM_ARRAY_push(compiler->include_pathes, "solo");
  
  SPVM_COMPILER_compile(compiler);
  
  if (compiler->error_count > 0) {
    return;
  }
  else {
#ifdef DEBUG
    // Dump spvm information
    SPVM_DUMPER_dump_all(compiler);
#endif
  }

  
  // Create run-time
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_new();
  
  // Copy constant pool to runtime
  runtime->constant_pool = SPVM_UTIL_ALLOCATOR_safe_malloc_i32(compiler->constant_pool->length, sizeof(int32_t));
  memcpy(runtime->constant_pool, compiler->constant_pool->values, compiler->constant_pool->length * sizeof(int32_t));

  // Copy bytecodes to runtime
  runtime->bytecodes = SPVM_UTIL_ALLOCATOR_safe_malloc_i32(compiler->bytecode_array->length, sizeof(uint8_t));
  memcpy(runtime->bytecodes, compiler->bytecode_array->values, compiler->bytecode_array->length * sizeof(uint8_t));

  // Entry point subroutine address
  const char* entry_point_sub_name = compiler->entry_point_sub_name;
  SPVM_OP* op_sub_start;
  int32_t sub_constant_pool_index;
  if (entry_point_sub_name) {
    op_sub_start = SPVM_HASH_search(compiler->op_sub_symtable, entry_point_sub_name, strlen(entry_point_sub_name));
    if (op_sub_start) {
      sub_constant_pool_index = op_sub_start->uv.sub->constant_pool_index;
    }
    else {
      fprintf(stderr, "Can't find entry point subroutine %s", entry_point_sub_name);
      exit(EXIT_FAILURE);
    }
  }
  else {
    fprintf(stderr, "Can't find entry point subroutine\n");
    exit(EXIT_FAILURE);
  }
  
  // Free compiler
  SPVM_COMPILER_free(compiler);
  
  // Initialize runtime before push arguments and call subroutine
  SPVM_RUNTIME_init(runtime);
  
  // Push argument
  SPVM_RUNTIME_API_push_var_long(runtime, 2);

  // Run
  SPVM_RUNTIME_call_sub(runtime, sub_constant_pool_index);
  
#ifdef DEBUG
  if (runtime->abort) {
    void* message_address = SPVM_RUNTIME_API_pop_return_value_address(runtime);
    int8_t* message = SPVM_DATA_API_get_array_values_byte(message_address);
    
    printf("%s", (char*)message);
    printf("\n");
  }
  else {
    // Get return value
    int64_t return_value = SPVM_RUNTIME_API_pop_return_value_long(runtime);
    
    printf("TEST return_value: %ld\n", return_value);
  }
#endif
  
  return 0;
}
