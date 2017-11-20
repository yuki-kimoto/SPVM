#ifndef SPVM_OUR_H
#define SPVM_OUR_H

#include "spvm_base.h"

// Field information
struct SPVM_our {
  SPVM_OP* op_package;
  SPVM_OP* op_package_var;
  SPVM_OP* op_type;
  int32_t id;
};

SPVM_OUR* SPVM_OUR_new(SPVM_COMPILER* compiler);

#endif
