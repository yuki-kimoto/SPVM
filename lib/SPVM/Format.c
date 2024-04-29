// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static const char* FILE_NAME = "Format.c";

int32_t SPVM__Format___native_snprintf_d(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t value = stack[0].ival;
  
  // "-2147483648"
  char formatted_string[12] = {0};
  
  int32_t length = snprintf(formatted_string, 12, "%"PRId32, value);
  
  stack[0].oval = env->new_string(env, stack, formatted_string, length);
  
  return 0;
}

int32_t SPVM__Format___native_snprintf_f(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  double value = stack[0].dval;
  int32_t precision = stack[1].ival;
  
  // "%." "2147483647" "f": 2 + 11 + 1
  char specifier[14] = {0};
  if (precision >= 0) {
    snprintf(specifier, 14, "%%.%" PRId32 "f", precision);
  }
  else {
    snprintf(specifier, 14, "%%f");
  }
  
  // "-9223372036854775808" + "." + width + precision
  int32_t max_length = 20 + 1 + precision;
  void* obj_formatted_string = env->new_string(env, stack, NULL, max_length);
  
  char* formatted_string = (char*)env->get_chars(env, stack, obj_formatted_string);
  
  int32_t length = snprintf(formatted_string, max_length + 1, specifier, value);
  
  stack[0].oval = env->new_string(env, stack, formatted_string, length);
  
  return 0;
}

int32_t SPVM__Format___native_snprintf_g(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  double value = stack[0].dval;
  int32_t precision = stack[1].ival;
  
  // "%." "2147483647" "f": 2 + 11 + 1
  char specifier[14] = {0};
  if (precision >= 0) {
    snprintf(specifier, 14, "%%.%" PRId32 "g", precision);
  }
  else {
    snprintf(specifier, 14, "%%g");
  }
  
  // "-9223372036854775808" + "." + width + precision
  int32_t max_length = 20 + 1 + precision;
  void* obj_formatted_string = env->new_string(env, stack, NULL, max_length);
  
  char* formatted_string = (char*)env->get_chars(env, stack, obj_formatted_string);
  
  int32_t length = snprintf(formatted_string, max_length + 1, specifier, value);
  
  stack[0].oval = env->new_string(env, stack, formatted_string, length);
  
  return 0;
}

int32_t SPVM__Format___native_snprintf_ld(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int64_t value = stack[0].lval;
  
  // "-9223372036854775808"
  char formatted_string[21] = {0};
  
  int32_t length = snprintf(formatted_string, 21, "%"PRId64, value);
  
  stack[0].oval = env->new_string(env, stack, formatted_string, length);
  
  return 0;
}

int32_t SPVM__Format___native_snprintf_lu(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  uint64_t value = (uint64_t)stack[0].lval;
  
  // "18446744073709551615"
  char formatted_string[21] = {0};
  
  int32_t length = snprintf(formatted_string, 21, "%"PRIu64, value);
  
  stack[0].oval = env->new_string(env, stack, formatted_string, length);
  
  return 0;
}

int32_t SPVM__Format___native_snprintf_lx(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  uint64_t value = (uint64_t)stack[0].lval;
  
  // "ffffffffffffffff"
  char formatted_string[17] = {0};
  
  int32_t length = snprintf(formatted_string, 17, "%"PRIx64, value);
  
  stack[0].oval = env->new_string(env, stack, formatted_string, length);
  
  return 0;
}
int32_t SPVM__Format___native_snprintf_p(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* value = stack[0].oval;
  
  // 0x8000000000000000
  int32_t max_length = 32;
  void* obj_formatted_string = env->new_string(env, stack, NULL, max_length);
  
  char* formatted_string = (char*)env->get_chars(env, stack, obj_formatted_string);
  
  int32_t length = snprintf(formatted_string, max_length + 1, "0x%"PRIxPTR, (uintptr_t)value);
  
  stack[0].oval = env->new_string(env, stack, formatted_string, length);
  
  return 0;
}

int32_t SPVM__Format___native_snprintf_u(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  uint32_t value = (uint32_t)stack[0].ival;
  
  // "4294967295"
  char formatted_string[11] = {0};
  
  int32_t length = snprintf(formatted_string, 11, "%"PRIu32, value);
  
  stack[0].oval = env->new_string(env, stack, formatted_string, length);
  
  return 0;
}

int32_t SPVM__Format___native_snprintf_x(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  uint32_t value = (uint32_t)stack[0].ival;
  
  // "ffffffff"
  char formatted_string[9] = {0};
  
  int32_t length = snprintf(formatted_string, 9, "%"PRIx32, value);
  
  stack[0].oval = env->new_string(env, stack, formatted_string, length);
  
  return 0;
}
