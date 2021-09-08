// lib/SPVM/MyAdd.cu
#include "spvm_native.h"
#include "cuda_array_culc.h"

extern "C" {

int32_t SPNATIVE__SPVM__MyAdd__add_cuda(SPVM_ENV* env, SPVM_VALUE* stack) {
   
  void* sv_nums1 = stack[0].oval;
  void* sv_nums2 = stack[1].oval;
  
  int32_t length1 = env->length(env, sv_nums1);
  int32_t length2 = env->length(env, sv_nums2); 
  
  float* nums1 = env->get_elems_float(env, sv_nums1);
  float* nums2 = env->get_elems_float(env, sv_nums2);   
  
  cuda_array_culc_add_float(nums1, nums2, length1);
 
  return 0;
}
} // End of extern "C"


