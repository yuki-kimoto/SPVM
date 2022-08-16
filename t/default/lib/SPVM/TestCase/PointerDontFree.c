#include <stdlib.h>
#include <string.h>

#include <spvm_native.h>

struct TestCase__PointerDontFree {
  int32_t x;
};

int32_t SPVM__TestCase__PointerDontFree__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t x = stack[0].ival;
  
  struct TestCase__PointerDontFree* pointer = env->alloc_memory_block_zero(env, sizeof(struct TestCase__PointerDontFree));
  
  pointer->x = x;
  
  int32_t e;
  void* struct_object = env->new_pointer_by_name(env, stack, "TestCase::PointerDontFree", pointer, &e, "TestCase/PointerDontFree.c", __LINE__);
  if (e) { return e; }
  
  stack[0].oval = struct_object;
  
  return 0;
}

int32_t SPVM__TestCase__PointerDontFree__get_x(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* self = stack[0].oval;
  
  struct TestCase__PointerDontFree* pointer = (struct TestCase__PointerDontFree*)env->get_pointer(env, stack, self);
  
  stack[0].ival = pointer->x;
  
  return 0;
}

int32_t SPVM__TestCase__PointerDontFree__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* obj_self = stack[0].oval;
  
  if (!env->check_flag_pointer_dont_free(env, stack, obj_self)) {
    struct TestCase__PointerDontFree* pointer = (struct TestCase__PointerDontFree*)env->get_pointer(env, stack, obj_self);
    env->free_memory_block(env, pointer);
  }
  
  return 0;
}
