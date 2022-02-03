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

static const char* MFILE = "Native/Fn.c";

int32_t SPVM__Native__Fn__FLT_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].fval = FLT_MAX;
  
  return 0;
}

int32_t SPVM__Native__Fn__FLT_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].fval = FLT_MIN;
  
  return 0;
}

int32_t SPVM__Native__Fn__DBL_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = DBL_MAX;
  
  return 0;
}

int32_t SPVM__Native__Fn__DBL_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = DBL_MIN;
  
  return 0;
}

int32_t SPVM__Native__Fn__srand(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int64_t seed = stack[0].lval;
  
  srand((unsigned)seed);

  return 0;
}

int32_t SPVM__Native__Fn__crand(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  stack[0].ival = rand();

  return 0;
}

int32_t SPVM__Native__Fn__RAND_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  stack[0].ival = RAND_MAX;

  return 0;
}


#define SPRINTF_MAX_RESULT_LEN 256
#define UINT64_MAX_LEN 20

int32_t SPVM__Native__Fn___snsprintf_double(SPVM_ENV* env, SPVM_VALUE* stack) {
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

int32_t SPVM__Native__Fn___long_to_unsigned_digits(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  unsigned long long value = stack[0].lval;
  void* onums = stack[1].oval;
  int8_t* nums = env->get_elems_byte(env, onums);
  int32_t* digit_count = stack[2].iref;

  for(*digit_count = 0; value > 0 && *digit_count < UINT64_MAX_LEN; ++*digit_count){
    nums[*digit_count] = (char)('0' + value % 10);
    value /= 10;
  }

  return 0;
}

int32_t SPVM__Native__Fn__to_int_with_base(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPVM__Native__Fn__to_long_with_base(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPVM__Native__Fn__to_float(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPVM__Native__Fn__to_double(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPVM__Native__Fn__memcpy_byte(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* sv_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* sv_source_data = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;

  if (!sv_dest) {
    return env->die(env, "Destnation must be defined", MFILE, __LINE__);
  }
  
  if (!sv_source_data) {
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
  
  int8_t* source = env->get_elems_byte(env, sv_source_data);
  int32_t source_len = env->length(env, sv_source_data);
  
  if (dest_offset + length > dest_len) {
    return env->die(env, "Destnation offset + length must be within the range of the destnation array", MFILE, __LINE__);
  }

  if (source_offset + length > source_len) {
    return env->die(env, "Source offset + length must be within the range of the source array", MFILE, __LINE__);
  }
  
  memcpy((char*)(dest + dest_offset), (char*)(source + source_offset), length);
  
  return 0;
}

int32_t SPVM__Native__Fn__memmove_byte(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* sv_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* sv_source_data = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;

  if (!sv_dest) { return env->die(env, "Destnation must be defined", MFILE, __LINE__); }
  
  if (!sv_source_data) { return env->die(env, "Source must be defined", MFILE, __LINE__); }
  
  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be more than or equals to 0", MFILE, __LINE__);
  }
  
  int8_t* dest = env->get_elems_byte(env, sv_dest);
  int32_t dest_len = env->length(env, sv_dest);
  
  int8_t* source = env->get_elems_byte(env, sv_source_data);
  int32_t source_len = env->length(env, sv_source_data);
  
  if (dest_offset + length > dest_len) {
    return env->die(env, "Destnation offset + length must be within the range of the destnation array", MFILE, __LINE__);
  }

  if (source_offset + length > source_len) {
    return env->die(env, "Source offset + length must be within the range of the source array", MFILE, __LINE__);
  }
  
  memmove((char*)(dest + dest_offset), (char*)(source + source_offset), length);
  
  return 0;
}

int32_t SPVM__Native__Fn__memcpy_short(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* sv_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* sv_source_data = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;

  if (!sv_dest) { return env->die(env, "Destnation must be defined", MFILE, __LINE__); }

  if (!sv_source_data) { return env->die(env, "Source must be defined", MFILE, __LINE__); }
  
  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be more than or equals to 0", MFILE, __LINE__);
  }
  
  int16_t* dest = env->get_elems_short(env, sv_dest);
  int32_t dest_len = env->length(env, sv_dest);
  
  int16_t* source = env->get_elems_short(env, sv_source_data);
  int32_t source_len = env->length(env, sv_source_data);
  
  if (dest_offset + length > dest_len) {
    return env->die(env, "Destnation offset + length must be within the range of the destnation array", MFILE, __LINE__);
  }
  
  if (source_offset + length > source_len) {
    return env->die(env, "Source offset + length must be within the range of the source array", MFILE, __LINE__);
  }
  
  memcpy((char*)(dest + dest_offset), (char*)(source + source_offset), length * sizeof(int16_t));
  
  return 0;
}

int32_t SPVM__Native__Fn__memmove_short(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* sv_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* sv_source_data = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;

  if (!sv_dest) { return env->die(env, "Destnation must be defined", MFILE, __LINE__); }
  
  if (!sv_source_data) { return env->die(env, "Source must be defined", MFILE, __LINE__); }
  
  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be more than or equals to 0", MFILE, __LINE__);
  }
  
  int16_t* dest = env->get_elems_short(env, sv_dest);
  int32_t dest_len = env->length(env, sv_dest);
  
  int16_t* source = env->get_elems_short(env, sv_source_data);
  int32_t source_len = env->length(env, sv_source_data);
  
  if (dest_offset + length > dest_len) {
    return env->die(env, "Destnation offset + length must be within the range of the destnation array", MFILE, __LINE__);
  }

  if (source_offset + length > source_len) {
    return env->die(env, "Source offset + length must be within the range of the source array", MFILE, __LINE__);
  }
  
  memmove((char*)(dest + dest_offset), (char*)(source + source_offset), length * sizeof(int16_t));
  
  return 0;
}

int32_t SPVM__Native__Fn__memcpy_int(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* sv_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* sv_source_data = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;

  if (!sv_dest) { return env->die(env, "Destnation must be defined", MFILE, __LINE__); }
  
  if (!sv_source_data) { return env->die(env, "Source must be defined", MFILE, __LINE__); }
  
  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be more than or equals to 0", MFILE, __LINE__);
  }
  
  int32_t* dest = env->get_elems_int(env, sv_dest);
  int32_t dest_len = env->length(env, sv_dest);
  
  int32_t* source = env->get_elems_int(env, sv_source_data);
  int32_t source_len = env->length(env, sv_source_data);
  
  if (dest_offset + length > dest_len) {
    return env->die(env, "Destnation offset + length must be within the range of the destnation array", MFILE, __LINE__);
  }
  
  if (source_offset + length > source_len) {
    return env->die(env, "Source offset + length must be within the range of the source array", MFILE, __LINE__);
  }
  
  memcpy((char*)(dest + dest_offset), (char*)(source + source_offset), length * sizeof(int32_t));
  
  return 0;
}

int32_t SPVM__Native__Fn__memmove_int(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* sv_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* sv_source_data = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;

  if (!sv_dest) { return env->die(env, "Destnation must be defined", MFILE, __LINE__); }
  
  if (!sv_source_data) { return env->die(env, "Source must be defined", MFILE, __LINE__); }
  
  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be more than or equals to 0", MFILE, __LINE__);
  }
  
  int32_t* dest = env->get_elems_int(env, sv_dest);
  int32_t dest_len = env->length(env, sv_dest);
  
  int32_t* source = env->get_elems_int(env, sv_source_data);
  int32_t source_len = env->length(env, sv_source_data);
  
  if (dest_offset + length > dest_len) {
    return env->die(env, "Destnation offset + length must be within the range of the destnation array", MFILE, __LINE__);
  }

  if (source_offset + length > source_len) {
    return env->die(env, "Source offset + length must be within the range of the source array", MFILE, __LINE__);
  }
  
  memmove((char*)(dest + dest_offset), (char*)(source + source_offset), length * sizeof(int32_t));
  
  return 0;
}

int32_t SPVM__Native__Fn__memcpy_long(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* sv_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* sv_source_data = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;

  if (!sv_dest) { return env->die(env, "Destnation must be defined", MFILE, __LINE__); }
  
  if (!sv_source_data) { return env->die(env, "Source must be defined", MFILE, __LINE__); }
  
  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be more than or equals to 0", MFILE, __LINE__);
  }
  
  int64_t* dest = env->get_elems_long(env, sv_dest);
  int32_t dest_len = env->length(env, sv_dest);
  
  int64_t* source = env->get_elems_long(env, sv_source_data);
  int32_t source_len = env->length(env, sv_source_data);
  
  if (dest_offset + length > dest_len) {
    return env->die(env, "Destnation offset + length must be within the range of the destnation array", MFILE, __LINE__);
  }
  
  if (source_offset + length > source_len) {
    return env->die(env, "Source offset + length must be within the range of the source array", MFILE, __LINE__);
  }
  
  memcpy((char*)(dest + dest_offset), (char*)(source + source_offset), length * sizeof(int64_t));
  
  return 0;
}

