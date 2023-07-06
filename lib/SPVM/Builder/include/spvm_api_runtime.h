// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_API_RUNTIME_H
#define SPVM_API_RUNTIME_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_ENV_RUNTIME* SPVM_API_RUNTIME_new_env();

// Runtime
SPVM_RUNTIME* SPVM_API_RUNTIME_new_instance();
void SPVM_API_RUNTIME_free_instance(SPVM_RUNTIME* runtime);

// Basic type
int32_t SPVM_API_RUNTIME_get_basic_types_length(SPVM_RUNTIME* runtime);
SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_basic_type_by_id(SPVM_RUNTIME* runtime, int32_t basic_type_id);
SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_basic_type_by_name(SPVM_RUNTIME* runtime, const char* basic_type_name);

int32_t SPVM_API_RUNTIME_get_basic_type_id(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);

int32_t SPVM_API_RUNTIME_get_basic_type_anon_basic_type_id(SPVM_RUNTIME* runtime, int32_t basic_type_id, int32_t anon_basic_type_index);

const char* SPVM_API_RUNTIME_get_basic_type_constant_string_value_nolen(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t constant_string_index);
const char* SPVM_API_RUNTIME_get_basic_type_constant_string_value(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t constant_string_index, int32_t* string_length);
int32_t SPVM_API_RUNTIME_get_basic_type_category(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
const char* SPVM_API_RUNTIME_get_basic_type_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_anon_basic_types_base(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_anon_basic_types_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_is_anon(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
const char* SPVM_API_RUNTIME_get_basic_type_module_rel_file(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
const char* SPVM_API_RUNTIME_get_basic_type_module_dir(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_fields_base(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_fields_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_methods_base(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_methods_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_class_vars_base(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_class_vars_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_basic_type_parent(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_is_pointer(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
const char* SPVM_API_RUNTIME_get_basic_type_version_string(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_basic_type_anon_basic_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t anon_basic_type_index);

// Class variable
SPVM_RUNTIME_CLASS_VAR* SPVM_API_RUNTIME_get_class_var(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t class_var_index);
SPVM_RUNTIME_CLASS_VAR* SPVM_API_RUNTIME_get_class_var_by_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, const char* class_var_name);

int32_t SPVM_API_RUNTIME_get_class_var_index(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* class_var);
const char* SPVM_API_RUNTIME_get_class_var_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_CLASS_VAR* class_var);
SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_class_var_current_basic_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_CLASS_VAR* class_var);
SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_class_var_basic_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_CLASS_VAR* class_var);
int32_t SPVM_API_RUNTIME_get_class_var_type_dimension(SPVM_RUNTIME* runtime, SPVM_RUNTIME_CLASS_VAR* class_var) ;
int32_t SPVM_API_RUNTIME_get_class_var_type_flag(SPVM_RUNTIME* runtime, SPVM_RUNTIME_CLASS_VAR* class_var);

// Field
SPVM_RUNTIME_FIELD* SPVM_API_RUNTIME_get_field(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t field_index);
SPVM_RUNTIME_FIELD* SPVM_API_RUNTIME_get_field_by_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, const char* field_name);

int32_t SPVM_API_RUNTIME_get_field_index(SPVM_RUNTIME* runtime, SPVM_RUNTIME_FIELD* field);
int32_t SPVM_API_RUNTIME_get_field_offset(SPVM_RUNTIME* runtime, SPVM_RUNTIME_FIELD* field);
SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_field_current_basic_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_FIELD* field);
int32_t SPVM_API_RUNTIME_get_field_type_dimension(SPVM_RUNTIME* runtime, SPVM_RUNTIME_FIELD* field) ;
SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_field_basic_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_FIELD* field);
int32_t SPVM_API_RUNTIME_get_field_type_flag(SPVM_RUNTIME* runtime, SPVM_RUNTIME_FIELD* field);
const char* SPVM_API_RUNTIME_get_field_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_FIELD* field);

// Method
SPVM_RUNTIME_METHOD* SPVM_API_RUNTIME_get_method(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t method_index);
SPVM_RUNTIME_METHOD* SPVM_API_RUNTIME_get_method_by_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, const char* method_name);

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_method_current_basic_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_opcodes_base(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_opcodes_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_index(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
const char* SPVM_API_RUNTIME_get_method_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_is_class_method(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_is_anon(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_is_native(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_is_precompile(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_args_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_required_args_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_args_base(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_call_stack_byte_vars_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_call_stack_short_vars_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_call_stack_int_vars_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_call_stack_long_vars_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_call_stack_float_vars_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_call_stack_double_vars_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_call_stack_object_vars_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_call_stack_ref_vars_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_mortal_stack_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_is_enum(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_method_return_basic_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_return_type_dimension(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_return_type_flag(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
void SPVM_API_RUNTIME_set_native_method_address(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method, void* address);
void SPVM_API_RUNTIME_set_precompile_method_address(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method, void* address);
void* SPVM_API_RUNTIME_get_native_method_address(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
void* SPVM_API_RUNTIME_get_precompile_method_address(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);

// Argument
SPVM_RUNTIME_ARG* SPVM_API_RUNTIME_get_arg(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method, int32_t arg_index);
SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_arg_basic_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_ARG* arg);
int32_t SPVM_API_RUNTIME_get_arg_type_dimension(SPVM_RUNTIME* runtime, SPVM_RUNTIME_ARG* arg);
int32_t SPVM_API_RUNTIME_get_arg_type_flag(SPVM_RUNTIME* runtime, SPVM_RUNTIME_ARG* arg);

// Opcode
SPVM_OPCODE* SPVM_API_RUNTIME_get_opcodes(SPVM_RUNTIME* runtime);

// Type utility
int32_t SPVM_API_RUNTIME_is_object_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t flag);
int32_t SPVM_API_RUNTIME_has_interface(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, SPVM_RUNTIME_BASIC_TYPE* interface_basic_type);

int32_t SPVM_API_RUNTIME_is_super(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* super_basic_type, SPVM_RUNTIME_BASIC_TYPE* child_basic_type);
int32_t SPVM_API_RUNTIME_can_assign(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* dist_basic_type, int32_t dist_type_dimension, int32_t dist_type_flag, SPVM_RUNTIME_BASIC_TYPE* src_basic_type, int32_t src_type_dimension, int32_t src_type_flag);

void SPVM_API_PRECOMPILE_build_precompile_module_source(SPVM_RUNTIME* runtime, SPVM_STRING_BUFFER* string_buffer, const char* module_name);

void SPVM_API_PRECOMPILE_build_precompile_method_source(SPVM_RUNTIME* runtime, SPVM_STRING_BUFFER* string_buffer, const char* module_name, const char* method_name);

#endif
