// Copyright (c) 2025 [--user-name]
// MIT License

#include "spvm_native.h"



static const char* FILE_NAME = "TestCase/NativeAPI.c";

int32_t SPVM__TestCase__NativeAPI__sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t x = stack[0].ival;
  
  int32_t y = stack[1].ival;
  
  int32_t ret = x + y;
  
  stack[0].ival = ret;
  
  return 0;
}
