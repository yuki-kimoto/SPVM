#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>

#include "spvm_native.h"
#include "spvm_api.h"
#include "spvm_api_compiler.h"
#include "spvm_api_runtime.h"
#include "spvm_api_allocator.h"
#include "spvm_api_string_buffer.h"

int32_t main(int32_t argc, const char *argv[]) {
  
  SPVM_ENV* env = SPVM_NATIVE_new_env_prepared();
  
  // Class name
  const char* class_name = "MyExe";
  
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
  
  SPVM_API_free_env_prepared(env);
  
  return status;
}

SPVM_ENV* SPVM_NATIVE_new_env_prepared() {
  // Class name
  const char* class_name = "MyExe";

  // Create env
  SPVM_ENV* env = SPVM_NATIVE_new_env_raw();
  
  // Create compiler
  void* compiler = SPVM_API_COMPILER_new();
  
  // compiler->debug = 1;
  
  SPVM_API_COMPILER_set_start_file(compiler, class_name);

  SPVM_API_COMPILER_set_start_line(compiler, 0);
  
  // Add module directory
  char* module_dir = "solo/SPVM";
  SPVM_API_COMPILER_add_module_dir(compiler, module_dir);

  int32_t compile_error_code = SPVM_API_COMPILER_compile_spvm(compiler, class_name);
  
  if (compile_error_code != 0) {
    int32_t error_messages_length = SPVM_API_COMPILER_get_error_messages_length(compiler);
    for (int32_t i = 0; i < error_messages_length; i++) {
      const char* error_message = SPVM_API_COMPILER_get_error_message(compiler, i);
      fprintf(stderr, "%s\n", error_message);
    }
    exit(255);
  }

  // Build runtime information
  void* runtime = SPVM_API_runtime_new(env);
  SPVM_API_COMPILER_build_runtime(compiler, runtime);
  
  SPVM_API_COMPILER_free(compiler);
  
  // Prepare runtime
  SPVM_API_runtime_prepare(runtime);

  // Set runtime information
  env->runtime = runtime;
  
  // Initialize env
  env->init_env(env);
  
  // Call INIT blocks
  env->call_init_blocks(env);
  
  return env;
}
