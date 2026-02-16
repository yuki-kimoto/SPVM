// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>

#include "spvm_typedecl.h"
#include "spvm_native.h"
#include "spvm_runtime_method.h"
#include "spvm_runtime_arg.h"
#include "spvm_opcode.h"
#include "spvm_api_method.h"





SPVM_API_METHOD* SPVM_API_METHOD_new_api() {
  
  void* native_apis_init[]  = {
    SPVM_API_METHOD_get_name,
    SPVM_API_METHOD_get_index,
    SPVM_API_METHOD_get_return_basic_type,
    SPVM_API_METHOD_get_return_type_dimension,
    SPVM_API_METHOD_get_return_type_flag,
    SPVM_API_METHOD_get_arg_by_index,
    SPVM_API_METHOD_get_args_length,
    SPVM_API_METHOD_get_required_args_length,
    SPVM_API_METHOD_get_current_basic_type,
    SPVM_API_METHOD_get_opcode_by_index,
    SPVM_API_METHOD_get_opcodes_length,
    SPVM_API_METHOD_is_class_method,
    SPVM_API_METHOD_is_anon,
    SPVM_API_METHOD_is_native,
    SPVM_API_METHOD_is_precompile,
    SPVM_API_METHOD_is_enum,
    SPVM_API_METHOD_get_byte_vars_width,
    SPVM_API_METHOD_get_short_vars_width,
    SPVM_API_METHOD_get_int_vars_width,
    SPVM_API_METHOD_get_long_vars_width,
    SPVM_API_METHOD_get_float_vars_width,
    SPVM_API_METHOD_get_double_vars_width,
    SPVM_API_METHOD_get_object_vars_width,
    SPVM_API_METHOD_get_ref_vars_width,
    SPVM_API_METHOD_get_mortal_stack_length,
    SPVM_API_METHOD_get_native_address,
    SPVM_API_METHOD_set_native_address,
    SPVM_API_METHOD_get_precompile_address,
    SPVM_API_METHOD_set_precompile_address,
    SPVM_API_METHOD_is_precompile_fallback,
    SPVM_API_METHOD_set_is_precompile_fallback,
    NULL, // removed31
    NULL, // removed32
    SPVM_API_METHOD_get_args_signature,
    SPVM_API_METHOD_get_abs_name,
  };
  
  SPVM_API_METHOD* native_apis = calloc(1, sizeof(native_apis_init));
  
  memcpy(native_apis, native_apis_init, sizeof(native_apis_init));
  
  return native_apis;
}

void SPVM_API_METHOD_free_api(SPVM_API_METHOD* api) {
  
  free(api);
}

const char* SPVM_API_METHOD_get_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  return method->name;
}

int32_t SPVM_API_METHOD_get_index(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  return method->index;
}

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_METHOD_get_return_basic_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  return method->return_basic_type;
}

int32_t SPVM_API_METHOD_get_return_type_dimension(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  return method->return_type_dimension;
}

int32_t SPVM_API_METHOD_get_return_type_flag(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  return method->return_type_flag;
}

SPVM_RUNTIME_ARG* SPVM_API_METHOD_get_arg_by_index(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method, int32_t arg_index) {
  
  if (arg_index < 0) {
    return NULL;
  }
  
  if (arg_index >= method->args_length) {
    return NULL;
  }
  
  SPVM_RUNTIME_ARG* arg = &method->args[arg_index];
  
  return arg;
}

int32_t SPVM_API_METHOD_get_args_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  return method->args_length;
}

int32_t SPVM_API_METHOD_get_required_args_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  return method->required_args_length;
}

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_METHOD_get_current_basic_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  return method->current_basic_type;
}

SPVM_OPCODE* SPVM_API_METHOD_get_opcode_by_index(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method, int32_t opcode_index) {
  
  if (opcode_index < 0) {
    return NULL;
  }
  
  if (opcode_index >= method->opcodes_length) {
    return NULL;
  }
  
  SPVM_OPCODE* opcode = &method->opcodes[opcode_index];
  
  return opcode;
}

int32_t SPVM_API_METHOD_get_opcodes_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  return method->opcodes_length;
}

int32_t SPVM_API_METHOD_is_class_method(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  return method->is_class_method;
}

int32_t SPVM_API_METHOD_is_anon(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  int32_t is_anon = strcmp(method->name, "") == 0;
  
  return is_anon;
}

int32_t SPVM_API_METHOD_is_native(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  return method->is_native;
}

int32_t SPVM_API_METHOD_is_precompile(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  return method->is_precompile;
}

int32_t SPVM_API_METHOD_is_enum(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  return method->is_enum;
}

int32_t SPVM_API_METHOD_get_byte_vars_width(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  int32_t byte_vars_width = method->byte_vars_width;
  
  return byte_vars_width;
}

int32_t SPVM_API_METHOD_get_short_vars_width(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  return method->short_vars_width;
}

int32_t SPVM_API_METHOD_get_int_vars_width(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  return method->int_vars_width;
}

int32_t SPVM_API_METHOD_get_long_vars_width(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  return method->long_vars_width;
}

int32_t SPVM_API_METHOD_get_float_vars_width(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  return method->float_vars_width;
}

int32_t SPVM_API_METHOD_get_double_vars_width(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  return method->double_vars_width;
}

int32_t SPVM_API_METHOD_get_object_vars_width(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  return method->object_vars_width;
}

int32_t SPVM_API_METHOD_get_ref_vars_width(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  return method->ref_vars_width;
}

int32_t SPVM_API_METHOD_get_mortal_stack_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  return method->mortal_stack_length;
}

void* SPVM_API_METHOD_get_native_address(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {

  return method->native_address;
}

void SPVM_API_METHOD_set_native_address(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method, void* address) {
  
  method->native_address = address;
}

void* SPVM_API_METHOD_get_precompile_address(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {

  return method->precompile_address;
}

void SPVM_API_METHOD_set_precompile_address(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method, void* address) {

  method->precompile_address = address;
}

int32_t SPVM_API_METHOD_is_precompile_fallback(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  return method->is_precompile_fallback;
}

void SPVM_API_METHOD_set_is_precompile_fallback(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method, int32_t is_precompile_fallback) {
  
  method->is_precompile_fallback = is_precompile_fallback;
}

const char* SPVM_API_METHOD_get_args_signature(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  return method->args_signature;
}

const char* SPVM_API_METHOD_get_abs_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method) {
  
  return method->abs_name;
}
