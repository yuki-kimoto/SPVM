#include "spvm_native.h"

#include <string.h>

static const char* MFILE = "SPVM/Array1.c";

int32_t SPVM__Array1__memcpy_byte(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* sv_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* sv_source = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;

  if (!sv_dest) {
    return env->die(env, stack, "Destnation must be defined", MFILE, __LINE__);
  }
  
  if (!sv_source) {
    return env->die(env, stack, "Source must be defined", MFILE, __LINE__);
  }
  
  if (length == 0) {
    return 0;
  }
  else if (length < 0) {
    return env->die(env, stack, "Length must be more than or equals to 0", MFILE, __LINE__);
  }
  
  int8_t* dest = env->get_elems_byte(env, stack, sv_dest);
  int32_t dest_len = env->length(env, stack, sv_dest);
  
  int8_t* source = env->get_elems_byte(env, stack, sv_source);
  int32_t source_len = env->length(env, stack, sv_source);
  
  if (dest_offset + length > dest_len) {
    return env->die(env, stack, "Destnation offset + length must be within the range of the destnation array", MFILE, __LINE__);
  }

  if (source_offset + length > source_len) {
    return env->die(env, stack, "Source offset + length must be within the range of the source array", MFILE, __LINE__);
  }
  
  memcpy((char*)(dest + dest_offset), (char*)(source + source_offset), length);
  
  return 0;
}
