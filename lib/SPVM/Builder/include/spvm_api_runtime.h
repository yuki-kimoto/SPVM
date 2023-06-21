// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_API_RUNTIME_H
#define SPVM_API_RUNTIME_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_ENV_RUNTIME* SPVM_API_RUNTIME_new_env();

// Private
SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_basic_type_by_id(SPVM_RUNTIME* runtime, int32_t basic_type_id);
SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_basic_type_by_name(SPVM_RUNTIME* runtime, const char* basic_type_name);
SPVM_RUNTIME_CLASS_VAR* SPVM_API_RUNTIME_get_class_var_by_address_id(SPVM_RUNTIME* runtime, int32_t class_var_address_id);
SPVM_RUNTIME_CLASS_VAR* SPVM_API_RUNTIME_get_class_var_by_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, const char* search_class_var_name);
SPVM_RUNTIME_FIELD* SPVM_API_RUNTIME_get_field_by_address_id(SPVM_RUNTIME* runtime, int32_t field_address_id);
SPVM_RUNTIME_METHOD* SPVM_API_RUNTIME_get_method_by_address_id(SPVM_RUNTIME* runtime, int32_t method_address_id);

// Runtime
SPVM_RUNTIME* SPVM_API_RUNTIME_new_object();
void SPVM_API_RUNTIME_free_object(SPVM_RUNTIME* runtime);
void SPVM_API_RUNTIME_build(SPVM_RUNTIME* runtime, int32_t* runtime_codes);

// Runtime codes
int32_t* SPVM_API_RUNTIME_get_runtime_codes(SPVM_RUNTIME* runtime);
int32_t SPVM_API_RUNTIME_get_runtime_codes_length(SPVM_RUNTIME* runtime);

// Constant string
int32_t SPVM_API_RUNTIME_get_constant_string_id(SPVM_RUNTIME* runtime, const char* string);
const char* SPVM_API_RUNTIME_get_constant_string_value(SPVM_RUNTIME* runtime, int32_t constant_string_id, int32_t* string_length);
const char* SPVM_API_RUNTIME_get_name(SPVM_RUNTIME* runtime, int32_t constant_string_id);

