#include "spvm_native.h"

static const char* MFILE = "SPVM/Array.c";

int32_t SPVM__Array__memcpy_byte(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPVM__Array__memmove_byte(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPVM__Array__memcpy_short(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPVM__Array__memmove_short(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPVM__Array__memcpy_int(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPVM__Array__memmove_int(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPVM__Array__memcpy_long(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPVM__Array__memmove_long(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPVM__Array__memcpy_float(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPVM__Array__memmove_float(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPVM__Array__memcpy_double(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPVM__Array__memmove_double(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPVM__Array__new_proto(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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
