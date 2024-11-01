// Copyright (c) 2024 Yuki Kimoto
// MIT License

#include "spvm_native.h"



static const char* FILE_NAME = "TestCase/Module/Fn.c";

int32_t SPVM__TestCase__Module__Fn__set_no_free_true(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* object = stack[0].oval;
  
  env->set_no_free(env, stack, object, 1);
  
  return 0;
}


