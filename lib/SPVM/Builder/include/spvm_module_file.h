// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_MODULE_FILE_H
#define SPVM_MODULE_FILE_H

#include "spvm_typedecl.h"

struct spvm_module_file {
  const char* module_name;
  const char* module_file;
  const char* module_rel_file;
  const char* module_dir;
  const char* content;
  const char* content_length;
};

SPVM_MODULE_FILE* SPVM_MODULE_FILE_new(SPVM_COMPILER* compiler);

#endif
