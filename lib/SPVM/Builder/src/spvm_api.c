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
#include "spvm_runtime_arg.h"
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
#include "spvm_utf8.h"
#include "spvm_type.h"
#include "spvm_runtime_call_stack_frame_info.h"
#include "spvm_toke.h"

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
    SPVM_API_set_command_info_basetime,
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
    SPVM_API_is_binary_compatible_object,
    SPVM_API_is_binary_compatible_stack,
    SPVM_API_new_stack,
    SPVM_API_free_stack,
    SPVM_API_get_field_object_defined_and_has_pointer_by_name,
    SPVM_API_get_field_object_ref,
    SPVM_API_get_field_object_ref_by_name,
    SPVM_API_check_bootstrap_method,
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
    SPVM_API_new_array_proto_element_no_mortal,
    SPVM_API_new_array_proto_element,
    SPVM_API_get_byte_object_value,
    SPVM_API_get_short_object_value,
    SPVM_API_get_int_object_value,
    SPVM_API_get_long_object_value,
    SPVM_API_get_float_object_value,
    SPVM_API_get_double_object_value,
    SPVM_API_no_free,
    SPVM_API_set_no_free,
    SPVM_API_get_stack_tmp_buffer,
    SPVM_API_print_exception_to_stderr,
    SPVM_API_dump_object_internal,
    SPVM_API_get_seed,
    SPVM_API_set_seed,
    SPVM_API_seed_initialized,
    SPVM_API_get_basic_type_name_in_version_from,
    SPVM_API_set_command_info_warning,
    SPVM_API_destroy_cache_class_vars,
    SPVM_API_new_stack_with_all_method_call_permitted,
    SPVM_API_call_instance_method_no_mortal,
    SPVM_API_call_instance_method,
    SPVM_API_call_method_no_mortal_no_check_args,
    SPVM_API_call_instance_method_no_mortal_less_check_args,
    SPVM_API_enable_options,
    SPVM_API_disable_options,
    SPVM_API_is_options,
    SPVM_API_is_any_object_array,
    SPVM_API_exists_field,
    SPVM_API_exists_field_by_name,
    SPVM_API_delete_field,
    SPVM_API_delete_field_by_name,
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

int32_t SPVM_API_call_method_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_METHOD* method, int32_t args_width) {
  
  int32_t mortal = 0;
  int32_t check_args_level = SPVM_API_C_CALL_METHOD_CHECK_ARGS_LEVEL_FULL_CHECK;
  int32_t error_id = SPVM_API_call_method_common(env, stack, method, args_width, mortal, check_args_level);
  
  return error_id;
}

int32_t SPVM_API_call_method(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_METHOD* method, int32_t args_width) {
  
  int32_t mortal = 1;
  int32_t check_args_level = SPVM_API_C_CALL_METHOD_CHECK_ARGS_LEVEL_FULL_CHECK;
  int32_t error_id = SPVM_API_call_method_common(env, stack, method, args_width, mortal, check_args_level);
  
  return error_id;
}

int32_t SPVM_API_call_method_no_mortal_no_check_args(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_METHOD* method, int32_t args_width) {
  
  int32_t mortal = 0;
  int32_t less_check_level = SPVM_API_C_CALL_METHOD_CHECK_ARGS_LEVEL_NO_CHECK;
  int32_t error_id = SPVM_API_call_method_common(env, stack, method, args_width, mortal, less_check_level);
  
  return error_id;
}

int32_t SPVM_API_call_instance_method_common(SPVM_ENV* env, SPVM_VALUE* stack, const char* method_name, int32_t args_width, int32_t mortal, int32_t check_args_level, const char* decl_args_signature) {
  
  int32_t error_id = 0;
  
  SPVM_OBJECT* object = stack[0].oval;
  
  SPVM_RUNTIME_METHOD* method = NULL;
  if (__builtin_expect(!!object, 1)) {
    method = SPVM_API_get_instance_method(env, stack, object, method_name);
    
    if (__builtin_expect(!!method, 1)) {
      if (check_args_level == SPVM_API_C_CALL_METHOD_CHECK_ARGS_LEVEL_AUTO_CHECK) {
        if (strcmp(method->args_signature, decl_args_signature) == 0) {
          check_args_level = SPVM_API_C_CALL_METHOD_CHECK_ARGS_LEVEL_NO_CHECK;
        }
      }
      
      error_id = SPVM_API_call_method_common(env, stack, method, args_width, mortal, check_args_level);
    }
    else {
      int32_t scope_id = SPVM_API_enter_scope(env, stack);
      void* obj_invocant_type_name = env->get_type_name(env, stack, object);
      const char* invocant_type_name = env->get_chars(env, stack, obj_invocant_type_name);
      
      char* tmp_buffer = env->get_stack_tmp_buffer(env, stack);
      snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_CALL_INSTANCE_METHOD_IMPLEMENT_NOT_FOUND], invocant_type_name, method_name);
      SPVM_API_leave_scope(env, stack, scope_id);
      void* exception = env->new_string_nolen_no_mortal(env, stack, tmp_buffer);
      env->set_exception(env, stack, exception);
      error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
  }
  else {
    char* tmp_buffer = env->get_stack_tmp_buffer(env, stack);
    snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_CALL_INSTANCE_METHOD_INVOCANT_UNDEF], method_name);
    void* exception = env->new_string_nolen_no_mortal(env, stack, tmp_buffer);
    env->set_exception(env, stack, exception);
    error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  
  return error_id;
}

int32_t SPVM_API_call_instance_method_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, const char* method_name, int32_t args_width) {
  
  int32_t mortal = 0;
  int32_t check_args_level = SPVM_API_C_CALL_METHOD_CHECK_ARGS_LEVEL_FULL_CHECK;
  int32_t error_id = SPVM_API_call_instance_method_common(env, stack, method_name, args_width, mortal, check_args_level, NULL);
  
  return error_id;
}

int32_t SPVM_API_call_instance_method_no_mortal_less_check_args(SPVM_ENV* env, SPVM_VALUE* stack, const char* method_name, int32_t args_width, const char* decl_args_signature) {
  
  int32_t mortal = 0;
  int32_t check_args_level = SPVM_API_C_CALL_METHOD_CHECK_ARGS_LEVEL_AUTO_CHECK;
  int32_t error_id = SPVM_API_call_instance_method_common(env, stack, method_name, args_width, mortal, check_args_level, decl_args_signature);
  
  return error_id;
}

int32_t SPVM_API_call_instance_method(SPVM_ENV* env, SPVM_VALUE* stack, const char* method_name, int32_t args_width) {
  
  int32_t mortal = 1;
  int32_t check_args_level = SPVM_API_C_CALL_METHOD_CHECK_ARGS_LEVEL_FULL_CHECK;
  int32_t error_id = SPVM_API_call_instance_method_common(env, stack, method_name, args_width, mortal, check_args_level, NULL);
  
  return error_id;
}

int32_t SPVM_API_call_method_common(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_METHOD* method, int32_t args_width, int32_t mortal, int32_t check_args_level) {
  
  int32_t error_id = 0;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  stack[SPVM_API_C_STACK_INDEX_ARGS_WIDTH].ival = args_width;
  stack[SPVM_API_C_STACK_INDEX_CALL_DEPTH].ival++;
  
  SPVM_RUNTIME_BASIC_TYPE* current_basic_type = method->current_basic_type;
  
  int32_t max_call_depth = 1000;
  if (__builtin_expect(stack[SPVM_API_C_STACK_INDEX_CALL_DEPTH].ival > max_call_depth, 0)) {
    error_id = SPVM_API_die(env, stack, "Deep recursion occurs. The depth of a method call must be less than %d.", max_call_depth, __func__, FILE_NAME, __LINE__);
    goto END_OF_FUNC;
  }
  else if (__builtin_expect(method->is_not_permitted && !stack[SPVM_API_C_STACK_INDEX_ALL_METHOD_CALL_PERMITTED].ival, 0)) {
    SPVM_API_die(env, stack, "The call to %s#%s method is not permmited.", current_basic_type->name, method->name, __func__, FILE_NAME, __LINE__);
    error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_METHOD_CALL_NOT_PERMITTED_CLASS;
    goto END_OF_FUNC;
  }
  
  if (__builtin_expect(method->is_init_method, 0)) {
    if (current_basic_type->initialized) {
      goto END_OF_FUNC;
    }
    else {
      current_basic_type->initialized = 1;
    }
  }
  
  // Set default values for optional arguments
  int32_t args_length = method->args_length;
  for (int32_t arg_index = 0; arg_index < method->args_length; arg_index++) {
    SPVM_RUNTIME_ARG* arg = &method->args[arg_index];
    
    int32_t arg_stack_index = arg->stack_index;
    if (arg_stack_index >= args_width) {
      if (arg->is_optional) {
        stack[arg_stack_index] = arg->default_value;
      }
      else {
        int32_t arg_type_width = SPVM_API_get_type_width(runtime, arg->basic_type, arg->type_dimension, arg->type_flag);
        memset(&stack[arg_stack_index], 0, sizeof(SPVM_VALUE) * arg_type_width);
      }
    }
  }
  
  if (!(check_args_level == SPVM_API_C_CALL_METHOD_CHECK_ARGS_LEVEL_NO_CHECK)) {
    if (check_args_level == SPVM_API_C_CALL_METHOD_CHECK_ARGS_LEVEL_FULL_CHECK) {
      // Do nothing
    }
    else if (check_args_level == SPVM_API_C_CALL_METHOD_CHECK_ARGS_LEVEL_AUTO_CHECK) {
      if (!method->has_object_args) {
        check_args_level = SPVM_API_C_CALL_METHOD_CHECK_ARGS_LEVEL_NO_CHECK;
      }
    }
    else {
      assert(0);
    }
    
    if (!(check_args_level == SPVM_API_C_CALL_METHOD_CHECK_ARGS_LEVEL_NO_CHECK)) {
      
      int32_t arg_index = 0;
      if (check_args_level == SPVM_API_C_CALL_METHOD_CHECK_ARGS_LEVEL_AUTO_CHECK && !method->is_class_method) {
        arg_index = 1;
      }
      for (; arg_index < method->args_length; arg_index++) {
        SPVM_RUNTIME_ARG* arg = &method->args[arg_index];
        
        int32_t arg_stack_index = arg->stack_index;
        if (arg_stack_index < args_width) {
          int32_t arg_is_object_type = SPVM_API_is_object_type(env->runtime, arg->basic_type, arg->type_dimension, arg->type_flag);
          if (arg_is_object_type) {
            SPVM_OBJECT* obj_arg = stack[arg_stack_index].oval;
            
            if (obj_arg) {
              int32_t can_assign = SPVM_API_isa(env, stack, obj_arg, arg->basic_type, arg->type_dimension);
              if (!can_assign) {
                int32_t arg_index_nth = method->is_class_method ? arg_index + 1 : arg_index;
                
                error_id = SPVM_API_die(env, stack, "The %ith argument must be assigned to the type of %ith argument of %s#%s method.", arg_index_nth, arg_index_nth, current_basic_type->name, method->name, __func__, FILE_NAME, __LINE__);
                goto END_OF_FUNC;
              }
            }
          }
        }
      }
    }
  }
  
  if (method->is_native) {
    error_id = SPVM_API_call_method_native(env, stack, method, args_width);
    if (error_id) {
      goto END_OF_FUNC;
    }
  }
  else if (method->is_precompile) {
    void* method_precompile_address = method->precompile_address;
    if (method_precompile_address) {
      int32_t (*precompile_address)(SPVM_ENV*, SPVM_VALUE*) = method_precompile_address;
      error_id = (*precompile_address)(env, stack);
      if (error_id) {
        goto END_OF_FUNC;
      }
    }
    else if (method->is_precompile_fallback) {
      error_id = SPVM_VM_call_method(env, stack, method, args_width);
      if (error_id) {
        goto END_OF_FUNC;
      }
    }
    else {
      error_id = SPVM_API_die(env, stack, "The execution address of %s#%s precompile method must not be NULL. Loading the dynamic link library maybe failed.", method->current_basic_type->name, method->name, __func__, FILE_NAME, __LINE__);
      goto END_OF_FUNC;
    }
  }
  else {
    error_id = SPVM_VM_call_method(env, stack, method, args_width);
    if (__builtin_expect(error_id, 0)) {
      goto END_OF_FUNC;
    }
  }
  
  if (__builtin_expect(mortal, 0)) {
    void* method_return_basic_type = method->return_basic_type;
    int32_t method_return_type_dimension = method->return_type_dimension;
    int32_t method_return_type_flag = method->return_type_flag;
    int32_t method_return_type_is_object = SPVM_API_is_object_type(runtime, method_return_basic_type, method_return_type_dimension, method_return_type_flag);
    
    if (method_return_type_is_object) {
      SPVM_API_push_mortal(env, stack, stack[0].oval);
    }
  }
  
  END_OF_FUNC:
  
  if (method->return_type_is_void) {
    stack[0].oval = NULL;
  }
  
  stack[SPVM_API_C_STACK_INDEX_CALL_DEPTH].ival--;
  
  return error_id;
}

int32_t SPVM_API_call_method_native(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_METHOD* method, int32_t args_width) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  int32_t error_id = 0;
  
  // Call native method
  int32_t (*native_address)(SPVM_ENV*, SPVM_VALUE*) = method->native_address;
  if (__builtin_expect(!native_address, 0)) {
    error_id = SPVM_API_die(env, stack, "The execution address of %s#%s native method must not be NULL. Loading the dynamic link library maybe failed.", method->current_basic_type->name, method->name, __func__, FILE_NAME, __LINE__);
    goto END_OF_FUNC;
  }
  
  int32_t native_mortal_stack_top = SPVM_API_enter_scope(env, stack);
  
  error_id = (*native_address)(env, stack);
  
  int32_t method_return_type_is_object = method->return_type_is_object;
  
  // Increment ref count of return value
  if (__builtin_expect(!error_id, 1)) {
    if (method_return_type_is_object) {
      SPVM_OBJECT* return_object = *(SPVM_OBJECT**)&stack[0];
      if (return_object != NULL) {
        SPVM_API_inc_ref_count(env, stack, return_object);
      }
    }
  }
  
  if (*(int32_t*)&stack[SPVM_API_C_STACK_INDEX_MORTAL_STACK_LENGTH] > native_mortal_stack_top) {
    SPVM_API_leave_scope(env, stack, native_mortal_stack_top);
  }
  
  // Decrement ref count of return value
  if (__builtin_expect(!error_id, 1)) {
    if (method_return_type_is_object) {
      SPVM_OBJECT* return_object = *(SPVM_OBJECT**)&stack[0];
      if (return_object != NULL) {
        SPVM_API_dec_ref_count(env, stack, return_object);
      }
    }
  }
  
  END_OF_FUNC:
  
  // Set an default exception message
  if (__builtin_expect(error_id, 0)) {
    if (SPVM_API_get_exception(env, stack) == NULL) {
      void* exception = SPVM_API_new_string_nolen_no_mortal(env, stack, "Error");
      SPVM_API_set_exception(env, stack, exception);
    }
  }
  
  return error_id;
}

void SPVM_API_call_class_method_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* method_name, int32_t args_width, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  
  if (!basic_type) {
    *error_id = SPVM_API_die(env, stack, "%s class is not found.", basic_type_name, func_name, file, line);
    return;
  }
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_BASIC_TYPE_get_method_by_name(env->runtime, basic_type, method_name);
  
  if (!method) {
    *error_id = SPVM_API_die(env, stack, "%s#%s method is not found.", basic_type_name, method_name, func_name, file, line);
    return;
  }
  
  if (!method->is_class_method) {
    *error_id = SPVM_API_die(env, stack, "%s#%s method must be a class method.", basic_type_name, method_name, func_name, file, line);
    return;
  }
  
  *error_id = SPVM_API_call_method(env, stack, method, args_width);
  
  if (*error_id) {
    const char* message = SPVM_API_get_chars(env, stack, SPVM_API_get_exception(env, stack));
    SPVM_API_die(env, stack, "%s", message, func_name, file, line);
  }
}

