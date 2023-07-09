// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_API_CLASS_VAR_H
#define SPVM_API_CLASS_VAR_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_API_CLASS_VAR* SPVM_API_CLASS_VAR_new_api();

void SPVM_API_CLASS_VAR_free_api(SPVM_API_CLASS_VAR* api);

const char* SPVM_API_CLASS_VAR_get_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_CLASS_VAR* class_var);

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_CLASS_VAR_get_basic_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_CLASS_VAR* class_var);

int32_t SPVM_API_CLASS_VAR_get_type_dimension(SPVM_RUNTIME* runtime, SPVM_RUNTIME_CLASS_VAR* class_var);

int32_t SPVM_API_CLASS_VAR_get_type_flag(SPVM_RUNTIME* runtime, SPVM_RUNTIME_CLASS_VAR* class_var);

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_CLASS_VAR_get_current_basic_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_CLASS_VAR* class_var);

#endif
