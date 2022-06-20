#include <stdlib.h>
#include <string.h>

#include <spvm_native.h>

struct TestCase__Pointer {
  int32_t x;
};

int32_t SPVM__TestCase__Pointer__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t x = stack[0].ival;
  
  struct TestCase__Pointer* pointer = env->alloc_memory_block_zero(env, sizeof(struct TestCase__Pointer));
  
  pointer->x = x;
  
  int32_t e;
  void* struct_object = env->new_pointer_by_name(env, "TestCase::Pointer", pointer, &e, "TestCase/Pointer.c", __LINE__);
  if (e) { return e; }
  
  stack[0].oval = struct_object;
  
  return 0;
}

int32_t SPVM__TestCase__Pointer__get_x(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* self = stack[0].oval;
  
  struct TestCase__Pointer* pointer = (struct TestCase__Pointer*)env->get_pointer(env, self);
  
  stack[0].ival = pointer->x;
  
  return 0;
}

int32_t SPVM__TestCase__Pointer__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* self = stack[0].oval;
  
  struct TestCase__Pointer* pointer = (struct TestCase__Pointer*)env->get_pointer(env, self);
  
  env->free_memory_block(env, pointer);
  
  return 0;
}
