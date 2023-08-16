// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_API_CLASS_FILE_H
#define SPVM_API_CLASS_FILE_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_API_CLASS_FILE* SPVM_API_CLASS_FILE_new_api(void);

void SPVM_API_CLASS_FILE_free_api(SPVM_API_CLASS_FILE* api);

SPVM_CLASS_FILE* SPVM_CLASS_FILE_clone(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file);

const char* SPVM_API_CLASS_FILE_get_class_name(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file);

const char* SPVM_API_CLASS_FILE_get_file(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file);

void SPVM_API_CLASS_FILE_set_file(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file, const char* file);

const char* SPVM_API_CLASS_FILE_get_dir(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file);

void SPVM_API_CLASS_FILE_set_dir(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file, const char* dir);

const char* SPVM_API_CLASS_FILE_get_rel_file(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file);  

void SPVM_API_CLASS_FILE_set_rel_file(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file, const char* rel_file);

const char* SPVM_API_CLASS_FILE_get_content(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file);  

void SPVM_API_CLASS_FILE_set_content(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file, const char* content);

int32_t SPVM_API_CLASS_FILE_get_content_length(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file);  

void SPVM_API_CLASS_FILE_set_content_length(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file, int32_t content_length);

#endif
