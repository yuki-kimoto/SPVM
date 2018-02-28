#ifndef SPVM_ON_STACK_REPLACEMENT_H
#define SPVM_ON_STACK_REPLACEMENT_H

#include "spvm_base.h"

struct SPVM_on_stack_replacement {
  int32_t jump_opcode_index;
};

SPVM_ON_STACK_REPLACEMENT* SPVM_ON_STACK_REPLACEMENT_new();

#endif
