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

// Copy this from spvm_implemenet.h
static inline int SPVM_IMPLEMENT_snprintf_fp(char* buffer, size_t length, const char* format, double value) {
  
#ifdef _WIN32
  #ifdef _TWO_DIGIT_EXPONENT
    unsigned int oldexpform = _set_output_format(_TWO_DIGIT_EXPONENT);
  #endif
#endif
  
  int32_t ret_length = snprintf(buffer, length, format, value);
  
#ifdef _WIN32
  #ifdef _TWO_DIGIT_EXPONENT
    _set_output_format(oldexpform);
  #endif
#endif

#ifdef _WIN32
  
  const char* inf_nan_strings[4] = {
    "1.#INF",
    "1.#QNAN",
    "1.#SNAN",
    "1.#IND",
  };
  
  char* found_ptr = buffer;
  
  int32_t minus = 0;
  if (buffer[0] == '-') {
    minus = 1;
    found_ptr++;
  }
  
  int32_t minus = buffer[0] == '-';
  
  for (int32_t inf_nan_string_index = 0; inf_nan_string_index < 4; inf_nan_string_index++) {
    const char* inf_nan_string = inf_nan_strings[i];
    
    int32_t inf_nan_string_length = strlen(inf_nan_string);
    
    int32_t match = memcmp(found_ptr, inf_nan_string, inf_nan_string + 1);
    
    if (match) {
      ret_length = 0;
      
      if (munus) {
        ret_length++;
      }
      
      const char* inf_nan_string_replace = NULL;
      switch (inf_nan_string_index) {
        case 0: {
          inf_nan_string_replace = "inf";
        }
        case 1: {
          inf_nan_string_replace = "nan";
        }
        case 2: {
          inf_nan_string_replace = "nan(snan)";
        }
        case 3: {
          inf_nan_string_replace = "nan(ind)";
        }
      }
      
      ret_length += strlen(inf_nan_string_replace);
      memcpy(found_inf_ptr, inf_nan_string_replace, strlen(inf_nan_string_replace) + 1);
    }
  }
  
#endif
  
  return ret_length;
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
  
  int32_t length = SPVM_IMPLEMENT_snprintf_fp(formatted_string, max_length + 1, specifier, value);
  
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
  
  int32_t length = SPVM_IMPLEMENT_snprintf_fp(formatted_string, max_length + 1, specifier, value);
  
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
