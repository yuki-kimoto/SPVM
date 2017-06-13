#ifndef SPVM_TYPE_H
#define SPVM_TYPE_H

#include <stdio.h>

#include "spvm_base.h"

enum {
  SPVM_TYPE_C_CODE_NAME,
  SPVM_TYPE_C_CODE_ARRAY,
};

extern const char* const SPVM_TYPE_C_CODE_NAMES[];

struct SPVM_type {
  SPVM_RESOLVED_TYPE* resolved_type;
  union {
    SPVM_TYPE_COMPONENT_NAME* type_component_name;
    SPVM_TYPE_COMPONENT_ARRAY* type_component_array;
  } uv;
  int32_t code;
};


SPVM_TYPE* SPVM_TYPE_new(SPVM_PARSER* parser);
void SPVM_TYPE_build_parts(SPVM_PARSER* parser, SPVM_TYPE* type, SPVM_ARRAY* parts);
_Bool SPVM_TYPE_resolve_type(SPVM_PARSER* parser, SPVM_OP* op_type, int32_t name_length);

#endif
