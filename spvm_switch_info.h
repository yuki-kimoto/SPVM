#ifndef SPVM_SWITCH_INFO_H
#define SPVM_SWITCH_INFO_H

#include "spvm_base.h"

enum {
  SPVM_SWITCH_INFO_C_CODE_TABLE_SWITCH,
  SPVM_SWITCH_INFO_C_CODE_LOOKUP_SWITCH,
};

// Parser information
struct SPVM_switch_info {
  SPVM_OP* op_term_condition;
  SPVM_ARRAY* op_cases;
  int64_t max;
  int64_t min;
  int32_t code;
};

SPVM_SWITCH_INFO* SPVM_SWITCH_INFO_new(SPVM* spvm);

#endif
