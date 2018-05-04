#ifndef SPVM_ARRAY_INIT_H
#define SPVM_ARRAY_INIT_H

#include "spvm_base.h"

struct SPVM_array_init {
  SPVM_OP* op_list_indexes;
  SPVM_OP* op_list_elements;
};

SPVM_ARRAY_INIT* SPVM_ARRAY_INIT_new();

#endif
