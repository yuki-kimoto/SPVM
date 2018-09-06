#ifndef SPVM_RUNTIME_INFO_CASE_INFO_H
#define SPVM_RUNTIME_INFO_CASE_INFO_H

#include "spvm_base.h"

// Field information
struct SPVM_runtime_info_case_info {
  int32_t match;
  int32_t opcode_rel_index;
};

SPVM_RUNTIME_INFO_CASE_INFO* SPVM_RUNTIME_INFO_CASE_INFO_new();

#endif
