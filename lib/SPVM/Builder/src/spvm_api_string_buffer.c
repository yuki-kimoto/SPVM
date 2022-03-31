#include "spvm_allocator.h"
#include "spvm_env_allocator.h"
#include "spvm_api_allocator.h"
#include "spvm_string_buffer.h"
#include "spvm_env_string_buffer.h"
#include "spvm_api_string_buffer.h"

SPVM_ENV_STRING_BUFFER* SPVM_API_STRING_BUFFER_new_env_raw() {
  
  return NULL;
}

SPVM_ENV_STRING_BUFFER* SPVM_API_STRING_BUFFER_new_tmp(SPVM_ENV_ALLOCATOR* env_allocator, int32_t capacity) {
  SPVM_STRING_BUFFER* string_buffer = SPVM_STRING_BUFFER_new_tmp(env_allocator->allocator, capacity);
  
  SPVM_ENV_STRING_BUFFER* env_string_buffer = SPVM_API_STRING_BUFFER_new_env_raw();
  env_string_buffer->strign_buffer = string_buffer;
  
  return string_buffer;
}

const char* SPVM_API_STRING_BUFFER_get_value(SPVM_ENV_STRING_BUFFER* env_string_buffer) {
  return env_string_buffer->string_buffer->value;
}

int32_t SPVM_API_STRING_BUFFER_get_length(SPVM_ENV_STRING_BUFFER* env_string_buffer) {
  return env_string_buffer->string_buffer->length;
}

void SPVM_API_STRING_BUFFER_free(SPVM_ENV_STRING_BUFFER* env_string_buffer) {
  SPVM_STRING_BUFFER_free(env_string_buffer->string_buffer);
}
