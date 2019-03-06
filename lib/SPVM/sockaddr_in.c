#include "spvm_native.h"

#include <assert.h>
#include <stdlib.h>
#include <netinet/in.h>

int32_t SPNATIVE__SPVM__sockaddr_in__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  struct sockaddr_in* sin = malloc(sizeof(struct sockaddr_in));
  
  int32_t sockaddr_in_basic_type_id = env->basic_type_id(env, "SPVM::sockaddr_in");
  assert(sockaddr_in_basic_type_id >= 0);
  void* obj_sin = env->new_pointer(env, sockaddr_in_basic_type_id, sin);
  
  stack[0].oval = obj_sin;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__sockaddr_in__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_sin = stack[0].oval;
  
  struct sockaddr_in* sin = env->pointer(env, obj_sin);
  
  free(sin);
  
  return SPVM_SUCCESS;
}
