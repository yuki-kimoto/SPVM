#ifndef SPVM_RUNTIME_H
#define SPVM_RUNTIME_H

#include "spvm_base.h"
#include "spvm_native.h"

/*
  "& ~(intptr_t)1" means dropping weaken flag
*/

#define SPVM_RUNTIME_C_INLINE_GET_OBJECT_NO_WEAKEN_ADDRESS(object) ((void*)((intptr_t)object & ~(intptr_t)1))
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

#define SPVM_RUNTIME_C_INLINE_ISWEAK(dist_address) (((intptr_t)*(void**)dist_address) & 1)
#define SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(dist_address, src_object) \
do {\
  void* tmp_object = src_object;\
  if (tmp_object != NULL) {\
    SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(tmp_object);\
  }\
  if (*(void**)(dist_address) != NULL) {\
    if (SPVM_RUNTIME_C_INLINE_ISWEAK(dist_address)) { env->unweaken(env, (void**)dist_address); }\
    if (SPVM_RUNTIME_C_INLINE_GET_REF_COUNT(*(void**)(dist_address)) > 1) { SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(*(void**)(dist_address)); }\
    else { env->dec_ref_count(env, *(void**)(dist_address)); }\
  }\
  *(void**)(dist_address) = tmp_object;\
} while (0)\


struct SPVM_runtime {
  
  char** symbols;
  int32_t symbols_length;
  
  SPVM_OPCODE* opcodes;
  
  SPVM_RUNTIME_MY* args;
  SPVM_RUNTIME_MY* mys;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_types;
  int32_t basic_types_length;

  SPVM_RUNTIME_FIELD* fields;
  int32_t fields_length;

  SPVM_RUNTIME_PACKAGE_VAR* package_vars;
  int32_t package_vars_length;

  SPVM_RUNTIME_SUB* subs;
  int32_t subs_length;

  SPVM_RUNTIME_PACKAGE* packages;
  int32_t packages_length;
  
  int64_t* info_long_values;
  double* info_double_values;
  char** info_string_values;
  int32_t info_string_values_length;
  int32_t* info_string_lengths;
  int32_t* info_sub_ids;
  int32_t* info_package_var_ids;
  int32_t* info_field_ids;
  SPVM_RUNTIME_INFO_TYPE* info_types;
  
  void** sub_native_addresses;
  void** sub_precompile_addresses;

  SPVM_LIST* info_switch_infos;
  
  // Symbol table
  SPVM_HASH* basic_type_symtable;
  SPVM_HASH* package_symtable;
  SPVM_HASH* field_symtable;
  SPVM_HASH* sub_symtable;

  // Exception
  SPVM_OBJECT* exception;
  
  // Package variables
  SPVM_VALUE* package_vars_heap;
  
  // Mortal stack
  SPVM_OBJECT** mortal_stack;
  int32_t mortal_stack_top;
  int32_t mortal_stack_capacity;
  
  // Memory blocks count
  int32_t memory_blocks_count;
  
  // Variable allocation max length
  int32_t vars_alloc_length_max;
  
  SPVM_PORTABLE* portable;
};

SPVM_ENV* SPVM_RUNTIME_create_env(SPVM_RUNTIME* runtime);
SPVM_ENV* SPVM_RUNTIME_build_runtime_env(SPVM_PORTABLE* portable);
void SPVM_RUNTIME_free(SPVM_ENV* env);

#endif
