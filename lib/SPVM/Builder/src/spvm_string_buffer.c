#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "spvm_string_buffer.h"
#include "spvm_util_allocator.h"
#include "spvm_compiler.h"
#include "spvm_compiler_allocator.h"

SPVM_STRING_BUFFER* SPVM_STRING_BUFFER_new(SPVM_COMPILER* compiler, int32_t capacity) {
  
  if (capacity == 0) {
    capacity = 16;
  }
  
  SPVM_STRING_BUFFER* string_buffer = (SPVM_STRING_BUFFER*)SPVM_COMPILER_ALLOCATOR_safe_malloc_zero_tmp(compiler, sizeof(SPVM_STRING_BUFFER));
  
  string_buffer->capacity = capacity;
  string_buffer->buffer = (char*)SPVM_COMPILER_ALLOCATOR_safe_malloc_zero_tmp(compiler, capacity);
  
  string_buffer->compiler = compiler;

  return string_buffer;
}

char* SPVM_STRING_BUFFER_get_buffer(SPVM_STRING_BUFFER* string_buffer) {
  
  return string_buffer->buffer;
}

void SPVM_STRING_BUFFER_maybe_extend(SPVM_STRING_BUFFER* string_buffer, int32_t new_length) {

  SPVM_COMPILER* compiler = string_buffer->compiler;

  // Extend
  while (new_length > string_buffer->capacity) {
    int32_t new_capacity = string_buffer->capacity * 2;
    char* new_buffer = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero_tmp(compiler, new_capacity);
    memcpy(new_buffer, string_buffer->buffer, string_buffer->length);
    SPVM_COMPILER_ALLOCATOR_free_tmp(compiler, string_buffer->buffer);
    string_buffer->buffer = new_buffer;
    string_buffer->capacity = new_capacity;
  }
}

int32_t SPVM_STRING_BUFFER_add_class_name(SPVM_STRING_BUFFER* string_buffer, const char* class_name) {
  
  int32_t id = string_buffer->length;
  
  SPVM_STRING_BUFFER_add(string_buffer, (char*)class_name);
  {
    int32_t index = string_buffer->length - strlen(class_name);
    
    while (index < string_buffer->length) {
      if (string_buffer->buffer[index] == ':') {
        string_buffer->buffer[index] = '_';
      }
      index++;
    }
  }
  
  return id;
}

int32_t SPVM_STRING_BUFFER_add_field_access_id_name(SPVM_STRING_BUFFER* string_buffer, const char* cur_class_name, const char* access_class_name, const char* field_name) {
  (void)cur_class_name;
  
  int32_t id = string_buffer->length;
  
  SPVM_STRING_BUFFER_add_class_name(string_buffer, cur_class_name);
  SPVM_STRING_BUFFER_add(string_buffer, "_ACCESS_FIELD_ID_");
  SPVM_STRING_BUFFER_add_class_name(string_buffer, access_class_name);
  SPVM_STRING_BUFFER_add(string_buffer, "__");
  SPVM_STRING_BUFFER_add_class_name(string_buffer, field_name);
  
  return id;
}

int32_t SPVM_STRING_BUFFER_add_field_access_offset_name(SPVM_STRING_BUFFER* string_buffer, const char* cur_class_name, const char* access_class_name, const char* field_name) {
  (void)cur_class_name;
  
  int32_t id = string_buffer->length;
  
  SPVM_STRING_BUFFER_add_class_name(string_buffer, cur_class_name);
  SPVM_STRING_BUFFER_add(string_buffer, "_ACCESS_FIELD_BYTE_OFFSET_");
  SPVM_STRING_BUFFER_add_class_name(string_buffer, access_class_name);
  SPVM_STRING_BUFFER_add(string_buffer, "__");
  SPVM_STRING_BUFFER_add_class_name(string_buffer, field_name);
  
  return id;
}

int32_t SPVM_STRING_BUFFER_add_method_access_id_name(SPVM_STRING_BUFFER* string_buffer, const char* cur_class_name, const char* access_class_name, const char* method_name) {
  (void)cur_class_name;
  
  int32_t id = string_buffer->length;

  SPVM_STRING_BUFFER_add_class_name(string_buffer, cur_class_name);
  SPVM_STRING_BUFFER_add(string_buffer, "_ACCESS_METHOD_ID_");
  SPVM_STRING_BUFFER_add_class_name(string_buffer, access_class_name);
  SPVM_STRING_BUFFER_add(string_buffer, "__");
  SPVM_STRING_BUFFER_add_class_name(string_buffer, method_name);
  
  return id;
}

int32_t SPVM_STRING_BUFFER_add_basic_type_access_id_name(SPVM_STRING_BUFFER* string_buffer, const char* cur_class_name, const char* basic_type_name) {
  (void)cur_class_name;
  
  int32_t id = string_buffer->length;
  
  SPVM_STRING_BUFFER_add_class_name(string_buffer, cur_class_name);
  SPVM_STRING_BUFFER_add(string_buffer, "_ACCESS_BASIC_TYPE_ID_");
  SPVM_STRING_BUFFER_add_class_name(string_buffer, basic_type_name);
  
  return id;
}

int32_t SPVM_STRING_BUFFER_add_class_var_access_id_name(SPVM_STRING_BUFFER* string_buffer, const char* cur_class_name, const char* access_class_name, const char* class_var_name) {
  (void)cur_class_name;
  
  int32_t id = string_buffer->length;
  
  SPVM_STRING_BUFFER_add_class_name(string_buffer, cur_class_name);
  SPVM_STRING_BUFFER_add(string_buffer, "_ACCESS_CLASS_VAR_ID_");
  SPVM_STRING_BUFFER_add_class_name(string_buffer, access_class_name);
  SPVM_STRING_BUFFER_add(string_buffer, "__");
  SPVM_STRING_BUFFER_add_class_name(string_buffer, &class_var_name[1]);
  
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

  SPVM_COMPILER* compiler = string_buffer->compiler;
  
  SPVM_COMPILER_ALLOCATOR_free_tmp(compiler, string_buffer->buffer);
  
  SPVM_COMPILER_ALLOCATOR_free_tmp(compiler, string_buffer);
}
