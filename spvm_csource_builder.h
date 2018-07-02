#ifndef SPVM_CSOURCE_BUILDER_H
#define SPVM_CSOURCE_BUILDER_H

#include "spvm_base.h"

// Constant macro
#define SPVM_CSOURCE_BUILDER_OBJECT_HEADER_BYTE_SIZE sizeof(SPVM_OBJECT)
#define SPVM_CSOURCE_BUILDER_OBJECT_LENGTH_BYTE_OFFSET ((int32_t)offsetof(SPVM_OBJECT, length))
#define SPVM_CSOURCE_BUILDER_OBJECT_REF_COUNT_BYTE_OFFSET ((int32_t)offsetof(SPVM_OBJECT, ref_count))
#define SPVM_CSOURCE_BUILDER_RUNTIME_EXCEPTION_BYTE_OFFSET ((int32_t)offsetof(SPVM_RUNTIME, exception))
#define SPVM_CSOURCE_BUILDER_TYPE_CODE_VOID (SPVM_BASIC_TYPE_C_ID_VOID)
#define SPVM_CSOURCE_BUILDER_TYPE_CODE_BYTE (SPVM_BASIC_TYPE_C_ID_BYTE)
#define SPVM_CSOURCE_BUILDER_TYPE_CODE_SHORT (SPVM_BASIC_TYPE_C_ID_SHORT)
#define SPVM_CSOURCE_BUILDER_TYPE_CODE_INT (SPVM_BASIC_TYPE_C_ID_INT)
#define SPVM_CSOURCE_BUILDER_TYPE_CODE_LONG (SPVM_BASIC_TYPE_C_ID_LONG)
#define SPVM_CSOURCE_BUILDER_TYPE_CODE_FLOAT (SPVM_BASIC_TYPE_C_ID_FLOAT)
#define SPVM_CSOURCE_BUILDER_TYPE_CODE_DOUBLE (SPVM_BASIC_TYPE_C_ID_DOUBLE)

// Inline macro function
#define SPVM_CSOURCE_BUILDER_INLINE_INC_REF_COUNT(object) ((*(int32_t*)((intptr_t)object + SPVM_CSOURCE_BUILDER_OBJECT_REF_COUNT_BYTE_OFFSET))++)
#define SPVM_CSOURCE_BUILDER_INLINE_DEC_REF_COUNT_ONLY(object) ((*(int32_t*)((intptr_t)object + SPVM_CSOURCE_BUILDER_OBJECT_REF_COUNT_BYTE_OFFSET))--)
#define SPVM_CSOURCE_BUILDER_INLINE_GET_EXCEPTION() (*(void**)((intptr_t)SPVM_CSOURCE_BUILDER_RUNTIME + SPVM_CSOURCE_BUILDER_RUNTIME_EXCEPTION_BYTE_OFFSET))
#define SPVM_CSOURCE_BUILDER_INLINE_SET_EXCEPTION_NULL() \
  do { \
    if ((*(void**)((intptr_t)SPVM_CSOURCE_BUILDER_RUNTIME + SPVM_CSOURCE_BUILDER_RUNTIME_EXCEPTION_BYTE_OFFSET)) != NULL) { \
      env->dec_ref_count(env, (*(void**)((intptr_t)SPVM_CSOURCE_BUILDER_RUNTIME + SPVM_CSOURCE_BUILDER_RUNTIME_EXCEPTION_BYTE_OFFSET))); \
    } \
    (*(void**)((intptr_t)SPVM_CSOURCE_BUILDER_RUNTIME + SPVM_CSOURCE_BUILDER_RUNTIME_EXCEPTION_BYTE_OFFSET)) = NULL; \
  } \
  while (0) \

#define SPVM_CSOURCE_BUILDER_INLINE_ISWEAK(object) ((intptr_t)object & 1)


void SPVM_CSOURCE_BUILDER_build_head(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer);
void SPVM_CSOURCE_BUILDER_build_sub_declaration(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* package_name, const char* sub_name);
void SPVM_CSOURCE_BUILDER_build_sub_implementation(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* package_name, const char* sub_name);
void SPVM_CSOURCE_BUILDER_build_package_csource(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* package_name);

void SPVM_CSOURCE_BUILDER_add_get_field(SPVM_STRING_BUFFER* string_buffer, const char* field_type_name, int32_t out_index, int32_t object_index, SPVM_FIELD* field);
void SPVM_CSOURCE_BUILDER_add_set_field(SPVM_STRING_BUFFER* string_buffer, const char* field_type_name, int32_t object_index, SPVM_FIELD* field, int32_t in_index);

#endif
