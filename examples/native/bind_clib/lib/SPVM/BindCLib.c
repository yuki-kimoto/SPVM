// lib/SPVM/BindCLib.c
#include "spvm_native.h"

#include "bind_clib.h"

int32_t SPNATIVE__SPVM__BindCLib__sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* sv_nums = stack[0].oval;
  
  int32_t length = env->length(env, sv_nums);
  
  int32_t* nums = env->get_elems_int(env, sv_nums);
  
  int32_t total = bind_clib_sum(nums, length);
  
  stack[0].ival = total;
  
  return 0;
}
