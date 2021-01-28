#ifndef SPVM_CASE_INFO_H
#define SPVM_CASE_INFO_H

#include "spvm_typedef.h"

struct spvm_case_info {
  SPVM_OP* op_case_info;
  SPVM_CONSTANT* constant;
  int32_t opcode_rel_index;
  int32_t index;
  int32_t is_default;
};

SPVM_CASE_INFO* SPVM_CASE_INFO_new();

#endif
