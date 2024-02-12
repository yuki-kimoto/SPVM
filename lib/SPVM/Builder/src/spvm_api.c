// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <inttypes.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <ctype.h>

#include "spvm_native.h"
#include "spvm_api.h"
#include "spvm_vm.h"
#include "spvm_api_runtime.h"
#include "spvm_api_allocator.h"
#include "spvm_api_string_buffer.h"
#include "spvm_opcode.h"
#include "spvm_strerror.h"
#include "spvm_object.h"
#include "spvm_allocator.h"
#include "spvm_weaken_backref.h"
#include "spvm_hash.h"
#include "spvm_string_buffer.h"
#include "spvm_runtime.h"
#include "spvm_runtime_string.h"
#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_class_var.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime_method.h"
#include "spvm_implement.h"
#include "spvm_api_string_buffer.h"
#include "spvm_api_compiler.h"
#include "spvm_api_runtime.h"
#include "spvm_api_class_file.h"
#include "spvm_api_basic_type.h"
#include "spvm_api_class_var.h"
#include "spvm_api_field.h"
#include "spvm_api_method.h"
#include "spvm_api_arg.h"
#include "spvm_api_type.h"
#include "spvm_api_internal.h"
#include "spvm_api_mutex.h"
#include "spvm_mutex.h"

static const char* FILE_NAME = "spvm_api.c";

SPVM_ENV* SPVM_NATIVE_new_env(void) {
  return SPVM_API_new_env();
}

SPVM_ENV* SPVM_API_new_env(void) {

  SPVM_API_ALLOCATOR* api_allocator = SPVM_API_ALLOCATOR_new_api();
  
  SPVM_API_STRING_BUFFER* api_string_buffer = SPVM_API_STRING_BUFFER_new_api();
  
  SPVM_API_COMPILER* api_compiler = SPVM_API_COMPILER_new_api();
  
  SPVM_API_RUNTIME* api_runtime = SPVM_API_RUNTIME_new_api();
  
  SPVM_API_CLASS_FILE* api_class_file = SPVM_API_CLASS_FILE_new_api();
  
  SPVM_API_BASIC_TYPE* api_basic_type = SPVM_API_BASIC_TYPE_new_api();
  
  SPVM_API_CLASS_VAR* api_class_var = SPVM_API_CLASS_VAR_new_api();
  
  SPVM_API_FIELD* api_field = SPVM_API_FIELD_new_api();
  
  SPVM_API_TYPE* api_type = SPVM_API_TYPE_new_api();
  
  SPVM_API_METHOD* api_method = SPVM_API_METHOD_new_api();
  
  SPVM_API_ARG* api_arg = SPVM_API_ARG_new_api();
  
  SPVM_API_INTERNAL* api_internal = SPVM_API_INTERNAL_new_api();
  
  SPVM_API_MUTEX* api_mutex = SPVM_API_MUTEX_new_api();
  
  void* env_api_init[]  = {
    api_allocator,
    api_string_buffer,
    api_compiler,
    api_class_file,
    api_runtime,
    api_basic_type,
    api_class_var,
    api_field,
    api_method,
    api_arg,
    api_type,
    api_internal,
    api_mutex,
  };
  SPVM_ENV_API* env_api = calloc(1, sizeof(env_api_init));
  memcpy(env_api, env_api_init, sizeof(env_api_init));




  // Native APIs
  void* env_init[]  = {
    NULL, // runtime
    env_api, // api
    SPVM_API_new_env,
    SPVM_API_free_env,
    SPVM_API_call_init_methods,
    SPVM_API_set_command_info_program_name,
    SPVM_API_set_command_info_argv,
    SPVM_API_set_command_info_base_time,
    SPVM_API_destroy_class_vars,
    SPVM_API_args_width,
    SPVM_API_get_object_basic_type,
    SPVM_API_get_object_basic_type_id,
    SPVM_API_get_object_basic_type_name,
    SPVM_API_get_object_type_dimension,
    SPVM_API_get_basic_type,
    SPVM_API_get_basic_type_by_name,
    SPVM_API_get_basic_type_by_id,
    SPVM_API_get_basic_type_id,
    SPVM_API_get_basic_type_id_by_name,
    SPVM_API_get_class_var,
    SPVM_API_get_class_var_byte,
    SPVM_API_get_class_var_short,
    SPVM_API_get_class_var_int,
    SPVM_API_get_class_var_long,
    SPVM_API_get_class_var_float,
    SPVM_API_get_class_var_double,
    SPVM_API_get_class_var_object,
    SPVM_API_get_class_var_string,
    SPVM_API_set_class_var_byte,
    SPVM_API_set_class_var_short,
    SPVM_API_set_class_var_int,
    SPVM_API_set_class_var_long,
    SPVM_API_set_class_var_float,
    SPVM_API_set_class_var_double,
    SPVM_API_set_class_var_object,
    SPVM_API_set_class_var_string,
    SPVM_API_get_class_var_object_ref,
    SPVM_API_get_class_var_byte_by_name,
    SPVM_API_get_class_var_short_by_name,
    SPVM_API_get_class_var_int_by_name,
    SPVM_API_get_class_var_long_by_name,
    SPVM_API_get_class_var_float_by_name,
    SPVM_API_get_class_var_double_by_name,
    SPVM_API_get_class_var_object_by_name,
    SPVM_API_get_class_var_string_by_name,
    SPVM_API_set_class_var_byte_by_name,
    SPVM_API_set_class_var_short_by_name,
    SPVM_API_set_class_var_int_by_name,
    SPVM_API_set_class_var_long_by_name,
    SPVM_API_set_class_var_float_by_name,
    SPVM_API_set_class_var_double_by_name,
    SPVM_API_set_class_var_object_by_name,
    SPVM_API_set_class_var_string_by_name,
    SPVM_API_get_field,
    SPVM_API_get_field_static,
    SPVM_API_get_field_byte,
    SPVM_API_get_field_short,
    SPVM_API_get_field_int,
    SPVM_API_get_field_long,
    SPVM_API_get_field_float,
    SPVM_API_get_field_double,
    SPVM_API_get_field_object,
    SPVM_API_get_field_string,
    SPVM_API_set_field_byte,
    SPVM_API_set_field_short,
    SPVM_API_set_field_int,
    SPVM_API_set_field_long,
    SPVM_API_set_field_float,
    SPVM_API_set_field_double,
    SPVM_API_set_field_object,
    SPVM_API_set_field_string,
    SPVM_API_get_field_byte_by_name,
    SPVM_API_get_field_short_by_name,
    SPVM_API_get_field_int_by_name,
    SPVM_API_get_field_long_by_name,
    SPVM_API_get_field_float_by_name,
    SPVM_API_get_field_double_by_name,
    SPVM_API_get_field_object_by_name,
    SPVM_API_get_field_string_by_name,
    SPVM_API_set_field_byte_by_name,
    SPVM_API_set_field_short_by_name,
    SPVM_API_set_field_int_by_name,
    SPVM_API_set_field_long_by_name,
    SPVM_API_set_field_float_by_name,
    SPVM_API_set_field_double_by_name,
    SPVM_API_set_field_object_by_name,
    SPVM_API_set_field_string_by_name,
    SPVM_API_get_field_string_chars_by_name,
    SPVM_API_get_method,
    SPVM_API_get_class_method,
    SPVM_API_get_instance_method_static,
    SPVM_API_get_instance_method,
    SPVM_API_call_method_no_mortal,
    SPVM_API_call_method,
    SPVM_API_call_class_method_by_name,
    SPVM_API_call_instance_method_static_by_name,
    SPVM_API_call_instance_method_by_name,
    SPVM_API_new_object_no_mortal,
    SPVM_API_new_object,
    SPVM_API_new_object_by_name,
    SPVM_API_new_pointer_object_no_mortal,
    SPVM_API_new_pointer_object,
    SPVM_API_new_pointer_object_by_name,
    SPVM_API_get_pointer,
    SPVM_API_set_pointer,
    SPVM_API_new_string_nolen_no_mortal,
    SPVM_API_new_string_nolen,
    SPVM_API_new_string_no_mortal,
    SPVM_API_new_string,
    SPVM_API_new_byte_array_no_mortal,
    SPVM_API_new_byte_array,
    SPVM_API_new_short_array_no_mortal,
    SPVM_API_new_short_array,
    SPVM_API_new_int_array_no_mortal,
    SPVM_API_new_int_array,
    SPVM_API_new_long_array_no_mortal,
    SPVM_API_new_long_array,
    SPVM_API_new_float_array_no_mortal,
    SPVM_API_new_float_array,
    SPVM_API_new_double_array_no_mortal,
    SPVM_API_new_double_array,
    SPVM_API_new_object_array_no_mortal,
    SPVM_API_new_object_array,
    SPVM_API_new_object_array_by_name,
    SPVM_API_new_string_array,
    SPVM_API_new_muldim_array_no_mortal,
    SPVM_API_new_muldim_array,
    SPVM_API_new_muldim_array_by_name,
    SPVM_API_new_mulnum_array_no_mortal,
    SPVM_API_new_mulnum_array,
    SPVM_API_new_mulnum_array_by_name,
    SPVM_API_new_array_proto_no_mortal,
    SPVM_API_new_array_proto,
    SPVM_API_length,
    SPVM_API_get_elems_byte,
    SPVM_API_get_elems_short,
    SPVM_API_get_elems_int,
    SPVM_API_get_elems_long,
    SPVM_API_get_elems_float,
    SPVM_API_get_elems_double,
    SPVM_API_get_elem_object,
    SPVM_API_get_elem_string,
    SPVM_API_set_elem_object,
    SPVM_API_set_elem_string,
    SPVM_API_get_chars,
    SPVM_API_get_bool_object_value,
    SPVM_API_concat_no_mortal,
    SPVM_API_concat,
    SPVM_API_shorten,
    SPVM_API_make_read_only,
    SPVM_API_is_read_only,
    SPVM_API_print,
    SPVM_API_print_stderr,
    SPVM_API_dump_no_mortal,
    SPVM_API_dump,
    SPVM_API_dumpc,
    SPVM_API_copy_no_mortal,
    SPVM_API_copy,
    SPVM_API_get_spvm_version_string,
    SPVM_API_get_spvm_version_number,
    SPVM_API_get_version_string,
    SPVM_API_get_version_number,
    SPVM_API_die,
    SPVM_API_get_exception,
    SPVM_API_set_exception,
    SPVM_API_new_stack_trace_no_mortal,
    SPVM_API_new_stack_trace,
    SPVM_API_is_string,
    SPVM_API_is_class,
    SPVM_API_is_pointer_class,
    SPVM_API_is_array,
    SPVM_API_is_object_array,
    SPVM_API_is_numeric_array,
    SPVM_API_is_mulnum_array,
    SPVM_API_isa,
    SPVM_API_isa_by_name,
    SPVM_API_is_type,
    SPVM_API_is_type_by_name,
    SPVM_API_elem_isa,
    SPVM_API_get_elem_size,
    SPVM_API_get_type_name_no_mortal,
    SPVM_API_get_type_name,
    SPVM_API_get_compile_type_name_no_mortal,
    SPVM_API_get_compile_type_name,
    SPVM_API_enter_scope,
    SPVM_API_leave_scope,
    SPVM_API_push_mortal,
    SPVM_API_weaken,
    SPVM_API_isweak,
    SPVM_API_unweaken,
    SPVM_API_strerror_string,
    SPVM_API_strerror_string_nolen,
    SPVM_API_strerror,
    SPVM_API_strerror_nolen,
    NULL, // reserved194,
    NULL, // reserved195,
    SPVM_API_new_stack,
    SPVM_API_free_stack,
    SPVM_API_get_field_object_defined_and_has_pointer_by_name,
    SPVM_API_get_field_object_ref,
    SPVM_API_get_field_object_ref_by_name,
    SPVM_API_check_stack_env,
    SPVM_API_assign_object,
    SPVM_API_new_string_array_no_mortal,
    SPVM_API_new_memory_block,
    SPVM_API_free_memory_block,
    SPVM_API_get_memory_blocks_count,
    SPVM_API_say,
    SPVM_API_warn,
    SPVM_API_spvm_stdin,
    SPVM_API_spvm_stdout,
    SPVM_API_spvm_stderr,
  };
  SPVM_ENV* env = calloc(1, sizeof(env_init));
  if (env == NULL) {
    return NULL;
  }
  memcpy(env, env_init, sizeof(env_init));
  
  return env;
}

void SPVM_API_free_env(SPVM_ENV* env) {

  // Free env api
  SPVM_API_ALLOCATOR_free_api(env->api->allocator);
  SPVM_API_STRING_BUFFER_free_api(env->api->string_buffer);
  SPVM_API_COMPILER_free_api(env->api->compiler);
  SPVM_API_RUNTIME_free_api(env->api->runtime);
  SPVM_API_CLASS_FILE_free_api(env->api->class_file);
  SPVM_API_BASIC_TYPE_free_api(env->api->basic_type);
  SPVM_API_CLASS_VAR_free_api(env->api->class_var);
  SPVM_API_FIELD_free_api(env->api->field);
  SPVM_API_TYPE_free_api(env->api->type);
  SPVM_API_METHOD_free_api(env->api->method);
  SPVM_API_ARG_free_api(env->api->arg);
  SPVM_API_INTERNAL_free_api(env->api->internal);
  
  free(env->api);
  
  // Free env
  free(env);
  env = NULL;
}

int32_t SPVM_API_call_init_methods(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Call INIT blocks
  int32_t basic_types_length = runtime->basic_types_length;
  for (int32_t basic_type_id = 0; basic_type_id < basic_types_length; basic_type_id++) {
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type_by_id(env->runtime, basic_type_id);
    if (basic_type->init_method) {
      SPVM_RUNTIME_METHOD* init_method = SPVM_API_BASIC_TYPE_get_method_by_index(env->runtime, basic_type, basic_type->init_method->index);      
      int32_t args_width = 0;
      error_id = SPVM_API_call_method_no_mortal(env, stack, init_method, args_width);
      if (error_id) { break; }
    }
  }
  
  return error_id;
}

