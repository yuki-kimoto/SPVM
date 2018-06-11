#ifndef SPVM_CSOURCE_BUILDER_H
#define SPVM_CSOURCE_BUILDER_H
#include <spvm_native.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <math.h>
#define SPVM_RUNTIME_C_INLINE_GET_REF_COUNT(object) ((*(int32_t*)((intptr_t)object + (intptr_t)env->object_ref_count_byte_offset)))
#define SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(object) ((*(int32_t*)((intptr_t)object + (intptr_t)env->object_ref_count_byte_offset))++)
#define SPVM_RUNTIME_C_INLINE_INC_REF_COUNT(object)\
do {\
  if (object != NULL) {\
    SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(object);\
  }\
} while (0)\

#define SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(object) ((*(int32_t*)((intptr_t)object + (intptr_t)env->object_ref_count_byte_offset))--)
#define SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT(object)\
do {\
  if (object != NULL) {\
    if (SPVM_RUNTIME_C_INLINE_GET_REF_COUNT(object) > 1) { SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(object); }\
    else { env->dec_ref_count(env, object); }\
  }\
} while (0)\

#define SPVM_RUNTIME_C_INLINE_ISWEAK(object) ((intptr_t)object & 1)

#define SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(dist_ptr, source) \
do {\
  void* tmp_object = source;\
  if (tmp_object != NULL) {\
    SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(tmp_object);\
  }\
  if (*(void**)(dist_ptr) != NULL) {\
    if (SPVM_RUNTIME_C_INLINE_ISWEAK(*(void**)(dist_ptr))) { env->unweaken(env, dist_ptr); }\
    if (SPVM_RUNTIME_C_INLINE_GET_REF_COUNT(*(void**)(dist_ptr)) > 1) { SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(*(void**)(dist_ptr)); }\
    else { env->dec_ref_count(env, *(void**)(dist_ptr)); }\
  }\
  *(void**)(dist_ptr) = tmp_object;\
} while (0)\

#endif
// Function Declarations
int32_t SPVM_PRECOMPILE_SPVM__Example__sum(SPVM_ENV* env, SPVM_VALUE* args);

// Function Implementations
int32_t SPVM_PRECOMPILE_SPVM__Example__sum(SPVM_ENV* env, SPVM_VALUE* args) {
  SPVM_VALUE vars[5];
  int32_t call_sub_arg_stack_top = -1;
  register int32_t condition_flag;
  char tmp_string[30];
  int32_t exception_flag = 0;
  *(SPVM_VALUE_int*)&vars[1] = 0;
  *(SPVM_VALUE_int*)&vars[2] = 0;
  *(SPVM_VALUE_int*)&vars[3] = 0;
  *(SPVM_VALUE_int*)&vars[4] = 0;

  *(void**)&vars[0] = *(void**)&args[0];
  if (*(void**)&vars[0] != NULL) { SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(*(void**)&vars[0]); }

  if (!exception_flag) {
    env->set_exception(env, NULL);
  }
  return exception_flag;
}


