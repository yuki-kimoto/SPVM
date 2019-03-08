#include "spvm_native.h"

#include <assert.h>
#include <stdlib.h>
#include <netdb.h>

int32_t SPNATIVE__SPVM__servent__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  struct servent* sent = env->alloc_memory_block_zero(env, (sizeof(struct servent));
  
  int32_t servent_basic_type_id = env->basic_type_id(env, "SPVM::servent");
  assert(servent_basic_type_id >= 0);
  void* obj_sent = env->new_pointer(env, servent_basic_type_id, sent);
  
  stack[0].oval = obj_sent;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__servent__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_sent = stack[0].oval;
  
  struct servent* sent = env->pointer(env, obj_sent);
  
  env->free_memory_block(env, sent);
  
  return SPVM_SUCCESS;
}
