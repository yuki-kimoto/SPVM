// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_COMPILER_STRING_BUFFER_H
#define SPVM_COMPILER_STRING_BUFFER_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

struct spvm_compiler_string_buffer {
  SPVM_ALLOCATOR* allocator;
  char* string;
  int32_t capacity;
  int32_t length;
  int8_t memory_block_type;
  SPVM_ENV* env;
};

SPVM_COMPILER_STRING_BUFFER* SPVM_COMPILER_STRING_BUFFER_new(SPVM_ALLOCATOR* allocator, int32_t capacity, int32_t memory_block_type);
char* SPVM_COMPILER_STRING_BUFFER_get_buffer(SPVM_COMPILER_STRING_BUFFER* string_buffer);
void SPVM_COMPILER_STRING_BUFFER_maybe_extend(SPVM_COMPILER_STRING_BUFFER* string_buffer, int32_t new_length);

int32_t SPVM_COMPILER_STRING_BUFFER_add(SPVM_COMPILER_STRING_BUFFER* string_buffer, const char* string);
int32_t SPVM_COMPILER_STRING_BUFFER_add_len(SPVM_COMPILER_STRING_BUFFER* string_buffer, char* string, int32_t string_length);
int32_t SPVM_COMPILER_STRING_BUFFER_add_hex_char(SPVM_COMPILER_STRING_BUFFER* string_buffer, char ch);
int32_t SPVM_COMPILER_STRING_BUFFER_add_byte(SPVM_COMPILER_STRING_BUFFER* string_buffer, int8_t value);
int32_t SPVM_COMPILER_STRING_BUFFER_add_short(SPVM_COMPILER_STRING_BUFFER* string_buffer, int16_t value);
int32_t SPVM_COMPILER_STRING_BUFFER_add_int(SPVM_COMPILER_STRING_BUFFER* string_buffer, int32_t value);
int32_t SPVM_COMPILER_STRING_BUFFER_add_long(SPVM_COMPILER_STRING_BUFFER* string_buffer, int64_t value);

void SPVM_COMPILER_STRING_BUFFER_free(SPVM_COMPILER_STRING_BUFFER* string_buffer);

int32_t SPVM_COMPILER_STRING_BUFFER_add_len_nullstr(SPVM_COMPILER_STRING_BUFFER* string_buffer, char* string, int32_t string_length);

SPVM_COMPILER_STRING_BUFFER* SPVM_COMPILER_STRING_BUFFER_new_tmp(SPVM_ALLOCATOR* allocator, int32_t capacity);

int32_t SPVM_COMPILER_STRING_BUFFER_contains(SPVM_COMPILER_STRING_BUFFER* string_buffer, int32_t offset, const char* string);

void SPVM_PRECOMPILE_add_basic_type_id(SPVM_PRECOMPILE* precompile, SPVM_COMPILER_STRING_BUFFER* string_buffer, const char* basic_type_name);

#endif
