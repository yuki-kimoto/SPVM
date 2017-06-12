#ifndef SPVM_TYPE_COMPONENT_ARRAY_H
#define SPVM_TYPE_COMPONENT_ARRAY_H

#include "spvm_base.h"

struct SPVM_type_component_array {
  SPVM_TYPE* type;
  SPVM_OP* op_term;
};

SPVM_TYPE_COMPONENT_ARRAY* SPVM_TYPE_COMPONENT_ARRAY_new(SPVM_* spvm);

#endif
