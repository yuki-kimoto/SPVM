#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

#include "spvm.h"
#include "spvm_parser.h"
#include "spvm_hash.h"
#include "spvm_array.h"
#include "spvm_api.h"
#include "spvm_allocator_util.h"
#include "spvm_constant_pool.h"
#include "spvm_bytecode_array.h"
#include "spvm_parser.h"
#include "spvm_env.h"
#include "spvm_sv.h"
#include "spvm_allocator_runtime.h"

void SPVM_run(SPVM* spvm, const char* package_name) {
  
  spvm->parser = SPVM_PARSER_new(spvm);
  
  SPVM_ARRAY_push(spvm, spvm->parser->include_pathes, ".");
  SPVM_ARRAY_push(spvm, spvm->parser->include_pathes, "lib");
  
  SPVM_PARSER_parse(spvm, package_name);
  
  if (spvm->parser->error_count > 0) {
    return;
  }
  
  // Entry point
  const char* entry_point_sub_name = spvm->entry_point_sub_name;
  
  // Create subroutine environment
  SPVM_ENV* env = SPVM_ENV_new(spvm);
  
  // Push argument
  SPVM_API_push_var_long(spvm, env, 2);
  
  // Run
  SPVM_API_call_sub(spvm, env, entry_point_sub_name);
  
#ifdef DEBUG
  if (env->abort) {
    void* message = SPVM_API_pop_return_value_address(spvm, env);
    
    SPVM_SV* sv_message = SPVM_API_get_string_sv(spvm, env, message);
    
    printf("%s", sv_message->buffer);
    printf("\n");
  }
  else {
    // Get return value
    int64_t return_value = SPVM_API_pop_return_value_long(spvm, env);
    
    printf("TEST return_value: %ld\n", return_value);
  }
#endif

  SPVM_ENV_free(spvm, env);
}

SPVM* SPVM_new() {
  SPVM* spvm = SPVM_ALLOCATOR_UTIL_safe_malloc_i32(1, sizeof(SPVM));
  
  // Parser
  spvm->parser = NULL;
  
  // Entry point sub name
  spvm->entry_point_sub_name = NULL;
  
  // Constant pool
  spvm->constant_pool = SPVM_CONSTANT_POOL_new(spvm);
  
  // Bytecodes
  spvm->bytecode_array = SPVM_BYTECODE_ARRAY_new(spvm);

  // Constant poll subroutine symbol table
  spvm->constant_pool_package_symtable = SPVM_HASH_new(spvm, 0);
  
  // Constant poll subroutine symbol table
  spvm->constant_pool_field_symtable = SPVM_HASH_new(spvm, 0);
  
  // Constant poll subroutine symbol table
  spvm->constant_pool_sub_symtable = SPVM_HASH_new(spvm, 0);
  
  // Runtime memory allocator
  spvm->allocator_runtime = SPVM_ALLOCATOR_RUNTIME_new(spvm);
  
  // use memory pool max reference byte size
  spvm->ref_max_byte_size_use_memory_pool = 0xFFFF;
  
  return spvm;
}

void SPVM_free(SPVM* spvm) {
  
  SPVM_PARSER_free(spvm, spvm->parser);
  
  // Free constant pool
  SPVM_CONSTANT_POOL_free(spvm, spvm->constant_pool);
  
  // Free bytecode array
  SPVM_BYTECODE_ARRAY_free(spvm, spvm->bytecode_array);
  
  // Free runtime allocator
  SPVM_ALLOCATOR_RUNTIME_free(spvm, spvm->allocator_runtime);
  
  free(spvm);
}
