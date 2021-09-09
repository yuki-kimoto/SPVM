#include <stdlib.h>
#include <string.h>

#include <spvm_native.h>

struct SPVM__TestCase__Pointer {
  int32_t x;
};

int32_t SPNATIVE__SPVM__TestCase__Pointer__new(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  
  int32_t x = args[0].ival;
  
  struct SPVM__TestCase__Pointer* pointer = malloc(sizeof(struct SPVM__TestCase__Pointer));
  
  pointer->x = x;
  
  int32_t basic_type_id = env->get_basic_type_id(env, "TestCase::Pointer");
  
  void* struct_object = env->new_pointer_raw(env, basic_type_id, pointer);
  
  args[0].oval = struct_object;
  
  return 0;
}

int32_t SPNATIVE__SPVM__TestCase__Pointer__get_x(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  void* self = args[0].oval;
  
  
  struct SPVM__TestCase__Pointer* pointer = (struct SPVM__TestCase__Pointer*)env->get_pointer(env, self);
  
  args[0].ival = pointer->x;
  
  return 0;
}

int32_t SPNATIVE__SPVM__TestCase__Pointer__DESTROY(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  void* self = args[0].oval;
  
  struct SPVM__TestCase__Pointer* pointer = (struct SPVM__TestCase__Pointer*)env->get_pointer(env, self);
  
  free(pointer);
  
  return 0;
}
