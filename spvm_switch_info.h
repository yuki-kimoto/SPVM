#ifndef SPVM_SWITCH_INFO_H
#define SPVM_SWITCH_INFO_H

#include "spvm_base.h"

enum {
  SPVM_SWITCH_INFO_C_CODE_TABLE_SWITCH,
  SPVM_SWITCH_INFO_C_CODE_LOOKUP_SWITCH,
};

// Parser information
struct SPVM_switch_info {
  SPVM_DYNAMIC_ARRAY* op_cases;
  SPVM_OP* op_default;
  int32_t max;
  int32_t min;
  int32_t code;
  int32_t bytecode_index;
  int32_t default_bytecode_index;
};

SPVM_SWITCH_INFO* SPVM_SWITCH_INFO_new(SPVM_COMPILER* compiler);

#endif
