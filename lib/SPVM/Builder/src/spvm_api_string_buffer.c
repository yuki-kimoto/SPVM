#include "spvm_native.h"

#include "spvm_api_string_buffer.h"

#include "spvm_allocator.h"
#include "spvm_string_buffer.h"

SPVM_STRING_BUFFER* SPVM_API_STRING_BUFFER_new_tmp(SPVM_ALLOCATOR* allocator, int32_t capacity) {
  SPVM_STRING_BUFFER* string_buffer = SPVM_STRING_BUFFER_new_tmp(allocator, capacity);
  
  return string_buffer;
}

const char* SPVM_API_STRING_BUFFER_get_value(SPVM_STRING_BUFFER* env_string_buffer) {
  return string_buffer->value;
}

int32_t SPVM_API_STRING_BUFFER_get_length(SPVM_STRING_BUFFER* env_string_buffer) {
  return string_buffer->length;
}

void SPVM_API_STRING_BUFFER_free(SPVM_STRING_BUFFER* env_string_buffer) {
  SPVM_STRING_BUFFER_free(string_buffer);
}
