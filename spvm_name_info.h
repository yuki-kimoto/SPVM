#ifndef SPVM_NAME_INFO_H
#define SPVM_NAME_INFO_H

#include "spvm_base.h"

enum {
  SPVM_NAME_INFO_C_CODE_VARBASENAME,
  SPVM_NAME_INFO_C_CODE_BASENAME,
  SPVM_NAME_INFO_C_CODE_ABSNAME,
};

struct SPVM_name_info {
  SPVM_OP* op_var;
  SPVM_OP* op_name;
  const char* resolved_name;
  int32_t code;
  int32_t constant_pool_address;
};

SPVM_NAME_INFO* SPVM_NAME_INFO_new(SPVM* spvm);

#endif
