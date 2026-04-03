// Copyright (c) 2024 Yuki Kimoto
// MIT License

#include "spvm_native.h"

static const char* FILE_NAME = "Native/Constant.c";

/*
  This empty boot function is required for Windows compatibility.
  It prevents linker errors when no native functions are defined,
  as ExtUtils::CBuilder expects this symbol for DLL export.
*/
void boot_Native__Constant(void) {}
