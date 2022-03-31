#ifndef SPVM_API_STRING_BUFFER_H
#define SPVM_API_STRING_BUFFER_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_ENV_STRING_BUFFER* SPVM_API_STRING_BUFFER_new_env_raw();
SPVM_ENV_STRING_BUFFER* SPVM_API_STRING_BUFFER_new_tmp(SPVM_ENV_ALLOCATOR* env_allocator, int32_t capacity);
const char* SPVM_API_STRING_BUFFER_get_value(SPVM_ENV_STRING_BUFFER* env_string_buffer);
int32_t SPVM_API_STRING_BUFFER_get_length(SPVM_ENV_STRING_BUFFER* env_string_buffer);
void SPVM_API_STRING_BUFFER_free(SPVM_ENV_STRING_BUFFER* env_string_buffer);

#endif