int32_t SPVM_API_set_command_info_program_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* obj_program_name) {
  
  int32_t error_id = 0;
  
  if (!obj_program_name) {
    return SPVM_API_die(env, stack, "The obj_program_name must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  SPVM_RUNTIME_BASIC_TYPE* obj_program_name_basic_type = SPVM_API_get_object_basic_type(env, stack, obj_program_name);
  if (!(obj_program_name_basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_STRING && obj_program_name->type_dimension == 0)) {
    return SPVM_API_die(env, stack, "The obj_program_name must be a string.", __func__, FILE_NAME, __LINE__);
  }
  
  SPVM_API_set_class_var_object_by_name(env, stack, "CommandInfo", "$PROGRAM_NAME", obj_program_name, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM_API_set_command_info_argv(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* obj_argv) {
  
  int32_t error_id = 0;
  
  if (!obj_argv) {
    return SPVM_API_die(env, stack, "The obj_argv must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  SPVM_RUNTIME_BASIC_TYPE* obj_argv_basic_type = SPVM_API_get_object_basic_type(env, stack, obj_argv);
  if (!(obj_argv_basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_STRING && obj_argv->type_dimension == 1)) {
    return SPVM_API_die(env, stack, "The obj_argv must be a string array.", __func__, FILE_NAME, __LINE__);
  }
  
  SPVM_API_set_class_var_object_by_name(env, stack, "CommandInfo", "$ARGV", obj_argv, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM_API_set_command_info_base_time(SPVM_ENV* env, SPVM_VALUE* stack, int64_t base_time) {
  
  int32_t error_id = 0;
  
  SPVM_API_set_class_var_long_by_name(env, stack, "CommandInfo", "$BASE_TIME", base_time, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

void SPVM_API_destroy_class_vars(SPVM_ENV* env, SPVM_VALUE* stack){

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Free objects of class variables
  for (int32_t basic_type_id = 0; basic_type_id < runtime->basic_types_length; basic_type_id++) {
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type_by_id(env->runtime, basic_type_id);
    
    for (int32_t class_var_index = 0; class_var_index < basic_type->class_vars_length; class_var_index++) {
      
      SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_BASIC_TYPE_get_class_var_by_index(runtime, basic_type, class_var_index);
      
      SPVM_RUNTIME_BASIC_TYPE* class_var_basic_type = class_var->basic_type;
      int32_t class_var_type_dimension = class_var->type_dimension;
      int32_t class_var_type_flag = class_var->type_flag;
      
      int32_t class_var_type_is_object = SPVM_API_TYPE_is_object_type(runtime, class_var_basic_type, class_var_type_dimension, class_var_type_flag);
      if (class_var_type_is_object) {
        SPVM_OBJECT** object_ref = (SPVM_OBJECT**)&class_var->data;
        SPVM_API_assign_object(env, stack, object_ref, NULL);
      }
    }
  }
}

int32_t SPVM_API_args_width(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t args_length = stack[SPVM_API_C_STACK_INDEX_ARGS_WIDTH].ival;
  
  return args_length;
}

int32_t SPVM_API_get_basic_type_id(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name) {
  

  SPVM_RUNTIME* runtime = env->runtime;

  if (basic_type_name == NULL) {
    return -1;
  }

  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type_by_name(runtime, basic_type_name);
  if (basic_type) {
    int32_t basic_type_id = basic_type->id;
    return basic_type_id;
  }
  else {
    return -1;
  }
}

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_get_basic_type(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name) {
  

  SPVM_RUNTIME* runtime = env->runtime;

  if (basic_type_name == NULL) {
    return NULL;
  }

  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type_by_name(runtime, basic_type_name);
  
  return basic_type;
}

void SPVM_API_call_class_method_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* method_name, int32_t args_width, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  SPVM_RUNTIME_METHOD* method = SPVM_API_BASIC_TYPE_get_method_by_name(env->runtime, basic_type, method_name);
  if (!method) {
    *error_id = SPVM_API_die(env, stack, "The %s class method in the %s class is not found", method_name, basic_type_name, func_name, file, line);
    return;
  }
  *error_id = SPVM_API_call_method_no_mortal(env, stack, method, args_width);
  if (*error_id) {
    const char* message = SPVM_API_get_chars(env, stack, SPVM_API_get_exception(env, stack));
    SPVM_API_die(env, stack, "%s", message, func_name, file, line);
  }
}

void SPVM_API_call_instance_method_static_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* method_name, int32_t args_width, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  SPVM_RUNTIME_METHOD* method = SPVM_API_BASIC_TYPE_get_method_by_name(env->runtime, basic_type, method_name);
  if (!method) {
    *error_id = SPVM_API_die(env, stack, "The %s instance method in the %s class is not found", method_name, basic_type_name, func_name, file, line);
    return;
  }
  *error_id = SPVM_API_call_method_no_mortal(env, stack, method, args_width);
  if (*error_id) {
    const char* message = SPVM_API_get_chars(env, stack, SPVM_API_get_exception(env, stack));
    SPVM_API_die(env, stack, "%s", message, func_name, file, line);
  }
}

void SPVM_API_call_instance_method_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* method_name, int32_t args_width, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_OBJECT* object = stack[0].oval;
  
  if (object == NULL) {
    *error_id = SPVM_API_die(env, stack, "The object must be defined", func_name, file, line);
    return;
  };
  
  if (object->type_dimension > 0) {
    *error_id = SPVM_API_die(env, stack, "The type dimension of the object must be equal to 0", func_name, file, line);
    return;
  };
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_get_instance_method(env, stack, object, method_name);
  if (!method) {
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    *error_id = SPVM_API_die(env, stack, "The %s instance method is not found in the %s class or its super class", method_name, basic_type_name, func_name, file, line);
    return;
  };
  
  *error_id = SPVM_API_call_method_no_mortal(env, stack, method, args_width);
  
  if (*error_id) {
    const char* message = SPVM_API_get_chars(env, stack, SPVM_API_get_exception(env, stack));
    SPVM_API_die(env, stack, "%s", message, func_name, file, line);
  }
}

void* SPVM_API_new_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  void* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    SPVM_API_die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error_id = 1;
    return NULL;
  };
  
  void* object = SPVM_API_new_object(env, stack, basic_type);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_pointer_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, void* pointer, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  void* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    *error_id = 1;
    SPVM_API_die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    return NULL;
  };
  SPVM_OBJECT* object = SPVM_API_new_pointer_object(env, stack, basic_type, pointer);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_object_array_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t length, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  void* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    SPVM_API_die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error_id = 1;
    return NULL;
  };
  
  void* object = SPVM_API_new_object_array(env, stack, basic_type, length);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_muldim_array_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t type_dimension, int32_t length, int32_t* error_id, const char* func_name, const char* file, int32_t line) {  *error_id = 0;
  
  void* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    SPVM_API_die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error_id = 1;
    return NULL;
  };
  
  void* object = SPVM_API_new_muldim_array(env, stack, basic_type, type_dimension, length);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_mulnum_array_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t length, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  void* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    SPVM_API_die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error_id = 1;
    return NULL;
  };
  
  void* object = SPVM_API_new_mulnum_array(env, stack, basic_type, length);
  
  return object;
}

int8_t SPVM_API_get_class_var_byte(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var) {
  
  assert(class_var);
  
  int8_t value = class_var->data.bval;
  
  return value;
}

int16_t SPVM_API_get_class_var_short(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var) {
  
  assert(class_var);
  
  int16_t value = class_var->data.sval;
  
  return value;
}

int32_t SPVM_API_get_class_var_int(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var) {
  
  assert(class_var);
  
  int32_t value = class_var->data.ival;
  
  return value;
}

int64_t SPVM_API_get_class_var_long(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var) {
  
  assert(class_var);
  
  int64_t value = class_var->data.lval;
  
  return value;
}

float SPVM_API_get_class_var_float(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var) {
  
  assert(class_var);
  
  float value = class_var->data.fval;
 
  return value;
}

double SPVM_API_get_class_var_double(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var) {
  
  assert(class_var);
  
  double value = class_var->data.dval;
  
  return value;
}

SPVM_OBJECT* SPVM_API_get_class_var_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var) {
  
  assert(class_var);
  
  SPVM_OBJECT* value_maybe_weaken = (SPVM_OBJECT*)class_var->data.oval;
  SPVM_OBJECT* value = SPVM_API_get_object_no_weaken_address(env, stack, value_maybe_weaken);
  
  return value;
}

SPVM_OBJECT** SPVM_API_get_class_var_object_ref(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var) {
  
  assert(class_var);
  
  SPVM_OBJECT** object_ref = (SPVM_OBJECT**)&class_var->data.oval;
  
  return object_ref;
}

SPVM_OBJECT* SPVM_API_get_class_var_string(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var) {
  
  return SPVM_API_get_class_var_object(env, stack, class_var);
}

void SPVM_API_set_class_var_byte(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var, int8_t value) {
  
  assert(class_var);
  
  class_var->data.bval = value;
}

void SPVM_API_set_class_var_short(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var, int16_t value) {
  
  assert(class_var);
  
  class_var->data.sval = value;
}

void SPVM_API_set_class_var_int(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var, int32_t value) {
  
  assert(class_var);
  
  class_var->data.ival = value;
}

void SPVM_API_set_class_var_long(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var, int64_t value) {
  
  assert(class_var);
  
  class_var->data.lval = value;
}

void SPVM_API_set_class_var_float(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var, float value) {
  
  assert(class_var);
  
  class_var->data.fval = value;
}

void SPVM_API_set_class_var_double(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var, double value) {
  
  assert(class_var);
  
  class_var->data.dval = value;
}

void SPVM_API_set_class_var_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var, SPVM_OBJECT* value) {
  
  assert(class_var);
  
  void* object_ref = &class_var->data.oval;
  SPVM_API_assign_object(env, stack, object_ref, value);
}

void SPVM_API_set_class_var_string(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var, SPVM_OBJECT* value) {
  
  assert(class_var);
  
  SPVM_API_set_class_var_object(env, stack, class_var, value);
}

int8_t SPVM_API_get_class_var_byte_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    SPVM_API_die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error_id = 1;
    return 0;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_BASIC_TYPE_get_class_var_by_name(env->runtime, basic_type, class_var_name);
  if (!class_var) {
    *error_id = 1;
    SPVM_API_die(env, stack, "The %s class variable in the %s class is not found", class_var_name, basic_type_name, func_name, file, line);
    return 0;
  };
  
  int8_t value = SPVM_API_get_class_var_byte(env, stack, class_var);
  return value;
}

int16_t SPVM_API_get_class_var_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    SPVM_API_die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error_id = 1;
    return 0;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_BASIC_TYPE_get_class_var_by_name(env->runtime, basic_type, class_var_name);
  if (!class_var) {
    *error_id = 1;
    SPVM_API_die(env, stack, "The %s class variable in the %s class is not found", class_var_name, basic_type_name, func_name, file, line);
    return 0;
  };
  
  int16_t value = SPVM_API_get_class_var_short(env, stack, class_var);
  return value;
}

int32_t SPVM_API_get_class_var_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    SPVM_API_die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error_id = 1;
    return 0;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_BASIC_TYPE_get_class_var_by_name(env->runtime, basic_type, class_var_name);
  if (!class_var) {
    *error_id = 1;
    SPVM_API_die(env, stack, "The %s class variable in the %s class is not found", class_var_name, basic_type_name, func_name, file, line);
    return 0;
  };
  
  int32_t value = SPVM_API_get_class_var_int(env, stack, class_var);
  return value;
}

int64_t SPVM_API_get_class_var_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    SPVM_API_die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error_id = 1;
    return 0;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_BASIC_TYPE_get_class_var_by_name(env->runtime, basic_type, class_var_name);
  if (!class_var) {
    *error_id = 1;
    SPVM_API_die(env, stack, "The %s class variable in the %s class is not found", class_var_name, basic_type_name, func_name, file, line);
    return 0;
  };
  
  int64_t value = SPVM_API_get_class_var_long(env, stack, class_var);
  return value;
}

float SPVM_API_get_class_var_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    SPVM_API_die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error_id = 1;
    return 0;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_BASIC_TYPE_get_class_var_by_name(env->runtime, basic_type, class_var_name);
  if (!class_var) {
    *error_id = 1;
    SPVM_API_die(env, stack, "The %s class variable in the %s class is not found", class_var_name, basic_type_name, func_name, file, line);
    return 0;
  };
  
  float value = SPVM_API_get_class_var_float(env, stack, class_var);
  return value;
}

double SPVM_API_get_class_var_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    SPVM_API_die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error_id = 1;
    return 0;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_BASIC_TYPE_get_class_var_by_name(env->runtime, basic_type, class_var_name);
  if (!class_var) {
    *error_id = 1;
    SPVM_API_die(env, stack, "The %s class variable in the %s class is not found", class_var_name, basic_type_name, func_name, file, line);
    return 0;
  };
  
  double value = SPVM_API_get_class_var_double(env, stack, class_var);
  return value;
}

SPVM_OBJECT* SPVM_API_get_class_var_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    SPVM_API_die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error_id = 1;
    return 0;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_BASIC_TYPE_get_class_var_by_name(env->runtime, basic_type, class_var_name);
  if (!class_var) {
    *error_id = 1;
    SPVM_API_die(env, stack, "The %s class variable in the %s class is not found", class_var_name, basic_type_name, func_name, file, line);
    return 0;
  };
  
  SPVM_OBJECT* value = SPVM_API_get_class_var_object(env, stack, class_var);
  return value;
}

SPVM_OBJECT* SPVM_API_get_class_var_string_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  return SPVM_API_get_class_var_object_by_name(env, stack, basic_type_name, class_var_name, error_id, func_name, file, line);
}

void SPVM_API_set_class_var_byte_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int8_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    SPVM_API_die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error_id = 1;
    return;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_BASIC_TYPE_get_class_var_by_name(env->runtime, basic_type, class_var_name);
  if (!class_var) {
    *error_id = 1;
    SPVM_API_die(env, stack, "The %s class variable in the %s class is not found", class_var_name, basic_type_name, func_name, file, line);
    return;
  };
  
  SPVM_API_set_class_var_byte(env, stack, class_var, value);
}

void SPVM_API_set_class_var_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int16_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    SPVM_API_die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error_id = 1;
    return;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_BASIC_TYPE_get_class_var_by_name(env->runtime, basic_type, class_var_name);
  if (!class_var) {
    *error_id = 1;
    SPVM_API_die(env, stack, "The %s class variable in the %s class is not found", class_var_name, basic_type_name, func_name, file, line);
    return;
  };
  
  SPVM_API_set_class_var_short(env, stack, class_var, value);
}

void SPVM_API_set_class_var_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    SPVM_API_die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error_id = 1;
    return;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_BASIC_TYPE_get_class_var_by_name(env->runtime, basic_type, class_var_name);
  if (!class_var) {
    *error_id = 1;
    SPVM_API_die(env, stack, "The %s class variable in the %s class is not found", class_var_name, basic_type_name, func_name, file, line);
    return;
  };
  
  SPVM_API_set_class_var_int(env, stack, class_var, value);
}

void SPVM_API_set_class_var_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int64_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    SPVM_API_die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error_id = 1;
    return;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_BASIC_TYPE_get_class_var_by_name(env->runtime, basic_type, class_var_name);
  if (!class_var) {
    *error_id = 1;
    SPVM_API_die(env, stack, "The %s class variable in the %s class is not found", class_var_name, basic_type_name, func_name, file, line);
    return;
  };
  
  SPVM_API_set_class_var_long(env, stack, class_var, value);
}

void SPVM_API_set_class_var_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, float value, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    SPVM_API_die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error_id = 1;
    return;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_BASIC_TYPE_get_class_var_by_name(env->runtime, basic_type, class_var_name);
  if (!class_var) {
    *error_id = 1;
    SPVM_API_die(env, stack, "The %s class variable in the %s class is not found", class_var_name, basic_type_name, func_name, file, line);
    return;
  };
  
  SPVM_API_set_class_var_float(env, stack, class_var, value);
}

void SPVM_API_set_class_var_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, double value, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    SPVM_API_die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error_id = 1;
    return;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_BASIC_TYPE_get_class_var_by_name(env->runtime, basic_type, class_var_name);
  if (!class_var) {
    *error_id = 1;
    SPVM_API_die(env, stack, "The %s class variable in the %s class is not found", class_var_name, basic_type_name, func_name, file, line);
    return;
  };
  
  SPVM_API_set_class_var_double(env, stack, class_var, value);
}

void SPVM_API_set_class_var_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, SPVM_OBJECT* value, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    SPVM_API_die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error_id = 1;
    return;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_BASIC_TYPE_get_class_var_by_name(env->runtime, basic_type, class_var_name);
  if (!class_var) {
    *error_id = 1;
    SPVM_API_die(env, stack, "The %s class variable in the %s class is not found", class_var_name, basic_type_name, func_name, file, line);
    return;
  };
  
  SPVM_API_set_class_var_object(env, stack, class_var, value);
}

void SPVM_API_set_class_var_string_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, SPVM_OBJECT* value, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  SPVM_API_set_class_var_object_by_name(env, stack, basic_type_name, class_var_name, value, error_id, func_name, file, line);
}

int8_t SPVM_API_get_field_byte(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field) {

  int8_t value = *(int8_t*)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + field->offset);

  return value;
}

int16_t SPVM_API_get_field_short(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field) {

  int16_t value = *(int16_t*)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + field->offset);
  
  return value;
}

int32_t SPVM_API_get_field_int(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field) {

  int32_t value = *(int32_t*)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + field->offset);
  
  return value;
}

