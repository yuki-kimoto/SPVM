#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "../spvm_compiler.h"
#include "../spvm_hash.h"
#include "../spvm_dynamic_array.h"
#include "../spvm_util_allocator.h"
#include "../spvm_constant_pool.h"
#include "../spvm_bytecode_array.h"
#include "../spvm_runtime.h"
#include "../spvm_runtime_allocator.h"
#include "../spvm_op.h"
#include "../spvm_sub.h"
#include "../spvm_dumper.h"
#include "../spvm_api.h"

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
  
  // compiler->debug = 1;
  
  compiler->entry_point_package_name = package_name;
  
  SPVM_DYNAMIC_ARRAY_push(compiler->include_pathes, "lib");
  SPVM_DYNAMIC_ARRAY_push(compiler->include_pathes, "solo");
  
  SPVM_COMPILER_compile(compiler);
  
  if (compiler->error_count > 0) {
    return 1;
  }
  else {
#ifdef DEBUG
    // Dump spvm information
    SPVM_DUMPER_dump_all(compiler);
#endif
  }

  
  // Create run-time
  SPVM_RUNTIME* runtime = SPVM_COMPILER_new_runtime(compiler);
  SPVM_API* api = runtime->api;

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
  
  SPVM_API_VALUE args[1];
  args[0].int_value = 2;
  
  // Run
  int32_t return_value = api->call_int_sub(api, sub_constant_pool_index, args);
  
#ifdef DEBUG
  if (runtime->exception) {
    void* message_object = runtime->exception;
    int8_t* message = api->get_byte_array_elements(api, message_object);
    
    printf("%s", (char*)message);
    printf("\n");
  }
  else {
    printf("TEST return_value: %" PRId32 "\n", return_value);
  }
#endif
  
  SPVM_RUNTIME_free(runtime);
  
  return 0;
}
