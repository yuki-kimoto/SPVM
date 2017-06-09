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

SPVM* SPVM_new();
void SPVM_run(SPVM* spvm, const char* package_name);
void SPVM_free(SPVM* spvm);

#endif
