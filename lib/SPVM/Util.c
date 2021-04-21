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

static const char* MFILE = "SPVM/Util.c";

#define SPRINTF_MAX_RESULT_LEN 256
#define UINT64_MAX_LEN 20

int32_t SPNATIVE__SPVM__Util___snsprintf_double(SPVM_ENV* env, SPVM_VALUE* stack) {
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

int32_t SPNATIVE__SPVM__Util___long_to_unsigned_digits(SPVM_ENV* env, SPVM_VALUE* stack) {
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

int32_t SPNATIVE__SPVM__Util__strtoi(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPNATIVE__SPVM__Util__strtol(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPNATIVE__SPVM__Util__strtof(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPNATIVE__SPVM__Util__strtod(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPNATIVE__SPVM__Util__isdigit(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t ch = stack[0].ival;
  
  int32_t is_valid = isdigit(ch);
  
  stack[0].ival = is_valid;

  return 0;
}

int32_t SPNATIVE__SPVM__Util__memcpy_byte(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest_data = stack[0].oval;
  if (!obj_dest_data) {
    return env->die(env, "Dist string must be defined", MFILE, __LINE__);
  }
  
  int32_t dest_offset = stack[1].ival;
  
  void* obj_src_data = stack[2].oval;
  if (!obj_src_data) {
    return env->die(env, "Source string must be defined", MFILE, __LINE__);
  }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be zero or positive value", MFILE, __LINE__);
  }
  
  int8_t* dest_data = env->get_elems_byte(env, obj_dest_data);
  int32_t dest_data_len = env->length(env, obj_dest_data);
  
  int8_t* src_data = env->get_elems_byte(env, obj_src_data);
  int32_t src_data_len = env->length(env, obj_src_data);
  
  if (dest_offset + length > dest_data_len) {
    return env->die(env, "Copy is over destination data", MFILE, __LINE__);
  }

  if (src_offset + length > src_data_len) {
    return env->die(env, "Copy is over source data", MFILE, __LINE__);
  }
  
  memcpy((char*)(dest_data + dest_offset), (char*)(src_data + src_offset), length);
  
  return 0;
}

int32_t SPNATIVE__SPVM__Util__memmove_byte(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest_data = stack[0].oval;
  if (!obj_dest_data) { return env->die(env, "Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dest_offset = stack[1].ival;
  
  void* obj_src_data = stack[2].oval;
  if (!obj_src_data) { return env->die(env, "Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be zero or positive value", MFILE, __LINE__);
  }
  
  int8_t* dest_data = env->get_elems_byte(env, obj_dest_data);
  int32_t dest_data_len = env->length(env, obj_dest_data);
  
  int8_t* src_data = env->get_elems_byte(env, obj_src_data);
  int32_t src_data_len = env->length(env, obj_src_data);
  
  if (dest_offset + length > dest_data_len) {
    return env->die(env, "Copy is over destination data", MFILE, __LINE__);
  }

  if (src_offset + length > src_data_len) {
    return env->die(env, "Copy is over source data", MFILE, __LINE__);
  }
  
  memmove((char*)(dest_data + dest_offset), (char*)(src_data + src_offset), length);
  
  return 0;
}

int32_t SPNATIVE__SPVM__Util__memcpy_short(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest_data = stack[0].oval;
  if (!obj_dest_data) { return env->die(env, "Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dest_offset = stack[1].ival;
  
  void* obj_src_data = stack[2].oval;
  if (!obj_src_data) { return env->die(env, "Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be zero or positive value", MFILE, __LINE__);
  }
  
  int16_t* dest_data = env->get_elems_short(env, obj_dest_data);
  int32_t dest_data_len = env->length(env, obj_dest_data);
  
  int16_t* src_data = env->get_elems_short(env, obj_src_data);
  int32_t src_data_len = env->length(env, obj_src_data);
  
  if (dest_offset + length > dest_data_len) {
    return env->die(env, "Copy is over destination data", MFILE, __LINE__);
  }
  
  if (src_offset + length > src_data_len) {
    return env->die(env, "Copy is over source data", MFILE, __LINE__);
  }
  
  memcpy((char*)(dest_data + dest_offset), (char*)(src_data + src_offset), length * sizeof(int16_t));
  
  return 0;
}

int32_t SPNATIVE__SPVM__Util__memmove_short(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest_data = stack[0].oval;
  if (!obj_dest_data) { return env->die(env, "Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dest_offset = stack[1].ival;
  
  void* obj_src_data = stack[2].oval;
  if (!obj_src_data) { return env->die(env, "Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be zero or positive value", MFILE, __LINE__);
  }
  
  int16_t* dest_data = env->get_elems_short(env, obj_dest_data);
  int32_t dest_data_len = env->length(env, obj_dest_data);
  
  int16_t* src_data = env->get_elems_short(env, obj_src_data);
  int32_t src_data_len = env->length(env, obj_src_data);
  
  if (dest_offset + length > dest_data_len) {
    return env->die(env, "Copy is over destination data", MFILE, __LINE__);
  }

  if (src_offset + length > src_data_len) {
    return env->die(env, "Copy is over source data", MFILE, __LINE__);
  }
  
  memmove((char*)(dest_data + dest_offset), (char*)(src_data + src_offset), length * sizeof(int16_t));
  
  return 0;
}

int32_t SPNATIVE__SPVM__Util__memcpy_int(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest_data = stack[0].oval;
  if (!obj_dest_data) { return env->die(env, "Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dest_offset = stack[1].ival;
  
  void* obj_src_data = stack[2].oval;
  if (!obj_src_data) { return env->die(env, "Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be zero or positive value", MFILE, __LINE__);
  }
  
  int32_t* dest_data = env->get_elems_int(env, obj_dest_data);
  int32_t dest_data_len = env->length(env, obj_dest_data);
  
  int32_t* src_data = env->get_elems_int(env, obj_src_data);
  int32_t src_data_len = env->length(env, obj_src_data);
  
  if (dest_offset + length > dest_data_len) {
    return env->die(env, "Copy is over destination data", MFILE, __LINE__);
  }
  
  if (src_offset + length > src_data_len) {
    return env->die(env, "Copy is over source data", MFILE, __LINE__);
  }
  
  memcpy((char*)(dest_data + dest_offset), (char*)(src_data + src_offset), length * sizeof(int32_t));
  
  return 0;
}

int32_t SPNATIVE__SPVM__Util__memmove_int(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest_data = stack[0].oval;
  if (!obj_dest_data) { return env->die(env, "Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dest_offset = stack[1].ival;
  
  void* obj_src_data = stack[2].oval;
  if (!obj_src_data) { return env->die(env, "Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be zero or positive value", MFILE, __LINE__);
  }
  
  int32_t* dest_data = env->get_elems_int(env, obj_dest_data);
  int32_t dest_data_len = env->length(env, obj_dest_data);
  
  int32_t* src_data = env->get_elems_int(env, obj_src_data);
  int32_t src_data_len = env->length(env, obj_src_data);
  
  if (dest_offset + length > dest_data_len) {
    return env->die(env, "Copy is over destination data", MFILE, __LINE__);
  }

  if (src_offset + length > src_data_len) {
    return env->die(env, "Copy is over source data", MFILE, __LINE__);
  }
  
  memmove((char*)(dest_data + dest_offset), (char*)(src_data + src_offset), length * sizeof(int32_t));
  
  return 0;
}

int32_t SPNATIVE__SPVM__Util__memcpy_long(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest_data = stack[0].oval;
  if (!obj_dest_data) { return env->die(env, "Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dest_offset = stack[1].ival;
  
  void* obj_src_data = stack[2].oval;
  if (!obj_src_data) { return env->die(env, "Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be zero or positive value", MFILE, __LINE__);
  }
  
  int64_t* dest_data = env->get_elems_long(env, obj_dest_data);
  int32_t dest_data_len = env->length(env, obj_dest_data);
  
  int64_t* src_data = env->get_elems_long(env, obj_src_data);
  int32_t src_data_len = env->length(env, obj_src_data);
  
  if (dest_offset + length > dest_data_len) {
    return env->die(env, "Copy is over destination data", MFILE, __LINE__);
  }
  
  if (src_offset + length > src_data_len) {
    return env->die(env, "Copy is over source data", MFILE, __LINE__);
  }
  
  memcpy((char*)(dest_data + dest_offset), (char*)(src_data + src_offset), length * sizeof(int64_t));
  
  return 0;
}

int32_t SPNATIVE__SPVM__Util__memmove_long(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest_data = stack[0].oval;
  if (!obj_dest_data) { return env->die(env, "Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dest_offset = stack[1].ival;
  
  void* obj_src_data = stack[2].oval;
  if (!obj_src_data) { return env->die(env, "Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be zero or positive value", MFILE, __LINE__);
  }
  
  int64_t* dest_data = env->get_elems_long(env, obj_dest_data);
  int32_t dest_data_len = env->length(env, obj_dest_data);
  
  int64_t* src_data = env->get_elems_long(env, obj_src_data);
  int32_t src_data_len = env->length(env, obj_src_data);
  
  if (dest_offset + length > dest_data_len) {
    return env->die(env, "Copy is over destination data", MFILE, __LINE__);
  }

  if (src_offset + length > src_data_len) {
    return env->die(env, "Copy is over source data", MFILE, __LINE__);
  }
  
  memmove((char*)(dest_data + dest_offset), (char*)(src_data + src_offset), length * sizeof(int64_t));
  
  return 0;
}

int32_t SPNATIVE__SPVM__Util__memcpy_float(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest_data = stack[0].oval;
  if (!obj_dest_data) { return env->die(env, "Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dest_offset = stack[1].ival;
  
  void* obj_src_data = stack[2].oval;
  if (!obj_src_data) { return env->die(env, "Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be zero or positive value", MFILE, __LINE__);
  }
  
  float* dest_data = env->get_elems_float(env, obj_dest_data);
  int32_t dest_data_len = env->length(env, obj_dest_data);
  
  float* src_data = env->get_elems_float(env, obj_src_data);
  int32_t src_data_len = env->length(env, obj_src_data);
  
  if (dest_offset + length > dest_data_len) {
    return env->die(env, "Copy is over destination data", MFILE, __LINE__);
  }
  
  if (src_offset + length > src_data_len) {
    return env->die(env, "Copy is over source data", MFILE, __LINE__);
  }
  
  memcpy((char*)(dest_data + dest_offset), (char*)(src_data + src_offset), length * sizeof(float));
  
  return 0;
}

int32_t SPNATIVE__SPVM__Util__memmove_float(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest_data = stack[0].oval;
  if (!obj_dest_data) { return env->die(env, "Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dest_offset = stack[1].ival;
  
  void* obj_src_data = stack[2].oval;
  if (!obj_src_data) { return env->die(env, "Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be zero or positive value", MFILE, __LINE__);
  }
  
  float* dest_data = env->get_elems_float(env, obj_dest_data);
  int32_t dest_data_len = env->length(env, obj_dest_data);
  
  float* src_data = env->get_elems_float(env, obj_src_data);
  int32_t src_data_len = env->length(env, obj_src_data);
  
  if (dest_offset + length > dest_data_len) {
    return env->die(env, "Copy is over destination data", MFILE, __LINE__);
  }

  if (src_offset + length > src_data_len) {
    return env->die(env, "Copy is over source data", MFILE, __LINE__);
  }
  
  memmove((char*)(dest_data + dest_offset), (char*)(src_data + src_offset), length * sizeof(float));
  
  return 0;
}

int32_t SPNATIVE__SPVM__Util__memcpy_double(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest_data = stack[0].oval;
  if (!obj_dest_data) { return env->die(env, "Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dest_offset = stack[1].ival;
  
  void* obj_src_data = stack[2].oval;
  if (!obj_src_data) { return env->die(env, "Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be zero or positive value", MFILE, __LINE__);
  }
  
  double* dest_data = env->get_elems_double(env, obj_dest_data);
  int32_t dest_data_len = env->length(env, obj_dest_data);
  
  double* src_data = env->get_elems_double(env, obj_src_data);
  int32_t src_data_len = env->length(env, obj_src_data);
  
  if (dest_offset + length > dest_data_len) {
    return env->die(env, "Copy is over destination data", MFILE, __LINE__);
  }
  
  if (src_offset + length > src_data_len) {
    return env->die(env, "Copy is over source data", MFILE, __LINE__);
  }
  
  memcpy((char*)(dest_data + dest_offset), (char*)(src_data + src_offset), length * sizeof(double));
  
  return 0;
}

int32_t SPNATIVE__SPVM__Util__memmove_double(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest_data = stack[0].oval;
  if (!obj_dest_data) { return env->die(env, "Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dest_offset = stack[1].ival;
  
  void* obj_src_data = stack[2].oval;
  if (!obj_src_data) { return env->die(env, "Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, "Length must be zero or positive value", MFILE, __LINE__);
  }
  
  double* dest_data = env->get_elems_double(env, obj_dest_data);
  int32_t dest_data_len = env->length(env, obj_dest_data);
  
  double* src_data = env->get_elems_double(env, obj_src_data);
  int32_t src_data_len = env->length(env, obj_src_data);
  
  if (dest_offset + length > dest_data_len) {
    return env->die(env, "Copy is over destination data", MFILE, __LINE__);
  }

  if (src_offset + length > src_data_len) {
    return env->die(env, "Copy is over source data", MFILE, __LINE__);
  }
  
  memmove((char*)(dest_data + dest_offset), (char*)(src_data + src_offset), length * sizeof(double));
  
  return 0;
}

int32_t SPNATIVE__SPVM__Util__getenv(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  void* obj_name = stack[0].oval;
  if (obj_name == NULL) {
    return env->die(env, "Name must be defined", MFILE, __LINE__);
  }
  const char* name = env->get_chars(env, obj_name);
  
  const char* value = getenv(name);
  
  void* obj_value;
  if (value == NULL) {
    obj_value = NULL;
  }
  else {
    int32_t length = (int32_t)strlen(value);
    obj_value = env->new_string(env, value, length);
  }
  
  stack[0].oval = obj_value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Util__abs(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  int32_t value = (int32_t)labs(stack[0].ival);
  
  stack[0].ival = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Util__labs(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  int64_t value = (int64_t)labs(stack[0].lval);
  
  stack[0].lval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Util__new_object_array_proto(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPNATIVE__SPVM__Util__FLT_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].fval = FLT_MAX;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Util__FLT_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].fval = FLT_MIN;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Util__DBL_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = DBL_MAX;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Util__DBL_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = DBL_MIN;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Util__srand(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int64_t seed = stack[0].lval;
  
  srand((unsigned)seed);

  return 0;
}

int32_t SPNATIVE__SPVM__Util__crand(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  stack[0].ival = rand();

  return 0;
}

int32_t SPNATIVE__SPVM__Util__RAND_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  stack[0].ival = RAND_MAX;

  return 0;
}