// Basic type
int32_t SPVM_API_RUNTIME_get_basic_types_length(SPVM_RUNTIME* runtime);
int32_t SPVM_API_RUNTIME_get_basic_type_id_by_name(SPVM_RUNTIME* runtime, const char* basic_type_name);
int32_t SPVM_API_RUNTIME_get_basic_type_category(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_name_id(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
const char* SPVM_API_RUNTIME_get_basic_type_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_basic_type_id(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_anon_basic_types_base_address_id(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_anon_basic_types_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_is_anon(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_module_dir_id(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_module_rel_file_id(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_fields_base_address_id(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_fields_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_methods_base_address_id(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_methods_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_class_vars_base_address_id(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_class_vars_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_parent_id(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_is_pointer(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_version_string_id(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_parent_id(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_version_string_id(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);

// Class variable
SPVM_RUNTIME_CLASS_VAR* SPVM_API_RUNTIME_get_class_var(SPVM_RUNTIME* runtime, int32_t basic_type_id, int32_t class_var_index);
int32_t SPVM_API_RUNTIME_get_class_var_address_id_by_name(SPVM_RUNTIME* runtime, const char* basic_type_name, const char* class_var_name);
int32_t SPVM_API_RUNTIME_get_class_var_name_id(SPVM_RUNTIME* runtime, SPVM_RUNTIME_CLASS_VAR* class_var);
int32_t SPVM_API_RUNTIME_get_class_var_current_basic_type_id(SPVM_RUNTIME* runtime, SPVM_RUNTIME_CLASS_VAR* class_var);
int32_t SPVM_API_RUNTIME_get_class_var_basic_type_id(SPVM_RUNTIME* runtime, SPVM_RUNTIME_CLASS_VAR* class_var);
int32_t SPVM_API_RUNTIME_get_class_var_type_dimension(SPVM_RUNTIME* runtime, SPVM_RUNTIME_CLASS_VAR* class_var) ;
int32_t SPVM_API_RUNTIME_get_class_var_type_flag(SPVM_RUNTIME* runtime, SPVM_RUNTIME_CLASS_VAR* class_var);

// Field
SPVM_RUNTIME_FIELD* SPVM_API_RUNTIME_get_field(SPVM_RUNTIME* runtime, int32_t basic_type_id, int32_t field_index);
SPVM_RUNTIME_FIELD* SPVM_API_RUNTIME_get_field_by_name(SPVM_RUNTIME* runtime, int32_t basic_type_id, const char* field_name);
int32_t SPVM_API_RUNTIME_get_field_address_id_by_index(SPVM_RUNTIME* runtime, int32_t basic_type_id, int32_t field_index);
int32_t SPVM_API_RUNTIME_get_field_address_id_by_name(SPVM_RUNTIME* runtime, const char* basic_type_name, const char* field_name);
int32_t SPVM_API_RUNTIME_get_field_current_basic_type_id(SPVM_RUNTIME* runtime, SPVM_RUNTIME_FIELD* field);
int32_t SPVM_API_RUNTIME_get_field_basic_type_id(SPVM_RUNTIME* runtime, SPVM_RUNTIME_FIELD* field);
int32_t SPVM_API_RUNTIME_get_field_type_dimension(SPVM_RUNTIME* runtime, SPVM_RUNTIME_FIELD* field) ;
int32_t SPVM_API_RUNTIME_get_field_type_flag(SPVM_RUNTIME* runtime, SPVM_RUNTIME_FIELD* field);
int32_t SPVM_API_RUNTIME_get_field_name_id(SPVM_RUNTIME* runtime, SPVM_RUNTIME_FIELD* field);

// Method
SPVM_RUNTIME_METHOD* SPVM_API_RUNTIME_get_method(SPVM_RUNTIME* runtime, int32_t basic_type_id, int32_t method_index);
SPVM_RUNTIME_METHOD* SPVM_API_RUNTIME_get_method_by_name(SPVM_RUNTIME* runtime, int32_t basic_type_id, const char* method_name);
int32_t SPVM_API_RUNTIME_get_method_address_id_by_index(SPVM_RUNTIME* runtime, int32_t basic_type_id, int32_t method_index);
int32_t SPVM_API_RUNTIME_get_method_address_id_by_name(SPVM_RUNTIME* runtime, const char* basic_type_name, const char* method_name);
int32_t SPVM_API_RUNTIME_get_method_current_basic_type_id(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_opcodes_base_address_id(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_opcodes_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_name_id(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_is_static(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_is_anon(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_is_native(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_is_precompile(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_args_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_required_args_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_args_base_address_id(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
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
int32_t SPVM_API_RUNTIME_get_method_return_basic_type_id(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_return_type_dimension(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_RUNTIME_get_method_return_type_flag(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);

// Argument
int32_t SPVM_API_RUNTIME_get_arg_basic_type_id(SPVM_RUNTIME* runtime, int32_t arg_id);
int32_t SPVM_API_RUNTIME_get_arg_type_dimension(SPVM_RUNTIME* runtime, int32_t arg_id);
int32_t SPVM_API_RUNTIME_get_arg_type_flag(SPVM_RUNTIME* runtime, int32_t arg_id);

// Opcode
SPVM_OPCODE* SPVM_API_RUNTIME_get_opcodes(SPVM_RUNTIME* runtime);
int32_t SPVM_API_RUNTIME_get_opcodes_length(SPVM_RUNTIME* runtime);

// Anon basic type
int32_t SPVM_API_RUNTIME_get_anon_basic_type_id(SPVM_RUNTIME* runtime, int32_t anon_basic_type_address_id);

// Native and precompile method
void SPVM_API_RUNTIME_set_native_method_address(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method, void* address);
void SPVM_API_RUNTIME_set_precompile_method_address(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method, void* address);
void* SPVM_API_RUNTIME_get_native_method_address(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);
void* SPVM_API_RUNTIME_get_precompile_method_address(SPVM_RUNTIME* runtime, SPVM_RUNTIME_METHOD* method);

// Type utility
int32_t SPVM_API_RUNTIME_is_object_type(SPVM_RUNTIME* runtime, int32_t basic_type_id, int32_t type_dimension, int32_t flag);
int32_t SPVM_API_RUNTIME_has_interface_by_id(SPVM_RUNTIME* runtime, int32_t basic_type_id, int32_t interface_basic_type_id);
int32_t SPVM_API_RUNTIME_is_super_by_id(SPVM_RUNTIME* runtime, int32_t super_basic_type_id, int32_t child_basic_type_id);
int32_t SPVM_API_RUNTIME_can_assign(SPVM_RUNTIME* runtime, int32_t dist_basic_type_id, int32_t dist_type_dimension, int32_t dist_type_flag, int32_t src_basic_type_id, int32_t src_type_dimension, int32_t src_type_flag);

// Allocation
SPVM_ALLOCATOR* SPVM_API_RUNTIME_get_allocator(SPVM_RUNTIME* runtime);

#endif
