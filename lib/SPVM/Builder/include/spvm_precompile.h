#ifndef SPVM_PRECOMPILE_H
#define SPVM_PRECOMPILE_H

#include "spvm_native.h"
#include "spvm_typedecl.h"

enum {
  SPVM_PRECOMPILE_C_CTYPE_ID_BYTE,
  SPVM_PRECOMPILE_C_CTYPE_ID_SHORT,
  SPVM_PRECOMPILE_C_CTYPE_ID_INT,
  SPVM_PRECOMPILE_C_CTYPE_ID_LONG,
  SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT,
  SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE,
  SPVM_PRECOMPILE_C_CTYPE_ID_BOOL_CONVERSION_OBJECT,
  SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT,
  SPVM_PRECOMPILE_C_CTYPE_ID_REF,
};

// Constant macro
#define SPVM_PRECOMPILE_OBJECT_HEADER_SIZE sizeof(SPVM_OBJECT)
#define SPVM_PRECOMPILE_OBJECT_LENGTH_BYTE_OFFSET ((int32_t)offsetof(SPVM_OBJECT, length))
#define SPVM_PRECOMPILE_OBJECT_REF_COUNT_BYTE_OFFSET ((int32_t)offsetof(SPVM_OBJECT, ref_count))
#define SPVM_PRECOMPILE_RUNTIME_EXCEPTION_BYTE_OFFSET ((int32_t)offsetof(SPVM_RUNTIME, exception))
#define SPVM_PRECOMPILE_TYPE_CODE_VOID (SPVM_NATIVE_C_BASIC_TYPE_ID_VOID)
#define SPVM_PRECOMPILE_TYPE_CODE_BYTE (SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE)
#define SPVM_PRECOMPILE_TYPE_CODE_SHORT (SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT)
#define SPVM_PRECOMPILE_TYPE_CODE_INT (SPVM_NATIVE_C_BASIC_TYPE_ID_INT)
#define SPVM_PRECOMPILE_TYPE_CODE_LONG (SPVM_NATIVE_C_BASIC_TYPE_ID_LONG)
#define SPVM_PRECOMPILE_TYPE_CODE_FLOAT (SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT)
#define SPVM_PRECOMPILE_TYPE_CODE_DOUBLE (SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE)

// Inline macro function
#define SPVM_PRECOMPILE_INLINE_INC_REF_COUNT(object) ((*(int32_t*)((intptr_t)object + SPVM_PRECOMPILE_OBJECT_REF_COUNT_BYTE_OFFSET))++)
#define SPVM_PRECOMPILE_INLINE_DEC_REF_COUNT_ONLY(object) ((*(int32_t*)((intptr_t)object + SPVM_PRECOMPILE_OBJECT_REF_COUNT_BYTE_OFFSET))--)
#define SPVM_PRECOMPILE_INLINE_GET_EXCEPTION() (*(void**)((intptr_t)SPVM_PRECOMPILE_RUNTIME + SPVM_PRECOMPILE_RUNTIME_EXCEPTION_BYTE_OFFSET))
#define SPVM_PRECOMPILE_INLINE_SET_EXCEPTION_NULL() \
  do { \
    if ((*(void**)((intptr_t)SPVM_PRECOMPILE_RUNTIME + SPVM_PRECOMPILE_RUNTIME_EXCEPTION_BYTE_OFFSET)) != NULL) { \
      env->dec_ref_count(env, stack, (*(void**)((intptr_t)SPVM_PRECOMPILE_RUNTIME + SPVM_PRECOMPILE_RUNTIME_EXCEPTION_BYTE_OFFSET))); \
    } \
    (*(void**)((intptr_t)SPVM_PRECOMPILE_RUNTIME + SPVM_PRECOMPILE_RUNTIME_EXCEPTION_BYTE_OFFSET)) = NULL; \
  } \
  while (0) \

#define SPVM_PRECOMPILE_INLINE_ISWEAK(object) ((intptr_t)object & 1)

// Parser information
struct spvm_precompile {
  SPVM_RUNTIME* runtime;
};

SPVM_PRECOMPILE* SPVM_PRECOMPILE_new();
void SPVM_PRECOMPILE_free(SPVM_PRECOMPILE* precompile);

void SPVM_PRECOMPILE_set_runtime(SPVM_PRECOMPILE* precompile, SPVM_RUNTIME* runtime);
SPVM_RUNTIME* SPVM_PRECOMPILE_get_runtime(SPVM_PRECOMPILE* precompile);

void SPVM_PRECOMPILE_create_precompile_source(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, const char* class_name);
void SPVM_PRECOMPILE_build_head(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer);
void SPVM_PRECOMPILE_build_method_declaration(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, const char* class_name, const char* method_name);
void SPVM_PRECOMPILE_build_method_implementation(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, const char* class_name, const char* method_name);

void SPVM_PRECOMPILE_add_operand(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t var_index);
void SPVM_PRECOMPILE_add_operand_address(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t var_index);

const char* SPVM_PRECOMPILE_get_ctype_name(SPVM_PRECOMPILE* precompile, int32_t ctype_id);

#endif
