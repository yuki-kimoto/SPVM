#ifndef SPVM_STRING_BUFFER_H
#define SPVM_STRING_BUFFER_H

#include "spvm_base.h"

struct SPVM_string_buffer {
  int32_t page_byte_size;
  int32_t pages_length;
  int32_t current_offset;
  char** pages;
  int32_t current_page;
  char* buffer;
  int32_t capacity;
  int32_t length;
};

SPVM_STRING_BUFFER* SPVM_STRING_BUFFER_new(int32_t page_byte_size);
void* SPVM_STRING_BUFFER_add(SPVM_STRING_BUFFER* string_buffer, char* string);
void SPVM_STRING_BUFFER_free(SPVM_STRING_BUFFER* string_buffer);

#endif