int64_t SPVM_API_get_field_long(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field) {

  int64_t value = *(int64_t*)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + field->offset);
  
  return value;
}

float SPVM_API_get_field_float(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field) {

  float value = *(float*)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + field->offset);
  
  return value;
}

double SPVM_API_get_field_double(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field) {

  double value = *(double*)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + field->offset);
  
  return value;
}

SPVM_OBJECT* SPVM_API_get_field_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field) {

  SPVM_OBJECT* value_maybe_weaken = *(SPVM_OBJECT**)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + field->offset);
  SPVM_OBJECT* value = SPVM_API_get_object_no_weaken_address(env, stack, value_maybe_weaken);
  
  return value;
}

SPVM_OBJECT** SPVM_API_get_field_object_ref(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field) {

  SPVM_OBJECT** object_ref = (SPVM_OBJECT**)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + field->offset);
  
  return object_ref;
}

SPVM_OBJECT* SPVM_API_get_field_string(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field) {
  
  SPVM_OBJECT* value = SPVM_API_get_field_object(env, stack, object, field);
  
  return value;
}

void SPVM_API_set_field_byte(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field, int8_t value) {

  // Get field value
  *(int8_t*)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + field->offset) = value;
}

void SPVM_API_set_field_short(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field, int16_t value) {

  // Get field value
  *(int16_t*)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + field->offset) = value;
}

void SPVM_API_set_field_int(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field, int32_t value) {

  // Get field value
  *(int32_t*)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + field->offset) = value;
}

void SPVM_API_set_field_long(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field, int64_t value) {

  // Get field value
  *(int64_t*)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + field->offset) = value;
}

void SPVM_API_set_field_float(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field, float value) {

  // Get field value
  *(float*)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + field->offset) = value;
}

void SPVM_API_set_field_double(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field, double value) {

  // Get field value
  *(double*)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + field->offset) = value;
}

void SPVM_API_set_field_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field, SPVM_OBJECT* value) {

  // Get field value
  void* object_ref = (void**)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + field->offset);

  SPVM_API_assign_object(env, stack, object_ref, value);
}

void SPVM_API_set_field_string(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field, SPVM_OBJECT* value) {
  
  SPVM_API_set_field_object(env, stack, object, field, value);
}

int8_t SPVM_API_get_field_byte_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  if (object == NULL) {
    SPVM_API_die(env, stack, "The object must be defined", func_name, file, line);
    return 0;
  };
  
  if (object->type_dimension > 0) {
    SPVM_API_die(env, stack, "The type dimension of the object must be equal to 0", func_name, file, line);
    return 0;
  };
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  if (!field) {
    *error_id = 1;
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    SPVM_API_die(env, stack, "The %s field is not found in the %s class or its super class", field_name, basic_type_name, func_name, file, line);
    return 0;
  };
  int8_t value = SPVM_API_get_field_byte(env, stack, object, field);
  return value;
}

int16_t SPVM_API_get_field_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  if (object == NULL) {
    SPVM_API_die(env, stack, "The object must be defined", func_name, file, line);
    return 0;
  };
  
  if (object->type_dimension > 0) {
    SPVM_API_die(env, stack, "The type dimension of the object must be equal to 0", func_name, file, line);
    return 0;
  };
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  if (!field) {
    *error_id = 1;
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    SPVM_API_die(env, stack, "The %s field is not found in the %s class or its super class", field_name, basic_type_name, func_name, file, line);
    return 0;
  };
  int16_t value = SPVM_API_get_field_short(env, stack, object, field);
  return value;
}

int32_t SPVM_API_get_field_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  if (object == NULL) {
    SPVM_API_die(env, stack, "The object must be defined", func_name, file, line);
    return 0;
  };
  
  if (object->type_dimension > 0) {
    SPVM_API_die(env, stack, "The type dimension of the object must be equal to 0", func_name, file, line);
    return 0;
  };
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  if (!field) {
    *error_id = 1;
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    SPVM_API_die(env, stack, "The %s field is not found in the %s class or its super class", field_name, basic_type_name, func_name, file, line);
    return 0;
  };
  int32_t value = SPVM_API_get_field_int(env, stack, object, field);
  return value;
}

int64_t SPVM_API_get_field_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  if (object == NULL) {
    SPVM_API_die(env, stack, "The object must be defined", func_name, file, line);
    return 0;
  };
  
  if (object->type_dimension > 0) {
    SPVM_API_die(env, stack, "The type dimension of the object must be equal to 0", func_name, file, line);
    return 0;
  };
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  if (!field) {
    *error_id = 1;
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    SPVM_API_die(env, stack, "The %s field is not found in the %s class or its super class", field_name, basic_type_name, func_name, file, line);
    return 0;
  };
  int64_t value = SPVM_API_get_field_long(env, stack, object, field);
  return value;
}

float SPVM_API_get_field_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  if (object == NULL) {
    SPVM_API_die(env, stack, "The object must be defined", func_name, file, line);
    return 0;
  };
  
  if (object->type_dimension > 0) {
    SPVM_API_die(env, stack, "The type dimension of the object must be equal to 0", func_name, file, line);
    return 0;
  };
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  if (!field) {
    *error_id = 1;
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    SPVM_API_die(env, stack, "The %s field is not found in the %s class or its super class", field_name, basic_type_name, func_name, file, line);
    return 0;
  };
  float value = SPVM_API_get_field_float(env, stack, object, field);
  return value;
}

double SPVM_API_get_field_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  if (object == NULL) {
    SPVM_API_die(env, stack, "The object must be defined", func_name, file, line);
    return 0;
  };
  
  if (object->type_dimension > 0) {
    SPVM_API_die(env, stack, "The type dimension of the object must be equal to 0", func_name, file, line);
    return 0;
  };
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  if (!field) {
    *error_id = 1;
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    SPVM_API_die(env, stack, "The %s field is not found in the %s class or its super class", field_name, basic_type_name, func_name, file, line);
    return 0;
  };
  double value = SPVM_API_get_field_double(env, stack, object, field);
  return value;
}

SPVM_OBJECT* SPVM_API_get_field_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  if (object == NULL) {
    SPVM_API_die(env, stack, "The object must be defined", func_name, file, line);
    return NULL;
  };
  
  if (object->type_dimension > 0) {
    SPVM_API_die(env, stack, "The type dimension of the object must be equal to 0", func_name, file, line);
    return NULL;
  };
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  if (!field) {
    *error_id = 1;
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    SPVM_API_die(env, stack, "The %s field is not found in the %s class or its super class", field_name, basic_type_name, func_name, file, line);
    return NULL;
  };
  SPVM_OBJECT* value = SPVM_API_get_field_object(env, stack, object, field);
  return value;
}

SPVM_OBJECT** SPVM_API_get_field_object_ref_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  if (object == NULL) {
    SPVM_API_die(env, stack, "The object must be defined", func_name, file, line);
    return NULL;
  };
  
  if (object->type_dimension > 0) {
    SPVM_API_die(env, stack, "The type dimension of the object must be equal to 0", func_name, file, line);
    return NULL;
  };
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  if (!field) {
    *error_id = 1;
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    SPVM_API_die(env, stack, "The %s field is not found in the %s class or its super class", field_name, basic_type_name, func_name, file, line);
    return NULL;
  };
  SPVM_OBJECT** object_ref = SPVM_API_get_field_object_ref(env, stack, object, field);
  return object_ref;
}

SPVM_OBJECT* SPVM_API_get_field_object_defined_and_has_pointer_by_name(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file_name, int32_t line) {
  
  *error_id = 0;
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, object, field_name, error_id, func_name, file_name, line);
  
  if (*error_id) { return NULL; }
  
  if (!obj_runtime) {
    *error_id = env->die(env, stack, "The %s field must be defined.", field_name, func_name, file_name, line);
    return NULL;
  }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  if (!runtime) {
    *error_id = env->die(env, stack, "The pointer of the %s field must be defined.", field_name, func_name, file_name, line);
    return NULL;
  }
  
  return obj_runtime;
}

SPVM_OBJECT* SPVM_API_get_field_string_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  return SPVM_API_get_field_object_by_name(env, stack, object, field_name, error_id, func_name, file, line);
}

const char* SPVM_API_get_field_string_chars_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  if (!field) {
    *error_id = 1;
    SPVM_API_die(env, stack, "The %s field is not found", field_name, func_name, file, line);
    return NULL;
  };
  SPVM_OBJECT* value = SPVM_API_get_field_string(env, stack, object, field);
  if (value == NULL) {
    return NULL;
  }
  else {
    const char* chars = SPVM_API_get_chars(env, stack, value);
    return chars;
  }
}

void SPVM_API_set_field_byte_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int8_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  if (object == NULL) {
    SPVM_API_die(env, stack, "The object must be defined", func_name, file, line);
    return;
  };
  
  if (object->type_dimension > 0) {
    SPVM_API_die(env, stack, "The type dimension of the object must be equal to 0", func_name, file, line);
    return;
  };
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  if (!field) {
    *error_id = 1;
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    SPVM_API_die(env, stack, "The %s field is not found in the %s class or its super class", field_name, basic_type_name, func_name, file, line);
    return;
  }
  SPVM_API_set_field_byte(env, stack, object, field, value);
}

void SPVM_API_set_field_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int16_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  if (object == NULL) {
    SPVM_API_die(env, stack, "The object must be defined", func_name, file, line);
    return;
  };
  
  if (object->type_dimension > 0) {
    SPVM_API_die(env, stack, "The type dimension of the object must be equal to 0", func_name, file, line);
    return;
  };
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  if (!field) {
    *error_id = 1;
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    SPVM_API_die(env, stack, "The %s field is not found in the %s class or its super class", field_name, basic_type_name, func_name, file, line);
    return;
  };
  SPVM_API_set_field_short(env, stack, object, field, value);
}

void SPVM_API_set_field_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  if (object == NULL) {
    SPVM_API_die(env, stack, "The object must be defined", func_name, file, line);
    return;
  };
  
  if (object->type_dimension > 0) {
    SPVM_API_die(env, stack, "The type dimension of the object must be equal to 0", func_name, file, line);
    return;
  };
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  if (!field) {
    *error_id = 1;
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    SPVM_API_die(env, stack, "The %s field is not found in the %s class or its super class", field_name, basic_type_name, func_name, file, line);
    return;
  };
  SPVM_API_set_field_int(env, stack, object, field, value);
}

void SPVM_API_set_field_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int64_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  if (object == NULL) {
    SPVM_API_die(env, stack, "The object must be defined", func_name, file, line);
    return;
  };
  
  if (object->type_dimension > 0) {
    SPVM_API_die(env, stack, "The type dimension of the object must be equal to 0", func_name, file, line);
    return;
  };
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  if (!field) {
    *error_id = 1;
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    SPVM_API_die(env, stack, "The %s field is not found in the %s class or its super class", field_name, basic_type_name, func_name, file, line);
    return;
  };
  SPVM_API_set_field_long(env, stack, object, field, value);
}

void SPVM_API_set_field_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, float value, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  if (object == NULL) {
    SPVM_API_die(env, stack, "The object must be defined", func_name, file, line);
    return;
  };
  
  if (object->type_dimension > 0) {
    SPVM_API_die(env, stack, "The type dimension of the object must be equal to 0", func_name, file, line);
    return;
  };
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  if (!field) {
    *error_id = 1;
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    SPVM_API_die(env, stack, "The %s field is not found in the %s class or its super class", field_name, basic_type_name, func_name, file, line);
    return;
  };
  SPVM_API_set_field_float(env, stack, object, field, value);
}

void SPVM_API_set_field_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, double value, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  if (object == NULL) {
    SPVM_API_die(env, stack, "The object must be defined", func_name, file, line);
    return;
  };
  
  if (object->type_dimension > 0) {
    SPVM_API_die(env, stack, "The type dimension of the object must be equal to 0", func_name, file, line);
    return;
  };
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  if (!field) {
    *error_id = 1;
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    SPVM_API_die(env, stack, "The %s field is not found in the %s class or its super class", field_name, basic_type_name, func_name, file, line);
    return;
  };
  SPVM_API_set_field_double(env, stack, object, field, value);
}

void SPVM_API_set_field_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, SPVM_OBJECT* value, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  if (object == NULL) {
    SPVM_API_die(env, stack, "The object must be defined", func_name, file, line);
    return;
  };
  
  if (object->type_dimension > 0) {
    SPVM_API_die(env, stack, "The type dimension of the object must be equal to 0", func_name, file, line);
    return;
  };
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  if (!field) {
    *error_id = 1;
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    SPVM_API_die(env, stack, "The %s field is not found in the %s class or its super class", field_name, basic_type_name, func_name, file, line);
    return;
  };
  SPVM_API_set_field_object(env, stack, object, field, value);
}

void SPVM_API_set_field_string_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, SPVM_OBJECT* value, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  SPVM_API_set_field_object_by_name(env, stack, object, field_name, value, error_id, func_name, file, line);
}

int32_t SPVM_API_die(SPVM_ENV* env, SPVM_VALUE* stack, const char* message, ...) {
  
  va_list args;
  
  char* message_with_line = (char*)SPVM_API_new_memory_block(env, stack, 512);
  int32_t message_length = strlen(message);
  if (message_length > 255) {
    message_length = 255;
  }
  memcpy(message_with_line, message, message_length);
  const char* place = "\n    %s at %s line %d";
  memcpy(message_with_line + message_length, place, strlen(place));

  char* buffer = (char*)SPVM_API_new_memory_block(env, stack, 512);
  va_start(args, message);
  vsnprintf(buffer, 511, message_with_line, args);
  va_end(args);
  
  void* exception = SPVM_API_new_string_no_mortal(env, stack, buffer, strlen(buffer));
  
  SPVM_API_free_memory_block(env, stack, message_with_line);
  message_with_line = NULL;
  
  SPVM_API_free_memory_block(env, stack, buffer);
  buffer = NULL;
  
  SPVM_API_set_exception(env, stack, exception);
  
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
}

SPVM_VALUE* SPVM_API_new_stack(SPVM_ENV* env) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Arguments and return values : 0-255
  // Stack local varialbe : 256-511
  //   Exception message 511
  //   Mortal stack 510
  //   Motal stack top 509
  //   Motal stack capacity 508
  
  SPVM_VALUE* stack = env->new_memory_block(env, NULL, sizeof(SPVM_VALUE) * 512);
  
  int32_t native_mortal_stack_capacity = 1;
  void* native_mortal_stack = SPVM_API_new_memory_block(env, stack, sizeof(SPVM_OBJECT*) * native_mortal_stack_capacity);
  if (native_mortal_stack == NULL) {
    return NULL;
  }
  stack[SPVM_API_C_STACK_INDEX_MORTAL_STACK_CAPACITY].ival = native_mortal_stack_capacity;
  stack[SPVM_API_C_STACK_INDEX_MORTAL_STACK].oval = native_mortal_stack;
  stack[SPVM_API_C_STACK_INDEX_ENV].oval = env;
  
  return stack;
}

void SPVM_API_free_stack(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_API_set_exception(env, stack, NULL);
  
  SPVM_OBJECT** mortal_stack = stack[SPVM_API_C_STACK_INDEX_MORTAL_STACK].oval;
  
  if (mortal_stack != NULL) {
    SPVM_API_free_memory_block(env, stack, mortal_stack);
    mortal_stack = NULL;
  }
  
  env->free_memory_block(env, stack, stack);
  stack = NULL;
}

int32_t SPVM_API_call_method_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_METHOD* method, int32_t args_width) {
  
  int32_t mortal = 0;
  int32_t error_id = SPVM_API_call_method_common(env, stack, method, args_width, mortal);
  
  return error_id;
}

int32_t SPVM_API_call_method(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_METHOD* method, int32_t args_width) {
  
  int32_t mortal = 1;
  int32_t error_id = SPVM_API_call_method_common(env, stack, method, args_width, mortal);
  
  return error_id;
}

