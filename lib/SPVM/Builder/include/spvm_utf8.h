// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_UTF8_H
#define SPVM_UTF8_H

#include "spvm_typedecl.h"

int32_t SPVM_UTF8_iterate(const uint8_t *str, size_t strlen, int32_t *dst);

int32_t SPVM_UTF8_is_valid_utf8_code_point(int32_t code_point);

int32_t SPVM_UTF8_is_unicode_scalar_value(int32_t code_point);

int32_t SPVM_UTF8_convert_unicode_codepoint_to_utf8_character(int32_t uc, uint8_t* dst);

int32_t SPVM_UTF8_is_utf8(const char* str, size_t len);

#endif
