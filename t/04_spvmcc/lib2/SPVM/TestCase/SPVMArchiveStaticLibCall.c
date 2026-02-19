#include "spvm_native.h"

#include "spvmcc_archive_test.h"

static const char* FILE_NAME = "TestCase/SPVMArchiveStaticLibCall.c";

int32_t SPVM__TestCase__SPVMArchiveStaticLibCall__spvmcc_archive_test_foo(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t ret = spvmcc_archive_test_foo();
  
  stack[0].ival = ret;
  
  return 0;
}
