#include <spvm_native.h>

#include <iostream>
#include <sstream>
#include <thread>

extern "C" {

void ThreadFunc(int num) {
  
}

int32_t SPVM__TestCase__NativeAPICpp__call_cpp_func(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t value = stack[0].ival;
  
  value *= 2;
  
  std::thread th1(ThreadFunc, 1);
  th1.join();
  
  stack[0].ival = value;
  
  return 0;
}

}
