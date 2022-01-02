#ifndef SPVM_STRING_BUFFER_H
#define SPVM_STRING_BUFFER_H

#include "spvm_typedecl.h"

struct spvm_string_buffer {
  SPVM_COMPILER* compiler;
  char* buffer;
  int32_t capacity;
  int32_t length;
  int8_t memory_block_type;
};

SPVM_STRING_BUFFER* SPVM_STRING_BUFFER_new(SPVM_COMPILER* compiler, int32_t capacity, int32_t memory_block_type);
char* SPVM_STRING_BUFFER_get_buffer(SPVM_STRING_BUFFER* string_buffer);
void SPVM_STRING_BUFFER_maybe_extend(SPVM_STRING_BUFFER* string_buffer, int32_t new_length);

int32_t SPVM_STRING_BUFFER_add_field_access_id_name(SPVM_STRING_BUFFER* string_buffer, const char* cur_class_name, const char* access_class_name, const char* field_name);
int32_t SPVM_STRING_BUFFER_add_field_access_offset_name(SPVM_STRING_BUFFER* string_buffer, const char* cur_class_name, const char* access_class_name, const char* field_name);
int32_t SPVM_STRING_BUFFER_add_method_access_id_name(SPVM_STRING_BUFFER* string_buffer, const char* cur_class_name, const char* access_class_name, const char* method_name);
int32_t SPVM_STRING_BUFFER_add_basic_type_access_id_name(SPVM_STRING_BUFFER* string_buffer, const char* cur_class_name, const char* basic_type_name);
int32_t SPVM_STRING_BUFFER_add_class_var_access_id_name(SPVM_STRING_BUFFER* string_buffer, const char* cur_class_name, const char* access_class_name, const char* class_var_name);

int32_t SPVM_STRING_BUFFER_add_class_name(SPVM_STRING_BUFFER* string_buffer, const char* class_name);
int32_t SPVM_STRING_BUFFER_add(SPVM_STRING_BUFFER* string_buffer, const char* string);
int32_t SPVM_STRING_BUFFER_add_len(SPVM_STRING_BUFFER* string_buffer, char* string, int32_t string_length);
int32_t SPVM_STRING_BUFFER_add_hex_char(SPVM_STRING_BUFFER* string_buffer, char ch);
int32_t SPVM_STRING_BUFFER_add_char(SPVM_STRING_BUFFER* string_buffer, int8_t value);
int32_t SPVM_STRING_BUFFER_add_short(SPVM_STRING_BUFFER* string_buffer, int16_t value);
int32_t SPVM_STRING_BUFFER_add_int(SPVM_STRING_BUFFER* string_buffer, int32_t value);
int32_t SPVM_STRING_BUFFER_add_long(SPVM_STRING_BUFFER* string_buffer, int64_t value);
int32_t SPVM_STRING_BUFFER_add_float(SPVM_STRING_BUFFER* string_buffer, float value);
int32_t SPVM_STRING_BUFFER_add_double(SPVM_STRING_BUFFER* string_buffer, double value);

void SPVM_STRING_BUFFER_free(SPVM_STRING_BUFFER* string_buffer);
  
#endif
