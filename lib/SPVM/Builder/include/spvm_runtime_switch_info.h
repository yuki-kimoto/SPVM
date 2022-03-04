#ifndef SPVM_RUNTIME_SWITCH_INFO_H
#define SPVM_RUNTIME_SWITCH_INFO_H

#include "spvm_typedecl.h"

// Parser information
struct spvm_runtime_switch_info {
  SPVM_LIST* case_infos;
  int32_t id;
  int32_t default_opcode_rel_index;
  int32_t switch_id;
};

#endif
