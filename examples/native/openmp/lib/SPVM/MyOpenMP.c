#include "spvm_native.h"

#include <string.h>

static const char* FILE_NAME = "SPVM/MyOpenMP.c";

int32_t SPVM__MyOpenMP__sum_vec_int(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_nums1 = stack[0].oval;
  if (obj_nums1 == NULL) {
    return env->die_v2(env, stack, "$nums1 must be defined.", __func__, FILE_NAME, __LINE__);
  }
  int32_t* nums1 = env->get_elems_int(env, stack, obj_nums1);
  
  void* obj_nums2 = stack[1].oval;
  if(obj_nums2 == NULL) {
    return env->die_v2(env, stack, "$nums2 must be defined.", __func__, FILE_NAME, __LINE__);
  }
  int32_t* nums2 = env->get_elems_int(env, stack, obj_nums2);
  
  int32_t length = env->length(env, stack, obj_nums1);
  
  void* obj_nums3 = env->new_int_array(env, stack, length);
  int32_t* nums3 = env->get_elems_int(env, stack, obj_nums3);
  
  int32_t i;
#pragma omp parallel for
  for (i = 0; i < length; i++) {
    nums3[i] = nums1[i] + nums2[i];
  }
  
  stack[0].oval = obj_nums3;
  
  return 0;
}
