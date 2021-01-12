#ifndef SPVM_SOURCE_H
#define SPVM_SOURCE_H

#include "spvm_base.h"

struct SPVM_source {
  const char* content;
  const char* file;
  const char* rel_file;
  const char* rel_file_package_name;
};

SPVM_SOURCE* SPVM_SOURCE_new(SPVM_COMPILER* compiler);

#endif
