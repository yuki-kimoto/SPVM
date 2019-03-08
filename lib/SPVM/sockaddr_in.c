#include "spvm_native.h"

#include <assert.h>
#include <stdlib.h>
#include <netinet/in.h>

int32_t SPNATIVE__SPVM__sockaddr_in__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  struct sockaddr_in* sin = env->alloc_memory_block_zero(env, sizeof(struct sockaddr_in));
  
  int32_t sockaddr_in_basic_type_id = env->basic_type_id(env, "SPVM::sockaddr_in");
  assert(sockaddr_in_basic_type_id >= 0);
  void* obj_sin = env->new_pointer(env, sockaddr_in_basic_type_id, sin);
  
  stack[0].oval = obj_sin;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__sockaddr_in__set_sin_family(SPVM_ENV* env, SPVM_VALUE* stack) {
  void* obj_sin = stack[0].oval;
  
  int8_t sin_family = stack[1].bval;
  
  struct sockaddr_in* sin = (struct sockaddr_in*)env->pointer(env, obj_sin);
  
  sin->sin_family = sin_family;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__sockaddr_in__sin_family(SPVM_ENV* env, SPVM_VALUE* stack) {
  void* obj_sin = stack[0].oval;
  
  struct sockaddr_in* sin = env->pointer(env, obj_sin);
  
  int8_t sin_family = sin->sin_family;
  
  stack[0].bval = sin_family;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__sockaddr_in__set_sin_port(SPVM_ENV* env, SPVM_VALUE* stack) {
  void* obj_sin = stack[0].oval;
  
  int16_t sin_port = stack[1].sval;
  
  struct sockaddr_in* sin = env->pointer(env, obj_sin);
  
  sin->sin_port = sin_port;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__sockaddr_in__sin_port(SPVM_ENV* env, SPVM_VALUE* stack) {
  void* obj_sin = stack[0].oval;
  
  struct sockaddr_in* sin = env->pointer(env, obj_sin);
  
  int16_t sin_port = sin->sin_port;
  
  stack[0].sval = sin_port;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__sockaddr_in__set_sin_addr(SPVM_ENV* env, SPVM_VALUE* stack) {
  void* obj_sin = stack[0].oval;
  
  int32_t sin_addr = stack[1].ival;
  
  struct sockaddr_in* sin = env->pointer(env, obj_sin);
  
  sin->sin_addr.s_addr = sin_addr;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__sockaddr_in__sin_addr(SPVM_ENV* env, SPVM_VALUE* stack) {
  void* obj_sin = stack[0].oval;
  
  struct sockaddr_in* sin = env->pointer(env, obj_sin);
  
  stack[0].ival = sin->sin_addr.s_addr;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__sockaddr_in__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_sin = stack[0].oval;
  
  struct sockaddr_in* sin = env->pointer(env, obj_sin);
  
  env->free_memory_block(env, sin);
  
  return SPVM_SUCCESS;
}
