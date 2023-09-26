// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_WEAKEN_BACKREF_H
#define SPVM_WEAKEN_BACKREF_H

#include "spvm_typedecl.h"

struct spvm_weaken_backref {
  SPVM_OBJECT** ref;
  SPVM_WEAKEN_BACKREF* next;
};

#endif
