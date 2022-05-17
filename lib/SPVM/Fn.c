#include "spvm_native.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <float.h>
#include <complex.h>
#include <memory.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <float.h>
#include <complex.h>
#include <memory.h>
#include <ctype.h>
#include <errno.h>

static const char* MFILE = "SPVM/Fn.c";

int32_t SPVM__Fn__FLT_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].fval = FLT_MAX;
  
  return 0;
}

int32_t SPVM__Fn__FLT_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].fval = FLT_MIN;
  
  return 0;
}

int32_t SPVM__Fn__DBL_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = DBL_MAX;
  
  return 0;
}

int32_t SPVM__Fn__DBL_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = DBL_MIN;
  
  return 0;
}

// https://code.woboq.org/userspace/glibc/stdlib/rand_r.c.html
static int
SPVM__Fn__rand_r (uint32_t *seed)
{
  uint32_t next = *seed;
  int result;
  next *= 1103515245;
  next += 12345;
  result = (uint32_t) (next / 65536) % 2048;
  next *= 1103515245;
  next += 12345;
  result <<= 10;
  result ^= (uint32_t) (next / 65536) % 1024;
  next *= 1103515245;
  next += 12345;
  result <<= 10;
  result ^= (uint32_t) (next / 65536) % 1024;
  *seed = next;
  return result;
}

int32_t SPVM__Fn__crand(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t* seed_ref = stack[0].iref;
  
  int32_t random_value = SPVM__Fn__rand_r(seed_ref);

  stack[0].ival = random_value;

  return 0;
}

int32_t SPVM__Fn__RAND_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  stack[0].ival = 2147483647;

  return 0;
}


#define SPRINTF_MAX_RESULT_LEN 256

int32_t SPVM__Fn__is_array(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  void* object = stack[0].oval;
  
  int32_t is_array;
  if (env->is_array(env, object)) {
    is_array = 1;
  }
  else {
    is_array = 0;
  }

  stack[0].ival = is_array;

  return 0;
}

int32_t SPVM__Fn__is_numeric_array(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  void* object = stack[0].oval;
  
  int32_t is_numeric_array;
  if (env->is_numeric_array(env, object)) {
    is_numeric_array = 1;
  }
  else {
    is_numeric_array = 0;
  }

  stack[0].ival = is_numeric_array;

  return 0;
}

int32_t SPVM__Fn__is_object_array(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  void* object = stack[0].oval;
  
  int32_t is_object_array;
  if (env->is_object_array(env, object)) {
    is_object_array = 1;
  }
  else {
    is_object_array = 0;
  }

  stack[0].ival = is_object_array;

  return 0;
}

int32_t SPVM__Fn__is_mulnum_array(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  void* object = stack[0].oval;
  
  int32_t is_mulnum_array;
  if (env->is_mulnum_array(env, object)) {
    is_mulnum_array = 1;
  }
  else {
    is_mulnum_array = 0;
  }

  stack[0].ival = is_mulnum_array;

  return 0;
}

int32_t SPVM__Fn__shorten(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  void* string = stack[0].oval;
  int32_t new_length = stack[1].ival;
  
  env->shorten(env, string, new_length);

  return 0;
}

int32_t SPVM__Fn___snsprintf_double(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  void* obj_format = stack[0].oval;
  if (!obj_format) { return env->die(env, "Format must be defined", MFILE, __LINE__); }

  const char* format = env->get_chars(env, obj_format);
  const double value = stack[1].dval;

  char tmp_result[SPRINTF_MAX_RESULT_LEN] = {};

  const int result_len = snprintf(tmp_result, SPRINTF_MAX_RESULT_LEN, format, value);
  if (result_len < 0) { return env->die(env, "snprintf fail", MFILE, __LINE__); }

  stack[0].oval = env->new_string(env, tmp_result, result_len);

  return 0;
}

