#include <stdlib.h>
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
  
  // Zero is not used because 0 mean string is not exists in string symbol table
  string_buffer->length = 1;
  
  return string_buffer;
}

char* SPVM_STRING_BUFFER_get_buffer(SPVM_STRING_BUFFER* string_buffer) {
  
  return string_buffer->buffer;
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

int32_t SPVM_STRING_BUFFER_add_package_name(SPVM_STRING_BUFFER* string_buffer, const char* package_name) {
  
  int32_t id = string_buffer->length;
  
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
  
  return id;
}

int32_t SPVM_STRING_BUFFER_add_field_id_name(SPVM_STRING_BUFFER* string_buffer, const char* package_name, const char* field_name) {
  
  int32_t id = string_buffer->length;
  
  SPVM_STRING_BUFFER_add(string_buffer, "FIELD_ID_");
  SPVM_STRING_BUFFER_add_package_name(string_buffer, package_name);
  SPVM_STRING_BUFFER_add(string_buffer, "__");
  SPVM_STRING_BUFFER_add_package_name(string_buffer, field_name);
  
  return id;
}

int32_t SPVM_STRING_BUFFER_add_field_offset_name(SPVM_STRING_BUFFER* string_buffer, const char* package_name, const char* field_name) {
  
  int32_t id = string_buffer->length;
  
  SPVM_STRING_BUFFER_add(string_buffer, "FIELD_BYTE_OFFSET_");
  SPVM_STRING_BUFFER_add_package_name(string_buffer, package_name);
  SPVM_STRING_BUFFER_add(string_buffer, "__");
  SPVM_STRING_BUFFER_add_package_name(string_buffer, field_name);
  
  return id;
}

int32_t SPVM_STRING_BUFFER_add_sub_id_name(SPVM_STRING_BUFFER* string_buffer, const char* package_name, const char* sub_name) {
  
  int32_t id = string_buffer->length;

  SPVM_STRING_BUFFER_add(string_buffer, "SUB_ID_");
  SPVM_STRING_BUFFER_add_package_name(string_buffer, package_name);
  SPVM_STRING_BUFFER_add(string_buffer, "__");
  SPVM_STRING_BUFFER_add_package_name(string_buffer, sub_name);
  
  return id;
}

int32_t SPVM_STRING_BUFFER_add_basic_type_id_name(SPVM_STRING_BUFFER* string_buffer, const char* basic_type_name) {
  
  int32_t id = string_buffer->length;
  
  SPVM_STRING_BUFFER_add(string_buffer, "BASIC_TYPE_ID_");
  SPVM_STRING_BUFFER_add_package_name(string_buffer, basic_type_name);
  
  return id;
}

int32_t SPVM_STRING_BUFFER_add_package_var_id_name(SPVM_STRING_BUFFER* string_buffer, const char* package_name, const char* package_var_name) {
  
  int32_t id = string_buffer->length;
  
  SPVM_STRING_BUFFER_add(string_buffer, "VAR_PACKAGE_VAR_ID_");
  SPVM_STRING_BUFFER_add_package_name(string_buffer, package_name);
  SPVM_STRING_BUFFER_add(string_buffer, "__");
  SPVM_STRING_BUFFER_add_package_name(string_buffer, &package_var_name[1]);
  
  return id;
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

int32_t SPVM_STRING_BUFFER_add_float(SPVM_STRING_BUFFER* string_buffer, float value) {

  int32_t id = string_buffer->length;
  
  int32_t max_length = 100;
  
  int32_t new_max_length = string_buffer->length + max_length;
  
  // Extend
  SPVM_STRING_BUFFER_maybe_extend(string_buffer, new_max_length);
  
  int32_t write_length = sprintf(string_buffer->buffer + string_buffer->length, "%a", value);
  
  string_buffer->length += write_length;
  
  return id;
}

int32_t SPVM_STRING_BUFFER_add_double(SPVM_STRING_BUFFER* string_buffer, double value) {

  int32_t id = string_buffer->length;
  
  int32_t max_length = 100;
  
  int32_t new_max_length = string_buffer->length + max_length;
  
  // Extend
  SPVM_STRING_BUFFER_maybe_extend(string_buffer, new_max_length);

  int32_t write_length = sprintf(string_buffer->buffer + string_buffer->length, "%a", value);
  
  string_buffer->length += write_length;

  return id;
}

void SPVM_STRING_BUFFER_free(SPVM_STRING_BUFFER* string_buffer) {
  
  free(string_buffer->buffer);
  
  free(string_buffer);
}