int32_t SPVM_API_is_array(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  int32_t is_array;
  if (object) {
    is_array = object->type_dimension > 0;
  }
  else {
    is_array = 0;
  }
  
  return is_array;
}

int32_t SPVM_API_is_string(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  int32_t is_string;
  if (object) {
    SPVM_RUNTIME_BASIC_TYPE* object_basic_type = SPVM_API_get_object_basic_type(env, stack, object);
    is_string = (object_basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_STRING && object->type_dimension == 0);
  }
  else {
    is_string = 0;
  }
  
  return is_string;
}

int32_t SPVM_API_is_numeric_array(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {

  SPVM_RUNTIME* runtime = env->runtime;
  
  int32_t is_numeric_array;
  if (object) {
    int32_t object_type_dimension = object->type_dimension;
    if (object_type_dimension == 0) {
      is_numeric_array = 0;
    }
    else if (object_type_dimension == 1) {
      SPVM_RUNTIME_BASIC_TYPE* object_basic_type = SPVM_API_get_object_basic_type(env, stack, object);
      int32_t object_basic_type_category = object_basic_type->category;
      switch (object_basic_type_category) {
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC:
        {
          is_numeric_array = 1;
          break;
        }
        default: {
          is_numeric_array = 0;
        }
      }
    }
    else if (object_type_dimension > 1) {
      is_numeric_array = 0;
    }
    else {
      assert(0);
    }
  }
  else {
    is_numeric_array = 0;
  }

  return is_numeric_array;
}


int32_t SPVM_API_is_object_array(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  SPVM_RUNTIME* runtime = env->runtime;

  int32_t is_object_array;
  if (object) {
    int32_t object_type_dimension = object->type_dimension;
    if (object_type_dimension == 0) {
      is_object_array = 0;
    }
    else if (object_type_dimension == 1) {
      SPVM_RUNTIME_BASIC_TYPE* object_basic_type = SPVM_API_get_object_basic_type(env, stack, object);
      int32_t element_type_dimension = 0;
      int32_t type_flag = 0;
      is_object_array = SPVM_API_TYPE_is_object_type(env->runtime, object_basic_type, element_type_dimension, type_flag);
    }
    else if (object_type_dimension > 1) {
      is_object_array = 1;
    }
    else {
      assert(0);
    }
  }
  else {
    is_object_array = 0;
  }
  
  return is_object_array;
}

int32_t SPVM_API_is_mulnum_array(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {

  SPVM_RUNTIME* runtime = env->runtime;

  int32_t is_mulnum_array;
  if (object) {
    int32_t object_type_dimension = object->type_dimension;
    if (object_type_dimension == 0) {
      is_mulnum_array = 0;
    }
    else if (object_type_dimension == 1) {
      SPVM_RUNTIME_BASIC_TYPE* object_basic_type = SPVM_API_get_object_basic_type(env, stack, object);
      int32_t object_basic_type_category = object_basic_type->category;
      switch (object_basic_type_category) {
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM:
        {
          is_mulnum_array = 1;
          break;
        }
        default: {
          is_mulnum_array = 0;
        }
      }
    }
    else if (object_type_dimension > 1) {
      is_mulnum_array = 0;
    }
    else {
      assert(0);
    }
  }
  else {
    is_mulnum_array = 0;
  }

  return is_mulnum_array;
}

int32_t SPVM_API_is_class(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  SPVM_RUNTIME* runtime = env->runtime;

  int32_t is_class;
  if (object) {
    int32_t object_type_dimension = object->type_dimension;
    if (object_type_dimension == 0) {
      SPVM_RUNTIME_BASIC_TYPE* object_basic_type = SPVM_API_get_object_basic_type(env, stack, object);
      int32_t object_basic_type_category = object_basic_type->category;
      
      switch (object_basic_type_category) {
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS: {
          is_class = 1;
          break;
        }
        default: {
          is_class = 0;
        }
      }
    }
    else {
      is_class = 0;
    }
  }
  else {
    is_class = 0;
  }
  
  return is_class;
}

int32_t SPVM_API_is_pointer_class(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  int32_t is_pointer_class;
  if (object) {
    int32_t object_type_dimension = object->type_dimension;
    if (object_type_dimension == 0) {
      SPVM_RUNTIME_BASIC_TYPE* object_basic_type = SPVM_API_get_object_basic_type(env, stack, object);
      int32_t object_basic_type_category = object_basic_type->category;
      
      switch (object_basic_type_category) {
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS: {
          int32_t basic_type_is_pointer = object_basic_type->is_pointer;
          
          if (basic_type_is_pointer) {
            is_pointer_class = 1;
          }
          else {
            is_pointer_class = 0;
          }
          break;
        }
        default: {
          is_pointer_class = 0;
        }
      }
    }
    else {
      is_pointer_class = 0;
    }
  }
  else {
    is_pointer_class = 0;
  }
  
  return is_pointer_class;
}

int32_t SPVM_API_get_elem_size(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  int32_t elem_size;
  if (array) {
    if (SPVM_API_is_string(env, stack, array)) {
      elem_size = 1;
    }
    else if (SPVM_API_is_object_array(env, stack, array)) {
      elem_size = sizeof(void*);
    }
    else if (SPVM_API_is_numeric_array(env, stack, array)) {
      
      SPVM_RUNTIME_BASIC_TYPE* array_basic_type = SPVM_API_get_object_basic_type(env, stack, array);
      int32_t type_dimension = array->type_dimension;
      assert(type_dimension == 1);
      
      if (array_basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
        elem_size = 1;
      }
      else if (array_basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
        elem_size = 2;
      }
      else if (array_basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT || array_basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
        elem_size = 4;
      }
      else if (array_basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG || array_basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
        elem_size = 8;
      }
      else {
        assert(0);
      }
    }
    else if (SPVM_API_is_mulnum_array(env, stack, array)) {
      SPVM_RUNTIME_BASIC_TYPE* array_basic_type = SPVM_API_get_object_basic_type(env, stack, array);
      int32_t type_dimension = array->type_dimension;
      assert(type_dimension == 1);
      
      int32_t fields_length = array_basic_type->fields_length;
      
      SPVM_RUNTIME_FIELD* first_field = SPVM_API_BASIC_TYPE_get_field_by_index(runtime, array_basic_type, 0);
      
      int32_t field_basic_type_id = first_field->basic_type->id;
      
      if (field_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
        elem_size = 1 * fields_length;
      }
      else if (field_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
        elem_size = 2 * fields_length;
      }
      else if (field_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT || field_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
        elem_size = 4 * fields_length;
      }
      else if (field_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG || field_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
        elem_size = 8 * fields_length;
      }
      else {
        assert(0);
      }
    }
  }
  else {
    elem_size = 0;
  }
  
  return elem_size;
}

int32_t SPVM_API_enter_scope(SPVM_ENV* env, SPVM_VALUE* stack){
  

  SPVM_OBJECT*** current_mortal_stack_ptr = (SPVM_OBJECT***)&stack[SPVM_API_C_STACK_INDEX_MORTAL_STACK];
  int32_t* current_mortal_stack_top_ptr = (int32_t*)&stack[SPVM_API_C_STACK_INDEX_MORTAL_STACK_TOP];
  int32_t* current_mortal_stack_capacity_ptr = (int32_t*)&stack[SPVM_API_C_STACK_INDEX_MORTAL_STACK_CAPACITY];
  
  int32_t mortal_stack_top = *current_mortal_stack_top_ptr ;
  
  return mortal_stack_top;
}

SPVM_OBJECT* SPVM_API_get_type_name_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  
  assert(object);
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
  int32_t type_dimension = object->type_dimension;
  
  int32_t length = 0;
  
  // Basic type
  length += strlen(basic_type_name);
  
  //[]
  length += type_dimension * 2;
  
  void* obj_type_name = SPVM_API_new_string_no_mortal(env, stack, NULL, length);
  
  char* type_name = (char*)SPVM_API_get_chars(env, stack, obj_type_name);
  
  int32_t type_name_index = 0;
  sprintf((char*)type_name, "%s", basic_type_name);
  type_name_index += strlen(basic_type_name);
  
  int32_t dim_index;
  for (dim_index = 0; dim_index < type_dimension; dim_index++) {
    sprintf((char*)(type_name + type_name_index), "[]");
    type_name_index += 2;
  }
  
  return obj_type_name;
}

SPVM_OBJECT* SPVM_API_get_type_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  
  SPVM_OBJECT* obj_type_name = SPVM_API_get_type_name_no_mortal(env, stack, object);
  
  SPVM_API_push_mortal(env, stack, obj_type_name);
  
  return obj_type_name;
}

int32_t SPVM_API_get_compile_type_name_length(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t type_dimension, int32_t type_flag) {
  
  int32_t compile_type_name_length = 0;
  
  // mutable
  if (type_flag & SPVM_NATIVE_C_TYPE_FLAG_MUTABLE) {
    compile_type_name_length += strlen("mutable ");
  }
  
  // Basic type
  compile_type_name_length += strlen(basic_type_name);
  
  // []
  compile_type_name_length += type_dimension * 2;
  
  // *
  if (type_flag & SPVM_NATIVE_C_TYPE_FLAG_REF) {
    compile_type_name_length += 1;
  }
  
  return compile_type_name_length;
}

SPVM_OBJECT* SPVM_API_get_compile_type_name_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t type_dimension, int32_t type_flag) {
  
  int32_t compile_type_name_length = SPVM_API_get_compile_type_name_length(env, stack, basic_type_name, type_dimension, type_flag);
  
  void* obj_compile_type_name = SPVM_API_new_string_no_mortal(env, stack, NULL, compile_type_name_length);
  
  char* compile_type_name = (char*)SPVM_API_get_chars(env, stack, obj_compile_type_name);
  
  if (type_flag & SPVM_NATIVE_C_TYPE_FLAG_MUTABLE) {
    sprintf(compile_type_name, "mutable ");
    compile_type_name += strlen("mutable ");
  }
  
  sprintf(compile_type_name, "%s", basic_type_name);
  compile_type_name += strlen(basic_type_name);
  
  for (int32_t type_dimension_index = 0; type_dimension_index < type_dimension; type_dimension_index++) {
    sprintf(compile_type_name, "[]");
    compile_type_name += 2;
  }
  
  // Reference
  if (type_flag & SPVM_NATIVE_C_TYPE_FLAG_REF) {
    sprintf(compile_type_name, "*");
    compile_type_name += 1;
  }
  
  *compile_type_name = '\0';
  compile_type_name++;
  
  return obj_compile_type_name;
}

SPVM_OBJECT* SPVM_API_get_compile_type_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t type_dimension, int32_t type_flag) {
  
  SPVM_OBJECT* obj_compile_type_name = SPVM_API_get_compile_type_name_no_mortal(env, stack, basic_type_name, type_dimension, type_flag);
  
  SPVM_API_push_mortal(env, stack, obj_compile_type_name);
  
  return obj_compile_type_name;
}

SPVM_OBJECT* SPVM_API_new_stack_trace_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* exception, SPVM_RUNTIME_METHOD* method, int32_t line) {

  if (stack[SPVM_API_C_STACK_INDEX_CALL_DEPTH].ival > 100) {
    return exception;
  }

  SPVM_RUNTIME* runtime = env->runtime;

  SPVM_RUNTIME_BASIC_TYPE* basic_type = method->current_basic_type;
  const char* basic_type_name = basic_type->name;
  const char* method_name = method->name;

  const char* class_dir = basic_type->class_dir;
  const char* class_dir_sep;
  if (class_dir) {
    class_dir_sep = "/";
  }
  else {
    class_dir = "";
    class_dir_sep = "";
  }
  
  const char* class_rel_file = basic_type->class_rel_file;
  
  // Basic type name and method name
  const char* new_line_part = "\n  ";
  const char* arrow_part = "->";
  const char* at_part = " at ";

  // Exception
  const char* exception_bytes = SPVM_API_get_chars(env, stack, exception);
  int32_t exception_length = SPVM_API_length(env, stack, exception);
  
  // Total string length
  int32_t total_length = 0;
  total_length += exception_length;
  total_length += strlen(new_line_part);
  total_length += strlen(basic_type_name);
  total_length += strlen(arrow_part);
  total_length += strlen(method_name);
  total_length += strlen(at_part);
  total_length += strlen(class_dir);
  total_length += strlen(class_dir_sep);
  total_length += strlen(class_rel_file);

  const char* line_part = " line ";
  char line_str[20];
  
  sprintf(line_str, "%" PRId32, line);
  total_length += strlen(line_part);
  total_length += strlen(line_str);
  
  // Create exception message
  void* new_exception = SPVM_API_new_string_no_mortal(env, stack, NULL, total_length);
  const char* new_exception_bytes = SPVM_API_get_chars(env, stack, new_exception);
  
  memcpy(
    (void*)(new_exception_bytes),
    (void*)(exception_bytes),
    exception_length
  );

  sprintf(
    (char*)new_exception_bytes + exception_length,
    "%s%s%s%s%s%s%s%s%s%" PRId32,
    new_line_part,
    basic_type_name,
    arrow_part,
    method_name,
    at_part,
    class_dir,
    class_dir_sep,
    class_rel_file,
    line_part,
    line
  );
  
  return new_exception;
}

SPVM_OBJECT* SPVM_API_new_stack_trace(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* exception, SPVM_RUNTIME_METHOD* method, int32_t line) {
  
  
  SPVM_OBJECT* stack_trace = SPVM_API_new_stack_trace_no_mortal(env, stack, exception, method, line);
  
  SPVM_API_push_mortal(env, stack, stack_trace);
  
  return stack_trace;
}

void SPVM_API_fprint(SPVM_ENV* env, SPVM_VALUE* stack, FILE* fh, SPVM_OBJECT* string) {
  
  if (string) {
    const char* bytes = SPVM_API_get_chars(env, stack, string);
    int32_t string_length = SPVM_API_length(env, stack, string);
    
    if (string_length > 0) {
      fwrite(bytes, 1, string_length, fh);
    }
  }
}

void SPVM_API_print(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_API_fprint(env, stack, runtime->spvm_stdout, string);
}

void SPVM_API_say(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_API_fprint(env, stack, runtime->spvm_stdout, string);
  
  fputc('\n', runtime->spvm_stdout);
}

void SPVM_API_warn(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string, const char* class_dir, const char* class_rel_file, int32_t line) {
  const char* class_dir_sep;
  if (class_dir) {
    class_dir_sep = "/";
  }
  else {
    class_dir_sep = "";
    class_dir = "";
  }
  
  FILE* spvm_stderr = SPVM_API_RUNTIME_get_spvm_stderr(env->runtime);
  
  int32_t empty_or_undef = 0;
  if (string) {
    const char* bytes =SPVM_API_get_chars(env, stack, string);
    int32_t string_length = SPVM_API_length(env, stack, string);
    
    if (string_length > 0) {
      size_t ret = fwrite(bytes, 1, string_length, spvm_stderr);
      
      // Add line and file information if last character is not '\n'
      int32_t add_line_file;
      if (bytes[string_length - 1] != '\n') {
        fprintf(spvm_stderr, "\n  at %s%s%s line %d\n", class_dir, class_dir_sep, class_rel_file, line);
      }
    }
    else {
      empty_or_undef = 1;
    }
  }
  else {
    empty_or_undef = 1;
  }
  
  if (empty_or_undef) {
    fprintf(spvm_stderr, "Warning\n  at %s%s%s line %d\n", class_dir, class_dir_sep, class_rel_file, line);
  }
}

void SPVM_API_print_stderr(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_API_fprint(env, stack, runtime->spvm_stderr, string);
}

