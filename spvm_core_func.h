#ifndef SPVM_CORE_FUNC_H
#define SPVM_CORE_FUNC_H

#include "spvm_base.h"

int64_t SPVM_CORE_FUNC_time(SPVM_API* api, SPVM_API_VALUE* args);
void SPVM_CORE_FUNC_print(SPVM_API* api, SPVM_API_VALUE* args);
void SPVM_CORE_FUNC_warn(SPVM_API* api, SPVM_API_VALUE* args);

#endif
