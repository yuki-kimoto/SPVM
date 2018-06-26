#include <stdlib.h>
#include <string.h>

#include <spvm_native.h>

struct TestCase__Struct {
  int32_t x;
};

int32_t SPVM_NATIVE_SUB(TestCase__Struct__new) (SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  
  int32_t x = args[0].ival;
  
  struct TestCase__Struct* struct_ptr = malloc(sizeof(struct TestCase__Struct));
  
  struct_ptr->x = x;
  
  int32_t basic_type_id = env->get_basic_type_id(env, "TestCase::Struct");
  
  void* struct_object = env->new_struct_raw(env, basic_type_id, struct_ptr);
  
  args[0].oval = struct_object;
  
  return 0;
}

int32_t SPVM_NATIVE_SUB(TestCase__Struct__get_x) (SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  void* self = args[0].oval;
  
  
  struct TestCase__Struct* struct_ptr = (struct TestCase__Struct*)env->get_struct(env, self);
  
  args[0].ival = struct_ptr->x;
  
  return 0;
}

int32_t SPVM_NATIVE_SUB(TestCase__Struct__DESTROY) (SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  void* self = args[0].oval;
  
  struct TestCase__Struct* struct_ptr = (struct TestCase__Struct*)env->get_struct(env, self);
  
  free(struct_ptr);
  
  return 0;
}