int32_t SPVM__Fn___native_snprintf_f(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

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
  void* obj_formatted_string = env->new_string(env, NULL, max_length);
  
  char* formatted_string = (char*)env->get_chars(env, obj_formatted_string);

  int32_t length = snprintf(formatted_string, max_length + 1, specifier, value);

  stack[0].oval = env->new_string(env, formatted_string, length);

  return 0;
}

int32_t SPVM__Fn___native_snprintf_g(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

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
  void* obj_formatted_string = env->new_string(env, NULL, max_length);
  
  char* formatted_string = (char*)env->get_chars(env, obj_formatted_string);

  int32_t length = snprintf(formatted_string, max_length + 1, specifier, value);

  stack[0].oval = env->new_string(env, formatted_string, length);

  return 0;
}

int32_t SPVM__Fn___native_snprintf_d(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  int32_t value = stack[0].ival;
  
  // "-2147483648"
  char formatted_string[12] = {0};

  int32_t length = snprintf(formatted_string, 12, "%"PRId32, value);

  stack[0].oval = env->new_string(env, formatted_string, length);

  return 0;
}

int32_t SPVM__Fn___native_snprintf_ld(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  int64_t value = stack[0].lval;
  
  // "-9223372036854775808"
  char formatted_string[21] = {0};

  int32_t length = snprintf(formatted_string, 21, "%"PRId64, value);

  stack[0].oval = env->new_string(env, formatted_string, length);

  return 0;
}

int32_t SPVM__Fn___native_snprintf_u(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  uint32_t value = (uint32_t)stack[0].ival;
  
  // "4294967295"
  char formatted_string[11] = {0};

  int32_t length = snprintf(formatted_string, 11, "%"PRIu32, value);

  stack[0].oval = env->new_string(env, formatted_string, length);

  return 0;
}

int32_t SPVM__Fn___native_snprintf_lu(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  uint64_t value = (uint64_t)stack[0].lval;
  
  // "18446744073709551615"
  char formatted_string[21] = {0};

  int32_t length = snprintf(formatted_string, 21, "%"PRIu64, value);

  stack[0].oval = env->new_string(env, formatted_string, length);

  return 0;
}

int32_t SPVM__Fn___native_snprintf_x(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  uint32_t value = (uint32_t)stack[0].ival;
  
  // "ffffffff"
  char formatted_string[9] = {0};

  int32_t length = snprintf(formatted_string, 9, "%"PRIx32, value);

  stack[0].oval = env->new_string(env, formatted_string, length);

  return 0;
}

int32_t SPVM__Fn___native_snprintf_lx(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  uint64_t value = (uint64_t)stack[0].lval;
  
  // "ffffffffffffffff"
  char formatted_string[17] = {0};

  int32_t length = snprintf(formatted_string, 17, "%"PRIx64, value);

  stack[0].oval = env->new_string(env, formatted_string, length);

  return 0;
}

int32_t SPVM__Fn__to_int_with_base(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_string = stack[0].oval;
  if (!obj_string) {
    return env->die(env, "String must be defined", MFILE, __LINE__);
  }
  const char* string = env->get_chars(env, obj_string);
  
  int32_t digit = stack[1].ival;
  
  if (!(digit == 2 || digit == 8 || digit == 10 || digit == 16)) {
    return env->die(env, "Digit must be 2, 8, 10, 16", MFILE, __LINE__);
  }
  
  char *end;
  errno = 0;
  long int num = strtol(string, &end, digit);
  if (*end != '\0') {
    return env->die(env, "Invalid number format", MFILE, __LINE__);
  }
  else if (errno == ERANGE || num < INT32_MIN || num > INT32_MAX) {
    return env->die(env, "Out of range", MFILE, __LINE__);
  }
  
  stack[0].ival = (int32_t)num;

  return 0;
}

