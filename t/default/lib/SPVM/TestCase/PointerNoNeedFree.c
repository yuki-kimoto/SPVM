#include <stdlib.h>
#include <string.h>

#include <spvm_native.h>

struct TestCase__PointerNoNeedFree {
  int32_t x;
};

int32_t SPVM__TestCase__PointerNoNeedFree__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t x = stack[0].ival;
  
  struct TestCase__PointerNoNeedFree* pointer = env->alloc_memory_block_zero(env, sizeof(struct TestCase__PointerNoNeedFree));
  
  pointer->x = x;
  
  int32_t e;
  void* struct_object = env->new_pointer_by_name(env, stack, "TestCase::PointerNoNeedFree", pointer, &e, "TestCase/PointerNoNeedFree.c", __LINE__);
  if (e) { return e; }
  
  stack[0].oval = struct_object;
  
  return 0;
}

int32_t SPVM__TestCase__PointerNoNeedFree__get_x(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* self = stack[0].oval;
  
  struct TestCase__PointerNoNeedFree* pointer = (struct TestCase__PointerNoNeedFree*)env->get_pointer(env, stack, self);
  
  stack[0].ival = pointer->x;
  
  return 0;
}

int32_t SPVM__TestCase__PointerNoNeedFree__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* obj_self = stack[0].oval;
  
  if (!env->get_pointer_no_need_free(env, stack, obj_self)) {
    struct TestCase__PointerNoNeedFree* pointer = (struct TestCase__PointerNoNeedFree*)env->get_pointer(env, stack, obj_self);
    env->free_memory_block(env, pointer);
  }
  
  return 0;
}
