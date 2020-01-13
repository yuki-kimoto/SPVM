#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>

#include "spvm_native.h"

#include "spvm_op.h"
#include "spvm_compiler.h"
#include "spvm_hash.h"
#include "spvm_list.h"
#include "spvm_runtime.h"
#include "spvm_runtime_api.h"
#include "spvm_runtime_info.h"

#include <spvm_native.h>

int32_t main(int32_t argc, const char *argv[]) {
  
  // Package name
  const char* package_name = "TestCase";
  
  // Create compiler
  SPVM_COMPILER* compiler = SPVM_COMPILER_new();
  
  // compiler->debug = 1;
  
  // Create use op for entry point package
  SPVM_OP* op_name_start = SPVM_OP_new_op_name(compiler, package_name, package_name, 0);
  SPVM_OP* op_type_start = SPVM_OP_build_basic_type(compiler, op_name_start);
  SPVM_OP* op_use_start = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, package_name, 0);
  SPVM_OP_build_use(compiler, op_use_start, op_type_start, NULL, 0);
  SPVM_LIST_push(compiler->op_use_stack, op_use_start);
  
  // Get script directory
  const char* cur_script_name = argv[0];
  int32_t cur_script_name_length = (int32_t)strlen(argv[0]);
  char* cur_script_dir = malloc(cur_script_name_length + 1);
  memcpy(cur_script_dir, cur_script_name, cur_script_name_length);
  cur_script_dir[cur_script_name_length] = '\0';
  int32_t found_sep = 0;
  for (int32_t i = cur_script_name_length - 1; i >= 0; i--) {
    if (cur_script_dir[i] == '/' || cur_script_dir[i] == '\\') {
      cur_script_dir[i] = '\0';
      found_sep = 1;
      break;
    }
  }
  if (!found_sep) {
    cur_script_dir[0] = '.';
    cur_script_dir[1] = '\0';
  }
  
  // Add include path
  SPVM_LIST_push(compiler->module_include_pathes, cur_script_dir);
  
  SPVM_COMPILER_compile(compiler);
  
  if (compiler->error_count > 0) {
    exit(1);
  }

  // Build runtime_info info
  SPVM_RUNTIME_INFO* runtime_info = SPVM_RUNTIME_INFO_build_runtime_info(compiler);
  
  // Build runtime
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_build_runtime(runtime_info);
  
  // Create env
  SPVM_ENV* env = SPVM_RUNTIME_API_create_env(runtime);
  
  // Free compiler
  SPVM_COMPILER_free(compiler);
  
  // Call begin blocks
  SPVM_RUNTIME_API_call_begin_blocks(env);

  // Call entry point sub
  int32_t status_code = SPVM_RUNTIME_API_call_entry_point_sub(env, package_name, argc, argv);
  
  SPVM_RUNTIME_API_free_env(env);
  SPVM_RUNTIME_API_free_runtime(runtime);
  
  return status_code;
}