int32_t SPVM__Fn__to_long_with_base(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_string = stack[0].oval;
  if (!obj_string) {
    return env->die(env, "String must be defined", MFILE, __LINE__);
  }
  const char* string = env->get_chars(env, obj_string);
  
  int32_t digit = stack[1].ival;

  if (!(digit == 2 || digit == 8 || digit == 10 || digit == 16)) {
    return env->die(env, "Digit must be 2, 8, 10, 16", MFILE, __LINE__);
  }
  
  char *end;
  errno = 0;
  long long int num = strtoll(string, &end, digit);
  if (*end != '\0') {
    return env->die(env, "Invalid number format", MFILE, __LINE__);
  }
  else if (errno == ERANGE || num < INT64_MIN || num > INT64_MAX) {
    return env->die(env, "Out of range", MFILE, __LINE__);
  }
  
  stack[0].lval = (int64_t)num;

  return 0;
}

int32_t SPVM__Fn__to_float(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_string = stack[0].oval;
  if (!obj_string) {
    return env->die(env, "String must be defined", MFILE, __LINE__);
  }
  const char* string = env->get_chars(env, obj_string);
  
  char *end;
  errno = 0;
  float num = strtof(string, &end);
  if (*end != '\0') {
    return env->die(env, "Invalid number format", MFILE, __LINE__);
  }
  else if (errno == ERANGE) {
    return env->die(env, "[ERANGE]Out of range", MFILE, __LINE__);
  }
  
  stack[0].fval = num;

  return 0;
}

int32_t SPVM__Fn__to_double(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_string = stack[0].oval;
  if (!obj_string) {
    return env->die(env, "String must be defined", MFILE, __LINE__);
  }
  const char* string = env->get_chars(env, obj_string);
  
  char *end;
  errno = 0;
  double num = strtod(string, &end);
  if (*end != '\0') {
    return env->die(env, "Invalid number format", MFILE, __LINE__);
  }
  else if (errno == ERANGE) {
    return env->die(env, "[ERANGE]Out of range", MFILE, __LINE__);
  }
  
  stack[0].dval = num;

  return 0;
}

int32_t SPVM__Fn__memcpy(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* dest = stack[0].oval;
  int32_t dest_byte_offset = stack[1].ival;
  void* source = stack[2].oval;
  int32_t source_byte_offset = stack[3].ival;
  int32_t byte_length = stack[4].ival;

  if (!dest) {
    return env->die(env, "Destnation must be defined", MFILE, __LINE__);
  }
  
  if (!(env->is_string(env, dest) || env->is_numeric_array(env, dest) || env->is_mulnum_array(env, dest))) {
    return env->die(env, "Destnation must be a string type, a numeric arrya type, or a multi numeric array", MFILE, __LINE__);
  }
  
  if (!source) {
    return env->die(env, "Source must be defined", MFILE, __LINE__);
  }

  if (!(env->is_string(env, source) || env->is_numeric_array(env, source) || env->is_mulnum_array(env, source))) {
    return env->die(env, "Source must be a string type, a numeric arrya type, or a multi numeric array", MFILE, __LINE__);
  }

  if (env->is_read_only(env, dest)) {
    return env->die(env, "Destnation must not be a read-only string", MFILE, __LINE__);
  }
  
  if (byte_length == 0) {
    return 0;
  }
  else if (byte_length < 0) {
    return env->die(env, "The length must be more than or equals to 0", MFILE, __LINE__);
  }
  
  char* dest_bytes = (char*)env->get_chars(env, dest);
  int32_t dest_len = env->length(env, dest);
  int32_t dest_elem_byte_size = env->get_elem_byte_size(env, dest);
  int32_t dest_byte_length = dest_elem_byte_size * dest_len;
  
  const char* source_bytes = env->get_chars(env, source);
  int32_t source_len = env->length(env, source);
  int32_t source_elem_byte_size = env->get_elem_byte_size(env, source);
  int32_t source_byte_length = source_elem_byte_size * source_len;
  
  if (dest_byte_offset + byte_length > dest_byte_length) {
    return env->die(env, "Destnation byte_offset + byte_length must be within the range of the destnation array", MFILE, __LINE__);
  }

  if (source_byte_offset + byte_length > source_byte_length) {
    return env->die(env, "Source byte_offset + byte_length must be within the range of the source array", MFILE, __LINE__);
  }
  
  memcpy((char*)(dest_bytes + dest_byte_offset), (char*)(source_bytes + source_byte_offset), byte_length);
  
  return 0;
}

