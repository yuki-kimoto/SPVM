#ifndef SPVM_STRING_BUFFER_H
#define SPVM_STRING_BUFFER_H

#include "spvm_base.h"

struct SPVM_string_buffer {
  char* buffer;
  int32_t capacity;
  int32_t length;
};

SPVM_STRING_BUFFER* SPVM_STRING_BUFFER_new(int32_t capacity);
char* SPVM_STRING_BUFFER_get_buffer(SPVM_STRING_BUFFER* string_buffer);
void SPVM_STRING_BUFFER_add_package_name(SPVM_STRING_BUFFER* string_buffer, const char* package_name);
void SPVM_STRING_BUFFER_add_field_index_name(SPVM_STRING_BUFFER* string_buffer, const char* package_name, const char* field_name);
void SPVM_STRING_BUFFER_add_sub_id_name(SPVM_STRING_BUFFER* string_buffer, const char* package_name, const char* sub_name);
void SPVM_STRING_BUFFER_add_basic_type_id_name(SPVM_STRING_BUFFER* string_buffer, const char* basic_type_name);
void SPVM_STRING_BUFFER_add_package_var_id_name(SPVM_STRING_BUFFER* string_buffer, const char* package_name, const char* package_var_name);
void SPVM_STRING_BUFFER_maybe_extend(SPVM_STRING_BUFFER* string_buffer, int32_t new_length);
void SPVM_STRING_BUFFER_add(SPVM_STRING_BUFFER* string_buffer, char* string);
void SPVM_STRING_BUFFER_add_hex_char(SPVM_STRING_BUFFER* string_buffer, char ch);
void SPVM_STRING_BUFFER_add_len(SPVM_STRING_BUFFER* string_buffer, char* string, int32_t string_length);
void SPVM_STRING_BUFFER_add_byte(SPVM_STRING_BUFFER* string_buffer, int8_t value);
void SPVM_STRING_BUFFER_add_short(SPVM_STRING_BUFFER* string_buffer, int16_t value);
void SPVM_STRING_BUFFER_add_int(SPVM_STRING_BUFFER* string_buffer, int32_t value);
void SPVM_STRING_BUFFER_add_long(SPVM_STRING_BUFFER* string_buffer, int64_t value);
void SPVM_STRING_BUFFER_add_float(SPVM_STRING_BUFFER* string_buffer, float value);
void SPVM_STRING_BUFFER_add_double(SPVM_STRING_BUFFER* string_buffer, double value);
void SPVM_STRING_BUFFER_free(SPVM_STRING_BUFFER* string_buffer);
  
#endif
