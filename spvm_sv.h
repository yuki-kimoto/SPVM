#ifndef SPVM_SV_H
#define SPVM_SV_H

#include "spvm_base.h"

// Field information
struct SPVM_sv {
  char* buffer;
  int64_t ref_count;
  int64_t length;
};

SPVM_SV* SPVM_SV_new_pvn(SPVM* spvm, const char* pv, size_t length);

#endif
