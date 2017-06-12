#ifndef SPVM_H
#define SPVM_H

#include <stdio.h>

#include "spvm_base.h"

// Parser information
struct spvm_ {
  
  // Parser
  SPVM_PARSER* parser;
  
  // Runtime
  SPVM_RUNTIME* runtime;
};

SPVM_* SPVM_new();
void SPVM_run(SPVM_* spvm, const char* package_name);
void SPVM_free(SPVM_* spvm);

#endif
