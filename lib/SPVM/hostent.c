#include "spvm_native.h"

#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <netdb.h>

int32_t SPNATIVE__SPVM__hostent__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  struct hostent* hent = env->alloc_memory_block_zero(env, sizeof(struct hostent));
  
  int32_t hostent_basic_type_id = env->basic_type_id(env, "SPVM::hostent");
  assert(hostent_basic_type_id >= 0);
  void* obj_hent = env->new_pointer(env, hostent_basic_type_id, hent);
  
  stack[0].oval = obj_hent;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__hostent__h_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_hent = stack[0].oval;
  
  struct hostent* hent = (struct hostent*)env->pointer(env, obj_hent);
  
  const char* h_name = hent->h_name;
  
  void* obj_h_name;
  if (h_name == NULL) {
    obj_h_name = NULL;
  }
  else {
    int32_t len = strlen(h_name);
    void* obj_h_name = env->new_str_len(env, h_name, len);
  }
  
  int32_t hostent_basic_type_id = env->basic_type_id(env, "SPVM::hostent");
  assert(hostent_basic_type_id >= 0);
  void* new_obj_hent = env->new_pointer(env, hostent_basic_type_id, hent);
  
  stack[0].oval = new_obj_hent;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__hostent__set_h_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  void* obj_hent = stack[0].oval;
  
  int8_t h_name = stack[1].bval;
  
  struct hostent* hent = (struct hostent*)env->pointer(env, obj_hent);
  
  hent->h_name = h_name;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__hostent__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_hent = stack[0].oval;
  
  struct hostent* hent = env->pointer(env, obj_hent);
  
  env->free_memory_block(env, hent);
  
  return SPVM_SUCCESS;
}
