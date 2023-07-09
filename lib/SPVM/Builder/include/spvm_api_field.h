// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_API_FIELD_H
#define SPVM_API_FIELD_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_API_FIELD* SPVM_API_FIELD_new_api();

void SPVM_API_FIELD_free_api(SPVM_API_FIELD* api);

const char* SPVM_API_FIELD_get_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_FIELD* field);

int32_t SPVM_API_FIELD_get_index(SPVM_RUNTIME* runtime, SPVM_RUNTIME_FIELD* field);

int32_t SPVM_API_FIELD_get_offset(SPVM_RUNTIME* runtime, SPVM_RUNTIME_FIELD* field);

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_FIELD_get_basic_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_FIELD* field);

int32_t SPVM_API_FIELD_get_type_dimension(SPVM_RUNTIME* runtime, SPVM_RUNTIME_FIELD* field);

int32_t SPVM_API_FIELD_get_type_flag(SPVM_RUNTIME* runtime, SPVM_RUNTIME_FIELD* field);

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_FIELD_get_current_basic_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_FIELD* field);

#endif
