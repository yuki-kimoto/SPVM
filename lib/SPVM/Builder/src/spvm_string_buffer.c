#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "spvm_string_buffer.h"
#include "spvm_allocator.h"
#include "spvm_allocator.h"
#include "spvm_native.h"

SPVM_STRING_BUFFER* SPVM_STRING_BUFFER_new(SPVM_ALLOCATOR* allocator, int32_t capacity, int32_t memory_block_type) {
  
  if (capacity == 0) {
    capacity = 16;
  }
  
  SPVM_STRING_BUFFER* string_buffer;
  if (memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP) {
    string_buffer = (SPVM_STRING_BUFFER*)SPVM_ALLOCATOR_alloc_memory_block_tmp(allocator, sizeof(SPVM_STRING_BUFFER));
  }
  else if (memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT) {
    string_buffer = (SPVM_STRING_BUFFER*)SPVM_ALLOCATOR_alloc_memory_block_permanent(allocator, sizeof(SPVM_STRING_BUFFER));
  }
  else {
    assert(0);
  }
  
  string_buffer->capacity = capacity;
  if (memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP) {
    string_buffer->buffer = (char*)SPVM_ALLOCATOR_alloc_memory_block_tmp(allocator, capacity);
  }
  else if (memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT) {
    string_buffer->buffer = (char*)SPVM_ALLOCATOR_alloc_memory_block_permanent(allocator, capacity);
  }
  else {
    assert(0);
  }

  string_buffer->allocator = allocator;
  
  string_buffer->memory_block_type = memory_block_type;
  
  return string_buffer;
}


