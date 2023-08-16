// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_API_TYPE_H
#define SPVM_API_TYPE_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_API_TYPE* SPVM_API_TYPE_new_api();

void SPVM_API_TYPE_free_api(SPVM_API_TYPE* api);

int32_t SPVM_API_TYPE_can_assign(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* dist_basic_type, int32_t dist_type_dimension, int32_t dist_type_flag, SPVM_RUNTIME_BASIC_TYPE* src_basic_type, int32_t src_type_dimension, int32_t src_type_flag);

int32_t SPVM_API_TYPE_get_type_width(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t dimension, int32_t flag);

int32_t SPVM_API_TYPE_is_object_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t flag);

int32_t SPVM_API_TYPE_is_any_object_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t flag);

int32_t SPVM_API_TYPE_is_object_array_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t dimension, int32_t flag);

int32_t SPVM_API_TYPE_is_any_object_array_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t flag);

#endif
