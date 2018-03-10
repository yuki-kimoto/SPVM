#ifndef SPVM_RUNTIME_H
#define SPVM_RUNTIME_H

#include "spvm_base.h"
#include "spvm_api.h"

#define SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE sizeof(SPVM_OBJECT)
#define SPVM_RUNTIME_C_OBJECT_LENGTH_BYTE_OFFSET ((int32_t)offsetof(SPVM_OBJECT, length))
#define SPVM_RUNTIME_C_OBJECT_REF_COUNT_BYTE_OFFSET ((int32_t)offsetof(SPVM_OBJECT, ref_count))
#define SPVM_RUNTIME_C_RUNTIME_EXCEPTION_BYTE_OFFSET ((int32_t)offsetof(SPVM_RUNTIME, exception))

#define SPVM_RUNTIME_C_INLINE_GET_REF_COUNT(object) ((*(SPVM_API_int*)((intptr_t)object + SPVM_RUNTIME_C_OBJECT_REF_COUNT_BYTE_OFFSET)))
#define SPVM_RUNTIME_C_INLINE_INC_REF_COUNT(object) ((*(SPVM_API_int*)((intptr_t)object + SPVM_RUNTIME_C_OBJECT_REF_COUNT_BYTE_OFFSET))++)
#define SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(object) ((*(SPVM_API_int*)((intptr_t)object + SPVM_RUNTIME_C_OBJECT_REF_COUNT_BYTE_OFFSET))--)
#define SPVM_RUNTIME_C_INLINE_ISWEAK(object) ((intptr_t)object & 1)

enum {
  SPVM_RUNTIME_C_JIT_MODE_AUTO,
  SPVM_RUNTIME_C_JIT_MODE_NONE,
  SPVM_RUNTIME_C_JIT_MODE_ALL,
};

struct SPVM_runtime {
  // Exception
  SPVM_OBJECT* exception;
  
  // Runtime memory allocator
  SPVM_RUNTIME_ALLOCATOR* allocator;

  // Env
  SPVM_API* api;
  
  // opcodes
  SPVM_OPCODE* opcodes;
  
  // Constant pool
  int32_t* constant_pool;
  
  // Constant pool field symbol table
  SPVM_HASH* field_symtable;
  
  // Package variables
  SPVM_API_VALUE* package_vars;
  
  // Type code to id
  int32_t type_code_to_id_base;
  
  int32_t objects_count;
  
  int8_t jit_mode;
  
  SPVM_COMPILER* compiler;
};

SPVM_RUNTIME* SPVM_RUNTIME_new();
void SPVM_RUNTIME_free(SPVM_RUNTIME* runtime);
SPVM_API* SPVM_RUNTIME_new_api(SPVM_RUNTIME* runtime);

SPVM_API_VALUE SPVM_RUNTIME_call_sub(SPVM_API* api, int32_t sub_id, SPVM_API_VALUE* args);

SPVM_API_VALUE SPVM_RUNTIME_call_sub_vm(SPVM_API* api, int32_t sub_id, SPVM_API_VALUE* args);
SPVM_API_VALUE SPVM_RUNTIME_call_sub_native(SPVM_API* api, int32_t sub_id, SPVM_API_VALUE* args);
SPVM_API_VALUE SPVM_RUNTIME_call_sub_jit(SPVM_API* api, int32_t sub_id, SPVM_API_VALUE* args);

#endif
