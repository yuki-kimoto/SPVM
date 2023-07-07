// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_API_STRING_BUFFER_H
#define SPVM_API_STRING_BUFFER_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_API_STRING_BUFFER* SPVM_API_STRING_BUFFER_new_env();
SPVM_STRING_BUFFER* SPVM_API_STRING_BUFFER_new_instance(SPVM_ALLOCATOR* allocator, int32_t capacity);
const char* SPVM_API_STRING_BUFFER_get_string(SPVM_STRING_BUFFER* env_string_buffer);
int32_t SPVM_API_STRING_BUFFER_get_length(SPVM_STRING_BUFFER* env_string_buffer);
void SPVM_API_STRING_BUFFER_free_instance(SPVM_STRING_BUFFER* env_string_buffer);

#endif
