#ifndef SPVM_SUB_CHECK_INFO_H
#define SPVM_SUB_CHECK_INFO_H

#include "spvm_base.h"

// Field information
struct SPVM_sub_check_info {
  SPVM_OP* op_type;
  SPVM_OP* op_name;
  const char* abs_name;
  int32_t id;
  int32_t index;
};

#endif
