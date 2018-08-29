#ifndef SPVM_CONSTANT_H
#define SPVM_CONSTANT_H

#include "spvm_base.h"
#include "spvm_native.h"

struct SPVM_constant {
  SPVM_OP* op_constant;
  SPVM_TYPE* type;
  SPVM_VALUE value;
  int32_t string_length;
  int32_t id;
  int32_t sub_rel_id;
  int32_t sub_rel_info_long_id;
  int32_t sub_rel_info_double_id;
  int32_t sub_rel_info_string_id;
  int32_t long_constant_id;
  int32_t double_constant_id;
  int32_t string_constant_id;
};

SPVM_CONSTANT* SPVM_CONSTANT_new(SPVM_COMPILER* compiler);
SPVM_CONSTANT* SPVM_CONSTANT_create_int_1(SPVM_COMPILER* compiler);

#endif
