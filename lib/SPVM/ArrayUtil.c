#include "spvm_native.h"


static const char* MFILE = "SPVM/ArrayUtil.c";

int32_t SPNATIVE__SPVM__ArrayUtil__memcpy_byte(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPNATIVE__SPVM__ArrayUtil__memmove_byte(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPNATIVE__SPVM__ArrayUtil__memcpy_short(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPNATIVE__SPVM__ArrayUtil__memmove_short(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPNATIVE__SPVM__ArrayUtil__memcpy_int(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPNATIVE__SPVM__ArrayUtil__memmove_int(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPNATIVE__SPVM__ArrayUtil__memcpy_long(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPNATIVE__SPVM__ArrayUtil__memmove_long(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPNATIVE__SPVM__ArrayUtil__memcpy_float(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPNATIVE__SPVM__ArrayUtil__memmove_float(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPNATIVE__SPVM__ArrayUtil__memcpy_double(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPNATIVE__SPVM__ArrayUtil__memmove_double(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPNATIVE__SPVM__ArrayUtil__new_object_array_proto(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