SPVM_STRING_BUFFER* SPVM_STRING_BUFFER_new_tmp(SPVM_ALLOCATOR* allocator, int32_t capacity) {
  return SPVM_STRING_BUFFER_new(allocator, capacity, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
}

char* SPVM_STRING_BUFFER_get_buffer(SPVM_STRING_BUFFER* string_buffer) {
  
  return string_buffer->buffer;
}

void SPVM_STRING_BUFFER_maybe_extend(SPVM_STRING_BUFFER* string_buffer, int32_t new_length) {

  SPVM_ALLOCATOR* allocator = string_buffer->allocator;

  // Extend
  while (new_length >= string_buffer->capacity) {
    int32_t new_capacity = string_buffer->capacity * 2;
    char* new_buffer;
    if (string_buffer->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP) {
      new_buffer = (char*)SPVM_ALLOCATOR_alloc_memory_block_tmp(allocator, new_capacity);
    }
    else if (string_buffer->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT) {
      new_buffer = (char*)SPVM_ALLOCATOR_alloc_memory_block_permanent(allocator, new_capacity);
    }
    else {
      assert(0);
    }

    memcpy(new_buffer, string_buffer->buffer, string_buffer->length);

    if (string_buffer->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP) {
      SPVM_ALLOCATOR_free_memory_block_tmp(allocator, string_buffer->buffer);
    }
    else if (string_buffer->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT) {
      // Nothing
    }
    else {
      assert(0);
    }

    string_buffer->buffer = new_buffer;
    string_buffer->capacity = new_capacity;
  }
}

int32_t SPVM_STRING_BUFFER_add(SPVM_STRING_BUFFER* string_buffer, const char* string) {
  
  int32_t id = string_buffer->length;
  
  int32_t string_length = strlen(string);
  
  int32_t new_length = string_buffer->length + string_length;
  
  // Extend
  SPVM_STRING_BUFFER_maybe_extend(string_buffer, new_length);
  
  memcpy(string_buffer->buffer + string_buffer->length, string, string_length);
  
  string_buffer->length = new_length;
  
  return id;
}

int32_t SPVM_STRING_BUFFER_add_len(SPVM_STRING_BUFFER* string_buffer, char* string, int32_t string_length) {
  
  int32_t id = string_buffer->length;
  
  int32_t new_length = string_buffer->length + string_length;
  
  // Extend
  SPVM_STRING_BUFFER_maybe_extend(string_buffer, new_length);
  
  memcpy(string_buffer->buffer + string_buffer->length, string, string_length);
  
  string_buffer->length = new_length;
  
  return id;
}

int32_t SPVM_STRING_BUFFER_add_len_nullstr(SPVM_STRING_BUFFER* string_buffer, char* string, int32_t string_length) {
  
  int32_t id = string_buffer->length;
  
  int32_t new_length = string_buffer->length + string_length + 1;
  
  // Extend
  SPVM_STRING_BUFFER_maybe_extend(string_buffer, new_length);
  
  memcpy(string_buffer->buffer + string_buffer->length, string, string_length);
  *(string_buffer->buffer + string_buffer->length + string_length) = '\0';
  
  string_buffer->length = new_length;
  
  return id;
}

int32_t SPVM_STRING_BUFFER_add_hex_char(SPVM_STRING_BUFFER* string_buffer, char ch) {
  
  int32_t id = string_buffer->length;

  int32_t new_length = string_buffer->length + 4;
  
  // Extend
  SPVM_STRING_BUFFER_maybe_extend(string_buffer, new_length);
  
  sprintf(string_buffer->buffer + string_buffer->length, "\\x%02X", ch & 0x000000FF);
  
  string_buffer->length = new_length;
  
  return id;
}

int32_t SPVM_STRING_BUFFER_add_char(SPVM_STRING_BUFFER* string_buffer, int8_t value) {
  
  int32_t id = string_buffer->length;
  
  int32_t max_length = 20;
  
  int32_t new_max_length = string_buffer->length + max_length;
  
  // Extend
  SPVM_STRING_BUFFER_maybe_extend(string_buffer, new_max_length);
  
  int32_t write_length = sprintf(string_buffer->buffer + string_buffer->length, "%" PRId8, value);
  
  string_buffer->length += write_length;
  
  return id;
}

int32_t SPVM_STRING_BUFFER_add_short(SPVM_STRING_BUFFER* string_buffer, int16_t value) {
  
  int32_t id = string_buffer->length;
  
  int32_t max_length = 20;
  
  int32_t new_max_length = string_buffer->length + max_length;
  
  // Extend
  SPVM_STRING_BUFFER_maybe_extend(string_buffer, new_max_length);
  
  int32_t write_length = sprintf(string_buffer->buffer + string_buffer->length, "%" PRId16, value);
  
  string_buffer->length += write_length;
  
  return id;
}

int32_t SPVM_STRING_BUFFER_add_int(SPVM_STRING_BUFFER* string_buffer, int32_t value) {
  
  int32_t id = string_buffer->length;
  
  int32_t max_length = 20;
  
  int32_t new_max_length = string_buffer->length + max_length;
  
  // Extend
  SPVM_STRING_BUFFER_maybe_extend(string_buffer, new_max_length);
  
  int32_t write_length;
  if (value == INT32_MIN) {
    write_length = sprintf(string_buffer->buffer + string_buffer->length, "INT32_MIN");
  }
  else {
    write_length = sprintf(string_buffer->buffer + string_buffer->length, "%" PRId32, value);
  }
  
  string_buffer->length += write_length;
  
  return id;
}

int32_t SPVM_STRING_BUFFER_add_long(SPVM_STRING_BUFFER* string_buffer, int64_t value) {
  
  int32_t id = string_buffer->length;

  int32_t max_length = 20 + 2;
  
  int32_t new_max_length = string_buffer->length + max_length;
  
  // Extend
  SPVM_STRING_BUFFER_maybe_extend(string_buffer, new_max_length);
  
  int32_t write_length;
  if (value == INT64_MIN) {
    write_length = sprintf(string_buffer->buffer + string_buffer->length, "INT64_MIN");
  }
  else {
    write_length = sprintf(string_buffer->buffer + string_buffer->length, "%" PRId64 "LL", value);
  }
  
  string_buffer->length += write_length;
  
  return id;
}

void SPVM_STRING_BUFFER_free(SPVM_STRING_BUFFER* string_buffer) {

  SPVM_ALLOCATOR* allocator = string_buffer->allocator;
  
  if (string_buffer->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP) {
    SPVM_ALLOCATOR_free_memory_block_tmp(allocator, string_buffer->buffer);
    SPVM_ALLOCATOR_free_memory_block_tmp(allocator, string_buffer);
  }
  else if (string_buffer->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT) {
    // Nothing
  }
  else {
    assert(0);
  }
}
