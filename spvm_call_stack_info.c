#include "spvm_call_stack_info.h"
#include "spvm_runtime.h"
#include "spvm_constant_pool_sub.h"

void SPVM_CALL_STACK_init_call_stack_info(SPVM_CALL_STACK_INFO* call_stack_info, SPVM_RUNTIME* runtime, int32_t sub_id) {
  // Constant pool
  int32_t* constant_pool = runtime->constant_pool;
  
  SPVM_CONSTANT_POOL_SUB* constant_pool_sub = (SPVM_CONSTANT_POOL_SUB*)&constant_pool[sub_id];
  
  // Length
  call_stack_info->length = constant_pool_sub->mys_length + 1 + constant_pool_sub->auto_dec_ref_count_stack_max_length;
  
  call_stack_info->auto_dec_ref_count_stack_top_index = constant_pool_sub->mys_length;
  call_stack_info->auto_dec_ref_count_stack_base = call_stack_info->auto_dec_ref_count_stack_top_index + 1;
}
