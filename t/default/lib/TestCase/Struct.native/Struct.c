#include <stdlib.h>
#include <string.h>

#include <spvm_native.h>

struct TestCase__Struct {
  int32_t x;
}

int32_t SPVM_NATIVE_SUB(TestCase__Struct__new) (SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  int32_t x = args[0].ival;
  
  void* struct_ptr = malloc(sizeof(strcut TestCase__Struct));
  
  int32_t basic_type_id = env->get_basic_type_id(env, "TestCase::Struct");
  
  SPVM_API_object* struct_object = api->new_struct(env, basic_type_id, struct_ptr);
  
  args[0].oval = struct_object;
  
  return 0;
}

int32_t SPVM_NATIVE_SUB(TestCase__Struct__get_x) (SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  SPVM_API_object* self = args[0].oval;
  
  return 0;
}

