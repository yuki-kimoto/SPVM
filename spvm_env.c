#include <assert.h>

#include "spvm.h"
#include "spvm_env.h"
#include "spvm_allocator_util.h"
#include "spvm_value.h"

SPVM_ENV* SPVM_ENV_new(SPVM* spvm) {
  (void)spvm;
  
  SPVM_ENV* env = SPVM_ALLOCATOR_UTIL_safe_malloc_i32(1, sizeof(SPVM_ENV));
  
  env->call_stack_capacity = 0xFF;
  env->call_stack = SPVM_ALLOCATOR_UTIL_safe_malloc_i32(env->call_stack_capacity, sizeof(SPVM_VALUE));
  env->call_stack_base = -1;
  env->operand_stack_top = -1;
  env->abort = 0;
  
  return env;
}

void SPVM_ENV_free(SPVM* spvm, SPVM_ENV* env) {
  (void)spvm;
  
  // Free call stack
  free(env->call_stack);
  
  free(env);
}
