#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "spvm_runtime_field.h"
#include "spvm_util_allocator.h"

SPVM_RUNTIME_FIELD* SPVM_RUNTIME_FIELD_new() {
  SPVM_RUNTIME_FIELD* runtime_field = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_RUNTIME_FIELD));
  
  return runtime_field;
}
