#ifndef SPVM_LIMIT_H
#define SPVM_LIMIT_H

#include "spvm_base.h"

enum {
  /* Fields count limit */
  SPVM_LIMIT_C_FIELDS = INT32_MAX,

  /* Fields count our */
  SPVM_LIMIT_C_OURS = INT32_MAX,
  
  /* Lexical variables count limit */
  SPVM_LIMIT_C_MY_VARS = INT32_MAX,

  /* Subroutines count limit */
  SPVM_LIMIT_C_SUBS = INT32_MAX,
  
  /* Resolved types count limit */
  SPVM_LIMIT_C_RESOLVED_TYPES = INT32_MAX, 

  /* Types count limit */
  SPVM_LIMIT_C_TYPES = INT32_MAX, 
  
  /* Case statements count limit */
  SPVM_LIMIT_C_CASES = INT32_MAX,
};

#endif
