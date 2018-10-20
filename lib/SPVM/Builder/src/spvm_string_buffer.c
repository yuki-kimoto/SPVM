#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "spvm_string_buffer.h"
#include "spvm_util_allocator.h"

SPVM_STRING_BUFFER* SPVM_STRING_BUFFER_new(int32_t capacity) {
  
  
  if (capacity == 0) {
    capacity = 0xFFFF;
  }
  
  SPVM_STRING_BUFFER* string_buffer = (SPVM_STRING_BUFFER*) SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_STRING_BUFFER));
  
  string_buffer->capacity = capacity;
  string_buffer->buffer = (char*)SPVM_UTIL_ALLOCATOR_safe_malloc_zero(capacity);
  
  return string_buffer;
}

char* SPVM_STRING_BUFFER_get_buffer(SPVM_STRING_BUFFER* string_buffer) {
  
  
  return string_buffer->buffer;
}

void SPVM_STRING_BUFFER_add_package_name(SPVM_STRING_BUFFER* string_buffer, const char* package_name) {
  
  
  SPVM_STRING_BUFFER_add(string_buffer, (char*)package_name);
  {
    int32_t index = string_buffer->length - strlen(package_name);
    
    while (index < string_buffer->length) {
      if (string_buffer->buffer[index] == ':') {
        string_buffer->buffer[index] = '_';
      }
      index++;
    }
  }
}

void SPVM_STRING_BUFFER_add_field_id_name(SPVM_STRING_BUFFER* string_buffer, const char* package_name, const char* field_name) {
  
  
  SPVM_STRING_BUFFER_add(string_buffer, "field_id_");
  SPVM_STRING_BUFFER_add_package_name(string_buffer, package_name);
  SPVM_STRING_BUFFER_add(string_buffer, "__");
  SPVM_STRING_BUFFER_add_package_name(string_buffer, field_name);
}

void SPVM_STRING_BUFFER_add_field_index_name(SPVM_STRING_BUFFER* string_buffer, const char* package_name, const char* field_name) {
  
  
  SPVM_STRING_BUFFER_add(string_buffer, "field_index_");
  SPVM_STRING_BUFFER_add_package_name(string_buffer, package_name);
  SPVM_STRING_BUFFER_add(string_buffer, "__");
  SPVM_STRING_BUFFER_add_package_name(string_buffer, field_name);
}

void SPVM_STRING_BUFFER_add_sub_id_name(SPVM_STRING_BUFFER* string_buffer, const char* package_name, const char* sub_name) {
  
  
  SPVM_STRING_BUFFER_add(string_buffer, "sub_id_");
  SPVM_STRING_BUFFER_add_package_name(string_buffer, package_name);
  SPVM_STRING_BUFFER_add(string_buffer, "__");
  SPVM_STRING_BUFFER_add_package_name(string_buffer, sub_name);
}

void SPVM_STRING_BUFFER_add_basic_type_id_name(SPVM_STRING_BUFFER* string_buffer, const char* basic_type_name) {
  
  
  SPVM_STRING_BUFFER_add(string_buffer, "basic_type_id_");
  SPVM_STRING_BUFFER_add_package_name(string_buffer, basic_type_name);
}

void SPVM_STRING_BUFFER_add_package_var_id_name(SPVM_STRING_BUFFER* string_buffer, const char* package_name, const char* package_var_name) {
  
  
  SPVM_STRING_BUFFER_add(string_buffer, "SPVM_GLOBAL_VAR_PACKAGE_VAR_ID_");
  SPVM_STRING_BUFFER_add_package_name(string_buffer, package_name);
  SPVM_STRING_BUFFER_add(string_buffer, "__");
  SPVM_STRING_BUFFER_add_package_name(string_buffer, &package_var_name[1]);
}

void SPVM_STRING_BUFFER_maybe_extend(SPVM_STRING_BUFFER* string_buffer, int32_t new_length) {
  
  
  // Extend
  if (new_length > string_buffer->capacity) {
    int32_t new_capacity = string_buffer->capacity * 2;
    char* new_buffer = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(new_capacity);
    memcpy(new_buffer, string_buffer->buffer, string_buffer->length);
    string_buffer->buffer = new_buffer;
    string_buffer->capacity = new_capacity;
  }
}