int32_t SPVM__Fn__memmove(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* dest = stack[0].oval;
  int32_t dest_byte_offset = stack[1].ival;
  void* source = stack[2].oval;
  int32_t source_byte_offset = stack[3].ival;
  int32_t byte_length = stack[4].ival;

  if (!dest) {
    return env->die(env, "Destnation must be defined", MFILE, __LINE__);
  }
  
  if (!(env->is_string(env, dest) || env->is_numeric_array(env, dest) || env->is_mulnum_array(env, dest))) {
    return env->die(env, "Destnation must be a string type, a numeric arrya type, or a multi numeric array", MFILE, __LINE__);
  }
  
  if (!source) {
    return env->die(env, "Source must be defined", MFILE, __LINE__);
  }

  if (!(env->is_string(env, source) || env->is_numeric_array(env, source) || env->is_mulnum_array(env, source))) {
    return env->die(env, "Source must be a string type, a numeric arrya type, or a multi numeric array", MFILE, __LINE__);
  }

  if (env->is_read_only(env, dest)) {
    return env->die(env, "Destnation must not be a read-only string", MFILE, __LINE__);
  }
  
  if (byte_length == 0) {
    return 0;
  }
  else if (byte_length < 0) {
    return env->die(env, "The length must be more than or equals to 0", MFILE, __LINE__);
  }
  
  char* dest_bytes = (char*)env->get_chars(env, dest);
  int32_t dest_len = env->length(env, dest);
  int32_t dest_elem_byte_size = env->get_elem_byte_size(env, dest);
  int32_t dest_byte_length = dest_elem_byte_size * dest_len;
  
  const char* source_bytes = env->get_chars(env, source);
  int32_t source_len = env->length(env, source);
  int32_t source_elem_byte_size = env->get_elem_byte_size(env, source);
  int32_t source_byte_length = source_elem_byte_size * source_len;
  
  if (dest_byte_offset + byte_length > dest_byte_length) {
    return env->die(env, "Destnation byte_offset + byte_length must be within the range of the destnation array", MFILE, __LINE__);
  }

  if (source_byte_offset + byte_length > source_byte_length) {
    return env->die(env, "Source byte_offset + byte_length must be within the range of the source array", MFILE, __LINE__);
  }
  
  memmove((char*)(dest_bytes + dest_byte_offset), (char*)(source_bytes + source_byte_offset), byte_length);
  
  return 0;
}

int32_t SPVM__Fn__memcpy_byte(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* sv_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* sv_source = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;

  if (!sv_dest) {
    return env->die(env, "Destnation must be defined", MFILE, __LINE__);
  }
  
  if (!sv_source) {
    return env->die(env, "Source must be defined", MFILE, __LINE__);
  }
  
  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be more than or equals to 0", MFILE, __LINE__);
  }
  
  int8_t* dest = env->get_elems_byte(env, sv_dest);
  int32_t dest_len = env->length(env, sv_dest);
  
  int8_t* source = env->get_elems_byte(env, sv_source);
  int32_t source_len = env->length(env, sv_source);
  
  if (dest_offset + length > dest_len) {
    return env->die(env, "Destnation offset + length must be within the range of the destnation array", MFILE, __LINE__);
  }

  if (source_offset + length > source_len) {
    return env->die(env, "Source offset + length must be within the range of the source array", MFILE, __LINE__);
  }
  
  memcpy((char*)(dest + dest_offset), (char*)(source + source_offset), length);
  
  return 0;
}

