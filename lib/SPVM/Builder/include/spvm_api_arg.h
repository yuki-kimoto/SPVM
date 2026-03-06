// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_API_ARG_H
#define SPVM_API_ARG_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_API_ARG* SPVM_API_ARG_new_api();

void SPVM_API_ARG_free_api(SPVM_API_ARG* api);

const char* SPVM_API_ARG_get_name(SPVM_NATIVE_RUNTIME* runtime, SPVM_NATIVE_ARG* arg);

int32_t SPVM_API_ARG_get_index(SPVM_NATIVE_RUNTIME* runtime, SPVM_NATIVE_ARG* arg);

SPVM_NATIVE_BASIC_TYPE* SPVM_API_ARG_get_basic_type(SPVM_NATIVE_RUNTIME* runtime, SPVM_NATIVE_ARG* arg);

int32_t SPVM_API_ARG_get_type_dimension(SPVM_NATIVE_RUNTIME* runtime, SPVM_NATIVE_ARG* arg);

int32_t SPVM_API_ARG_get_type_flag(SPVM_NATIVE_RUNTIME* runtime, SPVM_NATIVE_ARG* arg);

int32_t SPVM_API_ARG_get_stack_index(SPVM_NATIVE_RUNTIME* runtime, SPVM_NATIVE_ARG* arg);

SPVM_NATIVE_METHOD* SPVM_API_ARG_get_current_method(SPVM_NATIVE_RUNTIME* runtime, SPVM_NATIVE_ARG* arg);

int32_t SPVM_API_ARG_is_optional(SPVM_NATIVE_RUNTIME* runtime, SPVM_NATIVE_ARG* arg);

SPVM_VALUE SPVM_API_ARG_get_default_value(SPVM_NATIVE_RUNTIME* runtime, SPVM_NATIVE_ARG* arg);

#endif
