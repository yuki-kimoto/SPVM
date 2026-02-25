#include <spvm_native.h>

#include <iostream>
#include <sstream>
#include <thread>
#include <stdexcept>
#include <functional>

extern "C" {

void ThreadFunc(int32_t& num) {
  num += 1;
}

int32_t SPVM__TestCase__NativeAPICpp__call_cpp_func(SPVM_ENV* env, SPVM_VALUE* stack) {

  int32_t value = stack[0].ival;

  value *= 2;

  try {
    throw std::runtime_error("Dummy Error");
  }
  catch (const std::runtime_error& e) {
    value += 2;
  }

  std::thread th1(ThreadFunc, std::ref(value));
  th1.join();

  stack[0].ival = value;

  return 0;
}
}