int32_t SPVM__Fn__memmove_byte(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* sv_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* sv_source = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;

  if (!sv_dest) { return env->die(env, "Destnation must be defined", MFILE, __LINE__); }
  
  if (!sv_source) { return env->die(env, "Source must be defined", MFILE, __LINE__); }
  
  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be more than or equals to 0", MFILE, __LINE__);
  }
  
  int8_t* dest = env->get_elems_byte(env, sv_dest);
  int32_t dest_len = env->length(env, sv_dest);
  
  int8_t* source = env->get_elems_byte(env, sv_source);
  int32_t source_len = env->length(env, sv_source);
  
  if (dest_offset + length > dest_len) {
    return env->die(env, "Destnation offset + length must be within the range of the destnation array", MFILE, __LINE__);
  }

  if (source_offset + length > source_len) {
    return env->die(env, "Source offset + length must be within the range of the source array", MFILE, __LINE__);
  }
  
  memmove((char*)(dest + dest_offset), (char*)(source + source_offset), length);
  
  return 0;
}

int32_t SPVM__Fn__memcpy_short(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* sv_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* sv_source = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;

  if (!sv_dest) { return env->die(env, "Destnation must be defined", MFILE, __LINE__); }

  if (!sv_source) { return env->die(env, "Source must be defined", MFILE, __LINE__); }
  
  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be more than or equals to 0", MFILE, __LINE__);
  }
  
  int16_t* dest = env->get_elems_short(env, sv_dest);
  int32_t dest_len = env->length(env, sv_dest);
  
  int16_t* source = env->get_elems_short(env, sv_source);
  int32_t source_len = env->length(env, sv_source);
  
  if (dest_offset + length > dest_len) {
    return env->die(env, "Destnation offset + length must be within the range of the destnation array", MFILE, __LINE__);
  }
  
  if (source_offset + length > source_len) {
    return env->die(env, "Source offset + length must be within the range of the source array", MFILE, __LINE__);
  }
  
  memcpy((char*)(dest + dest_offset), (char*)(source + source_offset), length * sizeof(int16_t));
  
  return 0;
}

int32_t SPVM__Fn__memmove_short(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* sv_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* sv_source = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;

  if (!sv_dest) { return env->die(env, "Destnation must be defined", MFILE, __LINE__); }
  
  if (!sv_source) { return env->die(env, "Source must be defined", MFILE, __LINE__); }
  
  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be more than or equals to 0", MFILE, __LINE__);
  }
  
  int16_t* dest = env->get_elems_short(env, sv_dest);
  int32_t dest_len = env->length(env, sv_dest);
  
  int16_t* source = env->get_elems_short(env, sv_source);
  int32_t source_len = env->length(env, sv_source);
  
  if (dest_offset + length > dest_len) {
    return env->die(env, "Destnation offset + length must be within the range of the destnation array", MFILE, __LINE__);
  }

  if (source_offset + length > source_len) {
    return env->die(env, "Source offset + length must be within the range of the source array", MFILE, __LINE__);
  }
  
  memmove((char*)(dest + dest_offset), (char*)(source + source_offset), length * sizeof(int16_t));
  
  return 0;
}

int32_t SPVM__Fn__memcpy_int(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* sv_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* sv_source = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;

  if (!sv_dest) { return env->die(env, "Destnation must be defined", MFILE, __LINE__); }
  
  if (!sv_source) { return env->die(env, "Source must be defined", MFILE, __LINE__); }
  
  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be more than or equals to 0", MFILE, __LINE__);
  }
  
  int32_t* dest = env->get_elems_int(env, sv_dest);
  int32_t dest_len = env->length(env, sv_dest);
  
  int32_t* source = env->get_elems_int(env, sv_source);
  int32_t source_len = env->length(env, sv_source);
  
  if (dest_offset + length > dest_len) {
    return env->die(env, "Destnation offset + length must be within the range of the destnation array", MFILE, __LINE__);
  }
  
  if (source_offset + length > source_len) {
    return env->die(env, "Source offset + length must be within the range of the source array", MFILE, __LINE__);
  }
  
  memcpy((char*)(dest + dest_offset), (char*)(source + source_offset), length * sizeof(int32_t));
  
  return 0;
}

