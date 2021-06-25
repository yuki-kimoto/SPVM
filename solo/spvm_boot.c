#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>

#include "spvm_native.h"
#include "spvm_api.h"

#include "spvm_op.h"
#include "spvm_compiler.h"
#include "spvm_hash.h"
#include "spvm_list.h"

#include <spvm_native.h>

int32_t main(int32_t argc, const char *argv[]) {
  
  // Package name
  const char* package_name = "Main";
  
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
  SPVM_LIST_push(compiler->module_dirs, cur_script_dir);
  
  SPVM_COMPILER_compile(compiler);
  
  if (compiler->error_count > 0) {
    exit(1);
  }

  // Create env
  SPVM_ENV* env = SPVM_API_create_env(compiler);
  
  // Call begin blocks
  SPVM_API_call_begin_blocks(env);

  // Package
  int32_t method_id = SPVM_API_get_method_id(env, package_name, "main", "int(string[])");
  
  if (method_id < 0) {
    return -1;
  }
  
  // Enter scope
  int32_t scope_id = env->enter_scope(env);
  
  // new byte[][args_length] object
  int32_t arg_type_basic_id = env->get_basic_type_id(env, "byte");
  void* cmd_args_obj = env->new_muldim_array(env, arg_type_basic_id, 1, argc);
  
  // Set command line arguments
  for (int32_t arg_index = 0; arg_index < argc; arg_index++) {
    void* cmd_arg_obj = env->new_string(env, argv[arg_index], strlen(argv[arg_index]));
    env->set_elem_object(env, cmd_args_obj, arg_index, cmd_arg_obj);
  }
  
  SPVM_VALUE stack[255];
  stack[0].oval = cmd_args_obj;
  
  // Run
  int32_t exception_flag = env->call_spvm_method(env, method_id, stack);
  
  int32_t status;
  if (exception_flag) {
    SPVM_API_print(env, env->exception_object);
    printf("\n");
    status = 255;
  }
  else {
    status = stack[0].ival;
  }
  
  // Leave scope
  env->leave_scope(env, scope_id);
  
  SPVM_API_free_env(env);

  // Free compiler
  SPVM_COMPILER_free(compiler);
  
  return status;
}
