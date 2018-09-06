#ifndef SPVM_RUNTIME_INFO_STRING_INFO_H
#define SPVM_RUNTIME_INFO_STRING_INFO_H

#include "spvm_base.h"

// String information
struct SPVM_runtime_info_string_info {
  int32_t length;
  const char* string;
};

SPVM_RUNTIME_INFO_STRING_INFO* SPVM_RUNTIME_INFO_STRING_INFO_new();

#endif