SPVM_OBJECT* SPVM_API_concat_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string1, SPVM_OBJECT* string2) {
  
  int32_t string1_length = SPVM_API_length(env, stack, string1);
  int32_t string2_length = SPVM_API_length(env, stack, string2);
  
  int32_t string3_length = string1_length + string2_length;
  SPVM_OBJECT* string3 = SPVM_API_new_string_no_mortal(env, stack, NULL, string3_length);
  
  const char* string1_bytes = SPVM_API_get_chars(env, stack, string1);
  const char* string2_bytes = SPVM_API_get_chars(env, stack, string2);
  char* string3_bytes = (char*)SPVM_API_get_chars(env, stack, string3);
  
  if (string1_length > 0) {
    memcpy(string3_bytes, string1_bytes, string1_length);
  }
  if (string2_length) {
    memcpy(string3_bytes + string1_length, string2_bytes, string2_length);
  }
  
  return string3;
}

SPVM_OBJECT* SPVM_API_concat(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string1, SPVM_OBJECT* string2) {
  
  
  SPVM_OBJECT* str = SPVM_API_concat_no_mortal(env, stack, string1, string2);
  
  SPVM_API_push_mortal(env, stack, str);
  
  return str;
}

SPVM_OBJECT* SPVM_API_dump(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  
  SPVM_OBJECT* str = SPVM_API_dump_no_mortal(env, stack, object);
  
  SPVM_API_push_mortal(env, stack, str);
  
  return str;
}

SPVM_OBJECT* SPVM_API_dump_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  int32_t depth = 0;
  SPVM_STRING_BUFFER* string_buffer = SPVM_STRING_BUFFER_new(runtime->allocator, 255, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
  SPVM_HASH* address_symtable = SPVM_HASH_new(runtime->allocator, 255, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
  
  SPVM_API_dump_recursive(env, stack, object, &depth, string_buffer, address_symtable);
  
  int32_t string_buffer_length = string_buffer->length;
  
  SPVM_OBJECT* dump = SPVM_API_new_string_no_mortal(env, stack, string_buffer->string, string_buffer->length);
  
  SPVM_HASH_free(address_symtable);
  address_symtable = NULL;
  
  SPVM_STRING_BUFFER_free(string_buffer);
  string_buffer = NULL;
  
  return dump;
}

const char* SPVM_API_dumpc(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  
  SPVM_OBJECT* obj_dump = SPVM_API_dump(env, stack, object);
  
  const char* dump_chars = SPVM_API_get_chars(env, stack, obj_dump);
  
  return dump_chars;
}

#define utf_cont(ch)  (((ch) & 0xc0) == 0x80)
#define SPVM_UTF8PROC_ERROR_INVALIDUTF8 -3
static ptrdiff_t spvm_utf8proc_iterate(const uint8_t *str, ptrdiff_t strlen, int32_t *dst) {
  uint32_t uc;
  const uint8_t *end;
  
  *dst = -1;
  if (!strlen) return 0;
  end = str + ((strlen < 0) ? 4 : strlen);
  uc = *str++;
  if (uc < 0x80) {
    *dst = uc;
    return 1;
  }
  // Must be between 0xc2 and 0xf4 inclusive to be valid
  if ((uc - 0xc2) > (0xf4-0xc2)) return SPVM_UTF8PROC_ERROR_INVALIDUTF8;
  if (uc < 0xe0) {         // 2-byte sequence
     // Must have valid continuation character
     if (str >= end || !utf_cont(*str)) return SPVM_UTF8PROC_ERROR_INVALIDUTF8;
     *dst = ((uc & 0x1f)<<6) | (*str & 0x3f);
     return 2;
  }
  if (uc < 0xf0) {        // 3-byte sequence
     if ((str + 1 >= end) || !utf_cont(*str) || !utf_cont(str[1]))
        return SPVM_UTF8PROC_ERROR_INVALIDUTF8;
     // Check for surrogate chars
     if (uc == 0xed && *str > 0x9f)
         return SPVM_UTF8PROC_ERROR_INVALIDUTF8;
     uc = ((uc & 0xf)<<12) | ((*str & 0x3f)<<6) | (str[1] & 0x3f);
     if (uc < 0x800)
         return SPVM_UTF8PROC_ERROR_INVALIDUTF8;
     *dst = uc;
     return 3;
  }
  // 4-byte sequence
  // Must have 3 valid continuation characters
  if ((str + 2 >= end) || !utf_cont(*str) || !utf_cont(str[1]) || !utf_cont(str[2]))
     return SPVM_UTF8PROC_ERROR_INVALIDUTF8;
  // Make sure in correct range (0x10000 - 0x10ffff)
  if (uc == 0xf0) {
    if (*str < 0x90) return SPVM_UTF8PROC_ERROR_INVALIDUTF8;
  } else if (uc == 0xf4) {
    if (*str > 0x8f) return SPVM_UTF8PROC_ERROR_INVALIDUTF8;
  }
  *dst = ((uc & 7)<<18) | ((*str & 0x3f)<<12) | ((str[1] & 0x3f)<<6) | (str[2] & 0x3f);
  return 4;
}

void SPVM_API_dump_recursive(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t* depth, SPVM_STRING_BUFFER* string_buffer, SPVM_HASH* address_symtable) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  char tmp_buffer[256];
  
  SPVM_OBJECT* dump;
  if (object == NULL) {
    SPVM_STRING_BUFFER_add(string_buffer, "undef");
  }
  else {
    int32_t type_dimension = object->type_dimension;
    
    if (SPVM_API_is_string(env, stack, object)) {
      const char* chars = SPVM_API_get_chars(env, stack, object);
      int32_t chars_length  = SPVM_API_length(env, stack, object);
      
      SPVM_STRING_BUFFER_add(string_buffer, "\"");
      
      int32_t offset = 0;
      while (1) {
        
        if (offset >= chars_length) {
          break;
        }
        
        int32_t dst;
        int32_t utf8_char_len = (int32_t)spvm_utf8proc_iterate((const uint8_t*)(chars + offset), chars_length, &dst);
        
        int32_t uchar;
        if (utf8_char_len > 0) {
            
          if (utf8_char_len == 1 && !isprint(*(chars + offset))) {
            sprintf(tmp_buffer, "\\x{%02X}", *(chars + offset) & 0xFF);
            
            SPVM_STRING_BUFFER_add_len(string_buffer, tmp_buffer, strlen(tmp_buffer));
          }
          else {
            SPVM_STRING_BUFFER_add_len(string_buffer, (char*)(chars + offset), utf8_char_len);
          }
          
          offset += utf8_char_len;
        }
        else {
          
          sprintf(tmp_buffer, "\\x{%02X}", *(chars + offset) & 0xFF);
          
          SPVM_STRING_BUFFER_add_len(string_buffer, tmp_buffer, strlen(tmp_buffer));
          
          offset += 1;
        }
      }
      
      SPVM_STRING_BUFFER_add(string_buffer, "\"");
    }
    else if (type_dimension > 0) {
      int32_t array_length = SPVM_API_length(env, stack, object);
      int32_t element_type_dimension = type_dimension - 1;
      
      SPVM_STRING_BUFFER_add(string_buffer, "[\n");
            
      SPVM_RUNTIME_BASIC_TYPE* object_basic_type = SPVM_API_get_object_basic_type(env, stack, object);
      const char* object_basic_type_name =  object_basic_type->name;
          
      for (int32_t array_index = 0; array_index < array_length; array_index++) {
        
        for (int32_t depth_index = 0; depth_index < *depth + 1; depth_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
        }
        
        if (SPVM_API_is_mulnum_array(env, stack, object)) {
          
          SPVM_STRING_BUFFER_add(string_buffer, "{\n");
          
          int32_t fields_length = object_basic_type->fields_length;
          
          for (int32_t field_index = 0; field_index < fields_length; field_index++) {
            for (int32_t depth_index = 0; depth_index < *depth + 2; depth_index++) {
              SPVM_STRING_BUFFER_add(string_buffer, "  ");
            }
            
            SPVM_RUNTIME_FIELD* field = SPVM_API_BASIC_TYPE_get_field_by_index(runtime, object_basic_type, field_index);
            
            int32_t field_basic_type_id = field->basic_type->id;
            
            const char* field_name = field->name;
            SPVM_STRING_BUFFER_add(string_buffer, field_name);
            SPVM_STRING_BUFFER_add(string_buffer, " => ");
            
            switch (field_basic_type_id) {
              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                int8_t* element = &((int8_t*)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime)))[array_index * fields_length];
                sprintf(tmp_buffer, "%d", element[field_index]);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                int16_t* element = &((int16_t*)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime)))[array_index * fields_length];
                sprintf(tmp_buffer, "%d", element[field_index]);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                int32_t* element = &((int32_t*)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime)))[array_index * fields_length];
                sprintf(tmp_buffer, "%d", element[field_index]);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                int64_t* element = &((int64_t*)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime)))[array_index * fields_length];
                sprintf(tmp_buffer, "%lld", (long long int)element[field_index]);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                float* element = &((float*)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime)))[array_index * fields_length];
                sprintf(tmp_buffer, "%g", element[field_index]);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                double* element = &((double*)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime)))[array_index * fields_length];
                sprintf(tmp_buffer, "%g", element[field_index]);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
            }
            
            if (field_index == fields_length - 1) {
              SPVM_STRING_BUFFER_add(string_buffer, "\n");
            }
            else {
              SPVM_STRING_BUFFER_add(string_buffer, ",\n");
            }
          }
          
          SPVM_STRING_BUFFER_add(string_buffer, "  }");
        }
        else if (SPVM_API_is_numeric_array(env, stack, object)) {
          switch (object_basic_type->id) {
            case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
              int8_t element = ((int8_t*)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime)))[array_index];
              sprintf(tmp_buffer, "%d", element);
              SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
              int16_t element = ((int16_t*)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime)))[array_index];
              sprintf(tmp_buffer, "%d", element);
              SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
              int32_t element = ((int32_t*)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime)))[array_index];
              sprintf(tmp_buffer, "%d", element);
              SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
              int64_t element = ((int64_t*)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime)))[array_index];
              sprintf(tmp_buffer, "%lld", (long long int)element);
              SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
              float element = ((float*)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime)))[array_index];
              sprintf(tmp_buffer, "%g", element);
              SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
              double element = ((double*)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime)))[array_index];
              sprintf(tmp_buffer, "%g", element);
              SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
              break;
            }
          }
        }
        else if (SPVM_API_is_object_array(env, stack, object)) {
          SPVM_OBJECT* element = (((SPVM_OBJECT**)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime)))[array_index]);
          element = SPVM_API_get_object_no_weaken_address(env, stack, element);
          (*depth)++;
          SPVM_API_dump_recursive(env, stack, element, depth, string_buffer, address_symtable);
          (*depth)--;
        }
        else {
          assert(0);
        }
        
        if (array_index == array_length - 1) {
          SPVM_STRING_BUFFER_add(string_buffer, "\n");
        }
        else {
          SPVM_STRING_BUFFER_add(string_buffer, ",\n");
        }
      }
      
      for (int32_t depth_index = 0; depth_index < *depth; depth_index++) {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
      }
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      
      SPVM_STRING_BUFFER_add(string_buffer, " : ");
      SPVM_STRING_BUFFER_add(string_buffer, object_basic_type_name);
      for (int32_t type_dimension_index = 0; type_dimension_index < type_dimension; type_dimension_index++) {
        SPVM_STRING_BUFFER_add(string_buffer, "[]");
      }
      
      // If the object is weaken, this get the real address
      sprintf(tmp_buffer, "(%p)", SPVM_API_get_object_no_weaken_address(env, stack, object));
      SPVM_STRING_BUFFER_add(string_buffer, tmp_buffer);
    }
    else {
      // If the object is weaken, this get the real address
      sprintf(tmp_buffer, "%p", SPVM_API_get_object_no_weaken_address(env, stack, object));
      int32_t exists = (int32_t)(intptr_t)SPVM_HASH_get(address_symtable, tmp_buffer, strlen(tmp_buffer));
      if (exists) {
        // If the object is weaken, this get the real address
        sprintf(tmp_buffer, "REUSE_OBJECT(%p)", SPVM_API_get_object_no_weaken_address(env, stack, object));
        SPVM_STRING_BUFFER_add(string_buffer, tmp_buffer);
      }
      else {
        SPVM_RUNTIME_BASIC_TYPE* object_basic_type = SPVM_API_get_object_basic_type(env, stack, object);
        const char* basic_type_name = object_basic_type->name;
        
        SPVM_HASH_set(address_symtable, tmp_buffer, strlen(tmp_buffer), (void*)(intptr_t)1);
        
        SPVM_STRING_BUFFER_add(string_buffer, basic_type_name);
        sprintf(tmp_buffer, " (%p) ", object);
        SPVM_STRING_BUFFER_add(string_buffer, tmp_buffer);
        
        SPVM_STRING_BUFFER_add(string_buffer, "{\n");
        
        // Free object fields
        int32_t fields_length = object_basic_type->fields_length;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          for (int32_t depth_index = 0; depth_index < *depth + 1; depth_index++) {
            SPVM_STRING_BUFFER_add(string_buffer, "  ");
          }
          
          SPVM_RUNTIME_FIELD* field = SPVM_API_BASIC_TYPE_get_field_by_index(runtime, object_basic_type, field_index);
          
          int32_t field_basic_type_id = field->basic_type->id;
          int32_t field_type_dimension = field->type_dimension;
          int32_t field_offset = field->offset;
          const char* field_name = field->name;
          
          SPVM_STRING_BUFFER_add(string_buffer, field_name);
          SPVM_STRING_BUFFER_add(string_buffer, " => ");
          if (field_type_dimension == 0 && field_basic_type_id >= SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE && field_basic_type_id <= SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
            switch (field_basic_type_id) {
              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                int8_t field_value = *(int8_t*)((intptr_t)object + (size_t)SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + field_offset);
                sprintf(tmp_buffer, "%d", field_value);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                int16_t field_value = *(int16_t*)((intptr_t)object + (size_t)SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + field_offset);
                sprintf(tmp_buffer, "%d", field_value);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                int32_t field_value = *(int32_t*)((intptr_t)object + (size_t)SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + field_offset);
                sprintf(tmp_buffer, "%d", field_value);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                int64_t field_value = *(int64_t*)((intptr_t)object + (size_t)SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + field_offset);
                sprintf(tmp_buffer, "%lld", (long long int)field_value);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                float field_value = *(float*)((intptr_t)object + (size_t)SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + field_offset);
                sprintf(tmp_buffer, "%g", field_value);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                double field_value = *(double*)((intptr_t)object + (size_t)SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + field_offset);
                sprintf(tmp_buffer, "%g", field_value);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              default : {
                assert(0);
              }
            }
          }
          else  {
            SPVM_OBJECT* field_value = *(SPVM_OBJECT**)((intptr_t)object + (size_t)SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + field_offset);
            field_value = SPVM_API_get_object_no_weaken_address(env, stack, field_value);
            (*depth)++;
            SPVM_API_dump_recursive(env, stack, field_value, depth, string_buffer, address_symtable);
            (*depth)--;
          }
          
          if (field_index == fields_length - 1) {
            SPVM_STRING_BUFFER_add(string_buffer, "\n");
          }
          else {
            SPVM_STRING_BUFFER_add(string_buffer, ",\n");
          }
        }
        
        for (int32_t depth_index = 0; depth_index < *depth; depth_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
        }
        SPVM_STRING_BUFFER_add(string_buffer, "}");
      }
    }
  }
}

void SPVM_API_make_read_only(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string) {
  SPVM_RUNTIME_BASIC_TYPE* string_basic_type = SPVM_API_get_object_basic_type(env, stack, string);
  if (string && string_basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_STRING && string->type_dimension == 0) {
    string->flag |= SPVM_OBJECT_C_FLAG_IS_READ_ONLY;
  }
}

int32_t SPVM_API_is_read_only(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string) {
  
  int32_t is_read_only;
  if (string) {
    if (string->flag & SPVM_OBJECT_C_FLAG_IS_READ_ONLY) {
      is_read_only = 1;
    }
    else {
      is_read_only = 0;
    }
  }
  else {
    is_read_only = 0;
  }
  
  return is_read_only;
}

