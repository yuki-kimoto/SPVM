#ifndef SPVM_SWITCH_INFO_H
#define SPVM_SWITCH_INFO_H

#include "spvm_typedecl.h"

enum {
  SPVM_SWITCH_INFO_C_ID_TABLE_SWITCH,
  SPVM_SWITCH_INFO_C_ID_LOOKUP_SWITCH,
};

// Parser information
struct spvm_switch_info {
  SPVM_LIST* case_infos;
  SPVM_OP* op_default;
  int32_t id;
  int32_t default_opcode_rel_index;
  int32_t switch_id;
  int32_t opcode_id;
};

SPVM_SWITCH_INFO* SPVM_SWITCH_INFO_new(SPVM_COMPILER* compiler);

#endif
