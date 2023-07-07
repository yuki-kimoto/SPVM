// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>

#include "spvm_native.h"

#include "spvm_api_string_buffer.h"

#include "spvm_allocator.h"
#include "spvm_string_buffer.h"

SPVM_API_STRING_BUFFER* SPVM_API_STRING_BUFFER_new_api() {
  void* env_string_buffer_init[]  = {
    SPVM_API_STRING_BUFFER_new_instance,
    SPVM_API_STRING_BUFFER_free_instance,
    SPVM_API_STRING_BUFFER_get_string,
    SPVM_API_STRING_BUFFER_get_length,
  };
  SPVM_API_STRING_BUFFER* env_string_buffer = calloc(1, sizeof(env_string_buffer_init));
  memcpy(env_string_buffer, env_string_buffer_init, sizeof(env_string_buffer_init));
  
  return env_string_buffer;
}

SPVM_STRING_BUFFER* SPVM_API_STRING_BUFFER_new_instance(SPVM_ALLOCATOR* allocator, int32_t capacity) {
  SPVM_STRING_BUFFER* string_buffer = SPVM_STRING_BUFFER_new_tmp(allocator, capacity);
  
  return string_buffer;
}

const char* SPVM_API_STRING_BUFFER_get_string(SPVM_STRING_BUFFER* string_buffer) {
  return string_buffer->string;
}

int32_t SPVM_API_STRING_BUFFER_get_length(SPVM_STRING_BUFFER* string_buffer) {
  return string_buffer->length;
}

void SPVM_API_STRING_BUFFER_free_instance(SPVM_STRING_BUFFER* string_buffer) {
  SPVM_STRING_BUFFER_free(string_buffer);
}
