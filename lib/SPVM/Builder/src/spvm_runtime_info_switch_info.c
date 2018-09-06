#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "spvm_runtime_info_switch_info.h"
#include "spvm_util_allocator.h"

SPVM_RUNTIME_INFO_SWITCH_INFO* SPVM_RUNTIME_INFO_SWITCH_INFO_new() {
  SPVM_RUNTIME_INFO_SWITCH_INFO* runtime_info_switch_info = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_RUNTIME_INFO_SWITCH_INFO));
  
  return runtime_info_switch_info;
}
