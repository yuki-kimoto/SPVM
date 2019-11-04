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

static const char* MFILE = "SPVM/CORE.c";

int32_t SPNATIVE__SPVM__CORE__strtoi(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_string = stack[0].oval;
  if (!obj_string) {
    SPVM_DIE("String must be defined", MFILE, __LINE__);
  }
  const char* string = (const char*)env->belems(env, obj_string);
  
  int32_t digit = stack[1].ival;
  
  if (!(digit == 2 || digit == 8 || digit == 10 || digit == 16)) {
    SPVM_DIE("Digit must be 2, 8, 10, 16", MFILE, __LINE__);
  }
  
  char *end;
  errno = 0;
  long int num = strtol(string, &end, digit);
  if (*end != '\0') {
    SPVM_DIE("Invalid number format", MFILE, __LINE__);
  }
  else if (errno == ERANGE || num < INT32_MIN || num > INT32_MAX) {
    SPVM_DIE("Out of range", MFILE, __LINE__);
  }
  
  stack[0].ival = (int32_t)num;

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__strtol(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_string = stack[0].oval;
  if (!obj_string) {
    SPVM_DIE("String must be defined", MFILE, __LINE__);
  }
  const char* string = (const char*)env->belems(env, obj_string);
  
  int32_t digit = stack[1].ival;

  if (!(digit == 2 || digit == 8 || digit == 10 || digit == 16)) {
    SPVM_DIE("Digit must be 2, 8, 10, 16", MFILE, __LINE__);
  }
  
  char *end;
  errno = 0;
  long long int num = strtoll(string, &end, digit);
  if (*end != '\0') {
    SPVM_DIE("Invalid number format", MFILE, __LINE__);
  }
  else if (errno == ERANGE || num < INT64_MIN || num > INT64_MAX) {
    SPVM_DIE("Out of range", MFILE, __LINE__);
  }
  
  stack[0].lval = (int64_t)num;

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__strtof(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_string = stack[0].oval;
  if (!obj_string) {
    SPVM_DIE("String must be defined", MFILE, __LINE__);
  }
  const char* string = (const char*)env->belems(env, obj_string);
  
  char *end;
  errno = 0;
  float num = strtof(string, &end);
  if (*end != '\0') {
    SPVM_DIE("Invalid number format", MFILE, __LINE__);
  }
  else if (errno == ERANGE) {
    SPVM_DIE("[ERANGE]Out of range", MFILE, __LINE__);
  }
  
  stack[0].fval = num;

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__strtod(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_string = stack[0].oval;
  if (!obj_string) {
    SPVM_DIE("String must be defined", MFILE, __LINE__);
  }
  const char* string = (const char*)env->belems(env, obj_string);
  
  char *end;
  errno = 0;
  double num = strtod(string, &end);
  if (*end != '\0') {
    SPVM_DIE("Invalid number format", MFILE, __LINE__);
  }
  else if (errno == ERANGE) {
    SPVM_DIE("[ERANGE]Out of range", MFILE, __LINE__);
  }
  
  stack[0].dval = num;

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__isdigit(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t ch = stack[0].ival;
  
  int32_t is_valid = isdigit(ch);
  
  stack[0].ival = is_valid;

  return SPVM_SUCCESS;
}

// https://github.com/lattera/glibc/blob/master/stdlib/rand_r.c
static int
SPVM_rand_r (uint32_t *seed)
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

int32_t SPNATIVE__SPVM__CORE__memcpyb(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest_data = stack[0].oval;
  if (!obj_dest_data) {
    SPVM_DIE("Dist string must be defined", MFILE, __LINE__);
  }
  
  int32_t dest_offset = stack[1].ival;
  
  void* obj_src_data = stack[2].oval;
  if (!obj_src_data) {
    SPVM_DIE("Source string must be defined", MFILE, __LINE__);
  }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return SPVM_SUCCESS;
  }
  else if (length < 0) {
    SPVM_DIE("Length must be zero or positive value", MFILE, __LINE__);
  }
  
  char* dest_data = (char*)env->belems(env, obj_dest_data);
  int32_t dest_data_len = env->len(env, obj_dest_data);
  
  char* src_data = (char*)env->belems(env, obj_src_data);
  int32_t src_data_len = env->len(env, obj_src_data);
  
  if (dest_offset + length > dest_data_len) {
    SPVM_DIE("Copy is over destination data", MFILE, __LINE__);
  }

  if (src_offset + length > src_data_len) {
    SPVM_DIE("Copy is over source data", MFILE, __LINE__);
  }
  
  memcpy((char*)(dest_data + dest_offset), (char*)(src_data + src_offset), length);
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__memmoveb(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest_data = stack[0].oval;
  if (!obj_dest_data) { SPVM_DIE("Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dest_offset = stack[1].ival;
  
  void* obj_src_data = stack[2].oval;
  if (!obj_src_data) { SPVM_DIE("Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return SPVM_SUCCESS;
  }
  else if (length < 0) {
    SPVM_DIE("Length must be zero or positive value", MFILE, __LINE__);
  }
  
  char* dest_data = (char*)env->belems(env, obj_dest_data);
  int32_t dest_data_len = env->len(env, obj_dest_data);
  
  char* src_data = (char*)env->belems(env, obj_src_data);
  int32_t src_data_len = env->len(env, obj_src_data);
  
  if (dest_offset + length > dest_data_len) {
    SPVM_DIE("Copy is over destination data", MFILE, __LINE__);
  }

  if (src_offset + length > src_data_len) {
    SPVM_DIE("Copy is over source data", MFILE, __LINE__);
  }
  
  memmove((char*)(dest_data + dest_offset), (char*)(src_data + src_offset), length);
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__memcpys(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest_data = stack[0].oval;
  if (!obj_dest_data) { SPVM_DIE("Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dest_offset = stack[1].ival;
  
  void* obj_src_data = stack[2].oval;
  if (!obj_src_data) { SPVM_DIE("Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return SPVM_SUCCESS;
  }
  else if (length < 0) {
    SPVM_DIE("Length must be zero or positive value", MFILE, __LINE__);
  }
  
  char* dest_data = (char*)env->belems(env, obj_dest_data);
  int32_t dest_data_len = env->len(env, obj_dest_data);
  
  char* src_data = (char*)env->belems(env, obj_src_data);
  int32_t src_data_len = env->len(env, obj_src_data);
  
  if (dest_offset + length > dest_data_len) {
    SPVM_DIE("Copy is over destination data", MFILE, __LINE__);
  }
  
  if (src_offset + length > src_data_len) {
    SPVM_DIE("Copy is over source data", MFILE, __LINE__);
  }
  
  memcpy((char*)(dest_data + dest_offset * sizeof(int16_t)), (char*)(src_data + src_offset * sizeof(int16_t)), length * sizeof(int16_t));
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__memmoves(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest_data = stack[0].oval;
  if (!obj_dest_data) { SPVM_DIE("Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dest_offset = stack[1].ival;
  
  void* obj_src_data = stack[2].oval;
  if (!obj_src_data) { SPVM_DIE("Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return SPVM_SUCCESS;
  }
  else if (length < 0) {
    SPVM_DIE("Length must be zero or positive value", MFILE, __LINE__);
  }
  
  char* dest_data = (char*)env->belems(env, obj_dest_data);
  int32_t dest_data_len = env->len(env, obj_dest_data);
  
  char* src_data = (char*)env->belems(env, obj_src_data);
  int32_t src_data_len = env->len(env, obj_src_data);
  
  if (dest_offset + length > dest_data_len) {
    SPVM_DIE("Copy is over destination data", MFILE, __LINE__);
  }

  if (src_offset + length > src_data_len) {
    SPVM_DIE("Copy is over source data", MFILE, __LINE__);
  }
  
  memmove((char*)(dest_data + dest_offset * sizeof(int16_t)), (char*)(src_data + src_offset * sizeof(int16_t)), length * sizeof(int16_t));
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__memcpyi(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest_data = stack[0].oval;
  if (!obj_dest_data) { SPVM_DIE("Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dest_offset = stack[1].ival;
  
  void* obj_src_data = stack[2].oval;
  if (!obj_src_data) { SPVM_DIE("Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return SPVM_SUCCESS;
  }
  else if (length < 0) {
    SPVM_DIE("Length must be zero or positive value", MFILE, __LINE__);
  }
  
  char* dest_data = (char*)env->belems(env, obj_dest_data);
  int32_t dest_data_len = env->len(env, obj_dest_data);
  
  char* src_data = (char*)env->belems(env, obj_src_data);
  int32_t src_data_len = env->len(env, obj_src_data);
  
  if (dest_offset + length > dest_data_len) {
    SPVM_DIE("Copy is over destination data", MFILE, __LINE__);
  }
  
  if (src_offset + length > src_data_len) {
    SPVM_DIE("Copy is over source data", MFILE, __LINE__);
  }
  
  memcpy((char*)(dest_data + dest_offset * sizeof(int32_t)), (char*)(src_data + src_offset * sizeof(int32_t)), length * sizeof(int32_t));
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__memmovei(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest_data = stack[0].oval;
  if (!obj_dest_data) { SPVM_DIE("Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dest_offset = stack[1].ival;
  
  void* obj_src_data = stack[2].oval;
  if (!obj_src_data) { SPVM_DIE("Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return SPVM_SUCCESS;
  }
  else if (length < 0) {
    SPVM_DIE("Length must be zero or positive value", MFILE, __LINE__);
  }
  
  char* dest_data = (char*)env->belems(env, obj_dest_data);
  int32_t dest_data_len = env->len(env, obj_dest_data);
  
  char* src_data = (char*)env->belems(env, obj_src_data);
  int32_t src_data_len = env->len(env, obj_src_data);
  
  if (dest_offset + length > dest_data_len) {
    SPVM_DIE("Copy is over destination data", MFILE, __LINE__);
  }

  if (src_offset + length > src_data_len) {
    SPVM_DIE("Copy is over source data", MFILE, __LINE__);
  }
  
  memmove((char*)(dest_data + dest_offset * sizeof(int32_t)), (char*)(src_data + src_offset * sizeof(int32_t)), length * sizeof(int32_t));
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__memcpyl(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest_data = stack[0].oval;
  if (!obj_dest_data) { SPVM_DIE("Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dest_offset = stack[1].ival;
  
  void* obj_src_data = stack[2].oval;
  if (!obj_src_data) { SPVM_DIE("Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return SPVM_SUCCESS;
  }
  else if (length < 0) {
    SPVM_DIE("Length must be zero or positive value", MFILE, __LINE__);
  }
  
  char* dest_data = (char*)env->belems(env, obj_dest_data);
  int32_t dest_data_len = env->len(env, obj_dest_data);
  
  char* src_data = (char*)env->belems(env, obj_src_data);
  int32_t src_data_len = env->len(env, obj_src_data);
  
  if (dest_offset + length > dest_data_len) {
    SPVM_DIE("Copy is over destination data", MFILE, __LINE__);
  }
  
  if (src_offset + length > src_data_len) {
    SPVM_DIE("Copy is over source data", MFILE, __LINE__);
  }
  
  memcpy((char*)(dest_data + dest_offset * sizeof(int64_t)), (char*)(src_data + src_offset * sizeof(int64_t)), length * sizeof(int64_t));
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__memmovel(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest_data = stack[0].oval;
  if (!obj_dest_data) { SPVM_DIE("Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dest_offset = stack[1].ival;
  
  void* obj_src_data = stack[2].oval;
  if (!obj_src_data) { SPVM_DIE("Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return SPVM_SUCCESS;
  }
  else if (length < 0) {
    SPVM_DIE("Length must be zero or positive value", MFILE, __LINE__);
  }
  
  char* dest_data = (char*)env->belems(env, obj_dest_data);
  int32_t dest_data_len = env->len(env, obj_dest_data);
  
  char* src_data = (char*)env->belems(env, obj_src_data);
  int32_t src_data_len = env->len(env, obj_src_data);
  
  if (dest_offset + length > dest_data_len) {
    SPVM_DIE("Copy is over destination data", MFILE, __LINE__);
  }

  if (src_offset + length > src_data_len) {
    SPVM_DIE("Copy is over source data", MFILE, __LINE__);
  }
  
  memmove((char*)(dest_data + dest_offset * sizeof(int64_t)), (char*)(src_data + src_offset * sizeof(int64_t)), length * sizeof(int64_t));
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__memcpyf(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest_data = stack[0].oval;
  if (!obj_dest_data) { SPVM_DIE("Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dest_offset = stack[1].ival;
  
  void* obj_src_data = stack[2].oval;
  if (!obj_src_data) { SPVM_DIE("Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return SPVM_SUCCESS;
  }
  else if (length < 0) {
    SPVM_DIE("Length must be zero or positive value", MFILE, __LINE__);
  }
  
  char* dest_data = (char*)env->belems(env, obj_dest_data);
  int32_t dest_data_len = env->len(env, obj_dest_data);
  
  char* src_data = (char*)env->belems(env, obj_src_data);
  int32_t src_data_len = env->len(env, obj_src_data);
  
  if (dest_offset + length > dest_data_len) {
    SPVM_DIE("Copy is over destination data", MFILE, __LINE__);
  }
  
  if (src_offset + length > src_data_len) {
    SPVM_DIE("Copy is over source data", MFILE, __LINE__);
  }
  
  memcpy((char*)(dest_data + dest_offset * sizeof(float)), (char*)(src_data + src_offset * sizeof(float)), length * sizeof(float));
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__memmovef(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest_data = stack[0].oval;
  if (!obj_dest_data) { SPVM_DIE("Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dest_offset = stack[1].ival;
  
  void* obj_src_data = stack[2].oval;
  if (!obj_src_data) { SPVM_DIE("Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return SPVM_SUCCESS;
  }
  else if (length < 0) {
    SPVM_DIE("Length must be zero or positive value", MFILE, __LINE__);
  }
  
  char* dest_data = (char*)env->belems(env, obj_dest_data);
  int32_t dest_data_len = env->len(env, obj_dest_data);
  
  char* src_data = (char*)env->belems(env, obj_src_data);
  int32_t src_data_len = env->len(env, obj_src_data);
  
  if (dest_offset + length > dest_data_len) {
    SPVM_DIE("Copy is over destination data", MFILE, __LINE__);
  }

  if (src_offset + length > src_data_len) {
    SPVM_DIE("Copy is over source data", MFILE, __LINE__);
  }
  
  memmove((char*)(dest_data + dest_offset * sizeof(float)), (char*)(src_data + src_offset * sizeof(float)), length * sizeof(float));
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__memcpyd(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest_data = stack[0].oval;
  if (!obj_dest_data) { SPVM_DIE("Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dest_offset = stack[1].ival;
  
  void* obj_src_data = stack[2].oval;
  if (!obj_src_data) { SPVM_DIE("Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return SPVM_SUCCESS;
  }
  else if (length < 0) {
    SPVM_DIE("Length must be zero or positive value", MFILE, __LINE__);
  }
  
  char* dest_data = (char*)env->belems(env, obj_dest_data);
  int32_t dest_data_len = env->len(env, obj_dest_data);
  
  char* src_data = (char*)env->belems(env, obj_src_data);
  int32_t src_data_len = env->len(env, obj_src_data);
  
  if (dest_offset + length > dest_data_len) {
    SPVM_DIE("Copy is over destination data", MFILE, __LINE__);
  }
  
  if (src_offset + length > src_data_len) {
    SPVM_DIE("Copy is over source data", MFILE, __LINE__);
  }
  
  memcpy((char*)(dest_data + dest_offset * sizeof(double)), (char*)(src_data + src_offset * sizeof(double)), length * sizeof(double));
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__memmoved(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest_data = stack[0].oval;
  if (!obj_dest_data) { SPVM_DIE("Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dest_offset = stack[1].ival;
  
  void* obj_src_data = stack[2].oval;
  if (!obj_src_data) { SPVM_DIE("Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return SPVM_SUCCESS;
  }
  else if (length < 0) {
    SPVM_DIE("Length must be zero or positive value", MFILE, __LINE__);
  }
  
  char* dest_data = (char*)env->belems(env, obj_dest_data);
  int32_t dest_data_len = env->len(env, obj_dest_data);
  
  char* src_data = (char*)env->belems(env, obj_src_data);
  int32_t src_data_len = env->len(env, obj_src_data);
  
  if (dest_offset + length > dest_data_len) {
    SPVM_DIE("Copy is over destination data", MFILE, __LINE__);
  }

  if (src_offset + length > src_data_len) {
    SPVM_DIE("Copy is over source data", MFILE, __LINE__);
  }
  
  memmove((char*)(dest_data + dest_offset * sizeof(double)), (char*)(src_data + src_offset * sizeof(double)), length * sizeof(double));
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__getenv(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  void* obj_name = stack[0].oval;
  if (obj_name == NULL) {
    SPVM_DIE("Name must be defined", MFILE, __LINE__);
  }
  const char* name = (const char*)env->belems(env, obj_name);
  
  const char* value = getenv(name);
  
  void* obj_value;
  if (value == NULL) {
    obj_value = NULL;
  }
  else {
    obj_value = env->new_str(env, value);
  }
  
  stack[0].oval = obj_value;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__abs(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  int32_t value = (int32_t)labs(stack[0].ival);
  
  stack[0].ival = value;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__labs(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  int64_t value = (int64_t)labs(stack[0].lval);
  
  stack[0].lval = value;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__new_oarray_proto(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* oarray = stack[0].oval;
  int32_t length = stack[1].ival;
  
  if (oarray == NULL) {
    SPVM_DIE("Prototype array must be defined", MFILE, __LINE__);
  }
  
  int32_t basic_type_id = env->object_basic_type_id(env, oarray);
  int32_t element_dimension = env->object_type_dimension(env, oarray) - 1;
  
  void* new_oarray = env->new_marray(env, basic_type_id, element_dimension, length);
  
  stack[0].oval = new_oarray;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__reverseb(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* onums = stack[0].oval;
  
  if (onums == NULL) {
    SPVM_DIE("Array must be defined", MFILE, __LINE__);
  }

  int32_t array_length = env->len(env, onums);
  if (array_length == 0) {
    return SPVM_SUCCESS;
  }
  
  int8_t* nums = env->belems(env, onums);
  
  for(int32_t i = 0; i < array_length / 2; i++){
    int8_t tmp = nums[i];
    nums[i] = nums[array_length - i - 1];
    nums[array_length - i - 1] = tmp;
  }
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__reverses(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* onums = stack[0].oval;
  
  if (onums == NULL) {
    SPVM_DIE("Array must be defined", MFILE, __LINE__);
  }

  int32_t array_length = env->len(env, onums);
  if (array_length == 0) {
    return SPVM_SUCCESS;
  }
  
  int16_t* nums = env->selems(env, onums);
  
  for(int32_t i = 0; i < array_length / 2; i++){
    int16_t tmp = nums[i];
    nums[i] = nums[array_length - i - 1];
    nums[array_length - i - 1] = tmp;
  }
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__reversei(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* onums = stack[0].oval;
  
  if (onums == NULL) {
    SPVM_DIE("Array must be defined", MFILE, __LINE__);
  }

  int32_t array_length = env->len(env, onums);
  if (array_length == 0) {
    return SPVM_SUCCESS;
  }
  
  int32_t* nums = env->ielems(env, onums);
  
  for(int32_t i = 0; i < array_length / 2; i++){
    int32_t tmp = nums[i];
    nums[i] = nums[array_length - i - 1];
    nums[array_length - i - 1] = tmp;
  }
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__reversel(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* onums = stack[0].oval;
  
  if (onums == NULL) {
    SPVM_DIE("Array must be defined", MFILE, __LINE__);
  }

  int32_t array_length = env->len(env, onums);
  if (array_length == 0) {
    return SPVM_SUCCESS;
  }
  
  int64_t* nums = env->lelems(env, onums);
  
  for(int32_t i = 0; i < array_length / 2; i++){
    int64_t tmp = nums[i];
    nums[i] = nums[array_length - i - 1];
    nums[array_length - i - 1] = tmp;
  }
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__reversef(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* onums = stack[0].oval;
  
  if (onums == NULL) {
    SPVM_DIE("Array must be defined", MFILE, __LINE__);
  }

  int32_t array_length = env->len(env, onums);
  if (array_length == 0) {
    return SPVM_SUCCESS;
  }
  
  float* nums = env->felems(env, onums);
  
  for(int32_t i = 0; i < array_length / 2; i++){
    float tmp = nums[i];
    nums[i] = nums[array_length - i - 1];
    nums[array_length - i - 1] = tmp;
  }
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__reversed(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* onums = stack[0].oval;
  
  if (onums == NULL) {
    SPVM_DIE("Array must be defined", MFILE, __LINE__);
  }

  int32_t array_length = env->len(env, onums);
  if (array_length == 0) {
    return SPVM_SUCCESS;
  }
  
  double* nums = env->delems(env, onums);
  
  for(int32_t i = 0; i < array_length / 2; i++){
    double tmp = nums[i];
    nums[i] = nums[array_length - i - 1];
    nums[array_length - i - 1] = tmp;
  }
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__reverseo(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* onums = stack[0].oval;
  
  if (onums == NULL) {
    SPVM_DIE("Array must be defined", MFILE, __LINE__);
  }

  int32_t array_length = env->len(env, onums);
  if (array_length == 0) {
    return SPVM_SUCCESS;
  }
  
  for(int32_t i = 0; i < array_length / 2; i++){
    void* tmp = env->oelem(env, onums, i);
    env->set_oelem(env, onums, i, env->oelem(env, onums, array_length - i - 1));
    env->set_oelem(env, onums, array_length - i - 1, tmp);
  }
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__get_type_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  void* object = stack[0].oval;
  
  if (object == NULL) {
    return SPVM_EXCEPTION;
  }
  
  void* type_name = env->type_name(env, object);
  
  stack[0].oval = type_name;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__print(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  void* string = stack[0].oval;
  
  const char* bytes = (const char*)env->belems(env, string);
  int32_t string_length = env->len(env, string);
  
  {
    int32_t i;
    for (i = 0; i < string_length; i++) {
      putchar(bytes[i]);
    }
  }
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__FLT_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].fval = FLT_MAX;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__FLT_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].fval = FLT_MIN;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__DBL_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = DBL_MAX;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__DBL_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = DBL_MIN;
  
  return SPVM_SUCCESS;
}
