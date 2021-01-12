#ifndef SPVM_MODULE_SOURCE_H
#define SPVM_MODULE_SOURCE_H

#include "spvm_base.h"

struct SPVM_module_source {
  char* content;
  char* content_size;
  char* file;
  char* rel_file;
  char* rel_file_package_name;
};

SPVM_MODULE_SOURCE* SPVM_MODULE_SOURCE_new(SPVM_COMPILER* compiler);

#endif
