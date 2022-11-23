#include "spvm_native.h"

#include <string.h>

static const char* FILE_NAME = "Array.c";

int32_t SPVM__Array__memcpy_byte(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* obj_source = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;
  
  if (!obj_dest) {
    return env->die(env, stack, "The dest must be defined", FILE_NAME, __LINE__);
  }
  
  if (!obj_source) {
    return env->die(env, stack, "The source must be defined", FILE_NAME, __LINE__);
  }
  
  if (!(length >= 0)) {
    return env->die(env, stack, "The length must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (!(dest_offset >= 0)) {
    return env->die(env, stack, "The dest_offset must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (!(source_offset >= 0)) {
    return env->die(env, stack, "The source_offset must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (length == 0) {
    return 0;
  }
  
  int8_t* dest = env->get_elems_byte(env, stack, obj_dest);
  int32_t dest_length = env->length(env, stack, obj_dest);
  
  int8_t* source = env->get_elems_byte(env, stack, obj_source);
  int32_t source_length = env->length(env, stack, obj_source);
  
  if (!(dest_offset + length <= dest_length)) {
    return env->die(env, stack, "The dest_offset + the length must be less than or equal to the length of the dest", FILE_NAME, __LINE__);
  }
  
  if (!(source_offset + length <= source_length)) {
    return env->die(env, stack, "The source_offset + the length must be less than or equal to the length of the source", FILE_NAME, __LINE__);
  }
  
  memcpy((char*)(dest + dest_offset), (char*)(source + source_offset), length);
  
  return 0;
}

int32_t SPVM__Array__memcpy_double(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* obj_source = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;
  
  if (!obj_dest) {
    return env->die(env, stack, "The dest must be defined", FILE_NAME, __LINE__);
  }
  
  if (!obj_source) {
    return env->die(env, stack, "The source must be defined", FILE_NAME, __LINE__);
  }
  
  if (!(length >= 0)) {
    return env->die(env, stack, "The length must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (!(dest_offset >= 0)) {
    return env->die(env, stack, "The dest_offset must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (!(source_offset >= 0)) {
    return env->die(env, stack, "The source_offset must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (length == 0) {
    return 0;
  }
  
  double* dest = env->get_elems_double(env, stack, obj_dest);
  int32_t dest_length = env->length(env, stack, obj_dest);
  
  double* source = env->get_elems_double(env, stack, obj_source);
  int32_t source_length = env->length(env, stack, obj_source);
  
  if (!(dest_offset + length <= dest_length)) {
    return env->die(env, stack, "The dest_offset + the length must be less than or equal to the length of the dest", FILE_NAME, __LINE__);
  }
  
  if (!(source_offset + length <= source_length)) {
    return env->die(env, stack, "The source_offset + the length must be less than or equal to the length of the source", FILE_NAME, __LINE__);
  }
  
  memcpy((char*)(dest + dest_offset), (char*)(source + source_offset), length * sizeof(double));
  
  return 0;
}

int32_t SPVM__Array__memcpy_float(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* obj_source = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;
  
  if (!obj_dest) {
    return env->die(env, stack, "The dest must be defined", FILE_NAME, __LINE__);
  }
  
  if (!obj_source) {
    return env->die(env, stack, "The source must be defined", FILE_NAME, __LINE__);
  }
  
  if (!(length >= 0)) {
    return env->die(env, stack, "The length must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (!(dest_offset >= 0)) {
    return env->die(env, stack, "The dest_offset must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (!(source_offset >= 0)) {
    return env->die(env, stack, "The source_offset must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (length == 0) {
    return 0;
  }
  
  float* dest = env->get_elems_float(env, stack, obj_dest);
  int32_t dest_length = env->length(env, stack, obj_dest);
  
  float* source = env->get_elems_float(env, stack, obj_source);
  int32_t source_length = env->length(env, stack, obj_source);
  
  if (!(dest_offset + length <= dest_length)) {
    return env->die(env, stack, "The dest_offset + the length must be less than or equal to the length of the dest", FILE_NAME, __LINE__);
  }
  
  if (!(source_offset + length <= source_length)) {
    return env->die(env, stack, "The source_offset + the length must be less than or equal to the length of the source", FILE_NAME, __LINE__);
  }
  
  memcpy((char*)(dest + dest_offset), (char*)(source + source_offset), length * sizeof(float));
  
  return 0;
}

int32_t SPVM__Array__memcpy_int(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* obj_source = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;
  
  if (!obj_dest) {
    return env->die(env, stack, "The dest must be defined", FILE_NAME, __LINE__);
  }
  
  if (!obj_source) {
    return env->die(env, stack, "The source must be defined", FILE_NAME, __LINE__);
  }
  
  if (!(length >= 0)) {
    return env->die(env, stack, "The length must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (!(dest_offset >= 0)) {
    return env->die(env, stack, "The dest_offset must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (!(source_offset >= 0)) {
    return env->die(env, stack, "The source_offset must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (length == 0) {
    return 0;
  }
  
  int32_t* dest = env->get_elems_int(env, stack, obj_dest);
  int32_t dest_length = env->length(env, stack, obj_dest);
  
  int32_t* source = env->get_elems_int(env, stack, obj_source);
  int32_t source_length = env->length(env, stack, obj_source);
  
  if (!(dest_offset + length <= dest_length)) {
    return env->die(env, stack, "The dest_offset + the length must be less than or equal to the length of the dest", FILE_NAME, __LINE__);
  }
  
  if (!(source_offset + length <= source_length)) {
    return env->die(env, stack, "The source_offset + the length must be less than or equal to the length of the source", FILE_NAME, __LINE__);
  }
  
  memcpy((char*)(dest + dest_offset), (char*)(source + source_offset), length * sizeof(int32_t));
  
  return 0;
}

int32_t SPVM__Array__memcpy_long(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* obj_source = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;
  
  if (!obj_dest) {
    return env->die(env, stack, "The dest must be defined", FILE_NAME, __LINE__);
  }
  
  if (!obj_source) {
    return env->die(env, stack, "The source must be defined", FILE_NAME, __LINE__);
  }
  
  if (!(length >= 0)) {
    return env->die(env, stack, "The length must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (!(dest_offset >= 0)) {
    return env->die(env, stack, "The dest_offset must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (!(source_offset >= 0)) {
    return env->die(env, stack, "The source_offset must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (length == 0) {
    return 0;
  }
  
  int64_t* dest = env->get_elems_long(env, stack, obj_dest);
  int32_t dest_length = env->length(env, stack, obj_dest);
  
  int64_t* source = env->get_elems_long(env, stack, obj_source);
  int32_t source_length = env->length(env, stack, obj_source);
  
  if (!(dest_offset + length <= dest_length)) {
    return env->die(env, stack, "The dest_offset + the length must be less than or equal to the length of the dest", FILE_NAME, __LINE__);
  }
  
  if (!(source_offset + length <= source_length)) {
    return env->die(env, stack, "The source_offset + the length must be less than or equal to the length of the source", FILE_NAME, __LINE__);
  }
  
  memcpy((char*)(dest + dest_offset), (char*)(source + source_offset), length * sizeof(int64_t));
  
  return 0;
}

int32_t SPVM__Array__memcpy_short(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* obj_source = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;
  
  if (!obj_dest) {
    return env->die(env, stack, "The dest must be defined", FILE_NAME, __LINE__);
  }
  
  if (!obj_source) {
    return env->die(env, stack, "The source must be defined", FILE_NAME, __LINE__);
  }
  
  if (!(length >= 0)) {
    return env->die(env, stack, "The length must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (!(dest_offset >= 0)) {
    return env->die(env, stack, "The dest_offset must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (!(source_offset >= 0)) {
    return env->die(env, stack, "The source_offset must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (length == 0) {
    return 0;
  }
  
  int16_t* dest = env->get_elems_short(env, stack, obj_dest);
  int32_t dest_length = env->length(env, stack, obj_dest);
  
  int16_t* source = env->get_elems_short(env, stack, obj_source);
  int32_t source_length = env->length(env, stack, obj_source);
  
  if (!(dest_offset + length <= dest_length)) {
    return env->die(env, stack, "The dest_offset + the length must be less than or equal to the length of the dest", FILE_NAME, __LINE__);
  }
  
  if (!(source_offset + length <= source_length)) {
    return env->die(env, stack, "The source_offset + the length must be less than or equal to the length of the source", FILE_NAME, __LINE__);
  }
  
  memcpy((char*)(dest + dest_offset), (char*)(source + source_offset), length * sizeof(int16_t));
  
  return 0;
}

int32_t SPVM__Array__memmove_byte(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* obj_source = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;

  if (!obj_dest) {
    return env->die(env, stack, "The dest must be defined", FILE_NAME, __LINE__);
  }
  
  if (!obj_source) {
    return env->die(env, stack, "The source must be defined", FILE_NAME, __LINE__);
  }
  
  if (!(length >= 0)) {
    return env->die(env, stack, "The length must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (!(dest_offset >= 0)) {
    return env->die(env, stack, "The dest_offset must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (!(source_offset >= 0)) {
    return env->die(env, stack, "The source_offset must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (length == 0) {
    return 0;
  }
  
  int8_t* dest = env->get_elems_byte(env, stack, obj_dest);
  int32_t dest_length = env->length(env, stack, obj_dest);
  
  int8_t* source = env->get_elems_byte(env, stack, obj_source);
  int32_t source_length = env->length(env, stack, obj_source);
  
  if (!(dest_offset + length <= dest_length)) {
    return env->die(env, stack, "The dest_offset + the length must be less than or equal to the length of the dest", FILE_NAME, __LINE__);
  }
  
  if (!(source_offset + length <= source_length)) {
    return env->die(env, stack, "The source_offset + the length must be less than or equal to the length of the source", FILE_NAME, __LINE__);
  }
  
  memmove((char*)(dest + dest_offset), (char*)(source + source_offset), length);
  
  return 0;
}

int32_t SPVM__Array__memmove_double(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* obj_source = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;
  
  if (!obj_dest) {
    return env->die(env, stack, "The dest must be defined", FILE_NAME, __LINE__);
  }
  
  if (!obj_source) {
    return env->die(env, stack, "The source must be defined", FILE_NAME, __LINE__);
  }
  
  if (!(length >= 0)) {
    return env->die(env, stack, "The length must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (!(dest_offset >= 0)) {
    return env->die(env, stack, "The dest_offset must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (!(source_offset >= 0)) {
    return env->die(env, stack, "The source_offset must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (length == 0) {
    return 0;
  }
  
  double* dest = env->get_elems_double(env, stack, obj_dest);
  int32_t dest_length = env->length(env, stack, obj_dest);
  
  double* source = env->get_elems_double(env, stack, obj_source);
  int32_t source_length = env->length(env, stack, obj_source);
  
  if (!(dest_offset + length <= dest_length)) {
    return env->die(env, stack, "The dest_offset + the length must be less than or equal to the length of the dest", FILE_NAME, __LINE__);
  }
  
  if (!(source_offset + length <= source_length)) {
    return env->die(env, stack, "The source_offset + the length must be less than or equal to the length of the source", FILE_NAME, __LINE__);
  }
  
  memmove((char*)(dest + dest_offset), (char*)(source + source_offset), length * sizeof(double));
  
  return 0;
}

int32_t SPVM__Array__memmove_float(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* obj_source = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;
  
  if (!obj_dest) {
    return env->die(env, stack, "The dest must be defined", FILE_NAME, __LINE__);
  }
  
  if (!obj_source) {
    return env->die(env, stack, "The source must be defined", FILE_NAME, __LINE__);
  }
  
  if (!(length >= 0)) {
    return env->die(env, stack, "The length must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (!(dest_offset >= 0)) {
    return env->die(env, stack, "The dest_offset must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (!(source_offset >= 0)) {
    return env->die(env, stack, "The source_offset must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (length == 0) {
    return 0;
  }
  
  float* dest = env->get_elems_float(env, stack, obj_dest);
  int32_t dest_length = env->length(env, stack, obj_dest);
  
  float* source = env->get_elems_float(env, stack, obj_source);
  int32_t source_length = env->length(env, stack, obj_source);
  
  if (!(dest_offset + length <= dest_length)) {
    return env->die(env, stack, "The dest_offset + the length must be less than or equal to the length of the dest", FILE_NAME, __LINE__);
  }
  
  if (!(source_offset + length <= source_length)) {
    return env->die(env, stack, "The source_offset + the length must be less than or equal to the length of the source", FILE_NAME, __LINE__);
  }
  
  memmove((char*)(dest + dest_offset), (char*)(source + source_offset), length * sizeof(float));
  
  return 0;
}

int32_t SPVM__Array__memmove_int(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* obj_source = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;
  
  if (!obj_dest) {
    return env->die(env, stack, "The dest must be defined", FILE_NAME, __LINE__);
  }
  
  if (!obj_source) {
    return env->die(env, stack, "The source must be defined", FILE_NAME, __LINE__);
  }
  
  if (!(length >= 0)) {
    return env->die(env, stack, "The length must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (!(dest_offset >= 0)) {
    return env->die(env, stack, "The dest_offset must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (!(source_offset >= 0)) {
    return env->die(env, stack, "The source_offset must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (length == 0) {
    return 0;
  }
  
  int32_t* dest = env->get_elems_int(env, stack, obj_dest);
  int32_t dest_length = env->length(env, stack, obj_dest);
  
  int32_t* source = env->get_elems_int(env, stack, obj_source);
  int32_t source_length = env->length(env, stack, obj_source);
  
  if (!(dest_offset + length <= dest_length)) {
    return env->die(env, stack, "The dest_offset + the length must be less than or equal to the length of the dest", FILE_NAME, __LINE__);
  }
  
  if (!(source_offset + length <= source_length)) {
    return env->die(env, stack, "The source_offset + the length must be less than or equal to the length of the source", FILE_NAME, __LINE__);
  }
  
  memmove((char*)(dest + dest_offset), (char*)(source + source_offset), length * sizeof(int32_t));
  
  return 0;
}

int32_t SPVM__Array__memmove_long(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* obj_source = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;
  
  if (!obj_dest) {
    return env->die(env, stack, "The dest must be defined", FILE_NAME, __LINE__);
  }
  
  if (!obj_source) {
    return env->die(env, stack, "The source must be defined", FILE_NAME, __LINE__);
  }
  
  if (!(length >= 0)) {
    return env->die(env, stack, "The length must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (!(dest_offset >= 0)) {
    return env->die(env, stack, "The dest_offset must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (!(source_offset >= 0)) {
    return env->die(env, stack, "The source_offset must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (length == 0) {
    return 0;
  }
  
  int64_t* dest = env->get_elems_long(env, stack, obj_dest);
  int32_t dest_length = env->length(env, stack, obj_dest);
  
  int64_t* source = env->get_elems_long(env, stack, obj_source);
  int32_t source_length = env->length(env, stack, obj_source);
  
  if (!(dest_offset + length <= dest_length)) {
    return env->die(env, stack, "The dest_offset + the length must be less than or equal to the length of the dest", FILE_NAME, __LINE__);
  }
  
  if (!(source_offset + length <= source_length)) {
    return env->die(env, stack, "The source_offset + the length must be less than or equal to the length of the source", FILE_NAME, __LINE__);
  }
  
  memmove((char*)(dest + dest_offset), (char*)(source + source_offset), length * sizeof(int64_t));
  
  return 0;
}

int32_t SPVM__Array__memmove_short(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* obj_source = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;
  
  if (!obj_dest) {
    return env->die(env, stack, "The dest must be defined", FILE_NAME, __LINE__);
  }
  
  if (!obj_source) {
    return env->die(env, stack, "The source must be defined", FILE_NAME, __LINE__);
  }
  
  if (!(length >= 0)) {
    return env->die(env, stack, "The length must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (!(dest_offset >= 0)) {
    return env->die(env, stack, "The dest_offset must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (!(source_offset >= 0)) {
    return env->die(env, stack, "The source_offset must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (length == 0) {
    return 0;
  }
  
  int16_t* dest = env->get_elems_short(env, stack, obj_dest);
  int32_t dest_length = env->length(env, stack, obj_dest);
  
  int16_t* source = env->get_elems_short(env, stack, obj_source);
  int32_t source_length = env->length(env, stack, obj_source);
  
  if (!(dest_offset + length <= dest_length)) {
    return env->die(env, stack, "The dest_offset + the length must be less than or equal to the length of the dest", FILE_NAME, __LINE__);
  }
  
  if (!(source_offset + length <= source_length)) {
    return env->die(env, stack, "The source_offset + the length must be less than or equal to the length of the source", FILE_NAME, __LINE__);
  }
  
  memmove((char*)(dest + dest_offset), (char*)(source + source_offset), length * sizeof(int16_t));
  
  return 0;
}

int32_t SPVM__Array__new_proto(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* array = stack[0].oval;
  int32_t length = stack[1].ival;
  
  if (!array) {
    return env->die(env, stack, "The prototype array must be defined", FILE_NAME, __LINE__);
  }

  if (!(length >= 0)) {
    return env->die(env, stack, "The length must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  void* new_object_array = env->new_array_proto(env, stack, array, length);
  
  stack[0].oval = new_object_array;
  
  return 0;
}
