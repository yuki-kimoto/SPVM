#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "spvm_portable.h"
#include "spvm_util_allocator.h"

SPVM_PORTABLE* SPVM_PORTABLE_new() {
  SPVM_PORTABLE* portable = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_PORTABLE));
  
  return portable;
}
