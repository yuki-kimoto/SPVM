#include "spvm_native.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <float.h>
#include <complex.h>
#include <memory.h>

static const char* MFILE = "SPVM/CORE.c";

// https://github.com/lattera/glibc/blob/master/stdlib/rand_r.c
static int
SPVM_rand_r (unsigned int *seed)
{
  unsigned int next = *seed;
  int result;

  next *= 1103515245;
  next += 12345;
  result = (unsigned int) (next / 65536) % 2048;

  next *= 1103515245;
  next += 12345;
  result <<= 10;
  result ^= (unsigned int) (next / 65536) % 1024;

  next *= 1103515245;
  next += 12345;
  result <<= 10;
  result ^= (unsigned int) (next / 65536) % 1024;

  *seed = next;

  return result;
}

int32_t SPNATIVE__SPVM__CORE__rand(SPVM_ENV* env, SPVM_VALUE* stack) {

  uint32_t* next_ptr = (uint32_t*)stack[0].iref;
  
  stack[0].ival = (int32_t)SPVM_rand_r(next_ptr);

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__memcpyb(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dist_str = stack[0].oval;
  if (!obj_dist_str) { SPVM_DIE("Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dist_offset = stack[1].ival;
  
  void* obj_src_str = stack[2].oval;
  if (!obj_src_str) { SPVM_DIE("Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return SPVM_SUCCESS;
  }
  else if (length < 0) {
    SPVM_DIE("Length must be zero or positive value", MFILE, __LINE__);
  }
  
  char* dist_str = (char*)env->belems(env, obj_dist_str);
  int32_t dist_str_len = env->len(env, obj_dist_str);
  
  char* src_str = (char*)env->belems(env, obj_src_str);
  int32_t src_str_len = env->len(env, obj_src_str);
  
  if (dist_offset + length > dist_str_len) {
    SPVM_DIE("Copy is over dist string", MFILE, __LINE__);
  }

  if (src_offset + length > src_str_len) {
    SPVM_DIE("Copy is over source string", MFILE, __LINE__);
  }
  
  memcpy((char*)(dist_str + dist_offset), (char*)(src_str + src_offset), length);
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__memmoveb(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dist_str = stack[0].oval;
  if (!obj_dist_str) { SPVM_DIE("Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dist_offset = stack[1].ival;
  
  void* obj_src_str = stack[2].oval;
  if (!obj_src_str) { SPVM_DIE("Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return SPVM_SUCCESS;
  }
  else if (length < 0) {
    SPVM_DIE("Length must be zero or positive value", MFILE, __LINE__);
  }
  
  char* dist_str = (char*)env->belems(env, obj_dist_str);
  int32_t dist_str_len = env->len(env, obj_dist_str);
  
  char* src_str = (char*)env->belems(env, obj_src_str);
  int32_t src_str_len = env->len(env, obj_src_str);
  
  if (dist_offset + length > dist_str_len) {
    SPVM_DIE("Copy is over dist string", MFILE, __LINE__);
  }

  if (src_offset + length > src_str_len) {
    SPVM_DIE("Copy is over source string", MFILE, __LINE__);
  }
  
  memmove((char*)(dist_str + dist_offset), (char*)(src_str + src_offset), length);
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__memcpys(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dist_str = stack[0].oval;
  if (!obj_dist_str) { SPVM_DIE("Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dist_offset = stack[1].ival;
  
  void* obj_src_str = stack[2].oval;
  if (!obj_src_str) { SPVM_DIE("Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return SPVM_SUCCESS;
  }
  else if (length < 0) {
    SPVM_DIE("Length must be zero or positive value", MFILE, __LINE__);
  }
  
  char* dist_str = (char*)env->belems(env, obj_dist_str);
  int32_t dist_str_len = env->len(env, obj_dist_str);
  
  char* src_str = (char*)env->belems(env, obj_src_str);
  int32_t src_str_len = env->len(env, obj_src_str);
  
  if (dist_offset + length > dist_str_len) {
    SPVM_DIE("Copy is over dist string", MFILE, __LINE__);
  }
  
  if (src_offset + length > src_str_len) {
    SPVM_DIE("Copy is over source string", MFILE, __LINE__);
  }
  
  memcpy((char*)(dist_str + dist_offset * sizeof(int16_t)), (char*)(src_str + src_offset * sizeof(int16_t)), length * sizeof(int16_t));
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__memmoves(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dist_str = stack[0].oval;
  if (!obj_dist_str) { SPVM_DIE("Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dist_offset = stack[1].ival;
  
  void* obj_src_str = stack[2].oval;
  if (!obj_src_str) { SPVM_DIE("Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return SPVM_SUCCESS;
  }
  else if (length < 0) {
    SPVM_DIE("Length must be zero or positive value", MFILE, __LINE__);
  }
  
  char* dist_str = (char*)env->belems(env, obj_dist_str);
  int32_t dist_str_len = env->len(env, obj_dist_str);
  
  char* src_str = (char*)env->belems(env, obj_src_str);
  int32_t src_str_len = env->len(env, obj_src_str);
  
  if (dist_offset + length > dist_str_len) {
    SPVM_DIE("Copy is over dist string", MFILE, __LINE__);
  }

  if (src_offset + length > src_str_len) {
    SPVM_DIE("Copy is over source string", MFILE, __LINE__);
  }
  
  memmove((char*)(dist_str + dist_offset * sizeof(int16_t)), (char*)(src_str + src_offset * sizeof(int16_t)), length * sizeof(int16_t));
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__memcpyi(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dist_str = stack[0].oval;
  if (!obj_dist_str) { SPVM_DIE("Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dist_offset = stack[1].ival;
  
  void* obj_src_str = stack[2].oval;
  if (!obj_src_str) { SPVM_DIE("Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return SPVM_SUCCESS;
  }
  else if (length < 0) {
    SPVM_DIE("Length must be zero or positive value", MFILE, __LINE__);
  }
  
  char* dist_str = (char*)env->belems(env, obj_dist_str);
  int32_t dist_str_len = env->len(env, obj_dist_str);
  
  char* src_str = (char*)env->belems(env, obj_src_str);
  int32_t src_str_len = env->len(env, obj_src_str);
  
  if (dist_offset + length > dist_str_len) {
    SPVM_DIE("Copy is over dist string", MFILE, __LINE__);
  }
  
  if (src_offset + length > src_str_len) {
    SPVM_DIE("Copy is over source string", MFILE, __LINE__);
  }
  
  memcpy((char*)(dist_str + dist_offset * sizeof(int32_t)), (char*)(src_str + src_offset * sizeof(int32_t)), length * sizeof(int32_t));
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__memmovei(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dist_str = stack[0].oval;
  if (!obj_dist_str) { SPVM_DIE("Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dist_offset = stack[1].ival;
  
  void* obj_src_str = stack[2].oval;
  if (!obj_src_str) { SPVM_DIE("Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return SPVM_SUCCESS;
  }
  else if (length < 0) {
    SPVM_DIE("Length must be zero or positive value", MFILE, __LINE__);
  }
  
  char* dist_str = (char*)env->belems(env, obj_dist_str);
  int32_t dist_str_len = env->len(env, obj_dist_str);
  
  char* src_str = (char*)env->belems(env, obj_src_str);
  int32_t src_str_len = env->len(env, obj_src_str);
  
  if (dist_offset + length > dist_str_len) {
    SPVM_DIE("Copy is over dist string", MFILE, __LINE__);
  }

  if (src_offset + length > src_str_len) {
    SPVM_DIE("Copy is over source string", MFILE, __LINE__);
  }
  
  memmove((char*)(dist_str + dist_offset * sizeof(int32_t)), (char*)(src_str + src_offset * sizeof(int32_t)), length * sizeof(int32_t));
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__memcpyl(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dist_str = stack[0].oval;
  if (!obj_dist_str) { SPVM_DIE("Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dist_offset = stack[1].ival;
  
  void* obj_src_str = stack[2].oval;
  if (!obj_src_str) { SPVM_DIE("Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return SPVM_SUCCESS;
  }
  else if (length < 0) {
    SPVM_DIE("Length must be zero or positive value", MFILE, __LINE__);
  }
  
  char* dist_str = (char*)env->belems(env, obj_dist_str);
  int32_t dist_str_len = env->len(env, obj_dist_str);
  
  char* src_str = (char*)env->belems(env, obj_src_str);
  int32_t src_str_len = env->len(env, obj_src_str);
  
  if (dist_offset + length > dist_str_len) {
    SPVM_DIE("Copy is over dist string", MFILE, __LINE__);
  }
  
  if (src_offset + length > src_str_len) {
    SPVM_DIE("Copy is over source string", MFILE, __LINE__);
  }
  
  memcpy((char*)(dist_str + dist_offset * sizeof(int64_t)), (char*)(src_str + src_offset * sizeof(int64_t)), length * sizeof(int64_t));
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__memmovel(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dist_str = stack[0].oval;
  if (!obj_dist_str) { SPVM_DIE("Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dist_offset = stack[1].ival;
  
  void* obj_src_str = stack[2].oval;
  if (!obj_src_str) { SPVM_DIE("Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return SPVM_SUCCESS;
  }
  else if (length < 0) {
    SPVM_DIE("Length must be zero or positive value", MFILE, __LINE__);
  }
  
  char* dist_str = (char*)env->belems(env, obj_dist_str);
  int32_t dist_str_len = env->len(env, obj_dist_str);
  
  char* src_str = (char*)env->belems(env, obj_src_str);
  int32_t src_str_len = env->len(env, obj_src_str);
  
  if (dist_offset + length > dist_str_len) {
    SPVM_DIE("Copy is over dist string", MFILE, __LINE__);
  }

  if (src_offset + length > src_str_len) {
    SPVM_DIE("Copy is over source string", MFILE, __LINE__);
  }
  
  memmove((char*)(dist_str + dist_offset * sizeof(int64_t)), (char*)(src_str + src_offset * sizeof(int64_t)), length * sizeof(int64_t));
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__memcpyf(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dist_str = stack[0].oval;
  if (!obj_dist_str) { SPVM_DIE("Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dist_offset = stack[1].ival;
  
  void* obj_src_str = stack[2].oval;
  if (!obj_src_str) { SPVM_DIE("Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return SPVM_SUCCESS;
  }
  else if (length < 0) {
    SPVM_DIE("Length must be zero or positive value", MFILE, __LINE__);
  }
  
  char* dist_str = (char*)env->belems(env, obj_dist_str);
  int32_t dist_str_len = env->len(env, obj_dist_str);
  
  char* src_str = (char*)env->belems(env, obj_src_str);
  int32_t src_str_len = env->len(env, obj_src_str);
  
  if (dist_offset + length > dist_str_len) {
    SPVM_DIE("Copy is over dist string", MFILE, __LINE__);
  }
  
  if (src_offset + length > src_str_len) {
    SPVM_DIE("Copy is over source string", MFILE, __LINE__);
  }
  
  memcpy((char*)(dist_str + dist_offset * sizeof(float)), (char*)(src_str + src_offset * sizeof(float)), length * sizeof(float));
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__memmovef(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dist_str = stack[0].oval;
  if (!obj_dist_str) { SPVM_DIE("Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dist_offset = stack[1].ival;
  
  void* obj_src_str = stack[2].oval;
  if (!obj_src_str) { SPVM_DIE("Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return SPVM_SUCCESS;
  }
  else if (length < 0) {
    SPVM_DIE("Length must be zero or positive value", MFILE, __LINE__);
  }
  
  char* dist_str = (char*)env->belems(env, obj_dist_str);
  int32_t dist_str_len = env->len(env, obj_dist_str);
  
  char* src_str = (char*)env->belems(env, obj_src_str);
  int32_t src_str_len = env->len(env, obj_src_str);
  
  if (dist_offset + length > dist_str_len) {
    SPVM_DIE("Copy is over dist string", MFILE, __LINE__);
  }

  if (src_offset + length > src_str_len) {
    SPVM_DIE("Copy is over source string", MFILE, __LINE__);
  }
  
  memmove((char*)(dist_str + dist_offset * sizeof(float)), (char*)(src_str + src_offset * sizeof(float)), length * sizeof(float));
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__memcpyd(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dist_str = stack[0].oval;
  if (!obj_dist_str) { SPVM_DIE("Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dist_offset = stack[1].ival;
  
  void* obj_src_str = stack[2].oval;
  if (!obj_src_str) { SPVM_DIE("Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return SPVM_SUCCESS;
  }
  else if (length < 0) {
    SPVM_DIE("Length must be zero or positive value", MFILE, __LINE__);
  }
  
  char* dist_str = (char*)env->belems(env, obj_dist_str);
  int32_t dist_str_len = env->len(env, obj_dist_str);
  
  char* src_str = (char*)env->belems(env, obj_src_str);
  int32_t src_str_len = env->len(env, obj_src_str);
  
  if (dist_offset + length > dist_str_len) {
    SPVM_DIE("Copy is over dist string", MFILE, __LINE__);
  }
  
  if (src_offset + length > src_str_len) {
    SPVM_DIE("Copy is over source string", MFILE, __LINE__);
  }
  
  memcpy((char*)(dist_str + dist_offset * sizeof(double)), (char*)(src_str + src_offset * sizeof(double)), length * sizeof(double));
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__memmoved(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dist_str = stack[0].oval;
  if (!obj_dist_str) { SPVM_DIE("Dist string must be defined", MFILE, __LINE__); }
  
  int32_t dist_offset = stack[1].ival;
  
  void* obj_src_str = stack[2].oval;
  if (!obj_src_str) { SPVM_DIE("Source string must be defined", MFILE, __LINE__); }
  
  int32_t src_offset = stack[3].ival;
  
  int32_t length = stack[4].ival;

  if (length == 0) {
    return SPVM_SUCCESS;
  }
  else if (length < 0) {
    SPVM_DIE("Length must be zero or positive value", MFILE, __LINE__);
  }
  
  char* dist_str = (char*)env->belems(env, obj_dist_str);
  int32_t dist_str_len = env->len(env, obj_dist_str);
  
  char* src_str = (char*)env->belems(env, obj_src_str);
  int32_t src_str_len = env->len(env, obj_src_str);
  
  if (dist_offset + length > dist_str_len) {
    SPVM_DIE("Copy is over dist string", MFILE, __LINE__);
  }

  if (src_offset + length > src_str_len) {
    SPVM_DIE("Copy is over source string", MFILE, __LINE__);
  }
  
  memmove((char*)(dist_str + dist_offset * sizeof(double)), (char*)(src_str + src_offset * sizeof(double)), length * sizeof(double));
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__strerror(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_number = stack[0].ival;
  const char* string_error = strerror(error_number);
  
  void* obj_string_error = env->new_str(env, string_error);
  
  stack[0].oval = obj_string_error;
  
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

int32_t SPNATIVE__SPVM__CORE__init_native_constants(SPVM_ENV* env, SPVM_VALUE* stack) {

  // STDIN
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::CORE", "$STDIN", "SPVM::FileHandle");
    if (pkgvar_id < 0) { abort(); }
    int32_t fh_basic_type_id = env->basic_type_id(env, "SPVM::FileHandle");
    if (fh_basic_type_id < 0) { abort(); }
    void* ostdin = env->new_pointer(env, fh_basic_type_id, stdin);
    env->set_opkgvar(env, pkgvar_id, ostdin);
  }

  // STDOUT
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::CORE", "$STDOUT", "SPVM::FileHandle");
    if (pkgvar_id < 0) { abort(); }
    int32_t fh_basic_type_id = env->basic_type_id(env, "SPVM::FileHandle");
    if (fh_basic_type_id < 0) { abort(); }
    void* ostdout = env->new_pointer(env, fh_basic_type_id, stdout);
    env->set_opkgvar(env, pkgvar_id, ostdout);
  }
  
  // EOF
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::CORE", "$EOF", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EOF);
  }
  
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

int32_t SPNATIVE__SPVM__CORE__type_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  void* object = stack[0].oval;
  
  if (object == NULL) {
    return SPVM_EXCEPTION;
  }
  
  void* type_name = env->type_name(env, object);
  
  stack[0].oval = type_name;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__cadd(SPVM_ENV* env, SPVM_VALUE* stack) {
  double _Complex x_in1 = stack[0].dval + stack[1].dval * _Complex_I ;
  double _Complex x_in2 = stack[2].dval + stack[3].dval * _Complex_I ;
  
  double _Complex x_out = x_in1 + x_in2;
  
  stack[0].dval = creal(x_out);
  stack[1].dval = cimag(x_out);
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__csub(SPVM_ENV* env, SPVM_VALUE* stack) {
  double _Complex x_in1 = stack[0].dval + stack[1].dval * _Complex_I ;
  double _Complex x_in2 = stack[2].dval + stack[3].dval * _Complex_I ;
  
  double _Complex x_out = x_in1 - x_in2;
  
  stack[0].dval = creal(x_out);
  stack[1].dval = cimag(x_out);
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__cmul(SPVM_ENV* env, SPVM_VALUE* stack) {
  double _Complex x_in1 = stack[0].dval + stack[1].dval * _Complex_I ;
  double _Complex x_in2 = stack[2].dval + stack[3].dval * _Complex_I ;
  
  double _Complex x_out = x_in1 * x_in2;
  
  stack[0].dval = creal(x_out);
  stack[1].dval = cimag(x_out);
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__cdiv(SPVM_ENV* env, SPVM_VALUE* stack) {
  double _Complex x_in1 = stack[0].dval + stack[1].dval * _Complex_I ;
  double _Complex x_in2 = stack[2].dval + stack[3].dval * _Complex_I ;
  
  double _Complex x_out = x_in1 / x_in2;
  
  stack[0].dval = creal(x_out);
  stack[1].dval = cimag(x_out);
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__caddf(SPVM_ENV* env, SPVM_VALUE* stack) {
  float _Complex x_in1 = stack[0].fval + stack[1].fval * _Complex_I ;
  float _Complex x_in2 = stack[2].fval + stack[3].fval * _Complex_I ;
  
  float _Complex x_out = x_in1 + x_in2;
  
  stack[0].fval = creal(x_out);
  stack[1].fval = cimag(x_out);
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__csubf(SPVM_ENV* env, SPVM_VALUE* stack) {
  float _Complex x_in1 = stack[0].fval + stack[1].fval * _Complex_I ;
  float _Complex x_in2 = stack[2].fval + stack[3].fval * _Complex_I ;
  
  float _Complex x_out = x_in1 - x_in2;
  
  stack[0].fval = creal(x_out);
  stack[1].fval = cimag(x_out);
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__cmulf(SPVM_ENV* env, SPVM_VALUE* stack) {
  float _Complex x_in1 = stack[0].fval + stack[1].fval * _Complex_I ;
  float _Complex x_in2 = stack[2].fval + stack[3].fval * _Complex_I ;
  
  float _Complex x_out = x_in1 * x_in2;
  
  stack[0].fval = creal(x_out);
  stack[1].fval = cimag(x_out);
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__cdivf(SPVM_ENV* env, SPVM_VALUE* stack) {
  float _Complex x_in1 = stack[0].fval + stack[1].fval * _Complex_I ;
  float _Complex x_in2 = stack[2].fval + stack[3].fval * _Complex_I ;
  
  float _Complex x_out = x_in1 / x_in2;
  
  stack[0].fval = creal(x_out);
  stack[1].fval = cimag(x_out);
  
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

int32_t SPNATIVE__SPVM__CORE__warn(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  void* object = stack[0].oval;
  
  const char* bytes = (const char*)env->belems(env, object);
  int32_t string_length = env->len(env, object);
  
  {
    int32_t i;
    for (i = 0; i < string_length; i++) {
      putc(bytes[i], stderr);
    }
  }
  
  fprintf(stderr, "\n");
  
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

int32_t SPNATIVE__SPVM__CORE__INT8_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].bval = (int8_t)-128;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__INT8_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].bval = (int8_t)127;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__INT16_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].sval = (int16_t)-32768;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__INT16_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].sval = (int16_t)32767;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__INT32_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].ival = (int32_t)-2147483648UL;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__INT32_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].ival = (int32_t)2147483647L;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__INT64_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].lval = (int64_t)-9223372036854775808ULL;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__INT64_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].lval = (int64_t)9223372036854775807LL;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__PI(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = 3.14159265358979323846;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__E(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = 2.7182818284590452354;
  
  return SPVM_SUCCESS;
}

// https://github.com/gcc-mirror/gcc/blob/master/libstdc++-v3/libsupc++/hash_bytes.cc#L72-L112
int32_t SPNATIVE__SPVM__CORE__murmur_hash(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  void* object = stack[0].oval;
  uint32_t seed = stack[1].ival;

  const char* buf = (const char*)env->belems(env, object);
  uint32_t len = env->len(env, object);

  uint32_t m = 0x5bd1e995;
  uint32_t hash = seed ^ len;

  // Mix 4 bytes at a time into the hash.
  while(len >= 4) {
    uint32_t k;
    memcpy(&k, buf, sizeof(k));
    k *= m;
    k ^= k >> 24;
    k *= m;
    hash *= m;
    hash ^= k;
    buf += 4;
    len -= 4;
  }

  // Handle the last few bytes of the input array.
  switch(len) {
    case 3:
      hash ^= (unsigned char)buf[2] << 16;
    case 2:
      hash ^= (unsigned char)buf[1] << 8;
    case 1:
      hash ^= (unsigned char)buf[0];
      hash *= m;
    };

  // Do a few final mixes of the hash.
  hash ^= hash >> 13;
  hash *= m;
  hash ^= hash >> 15;
  stack[0].lval = hash; // return a long value to ensure being positive.

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__CORE__sleep(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void) env;

  uint32_t seconds = stack[0].lval;
  sleep(seconds);

  return SPVM_SUCCESS;
}
