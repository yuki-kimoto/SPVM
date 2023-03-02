#include <spvm_native.h>

#include "mylib.hpp"

#include <sstream>

extern "C" {

int32_t SPVM__TestCase__NativeAPICpp__call_cpp_func(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t value = stack[0].ival;
  
  value *= 2;
  
  std::ostringstream str_stream;
  
  str_stream << "abc";
  
  stack[0].ival = value;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPICpp__call_native_func(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t value = stack[0].ival;
  
  value = Foo::mul3((int)value);

  spvm_warn("Foo %s %d", "aaa", 3);
  spvm_warn("Foo");
  
  const char* func_name = __func__;

  stack[0].ival = value;
  
  return 0;
}

}
