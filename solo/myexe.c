#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>

#include "spvm_native.h"
#include "spvm_api.h"
#include "spvm_compiler.h"

int32_t main(int32_t argc, const char *argv[]) {
  
  // Class name
  const char* class_name = "MyExe";
  
  SPVM_ENV* empty_env = NULL;
  
  // Create compiler
  SPVM_COMPILER* compiler = SPVM_API_new_compiler(empty_env);
  
  // compiler->debug = 1;
  
  SPVM_API_set_compiler_start_file(empty_env, compiler, class_name);

  SPVM_API_set_compiler_start_line(empty_env, compiler, 0);
  
  // Add module directory
  char* module_dir = "solo/SPVM";
  SPVM_API_add_module_dir(empty_env, compiler, module_dir);

  SPVM_API_compile_spvm(empty_env, compiler, class_name);
  
  if (SPVM_COMPILER_get_error_count(compiler) > 0) {
    SPVM_COMPILER_print_error_messages(compiler, stderr);
    exit(255);
  }

  // Create env
  SPVM_ENV* env = SPVM_API_new_env_raw();
  
  // Set the compiler
  env->compiler = compiler;
  
  // Initialize env
  SPVM_API_init_env(env);
  
  // Call INIT blocks
  env->call_init_blocks(env);
  
  // Class
  int32_t method_id = env->get_class_method_id(env, class_name, "main", "int(string,string[])");
  
  if (method_id < 0) {
    fprintf(stderr, "Can't find main method\n");
    return -1;
  }
  
  // Enter scope
  int32_t scope_id = env->enter_scope(env);
  
  // Starting file name
  void* cmd_start_file_obj = env->new_string(env, argv[0], strlen(argv[0]));
  
  // new byte[][args_length] object
  int32_t arg_type_basic_id = env->get_basic_type_id(env, "byte");
  void* cmd_args_obj = env->new_muldim_array(env, arg_type_basic_id, 1, argc - 1);
  
  // Set command line arguments
  for (int32_t arg_index = 1; arg_index < argc; arg_index++) {
    void* cmd_arg_obj = env->new_string(env, argv[arg_index], strlen(argv[arg_index]));
    env->set_elem_object(env, cmd_args_obj, arg_index - 1, cmd_arg_obj);
  }
  
  SPVM_VALUE stack[255];
  stack[0].oval = cmd_start_file_obj;
  stack[1].oval = cmd_args_obj;
  
  // Run
  int32_t exception_flag = env->call_spvm_method(env, method_id, stack);
  
  int32_t status;
  if (exception_flag) {
    env->print_stderr(env, env->exception_object);
    printf("\n");
    status = 255;
  }
  else {
    status = stack[0].ival;
  }
  
  // Leave scope
  env->leave_scope(env, scope_id);
  
  // Cleanup global variables
  SPVM_API_cleanup_global_vars(env);
  
  // Free env
  env->free_env(env);

  // Free compiler
  SPVM_API_free_compiler(empty_env, compiler);
  
  return status;
}