int32_t SPVM_API_set_exception(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* exception) {
  
  SPVM_OBJECT** current_exception_ptr = (SPVM_OBJECT**)&stack[SPVM_API_C_STACK_INDEX_EXCEPTION];
  
  SPVM_API_assign_object(env, stack, current_exception_ptr, exception);
  
  return 0;
}

SPVM_OBJECT* SPVM_API_get_exception(SPVM_ENV* env, SPVM_VALUE* stack){

  SPVM_OBJECT** current_exception_ptr = (SPVM_OBJECT**)&stack[SPVM_API_C_STACK_INDEX_EXCEPTION];
  SPVM_OBJECT* current_exception = *current_exception_ptr;
  
  return current_exception;
}

SPVM_OBJECT* SPVM_API_new_byte_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  
  SPVM_OBJECT* object = SPVM_API_new_byte_array_no_mortal(env, stack, length);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_short_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  
  SPVM_OBJECT* object = SPVM_API_new_short_array_no_mortal(env, stack, length);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_int_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  
  SPVM_OBJECT* object = SPVM_API_new_int_array_no_mortal(env, stack, length);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_long_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  
  SPVM_OBJECT* object = SPVM_API_new_long_array_no_mortal(env, stack, length);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_float_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  
  SPVM_OBJECT* object = SPVM_API_new_float_array_no_mortal(env, stack, length);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_double_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  
  SPVM_OBJECT* object = SPVM_API_new_double_array_no_mortal(env, stack, length);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_string_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  
  SPVM_OBJECT* string_array = SPVM_API_new_string_array_no_mortal(env, stack, length);
  
  SPVM_API_push_mortal(env, stack, string_array);
  
  return string_array;
}

SPVM_OBJECT* SPVM_API_new_string_array_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  
  SPVM_RUNTIME_BASIC_TYPE* string_basic_type = SPVM_API_RUNTIME_get_basic_type_by_id(env->runtime, SPVM_NATIVE_C_BASIC_TYPE_ID_STRING);
  
  SPVM_OBJECT* object = SPVM_API_new_object_array_no_mortal(env, stack, string_basic_type, length);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  SPVM_OBJECT* object = SPVM_API_new_object_no_mortal(env, stack, basic_type);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_object_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (!basic_type) {
    return NULL;
  }
  
  if (basic_type->category != SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS) {
    return NULL;
  }
  
  // Alloc body length + 1
  int32_t fields_length = basic_type->fields_length;
  
  size_t alloc_size = (size_t)SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + basic_type->fields_size + 1;
  
  if (!basic_type) {
    return NULL;
  }
  SPVM_OBJECT* object = SPVM_API_new_object_common(env, stack, alloc_size, basic_type, 0, fields_length, 0);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_pointer_object_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_BASIC_TYPE* basic_type, void* pointer) {
  
  void* obj_object = SPVM_API_new_object_no_mortal(env, stack, basic_type);
  
  SPVM_API_set_pointer(env, stack, obj_object, pointer);
  
  return obj_object;
}

SPVM_OBJECT* SPVM_API_new_pointer_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_BASIC_TYPE* basic_type, void* pointer) {
  
  
  SPVM_OBJECT* object = SPVM_API_new_pointer_object_no_mortal(env, stack, basic_type, pointer);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_string_nolen_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes) {
  
  
  int32_t length = strlen((char*)bytes);
  
  SPVM_OBJECT* object = SPVM_API_new_string_no_mortal(env, stack, NULL, length);
  
  if (bytes != NULL && length > 0) {
    memcpy((void*)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime)), (char*)bytes, length);
  }
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_string_nolen(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes) {
  
  
  SPVM_OBJECT* object = SPVM_API_new_string_nolen_no_mortal(env, stack, bytes);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_string_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes, int32_t length) {
  
  
  if (length < 0) {
    return NULL;
  }
  
  size_t alloc_size = (size_t)SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + sizeof(char) * (length + 1);
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type_by_id(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_STRING);
  
  SPVM_OBJECT* object = SPVM_API_new_object_common(env, stack, alloc_size, basic_type, 0, length, 0);
  
  if (object) {
    if (bytes != NULL && length > 0) {
      memcpy((void*)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime)), (char*)bytes, length);
    }
  }
  
  return object;
}

int32_t SPVM_API_get_bool_object_value(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* bool_object) {
  
  int32_t value = *(int32_t*)((intptr_t)bool_object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime));
  
  return value;
}

SPVM_OBJECT* SPVM_API_new_string(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes, int32_t length) {
  
  
  SPVM_OBJECT* object = SPVM_API_new_string_no_mortal(env, stack, bytes, length);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_byte_array_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  
  if (length < 0) {
    return NULL;
  }
  
  size_t alloc_size = (size_t)SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + sizeof(int8_t) * (length + 1);
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type_by_id(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE);
  
  SPVM_OBJECT* object = SPVM_API_new_object_common(env, stack, alloc_size, basic_type, 1, length, 0);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_short_array_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  
  size_t alloc_size = (size_t)SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + sizeof(int16_t) * (length + 1);
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type_by_id(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT);
  
  SPVM_OBJECT* object = SPVM_API_new_object_common(env, stack, alloc_size, basic_type, 1, length, 0);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_int_array_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  
  size_t alloc_size = (size_t)SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + sizeof(int32_t) * (length + 1);
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type_by_id(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_INT);
  
  SPVM_OBJECT* object = SPVM_API_new_object_common(env, stack, alloc_size, basic_type, 1, length, 0);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_long_array_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  
  if (length < 0) {
    return NULL;
  }
  
  size_t alloc_size = (size_t)SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + sizeof(int64_t) * (length + 1);
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type_by_id(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_LONG);
  
  SPVM_OBJECT* object = SPVM_API_new_object_common(env, stack, alloc_size, basic_type, 1, length, 0);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_float_array_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  
  size_t alloc_size = (size_t)SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + sizeof(float) * (length + 1);
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type_by_id(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT);
  
  SPVM_OBJECT* object = SPVM_API_new_object_common(env, stack, alloc_size, basic_type, 1, length, 0);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_double_array_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  
  size_t alloc_size = (size_t)SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + sizeof(double) * (length + 1);
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type_by_id(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE);
  
  SPVM_OBJECT* object = SPVM_API_new_object_common(env, stack, alloc_size, basic_type, 1, length, 0);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_object_array_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t length) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_OBJECT object_for_type_check;
  object_for_type_check.basic_type = basic_type;
  object_for_type_check.type_dimension = 1;
  
  int32_t is_object_array = SPVM_API_is_object_array(env, stack, &object_for_type_check);
  
  if (!is_object_array) {
    return NULL;
  }
  
  if (!basic_type) {
    return NULL;
  }
  
  size_t alloc_size = (size_t)SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + sizeof(void*) * (length + 1);
  
  SPVM_OBJECT* object = SPVM_API_new_object_common(env, stack, alloc_size, basic_type, 1, length, 0);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_object_array(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t length) {
  
  SPVM_OBJECT* object = SPVM_API_new_object_array_no_mortal(env, stack, basic_type, length);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_muldim_array_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t length) {
  
  if (type_dimension < 2) {
    return NULL;
  }
  else if (basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_ANY_OBJECT) {
    return NULL;
  }
  
  size_t alloc_size = (size_t)SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + sizeof(void*) * (length + 1);
  
  if (!basic_type) {
    return NULL;
  }
  SPVM_OBJECT* object = SPVM_API_new_object_common(env, stack, alloc_size, basic_type, type_dimension, length, 0);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_muldim_array(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t length) {
  
  SPVM_OBJECT* object = SPVM_API_new_muldim_array_no_mortal(env, stack, basic_type, type_dimension, length);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_mulnum_array_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t length) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  // valut_t array dimension must be 1
  const char* basic_type_name = basic_type->name;
  
  int32_t fields_length = basic_type->fields_length;
  SPVM_RUNTIME_FIELD* field_first = SPVM_API_BASIC_TYPE_get_field_by_index(runtime, basic_type, 0);
  
  int32_t field_basic_type_id = field_first->basic_type->id;
  
  int32_t unit_size;
  if (field_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
    unit_size = sizeof(int8_t);
  }
  else if (field_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
    unit_size = sizeof(int16_t);
  }
  else if (field_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
    unit_size = sizeof(int32_t);
  }
  else if (field_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
    unit_size = sizeof(int64_t);
  }
  else if (field_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
    unit_size = sizeof(float);
  }
  else if (field_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
    unit_size = sizeof(double);
  }
  else {
    assert(0);
  }
  
  size_t alloc_size = (size_t)SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + unit_size * fields_length * (length + 1);
  
  SPVM_OBJECT* object = SPVM_API_new_object_common(env, stack, alloc_size, basic_type, 1, length, 0);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_mulnum_array(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t length) {
  
  SPVM_OBJECT* object = SPVM_API_new_mulnum_array_no_mortal(env, stack, basic_type, length);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_array_proto_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, int32_t length) {

  if (array == NULL) {
    return NULL;
  }
  
  if (length < 0) {
    return NULL;
  }
  
  size_t element_size = SPVM_API_get_elem_size(env, stack, array);
  
  size_t alloc_size = (size_t)SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + element_size * (length + 1);
  
  SPVM_RUNTIME_BASIC_TYPE* array_basic_type = SPVM_API_get_object_basic_type(env, stack, array);
  SPVM_OBJECT* new_array = SPVM_API_new_object_common(env, stack, alloc_size, array_basic_type, array->type_dimension, length, 0);
  
  return new_array;
}

SPVM_OBJECT* SPVM_API_new_array_proto(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, int32_t length) {
  
  
  SPVM_OBJECT* object = SPVM_API_new_array_proto_no_mortal(env, stack, array, length);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

int32_t SPVM_API_get_object_basic_type_id(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  return object->basic_type->id;
}

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_get_object_basic_type(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  return object->basic_type;
}

const char* SPVM_API_get_object_basic_type_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  SPVM_RUNTIME_BASIC_TYPE* object_basic_type = SPVM_API_get_object_basic_type(env, stack, object);
  
  return object_basic_type->name;
}

int32_t SPVM_API_get_object_type_dimension(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  return object->type_dimension;
}

int32_t SPVM_API_length(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  int32_t length = object->length;
  
  return length;
}

void SPVM_API_set_length(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t length) {
  
  object->length = length;
}

int8_t* SPVM_API_get_elems_byte(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  return (int8_t*)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime));
}

const char* SPVM_API_get_chars(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string) {
  
  return (const char*)((intptr_t)string + SPVM_API_RUNTIME_get_object_data_offset(env->runtime));
}

int16_t* SPVM_API_get_elems_short(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  return (int16_t*)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime));
}

int32_t* SPVM_API_get_elems_int(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  return (int32_t*)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime));
}

int64_t* SPVM_API_get_elems_long(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  return (int64_t*)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime));
}

float* SPVM_API_get_elems_float(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  return (float*)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime));
}

double* SPVM_API_get_elems_double(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  return (double*)((intptr_t)object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime));
}

SPVM_OBJECT* SPVM_API_get_elem_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, int32_t index) {
  
  SPVM_OBJECT* object_maybe_weaken = ((SPVM_OBJECT**)((intptr_t)array + SPVM_API_RUNTIME_get_object_data_offset(env->runtime)))[index];
  SPVM_OBJECT* object = SPVM_API_get_object_no_weaken_address(env, stack, object_maybe_weaken);
  
  return object;
}

void SPVM_API_set_elem_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, int32_t index, SPVM_OBJECT* object) {
  
  void* object_ref = &((void**)((intptr_t)array + SPVM_API_RUNTIME_get_object_data_offset(env->runtime)))[index];
  
  SPVM_API_assign_object(env, stack, object_ref, object);
}

SPVM_OBJECT* SPVM_API_get_elem_string(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, int32_t index) {
  
  return SPVM_API_get_elem_object(env, stack, array, index);
}

void SPVM_API_set_elem_string(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, int32_t index, SPVM_OBJECT* string) {
  
  SPVM_API_set_elem_object(env, stack, array, index, string);
}

void* SPVM_API_get_pointer(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  void* pointer = SPVM_NATIVE_GET_POINTER(object);
  
  return pointer;
}

void SPVM_API_set_pointer(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, void* pointer) {
  
  SPVM_NATIVE_SET_POINTER(object, pointer);
}

SPVM_RUNTIME_FIELD* SPVM_API_get_field(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (!object) {
    return NULL;
  }
  
  SPVM_RUNTIME_BASIC_TYPE* object_basic_type = SPVM_API_get_object_basic_type(env, stack, object);
  
  if (object->type_dimension != 0) {
    return NULL;
  }
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_BASIC_TYPE_get_field_by_name(runtime, object_basic_type, field_name);
  
  return field;
}

SPVM_RUNTIME_FIELD* SPVM_API_get_field_static(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* field_name) {
  
  void* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  
  if (!basic_type) {
    return NULL;
  }
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_BASIC_TYPE_get_field_by_name(env->runtime, basic_type, field_name);
  
  return field;
}

SPVM_RUNTIME_CLASS_VAR* SPVM_API_get_class_var(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  
  if (!basic_type) {
    return NULL;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_BASIC_TYPE_get_class_var_by_name(env->runtime, basic_type, class_var_name);
  
  return class_var;
}

SPVM_RUNTIME_METHOD* SPVM_API_get_method(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* method_name) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  
  if (!basic_type) {
    return NULL;
  }
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_BASIC_TYPE_get_method_by_name(env->runtime, basic_type, method_name);
  
  return method;
}

SPVM_RUNTIME_METHOD* SPVM_API_get_class_method(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* method_name) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_get_method(env, stack, basic_type_name, method_name);
  
  if (method) {
    if (!method->is_class_method) {
      return NULL;
    }
  }
  
  return method;
}

SPVM_RUNTIME_METHOD* SPVM_API_get_instance_method_static(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* method_name) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_get_method(env, stack, basic_type_name, method_name);
  
  if (method) {
    if (method->is_class_method) {
      return NULL;
    }
  }
  
  return method;
}

SPVM_RUNTIME_METHOD* SPVM_API_get_instance_method(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* method_name) {
  
  // Method
  SPVM_RUNTIME_METHOD* method = NULL;
  
  // Compiler
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (!object) {
    return NULL;
  }
  
  // Basic type
  SPVM_RUNTIME_BASIC_TYPE* object_basic_type = SPVM_API_get_object_basic_type(env, stack, object);
  SPVM_RUNTIME_BASIC_TYPE* parent_basic_type = object_basic_type;
  
  while (1) {
    if (!parent_basic_type) {
      break;
    }
    
    // Method
    method = SPVM_API_BASIC_TYPE_get_method_by_name(runtime, parent_basic_type, method_name);
    if (method) {
      // Instance method
      if (method->is_class_method) {
        method = NULL;
      }
      break;
    }
    
    parent_basic_type = parent_basic_type->parent;
  }
  
  return method;
}

void* SPVM_API_new_memory_block(SPVM_ENV* env, SPVM_VALUE* stack, size_t size) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  assert(size > 0);
  
  if ((uint64_t)size > (uint64_t)SIZE_MAX) {
    return NULL;
  }
  
  void* block = SPVM_ALLOCATOR_alloc_memory_block_unmanaged((size_t)size);
  
  SPVM_MUTEX* runtime_mutex_atomic = runtime->mutex_atomic;
  {
    SPVM_MUTEX_lock(runtime_mutex_atomic);
    
    runtime->memory_blocks_count++;
    
    SPVM_MUTEX_unlock(runtime_mutex_atomic);
  }
  
