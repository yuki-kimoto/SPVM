#ifndef SPVM_CASE_INFO_H
#define SPVM_CASE_INFO_H

#include "spvm_base.h"

struct SPVM_case_info {
  SPVM_OP* op_term;
  SPVM_OP* op_constant;
  int32_t goto_opcode_rel_index;
};

SPVM_CASE_INFO* SPVM_CASE_INFO_new();

#endif
