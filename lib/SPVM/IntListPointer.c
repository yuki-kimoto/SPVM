#include "spvm_native.h"

static const char* MFILE = "SPVM/IntListPointer.c";

int32_t SPNATIVE__SPVM__IntListPointer__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void** pointer = (void**)env->alloc_memory_block_zero(env, sizeof(void*) * 3);
  
  int32_t capacity = 16;
  int32_t* values = env->alloc_memory_block_zero(env, sizeof(int32_t) * capacity);
  int32_t length = 0;
  
  pointer[0] = values;
  pointer[1] = (void*)(intptr_t)capacity;
  pointer[2] = (void*)(intptr_t)length;

  void* obj_intlistpointer = SPVM_POINTER(env, "SPVM::IntListPointer", pointer, MFILE, __LINE__);
  
  stack[0].oval = obj_intlistpointer;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IntListPointer__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_intlistpointer = stack[0].oval;
  
  void** pointer = (void**)env->pointer(env, obj_intlist_pointer);
  
  int32_t* values = (int32_t*)pointer[0];
  
  env->free_memory_block(env, values);
  
  env->free_memory_block(env, pointer);
  
  return SPVM_SUCCESS;
}