#ifdef SPVM_DEBUG_MEMORY
    {
      SPVM_MUTEX_reader_lock(runtime_mutex_atomic);
      fprintf(runtime->spvm_stderr, "[Debug]Function : new_memory_block, Block Address: %p, Stack Address : %p, Memory Blocks Count : %d\n", block, stack, runtime->memory_blocks_count);
      SPVM_MUTEX_reader_unlock(runtime_mutex_atomic);
    }
#endif
  
  return block;
}

// Deprecated
void SPVM_API_free_memory_block(SPVM_ENV* env, SPVM_VALUE* stack, void* block) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (block) {
    SPVM_ALLOCATOR_free_memory_block_unmanaged(block);
    
    SPVM_MUTEX* runtime_mutex_atomic = runtime->mutex_atomic;
    {
      SPVM_MUTEX_lock(runtime_mutex_atomic);
      
      runtime->memory_blocks_count--;
      
      SPVM_MUTEX_unlock(runtime_mutex_atomic);
    }
    
#ifdef SPVM_DEBUG_MEMORY
    {
      SPVM_MUTEX_reader_lock(runtime_mutex_atomic);
      fprintf(runtime->spvm_stderr, "[Debug]Function : free_memory_block, Block Address: %p, Stack Address : %p, Memory Blocks Count : %d\n", block, stack, runtime->memory_blocks_count);
      SPVM_MUTEX_reader_unlock(runtime_mutex_atomic);
    }
#endif
  }
}

int32_t SPVM_API_get_memory_blocks_count(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_MUTEX* runtime_mutex_atomic = runtime->mutex_atomic;
  
  int32_t memory_blocks_count = 0;
  {
    SPVM_MUTEX_reader_lock(runtime_mutex_atomic);
    memory_blocks_count = runtime->memory_blocks_count;
    SPVM_MUTEX_reader_unlock(runtime_mutex_atomic);
  }
  
  return memory_blocks_count;
}

SPVM_OBJECT* SPVM_API_copy_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  if (!object) {
    return NULL;
  }
  
  SPVM_OBJECT* new_object;
  
  int32_t length = SPVM_API_length(env, stack, object);
  
  if (SPVM_API_is_string(env, stack, object)) {
    new_object = SPVM_API_new_string_no_mortal(env, stack, NULL, length);
    
    const char* object_chars = SPVM_API_get_chars(env, stack, object);
    char* new_object_chars = (char*)SPVM_API_get_chars(env, stack, new_object);
    
    memcpy(new_object_chars, object_chars, length);
  }
  else if (SPVM_API_is_numeric_array(env, stack, object) || SPVM_API_is_mulnum_array(env, stack, object)) {
    new_object = SPVM_API_new_array_proto_no_mortal(env, stack, object, length);
    
    const char* object_bytes = (const char*)SPVM_API_get_elems_byte(env, stack, object);
    char* new_object_bytes = (char*)SPVM_API_get_elems_byte(env, stack, new_object);
    
    size_t element_size = SPVM_API_get_elem_size(env, stack, object);
    
    memcpy(new_object_bytes, object_bytes, element_size * length);
  }
  else {
    new_object = NULL;
  }
  
  return new_object;
}

SPVM_OBJECT* SPVM_API_copy(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  
  SPVM_OBJECT* new_object = SPVM_API_copy_no_mortal(env, stack, object);
  
  SPVM_API_push_mortal(env, stack, new_object);
  
  return new_object;
}

void SPVM_API_shorten(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string, int32_t new_length) {
  
  
  if (string != NULL) {
    if (SPVM_API_is_string(env, stack, string)) {
      if (!SPVM_API_is_read_only(env, stack, string)) {
        int32_t length = SPVM_API_length(env, stack, string);
        
        if (new_length > length) {
          new_length = length;
        }
        else if (new_length < 0) {
          new_length = 0;
        }
        
        SPVM_API_set_length(env, stack, string, new_length);
        char* chars = (char*)SPVM_API_get_chars(env, stack, string);
        if (new_length > length) {
          memset(chars + new_length, 0, new_length - length);
        }
      }
    }
  }
}

int32_t SPVM_API_elem_isa(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, SPVM_OBJECT* element) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  assert(array);
  
  SPVM_RUNTIME_BASIC_TYPE* array_basic_type = SPVM_API_get_object_basic_type(env, stack,array);
  
  int32_t array_type_dimension = array->type_dimension;
  
  assert(array_type_dimension > 0);
  int32_t runtime_assignability = SPVM_API_isa(env, stack, element, array_basic_type, array_type_dimension - 1);

  return runtime_assignability;
}

int32_t SPVM_API_is_type(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension) {
  
  // Object must be not null
  assert(object);
  
  int32_t is_type = 0;
  SPVM_RUNTIME_BASIC_TYPE* object_basic_type = SPVM_API_get_object_basic_type(env, stack, object);
  if (object_basic_type->id == basic_type->id && object->type_dimension == type_dimension) {
    is_type = 1;
  }
  
  return is_type;
}

int32_t SPVM_API_is_type_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* basic_type_name, int32_t type_dimension) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    return 0;
  };
  
  int32_t is_type = SPVM_API_is_type(env, stack, object, basic_type, type_dimension);
  
  return is_type;
}

int32_t SPVM_API_isa(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  int32_t isa;
  if (object == NULL) {
    isa = 1;
  }
  else {
    SPVM_RUNTIME_BASIC_TYPE* object_basic_type = SPVM_API_get_object_basic_type(env, stack, object);
    int32_t object_type_dimension = object->type_dimension;
    if (!basic_type) {
      isa = 0;
    }
    else {
      isa = SPVM_API_TYPE_can_assign(env->runtime, basic_type, type_dimension, 0, object_basic_type, object_type_dimension, 0);
    }
  }
  
  return isa;
}

int32_t SPVM_API_isa_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* basic_type_name, int32_t type_dimension) {
  
  void* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    return 0;
  };
  
  int32_t isa = SPVM_API_isa(env, stack, object, basic_type, type_dimension);
  
  return isa;
}

int32_t SPVM_API_get_basic_type_id_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  int32_t basic_type_id = SPVM_API_get_basic_type_id(env, stack, basic_type_name);
  if (basic_type_id < 0) {
    *error_id = 1;
    SPVM_API_die(env, stack, "The %s basic type is not found", basic_type_name, func_name, file, line);
  };
  return basic_type_id;
}

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_get_basic_type_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  void* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    *error_id = 1;
    SPVM_API_die(env, stack, "The %s basic type is not found", basic_type_name, func_name, file, line);
  };
  
  return basic_type;
}

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_get_basic_type_by_id(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id) {
  
  void* basic_type = SPVM_API_RUNTIME_get_basic_type_by_id(env->runtime, basic_type_id);
  
  return basic_type;
}

void* SPVM_API_strerror_string(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value, int32_t length) {
  
  assert(length >= 0);
  
  if (length == 0) {
    // Linux maybe needs at least 49.
    // Windows needs at least 94.
    length = 128;
  }
  
  void* obj_strerror_value = SPVM_API_new_string(env, stack, NULL, length);
  char* strerror_value = (char*)SPVM_API_get_chars(env, stack, obj_strerror_value);
  
  int32_t status = SPVM_STRERROR_strerror(errno_value, strerror_value, length);
  
  if (!(status == 0)) {
    errno = status;
    sprintf(strerror_value, "strerror failed. errno is %d.", errno);
  }
  
  SPVM_API_shorten(env, stack, obj_strerror_value, strlen(strerror_value));
  
  return obj_strerror_value;
}

const char* SPVM_API_strerror(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value, int32_t length) {
  
  void* obj_strerror_value = SPVM_API_strerror_string(env, stack, errno_value, length);
  
  if (obj_strerror_value) {
    char* strerror_value = (char*)SPVM_API_get_chars(env, stack, obj_strerror_value);
    return strerror_value;
  }
  else {
    return NULL;
  }
}

void* SPVM_API_strerror_string_nolen(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value) {
  return SPVM_API_strerror_string(env, stack, errno_value, 0);
}

const char* SPVM_API_strerror_nolen(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value) {
  return SPVM_API_strerror(env, stack, errno_value, 0);
}

int32_t SPVM_API_call_method_vm(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_METHOD* method, int32_t args_width) {
  return SPVM_VM_call_method(env, stack, method, args_width);
}

const char* SPVM_API_get_spvm_version_string(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  const char* spvm_version_string = SPVM_NATIVE_VERSION_STRING;
  
  return spvm_version_string;
}

double SPVM_API_get_spvm_version_number(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  const char* spvm_version_string = SPVM_API_get_spvm_version_string(env, stack);
  
  assert(spvm_version_string);
  
  int32_t spvm_version_string_length = strlen(spvm_version_string);
  
  char *end;
  errno = 0;
  double version_number = strtod(spvm_version_string, &end);
  assert(*end == '\0');
  assert(errno == 0);
  
  return version_number;
}

const char* SPVM_API_get_version_string(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_BASIC_TYPE* basic_type){
  
  return basic_type->version_string;
}

double SPVM_API_get_version_number(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  const char* version_string = SPVM_API_get_version_string(env, stack, basic_type);
  
  if (!version_string) {
    return -1;
  }
  
  int32_t version_string_length = strlen(version_string);
  
  char version_string_without_hyphen[20] = {0};
  int32_t version_string_without_hyphen_length = 0;
  for (int32_t i = 0; i < version_string_length; i++) {
    char ch = version_string[i];
    if (!(ch == '_')) {
      version_string_without_hyphen[version_string_without_hyphen_length] = ch;
      version_string_without_hyphen_length++;
    }
  }
  
  char *end;
  errno = 0;
  double version_number = strtod(version_string_without_hyphen, &end);
  assert(*end == '\0');
  assert(errno == 0);
  
  return version_number;
}

SPVM_OBJECT* SPVM_API_new_object_common(SPVM_ENV* env, SPVM_VALUE* stack, size_t alloc_size, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t length, int32_t flag) {
  
  SPVM_OBJECT* object = SPVM_API_new_memory_block(env, stack, alloc_size);
  
  if (object) {
    object->basic_type = basic_type;
    object->type_dimension = type_dimension;
    object->flag = flag;
    
    // The length of string can be shorten.
    SPVM_API_set_length(env, stack, object, length);
  }
  
  return object;
}

int32_t SPVM_API_check_stack_env(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t is_valid = 0;
  if (stack[SPVM_API_C_STACK_INDEX_ENV].oval == env) {
    is_valid = 1;
  }
  
  return is_valid;
}

int32_t SPVM_API_call_method_common(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_METHOD* method, int32_t args_width, int32_t mortal) {
  
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  int32_t error_id = 0;
  stack[SPVM_API_C_STACK_INDEX_ARGS_WIDTH].ival = args_width;
  stack[SPVM_API_C_STACK_INDEX_CALL_DEPTH].ival++;
  
  int32_t max_call_depth = 1000;
  if (stack[SPVM_API_C_STACK_INDEX_CALL_DEPTH].ival > max_call_depth) {
    
    error_id = SPVM_API_die(env, stack, "Deep recursion occurs. The depth of a method call must be less than %d.", max_call_depth, __func__, FILE_NAME, __LINE__);
  }
  else {
    void* method_return_basic_type = method->return_basic_type;
    int32_t method_return_type_dimension = method->return_type_dimension;
    int32_t method_return_type_flag = method->return_type_flag;
    
    SPVM_RUNTIME_BASIC_TYPE* current_basic_type = method->current_basic_type;
    
    int32_t method_return_type_is_object = SPVM_API_TYPE_is_object_type(runtime, method_return_basic_type, method_return_type_dimension, method_return_type_flag);
    int32_t no_need_call = 0;
    if (method->is_init) {
      
      if (current_basic_type->initialized) {
        no_need_call = 1;
      }
      else {
        current_basic_type->initialized = 1;
      }
    }
    
    if (!no_need_call) {
      // Call native method
      if (method->is_native) {
        // Enter scope
        int32_t original_mortal_stack_top = SPVM_API_enter_scope(env, stack);
        
        // Set argument default values
        int32_t optional_args_length = method->args_length - method->required_args_length;
        if (optional_args_length > 0) {
          
          // Operation codes
          SPVM_OPCODE* opcodes = method->opcodes;
          
          // Execute operation codes
          int32_t opcode_rel_index = 0;
          while (1) {
            
            SPVM_OPCODE* opcode = &(opcodes[opcode_rel_index]);
            
            if (opcode->id == SPVM_OPCODE_C_ID_END_ARGS) {
              break;
            }
            
            switch (opcode->id) {
              case SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_BYTE: {
                int32_t stack_index = opcode->operand3 & 0xFF;
                if (stack_index >= args_width) {
                  stack[stack_index].bval = (int8_t)(uint8_t)opcode->operand1;
                }
                break;
              }
              case SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_SHORT: {
                int32_t stack_index = opcode->operand3 & 0xFF;
                if (stack_index >= args_width) {
                  stack[stack_index].sval = (int16_t)(uint16_t)opcode->operand1;
                }
                break;
              }
              case SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_INT: {
                int32_t stack_index = opcode->operand3 & 0xFF;
                if (stack_index >= args_width) {
                  stack[stack_index].ival = (int32_t)opcode->operand1;
                }
                break;
              }
              case SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_LONG: {
                int32_t stack_index = opcode->operand3 & 0xFF;
                if (stack_index >= args_width) {
                  stack[stack_index].lval = *(int64_t*)&opcode->operand1;
                }
                break;
              }
              case SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_FLOAT: {
                int32_t stack_index = opcode->operand3 & 0xFF;
                if (stack_index >= args_width) {
                  SPVM_VALUE default_value;
                  default_value.ival = (int32_t)opcode->operand1;
                  stack[stack_index].fval = default_value.fval;
                }
                break;
              }
              case SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_DOUBLE: {
                int32_t stack_index = opcode->operand3 & 0xFF;
                if (stack_index >= args_width) {
                  stack[stack_index].dval = *(double*)&opcode->operand1;
                }
                break;
              }
              case SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_OBJECT: {
                int32_t stack_index = opcode->operand3 & 0xFF;
                if (stack_index >= args_width) {
                  stack[stack_index].oval = NULL;
                }
                break;
              }
            }
            
            opcode_rel_index++;
          }
        }
        
        // Call native subrotuine
        int32_t (*native_address)(SPVM_ENV*, SPVM_VALUE*) = method->native_address;
        assert(native_address != NULL);
        error_id = (*native_address)(env, stack);
        
        // Increment ref count of return value
        if (!error_id) {
          if (method_return_type_is_object) {
            SPVM_OBJECT* return_object = *(void**)&stack[0];
            if (return_object != NULL) {
              SPVM_API_inc_ref_count(env, stack, return_object);
            }
          }
        }
        
        // Leave scope
        SPVM_API_leave_scope(env, stack, original_mortal_stack_top);
        
        // Decrement ref count of return value
        if (!error_id) {
          if (method_return_type_is_object) {
            SPVM_OBJECT* return_object = *(void**)&stack[0];
            if (return_object != NULL) {
              SPVM_API_dec_ref_count(env, stack, return_object);
            }
          }
        }
        
        // Set default exception message
        if (error_id && SPVM_API_get_exception(env, stack) == NULL) {
          void* exception = SPVM_API_new_string_nolen_no_mortal(env, stack, "Error");
          SPVM_API_set_exception(env, stack, exception);
        }
      }
      else {
        // Call precompiled method
        void* method_precompile_address = method->precompile_address;
        if (method_precompile_address) {
          int32_t (*precompile_address)(SPVM_ENV*, SPVM_VALUE*) = method_precompile_address;
          error_id = (*precompile_address)(env, stack);
        }
        // Call sub virtual machine
        else {
          error_id = SPVM_API_call_method_vm(env, stack, method, args_width);
        }
      }
      
      if (mortal && method_return_type_is_object) {
        SPVM_API_push_mortal(env, stack, stack[0].oval);
      }
    }
  }
  
  stack[SPVM_API_C_STACK_INDEX_CALL_DEPTH].ival--;
  
  return error_id;
}

