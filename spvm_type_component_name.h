#ifndef SPVM_TYPE_COMPONENT_NAME_H
#define SPVM_TYPE_COMPONENT_NAME_H

#include "spvm_base.h"

struct SPVM_type_component_name {
  SPVM_OP* op_name;
};

SPVM_TYPE_COMPONENT_NAME* SPVM_TYPE_COMPONENT_NAME_new(SPVM* spvm);

#endif
