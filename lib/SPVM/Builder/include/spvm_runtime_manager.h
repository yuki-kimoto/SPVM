#ifndef SPVM_RUNTIME_MANAGER_H
#define SPVM_RUNTIME_MANAGER_H

#include "spvm_typedecl.h"

// Parser information
struct spvm_runtime_manager {
  // This is all memory blocks count allocated by the SPVM.
  int32_t memory_blocks_count;
};

#endif