int32_t SPVM__Native__Fn__memmove_long(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* sv_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* sv_source_data = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;

  if (!sv_dest) { return env->die(env, "Destnation must be defined", MFILE, __LINE__); }
  
  if (!sv_source_data) { return env->die(env, "Source must be defined", MFILE, __LINE__); }
  
  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be more than or equals to 0", MFILE, __LINE__);
  }
  
  int64_t* dest = env->get_elems_long(env, sv_dest);
  int32_t dest_len = env->length(env, sv_dest);
  
  int64_t* source = env->get_elems_long(env, sv_source_data);
  int32_t source_len = env->length(env, sv_source_data);
  
  if (dest_offset + length > dest_len) {
    return env->die(env, "Destnation offset + length must be within the range of the destnation array", MFILE, __LINE__);
  }

  if (source_offset + length > source_len) {
    return env->die(env, "Source offset + length must be within the range of the source array", MFILE, __LINE__);
  }
  
  memmove((char*)(dest + dest_offset), (char*)(source + source_offset), length * sizeof(int64_t));
  
  return 0;
}

int32_t SPVM__Native__Fn__memcpy_float(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* sv_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* sv_source_data = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;

  if (!sv_dest) { return env->die(env, "Destnation must be defined", MFILE, __LINE__); }
  
  if (!sv_source_data) { return env->die(env, "Source must be defined", MFILE, __LINE__); }
  
  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be more than or equals to 0", MFILE, __LINE__);
  }
  
  float* dest = env->get_elems_float(env, sv_dest);
  int32_t dest_len = env->length(env, sv_dest);
  
  float* source = env->get_elems_float(env, sv_source_data);
  int32_t source_len = env->length(env, sv_source_data);
  
  if (dest_offset + length > dest_len) {
    return env->die(env, "Destnation offset + length must be within the range of the destnation array", MFILE, __LINE__);
  }
  
  if (source_offset + length > source_len) {
    return env->die(env, "Source offset + length must be within the range of the source array", MFILE, __LINE__);
  }
  
  memcpy((char*)(dest + dest_offset), (char*)(source + source_offset), length * sizeof(float));
  
  return 0;
}

