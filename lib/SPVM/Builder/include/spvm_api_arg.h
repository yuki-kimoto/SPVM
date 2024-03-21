// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_API_ARG_H
#define SPVM_API_ARG_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_API_ARG* SPVM_API_ARG_new_api();

void SPVM_API_ARG_free_api(SPVM_API_ARG* api);

const char* SPVM_API_ARG_get_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_ARG* arg);

int32_t SPVM_API_ARG_get_index(SPVM_RUNTIME* runtime, SPVM_RUNTIME_ARG* arg);

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_ARG_get_basic_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_ARG* arg);

int32_t SPVM_API_ARG_get_type_dimension(SPVM_RUNTIME* runtime, SPVM_RUNTIME_ARG* arg);

int32_t SPVM_API_ARG_get_type_flag(SPVM_RUNTIME* runtime, SPVM_RUNTIME_ARG* arg);

int32_t SPVM_API_ARG_get_stack_index(SPVM_RUNTIME* runtime, SPVM_RUNTIME_ARG* arg);

SPVM_RUNTIME_METHOD* SPVM_API_ARG_get_current_method(SPVM_RUNTIME* runtime, SPVM_RUNTIME_ARG* arg);

#endif
