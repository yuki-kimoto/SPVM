#ifndef SPVM_RUNTIME_INFO_SWITCH_INFO_H
#define SPVM_RUNTIME_INFO_SWITCH_INFO_H

#include "spvm_base.h"

// Field information
struct SPVM_runtime_info_switch_info {
  int32_t default_opcode_rel_index;
  SPVM_LIST* case_infos;
};

SPVM_RUNTIME_INFO_SWITCH_INFO* SPVM_RUNTIME_INFO_SWITCH_INFO_new();

#endif