void SPVM_STRING_BUFFER_add(SPVM_STRING_BUFFER* string_buffer, char* string) {
  
  
  int32_t string_length = strlen(string);
  
  int32_t new_length = string_buffer->length + string_length;
  
  // Extend
  SPVM_STRING_BUFFER_maybe_extend(string_buffer, new_length);
  
  memcpy(string_buffer->buffer + string_buffer->length, string, string_length);
  
  string_buffer->length = new_length;
  
  return;
}

void SPVM_STRING_BUFFER_add_hex_char(SPVM_STRING_BUFFER* string_buffer, char ch) {
  
  
  int32_t new_length = string_buffer->length + 4;
  
  // Extend
  SPVM_STRING_BUFFER_maybe_extend(string_buffer, new_length);
  
  sprintf(string_buffer->buffer + string_buffer->length, "\\x%02X", ch & 0x000000FF);
  
  string_buffer->length = new_length;
  
  return;
}

void SPVM_STRING_BUFFER_add_len(SPVM_STRING_BUFFER* string_buffer, char* string, int32_t string_length) {
  
  
  int32_t new_length = string_buffer->length + string_length;
  
  // Extend
  SPVM_STRING_BUFFER_maybe_extend(string_buffer, new_length);
  
  memcpy(string_buffer->buffer + string_buffer->length, string, string_length);
  
  string_buffer->length = new_length;
  
  return;
}

void SPVM_STRING_BUFFER_add_byte(SPVM_STRING_BUFFER* string_buffer, int8_t value) {
  
  
  int32_t max_length = 20;
  
  int32_t new_max_length = string_buffer->length + max_length;
  
  // Extend
  SPVM_STRING_BUFFER_maybe_extend(string_buffer, new_max_length);
  
  int32_t write_length = sprintf(string_buffer->buffer + string_buffer->length, "%" PRId8, value);
  
  string_buffer->length += write_length;
  
  return;
}

void SPVM_STRING_BUFFER_add_short(SPVM_STRING_BUFFER* string_buffer, int16_t value) {
  
  
  int32_t max_length = 20;
  
  int32_t new_max_length = string_buffer->length + max_length;
  
  // Extend
  SPVM_STRING_BUFFER_maybe_extend(string_buffer, new_max_length);
  
  int32_t write_length = sprintf(string_buffer->buffer + string_buffer->length, "%" PRId16, value);
  
  string_buffer->length += write_length;
  
  return;
}

void SPVM_STRING_BUFFER_add_int(SPVM_STRING_BUFFER* string_buffer, int32_t value) {
  
  
  int32_t max_length = 20;
  
  int32_t new_max_length = string_buffer->length + max_length;
  
  // Extend
  SPVM_STRING_BUFFER_maybe_extend(string_buffer, new_max_length);
  
  int32_t write_length = sprintf(string_buffer->buffer + string_buffer->length, "%" PRId32, value);
  
  string_buffer->length += write_length;
  
  return;
}

void SPVM_STRING_BUFFER_add_long(SPVM_STRING_BUFFER* string_buffer, int64_t value) {
  
  
  int32_t max_length = 20;
  
  int32_t new_max_length = string_buffer->length + max_length;
  
  // Extend
  SPVM_STRING_BUFFER_maybe_extend(string_buffer, new_max_length);
  
  int32_t write_length = sprintf(string_buffer->buffer + string_buffer->length, "%" PRId64, value);
  
  string_buffer->length += write_length;
  
  return;
}

void SPVM_STRING_BUFFER_add_float(SPVM_STRING_BUFFER* string_buffer, float value) {
  
  
  int32_t max_length = 20;
  
  int32_t new_max_length = string_buffer->length + max_length;
  
  // Extend
  SPVM_STRING_BUFFER_maybe_extend(string_buffer, new_max_length);
  
  int32_t write_length = sprintf(string_buffer->buffer + string_buffer->length, "%.40f", value);
  
  string_buffer->length += write_length;
  
  return;
}

void SPVM_STRING_BUFFER_add_double(SPVM_STRING_BUFFER* string_buffer, double value) {
  
  
  int32_t max_length = 20;
  
  int32_t new_max_length = string_buffer->length + max_length;
  
  // Extend
  SPVM_STRING_BUFFER_maybe_extend(string_buffer, new_max_length);
  
  int32_t write_length = sprintf(string_buffer->buffer + string_buffer->length, "%.70f", value);
  
  string_buffer->length += write_length;
  
  return;
}

void SPVM_STRING_BUFFER_free(SPVM_STRING_BUFFER* string_buffer) {
  
  
  free(string_buffer->buffer);
  
  free(string_buffer);
}
