#ifndef SPVM_HASH_ENTRY_H
#define SPVM_HASH_ENTRY_H

#include "spvm_typedef.h"

// Hash entry
struct SPVM_hash_entry {
  void* value;
  int32_t next_index;
  int32_t key_index;
};

#endif
