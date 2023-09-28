#include <stdlib.h>
#include <string.h>

#include <spvm_native.h>

struct TestCase__Pointer {
  int32_t x;
};

static const char* FILE_NAME = "TestCase/Pointer.c";

int32_t SPVM__TestCase__Pointer__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t x = stack[0].ival;
  
  struct TestCase__Pointer* pointer = env->new_memory_block(env, stack, sizeof(struct TestCase__Pointer));
  
  pointer->x = x;
  
  int32_t e;
  void* struct_object = env->new_pointer_object_by_name(env, stack, "TestCase::Pointer", pointer, &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].oval = struct_object;
  
  return 0;
}

int32_t SPVM__TestCase__Pointer__get_x(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* self = stack[0].oval;
  
  struct TestCase__Pointer* pointer = (struct TestCase__Pointer*)env->get_pointer(env, stack, self);
  
  stack[0].ival = pointer->x;
  
  return 0;
}

int32_t SPVM__TestCase__Pointer__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* self = stack[0].oval;
  
  struct TestCase__Pointer* pointer = (struct TestCase__Pointer*)env->get_pointer(env, stack, self);
  
  env->free_memory_block(env, stack, pointer);
  
  return 0;
}
