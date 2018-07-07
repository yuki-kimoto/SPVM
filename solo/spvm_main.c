#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "spvm_compiler.h"
#include "spvm_hash.h"
#include "spvm_list.h"
#include "spvm_util_allocator.h"
#include "spvm_opcode_array.h"
#include "spvm_runtime.h"
#include "spvm_op.h"
#include "spvm_sub.h"
#include "spvm_dumper.h"
#include "spvm_yacc_util.h"
#include "spvm_runtime_api.h"
#include "spvm_opcode_builder.h"
#include "spvm_csource_builder.h"
#include "spvm_core_func.h"

#include <spvm_native.h>

int main(int argc, char *argv[])
{
  if (argc < 2) {
    fprintf(stderr, "Not script\n");
    exit(1);
  }
  
  // Package name
  const char* start_package_name = argv[1];
  
  // Create compiler
  SPVM_COMPILER* compiler = SPVM_COMPILER_new();
  
  // compiler->debug = 1;
  
  // Create use op for entry point package
  SPVM_OP* op_name_start = SPVM_OP_new_op_name(compiler, start_package_name, start_package_name, 0);
  SPVM_OP* op_type_start = SPVM_OP_build_basic_type(compiler, op_name_start);
  SPVM_OP* op_use_start = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, start_package_name, 0);
  SPVM_OP_build_use(compiler, op_use_start, op_type_start);
  SPVM_LIST_push(compiler->op_use_stack, op_use_start);
  
  // Entry point
  int32_t start_package_name_length = (int32_t)strlen(start_package_name);
  int32_t start_sub_name_length =  (int32_t)(start_package_name_length + 6);
  char* start_sub_name = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(start_sub_name_length + 1);
  strncpy(start_sub_name, start_package_name, start_package_name_length);
  strncpy(start_sub_name + start_package_name_length, "::main", 6);
  start_sub_name[start_sub_name_length] = '\0';
  compiler->start_sub_name = start_sub_name;

  SPVM_LIST_push(compiler->module_include_pathes, "lib");
  SPVM_LIST_push(compiler->module_include_pathes, "solo/lib");
  
  SPVM_COMPILER_compile(compiler);
  
  if (compiler->error_count > 0) {
    exit(1);
  }
  
  // Create run-time
  SPVM_RUNTIME* runtime = SPVM_COMPILER_new_runtime(compiler);
  compiler->runtime = runtime;
  
  SPVM_ENV* env = runtime->env;

  // Entry point subroutine address
  SPVM_OP* op_sub_start;
  int32_t sub_id;
  if (start_sub_name) {
    op_sub_start = SPVM_HASH_fetch(compiler->op_sub_symtable, start_sub_name, strlen(start_sub_name));
    if (op_sub_start) {
      sub_id = op_sub_start->uv.sub->id;
    }
    else {
      fprintf(stderr, "Can't find entry point subroutine %s", start_sub_name);
      exit(EXIT_FAILURE);
    }
  }
  else {
    fprintf(stderr, "Can't find entry point subroutine\n");
    exit(EXIT_FAILURE);
  }

  SPVM_VALUE* stack = runtime->stack;
  args[0].ival = 2;
  
  // Run
  int32_t exception_flag = env->call_sub(env, sub_id, stack);
  
  if (exception_flag) {
    SPVM_RUNTIME_API_print(env, runtime->exception);
    printf("\n");
  }
  else {
    printf("TEST return_value: %" PRId32 "\n", stack[0].ival);
  }
  
  SPVM_RUNTIME_free(runtime);
  
  return 0;
}
