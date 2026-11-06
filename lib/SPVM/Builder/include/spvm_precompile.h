// Copyright (c) 2023 Yuki Kimoto
// MIT License

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
  SPVM_PRECOMPILE_C_CTYPE_ID_CONDITION_EVALUATION_OBJECT,
  SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT,
  SPVM_PRECOMPILE_C_CTYPE_ID_REF,
};

struct spvm_precompile {
  SPVM_RUNTIME* runtime;
};

SPVM_PRECOMPILE* SPVM_PRECOMPILE_new(void);

void SPVM_PRECOMPILE_free(SPVM_PRECOMPILE* precompile);

void SPVM_PRECOMPILE_set_runtime(SPVM_PRECOMPILE* precompile, SPVM_RUNTIME* runtime);

SPVM_RUNTIME* SPVM_PRECOMPILE_get_runtime(SPVM_PRECOMPILE* precompile);

void SPVM_PRECOMPILE_build_class_source(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, SPVM_RUNTIME_BASIC_TYPE* basic_type);

void SPVM_PRECOMPILE_build_header(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer);

void SPVM_PRECOMPILE_build_method_declaration(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, SPVM_RUNTIME_BASIC_TYPE* basic_type, SPVM_RUNTIME_METHOD* method);

void SPVM_PRECOMPILE_build_method_source(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, SPVM_RUNTIME_BASIC_TYPE* current_basic_type, SPVM_RUNTIME_METHOD* current_method);

void SPVM_PRECOMPILE_build_local_vars_declaration(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, SPVM_RUNTIME_BASIC_TYPE* current_basic_type, SPVM_RUNTIME_METHOD* current_method);

void SPVM_PRECOMPILE_build_static_vars_declaration(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, SPVM_RUNTIME_BASIC_TYPE* current_basic_type, SPVM_RUNTIME_METHOD* current_method);

void SPVM_PRECOMPILE_add_operand(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t var_index);

void SPVM_PRECOMPILE_add_operand_address(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t var_index);

void SPVM_PRECOMPILE_add_cvar_for_basic_type(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, const char* basic_type_name);

void SPVM_PRECOMPILE_add_cvar_for_class_var(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, const char* class_var_abs_name);
void SPVM_PRECOMPILE_add_cvar_for_field(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, const char* field_abs_name);
void SPVM_PRECOMPILE_add_cvar_for_field_offset(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, const char* field_abs_name);
void SPVM_PRECOMPILE_add_cvar_for_field_exists_offset(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, const char* field_abs_name);
void SPVM_PRECOMPILE_add_cvar_for_field_exists_bit(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, const char* field_abs_name);
void SPVM_PRECOMPILE_add_cvar_for_field_index(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, const char* field_abs_name);
void SPVM_PRECOMPILE_add_cvar_for_static_method(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, const char* method_abs_name);
void SPVM_PRECOMPILE_add_cvar(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, const char* prefix, const char* name);
void SPVM_PRECOMPILE_replace_colon_and_dollar_with_under_score(SPVM_PRECOMPILE* precompile, char* string);

// Defined in spvm_precompile_header_content.c
const char* get_precompile_header_content();

#endif
