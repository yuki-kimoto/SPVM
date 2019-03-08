#include "spvm_native.h"

#include <assert.h>
#include <stdlib.h>
#include <netdb.h>

int32_t SPNATIVE__SPVM__protoent__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  struct protoent* pent = env->alloc_memory_block_zero(env, sizeof(struct protoent));
  
  int32_t protoent_basic_type_id = env->basic_type_id(env, "SPVM::protoent");
  assert(protoent_basic_type_id >= 0);
  void* obj_pent = env->new_pointer(env, protoent_basic_type_id, pent);
  
  stack[0].oval = obj_pent;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__protoent__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_pent = stack[0].oval;
  
  struct protoent* pent = env->pointer(env, obj_pent);
  
  env->free_memory_block(env, pent);
  
  return SPVM_SUCCESS;
}
