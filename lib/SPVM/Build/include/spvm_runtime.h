#ifndef SPVM_RUNTIME_H
#define SPVM_RUNTIME_H

#include "spvm_base.h"
#include "spvm_native.h"

#define SPVM_RUNTIME_C_INLINE_GET_REF_COUNT(object) ((*(SPVM_VALUE_int*)((intptr_t)object + (intptr_t)env->object_ref_count_byte_offset)))
#define SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(object) ((*(SPVM_VALUE_int*)((intptr_t)object + (intptr_t)env->object_ref_count_byte_offset))++)
#define SPVM_RUNTIME_C_INLINE_INC_REF_COUNT(object)\
do {\
  if (object != NULL) {\
    SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(object);\
  }\
} while (0)\

#define SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(object) ((*(SPVM_VALUE_int*)((intptr_t)object + (intptr_t)env->object_ref_count_byte_offset))--)
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
    if (SPVM_RUNTIME_C_INLINE_ISWEAK(*(void**)(dist_ptr))) { env->unweaken(env, (void**)dist_ptr); }\
    if (SPVM_RUNTIME_C_INLINE_GET_REF_COUNT(*(void**)(dist_ptr)) > 1) { SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(*(void**)(dist_ptr)); }\
    else { env->dec_ref_count(env, *(void**)(dist_ptr)); }\
  }\
  *(void**)(dist_ptr) = tmp_object;\
} while (0)\


struct SPVM_runtime {
  // API
  SPVM_ENV* env;
  
  // Compiler
  SPVM_COMPILER* compiler;
  
  // Exception
  SPVM_OBJECT* exception;
  
  // Package variables
  SPVM_VALUE* package_vars_heap;
  
  SPVM_OBJECT** mortal_stack;
  
  int32_t mortal_stack_top;
  
  int32_t mortal_stack_capacity;

  int32_t memory_blocks_count;
  
  SPVM_LIST* strings;
  
  SPVM_LIST* basic_types;
  
  SPVM_HASH* basic_type_symtable;

  SPVM_LIST* packages;
  
  SPVM_HASH* package_symtable;

  SPVM_LIST* fields;
  
  SPVM_HASH* field_symtable;

  SPVM_LIST* package_vars;
  
  SPVM_HASH* package_var_symtable;

  SPVM_LIST* subs;
  
  SPVM_HASH* sub_symtable;

  SPVM_LIST* args;

  SPVM_LIST* info_field_ids;

  SPVM_LIST* info_types;
  
  SPVM_LIST* info_switch_infos;
  
  SPVM_OPCODE* opcodes;
  
  int64_t* info_longs;

  int32_t* info_sub_ids;

  int32_t* info_package_var_ids;
};

SPVM_RUNTIME* SPVM_RUNTIME_new();
void SPVM_RUNTIME_free(SPVM_RUNTIME* runtime);
SPVM_ENV* SPVM_RUNTIME_new_env(SPVM_RUNTIME* runtime);

int32_t SPVM_RUNTIME_call_sub(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* stack);
int32_t SPVM_RUNTIME_call_sub_vm(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* stack);
int32_t SPVM_RUNTIME_call_sub_native(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* stack);
int32_t SPVM_RUNTIME_call_sub_precompile(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* stack);

#endif