int32_t SPVM__Native__Fn__memmove_float(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* sv_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* sv_source_data = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;

  if (!sv_dest) { return env->die(env, "Destnation must be defined", MFILE, __LINE__); }
  
  if (!sv_source_data) { return env->die(env, "Source must be defined", MFILE, __LINE__); }
  

  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be more than or equals to 0", MFILE, __LINE__);
  }
  
  float* dest = env->get_elems_float(env, sv_dest);
  int32_t dest_len = env->length(env, sv_dest);
  
  float* source = env->get_elems_float(env, sv_source_data);
  int32_t source_len = env->length(env, sv_source_data);
  
  if (dest_offset + length > dest_len) {
    return env->die(env, "Destnation offset + length must be within the range of the destnation array", MFILE, __LINE__);
  }

  if (source_offset + length > source_len) {
    return env->die(env, "Source offset + length must be within the range of the source array", MFILE, __LINE__);
  }
  
  memmove((char*)(dest + dest_offset), (char*)(source + source_offset), length * sizeof(float));
  
  return 0;
}

int32_t SPVM__Native__Fn__memcpy_double(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* sv_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* sv_source_data = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;

  if (!sv_dest) { return env->die(env, "Destnation must be defined", MFILE, __LINE__); }
  
  if (!sv_source_data) { return env->die(env, "Source must be defined", MFILE, __LINE__); }
  

  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be more than or equals to 0", MFILE, __LINE__);
  }
  
  double* dest = env->get_elems_double(env, sv_dest);
  int32_t dest_len = env->length(env, sv_dest);
  
  double* source = env->get_elems_double(env, sv_source_data);
  int32_t source_len = env->length(env, sv_source_data);
  
  if (dest_offset + length > dest_len) {
    return env->die(env, "Destnation offset + length must be within the range of the destnation array", MFILE, __LINE__);
  }
  
  if (source_offset + length > source_len) {
    return env->die(env, "Source offset + length must be within the range of the source array", MFILE, __LINE__);
  }
  
  memcpy((char*)(dest + dest_offset), (char*)(source + source_offset), length * sizeof(double));
  
  return 0;
}

int32_t SPVM__Native__Fn__memmove_double(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* sv_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* sv_source_data = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;

  if (!sv_dest) { return env->die(env, "Destnation must be defined", MFILE, __LINE__); }
  
  if (!sv_source_data) { return env->die(env, "Source must be defined", MFILE, __LINE__); }

  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be more than or equals to 0", MFILE, __LINE__);
  }
  
  double* dest = env->get_elems_double(env, sv_dest);
  int32_t dest_len = env->length(env, sv_dest);
  
  double* source = env->get_elems_double(env, sv_source_data);
  int32_t source_len = env->length(env, sv_source_data);
  
  if (dest_offset + length > dest_len) {
    return env->die(env, "Destnation offset + length must be within the range of the destnation array", MFILE, __LINE__);
  }

  if (source_offset + length > source_len) {
    return env->die(env, "Source offset + length must be within the range of the source array", MFILE, __LINE__);
  }
  
  memmove((char*)(dest + dest_offset), (char*)(source + source_offset), length * sizeof(double));
  
  return 0;
}

int32_t SPVM__Native__Fn__new_array_proto(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* oarray = stack[0].oval;
  int32_t length = stack[1].ival;
  
  if (oarray == NULL) {
    return env->die(env, "Prototype array must be defined", MFILE, __LINE__);
  }
  
  int32_t basic_type_id = env->get_object_basic_type_id(env, oarray);
  int32_t element_dimension = env->get_object_type_dimension(env, oarray) - 1;
  
  void* new_object_array = env->new_muldim_array(env, basic_type_id, element_dimension, length);
  
  stack[0].oval = new_object_array;
  
  return 0;
}

