#ifndef SPVM_RUNTIME_H
#define SPVM_RUNTIME_H

#include "spvm_base.h"
#include "spvm_native.h"

struct SPVM_runtime {
  // Package variables
  SPVM_VALUE* package_vars_heap;
  
  // Memory blocks count
  int32_t memory_blocks_count;
  
  SPVM_COMPILER* compiler;
};

#endif
