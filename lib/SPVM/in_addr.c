#include "spvm_native.h"

#include <assert.h>
#include <stdlib.h>
#include <netinet/in.h>

int32_t SPNATIVE__SPVM__in_addr__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  struct in_addr* ina = malloc(sizeof(struct in_addr));
  
  int32_t in_addr_basic_type_id = env->basic_type_id(env, "SPVM::in_addr");
  assert(in_addr_basic_type_id >= 0);
  void* obj_ina = env->new_pointer(env, in_addr_basic_type_id, ina);
  
  stack[0].oval = obj_ina;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__in_addr__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_ina = stack[0].oval;
  
  struct in_addr* ina = env->pointer(env, obj_ina);
  
  free(ina);
  
  return SPVM_SUCCESS;
}
