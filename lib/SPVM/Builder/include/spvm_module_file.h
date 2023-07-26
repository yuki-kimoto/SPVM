// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_MODULE_FILE_H
#define SPVM_MODULE_FILE_H

#include "spvm_typedecl.h"

struct spvm_module_file {
  const char* module_name;
  const char* file;
  const char* dir;
  const char* rel_file;
  const char* content;
  int32_t content_length;
};

SPVM_MODULE_FILE* SPVM_MODULE_FILE_new(SPVM_COMPILER* compiler);

SPVM_MODULE_FILE* SPVM_MODULE_FILE_new_v2(SPVM_COMPILER* compiler, const char* module_name);

SPVM_MODULE_FILE* SPVM_MODULE_FILE_free_v2(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file);

const char* SPVM_MODULE_FILE_get_module_name(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file);

void SPVM_MODULE_FILE_set_module_name(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file, const char* module_name);

const char* SPVM_MODULE_FILE_get_file(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file);

void SPVM_MODULE_FILE_set_file(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file, const char* file);

const char* SPVM_MODULE_FILE_get_dir(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file);

void SPVM_MODULE_FILE_set_dir(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file, const char* dir);

const char* SPVM_MODULE_FILE_get_rel_file(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file);

void SPVM_MODULE_FILE_set_rel_file(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file, const char* rel_file);

const char* SPVM_MODULE_FILE_get_content(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file);

void SPVM_MODULE_FILE_set_content(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file, const char* content);

int32_t SPVM_MODULE_FILE_get_content_length(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file);

void SPVM_MODULE_FILE_set_content_length(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file, int32_t content_length);

#endif
