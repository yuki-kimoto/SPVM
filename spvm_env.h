#ifndef SPVM_ENV_H
#define SPVM_ENV_H

#include <stdint.h>

struct SPVM_env {
  void* runtime;
  int32_t (*get_array_length)(void*, void*, void*);
};

#endif