int32_t SPVM__Fn__memmove_int(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* sv_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* sv_source = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;

  if (!sv_dest) { return env->die(env, "Destnation must be defined", MFILE, __LINE__); }
  
  if (!sv_source) { return env->die(env, "Source must be defined", MFILE, __LINE__); }
  
  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be more than or equals to 0", MFILE, __LINE__);
  }
  
  int32_t* dest = env->get_elems_int(env, sv_dest);
  int32_t dest_len = env->length(env, sv_dest);
  
  int32_t* source = env->get_elems_int(env, sv_source);
  int32_t source_len = env->length(env, sv_source);
  
  if (dest_offset + length > dest_len) {
    return env->die(env, "Destnation offset + length must be within the range of the destnation array", MFILE, __LINE__);
  }

  if (source_offset + length > source_len) {
    return env->die(env, "Source offset + length must be within the range of the source array", MFILE, __LINE__);
  }
  
  memmove((char*)(dest + dest_offset), (char*)(source + source_offset), length * sizeof(int32_t));
  
  return 0;
}

int32_t SPVM__Fn__memcpy_long(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* sv_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* sv_source = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;

  if (!sv_dest) { return env->die(env, "Destnation must be defined", MFILE, __LINE__); }
  
  if (!sv_source) { return env->die(env, "Source must be defined", MFILE, __LINE__); }
  
  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be more than or equals to 0", MFILE, __LINE__);
  }
  
  int64_t* dest = env->get_elems_long(env, sv_dest);
  int32_t dest_len = env->length(env, sv_dest);
  
  int64_t* source = env->get_elems_long(env, sv_source);
  int32_t source_len = env->length(env, sv_source);
  
  if (dest_offset + length > dest_len) {
    return env->die(env, "Destnation offset + length must be within the range of the destnation array", MFILE, __LINE__);
  }
  
  if (source_offset + length > source_len) {
    return env->die(env, "Source offset + length must be within the range of the source array", MFILE, __LINE__);
  }
  
  memcpy((char*)(dest + dest_offset), (char*)(source + source_offset), length * sizeof(int64_t));
  
  return 0;
}

int32_t SPVM__Fn__memmove_long(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* sv_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* sv_source = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;

  if (!sv_dest) { return env->die(env, "Destnation must be defined", MFILE, __LINE__); }
  
  if (!sv_source) { return env->die(env, "Source must be defined", MFILE, __LINE__); }
  
  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be more than or equals to 0", MFILE, __LINE__);
  }
  
  int64_t* dest = env->get_elems_long(env, sv_dest);
  int32_t dest_len = env->length(env, sv_dest);
  
  int64_t* source = env->get_elems_long(env, sv_source);
  int32_t source_len = env->length(env, sv_source);
  
  if (dest_offset + length > dest_len) {
    return env->die(env, "Destnation offset + length must be within the range of the destnation array", MFILE, __LINE__);
  }

  if (source_offset + length > source_len) {
    return env->die(env, "Source offset + length must be within the range of the source array", MFILE, __LINE__);
  }
  
  memmove((char*)(dest + dest_offset), (char*)(source + source_offset), length * sizeof(int64_t));
  
  return 0;
}

int32_t SPVM__Fn__memcpy_float(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* sv_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* sv_source = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;

  if (!sv_dest) { return env->die(env, "Destnation must be defined", MFILE, __LINE__); }
  
  if (!sv_source) { return env->die(env, "Source must be defined", MFILE, __LINE__); }
  
  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be more than or equals to 0", MFILE, __LINE__);
  }
  
  float* dest = env->get_elems_float(env, sv_dest);
  int32_t dest_len = env->length(env, sv_dest);
  
  float* source = env->get_elems_float(env, sv_source);
  int32_t source_len = env->length(env, sv_source);
  
  if (dest_offset + length > dest_len) {
    return env->die(env, "Destnation offset + length must be within the range of the destnation array", MFILE, __LINE__);
  }
  
  if (source_offset + length > source_len) {
    return env->die(env, "Source offset + length must be within the range of the source array", MFILE, __LINE__);
  }
  
  memcpy((char*)(dest + dest_offset), (char*)(source + source_offset), length * sizeof(float));
  
  return 0;
}

