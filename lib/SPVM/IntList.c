#include "spvm_native.h"

static const char* MFILE = "SPVM/IntList.c";

int32_t SPNATIVE__SPVM__IntList__length(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  void* obj_pointer;
  SPVM_OFIELD(env, obj_pointer, obj_self, "SPVM::IntList", "pointer", "SPVM::IntListPointer", MFILE, __LINE__);
  
  void** pointer = (void**)env->pointer(env, obj_pointer);
  
  int32_t length = (int32_t)(intptr_t)pointer[2];
  
  stack[0].ival = length;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IntList__push(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IntList__unshift(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IntList__shift(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IntList__set(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IntList__get(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IntList__to_array(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  
  return SPVM_SUCCESS;
}

