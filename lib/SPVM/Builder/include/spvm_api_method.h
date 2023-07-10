// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_API_METHOD_H
#define SPVM_API_METHOD_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_API_METHOD* SPVM_API_METHOD_new_api();

void SPVM_API_METHOD_free_api(SPVM_API_METHOD* api);

const char* SPVM_API_METHOD_get_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);

int32_t SPVM_API_METHOD_get_index(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_METHOD_get_return_basic_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);

int32_t SPVM_API_METHOD_get_return_type_dimension(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);

int32_t SPVM_API_METHOD_get_return_type_flag(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);

SPVM_RUNTIME_ARG* SPVM_API_METHOD_get_arg_by_index(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method, int32_t arg_index);

int32_t SPVM_API_METHOD_get_args_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);

int32_t SPVM_API_METHOD_get_required_args_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_METHOD_get_current_basic_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);

SPVM_OPCODE* SPVM_API_METHOD_get_opcodes(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);

int32_t SPVM_API_METHOD_get_opcodes_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);

int32_t SPVM_API_METHOD_get_is_class_method(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);

int32_t SPVM_API_METHOD_get_is_anon(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);

int32_t SPVM_API_METHOD_get_is_native(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);

int32_t SPVM_API_METHOD_get_is_precompile(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);

int32_t SPVM_API_METHOD_get_is_enum(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);

int32_t SPVM_API_METHOD_get_byte_vars_width(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);

int32_t SPVM_API_METHOD_get_short_vars_width(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);

int32_t SPVM_API_METHOD_get_int_vars_width(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);

int32_t SPVM_API_METHOD_get_long_vars_width(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);

int32_t SPVM_API_METHOD_get_float_vars_width(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);

int32_t SPVM_API_METHOD_get_double_vars_width(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);

int32_t SPVM_API_METHOD_get_object_vars_width(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);

int32_t SPVM_API_METHOD_get_ref_vars_width(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);

int32_t SPVM_API_METHOD_get_mortal_stack_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);

#endif