void SPVM_API_call_instance_method_static_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* method_name, int32_t args_width, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  
  if (!basic_type) {
    *error_id = SPVM_API_die(env, stack, "%s class is not found.", basic_type_name, func_name, file, line);
    return;
  }
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_BASIC_TYPE_get_method_by_name(env->runtime, basic_type, method_name);
  
  if (!method) {
    *error_id = SPVM_API_die(env, stack, "%s#%s method is not found.", basic_type_name, method_name, func_name, file, line);
    return;
  }
  
  if (method->is_class_method) {
    *error_id = SPVM_API_die(env, stack, "%s#%s method must be an instance method.", basic_type_name, method_name, func_name, file, line);
    return;
  }
  
  SPVM_OBJECT* object = stack[0].oval;
  
  if (!object) {
    *error_id = SPVM_API_die(env, stack, "The invocant must be defined.", func_name, file, line);
    return;
  };
  
  if (!SPVM_API_isa(env, stack, object, basic_type, 0)) {
    *error_id = SPVM_API_die(env, stack, "The invocant must be assigned to %s class.", basic_type_name, func_name, file, line);
    return;
  };
  
  *error_id = SPVM_API_call_method(env, stack, method, args_width);
  
  if (*error_id) {
    const char* message = SPVM_API_get_chars(env, stack, SPVM_API_get_exception(env, stack));
    SPVM_API_die(env, stack, "%s", message, func_name, file, line);
  }
}

void SPVM_API_call_instance_method_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* method_name, int32_t args_width, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = SPVM_API_call_instance_method(env, stack, method_name, args_width);
  
  if (*error_id) {
    const char* message = SPVM_API_get_chars(env, stack, SPVM_API_get_exception(env, stack));
    SPVM_API_die(env, stack, "%s", message, func_name, file, line);
  }
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
      error_id = SPVM_API_call_method(env, stack, init_method, args_width);
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

int32_t SPVM_API_set_command_info_basetime(SPVM_ENV* env, SPVM_VALUE* stack, int64_t basetime) {
  
  int32_t error_id = 0;
  
  SPVM_API_set_class_var_long_by_name(env, stack, "CommandInfo", "$BASETIME", basetime, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

static void SPVM_API_destroy_class_vars_common(SPVM_ENV* env, SPVM_VALUE* stack, int32_t only_cache){

  SPVM_RUNTIME* runtime = env->runtime;
  
  for (int32_t basic_type_id = 0; basic_type_id < runtime->basic_types_length; basic_type_id++) {
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type_by_id(env->runtime, basic_type_id);
    
    for (int32_t class_var_index = 0; class_var_index < basic_type->class_vars_length; class_var_index++) {
      
      SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_BASIC_TYPE_get_class_var_by_index(runtime, basic_type, class_var_index);
      
      SPVM_RUNTIME_BASIC_TYPE* class_var_basic_type = class_var->basic_type;
      int32_t class_var_type_dimension = class_var->type_dimension;
      int32_t class_var_type_flag = class_var->type_flag;
      int32_t class_var_is_cache = class_var->is_cache;
      int32_t class_var_type_is_object = SPVM_API_is_object_type(runtime, class_var_basic_type, class_var_type_dimension, class_var_type_flag);
      
      int32_t do_free = 0;
      if (only_cache) {
        if (class_var_is_cache) {
          do_free = 1;
        }
      }
      else {
        do_free = 1;
      }
      
      if (do_free) {
        if (class_var_type_is_object) {
          SPVM_OBJECT** ref = (SPVM_OBJECT**)&class_var->data;
          SPVM_API_assign_object(env, stack, ref, NULL);
        }
      }
    }
  }
}

void SPVM_API_destroy_class_vars(SPVM_ENV* env, SPVM_VALUE* stack){
  
  int32_t only_cache = 0;
  SPVM_API_destroy_class_vars_common(env, stack, only_cache);
}

void SPVM_API_destroy_cache_class_vars(SPVM_ENV* env, SPVM_VALUE* stack){

  int32_t only_cache = 1;
  SPVM_API_destroy_class_vars_common(env, stack, only_cache);
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
  
  if (!basic_type_name) {
    return NULL;
  }
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type_by_name(runtime, basic_type_name);
  
  return basic_type;
}

void* SPVM_API_new_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  void* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    *error_id = SPVM_API_die(env, stack, "%s class is not found.", basic_type_name, func_name, file, line);
    return NULL;
  };
  
  void* object = SPVM_API_new_object(env, stack, basic_type);
  
  if (!object) {
    *error_id = SPVM_API_die(env, stack, "The creation of the object of %s class failed.", basic_type_name, func_name, file, line);
    return NULL;
  }
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_pointer_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, void* pointer, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  void* object = SPVM_API_new_object_by_name(env, stack, basic_type_name, error_id, func_name, file, line);
  
  if (object) {
    SPVM_API_set_pointer(env, stack, object, pointer);
  }
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_object_array_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t length, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  void* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    *error_id = SPVM_API_die(env, stack, "%s class is not found.", basic_type_name, func_name, file, line);
    return NULL;
  };
  
  void* array = SPVM_API_new_object_array(env, stack, basic_type, length);
  
  if (!array) {
    *error_id = SPVM_API_die(env, stack, "The creation of the array of %s class failed.", basic_type_name, func_name, file, line);
    return NULL;
  }
  
  return array;
}

SPVM_OBJECT* SPVM_API_new_muldim_array_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t type_dimension, int32_t length, int32_t* error_id, const char* func_name, const char* file, int32_t line) {  *error_id = 0;
  
  void* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    *error_id = SPVM_API_die(env, stack, "%s class is not found.", basic_type_name, func_name, file, line);
    return NULL;
  };
  
  void* object = SPVM_API_new_muldim_array(env, stack, basic_type, type_dimension, length);
  
  if (!object) {
    *error_id = SPVM_API_die(env, stack, "The creation of the multi-dimensional array of %s class with the dimension %d failed.", basic_type_name, type_dimension, func_name, file, line);
    return NULL;
  }
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_mulnum_array_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t length, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  void* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    *error_id = SPVM_API_die(env, stack, "%s class is not found.", basic_type_name, func_name, file, line);
    return NULL;
  };
  
  void* array = SPVM_API_new_mulnum_array(env, stack, basic_type, length);
  
  if (!array) {
    *error_id = SPVM_API_die(env, stack, "The creation of the multi-numeric array of %s class failed.", basic_type_name, func_name, file, line);
    return NULL;
  }
  
  return array;
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
  SPVM_OBJECT* value = SPVM_API_drop_tag_pointers(env, stack, value_maybe_weaken);
  
  return value;
}

SPVM_OBJECT** SPVM_API_get_class_var_object_ref(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var) {
  
  assert(class_var);
  
  SPVM_OBJECT** ref = (SPVM_OBJECT**)&class_var->data.oval;
  
  return ref;
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
  
  SPVM_OBJECT** ref = (SPVM_OBJECT**)&class_var->data.oval;
  SPVM_API_assign_object(env, stack, ref, value);
}

void SPVM_API_set_class_var_string(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var, SPVM_OBJECT* value) {
  
  assert(class_var);
  
  SPVM_API_set_class_var_object(env, stack, class_var, value);
}

int8_t SPVM_API_get_class_var_byte_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    *error_id = SPVM_API_die(env, stack, "%s class is not found.", basic_type_name, func_name, file, line);
    return 0;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_BASIC_TYPE_get_class_var_by_name(env->runtime, basic_type, class_var_name);
  if (!class_var) {
    *error_id = SPVM_API_die(env, stack, "$%s#%s class variable is not found.", basic_type_name, class_var_name + 1, func_name, file, line);
    return 0;
  };
  
  int32_t is_numeric_type = SPVM_API_is_numeric_type(runtime, class_var->basic_type, class_var->type_dimension, class_var->type_flag);
  
  int32_t is_invalid_type = 0;
  
  int8_t value = 0;
  if (is_numeric_type) {
    switch (class_var->basic_type->id) {
      case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE : {
        value = SPVM_API_get_class_var_byte(env, stack, class_var);
        break;
      }
      default : {
        is_invalid_type = 1;
      }
    }
  }
  else {
    is_invalid_type = 1;
  }
  
  if (is_invalid_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the class variable must be byte type.", func_name, file, line);
    return 0;
  }
  
  return value;
}

int16_t SPVM_API_get_class_var_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    *error_id = SPVM_API_die(env, stack, "%s class is not found.", basic_type_name, func_name, file, line);
    return 0;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_BASIC_TYPE_get_class_var_by_name(env->runtime, basic_type, class_var_name);
  if (!class_var) {
    *error_id = SPVM_API_die(env, stack, "$%s#%s class variable is not found.", basic_type_name, class_var_name + 1, func_name, file, line);
    return 0;
  };
  
  int32_t is_numeric_type = SPVM_API_is_numeric_type(runtime, class_var->basic_type, class_var->type_dimension, class_var->type_flag);
  
  int32_t is_invalid_type = 0;
  
  int16_t value = 0;
  if (is_numeric_type) {
    switch (class_var->basic_type->id) {
      case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE : {
        value = SPVM_API_get_class_var_byte(env, stack, class_var);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT : {
        value = SPVM_API_get_class_var_short(env, stack, class_var);
        break;
      }
      default : {
        is_invalid_type = 1;
      }
    }
  }
  else {
    is_invalid_type = 1;
  }
  
  if (is_invalid_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the class variable must be short type or smaller numeric type.", func_name, file, line);
    return 0;
  }
  
  return value;
}