int32_t SPVM__Fn__memmove_float(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* sv_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* sv_source = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;

  if (!sv_dest) { return env->die(env, "Destnation must be defined", MFILE, __LINE__); }
  
  if (!sv_source) { return env->die(env, "Source must be defined", MFILE, __LINE__); }
  

  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be more than or equals to 0", MFILE, __LINE__);
  }
  
  float* dest = env->get_elems_float(env, sv_dest);
  int32_t dest_len = env->length(env, sv_dest);
  
  float* source = env->get_elems_float(env, sv_source);
  int32_t source_len = env->length(env, sv_source);
  
  if (dest_offset + length > dest_len) {
    return env->die(env, "Destnation offset + length must be within the range of the destnation array", MFILE, __LINE__);
  }

  if (source_offset + length > source_len) {
    return env->die(env, "Source offset + length must be within the range of the source array", MFILE, __LINE__);
  }
  
  memmove((char*)(dest + dest_offset), (char*)(source + source_offset), length * sizeof(float));
  
  return 0;
}

int32_t SPVM__Fn__memcpy_double(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* sv_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* sv_source = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;

  if (!sv_dest) { return env->die(env, "Destnation must be defined", MFILE, __LINE__); }
  
  if (!sv_source) { return env->die(env, "Source must be defined", MFILE, __LINE__); }
  

  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be more than or equals to 0", MFILE, __LINE__);
  }
  
  double* dest = env->get_elems_double(env, sv_dest);
  int32_t dest_len = env->length(env, sv_dest);
  
  double* source = env->get_elems_double(env, sv_source);
  int32_t source_len = env->length(env, sv_source);
  
  if (dest_offset + length > dest_len) {
    return env->die(env, "Destnation offset + length must be within the range of the destnation array", MFILE, __LINE__);
  }
  
  if (source_offset + length > source_len) {
    return env->die(env, "Source offset + length must be within the range of the source array", MFILE, __LINE__);
  }
  
  memcpy((char*)(dest + dest_offset), (char*)(source + source_offset), length * sizeof(double));
  
  return 0;
}

int32_t SPVM__Fn__memmove_double(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* sv_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* sv_source = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;

  if (!sv_dest) { return env->die(env, "Destnation must be defined", MFILE, __LINE__); }
  
  if (!sv_source) { return env->die(env, "Source must be defined", MFILE, __LINE__); }

  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be more than or equals to 0", MFILE, __LINE__);
  }
  
  double* dest = env->get_elems_double(env, sv_dest);
  int32_t dest_len = env->length(env, sv_dest);
  
  double* source = env->get_elems_double(env, sv_source);
  int32_t source_len = env->length(env, sv_source);
  
  if (dest_offset + length > dest_len) {
    return env->die(env, "Destnation offset + length must be within the range of the destnation array", MFILE, __LINE__);
  }

  if (source_offset + length > source_len) {
    return env->die(env, "Source offset + length must be within the range of the source array", MFILE, __LINE__);
  }
  
  memmove((char*)(dest + dest_offset), (char*)(source + source_offset), length * sizeof(double));
  
  return 0;
}

int32_t SPVM__Fn__new_array_proto(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* array = stack[0].oval;
  int32_t length = stack[1].ival;
  
  if (array == NULL) {
    return env->die(env, "Prototype array must be defined", MFILE, __LINE__);
  }

  if (length < 0) {
    return env->die(env, "The length must be greater than or equals to 0", MFILE, __LINE__);
  }
  
  void* new_object_array = env->new_array_proto(env, array, length);
  
  stack[0].oval = new_object_array;
  
  return 0;
}

