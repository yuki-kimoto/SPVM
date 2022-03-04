#ifndef SPVM_RUNTIME_INFO_H
#define SPVM_RUNTIME_INFO_H

#include "spvm_typedecl.h"

struct spvm_runtime_info {
  SPVM_LIST* basic_types;
  SPVM_HASH* basic_type_symtable;
  SPVM_LIST* types;
  SPVM_LIST* classes;
  SPVM_HASH* class_symtable;
  SPVM_LIST* switch_infos;
  const char** strings;
};

#endif
