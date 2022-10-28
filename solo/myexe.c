#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>

#include "spvm_native.h"

int32_t main(int32_t command_args_length, const char *command_args[]) {
  
  // Binary mode in all systems
#ifdef _WIN32
  _setmode(stdout, _O_BINARY);
  _setmode(stderr, _O_BINARY);
  _setmode(stdin, _O_BINARY);
#endif
  
  SPVM_ENV* env = SPVM_NATIVE_new_env_prepared();
  
  // Class name
  const char* class_name = "MyExe";
  
  // Class
  int32_t method_id = env->get_class_method_id(env, class_name, "main");
  
  if (method_id < 0) {
    fprintf(stderr, "The class method %s->main is not defined\n", class_name);
    return -1;
  }
  
  SPVM_VALUE* stack = env->new_stack(env);

  // Enter scope
  int32_t scope_id = env->enter_scope(env, stack);
  
  // Program name - string
  void* obj_program_name = env->new_string(env, stack, command_args[0], strlen(command_args[0]));
  
  // ARGV - string[]
  void* obj_argv = env->new_object_array(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_STRING, command_args_length - 1);
  for (int32_t arg_index = 1; arg_index < command_args_length; arg_index++) {
    void* obj_arg = env->new_string(env, stack, command_args[arg_index], strlen(command_args[arg_index]));
    env->set_elem_object(env, stack, obj_argv, arg_index - 1, obj_arg);
  }
  
  int32_t args_stack_length = 2;
  stack[0].oval = obj_program_name;
  stack[1].oval = obj_argv;

  // Call INIT blocks
  env->call_init_blocks(env, stack);
  
  // Set command info
  {
    int32_t e;
    e = env->set_command_info_program_name(env, stack, obj_program_name);
    assert(e == 0);
    e = env->set_command_info_argv(env, stack, obj_argv);
    assert(e == 0);
  }
  
  // Run
  int32_t error = env->call_spvm_method(env, stack, method_id, args_stack_length);

  int32_t status;
  if (error) {
    env->print_stderr(env, stack, env->get_exception(env, stack));
    printf("\n");
    status = 255;
  }
  else {
    status = stack[0].ival;
  }

  // Leave scope
  env->leave_scope(env, stack, scope_id);

  env->cleanup_global_vars(env, stack);
  
  env->free_stack(env, stack);
  
  env->free_env_prepared(env);
  
  return status;
}

SPVM_ENV* SPVM_NATIVE_new_env_prepared() {
  // Class name
  const char* class_name = "MyExe";

  // Create env
  SPVM_ENV* env = SPVM_NATIVE_new_env_raw();
  
  // Create compiler
  void* compiler = env->api->compiler->new_compiler();
  
  // compiler->debug = 1;
  
  env->api->compiler->set_start_file(compiler, class_name);

  env->api->compiler->set_start_line(compiler, 0);
  
  // Add module directory
  char* module_dir = "solo/SPVM";
  env->api->compiler->add_module_dir(compiler, module_dir);

  int32_t compile_error_code = env->api->compiler->compile_spvm(compiler, class_name);
  
  if (compile_error_code != 0) {
    int32_t error_messages_length = env->api->compiler->get_error_messages_length(compiler);
    for (int32_t i = 0; i < error_messages_length; i++) {
      const char* error_message = env->api->compiler->get_error_message(compiler, i);
      fprintf(stderr, "%s\n", error_message);
    }
    exit(255);
  }

  // New runtime
  void* runtime = env->api->runtime->new_runtime(env);
  
  // Runtime allocator
  void* runtime_allocator = env->api->runtime->get_allocator(runtime);
  
  // Create SPVM 32bit codes
  int32_t* spvm_32bit_codes = env->api->compiler->create_spvm_32bit_codes(compiler, runtime_allocator);
  
  // Free compiler
  env->api->compiler->free_compiler(compiler);
  
  // Build runtime
  env->api->runtime->build(runtime, spvm_32bit_codes);
  
  // Prepare runtime
  env->api->runtime->prepare(runtime);

  // Set runtime information
  env->runtime = runtime;
  
  // Initialize env
  env->init_env(env);
  
  return env;
}
