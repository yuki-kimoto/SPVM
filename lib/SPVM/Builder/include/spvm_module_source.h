#ifndef SPVM_MODULE_SOURCE_H
#define SPVM_MODULE_SOURCE_H

#include "spvm_base.h"

struct SPVM_module_source {
  char* content;
  char* file;
  char* rel_file;
  char* rel_file_package_name;
  int32_t content_size;
};

SPVM_MODULE_SOURCE* SPVM_MODULE_SOURCE_new(SPVM_COMPILER* compiler);

#endif