int32_t SPVM_API_push_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  
  SPVM_OBJECT*** current_mortal_stack_ptr = (SPVM_OBJECT***)&stack[SPVM_API_C_STACK_INDEX_MORTAL_STACK];
  int32_t* current_mortal_stack_top_ptr = (int32_t*)&stack[SPVM_API_C_STACK_INDEX_MORTAL_STACK_TOP];
  int32_t* current_mortal_stack_capacity_ptr = (int32_t*)&stack[SPVM_API_C_STACK_INDEX_MORTAL_STACK_CAPACITY];
  
  if (object != NULL) {
    // Extend mortal stack
    if (*current_mortal_stack_top_ptr >= *current_mortal_stack_capacity_ptr) {
      int32_t new_mortal_stack_capacity = *current_mortal_stack_capacity_ptr * 2;
      SPVM_OBJECT** new_mortal_stack = SPVM_API_new_memory_block(env, stack, sizeof(void*) * new_mortal_stack_capacity);
      if (new_mortal_stack == NULL) {
        return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
      }
      memcpy(new_mortal_stack, *current_mortal_stack_ptr, sizeof(void*) * *current_mortal_stack_capacity_ptr);
      *current_mortal_stack_capacity_ptr = new_mortal_stack_capacity;
      SPVM_API_free_memory_block(env, stack, *current_mortal_stack_ptr);
      *current_mortal_stack_ptr = NULL;
      *current_mortal_stack_ptr = new_mortal_stack;
    }
    
    SPVM_API_assign_object(env, stack, &(*current_mortal_stack_ptr)[*current_mortal_stack_top_ptr], object);
    
    *current_mortal_stack_top_ptr = *current_mortal_stack_top_ptr + 1;
  }
  
  return 0;
}

void SPVM_API_leave_scope(SPVM_ENV* env, SPVM_VALUE* stack, int32_t original_mortal_stack_top) {
  
  SPVM_OBJECT*** current_mortal_stack_ptr = (SPVM_OBJECT***)&stack[SPVM_API_C_STACK_INDEX_MORTAL_STACK];
  int32_t* current_mortal_stack_top_ptr = (int32_t*)&stack[SPVM_API_C_STACK_INDEX_MORTAL_STACK_TOP];
  int32_t* current_mortal_stack_capacity_ptr = (int32_t*)&stack[SPVM_API_C_STACK_INDEX_MORTAL_STACK_CAPACITY];
  
  int32_t mortal_stack_index;
  for (mortal_stack_index = original_mortal_stack_top; mortal_stack_index < *current_mortal_stack_top_ptr; mortal_stack_index++) {
    
    SPVM_OBJECT** object_ref = &(*current_mortal_stack_ptr)[mortal_stack_index];
    
    SPVM_API_assign_object(env, stack, object_ref, NULL);
    
  }
  
  *current_mortal_stack_top_ptr = original_mortal_stack_top;
}

void SPVM_API_leave_scope_local(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT** object_vars, int32_t* mortal_stack, int32_t* mortal_stack_top_ptr, int32_t original_mortal_stack_top) {
  
  for (int32_t mortal_stack_index = original_mortal_stack_top; mortal_stack_index < *mortal_stack_top_ptr; mortal_stack_index++) {
    int32_t var_index = mortal_stack[mortal_stack_index];
    SPVM_OBJECT** object_ref = (SPVM_OBJECT**)&object_vars[var_index];
    if (*object_ref != NULL) {
      SPVM_API_assign_object(env, stack, object_ref, NULL);
    }
  }
  *mortal_stack_top_ptr = original_mortal_stack_top;
  
}

SPVM_OBJECT* SPVM_API_get_object_no_weaken_address(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  //  Dropping weaken flag
  void* object_no_weaken_address = (void*)((intptr_t)object & ~(intptr_t)1);
  
  return object_no_weaken_address;
}

int32_t SPVM_API_isweak_only_check_flag(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT** ref) {
  int32_t isweak = (intptr_t)*ref & 1;
  return isweak;
}

int32_t SPVM_API_isweak(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT** ref) {
  SPVM_RUNTIME* runtime = env->runtime;
  
  assert(ref);
  
  if (*ref == NULL) {
    return 0;
  }
  
  SPVM_OBJECT* object = SPVM_API_get_object_no_weaken_address(env, stack, *ref);
  
  int32_t isweak = SPVM_API_isweak_only_check_flag(env, stack, ref);
  
  return isweak;
}

int32_t SPVM_API_weaken(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT** ref) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_MUTEX* runtime_mutex = runtime->mutex;
  
  SPVM_OBJECT* destroied_referent = NULL;
  {
    SPVM_MUTEX_lock(runtime_mutex);
    
    assert(ref);
    
    if (!(*ref == NULL)) {
      
      SPVM_OBJECT* object = SPVM_API_get_object_no_weaken_address(env, stack, *ref);
      
      int32_t isweak = SPVM_API_isweak_only_check_flag(env, stack, ref);
      
      if (!isweak) {
        
        int32_t ref_count = SPVM_API_get_ref_count(env, stack, object);
        
        assert(ref_count > 0);
        
        // If reference count is 1, the object is destroied
        if (ref_count == 1) {
          destroied_referent = object;
          *ref = NULL;
        }
        else {
          // Weaken is implemented by tag pointer.
          // If pointer most right bit is 1, object is weaken.
          *ref = (SPVM_OBJECT*)((intptr_t)*ref | 1);
          
          SPVM_API_dec_ref_count(env, stack, object);
          
          SPVM_WEAKEN_BACKREF* new_weaken_backref = SPVM_API_new_memory_block(env, stack, sizeof(SPVM_WEAKEN_BACKREF));
          new_weaken_backref->ref = ref;
          
          // Create a new weaken back refference
          if (object->weaken_backref_head == NULL) {
            object->weaken_backref_head = new_weaken_backref;
          }
          // Add weaken back refference
          else {
            SPVM_WEAKEN_BACKREF* weaken_backref_next = object->weaken_backref_head;
            
            while (weaken_backref_next->next != NULL){
              weaken_backref_next = weaken_backref_next->next;
            }
            weaken_backref_next->next = new_weaken_backref;
          }
        }
      }
    }
    
    SPVM_MUTEX_unlock(runtime_mutex);
  }
  
  if (destroied_referent) {
    SPVM_API_assign_object(env, stack, &destroied_referent, NULL);
  }
  
  return 0;
}

void SPVM_API_unweaken_thread_unsafe(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT** ref) {
  
  assert(ref);
  
  if (*ref == NULL) {
    return;
  }
  
  SPVM_OBJECT* object = SPVM_API_get_object_no_weaken_address(env, stack, *ref);
  
  int32_t isweak = SPVM_API_isweak_only_check_flag(env, stack, ref);
  
  if (isweak) {
    
    assert(object->weaken_backref_head);
    
    // Drop weaken flag
    *ref = (SPVM_OBJECT*)((intptr_t)*ref & ~(intptr_t)1);
    
    SPVM_API_inc_ref_count(env, stack, object);
    
    // Remove a weaken back reference
    SPVM_WEAKEN_BACKREF** weaken_backref_cur_ptr = &object->weaken_backref_head;
    
    while (*weaken_backref_cur_ptr != NULL){
      if ((*weaken_backref_cur_ptr)->ref == ref) {
        SPVM_WEAKEN_BACKREF* weaken_backref_next = (*weaken_backref_cur_ptr)->next;
        
        SPVM_WEAKEN_BACKREF* weaken_backref_cur = *weaken_backref_cur_ptr;
        
        SPVM_API_free_memory_block(env, stack, weaken_backref_cur);
        weaken_backref_cur = NULL;
        
        *weaken_backref_cur_ptr = weaken_backref_next;
        break;
      }
      weaken_backref_cur_ptr = &((*weaken_backref_cur_ptr)->next);
    }
  }
  
}

void SPVM_API_unweaken(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT** ref) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_MUTEX* runtime_mutex = runtime->mutex;
  
  {
    SPVM_MUTEX_lock(runtime_mutex);
    
    assert(ref);
    
    if (!(*ref == NULL)) {
      SPVM_OBJECT* object = SPVM_API_get_object_no_weaken_address(env, stack, *ref);
      
      SPVM_API_unweaken_thread_unsafe(env, stack, ref);
    }
    
    SPVM_MUTEX_unlock(runtime_mutex);
  }
  
}

void SPVM_API_free_weaken_backrefs(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_WEAKEN_BACKREF* weaken_backref_head) {
  
  SPVM_WEAKEN_BACKREF* weaken_backref_cur = weaken_backref_head;
  while (weaken_backref_cur != NULL){
    int32_t isweak = SPVM_API_isweak_only_check_flag(env, stack, weaken_backref_cur->ref);
    
    assert(isweak);
    
    *(weaken_backref_cur->ref) = NULL;
    
    SPVM_WEAKEN_BACKREF* weaken_backref_head_next = weaken_backref_cur->next;
    
    SPVM_API_free_memory_block(env, stack, weaken_backref_cur);
    weaken_backref_cur = NULL;
    
    weaken_backref_cur = weaken_backref_head_next;
  }
}

void SPVM_API_assign_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT** ref, SPVM_OBJECT* object) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_MUTEX* runtime_mutex = runtime->mutex;
  
  SPVM_OBJECT* released_object = NULL;
  {
    SPVM_MUTEX_lock(runtime_mutex);
    
    released_object = SPVM_API_get_object_no_weaken_address(env, stack, *ref);
    
    assert(!((intptr_t)object & 1));
    
    SPVM_API_unweaken_thread_unsafe(env, stack, ref);
    
    if (object) {
      SPVM_API_inc_ref_count(env, stack, object);
    }
    
    *ref = object;
    
    SPVM_MUTEX_unlock(runtime_mutex);
  }
  
  if (released_object) {
    int32_t do_dec_ref_count_only = 0;
    
    {
      SPVM_MUTEX_lock(runtime_mutex);
      
      int32_t released_object_ref_count = SPVM_API_get_ref_count(env, stack, released_object);
      
      assert(released_object_ref_count > 0);
      
      if (released_object_ref_count > 1) {
        SPVM_API_dec_ref_count(env, stack, released_object);
        do_dec_ref_count_only = 1;
      }
      
      SPVM_MUTEX_unlock(runtime_mutex);
    }
    
    if (!do_dec_ref_count_only) {
      // Free released_object array
      if (SPVM_API_is_object_array(env, stack, released_object)) {
        int32_t length = SPVM_API_length(env, stack, released_object);
        for (int32_t index = 0; index < length; index++) {
          SPVM_OBJECT** ref = &(((SPVM_OBJECT**)((intptr_t)released_object + SPVM_API_RUNTIME_get_object_data_offset(env->runtime)))[index]);
          SPVM_API_assign_object(env, stack, ref, NULL);
        }
      }
      // Free released_object
      else {
        SPVM_RUNTIME_BASIC_TYPE* released_object_basic_type = SPVM_API_get_object_basic_type(env, stack, released_object);
        int32_t released_object_basic_type_category = released_object_basic_type->category;
        if (released_object_basic_type_category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS) {
          // Class
          SPVM_RUNTIME* runtime = env->runtime;
          
          // Call destructor
          if (released_object_basic_type->destructor_method) {
            
            SPVM_VALUE save_stack0 = stack[0];
            SPVM_OBJECT* save_exception = SPVM_API_get_exception(env, stack);
            SPVM_OBJECT* save_exception_referent = NULL;
            SPVM_API_assign_object(env, stack, &save_exception_referent, save_exception);
            
            SPVM_RUNTIME_METHOD* destructor_method = SPVM_API_BASIC_TYPE_get_method_by_index(env->runtime, released_object_basic_type, released_object_basic_type->destructor_method->index);
            
            stack[0].oval = released_object;
            int32_t args_width = 1;
            int32_t error_id = SPVM_API_call_method_no_mortal(env, stack, destructor_method, args_width);
            
            // Exception in destructor is changed to warning
            if (error_id) {
              void* exception = SPVM_API_get_exception(env, stack);
              const char* exception_chars = SPVM_API_get_chars(env, stack, exception);
              fprintf(runtime->spvm_stderr, "[The following exception is coverted to a warning because it is thrown in the DESTROY method]\n%s\n", exception_chars);
            }
            
            // Restore stack and exception
            stack[0] = save_stack0;
            SPVM_API_set_exception(env, stack, save_exception);
            SPVM_API_assign_object(env, stack, &save_exception_referent, NULL);
          }
          
          // Free released_object fields
          int32_t released_object_fields_length = released_object_basic_type->fields_length;
          for (int32_t field_index = 0; field_index < released_object_fields_length; field_index++) {
            SPVM_RUNTIME_FIELD* field = SPVM_API_BASIC_TYPE_get_field_by_index(runtime, released_object_basic_type, field_index);
            
            void* field_basic_type = field->basic_type;
            int32_t field_type_dimension = field->type_dimension;
            int32_t field_type_flag = field->type_flag;
            int32_t field_type_is_released_object = SPVM_API_TYPE_is_object_type(runtime, field_basic_type, field_type_dimension, field_type_flag);
            
            if (field_type_is_released_object) {
              SPVM_OBJECT** ref = (SPVM_OBJECT**)((intptr_t)released_object + (size_t)SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + field->offset);
              SPVM_API_assign_object(env, stack, ref, NULL);
            }
          }
        }
      
      }
      
      {
        SPVM_MUTEX_lock(runtime_mutex);
        
        SPVM_API_dec_ref_count(env, stack, released_object);
        
        int32_t released_object_ref_count = SPVM_API_get_ref_count(env, stack, released_object);
        
        if (released_object_ref_count == 0) {
          
          // Free weak back refenreces
          if (released_object->weaken_backref_head != NULL) {
            SPVM_API_free_weaken_backrefs(env, stack, released_object->weaken_backref_head);
            released_object->weaken_backref_head = NULL;
          }
          
          // Free released_object
          SPVM_API_free_memory_block(env, stack, released_object);
          released_object = NULL;
        }
        
        SPVM_MUTEX_unlock(runtime_mutex);
      }
    }
  }
}

void SPVM_API_inc_ref_count(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  if (object != NULL) {
    int32_t ref_count = SPVM_API_get_ref_count(env, stack, object);
    assert(ref_count >= 0);
    
    SPVM_RUNTIME* runtime = env->runtime;
    
    SPVM_MUTEX* runtime_mutex_atomic = runtime->mutex_atomic;
    
    {
      SPVM_MUTEX_lock(runtime_mutex_atomic);
      object->ref_count++;
      SPVM_MUTEX_unlock(runtime_mutex_atomic);
    }
  }
}

void SPVM_API_dec_ref_count(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (object != NULL) {
    int32_t ref_count = SPVM_API_get_ref_count(env, stack, object);
    assert(ref_count > 0);
    
    SPVM_RUNTIME* runtime = env->runtime;
    
    SPVM_MUTEX* runtime_mutex_atomic = runtime->mutex_atomic;
    
    {
      SPVM_MUTEX_lock(runtime_mutex_atomic);
      object->ref_count--;
      SPVM_MUTEX_unlock(runtime_mutex_atomic);
    }
  }
  
}

int32_t SPVM_API_get_ref_count(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  int32_t ref_count = object->ref_count;
  
  return ref_count;
}

FILE* SPVM_API_spvm_stdin(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  FILE* spvm_stdin = env->api->runtime->get_spvm_stdin(env->runtime);
  
  return spvm_stdin;
}

FILE* SPVM_API_spvm_stdout(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  FILE* spvm_stdout = env->api->runtime->get_spvm_stdout(env->runtime);
  
  return spvm_stdout;
}

FILE* SPVM_API_spvm_stderr(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  FILE* spvm_stderr = env->api->runtime->get_spvm_stderr(env->runtime);
  
  return spvm_stderr;
}