int32_t SPVM_API_get_class_var_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    *error_id = SPVM_API_die(env, stack, "%s class is not found.", basic_type_name, func_name, file, line);
    return 0;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_BASIC_TYPE_get_class_var_by_name(env->runtime, basic_type, class_var_name);
  if (!class_var) {
    *error_id = SPVM_API_die(env, stack, "$%s#%s class variable is not found.", basic_type_name, class_var_name + 1, func_name, file, line);
    return 0;
  };
  
  int32_t is_numeric_type = SPVM_API_is_numeric_type(runtime, class_var->basic_type, class_var->type_dimension, class_var->type_flag);
  
  int32_t is_invalid_type = 0;
  
  int32_t value = 0;
  if (is_numeric_type) {
    switch (class_var->basic_type->id) {
      case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE : {
        value = SPVM_API_get_class_var_byte(env, stack, class_var);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT : {
        value = SPVM_API_get_class_var_short(env, stack, class_var);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_INT : {
        value = SPVM_API_get_class_var_int(env, stack, class_var);
        break;
      }
      default : {
        is_invalid_type = 1;
      }
    }
  }
  else {
    is_invalid_type = 1;
  }
  
  if (is_invalid_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the class variable must be int type or smaller numeric type.", func_name, file, line);
    return 0;
  }
  
  return value;
}

int64_t SPVM_API_get_class_var_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    *error_id = SPVM_API_die(env, stack, "%s class is not found.", basic_type_name, func_name, file, line);
    return 0;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_BASIC_TYPE_get_class_var_by_name(env->runtime, basic_type, class_var_name);
  if (!class_var) {
    *error_id = SPVM_API_die(env, stack, "$%s#%s class variable is not found.", basic_type_name, class_var_name + 1, func_name, file, line);
    return 0;
  };
  
  int32_t is_numeric_type = SPVM_API_is_numeric_type(runtime, class_var->basic_type, class_var->type_dimension, class_var->type_flag);
  
  int32_t is_invalid_type = 0;
  
  int64_t value = 0;
  if (is_numeric_type) {
    switch (class_var->basic_type->id) {
      case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE : {
        value = SPVM_API_get_class_var_byte(env, stack, class_var);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT : {
        value = SPVM_API_get_class_var_short(env, stack, class_var);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_INT : {
        value = SPVM_API_get_class_var_int(env, stack, class_var);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG : {
        value = SPVM_API_get_class_var_long(env, stack, class_var);
        break;
      }
      default : {
        is_invalid_type = 1;
      }
    }
  }
  else {
    is_invalid_type = 1;
  }
  
  if (is_invalid_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the class variable must be long type or smaller numeric type.", func_name, file, line);
    return 0;
  }
  
  return value;
}

float SPVM_API_get_class_var_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    *error_id = SPVM_API_die(env, stack, "%s class is not found.", basic_type_name, func_name, file, line);
    return 0;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_BASIC_TYPE_get_class_var_by_name(env->runtime, basic_type, class_var_name);
  if (!class_var) {
    *error_id = SPVM_API_die(env, stack, "$%s#%s class variable is not found.", basic_type_name, class_var_name + 1, func_name, file, line);
    return 0;
  };
  
  int32_t is_numeric_type = SPVM_API_is_numeric_type(runtime, class_var->basic_type, class_var->type_dimension, class_var->type_flag);
  
  int32_t is_invalid_type = 0;
  
  float value = 0;
  if (is_numeric_type) {
    switch (class_var->basic_type->id) {
      case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE : {
        value = SPVM_API_get_class_var_byte(env, stack, class_var);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT : {
        value = SPVM_API_get_class_var_short(env, stack, class_var);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_INT : {
        value = SPVM_API_get_class_var_int(env, stack, class_var);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG : {
        value = SPVM_API_get_class_var_long(env, stack, class_var);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT : {
        value = SPVM_API_get_class_var_float(env, stack, class_var);
        break;
      }
      default : {
        is_invalid_type = 1;
      }
    }
  }
  else {
    is_invalid_type = 1;
  }
  
  if (is_invalid_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the class variable must be float type or smaller numeric type.", func_name, file, line);
    return 0;
  }
  
  return value;
}

double SPVM_API_get_class_var_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    *error_id = SPVM_API_die(env, stack, "%s class is not found.", basic_type_name, func_name, file, line);
    return 0;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_BASIC_TYPE_get_class_var_by_name(env->runtime, basic_type, class_var_name);
  if (!class_var) {
    *error_id = SPVM_API_die(env, stack, "$%s#%s class variable is not found.", basic_type_name, class_var_name + 1, func_name, file, line);
    return 0;
  };
  
  int32_t is_numeric_type = SPVM_API_is_numeric_type(runtime, class_var->basic_type, class_var->type_dimension, class_var->type_flag);
  
  int32_t is_invalid_type = 0;
  
  double value = 0;
  if (is_numeric_type) {
    switch (class_var->basic_type->id) {
      case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE : {
        value = SPVM_API_get_class_var_byte(env, stack, class_var);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT : {
        value = SPVM_API_get_class_var_short(env, stack, class_var);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_INT : {
        value = SPVM_API_get_class_var_int(env, stack, class_var);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG : {
        value = SPVM_API_get_class_var_long(env, stack, class_var);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT : {
        value = SPVM_API_get_class_var_float(env, stack, class_var);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE : {
        value = SPVM_API_get_class_var_double(env, stack, class_var);
        break;
      }
      default : {
        is_invalid_type = 1;
      }
    }
  }
  else {
    is_invalid_type = 1;
  }
  
  if (is_invalid_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the class variable must be double type or smaller numeric type.", func_name, file, line);
    return 0;
  }
  
  return value;
}

SPVM_OBJECT* SPVM_API_get_class_var_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    *error_id = SPVM_API_die(env, stack, "%s class is not found.", basic_type_name, func_name, file, line);
    return 0;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_BASIC_TYPE_get_class_var_by_name(env->runtime, basic_type, class_var_name);
  if (!class_var) {
    *error_id = SPVM_API_die(env, stack, "$%s#%s class variable is not found.", basic_type_name, class_var_name + 1, func_name, file, line);
    return 0;
  };
  
  int32_t is_object_type = SPVM_API_is_object_type(runtime, class_var->basic_type, class_var->type_dimension, class_var->type_flag);
  
  int32_t is_invalid_type = 0;
  
  void* value = 0;
  if (is_object_type) {
    value = SPVM_API_get_class_var_object(env, stack, class_var);
  }
  else {
    is_invalid_type = 1;
  }
  
  if (is_invalid_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the class variable must be an object type.", func_name, file, line);
    return 0;
  }
  
  return value;
}

SPVM_OBJECT* SPVM_API_get_class_var_string_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  return SPVM_API_get_class_var_object_by_name(env, stack, basic_type_name, class_var_name, error_id, func_name, file, line);
}

void SPVM_API_set_class_var_byte_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int8_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    *error_id = SPVM_API_die(env, stack, "%s class is not found.", basic_type_name, func_name, file, line);
    return;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_BASIC_TYPE_get_class_var_by_name(env->runtime, basic_type, class_var_name);
  if (!class_var) {
    *error_id = SPVM_API_die(env, stack, "$%s#%s class variable is not found.", basic_type_name, class_var_name + 1, func_name, file, line);
    return;
  };
  
  int32_t is_numeric_type = SPVM_API_is_numeric_type(runtime, class_var->basic_type, class_var->type_dimension, class_var->type_flag);
  
  int32_t is_invalid_type = 0;
  
  if (is_numeric_type) {
    switch (class_var->basic_type->id) {
      case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE : {
        SPVM_API_set_class_var_byte(env, stack, class_var, value);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT : {
        SPVM_API_set_class_var_short(env, stack, class_var, value);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_INT : {
        SPVM_API_set_class_var_int(env, stack, class_var, value);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG : {
        SPVM_API_set_class_var_long(env, stack, class_var, value);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT : {
        SPVM_API_set_class_var_float(env, stack, class_var, value);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE : {
        SPVM_API_set_class_var_double(env, stack, class_var, value);
        break;
      }
      default : {
        is_invalid_type = 1;
      }
    }
  }
  else {
    is_invalid_type = 1;
  }
  
  if (is_invalid_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the class variable must be byte or larger numeric type.", func_name, file, line);
    return;
  }
}

void SPVM_API_set_class_var_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int16_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    *error_id = SPVM_API_die(env, stack, "%s class is not found.", basic_type_name, func_name, file, line);
    return;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_BASIC_TYPE_get_class_var_by_name(env->runtime, basic_type, class_var_name);
  if (!class_var) {
    *error_id = SPVM_API_die(env, stack, "$%s#%s class variable is not found.", basic_type_name, class_var_name + 1, func_name, file, line);
    return;
  };
  
  int32_t is_numeric_type = SPVM_API_is_numeric_type(runtime, class_var->basic_type, class_var->type_dimension, class_var->type_flag);
  
  int32_t is_invalid_type = 0;
  
  if (is_numeric_type) {
    switch (class_var->basic_type->id) {
      case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT : {
        SPVM_API_set_class_var_short(env, stack, class_var, value);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_INT : {
        SPVM_API_set_class_var_int(env, stack, class_var, value);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG : {
        SPVM_API_set_class_var_long(env, stack, class_var, value);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT : {
        SPVM_API_set_class_var_float(env, stack, class_var, value);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE : {
        SPVM_API_set_class_var_double(env, stack, class_var, value);
        break;
      }
      default : {
        is_invalid_type = 1;
      }
    }
  }
  else {
    is_invalid_type = 1;
  }
  
  if (is_invalid_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the class variable must be short or larger numeric type.", func_name, file, line);
    return;
  }
}

void SPVM_API_set_class_var_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    *error_id = SPVM_API_die(env, stack, "%s class is not found.", basic_type_name, func_name, file, line);
    return;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_BASIC_TYPE_get_class_var_by_name(env->runtime, basic_type, class_var_name);
  if (!class_var) {
    *error_id = SPVM_API_die(env, stack, "$%s#%s class variable is not found.", basic_type_name, class_var_name + 1, func_name, file, line);
    return;
  };
  
  int32_t is_numeric_type = SPVM_API_is_numeric_type(runtime, class_var->basic_type, class_var->type_dimension, class_var->type_flag);
  
  int32_t is_invalid_type = 0;
  
  if (is_numeric_type) {
    switch (class_var->basic_type->id) {
      case SPVM_NATIVE_C_BASIC_TYPE_ID_INT : {
        SPVM_API_set_class_var_int(env, stack, class_var, value);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG : {
        SPVM_API_set_class_var_long(env, stack, class_var, value);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT : {
        SPVM_API_set_class_var_float(env, stack, class_var, value);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE : {
        SPVM_API_set_class_var_double(env, stack, class_var, value);
        break;
      }
      default : {
        is_invalid_type = 1;
      }
    }
  }
  else {
    is_invalid_type = 1;
  }
  
  if (is_invalid_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the class variable must be int or larger numeric type.", func_name, file, line);
    return;
  }
}

void SPVM_API_set_class_var_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int64_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    *error_id = SPVM_API_die(env, stack, "%s class is not found.", basic_type_name, func_name, file, line);
    return;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_BASIC_TYPE_get_class_var_by_name(env->runtime, basic_type, class_var_name);
  if (!class_var) {
    *error_id = SPVM_API_die(env, stack, "$%s#%s class variable is not found.", basic_type_name, class_var_name + 1, func_name, file, line);
    return;
  };
  
  int32_t is_numeric_type = SPVM_API_is_numeric_type(runtime, class_var->basic_type, class_var->type_dimension, class_var->type_flag);
  
  int32_t is_invalid_type = 0;
  
  if (is_numeric_type) {
    switch (class_var->basic_type->id) {
      case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG : {
        SPVM_API_set_class_var_long(env, stack, class_var, value);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT : {
        SPVM_API_set_class_var_float(env, stack, class_var, value);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE : {
        SPVM_API_set_class_var_double(env, stack, class_var, value);
        break;
      }
      default : {
        is_invalid_type = 1;
      }
    }
  }
  else {
    is_invalid_type = 1;
  }
  
  if (is_invalid_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the class variable must be long or larger numeric type.", func_name, file, line);
    return;
  }
}

void SPVM_API_set_class_var_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, float value, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    *error_id = SPVM_API_die(env, stack, "%s class is not found.", basic_type_name, func_name, file, line);
    return;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_BASIC_TYPE_get_class_var_by_name(env->runtime, basic_type, class_var_name);
  if (!class_var) {
    *error_id = SPVM_API_die(env, stack, "$%s#%s class variable is not found.", basic_type_name, class_var_name + 1, func_name, file, line);
    return;
  };
  
  int32_t is_numeric_type = SPVM_API_is_numeric_type(runtime, class_var->basic_type, class_var->type_dimension, class_var->type_flag);
  
  int32_t is_invalid_type = 0;
  
  if (is_numeric_type) {
    switch (class_var->basic_type->id) {
      case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT : {
        SPVM_API_set_class_var_float(env, stack, class_var, value);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE : {
        SPVM_API_set_class_var_double(env, stack, class_var, value);
        break;
      }
      default : {
        is_invalid_type = 1;
      }
    }
  }
  else {
    is_invalid_type = 1;
  }
  
  if (is_invalid_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the class variable must be float or larger numeric type.", func_name, file, line);
    return;
  }
}

void SPVM_API_set_class_var_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, double value, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    *error_id = SPVM_API_die(env, stack, "%s class is not found.", basic_type_name, func_name, file, line);
    return;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_BASIC_TYPE_get_class_var_by_name(env->runtime, basic_type, class_var_name);
  if (!class_var) {
    *error_id = SPVM_API_die(env, stack, "$%s#%s class variable is not found.", basic_type_name, class_var_name + 1, func_name, file, line);
    return;
  };
  
  int32_t is_numeric_type = SPVM_API_is_numeric_type(runtime, class_var->basic_type, class_var->type_dimension, class_var->type_flag);
  
  int32_t is_invalid_type = 0;
  
  if (is_numeric_type) {
    switch (class_var->basic_type->id) {
      case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE : {
        SPVM_API_set_class_var_double(env, stack, class_var, value);
        break;
      }
      default : {
        is_invalid_type = 1;
      }
    }
  }
  else {
    is_invalid_type = 1;
  }
  
  if (is_invalid_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the class variable must be double type.", func_name, file, line);
    return;
  }
}

void SPVM_API_set_class_var_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, SPVM_OBJECT* value, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    *error_id = SPVM_API_die(env, stack, "%s class is not found.", basic_type_name, func_name, file, line);
    return;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_BASIC_TYPE_get_class_var_by_name(env->runtime, basic_type, class_var_name);
  if (!class_var) {
    *error_id = SPVM_API_die(env, stack, "$%s#%s class variable is not found.", basic_type_name, class_var_name + 1, func_name, file, line);
    return;
  };
  
  int32_t is_object_type = SPVM_API_is_object_type(runtime, class_var->basic_type, class_var->type_dimension, class_var->type_flag);
  
  int32_t is_invalid_type = 0;
  
  if (is_object_type) {
    SPVM_API_set_class_var_object(env, stack, class_var, value);
  }
  else {
    is_invalid_type = 1;
  }
  
  if (is_invalid_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the class variable must be an object type.", func_name, file, line);
    return;
  }
}

void SPVM_API_set_class_var_string_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, SPVM_OBJECT* value, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  SPVM_API_set_class_var_object_by_name(env, stack, basic_type_name, class_var_name, value, error_id, func_name, file, line);
}

int8_t SPVM_API_get_field_byte(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field) {
  
  int8_t value = *(int8_t*)(GET_DATA_ADDRESS(env, object) + field->offset);
  
  return value;
}

int16_t SPVM_API_get_field_short(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field) {
  
  int16_t value = *(int16_t*)(GET_DATA_ADDRESS(env, object) + field->offset);
  
  return value;
}

int32_t SPVM_API_get_field_int(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field) {
  
  int32_t value = *(int32_t*)(GET_DATA_ADDRESS(env, object) + field->offset);
  
  return value;
}

int64_t SPVM_API_get_field_long(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field) {
  
  int64_t value = *(int64_t*)(GET_DATA_ADDRESS(env, object) + field->offset);
  
  return value;
}

float SPVM_API_get_field_float(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field) {
  
  float value = *(float*)(GET_DATA_ADDRESS(env, object) + field->offset);
  
  return value;
}

double SPVM_API_get_field_double(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field) {
  
  double value = *(double*)(GET_DATA_ADDRESS(env, object) + field->offset);
  
  return value;
}

SPVM_OBJECT* SPVM_API_get_field_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field) {
  
  SPVM_OBJECT* value_maybe_weaken = *(SPVM_OBJECT**)(GET_DATA_ADDRESS(env, object) + field->offset);
  SPVM_OBJECT* value = SPVM_API_drop_tag_pointers(env, stack, value_maybe_weaken);
  
  return value;
}

SPVM_OBJECT** SPVM_API_get_field_object_ref(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field) {
  
  SPVM_OBJECT** ref = (SPVM_OBJECT**)(GET_DATA_ADDRESS(env, object) + field->offset);
  
  return ref;
}

SPVM_OBJECT* SPVM_API_get_field_string(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field) {
  
  SPVM_OBJECT* value = SPVM_API_get_field_object(env, stack, object, field);
  
  return value;
}

void SPVM_API_set_field_byte(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field, int8_t value) {
  
  *(int8_t*)(GET_DATA_ADDRESS(env, object) + field->offset) = value;
  SPVM_IMPLEMENT_ENABLE_EXISTS_FLAG(env, stack, object, field->exists_offset, field->exists_bit);
}

void SPVM_API_set_field_short(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field, int16_t value) {
  
  *(int16_t*)(GET_DATA_ADDRESS(env, object) + field->offset) = value;
  SPVM_IMPLEMENT_ENABLE_EXISTS_FLAG(env, stack, object, field->exists_offset, field->exists_bit);
}

void SPVM_API_set_field_int(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field, int32_t value) {
  
  *(int32_t*)(GET_DATA_ADDRESS(env, object) + field->offset) = value;
  SPVM_IMPLEMENT_ENABLE_EXISTS_FLAG(env, stack, object, field->exists_offset, field->exists_bit);
}

void SPVM_API_set_field_long(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field, int64_t value) {
  
  *(int64_t*)(GET_DATA_ADDRESS(env, object) + field->offset) = value;
  SPVM_IMPLEMENT_ENABLE_EXISTS_FLAG(env, stack, object, field->exists_offset, field->exists_bit);
}

void SPVM_API_set_field_float(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field, float value) {
  
  *(float*)(GET_DATA_ADDRESS(env, object) + field->offset) = value;
  SPVM_IMPLEMENT_ENABLE_EXISTS_FLAG(env, stack, object, field->exists_offset, field->exists_bit);
}

void SPVM_API_set_field_double(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field, double value) {
  
  *(double*)(GET_DATA_ADDRESS(env, object) + field->offset) = value;
  SPVM_IMPLEMENT_ENABLE_EXISTS_FLAG(env, stack, object, field->exists_offset, field->exists_bit);
}

void SPVM_API_set_field_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field, SPVM_OBJECT* value) {
  
  SPVM_OBJECT** ref = (SPVM_OBJECT**)(GET_DATA_ADDRESS(env, object) + field->offset);
  
  SPVM_API_assign_object(env, stack, ref, value);
  SPVM_IMPLEMENT_ENABLE_EXISTS_FLAG(env, stack, object, field->exists_offset, field->exists_bit);
}

void SPVM_API_set_field_string(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field, SPVM_OBJECT* value) {
  
  SPVM_API_set_field_object(env, stack, object, field, value);
}

int8_t SPVM_API_get_field_byte_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (object == NULL) {
    *error_id = SPVM_API_die(env, stack, "The object must be defined.", func_name, file, line);
    return 0;
  };
  
  SPVM_RUNTIME_BASIC_TYPE* object_basic_type = object->basic_type;
  
  int32_t object_type_dimension = object->type_dimension;
  
  int32_t object_is_class_type = SPVM_API_is_class_type(runtime, object_basic_type, object_type_dimension, 0);
  
  if (!object_is_class_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the invocant must be a class type.", func_name, file, line);
    return 0;
  };
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  if (!field) {
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    *error_id = SPVM_API_die(env, stack, "%s#%s field is not found in the class or its super classes.", basic_type_name, field_name, func_name, file, line);
    return 0;
  };
  
  int32_t is_numeric_type = SPVM_API_is_numeric_type(runtime, field->basic_type, field->type_dimension, field->type_flag);
  
  int32_t is_invalid_type = 0;
  
  int8_t value = 0;
  if (is_numeric_type) {
    switch (field->basic_type->id) {
      case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE : {
        value = SPVM_API_get_field_byte(env, stack, object, field);
        break;
      }
      default : {
        is_invalid_type = 1;
      }
    }
  }
  else {
    is_invalid_type = 1;
  }
  
  if (is_invalid_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the field must be byte type.", func_name, file, line);
    return 0;
  }
  
  return value;
}

int16_t SPVM_API_get_field_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (object == NULL) {
    *error_id = SPVM_API_die(env, stack, "The object must be defined.", func_name, file, line);
    return 0;
  };
  
  SPVM_RUNTIME_BASIC_TYPE* object_basic_type = object->basic_type;
  
  int32_t object_type_dimension = object->type_dimension;
  
  int32_t object_is_class_type = SPVM_API_is_class_type(runtime, object_basic_type, object_type_dimension, 0);
  
  if (!object_is_class_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the invocant must be a class type.", func_name, file, line);
    return 0;
  };
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  if (!field) {
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    *error_id = SPVM_API_die(env, stack, "%s#%s field is not found in the class or its super classes.", basic_type_name, field_name, func_name, file, line);
    return 0;
  };
  
  int32_t is_numeric_type = SPVM_API_is_numeric_type(runtime, field->basic_type, field->type_dimension, field->type_flag);
  
  int32_t is_invalid_type = 0;
  
  int16_t value = 0;
  if (is_numeric_type) {
    switch (field->basic_type->id) {
      case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE : {
        value = SPVM_API_get_field_byte(env, stack, object, field);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT : {
        value = SPVM_API_get_field_short(env, stack, object, field);
        break;
      }
      default : {
        is_invalid_type = 1;
      }
    }
  }
  else {
    is_invalid_type = 1;
  }
  
  if (is_invalid_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the field must be short type or smaller numeric type.", func_name, file, line);
    return 0;
  }
  
  return value;
}

int32_t SPVM_API_get_field_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (object == NULL) {
    *error_id = SPVM_API_die(env, stack, "The object must be defined.", func_name, file, line);
    return 0;
  };
  
  SPVM_RUNTIME_BASIC_TYPE* object_basic_type = object->basic_type;
  
  int32_t object_type_dimension = object->type_dimension;
  
  int32_t object_is_class_type = SPVM_API_is_class_type(runtime, object_basic_type, object_type_dimension, 0);
  
  if (!object_is_class_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the invocant must be a class type.", func_name, file, line);
    return 0;
  };
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  if (!field) {
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    *error_id = SPVM_API_die(env, stack, "%s#%s field is not found in the class or its super classes.", basic_type_name, field_name, func_name, file, line);
    return 0;
  };
  
  int32_t is_numeric_type = SPVM_API_is_numeric_type(runtime, field->basic_type, field->type_dimension, field->type_flag);
  
  int32_t is_invalid_type = 0;
  
  int32_t value = 0;
  if (is_numeric_type) {
    switch (field->basic_type->id) {
      case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE : {
        value = SPVM_API_get_field_byte(env, stack, object, field);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT : {
        value = SPVM_API_get_field_short(env, stack, object, field);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_INT : {
        value = SPVM_API_get_field_int(env, stack, object, field);
        break;
      }
      default : {
        is_invalid_type = 1;
      }
    }
  }
  else {
    is_invalid_type = 1;
  }
  
  if (is_invalid_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the field must be int type or smaller numeric type.", func_name, file, line);
    return 0;
  }
  
  return value;
}

int64_t SPVM_API_get_field_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (object == NULL) {
    *error_id = SPVM_API_die(env, stack, "The object must be defined.", func_name, file, line);
    return 0;
  };
  
  SPVM_RUNTIME_BASIC_TYPE* object_basic_type = object->basic_type;
  
  int32_t object_type_dimension = object->type_dimension;
  
  int32_t object_is_class_type = SPVM_API_is_class_type(runtime, object_basic_type, object_type_dimension, 0);
  
  if (!object_is_class_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the invocant must be a class type.", func_name, file, line);
    return 0;
  };
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  if (!field) {
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    *error_id = SPVM_API_die(env, stack, "%s#%s field is not found in the class or its super classes.", basic_type_name, field_name, func_name, file, line);
    return 0;
  };
  
  int32_t is_numeric_type = SPVM_API_is_numeric_type(runtime, field->basic_type, field->type_dimension, field->type_flag);
  
  int32_t is_invalid_type = 0;
  
  int64_t value = 0;
  if (is_numeric_type) {
    switch (field->basic_type->id) {
      case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE : {
        value = SPVM_API_get_field_byte(env, stack, object, field);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT : {
        value = SPVM_API_get_field_short(env, stack, object, field);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_INT : {
        value = SPVM_API_get_field_int(env, stack, object, field);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG : {
        value = SPVM_API_get_field_long(env, stack, object, field);
        break;
      }
      default : {
        is_invalid_type = 1;
      }
    }
  }
  else {
    is_invalid_type = 1;
  }
  
  if (is_invalid_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the field must be long type or smaller numeric type.", func_name, file, line);
    return 0;
  }
  
  return value;
}

float SPVM_API_get_field_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (object == NULL) {
    *error_id = SPVM_API_die(env, stack, "The object must be defined.", func_name, file, line);
    return 0;
  };
  
  SPVM_RUNTIME_BASIC_TYPE* object_basic_type = object->basic_type;
  
  int32_t object_type_dimension = object->type_dimension;
  
  int32_t object_is_class_type = SPVM_API_is_class_type(runtime, object_basic_type, object_type_dimension, 0);
  
  if (!object_is_class_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the invocant must be a class type.", func_name, file, line);
    return 0;
  };
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  if (!field) {
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    *error_id = SPVM_API_die(env, stack, "%s#%s field is not found in the class or its super classes.", basic_type_name, field_name, func_name, file, line);
    return 0;
  };
  
  int32_t is_numeric_type = SPVM_API_is_numeric_type(runtime, field->basic_type, field->type_dimension, field->type_flag);
  
  int32_t is_invalid_type = 0;
  
  float value = 0;
  if (is_numeric_type) {
    switch (field->basic_type->id) {
      case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE : {
        value = SPVM_API_get_field_byte(env, stack, object, field);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT : {
        value = SPVM_API_get_field_short(env, stack, object, field);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_INT : {
        value = SPVM_API_get_field_int(env, stack, object, field);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG : {
        value = SPVM_API_get_field_long(env, stack, object, field);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT : {
        value = SPVM_API_get_field_float(env, stack, object, field);
        break;
      }
      default : {
        is_invalid_type = 1;
      }
    }
  }
  else {
    is_invalid_type = 1;
  }
  
  if (is_invalid_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the field must be float type or smaller numeric type.", func_name, file, line);
    return 0;
  }
  
  return value;
}

double SPVM_API_get_field_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (object == NULL) {
    *error_id = SPVM_API_die(env, stack, "The object must be defined.", func_name, file, line);
    return 0;
  };
  
  SPVM_RUNTIME_BASIC_TYPE* object_basic_type = object->basic_type;
  
  int32_t object_type_dimension = object->type_dimension;
  
  int32_t object_is_class_type = SPVM_API_is_class_type(runtime, object_basic_type, object_type_dimension, 0);
  
  if (!object_is_class_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the invocant must be a class type.", func_name, file, line);
    return 0;
  };
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  if (!field) {
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    *error_id = SPVM_API_die(env, stack, "%s#%s field is not found in the class or its super classes.", basic_type_name, field_name, func_name, file, line);
    return 0;
  };
  
  int32_t is_numeric_type = SPVM_API_is_numeric_type(runtime, field->basic_type, field->type_dimension, field->type_flag);
  
  int32_t is_invalid_type = 0;
  
  double value = 0;
  if (is_numeric_type) {
    switch (field->basic_type->id) {
      case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE : {
        value = SPVM_API_get_field_byte(env, stack, object, field);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT : {
        value = SPVM_API_get_field_short(env, stack, object, field);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_INT : {
        value = SPVM_API_get_field_int(env, stack, object, field);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG : {
        value = SPVM_API_get_field_long(env, stack, object, field);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT : {
        value = SPVM_API_get_field_float(env, stack, object, field);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE : {
        value = SPVM_API_get_field_double(env, stack, object, field);
        break;
      }
      default : {
        is_invalid_type = 1;
      }
    }
  }
  else {
    is_invalid_type = 1;
  }
  
  if (is_invalid_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the field must be double type or smaller numeric type.", func_name, file, line);
    return 0;
  }
  
  return value;
}

SPVM_OBJECT* SPVM_API_get_field_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (object == NULL) {
    *error_id = SPVM_API_die(env, stack, "The object must be defined.", func_name, file, line);
    return NULL;
  };
  
  SPVM_RUNTIME_BASIC_TYPE* object_basic_type = object->basic_type;
  
  int32_t object_type_dimension = object->type_dimension;
  
  int32_t object_is_class_type = SPVM_API_is_class_type(runtime, object_basic_type, object_type_dimension, 0);
  
  if (!object_is_class_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the invocant must be a class type.", func_name, file, line);
    return 0;
  };
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  if (!field) {
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    *error_id = SPVM_API_die(env, stack, "%s#%s field is not found in the class or its super classes.", basic_type_name, field_name, func_name, file, line);
    return NULL;
  };
  
  int32_t is_object_type = SPVM_API_is_object_type(runtime, field->basic_type, field->type_dimension, field->type_flag);
  
  int32_t is_invalid_type = 0;
  
  SPVM_OBJECT* value = NULL;
  if (is_object_type) {
    value = SPVM_API_get_field_object(env, stack, object, field);
  }
  else {
    is_invalid_type = 1;
  }
  
  if (is_invalid_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the field must be an object type.", func_name, file, line);
    return 0;
  }
  
  return value;
}

SPVM_OBJECT** SPVM_API_get_field_object_ref_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (object == NULL) {
    *error_id = SPVM_API_die(env, stack, "The object must be defined.", func_name, file, line);
    return NULL;
  };
  
  SPVM_RUNTIME_BASIC_TYPE* object_basic_type = object->basic_type;
  
  int32_t object_type_dimension = object->type_dimension;
  
  int32_t object_is_class_type = SPVM_API_is_class_type(runtime, object_basic_type, object_type_dimension, 0);
  
  if (!object_is_class_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the invocant must be a class type.", func_name, file, line);
    return 0;
  };
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  
  if (!field) {
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    *error_id = SPVM_API_die(env, stack, "%s#%s field is not found in the class or its super classes.", basic_type_name, field_name, func_name, file, line);
    return NULL;
  };
  
  int32_t is_object_type = SPVM_API_is_object_type(runtime, field->basic_type, field->type_dimension, field->type_flag);
  
  int32_t is_invalid_type = 0;
  
  SPVM_OBJECT** ref = NULL;
  if (is_object_type) {
    ref = SPVM_API_get_field_object_ref(env, stack, object, field);
  }
  else {
    is_invalid_type = 1;
  }
  
  if (is_invalid_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the field must be an object type.", func_name, file, line);
    return 0;
  }
  
  return ref;
}

SPVM_OBJECT* SPVM_API_get_field_object_defined_and_has_pointer_by_name(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file_name, int32_t line) {
  
  *error_id = 0;
  
  void* obj_field = env->get_field_object_by_name(env, stack, object, field_name, error_id, func_name, file_name, line);
  
  if (*error_id) { return NULL; }
  
  if (!obj_field) {
    *error_id = SPVM_API_die(env, stack, "%s field must be defined.", field_name, func_name, file_name, line);
    return obj_field;
  }
  
  void* field = env->get_pointer(env, stack, obj_field);
  
  if (!field) {
    *error_id = SPVM_API_die(env, stack, "The pointer of %s field must be defined.", field_name, func_name, file_name, line);
  }
  
  return obj_field;
}

SPVM_OBJECT* SPVM_API_get_field_string_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  return SPVM_API_get_field_object_by_name(env, stack, object, field_name, error_id, func_name, file, line);
}

const char* SPVM_API_get_field_string_chars_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  if (!field) {
    *error_id = SPVM_API_die(env, stack, "%s field is not found.", field_name, func_name, file, line);
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
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (object == NULL) {
    *error_id = SPVM_API_die(env, stack, "The object must be defined.", func_name, file, line);
    return;
  };
  
  SPVM_RUNTIME_BASIC_TYPE* object_basic_type = object->basic_type;
  
  int32_t object_type_dimension = object->type_dimension;
  
  int32_t object_is_class_type = SPVM_API_is_class_type(runtime, object_basic_type, object_type_dimension, 0);
  
  if (!object_is_class_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the invocant must be a class type.", func_name, file, line);
    return;
  };
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  if (!field) {
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    *error_id = SPVM_API_die(env, stack, "%s#%s field is not found in the class or its super classes.", basic_type_name, field_name, func_name, file, line);
    return;
  }
  
  int32_t is_numeric_type = SPVM_API_is_numeric_type(runtime, field->basic_type, field->type_dimension, field->type_flag);
  
  int32_t is_invalid_type = 0;
  
  if (is_numeric_type) {
    switch (field->basic_type->id) {
      case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE : {
        SPVM_API_set_field_byte(env, stack, object, field, value);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT : {
        SPVM_API_set_field_short(env, stack, object, field, value);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_INT : {
        SPVM_API_set_field_int(env, stack, object, field, value);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG : {
        SPVM_API_set_field_long(env, stack, object, field, value);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT : {
        SPVM_API_set_field_float(env, stack, object, field, value);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE : {
        SPVM_API_set_field_double(env, stack, object, field, value);
        break;
      }
      default : {
        is_invalid_type = 1;
      }
    }
  }
  else {
    is_invalid_type = 1;
  }
  
  if (is_invalid_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the field must be byte or larger numeric type.", func_name, file, line);
    return;
  }
}

void SPVM_API_set_field_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int16_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (object == NULL) {
    *error_id = SPVM_API_die(env, stack, "The object must be defined.", func_name, file, line);
    return;
  };
  
  SPVM_RUNTIME_BASIC_TYPE* object_basic_type = object->basic_type;
  
  int32_t object_type_dimension = object->type_dimension;
  
  int32_t object_is_class_type = SPVM_API_is_class_type(runtime, object_basic_type, object_type_dimension, 0);
  
  if (!object_is_class_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the invocant must be a class type.", func_name, file, line);
    return;
  };
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  if (!field) {
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    *error_id = SPVM_API_die(env, stack, "%s#%s field is not found in the class or its super classes.", basic_type_name, field_name, func_name, file, line);
    return;
  };
  
  int32_t is_numeric_type = SPVM_API_is_numeric_type(runtime, field->basic_type, field->type_dimension, field->type_flag);
  
  int32_t is_invalid_type = 0;
  
  if (is_numeric_type) {
    switch (field->basic_type->id) {
      case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT : {
        SPVM_API_set_field_short(env, stack, object, field, value);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_INT : {
        SPVM_API_set_field_int(env, stack, object, field, value);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG : {
        SPVM_API_set_field_long(env, stack, object, field, value);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT : {
        SPVM_API_set_field_float(env, stack, object, field, value);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE : {
        SPVM_API_set_field_double(env, stack, object, field, value);
        break;
      }
      default : {
        is_invalid_type = 1;
      }
    }
  }
  else {
    is_invalid_type = 1;
  }
  
  if (is_invalid_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the field must be short or larger numeric type.", func_name, file, line);
    return;
  }
}

void SPVM_API_set_field_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (object == NULL) {
    *error_id = SPVM_API_die(env, stack, "The object must be defined.", func_name, file, line);
    return;
  };
  
  SPVM_RUNTIME_BASIC_TYPE* object_basic_type = object->basic_type;
  
  int32_t object_type_dimension = object->type_dimension;
  
  int32_t object_is_class_type = SPVM_API_is_class_type(runtime, object_basic_type, object_type_dimension, 0);
  
  if (!object_is_class_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the invocant must be a class type.", func_name, file, line);
    return;
  };
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  if (!field) {
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    *error_id = SPVM_API_die(env, stack, "%s#%s field is not found in the class or its super classes.", basic_type_name, field_name, func_name, file, line);
    return;
  };
  
  int32_t is_numeric_type = SPVM_API_is_numeric_type(runtime, field->basic_type, field->type_dimension, field->type_flag);
  
  int32_t is_invalid_type = 0;
  
  if (is_numeric_type) {
    switch (field->basic_type->id) {
      case SPVM_NATIVE_C_BASIC_TYPE_ID_INT : {
        SPVM_API_set_field_int(env, stack, object, field, value);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG : {
        SPVM_API_set_field_long(env, stack, object, field, value);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT : {
        SPVM_API_set_field_float(env, stack, object, field, value);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE : {
        SPVM_API_set_field_double(env, stack, object, field, value);
        break;
      }
      default : {
        is_invalid_type = 1;
      }
    }
  }
  else {
    is_invalid_type = 1;
  }
  
  if (is_invalid_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the field must be int or larger numeric type.", func_name, file, line);
    return;
  }
}

void SPVM_API_set_field_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int64_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (object == NULL) {
    *error_id = SPVM_API_die(env, stack, "The object must be defined.", func_name, file, line);
    return;
  };
  
  SPVM_RUNTIME_BASIC_TYPE* object_basic_type = object->basic_type;
  
  int32_t object_type_dimension = object->type_dimension;
  
  int32_t object_is_class_type = SPVM_API_is_class_type(runtime, object_basic_type, object_type_dimension, 0);
  
  if (!object_is_class_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the invocant must be a class type.", func_name, file, line);
    return;
  };
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  if (!field) {
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    *error_id = SPVM_API_die(env, stack, "%s#%s field is not found in the class or its super classes.", basic_type_name, field_name, func_name, file, line);
    return;
  };
  
  int32_t is_numeric_type = SPVM_API_is_numeric_type(runtime, field->basic_type, field->type_dimension, field->type_flag);
  
  int32_t is_invalid_type = 0;
  
  if (is_numeric_type) {
    switch (field->basic_type->id) {
      case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG : {
        SPVM_API_set_field_long(env, stack, object, field, value);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT : {
        SPVM_API_set_field_float(env, stack, object, field, value);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE : {
        SPVM_API_set_field_double(env, stack, object, field, value);
        break;
      }
      default : {
        is_invalid_type = 1;
      }
    }
  }
  else {
    is_invalid_type = 1;
  }
  
  if (is_invalid_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the field must be long or larger numeric type.", func_name, file, line);
    return;
  }
}

void SPVM_API_set_field_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, float value, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (object == NULL) {
    *error_id = SPVM_API_die(env, stack, "The object must be defined.", func_name, file, line);
    return;
  };
  
  SPVM_RUNTIME_BASIC_TYPE* object_basic_type = object->basic_type;
  
  int32_t object_type_dimension = object->type_dimension;
  
  int32_t object_is_class_type = SPVM_API_is_class_type(runtime, object_basic_type, object_type_dimension, 0);
  
  if (!object_is_class_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the invocant must be a class type.", func_name, file, line);
    return;
  };
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  if (!field) {
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    *error_id = SPVM_API_die(env, stack, "%s#%s field is not found in the class or its super classes.", basic_type_name, field_name, func_name, file, line);
    return;
  };
  
  int32_t is_numeric_type = SPVM_API_is_numeric_type(runtime, field->basic_type, field->type_dimension, field->type_flag);
  
  int32_t is_invalid_type = 0;
  
  if (is_numeric_type) {
    switch (field->basic_type->id) {
      case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT : {
        SPVM_API_set_field_float(env, stack, object, field, value);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE : {
        SPVM_API_set_field_double(env, stack, object, field, value);
        break;
      }
      default : {
        is_invalid_type = 1;
      }
    }
  }
  else {
    is_invalid_type = 1;
  }
  
  if (is_invalid_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the field must be float or larger numeric type.", func_name, file, line);
    return;
  }
}

void SPVM_API_set_field_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, double value, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (object == NULL) {
    *error_id = SPVM_API_die(env, stack, "The object must be defined.", func_name, file, line);
    return;
  };
  
  SPVM_RUNTIME_BASIC_TYPE* object_basic_type = object->basic_type;
  
  int32_t object_type_dimension = object->type_dimension;
  
  int32_t object_is_class_type = SPVM_API_is_class_type(runtime, object_basic_type, object_type_dimension, 0);
  
  if (!object_is_class_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the invocant must be a class type.", func_name, file, line);
    return;
  };
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  if (!field) {
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    *error_id = SPVM_API_die(env, stack, "%s#%s field is not found in the class or its super classes.", basic_type_name, field_name, func_name, file, line);
    return;
  };
  
  int32_t is_numeric_type = SPVM_API_is_numeric_type(runtime, field->basic_type, field->type_dimension, field->type_flag);
  
  int32_t is_invalid_type = 0;
  
  if (is_numeric_type) {
    switch (field->basic_type->id) {
      case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE : {
        SPVM_API_set_field_double(env, stack, object, field, value);
        break;
      }
      default : {
        is_invalid_type = 1;
      }
    }
  }
  else {
    is_invalid_type = 1;
  }
  
  if (is_invalid_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the field must be double type.", func_name, file, line);
    return;
  }
}

void SPVM_API_set_field_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, SPVM_OBJECT* value, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (object == NULL) {
    *error_id = SPVM_API_die(env, stack, "The object must be defined.", func_name, file, line);
    return;
  };
  
  SPVM_RUNTIME_BASIC_TYPE* object_basic_type = object->basic_type;
  
  int32_t object_type_dimension = object->type_dimension;
  
  int32_t object_is_class_type = SPVM_API_is_class_type(runtime, object_basic_type, object_type_dimension, 0);
  
  if (!object_is_class_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the invocant must be a class type.", func_name, file, line);
    return;
  };
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  if (!field) {
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    *error_id = SPVM_API_die(env, stack, "%s#%s field is not found in the class or its super classes.", basic_type_name, field_name, func_name, file, line);
    return;
  };
  
  
  int32_t is_object_type = SPVM_API_is_object_type(runtime, field->basic_type, field->type_dimension, field->type_flag);
  
  int32_t is_invalid_type = 0;
  
  if (is_object_type) {
    SPVM_API_set_field_object(env, stack, object, field, value);
  }
  else {
    is_invalid_type = 1;
  }
  
  if (is_invalid_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the field must be an object type.", func_name, file, line);
    return;
  }
}

void SPVM_API_set_field_string_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, SPVM_OBJECT* value, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  SPVM_API_set_field_object_by_name(env, stack, object, field_name, value, error_id, func_name, file, line);
}

int32_t SPVM_API_die(SPVM_ENV* env, SPVM_VALUE* stack, const char* message, ...) {
  
  va_list args;
  
  char tmp_buffer[SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE] = {0};
  char* message_with_line = tmp_buffer;
  int32_t message_length = strlen(message);
  if (message_length > 255) {
    message_length = 255;
  }
  memcpy(message_with_line, message, message_length);
  const char* place = "\n    %s at %s line %d";
  memcpy(message_with_line + message_length, place, strlen(place));
  message_with_line[message_length + strlen(place)] = '\0';
  
  assert(message_length + strlen(place) <= SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE);
  
  void* exception = SPVM_API_new_string_no_mortal(env, stack, NULL, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE);
  char* exception_chars = (char*)SPVM_API_get_chars(env, stack, exception);
  
  va_start(args, message);
  vsnprintf(exception_chars, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, message_with_line, args);
  va_end(args);
  
  SPVM_API_shorten(env, stack, exception, strlen(exception_chars));
  
  SPVM_API_set_exception(env, stack, exception);
  
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
}

SPVM_VALUE* SPVM_API_new_stack(SPVM_ENV* env) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_VALUE* stack = env->new_memory_block(env, NULL, sizeof(SPVM_VALUE) * SPVM_API_C_STACK_LENGTH);
  
  stack[SPVM_API_C_STACK_INDEX_MORTAL_STACK_CAPACITY].ival = 1;
  void* native_mortal_stack = SPVM_API_new_memory_block(env, stack, sizeof(SPVM_OBJECT*) * stack[SPVM_API_C_STACK_INDEX_MORTAL_STACK_CAPACITY].ival);
  if (native_mortal_stack == NULL) {
    return NULL;
  }
  stack[SPVM_API_C_STACK_INDEX_MORTAL_STACK].oval = native_mortal_stack;
  stack[SPVM_API_C_STACK_INDEX_ENV].oval = env;
  
  stack[SPVM_API_C_STACK_INDEX_CALL_DEPTH].ival = -1;
  
  stack[SPVM_API_C_STACK_INDEX_CALL_STACK_FRAME_INFOS_CAPACITY].ival = 1;
  stack[SPVM_API_C_STACK_INDEX_CALL_STACK_FRAME_INFOS].oval = SPVM_API_new_memory_block_for_call_stack(env, stack, sizeof(SPVM_RUNTIME_CALL_STACK_FRAME_INFO) * stack[SPVM_API_C_STACK_INDEX_CALL_STACK_FRAME_INFOS_CAPACITY].ival);
  
  stack[SPVM_API_C_STACK_INDEX_CALL_STACK_MEMORY_BLOCKS_CAPACITY].ival = 1;
  void** call_stack_memory_blocks = SPVM_API_new_memory_block_for_call_stack(env, stack, sizeof(void*) * stack[SPVM_API_C_STACK_INDEX_CALL_STACK_FRAME_INFOS_CAPACITY].ival);
  for (int32_t i = 0; i < stack[SPVM_API_C_STACK_INDEX_CALL_STACK_MEMORY_BLOCKS_CAPACITY].ival; i++) {
    call_stack_memory_blocks[i] = SPVM_API_new_memory_block_for_call_stack(env, stack, SPVM_API_C_CALL_STACK_MEMORY_BLOCK_SIZE);
  }
  stack[SPVM_API_C_STACK_INDEX_CALL_STACK_MEMORY_BLOCKS].oval = call_stack_memory_blocks;
  
  return stack;
}

SPVM_VALUE* SPVM_API_new_stack_with_all_method_call_permitted(SPVM_ENV* env) {
  
  SPVM_VALUE* stack = SPVM_API_new_stack(env);
  
  stack[SPVM_API_C_STACK_INDEX_ALL_METHOD_CALL_PERMITTED].ival = 1;
  
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
  
  void** call_stack_memory_blocks = stack[SPVM_API_C_STACK_INDEX_CALL_STACK_MEMORY_BLOCKS].oval;
  int32_t call_stack_memory_blocks_capacity = stack[SPVM_API_C_STACK_INDEX_CALL_STACK_MEMORY_BLOCKS_CAPACITY].ival;
  for (int32_t i = 0; i < call_stack_memory_blocks_capacity; i++) {
    void* call_stack_memory_block = call_stack_memory_blocks[i];
    SPVM_API_free_memory_block_for_call_stack(env, stack, call_stack_memory_block);
    call_stack_memory_block = NULL;
  }
  
  SPVM_API_free_memory_block_for_call_stack(env, stack, call_stack_memory_blocks);
  
  call_stack_memory_blocks = NULL;
  
  void** call_stack_frame_infos = stack[SPVM_API_C_STACK_INDEX_CALL_STACK_FRAME_INFOS].oval;
  SPVM_API_free_memory_block_for_call_stack(env, stack, call_stack_frame_infos);
  call_stack_frame_infos = NULL;
  
  assert(stack[SPVM_API_C_STACK_INDEX_MEMORY_BLOCKS_FOR_CALL_STACK].ival == 0);
  
  env->free_memory_block(env, stack, stack);
  stack = NULL;
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
      is_object_array = SPVM_API_is_object_type(env->runtime, object_basic_type, element_type_dimension, type_flag);
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

int32_t SPVM_API_is_any_object_array(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  int32_t is_any_object_array;
  if (object) {
    SPVM_RUNTIME_BASIC_TYPE* object_basic_type = SPVM_API_get_object_basic_type(env, stack, object);
    is_any_object_array = (object_basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_ANY_OBJECT && object->type_dimension == 1);
  }
  else {
    is_any_object_array = 0;
  }
  
  return is_any_object_array;
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
  
  if (obj_type_name) {
    char* type_name = (char*)SPVM_API_get_chars(env, stack, obj_type_name);
    
    int32_t type_name_index = 0;
    sprintf((char*)type_name, "%s", basic_type_name);
    type_name_index += strlen(basic_type_name);
    
    int32_t dim_index;
    for (dim_index = 0; dim_index < type_dimension; dim_index++) {
      sprintf((char*)(type_name + type_name_index), "[]");
      type_name_index += 2;
    }
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
  
  if (obj_compile_type_name) {
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
  }
  
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
  
  const char* class_file = basic_type->file;
  
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
  total_length += strlen(class_file);
  
  const char* line_part = " line ";
  
  total_length += strlen(line_part);
  char tmp_buffer[SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE] = {0};
  snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%" PRId32, line);
  total_length += strlen(tmp_buffer);
  
  // Create exception message
  void* new_exception = SPVM_API_new_string_no_mortal(env, stack, NULL, total_length);
  
  if (new_exception) {
    const char* new_exception_bytes = SPVM_API_get_chars(env, stack, new_exception);
    
    memcpy(
      (void*)(new_exception_bytes),
      (void*)(exception_bytes),
      exception_length
    );
    
    sprintf(
      (char*)new_exception_bytes + exception_length,
      "%s%s%s%s%s%s%s%" PRId32,
      new_line_part,
      basic_type_name,
      arrow_part,
      method_name,
      at_part,
      class_file,
      line_part,
      line
    );
  }
  
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

void SPVM_API_warn(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string, const char* basic_type_name, const char* method_name, const char* file, int32_t line) {
  
  FILE* spvm_stderr = SPVM_API_RUNTIME_get_spvm_stderr(env->runtime);
  
  if (string) {
    if (env->is_type_by_name(env, stack, string, "string", 0)) {
      const char* chars =SPVM_API_get_chars(env, stack, string);
      
      int32_t string_length = SPVM_API_length(env, stack, string);
      
      if (string_length > 0) {
        size_t ret = fwrite(chars, 1, string_length, spvm_stderr);
      }
      
      fprintf(spvm_stderr, "\n  %s->%s at %s line %d\n", basic_type_name, method_name, file, line);
    }
    else {
      int32_t scope_id = SPVM_API_enter_scope(env, stack);
      void* obj_type_name = env->get_type_name(env, stack, string);
      const char* type_name = env->get_chars(env, stack, obj_type_name);
      
      fprintf(spvm_stderr, "%s", type_name);
      fprintf(spvm_stderr, "(0x%" PRIxPTR ")\n  %s->%s at %s line %d\n", (uintptr_t)string, basic_type_name, method_name, file, line);
      SPVM_API_leave_scope(env, stack, scope_id);
    }
  }
  else {
    fprintf(spvm_stderr, "undef\n  %s->%s at %s line %d\n", basic_type_name, method_name, file, line);
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
  
  if (string3) {
    const char* string1_bytes = SPVM_API_get_chars(env, stack, string1);
    const char* string2_bytes = SPVM_API_get_chars(env, stack, string2);
    char* string3_bytes = (char*)SPVM_API_get_chars(env, stack, string3);
    
    if (string1_length > 0) {
      memcpy(string3_bytes, string1_bytes, string1_length);
    }
    if (string2_length) {
      memcpy(string3_bytes + string1_length, string2_bytes, string2_length);
    }
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

// This code is copied from SPVM_TOKE_isprint_ascii
static int32_t isprint_ascii(int32_t ch) {
  
  int32_t isprint_ascii = 0;
  
  // Avoid isprint because it depends locale dependent.
  if (isascii(ch) && (ch >= 0x20 && ch <= 0x7F)) {
    isprint_ascii = 1;
  }
  
  return isprint_ascii;
}

void SPVM_API_dump_recursive(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t* depth, SPVM_STRING_BUFFER* string_buffer, SPVM_HASH* address_symtable) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  char tmp_buffer[SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE] = {0};
  
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
        int32_t utf8_char_len = (int32_t)SPVM_UTF8_iterate((const uint8_t*)(chars + offset), chars_length, &dst);
        
        int32_t uchar;
        if (utf8_char_len > 0) {
            
          if (utf8_char_len == 1 && !isprint_ascii(*(chars + offset))) {
            snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "\\x{%02X}", *(chars + offset) & 0xFF);
            
            SPVM_STRING_BUFFER_add_len(string_buffer, tmp_buffer, strlen(tmp_buffer));
          }
          else {
            SPVM_STRING_BUFFER_add_len(string_buffer, (char*)(chars + offset), utf8_char_len);
          }
          
          offset += utf8_char_len;
        }
        else {
          
          snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "\\x{%02X}", *(chars + offset) & 0xFF);
          
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
                int8_t* element = &((int8_t*)(GET_DATA_ADDRESS(env, object)))[array_index * fields_length];
                snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%d", element[field_index]);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                int16_t* element = &((int16_t*)(GET_DATA_ADDRESS(env, object)))[array_index * fields_length];
                snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%d", element[field_index]);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                int32_t* element = &((int32_t*)(GET_DATA_ADDRESS(env, object)))[array_index * fields_length];
                snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%d", element[field_index]);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                int64_t* element = &((int64_t*)(GET_DATA_ADDRESS(env, object)))[array_index * fields_length];
                snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%lld", (long long int)element[field_index]);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                float* element = &((float*)(GET_DATA_ADDRESS(env, object)))[array_index * fields_length];
                snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%g", element[field_index]);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                double* element = &((double*)(GET_DATA_ADDRESS(env, object)))[array_index * fields_length];
                snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%g", element[field_index]);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
            }
            
            SPVM_STRING_BUFFER_add(string_buffer, ",\n");
          }
          
          SPVM_STRING_BUFFER_add(string_buffer, "  }");
        }
        else if (SPVM_API_is_numeric_array(env, stack, object)) {
          switch (object_basic_type->id) {
            case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
              int8_t element = ((int8_t*)(GET_DATA_ADDRESS(env, object)))[array_index];
              snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%d", element);
              SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
              int16_t element = ((int16_t*)(GET_DATA_ADDRESS(env, object)))[array_index];
              snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%d", element);
              SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
              int32_t element = ((int32_t*)(GET_DATA_ADDRESS(env, object)))[array_index];
              snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%d", element);
              SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
              int64_t element = ((int64_t*)(GET_DATA_ADDRESS(env, object)))[array_index];
              snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%lld", (long long int)element);
              SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
              float element = ((float*)(GET_DATA_ADDRESS(env, object)))[array_index];
              snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%g", element);
              SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
              double element = ((double*)(GET_DATA_ADDRESS(env, object)))[array_index];
              snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%g", element);
              SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
              break;
            }
          }
        }
        else if (SPVM_API_is_object_array(env, stack, object)) {
          SPVM_OBJECT* element = (((SPVM_OBJECT**)(GET_DATA_ADDRESS(env, object)))[array_index]);
          element = SPVM_API_drop_tag_pointers(env, stack, element);
          (*depth)++;
          SPVM_API_dump_recursive(env, stack, element, depth, string_buffer, address_symtable);
          (*depth)--;
        }
        else {
          assert(0);
        }
        
        SPVM_STRING_BUFFER_add(string_buffer, ",\n");
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
      snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "(%p)", SPVM_API_drop_tag_pointers(env, stack, object));
      SPVM_STRING_BUFFER_add(string_buffer, tmp_buffer);
    }
    else {
      // If the object is weaken, this get the real address
      snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%p", SPVM_API_drop_tag_pointers(env, stack, object));
      int32_t exists = (int32_t)(intptr_t)SPVM_HASH_get(address_symtable, tmp_buffer, strlen(tmp_buffer));
      if (exists) {
        // If the object is weaken, this get the real address
        snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "REUSE_OBJECT(%p)", SPVM_API_drop_tag_pointers(env, stack, object));
        SPVM_STRING_BUFFER_add(string_buffer, tmp_buffer);
      }
      else {
        SPVM_RUNTIME_BASIC_TYPE* object_basic_type = SPVM_API_get_object_basic_type(env, stack, object);
        const char* basic_type_name = object_basic_type->name;
        
        SPVM_HASH_set(address_symtable, tmp_buffer, strlen(tmp_buffer), (void*)(intptr_t)1);
        
        SPVM_STRING_BUFFER_add(string_buffer, basic_type_name);
        snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, " (%p) ", object);
        SPVM_STRING_BUFFER_add(string_buffer, tmp_buffer);
        
        SPVM_STRING_BUFFER_add(string_buffer, "{\n");
        
        // Free object fields
        int32_t fields_length = object_basic_type->fields_length;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_RUNTIME_FIELD* field = SPVM_API_BASIC_TYPE_get_field_by_index(runtime, object_basic_type, field_index);
          
          int32_t field_basic_type_id = field->basic_type->id;
          int32_t field_type_dimension = field->type_dimension;
          int32_t field_offset = field->offset;
          const char* field_name = field->name;
          
          for (int32_t depth_index = 0; depth_index < *depth + 1; depth_index++) {
            SPVM_STRING_BUFFER_add(string_buffer, "  ");
          }
          
          SPVM_STRING_BUFFER_add(string_buffer, field_name);
          SPVM_STRING_BUFFER_add(string_buffer, " => ");
          if (field_type_dimension == 0 && field_basic_type_id >= SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE && field_basic_type_id <= SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
            switch (field_basic_type_id) {
              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                int8_t field_value = *(int8_t*)(GET_DATA_ADDRESS(env, object) + field_offset);
                snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%d", field_value);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                int16_t field_value = *(int16_t*)(GET_DATA_ADDRESS(env, object) + field_offset);
                snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%d", field_value);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                int32_t field_value = *(int32_t*)(GET_DATA_ADDRESS(env, object) + field_offset);
                snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%d", field_value);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                int64_t field_value = *(int64_t*)(GET_DATA_ADDRESS(env, object) + field_offset);
                snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%lld", (long long int)field_value);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                float field_value = *(float*)(GET_DATA_ADDRESS(env, object) + field_offset);
                snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%g", field_value);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                double field_value = *(double*)(GET_DATA_ADDRESS(env, object) + field_offset);
                snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%g", field_value);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              default : {
                assert(0);
              }
            }
          }
          else  {
            SPVM_OBJECT* field_value = *(SPVM_OBJECT**)(GET_DATA_ADDRESS(env, object) + field_offset);
            field_value = SPVM_API_drop_tag_pointers(env, stack, field_value);
            (*depth)++;
            SPVM_API_dump_recursive(env, stack, field_value, depth, string_buffer, address_symtable);
            (*depth)--;
          }
          
          SPVM_STRING_BUFFER_add(string_buffer, ",\n");
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
    __sync_fetch_and_or(&string->flag, SPVM_OBJECT_C_FLAG_IS_READ_ONLY);
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
    assert(0);
  }
  
  if (basic_type->category != SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS) {
    assert(0);
  }
  
  // Alloc body length + 1
  int32_t fields_length = basic_type->fields_length;
  
  int32_t exists_byte_blocks_length = (fields_length + 7) / 8;
  
  size_t alloc_size = (size_t)SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + basic_type->fields_size +(sizeof(uint8_t) * exists_byte_blocks_length);
  
  SPVM_OBJECT* object = SPVM_API_new_object_common(env, stack, alloc_size, basic_type, 0, fields_length, 0);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_pointer_object_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_BASIC_TYPE* basic_type, void* pointer) {
  
  void* obj_object = SPVM_API_new_object_no_mortal(env, stack, basic_type);
  
  if (obj_object) {
    SPVM_API_set_pointer(env, stack, obj_object, pointer);
  }
  
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
  
  if (object) {
    if (bytes != NULL && length > 0) {
      memcpy((void*)(GET_DATA_ADDRESS(env, object)), (char*)bytes, length);
    }
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
      memcpy((void*)(GET_DATA_ADDRESS(env, object)), (char*)bytes, length);
    }
  }
  
  return object;
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
  
  if (length < 0) {
    return NULL;
  }
  
  size_t alloc_size = (size_t)SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + sizeof(int16_t) * (length + 1);
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type_by_id(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT);
  
  SPVM_OBJECT* object = SPVM_API_new_object_common(env, stack, alloc_size, basic_type, 1, length, 0);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_int_array_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  
  if (length < 0) {
    return NULL;
  }
  
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
  
  if (length < 0) {
    return NULL;
  }
  
  size_t alloc_size = (size_t)SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + sizeof(float) * (length + 1);
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type_by_id(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT);
  
  SPVM_OBJECT* object = SPVM_API_new_object_common(env, stack, alloc_size, basic_type, 1, length, 0);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_double_array_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  
  if (length < 0) {
    return NULL;
  }
  
  size_t alloc_size = (size_t)SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + sizeof(double) * (length + 1);
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type_by_id(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE);
  
  SPVM_OBJECT* object = SPVM_API_new_object_common(env, stack, alloc_size, basic_type, 1, length, 0);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_object_array_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t length) {
  
  if (length < 0) {
    return NULL;
  }
  
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
  
  if (length < 0) {
    return NULL;
  }
  
  if (type_dimension < 2) {
    return NULL;
  }
  else if (basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_ANY_OBJECT) {
    return NULL;
  }
  
  if (!basic_type) {
    return NULL;
  }
  
  size_t alloc_size = (size_t)SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + sizeof(void*) * (length + 1);
  
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
  
  if (!SPVM_API_is_array(env, stack, array)) {
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
  
  
  SPVM_OBJECT* new_array = SPVM_API_new_array_proto_no_mortal(env, stack, array, length);
  
  SPVM_API_push_mortal(env, stack, new_array);
  
  return new_array;
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

int32_t SPVM_API_has_dynamic_data(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  int32_t has_dynamic_data = 0;
  if (object->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_STRING || object->type_dimension > 0) {
    has_dynamic_data = 1;
  }
  
  return has_dynamic_data;
}

int32_t SPVM_API_length(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  int32_t length = 0;
  
  if (SPVM_API_has_dynamic_data(env, stack, object)) {
    length = object->length;
  }
  
  return length;
}

void SPVM_API_set_length(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t length) {
  
  if (SPVM_API_has_dynamic_data(env, stack, object)) {
    object->length = length;
  }
}

int8_t* SPVM_API_get_elems_byte(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  return (int8_t*)(GET_DATA_ADDRESS(env, object));
}

const char* SPVM_API_get_chars(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string) {
  
  return (const char*)(GET_DATA_ADDRESS(env, string));
}

int16_t* SPVM_API_get_elems_short(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  return (int16_t*)(GET_DATA_ADDRESS(env, object));
}

int32_t* SPVM_API_get_elems_int(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  return (int32_t*)(GET_DATA_ADDRESS(env, object));
}

int64_t* SPVM_API_get_elems_long(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  return (int64_t*)(GET_DATA_ADDRESS(env, object));
}

float* SPVM_API_get_elems_float(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  return (float*)(GET_DATA_ADDRESS(env, object));
}

double* SPVM_API_get_elems_double(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  return (double*)(GET_DATA_ADDRESS(env, object));
}

SPVM_OBJECT* SPVM_API_get_elem_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, int32_t index) {
  
  SPVM_OBJECT* object_maybe_weaken = ((SPVM_OBJECT**)(GET_DATA_ADDRESS(env, array)))[index];
  SPVM_OBJECT* object = SPVM_API_drop_tag_pointers(env, stack, object_maybe_weaken);
  
  return object;
}

void SPVM_API_set_elem_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, int32_t index, SPVM_OBJECT* object) {
  
  SPVM_OBJECT** ref = &((SPVM_OBJECT**)(GET_DATA_ADDRESS(env, array)))[index];
  
  SPVM_API_assign_object(env, stack, ref, object);
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

void* SPVM_API_new_memory_block(SPVM_ENV* env, SPVM_VALUE* stack, size_t size) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  void* block = SPVM_ALLOCATOR_alloc_memory_block_unmanaged((size_t)size);
  
  if (block) {
    int32_t save_memory_blocks_count = __sync_fetch_and_add(&runtime->memory_blocks_count, 1);
    
#ifdef SPVM_DEBUG_MEMORY
    fprintf(runtime->spvm_stderr, "[Debug]Function : new_memory_block, Block Address: %p, Stack Address : %p, Memory Blocks Count : %d.\n", block, stack, save_memory_blocks_count + 1);
#endif
  }
  
  return block;
}

// Deprecated
void SPVM_API_free_memory_block(SPVM_ENV* env, SPVM_VALUE* stack, void* block) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (block) {
    SPVM_ALLOCATOR_free_memory_block_unmanaged(block);
    
    int32_t save_memory_blocks_count = __sync_fetch_and_add(&runtime->memory_blocks_count, -1);
    
#ifdef SPVM_DEBUG_MEMORY
    fprintf(runtime->spvm_stderr, "[Debug]Function : free_memory_block, Block Address: %p, Stack Address : %p, Memory Blocks Count : %d.\n", block, stack, save_memory_blocks_count - 1);
#endif
      
  }
}

int32_t SPVM_API_get_memory_blocks_count(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  int32_t memory_blocks_count = runtime->memory_blocks_count;
  
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
    assert(0);
  }
  
  return new_object;
}

SPVM_OBJECT* SPVM_API_copy(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  
  SPVM_OBJECT* new_object = SPVM_API_copy_no_mortal(env, stack, object);
  
  SPVM_API_push_mortal(env, stack, new_object);
  
  return new_object;
}

void SPVM_API_shorten(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string, int32_t new_length) {
  
  if (!string) {
    return;
  }
  
  if (!SPVM_API_is_string(env, stack, string)) {
    return;
  }
  
  if (SPVM_API_is_read_only(env, stack, string)) {
    return;
  }
  
  int32_t length = SPVM_API_length(env, stack, string);
  
  if (!(new_length >= 0)) {
    return;
  }
  
  if (!(new_length < length)) {
    return;
  }
  
  SPVM_API_set_length(env, stack, string, new_length);
  
  char* chars = (char*)SPVM_API_get_chars(env, stack, string);
  
  assert(length - new_length > 0);
  
  memset(chars + new_length, 0, length - new_length);
}

int32_t SPVM_API_elem_isa(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, SPVM_OBJECT* element) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  assert(array);
  
  SPVM_RUNTIME_BASIC_TYPE* array_basic_type = SPVM_API_get_object_basic_type(env, stack,array);
  
  int32_t array_type_dimension = array->type_dimension;
  
  assert(array_type_dimension > 0);
  int32_t elem_isa = SPVM_API_isa(env, stack, element, array_basic_type, array_type_dimension - 1);
  
  return elem_isa;
}

int32_t SPVM_API_is_type(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension) {
  
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
  
  int32_t isa = 0;
  if (object == NULL) {
    isa = 1;
  }
  else {
    SPVM_RUNTIME_BASIC_TYPE* object_basic_type = object->basic_type;
    int32_t object_type_dimension = object->type_dimension;
    if (!basic_type) {
      isa = 0;
    }
    else {
      // Check type by an easy way at first because SPVM_API_can_assign uses hash and mutex lock.
      if (type_dimension == object_type_dimension) {
        if (object_basic_type->id == basic_type->id) {
          isa = 1;
        }
        else {
          if (basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT && type_dimension == 1) {
            if (object_basic_type->is_object_type && object->type_dimension > 0) {
              isa = 1;
            }
          }
          else {
            SPVM_RUNTIME_BASIC_TYPE* parent_object_basic_type = object_basic_type->parent;
            while (1) {
              if (parent_object_basic_type) {
                if (parent_object_basic_type->id == basic_type->id) {
                  isa = 1;
                  break;
                }
                else {
                  parent_object_basic_type = parent_object_basic_type->parent;
                }
              }
              else {
                break;
              }
            }
          }
        }
      }
      
      if (!isa) {
        isa = SPVM_API_can_assign(env->runtime, basic_type, type_dimension, 0, object_basic_type, object_type_dimension, 0);
      }
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
    *error_id = SPVM_API_die(env, stack, "The %s basic type is not found.", basic_type_name, func_name, file, line);
  };
  return basic_type_id;
}

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_get_basic_type_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  *error_id = 0;
  
  void* basic_type = SPVM_API_get_basic_type(env, stack, basic_type_name);
  if (!basic_type) {
    *error_id = SPVM_API_die(env, stack, "The %s basic type is not found.", basic_type_name, func_name, file, line);
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
  
  char *end;
  errno = 0;
  double version_number = strtod(version_string, &end);
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

int32_t SPVM_API_is_binary_compatible_stack(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t is_binary_compatible_stack = 0;
  if (stack[SPVM_API_C_STACK_INDEX_ENV].oval == env) {
    is_binary_compatible_stack = 1;
  }
  
  return is_binary_compatible_stack;
}

int32_t SPVM_API_push_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  if (object != NULL) {
    SPVM_OBJECT*** current_mortal_stack_ptr = (SPVM_OBJECT***)&stack[SPVM_API_C_STACK_INDEX_MORTAL_STACK];
    int32_t* current_mortal_stack_top_ptr = (int32_t*)&stack[SPVM_API_C_STACK_INDEX_MORTAL_STACK_LENGTH];
    int32_t* current_mortal_stack_capacity_ptr = (int32_t*)&stack[SPVM_API_C_STACK_INDEX_MORTAL_STACK_CAPACITY];
    
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
  int32_t* current_mortal_stack_top_ptr = (int32_t*)&stack[SPVM_API_C_STACK_INDEX_MORTAL_STACK_LENGTH];
  
  for (int32_t mortal_stack_index = original_mortal_stack_top; mortal_stack_index < *current_mortal_stack_top_ptr; mortal_stack_index++) {
    
    SPVM_OBJECT** ref = &(*current_mortal_stack_ptr)[mortal_stack_index];
    
    SPVM_API_assign_object(env, stack, ref, NULL);
    
  }
  
  *current_mortal_stack_top_ptr = original_mortal_stack_top;
}

int32_t SPVM_API_enter_scope(SPVM_ENV* env, SPVM_VALUE* stack){
  
  int32_t mortal_stack_top = *(int32_t*)&stack[SPVM_API_C_STACK_INDEX_MORTAL_STACK_LENGTH];
  
  return mortal_stack_top;
}

void SPVM_API_leave_scope_local_removed3(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT** object_vars, int32_t* mortal_stack_typed_var_index, int32_t* mortal_stack_top_ptr, int32_t original_mortal_stack_top) {
  
  for (int32_t mortal_stack_index = original_mortal_stack_top; mortal_stack_index < *mortal_stack_top_ptr; mortal_stack_index++) {
    int32_t var_index = mortal_stack_typed_var_index[mortal_stack_index];
    SPVM_OBJECT** ref = (SPVM_OBJECT**)&object_vars[var_index];
    if (*ref != NULL) {
      SPVM_API_assign_object(env, stack, ref, NULL);
    }
  }
  *mortal_stack_top_ptr = original_mortal_stack_top;
  
}

void SPVM_API_leave_scope_local(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT** object_vars, int32_t* mortal_stack_typed_var_index, int32_t* mortal_stack_top_ptr, int32_t* mortal_stack_tops, int32_t mortal_stack_tops_index) {
  
  assert(mortal_stack_tops[mortal_stack_tops_index] != -1);
  
  for (int32_t mortal_stack_index = mortal_stack_tops[mortal_stack_tops_index]; mortal_stack_index < *mortal_stack_top_ptr; mortal_stack_index++) {
    int32_t var_index = mortal_stack_typed_var_index[mortal_stack_index];
    
    assert(var_index != -1);
    
    SPVM_OBJECT** ref = (SPVM_OBJECT**)&object_vars[var_index];
    if (*ref != NULL) {
      SPVM_API_assign_object(env, stack, ref, NULL);
    }
    mortal_stack_typed_var_index[mortal_stack_index] = -1;
  }
  *mortal_stack_top_ptr = mortal_stack_tops[mortal_stack_tops_index];
  mortal_stack_tops[mortal_stack_tops_index] = -1;
}

SPVM_OBJECT* SPVM_API_drop_tag_pointers(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  object = SPVM_IMPLEMENT_DROP_TAG_POINTERS(object);
  
  return object;
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
  
  SPVM_OBJECT* object = SPVM_API_drop_tag_pointers(env, stack, *ref);
  
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
      
      SPVM_OBJECT* object = SPVM_API_drop_tag_pointers(env, stack, *ref);
      
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
  
  SPVM_OBJECT* object = SPVM_API_drop_tag_pointers(env, stack, *ref);
  
  int32_t isweak = SPVM_API_isweak_only_check_flag(env, stack, ref);
  
  if (isweak) {
    
    assert(object->weaken_backref_head);
    
    // Drop weaken flag
    *ref = SPVM_API_drop_tag_pointers(env, stack, *ref);
    
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
      SPVM_OBJECT* object = SPVM_API_drop_tag_pointers(env, stack, *ref);
      
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
    
    released_object = SPVM_API_drop_tag_pointers(env, stack, *ref);
    
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
          SPVM_OBJECT** ref = &(((SPVM_OBJECT**)(GET_DATA_ADDRESS(env, released_object)))[index]);
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
          if (released_object_basic_type->destroy_method) {
            
            // Save return value and exception variable
            SPVM_VALUE save_stack_ret = stack[0];
            void* save_stack_exception_var = stack[SPVM_API_C_STACK_INDEX_EXCEPTION].oval;
            stack[SPVM_API_C_STACK_INDEX_EXCEPTION].oval = NULL;
            
            SPVM_RUNTIME_METHOD* destroy_method = released_object_basic_type->destroy_method;
            
            stack[0].oval = released_object;
            int32_t args_width = 1;
            int32_t error_id = SPVM_API_call_method(env, stack, destroy_method, args_width);
            
            // An exception thrown in a destructor is converted to a warning message
            if (error_id) {
              void* exception = SPVM_API_get_exception(env, stack);
              
              assert(exception);
              
              const char* exception_chars = SPVM_API_get_chars(env, stack, exception);
              
              fprintf(runtime->spvm_stderr, "[An exception thrown in DESTROY method is converted to a warning message]\n%s\n", exception_chars);
            }
            
            SPVM_API_set_exception(env, stack, NULL);
            
            // Restore return value and exception variable
            stack[0] = save_stack_ret;
            stack[SPVM_API_C_STACK_INDEX_EXCEPTION].oval = save_stack_exception_var;
          }
          
          // Free released_object fields
          int32_t released_object_fields_length = released_object_basic_type->fields_length;
          for (int32_t field_index = 0; field_index < released_object_fields_length; field_index++) {
            SPVM_RUNTIME_FIELD* field = SPVM_API_BASIC_TYPE_get_field_by_index(runtime, released_object_basic_type, field_index);
            
            void* field_basic_type = field->basic_type;
            int32_t field_type_dimension = field->type_dimension;
            int32_t field_type_flag = field->type_flag;
            int32_t field_type_is_released_object = SPVM_API_is_object_type(runtime, field_basic_type, field_type_dimension, field_type_flag);
            
            if (field_type_is_released_object) {
              SPVM_OBJECT** ref = (SPVM_OBJECT**)(GET_DATA_ADDRESS(env, released_object) + field->offset);
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
    
    __sync_fetch_and_add(&object->ref_count, 1);
  }
}

void SPVM_API_dec_ref_count(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (object != NULL) {
    int32_t ref_count = SPVM_API_get_ref_count(env, stack, object);
    assert(ref_count > 0);
    
    __sync_fetch_and_add(&object->ref_count, -1);
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

int32_t SPVM_API_check_bootstrap_method(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name) {
  
  int32_t error_id = 0;
  
  void* class_basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, basic_type_name);
  void* method = env->api->basic_type->get_method_by_name(env->runtime, class_basic_type, "main");
  
  if (method) {
    int32_t is_class_method = env->api->method->is_class_method(env->runtime, method);
    
    if (is_class_method) {
      int32_t args_length = env->api->method->get_args_length(env->runtime, method);
      
      if (!(args_length == 0)) {
        error_id = SPVM_API_die(env, stack, "The length of the arguments of %s#main method must be 0.", basic_type_name, __func__, FILE_NAME, __LINE__);
      }
      else {
        void* return_basic_type = env->api->method->get_return_basic_type(env->runtime, method);
        const char* return_basic_type_name = env->api->basic_type->get_name(env->runtime, return_basic_type);
        
        if (!(strcmp(return_basic_type_name, "void") == 0)) {
          error_id = SPVM_API_die(env, stack, "The return type of %s#main method must be the void type.", basic_type_name, __func__, FILE_NAME, __LINE__);
        }
      }
    }
    else {
      error_id = SPVM_API_die(env, stack, "%s#main method must be a class method.", basic_type_name, __func__, FILE_NAME, __LINE__);
    }
  }
  else {
    error_id = SPVM_API_die(env, stack, "%s#main method must be defined.", basic_type_name, __func__, FILE_NAME, __LINE__);
  }
  
  return error_id;
}

SPVM_OBJECT* SPVM_API_new_array_proto_element_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* element, int32_t length) {
  
  if (element == NULL) {
    return NULL;
  }
  
  if (length < 0) {
    return NULL;
  }
  
  size_t element_size = 1;
  
  size_t alloc_size = (size_t)SPVM_API_RUNTIME_get_object_data_offset(env->runtime) + sizeof(void*) * (length + 1);
  
  SPVM_RUNTIME_BASIC_TYPE* element_basic_type = SPVM_API_get_object_basic_type(env, stack, element);
  SPVM_OBJECT* new_array = SPVM_API_new_object_common(env, stack, alloc_size, element_basic_type, element->type_dimension + 1, length, 0);
  
  return new_array;
}

SPVM_OBJECT* SPVM_API_new_array_proto_element(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* element, int32_t length) {
  
  
  SPVM_OBJECT* new_array = SPVM_API_new_array_proto_element_no_mortal(env, stack, element, length);
  
  SPVM_API_push_mortal(env, stack, new_array);
  
  return new_array;
}

int32_t SPVM_API_is_binary_compatible_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  int32_t is_binary_compatible_object = 0;
  
  int32_t is_binary_compatible_stack = SPVM_API_is_binary_compatible_stack(env, stack);
  
  if (is_binary_compatible_stack) {
    int32_t basic_type_id = object->basic_type->id;
    
    int32_t is_shareable_type = 0;
    switch (basic_type_id) {
      case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE:
      case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT:
      case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
      case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
      case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
      case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
      case SPVM_NATIVE_C_BASIC_TYPE_ID_STRING:
      {
        is_shareable_type = 1;
      }
    }
    
    if (is_shareable_type || object->basic_type->current_runtime == env->runtime) {
      is_binary_compatible_object = 1;
    }
  }
  
  return is_binary_compatible_object;
}

int32_t SPVM_API_get_bool_object_value(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* bool_object) {
  
  int32_t value = *(int8_t*)(GET_DATA_ADDRESS(env, bool_object));
  
  return value;
}

int32_t SPVM_API_get_byte_object_value(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* byte_object) {
  
  int32_t value = *(int8_t*)(GET_DATA_ADDRESS(env, byte_object));
  
  return value;
}

int32_t SPVM_API_get_short_object_value(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* short_object) {
  
  int32_t value = *(int16_t*)(GET_DATA_ADDRESS(env, short_object));
  
  return value;
}

int32_t SPVM_API_get_int_object_value(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* int_object) {
  
  int32_t value = *(int32_t*)(GET_DATA_ADDRESS(env, int_object));
  
  return value;
}

int64_t SPVM_API_get_long_object_value(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* long_object) {
  
  int64_t value = *(int64_t*)(GET_DATA_ADDRESS(env, long_object));
  
  return value;
}

float SPVM_API_get_float_object_value(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* float_object) {
  
  float value = *(float*)(GET_DATA_ADDRESS(env, float_object));
  
  return value;
}

double SPVM_API_get_double_object_value(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* double_object) {
  
  double value = *(double*)(GET_DATA_ADDRESS(env, double_object));
  
  return value;
}

char* SPVM_API_get_stack_tmp_buffer(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  char* tmp_buffer = (char*)&stack[SPVM_API_C_STACK_INDEX_TMP_BUFFER];
  
  return tmp_buffer;
}

int32_t SPVM_API_no_free(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  int32_t no_free = !!(object->flag & SPVM_OBJECT_C_FLAG_NO_FREE);
  
  return no_free;
}

void SPVM_API_set_no_free(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t no_free) {
  
  if (no_free) {
    __sync_fetch_and_or(&object->flag, SPVM_OBJECT_C_FLAG_NO_FREE);
  }
  else {
    __sync_fetch_and_xor(&object->flag, SPVM_OBJECT_C_FLAG_NO_FREE);
  }
}

void SPVM_API_print_exception_to_stderr(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_exception = env->get_exception(env, stack);
  const char* exception = env->get_chars(env, stack, obj_exception);
  
  fprintf(env->api->runtime->get_spvm_stderr(env->runtime), "[An exception is converted to a warning]\n");
  
  env->print_stderr(env, stack, obj_exception);
  
  fprintf(env->api->runtime->get_spvm_stderr(env->runtime), "\n");
}

SPVM_OBJECT* SPVM_API_dump_object_internal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  void* obj_dump = NULL;
  char* tmp_buffer = env->get_stack_tmp_buffer(env, stack);
  if (object) {
    void* pointer = object->pointer;
    
    int32_t weaken_backrefs_length = 0;
    
    SPVM_WEAKEN_BACKREF* weaken_backref_cur = object->weaken_backref_head;
    
    while (weaken_backref_cur) {
      weaken_backrefs_length++;
      weaken_backref_cur = weaken_backref_cur->next;
    }
    
    int32_t ref_count = object->ref_count;
    
    SPVM_RUNTIME_BASIC_TYPE* basic_type = object->basic_type;
    
    const char* basic_type_name = basic_type->name;
    
    uint8_t type_dimension = object->type_dimension;
    
    uint8_t flag = object->flag;
    const char* is_read_only_flag_str = "";
    if (flag & SPVM_OBJECT_C_FLAG_IS_READ_ONLY) {
      is_read_only_flag_str = "is_read_only";
    }
    
    const char* no_free_flag_str = "";
    if (flag & SPVM_OBJECT_C_FLAG_NO_FREE) {
      no_free_flag_str = "no_free";
    }
    
    int32_t length = object->length;
    
    snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "[Object Intenal:%p]\npointer:%p\nweaken_backrefs_length:%d\nref_count:%d\nbasic_type_name:%s\ntype_dimension:%d\nflag:%s %s\nlength:%d", object, pointer, weaken_backrefs_length, ref_count, basic_type_name, type_dimension, is_read_only_flag_str, no_free_flag_str, length);
    
    obj_dump = env->new_string_nolen(env, stack, tmp_buffer);
  }
  else {
    obj_dump = env->new_string_nolen(env, stack, "undef");
  }
  
  return obj_dump;
}

int32_t SPVM_API_get_seed(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t seed = *(int32_t*)&stack[SPVM_API_C_STACK_INDEX_SEED];
  
  return seed;
}

void SPVM_API_set_seed(SPVM_ENV* env, SPVM_VALUE* stack, int32_t seed) {
  
  *(int32_t*)&stack[SPVM_API_C_STACK_INDEX_SEED] = seed;
  
  if (!*(int32_t*)&stack[SPVM_API_C_STACK_INDEX_SEED_INITIALIZED]) {
    *(int32_t*)&stack[SPVM_API_C_STACK_INDEX_SEED_INITIALIZED] = 1;
  }
}

int32_t SPVM_API_seed_initialized(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t seed_initialized = !!*(int32_t*)&stack[SPVM_API_C_STACK_INDEX_SEED_INITIALIZED];
  
  return seed_initialized;
}

const char* SPVM_API_get_basic_type_name_in_version_from(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  const char* basic_type_name_in_version_from = NULL;
  if (basic_type->basic_type_in_version_from) {
    basic_type_name_in_version_from = basic_type->basic_type_in_version_from->name;
  }
  
  return basic_type_name_in_version_from;
}

int32_t SPVM_API_set_command_info_warning(SPVM_ENV* env, SPVM_VALUE* stack, int32_t warning) {
  
  int32_t error_id = 0;
  
  SPVM_API_set_class_var_byte_by_name(env, stack, "CommandInfo", "$WARNING", warning, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}


/*
  Type native APIs
*/

int32_t SPVM_API_is_numeric_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t type_flag) {
  
  if (basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC && type_dimension == 0 && !(type_flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_API_is_object_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t type_flag) {
  
  if (type_dimension > 0) {
    return 1;
  }
  else if (basic_type->is_object_type && !(type_flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_API_is_class_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t type_flag) {
  
  SPVM_COMPILER* compiler = runtime->compiler;
  
  int32_t is_class_type = SPVM_TYPE_is_class_type(compiler, basic_type->id, type_dimension, type_flag);
  
  return is_class_type;
}

int32_t SPVM_API_is_any_object_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t type_flag) {
  
  if (basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT && type_dimension == 0 && !(type_flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_API_is_object_array_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t type_flag) {
  
  if (basic_type->is_object_type && type_dimension > 0 && !(type_flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_API_is_any_object_array_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t type_flag) {
  
  if (basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT && type_dimension > 0 && !(type_flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_API_is_mulnum_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t type_flag) {
  
  if (basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM && type_dimension == 0 && !(type_flag & SPVM_NATIVE_C_TYPE_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_API_get_type_width(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t type_flag) {
  
  int32_t is_mulnum_type = SPVM_API_is_mulnum_type(runtime, basic_type, type_dimension, type_flag);
  
  int32_t type_width = -1;
  if (is_mulnum_type) {
    type_width = basic_type->fields_length;
  }
  else {
    type_width = 1;
  }
  
  return type_width;
}

int32_t SPVM_API_can_assign(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* dist_basic_type, int32_t dist_type_dimension, int32_t dist_type_flag, SPVM_RUNTIME_BASIC_TYPE* src_basic_type, int32_t src_type_dimension, int32_t src_type_flag) {
  
  int32_t isa = 0;
  
  char assinability_key[256] = {0};
  snprintf(assinability_key, 255, "%d-%d-%d-%d-%d-%d", dist_basic_type->id, dist_type_dimension, dist_type_flag, src_basic_type->id, src_type_dimension, src_type_flag);
  
  SPVM_MUTEX* runtime_mutex = runtime->mutex;
  
  SPVM_MUTEX_reader_lock(runtime_mutex);
  
  int32_t can_assign = (intptr_t)SPVM_HASH_get(runtime->assignment_requirement_symtable, assinability_key, strlen(assinability_key));
  
  SPVM_MUTEX_reader_unlock(runtime_mutex);
  
  if (can_assign > 0) {
    isa = 1;
  }
  else if (can_assign < 0) {
    isa = 0;
  }
  else {
    
    SPVM_COMPILER* compiler = runtime->compiler;
    
    isa = SPVM_TYPE_satisfy_assignment_requirement_without_data_conversion(
      compiler,
      dist_basic_type->id, dist_type_dimension, dist_type_flag,
      src_basic_type->id, src_type_dimension, src_type_flag,
      NULL
    );
    
    SPVM_MUTEX_lock(runtime_mutex);
    
    SPVM_HASH_set(runtime->assignment_requirement_symtable, assinability_key, strlen(assinability_key), (void*)(intptr_t)(isa ? 1 : -1));
    
    SPVM_MUTEX_unlock(runtime_mutex);
  }
  
  return isa;
}

/*
  The end of type native APIs
*/

int32_t SPVM_API_get_call_stack_frame_size(SPVM_RUNTIME_METHOD* method) {
  
  int32_t call_stack_frame_size = 0;
  call_stack_frame_size += (method->long_vars_width + 1) * sizeof(int64_t);
  call_stack_frame_size += (method->double_vars_width + 1) * sizeof(double);
  call_stack_frame_size += (method->object_vars_width + 1) * sizeof(void*);
  call_stack_frame_size += (method->ref_vars_width + 1) * sizeof(void*);
  call_stack_frame_size += (method->int_vars_width + 1) * sizeof(int32_t);
  call_stack_frame_size += (method->float_vars_width + 1) * sizeof(float);
  call_stack_frame_size += (method->mortal_stack_length + 1) * sizeof(int32_t);
  call_stack_frame_size += (method->mortal_stack_tops_length + 1) * sizeof(int32_t);
  call_stack_frame_size += (method->short_vars_width + 1) * sizeof(int16_t);
  call_stack_frame_size += (method->byte_vars_width + 1) * sizeof(int8_t);
  
  // Adjust allignment
  int32_t alignment = sizeof(void*) > sizeof(int64_t) ? sizeof(void*) : sizeof(int64_t);
  assert(alignment >= 8);
  call_stack_frame_size = (call_stack_frame_size + (alignment - 1)) & ~(alignment - 1);
  assert(call_stack_frame_size % alignment == 0);
  
  return call_stack_frame_size;
}

int32_t SPVM_API_set_call_stack_frame_info(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CALL_STACK_FRAME_INFO* call_stack_frame_info, char* call_stack_frame) {
  
  SPVM_RUNTIME_METHOD* method = call_stack_frame_info->method;
  
  // Alignment is important for performance
  // + 1 is needed for pointing a different address when width is 0.
  int32_t call_stack_frame_offset = 0;
  
  // Long varialbes. 8 bytes
  *call_stack_frame_info->long_vars_address = (int64_t*)&call_stack_frame[call_stack_frame_offset];
  call_stack_frame_offset += (method->long_vars_width + 1) * sizeof(int64_t);
  
  // Double variables. 8 bytes
  *call_stack_frame_info->double_vars_address = (double*)&call_stack_frame[call_stack_frame_offset];
  call_stack_frame_offset += (method->double_vars_width + 1) * sizeof(double);
  
  // Object variables. 8 bytes in 64bit architecture, 4 bytes in 32bit architecture
  *call_stack_frame_info->object_vars_address = (void**)&call_stack_frame[call_stack_frame_offset];
  call_stack_frame_offset += (method->object_vars_width + 1) * sizeof(void*);
  
  // Refernce variables. 8 bytes in 64bit architecture, 4 bytes in 32bit architecture
  *call_stack_frame_info->ref_vars_address = (void**)&call_stack_frame[call_stack_frame_offset];
  call_stack_frame_offset += (method->ref_vars_width + 1) * sizeof(void*);
  
  // Int variables. 4 bytes
  *call_stack_frame_info->int_vars_address = (int32_t*)&call_stack_frame[call_stack_frame_offset];
  call_stack_frame_offset += (method->int_vars_width + 1) * sizeof(int32_t);
  
  // Float variables. 4 bytes
  *call_stack_frame_info->float_vars_address = (float*)&call_stack_frame[call_stack_frame_offset];
  call_stack_frame_offset += (method->float_vars_width + 1) * sizeof(float);
  
  // Mortal stack. 4 bytes
  *call_stack_frame_info->mortal_stack_address = (int32_t*)&call_stack_frame[call_stack_frame_offset];
  call_stack_frame_offset += (method->mortal_stack_length + 1) * sizeof(int32_t);
  
  // Mortal stack tops. 4 bytes
  *call_stack_frame_info->mortal_stack_tops_address = (int32_t*)&call_stack_frame[call_stack_frame_offset];
  call_stack_frame_offset += (method->mortal_stack_tops_length + 1) * sizeof(int32_t);
  
  // Short variables. 2 bytes
  *call_stack_frame_info->short_vars_address = (int16_t*)&call_stack_frame[call_stack_frame_offset];
  call_stack_frame_offset += (method->short_vars_width + 1) * sizeof(int16_t);
  
  // Byte variables. 1 bytes
  *call_stack_frame_info->byte_vars_address = (int8_t*)&call_stack_frame[call_stack_frame_offset];
  call_stack_frame_offset += (method->byte_vars_width + 1) * sizeof(int8_t);
  
  call_stack_frame_info->call_stack_frame = call_stack_frame;

}

int32_t SPVM_API_push_call_stack_frame(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CALL_STACK_FRAME_INFO* call_stack_frame_info) {
  
  SPVM_RUNTIME_METHOD* method = call_stack_frame_info->method;
  
  int32_t call_stack_frame_size = method->call_stack_frame_size;
  
  char* call_stack_frame = NULL;
  if (call_stack_frame_size > SPVM_API_C_CALL_STACK_MEMORY_BLOCK_SIZE) {
    call_stack_frame = SPVM_API_new_memory_block_for_call_stack(env, stack, call_stack_frame_size);
    if (!call_stack_frame) {
      return -1;
    }
    call_stack_frame_info->on_heap = 1;
  }
  else {
    void** call_stack_memory_blocks = stack[SPVM_API_C_STACK_INDEX_CALL_STACK_MEMORY_BLOCKS].oval;
    
    int32_t call_stack_offset = stack[SPVM_API_C_STACK_INDEX_CALL_STACK_OFFSET].ival;
    
    int32_t call_stack_memory_blocks_index = call_stack_offset / SPVM_API_C_CALL_STACK_MEMORY_BLOCK_SIZE;
    
    int32_t call_stack_memory_block_offset = call_stack_offset - (SPVM_API_C_CALL_STACK_MEMORY_BLOCK_SIZE * call_stack_memory_blocks_index);
    
    if (call_stack_memory_block_offset + call_stack_frame_size >= SPVM_API_C_CALL_STACK_MEMORY_BLOCK_SIZE) {
      call_stack_memory_blocks_index++;
      call_stack_memory_block_offset = 0;
    }
    
    int32_t call_stack_memory_blocks_capacity = stack[SPVM_API_C_STACK_INDEX_CALL_STACK_MEMORY_BLOCKS_CAPACITY].ival;
    
    if (call_stack_memory_blocks_index >= call_stack_memory_blocks_capacity) {
      int32_t new_call_stack_memory_blocks_capacity = call_stack_memory_blocks_capacity * 2;
      void** new_call_stack_memory_blocks = SPVM_API_new_memory_block_for_call_stack(env, stack, sizeof(void*) * new_call_stack_memory_blocks_capacity);
      if (!new_call_stack_memory_blocks) {
        return -1;
      }
      
      memcpy(new_call_stack_memory_blocks, call_stack_memory_blocks, sizeof(void*) * call_stack_memory_blocks_capacity);
      
      stack[SPVM_API_C_STACK_INDEX_CALL_STACK_MEMORY_BLOCKS].oval = new_call_stack_memory_blocks;
      stack[SPVM_API_C_STACK_INDEX_CALL_STACK_MEMORY_BLOCKS_CAPACITY].ival = new_call_stack_memory_blocks_capacity;
      
      SPVM_API_free_memory_block_for_call_stack(env, stack, call_stack_memory_blocks);
      
      for (int32_t i = 0; i < new_call_stack_memory_blocks_capacity; i++) {
        if (i >= call_stack_memory_blocks_capacity) {
          new_call_stack_memory_blocks[i] = SPVM_API_new_memory_block_for_call_stack(env, stack, SPVM_API_C_CALL_STACK_MEMORY_BLOCK_SIZE);
        }
      }
      
      call_stack_memory_blocks = new_call_stack_memory_blocks;
    }
    
    char* call_stck_memory_block = call_stack_memory_blocks[call_stack_memory_blocks_index];
    
    call_stack_frame = &call_stck_memory_block[call_stack_memory_block_offset];
    
    call_stack_frame_info->call_stack_offset = stack[SPVM_API_C_STACK_INDEX_CALL_STACK_OFFSET].ival;
    
    int32_t new_call_stack_offset = SPVM_API_C_CALL_STACK_MEMORY_BLOCK_SIZE * call_stack_memory_blocks_index + call_stack_memory_block_offset + call_stack_frame_size;
    
    stack[SPVM_API_C_STACK_INDEX_CALL_STACK_OFFSET].ival = new_call_stack_offset;
  }
  
  memset(call_stack_frame, 0, call_stack_frame_size);
  
  assert((intptr_t)call_stack_frame % 8 == 0);
  
  SPVM_API_set_call_stack_frame_info(env, stack, call_stack_frame_info, call_stack_frame);
  
  memset(*call_stack_frame_info->mortal_stack_address, -1, method->mortal_stack_length * sizeof(int32_t));
  memset(*call_stack_frame_info->mortal_stack_tops_address, -1, method->mortal_stack_tops_length * sizeof(int32_t));
  
  return 0;
}

void SPVM_API_pop_call_stack_frame(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CALL_STACK_FRAME_INFO* call_stack_frame_info) {
  
  if (call_stack_frame_info->on_heap) {
    SPVM_API_free_memory_block_for_call_stack(env, stack, call_stack_frame_info->call_stack_frame);
  }
  else {
    assert(stack[SPVM_API_C_STACK_INDEX_CALL_STACK_OFFSET].ival > 0);
    stack[SPVM_API_C_STACK_INDEX_CALL_STACK_OFFSET].ival = call_stack_frame_info->call_stack_offset;
  }
}

void* SPVM_API_new_memory_block_for_call_stack(SPVM_ENV* env, SPVM_VALUE* stack, int32_t size) {
  
  void* memory_block = SPVM_ALLOCATOR_alloc_memory_block_unmanaged(size);
  if (memory_block) {
    stack[SPVM_API_C_STACK_INDEX_MEMORY_BLOCKS_FOR_CALL_STACK].ival++;
  }
  
  return memory_block;
}

void SPVM_API_free_memory_block_for_call_stack(SPVM_ENV* env, SPVM_VALUE* stack, void* block) {
  
  if (block) {
    SPVM_ALLOCATOR_free_memory_block_unmanaged(block);
    stack[SPVM_API_C_STACK_INDEX_MEMORY_BLOCKS_FOR_CALL_STACK].ival--;
  }
  
}

void SPVM_API_enable_options(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  if (object) {
    if (SPVM_API_is_object_array(env, stack, object)) {
      __sync_fetch_and_or(&object->flag, SPVM_OBJECT_C_FLAG_IS_OPTIONS);
    }
  }
}

void SPVM_API_disable_options(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  if (object) {
    __sync_fetch_and_and(&object->flag, ~SPVM_OBJECT_C_FLAG_IS_OPTIONS);
  }
}

int32_t SPVM_API_is_options(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  int32_t is_options;
  if (object) {
    if (object->flag & SPVM_OBJECT_C_FLAG_IS_OPTIONS) {
      is_options = 1;
    }
    else {
      is_options = 0;
    }
  }
  else {
    is_options = 0;
  }
  
  return is_options;
}

int32_t SPVM_API_exists_field(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field) {
  
  int32_t value = SPVM_IMPLEMENT_GET_EXISTS_FLAG(env, stack, object, field->exists_offset, field->exists_bit);
  
  return value;
}

int32_t SPVM_API_exists_field_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (object == NULL) {
    *error_id = SPVM_API_die(env, stack, "The object must be defined.", func_name, file, line);
    return 0;
  };
  
  SPVM_RUNTIME_BASIC_TYPE* object_basic_type = object->basic_type;
  
  int32_t object_type_dimension = object->type_dimension;
  
  int32_t object_is_class_type = SPVM_API_is_class_type(runtime, object_basic_type, object_type_dimension, 0);
  
  if (!object_is_class_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the invocant must be a class type.", func_name, file, line);
    return 0;
  };
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  if (!field) {
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    *error_id = SPVM_API_die(env, stack, "%s#%s field is not found in the class or its super classes.", basic_type_name, field_name, func_name, file, line);
    return 0;
  };
  
  int32_t exists = SPVM_API_exists_field(env, stack, object, field);
  
  return exists;
}

void SPVM_API_delete_field(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  int32_t is_numeric_type = SPVM_API_is_numeric_type(runtime, field->basic_type, field->type_dimension, field->type_flag);
  
  if (is_numeric_type) {
    switch (field->basic_type->id) {
      case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE : {
        SPVM_API_set_field_byte(env, stack, object, field, 0);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT : {
        SPVM_API_set_field_short(env, stack, object, field, 0);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_INT : {
        SPVM_API_set_field_int(env, stack, object, field, 0);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG : {
        SPVM_API_set_field_long(env, stack, object, field, 0);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT : {
        SPVM_API_set_field_float(env, stack, object, field, 0);
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE : {
        SPVM_API_set_field_double(env, stack, object, field, 0);
        break;
      }
      default : {
        assert(0);
      }
    }
  }
  else {
    int32_t is_object_type = SPVM_API_is_object_type(runtime, field->basic_type, field->type_dimension, field->type_flag);
    if (is_object_type) {
      SPVM_API_set_field_object(env, stack, object, field, NULL);
    }
    else {
      assert(0);
    }
  }
  
  SPVM_IMPLEMENT_DISABLE_EXISTS_FLAG(env, stack, object, field->exists_offset, field->exists_bit);
}

void SPVM_API_delete_field_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (object == NULL) {
    *error_id = SPVM_API_die(env, stack, "The object must be defined.", func_name, file, line);
    return;
  };
  
  SPVM_RUNTIME_BASIC_TYPE* object_basic_type = object->basic_type;
  
  int32_t object_type_dimension = object->type_dimension;
  
  int32_t object_is_class_type = SPVM_API_is_class_type(runtime, object_basic_type, object_type_dimension, 0);
  
  if (!object_is_class_type) {
    *error_id = SPVM_API_die(env, stack, "The type of the invocant must be a class type.", func_name, file, line);
    return;
  };
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_get_field(env, stack, object, field_name);
  if (!field) {
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    *error_id = SPVM_API_die(env, stack, "%s#%s field is not found in the class or its super classes.", basic_type_name, field_name, func_name, file, line);
    return;
  };
  
  SPVM_API_delete_field(env, stack, object, field);
}
